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
STATE_DIR="$(mktemp -d "${TMPDIR:-/tmp}/asc-stl-codecheck.XXXXXX")"
STAGE_DIR="$STATE_DIR/repo"
trap 'rm -rf -- "$STATE_DIR"' EXIT
mkdir -p "$STAGE_DIR"
# A linked worktree stores .git as a file; exclude both files and directories.
rsync -a --exclude '/.git' --exclude '/build/' --exclude '.env' --exclude '.env.*' "$ROOT/" "$STAGE_DIR/"
cd "$STAGE_DIR"
git init --quiet
git add --all
git -c user.name=ASC-STL -c user.email=asc-stl@example.invalid \
    commit --quiet -m "temporary CodeCheck stage" --no-verify
git diff --binary -- >"$STATE_DIR/before.diff"
pre-commit validate-config
pre-commit run --all-files
git diff --binary -- >"$STATE_DIR/after.diff"
if ! cmp -s "$STATE_DIR/before.diff" "$STATE_DIR/after.diff"; then
    echo "CodeCheck modified tracked files; apply the fixes before validation." >&2
    exit 1
fi
echo "ASC_STL_CODECHECK_PASS"
