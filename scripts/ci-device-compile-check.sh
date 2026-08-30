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

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="${ASC_STL_DEVICE_BUILD_DIR:-$ROOT/build/device-gate}"

# shellcheck disable=SC1091
source "$ROOT/scripts/cann-env.sh"

CANN_PACKAGE_PATH="${ASC_STL_CANN_PACKAGE_PATH:-${ASCEND_HOME_PATH:-}}"
TARGET_SOC="${ASC_STL_TARGET_SOC:-Ascend950PR_9599}"
NPU_ARCH="${ASC_STL_NPU_ARCH:-dav-3510}"

if [ -z "$CANN_PACKAGE_PATH" ] || [ ! -d "$CANN_PACKAGE_PATH" ]; then
    echo "BLOCKED_ENVIRONMENT: set ASC_STL_CANN_PACKAGE_PATH or ASCEND_HOME_PATH to an installed CANN package."
    exit 2
fi

cmake -S "$ROOT" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DASC_STL_ENABLE_DEVICE_COMPILE_TESTS=ON \
    -DASC_STL_CANN_PACKAGE_PATH="$CANN_PACKAGE_PATH" \
    -DASC_STL_TARGET_SOC="$TARGET_SOC" \
    -DASC_STL_NPU_ARCH="$NPU_ARCH"

ctest --test-dir "$BUILD_DIR" -L "header-device|device-compile" --output-on-failure
