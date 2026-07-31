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
BUILD_DIR="${ASC_STL_BUILD_DIR:-$ROOT/build/ci}"

cmake_path() {
    if command -v cygpath >/dev/null 2>&1; then
        cygpath -m "$1"
    else
        printf '%s\n' "$1"
    fi
}

cd "$ROOT"

bash scripts/check-style.sh

CMAKE_ROOT="$(cmake_path "$ROOT")"
CMAKE_BUILD_DIR="$(cmake_path "$BUILD_DIR")"

cmake -S "$CMAKE_ROOT" -B "$CMAKE_BUILD_DIR" -DCMAKE_BUILD_TYPE=Release
cmake --build "$CMAKE_BUILD_DIR"
ctest --test-dir "$CMAKE_BUILD_DIR" \
    -L "metadata|static-rules|header-host|semantic-host|affected-regression" \
    --output-on-failure
