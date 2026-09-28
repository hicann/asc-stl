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
CHANGED_TARGETS_FILE="${1:-${ASC_STL_DEVICE_CHANGED_TARGETS_FILE:-}}"
BUILD_DIR="${ASC_STL_DEVICE_AFFECTED_BUILD_DIR:-$ROOT/build/device-affected-gate}"

if [ -z "$CHANGED_TARGETS_FILE" ] || [ ! -f "$CHANGED_TARGETS_FILE" ]; then
    echo "Usage: $0 <changed-targets-file>" >&2
    exit 2
fi

if ! source "$ROOT/scripts/cann-env.sh"; then
    echo "BLOCKED_ENVIRONMENT: CANN Device compile environment is unavailable." >&2
    exit 2
fi

CANN_PACKAGE_PATH="${ASC_STL_CANN_PACKAGE_PATH:-${ASCEND_HOME_PATH:-}}"
TARGET_SOC="${ASC_STL_TARGET_SOC:-Ascend950PR_9599}"
NPU_ARCH="${ASC_STL_NPU_ARCH:-dav-3510}"
DEVICE_JOBS="${ASC_STL_DEVICE_JOBS:-4}"
TASK_TIMEOUT_SECONDS="${ASC_STL_DEVICE_TASK_TIMEOUT_SECONDS:-600}"

if [ -z "$CANN_PACKAGE_PATH" ] || [ ! -d "$CANN_PACKAGE_PATH" ]; then
    echo "BLOCKED_ENVIRONMENT: set ASC_STL_CANN_PACKAGE_PATH or ASCEND_HOME_PATH." >&2
    exit 2
fi

cmake -S "$ROOT" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DASC_STL_ENABLE_DEVICE_COMPILE_TESTS=ON \
    -DASC_STL_CANN_PACKAGE_PATH="$CANN_PACKAGE_PATH" \
    -DASC_STL_TARGET_SOC="$TARGET_SOC" \
    -DASC_STL_NPU_ARCH="$NPU_ARCH" \
    -DASC_STL_DEVICE_COMPILE_JOBS="$DEVICE_JOBS" \
    -DASC_STL_DEVICE_TASK_TIMEOUT_SECONDS="$TASK_TIMEOUT_SECONDS" \
    -DASC_STL_DEVICE_CHANGED_TARGETS_FILE="$CHANGED_TARGETS_FILE" \
    -DASC_STL_DEVICE_REPORT="$BUILD_DIR/device-compile-report.json"

ctest --test-dir "$BUILD_DIR" -R '^gate.device.compile$' --output-on-failure
