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
cd "$ROOT"

echo "Step 1: check canonical license headers"

LICENSE_SOURCES="$({
    git ls-files --cached --others --exclude-standard \
        '*.c' '*.cc' '*.cpp' '*.cxx' '*.h' '*.hpp' '*.cuh' '*.py' '*.sh' '*.bash' '*.cmake' '*.cpp.in'
    git ls-files --cached --others --exclude-standard -- 'CMakeLists.txt' '*/CMakeLists.txt' '*/__config'
} 2>/dev/null | sort -u)"

if [ -n "$LICENSE_SOURCES" ]; then
    printf '%s\n' "$LICENSE_SOURCES" | xargs python3 scripts/add_license_header.py --check
fi
echo "canonical license headers passed"

echo "Step 2: check clang-format"

CLANG_FORMAT=""
for version in 18 17 16 15 14; do
    if command -v "clang-format-$version" >/dev/null 2>&1; then
        CLANG_FORMAT="clang-format-$version"
        break
    fi
done
CLANG_FORMAT="${CLANG_FORMAT:-clang-format}"

SOURCES="$({
    git ls-files --cached --others --exclude-standard \
        '*.h' '*.hpp' '*.cuh' '*.cc' '*.cpp' '*.cxx' '*.cpp.in'
    git ls-files --cached --others --exclude-standard -- '*/__config'
} 2>/dev/null | sort -u)"

if [ -z "$SOURCES" ]; then
    echo "No C/C++ source files found; skip clang-format and cpplint."
    exit 0
fi

if ! command -v "$CLANG_FORMAT" >/dev/null 2>&1; then
    echo "Missing clang-format. Install clang-format 14 or newer."
    exit 1
fi

printf '%s\n' "$SOURCES" | xargs "$CLANG_FORMAT" --dry-run --Werror
echo "clang-format passed"

echo "Step 3: check cpplint"
if ! command -v cpplint >/dev/null 2>&1; then
    echo "Missing cpplint. Install it with: python -m pip install cpplint"
    exit 1
fi

CPPLINT_SOURCES="$(printf '%s\n' "$SOURCES" | grep -E '\.(h|hpp|cuh|cc|cpp|cxx)$' || true)"
if [ -n "$CPPLINT_SOURCES" ]; then
    printf '%s\n' "$CPPLINT_SOURCES" | xargs cpplint --extensions=h,hpp,cuh,cc,cpp,cxx --quiet
fi
echo "cpplint passed"
