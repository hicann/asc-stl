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

set -uo pipefail

if [ "$#" -ne 6 ]; then
    echo "Usage: $0 <cannsim> <application> <simulator-soc> <result-root> <runtime-library-dir> <pass-marker>" >&2
    exit 2
fi

CANNSIM_EXECUTABLE="$1"
APPLICATION="$2"
SIMULATOR_SOC="$3"
RESULT_ROOT="$4"
RUNTIME_LIBRARY_DIR="$5"
PASS_MARKER="$6"

if [ ! -x "$CANNSIM_EXECUTABLE" ]; then
    echo "Cannsim executable is missing or not executable: $CANNSIM_EXECUTABLE" >&2
    exit 2
fi
if [ ! -x "$APPLICATION" ]; then
    echo "Cannsim application is missing or not executable: $APPLICATION" >&2
    exit 2
fi
if [ ! -d "$RUNTIME_LIBRARY_DIR" ]; then
    echo "Cannsim runtime library directory is missing: $RUNTIME_LIBRARY_DIR" >&2
    exit 2
fi

export LD_LIBRARY_PATH="$RUNTIME_LIBRARY_DIR${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

mkdir -p "$RESULT_ROOT" || exit 2
RESULT_DIR="$(mktemp -d "$RESULT_ROOT/run.XXXXXX")" || exit 2
COMMAND_LOG="$RESULT_DIR/cannsim-command.log"
echo "Cannsim result directory: $RESULT_DIR"

"$CANNSIM_EXECUTABLE" record "$APPLICATION" \
    --soc-version "$SIMULATOR_SOC" \
    --gen-report \
    --output "$RESULT_DIR" >"$COMMAND_LOG" 2>&1
CANNSIM_STATUS=$?
sed -n '1,240p' "$COMMAND_LOG"

if [ "$CANNSIM_STATUS" -ne 0 ]; then
    echo "cannsim record failed with status $CANNSIM_STATUS; results preserved at $RESULT_DIR" >&2
    exit 1
fi

mapfile -t CANNSIM_LOGS < <(
    find "$RESULT_DIR" -type f \( -name cannsim.log -o -name npusim.log \) -print
)
if [ "${#CANNSIM_LOGS[@]}" -ne 1 ]; then
    echo "Expected exactly one supported simulator log (cannsim.log or npusim.log), found ${#CANNSIM_LOGS[@]}; results preserved at $RESULT_DIR" >&2
    exit 1
fi

SIMULATOR_LOG="${CANNSIM_LOGS[0]}"
SIMULATOR_LOG_NAME="$(basename "$SIMULATOR_LOG")"
sed -n '1,240p' "$SIMULATOR_LOG"
if grep -Fq "Mismatch at" "$SIMULATOR_LOG"; then
    echo "Cannsim golden output mismatch; results preserved at $RESULT_DIR" >&2
    exit 1
fi

case "$SIMULATOR_LOG_NAME" in
    cannsim.log)
        if ! grep -Fq "sendStarsSQE" "$SIMULATOR_LOG"; then
            echo "Cannsim log has no simulated kernel dispatch evidence; results preserved at $RESULT_DIR" >&2
            exit 1
        fi
        PASS_MARKER_COUNT="$(grep -Fxc "$PASS_MARKER" "$SIMULATOR_LOG" || true)"
        ;;
    npusim.log)
        if ! grep -Fq "sendStarsSQE" "$SIMULATOR_LOG"; then
            echo "Npusim log has no simulated kernel dispatch evidence; results preserved at $RESULT_DIR" >&2
            exit 1
        fi
        if ! grep -Fq "[TASK_BEGIN]" "$SIMULATOR_LOG"; then
            echo "Npusim log has no simulated task begin evidence; results preserved at $RESULT_DIR" >&2
            exit 1
        fi
        if ! grep -Fq "[TASK_DONE]" "$SIMULATOR_LOG"; then
            echo "Npusim log has no completed simulated task evidence; results preserved at $RESULT_DIR" >&2
            exit 1
        fi
        PASS_MARKER_COUNT="$(grep -Fo -- "$PASS_MARKER" "$SIMULATOR_LOG" | wc -l)"
        ;;
esac

if [ "$PASS_MARKER_COUNT" -ne 1 ]; then
    echo "Expected one cannsim PASS marker, found $PASS_MARKER_COUNT; results preserved at $RESULT_DIR" >&2
    exit 1
fi

echo "ASC_STL_CANNSIM_GATE_PASS"
