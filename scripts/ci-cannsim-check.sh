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

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="${ASC_STL_CANNSIM_BUILD_DIR:-$ROOT/build/cannsim-gate}"

# shellcheck disable=SC1091
source "$ROOT/scripts/cann-env.sh"

CANN_PACKAGE_PATH="${ASC_STL_CANN_PACKAGE_PATH:-$ASCEND_HOME_PATH}"
TARGET_SOC="${ASC_STL_TARGET_SOC:-Ascend950PR_9599}"
SIMULATOR_SOC="${ASC_STL_CANNSIM_SOC:-Ascend950}"
CANNSIM_EXECUTABLE="${ASC_STL_CANNSIM_EXECUTABLE:-$(command -v cannsim || true)}"

if [ -z "$CANNSIM_EXECUTABLE" ] || [ ! -x "$CANNSIM_EXECUTABLE" ]; then
    echo "BLOCKED_ENVIRONMENT: cannsim is unavailable in the loaded CANN environment." >&2
    exit 2
fi

bash "$ROOT/test/scripts/test_cannsim_runner_failures.sh"

cmake -S "$ROOT" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DASC_STL_ENABLE_CANNSIM_TESTS=ON \
    -DASC_STL_CANN_PACKAGE_PATH="$CANN_PACKAGE_PATH" \
    -DASC_STL_TARGET_SOC="$TARGET_SOC" \
    -DASC_STL_CANNSIM_EXECUTABLE="$CANNSIM_EXECUTABLE" \
    -DASC_STL_CANNSIM_SOC="$SIMULATOR_SOC"

cmake --build "$BUILD_DIR" --target asc_stl_cannsim_tests
ctest --test-dir "$BUILD_DIR" -L "cannsim-smoke|cannsim-runtime" --output-on-failure
