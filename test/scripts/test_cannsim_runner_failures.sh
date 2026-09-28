#!/usr/bin/env bash

# Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
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
    'case "${FAKE_CANNSIM_MODE:?}" in' \
    '  nonzero) exit 7 ;;' \
    '  no_marker) echo "Simulation SUCCESS" ;;' \
    '  mismatch) echo "Mismatch at 3"; echo "ASC_STL_CANNSIM_SMOKE_PASS" ;;' \
    '  no_dispatch) echo "ASC_STL_CANNSIM_SMOKE_PASS" ;;' \
    '  duplicate) echo "Simulation SUCCESS ASC_STL_CANNSIM_SMOKE_PASS ASC_STL_CANNSIM_SMOKE_PASS" ;;' \
    '  pass) echo "Simulation SUCCESS"; echo "ASC_STL_CANNSIM_SMOKE_PASS" ;;' \
    'esac' >"$FAKE_CANNSIM"
chmod +x "$FAKE_CANNSIM"

expect_failure() {
    local mode="$1"
    if FAKE_CANNSIM_MODE="$mode" "$RUNNER" "$FAKE_CANNSIM" "$FAKE_APPLICATION" Ascend950 \
        "$TEST_ROOT/$mode" "$FAKE_RUNTIME" ASC_STL_CANNSIM_SMOKE_PASS >/dev/null 2>&1; then
        echo "Runner unexpectedly accepted negative case: $mode" >&2
        return 1
    fi
}

expect_failure nonzero
expect_failure no_marker
expect_failure mismatch
expect_failure no_dispatch
expect_failure duplicate
FAKE_CANNSIM_MODE=pass "$RUNNER" "$FAKE_CANNSIM" "$FAKE_APPLICATION" Ascend950 \
    "$TEST_ROOT/pass" "$FAKE_RUNTIME" ASC_STL_CANNSIM_SMOKE_PASS >/dev/null
echo "ASC_STL_CANNSIM_RUNNER_SELF_TEST_PASS"
