#!/usr/bin/env bash
# Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
RUNNER="$ROOT/run_cannsim_test.sh"
TEST_ROOT="$(mktemp -d "${TMPDIR:-/tmp}/asc-stl-cannsim-runner.XXXXXX")"
trap 'rm -rf -- "$TEST_ROOT"' EXIT

FAKE_CANNSIM="$TEST_ROOT/fake-cannsim"
FAKE_APPLICATION="$TEST_ROOT/fake-application"
FAKE_RUNTIME="$TEST_ROOT/runtime"
mkdir -p "$FAKE_RUNTIME"

printf '%s\n' '#!/usr/bin/env bash' 'exit 0' >"$FAKE_APPLICATION"
chmod +x "$FAKE_APPLICATION"

printf '%s\n' \
    '#!/usr/bin/env bash' \
    'set -euo pipefail' \
    'output=""' \
    'while [ "$#" -gt 0 ]; do' \
    '    if [ "$1" = "--output" ]; then output="$2"; shift 2; else shift; fi' \
    'done' \
    'case "${FAKE_CANNSIM_MODE:?}" in' \
    '    nonzero) exit 7 ;;' \
    '    no_log) exit 0 ;;' \
    '    no_marker) mkdir -p "$output/result"; printf "%s\\n" "simulation complete" >"$output/result/cannsim.log" ;;' \
    '    mismatch) mkdir -p "$output/result"; printf "%s\\n" "Mismatch at 3" "ASC_STL_CANNSIM_SMOKE_PASS" >"$output/result/cannsim.log" ;;' \
    '    no_dispatch) mkdir -p "$output/result"; printf "%s\\n" "ASC_STL_CANNSIM_SMOKE_PASS" >"$output/result/cannsim.log" ;;' \
    '    pass) mkdir -p "$output/result"; printf "%s\\n" "sendStarsSQE" "ASC_STL_CANNSIM_SMOKE_PASS" >"$output/result/cannsim.log" ;;' \
    '    npusim_no_marker) mkdir -p "$output/result"; printf "%s\\n" "sendStarsSQE" "[TASK_BEGIN] task_id:0" "[TASK_DONE] task_id:0" >"$output/result/npusim.log" ;;' \
    '    npusim_mismatch) mkdir -p "$output/result"; printf "%s\\n" "sendStarsSQE" "[TASK_BEGIN] task_id:0" "Mismatch at 3" "[TASK_DONE] task_id:0" "ASC_STL_CANNSIM_SMOKE_PASS" >"$output/result/npusim.log" ;;' \
    '    npusim_no_dispatch) mkdir -p "$output/result"; printf "%s\\n" "[TASK_BEGIN] task_id:0" "[TASK_DONE] task_id:0" "ASC_STL_CANNSIM_SMOKE_PASS" >"$output/result/npusim.log" ;;' \
    '    npusim_no_begin) mkdir -p "$output/result"; printf "%s\\n" "sendStarsSQE" "[TASK_DONE] task_id:0" "ASC_STL_CANNSIM_SMOKE_PASS" >"$output/result/npusim.log" ;;' \
    '    npusim_no_completion) mkdir -p "$output/result"; printf "%s\\n" "sendStarsSQE" "[TASK_BEGIN] task_id:0" "ASC_STL_CANNSIM_SMOKE_PASS" >"$output/result/npusim.log" ;;' \
    '    npusim_duplicate_marker) mkdir -p "$output/result"; printf "%s\\n" "sendStarsSQE" "[TASK_BEGIN] task_id:0" "[TASK_DONE] task_id:0" "ASC_STL_CANNSIM_SMOKE_PASS ASC_STL_CANNSIM_SMOKE_PASS" >"$output/result/npusim.log" ;;' \
    '    npusim_pass) mkdir -p "$output/result"; printf "%s\\n" "sendStarsSQE" "[TASK_BEGIN] task_id:0" "[TASK_DONE] task_id:0" "ASC_STL_CANNSIM_SMOKE_PASS" >"$output/result/npusim.log" ;;' \
    '    ambiguous_logs) mkdir -p "$output/result"; printf "%s\\n" "sendStarsSQE" "ASC_STL_CANNSIM_SMOKE_PASS" | tee "$output/result/cannsim.log" >"$output/result/npusim.log" ;;' \
    'esac' >"$FAKE_CANNSIM"
chmod +x "$FAKE_CANNSIM"

expect_failure() {
    local mode="$1"
    local expected_error="${2:-}"
    if FAKE_CANNSIM_MODE="$mode" "$RUNNER" \
        "$FAKE_CANNSIM" "$FAKE_APPLICATION" Ascend950 "$TEST_ROOT/$mode" "$FAKE_RUNTIME" \
        ASC_STL_CANNSIM_SMOKE_PASS \
        >"$TEST_ROOT/$mode.output" 2>&1; then
        echo "Runner unexpectedly accepted negative case: $mode" >&2
        return 1
    fi
    if [ -n "$expected_error" ]; then
        grep -Fq "$expected_error" "$TEST_ROOT/$mode.output"
    fi
}

expect_failure nonzero
expect_failure no_log
expect_failure no_marker
expect_failure mismatch
expect_failure no_dispatch
expect_failure npusim_no_marker "Expected one cannsim PASS marker"
expect_failure npusim_mismatch "Cannsim golden output mismatch"
expect_failure npusim_no_dispatch "Npusim log has no simulated kernel dispatch evidence"
expect_failure npusim_no_begin "Npusim log has no simulated task begin evidence"
expect_failure npusim_no_completion "Npusim log has no completed simulated task evidence"
expect_failure npusim_duplicate_marker "Expected one cannsim PASS marker, found 2"
expect_failure ambiguous_logs "Expected exactly one supported simulator log"

FAKE_CANNSIM_MODE=pass "$RUNNER" \
    "$FAKE_CANNSIM" "$FAKE_APPLICATION" Ascend950 "$TEST_ROOT/pass" "$FAKE_RUNTIME" \
    ASC_STL_CANNSIM_SMOKE_PASS \
    >"$TEST_ROOT/pass.output" 2>&1
grep -Fxq "ASC_STL_CANNSIM_GATE_PASS" "$TEST_ROOT/pass.output"

FAKE_CANNSIM_MODE=npusim_pass "$RUNNER" \
    "$FAKE_CANNSIM" "$FAKE_APPLICATION" Ascend950 "$TEST_ROOT/npusim_pass" "$FAKE_RUNTIME" \
    ASC_STL_CANNSIM_SMOKE_PASS \
    >"$TEST_ROOT/npusim_pass.output" 2>&1
grep -Fxq "ASC_STL_CANNSIM_GATE_PASS" "$TEST_ROOT/npusim_pass.output"

echo "ASC_STL_CANNSIM_RUNNER_SELF_TEST_PASS"
