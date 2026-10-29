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
BUILD_DIR="${ASC_STL_BUILD_DIR:-$ROOT/build/ci}"

cd "$ROOT"
bash scripts/check-style.sh
cmake -S "$ROOT" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release \
    -DASC_STL_DOC_EXAMPLE_JOBS="${ASC_STL_DOC_EXAMPLE_JOBS:-4}"
cmake --build "$BUILD_DIR"
ctest --test-dir "$BUILD_DIR" \
    -L "metadata|static-rules|header-host|semantic-host|affected-regression" \
    --output-on-failure
