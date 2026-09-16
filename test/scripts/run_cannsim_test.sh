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

if [ ! -x "$CANNSIM_EXECUTABLE" ] || [ ! -x "$APPLICATION" ] || [ ! -d "$RUNTIME_LIBRARY_DIR" ]; then
    echo "Cannsim runner input is missing or not executable." >&2
    exit 2
fi

export LD_LIBRARY_PATH="$RUNTIME_LIBRARY_DIR${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
mkdir -p "$RESULT_ROOT" || exit 2
RESULT_DIR="$(mktemp -d "$RESULT_ROOT/run.XXXXXX")" || exit 2
COMMAND_LOG="$RESULT_DIR/cannsim-command.log"

"$CANNSIM_EXECUTABLE" record -o "$RESULT_DIR/output" -s "$SIMULATOR_SOC" "$APPLICATION" \
    >"$COMMAND_LOG" 2>&1
CANNSIM_STATUS=$?
sed -n '1,320p' "$COMMAND_LOG"
if [ "$CANNSIM_STATUS" -ne 0 ]; then
    echo "cannsim record failed with status $CANNSIM_STATUS; results preserved at $RESULT_DIR" >&2
    exit 1
fi
if grep -Fq "Mismatch at" "$COMMAND_LOG"; then
    echo "Cannsim golden output mismatch; results preserved at $RESULT_DIR" >&2
    exit 1
fi
PASS_MARKER_COUNT="$(grep -Fo -- "$PASS_MARKER" "$COMMAND_LOG" | wc -l)"
if [ "$PASS_MARKER_COUNT" -ne 1 ]; then
    echo "Expected one cannsim PASS marker, found $PASS_MARKER_COUNT" >&2
    exit 1
fi
if ! grep -Eq "task [0-9]+ done|Simulation SUCCESS|sendStarsSQE" "$COMMAND_LOG"; then
    echo "Cannsim output has no simulated dispatch completion evidence." >&2
    exit 1
fi
echo "ASC_STL_CANNSIM_GATE_PASS"
