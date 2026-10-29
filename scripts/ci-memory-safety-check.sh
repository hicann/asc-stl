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
BUILD_DIR="${ASC_STL_MEMORY_SAFETY_BUILD_DIR:-$ROOT/build/memory-safety}"
COMPILER="${CXX:-g++}"
mkdir -p "$BUILD_DIR"

for standard in 17 20; do
    binary="$BUILD_DIR/vector-aliasing-cxx$standard"
    "$COMPILER" -std="c++$standard" -O1 -g -Wall -Wextra -Werror -pedantic -UNDEBUG \
        -fsanitize=address,undefined -fno-omit-frame-pointer -I "$ROOT/include" \
        "$ROOT/test/cases/asc/std/vector/aliasing.pass.cpp" -o "$binary"
    ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
        UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 "$binary"
    echo "PASS: vector aliasing, lifetime and exception safety with ASan/UBSan C++$standard"
done

echo "ASC_STL_MEMORY_SAFETY_PASS"
