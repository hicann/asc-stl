#!/usr/bin/env python3

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

"""Check product Header byte hygiene, guards, and semantic blank lines."""

from __future__ import annotations

import argparse
import logging
from pathlib import Path

from header_layout_contract import SHARED_ROOTS


LOGGER = logging.getLogger(__name__)

SYSTEM_HEADER_BLOCK = [
    "#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)",
    "#pragma GCC system_header",
    "#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)",
    "#pragma clang system_header",
    "#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)",
    "#pragma system_header",
    "#endif",
]


def audit_bytes(data: bytes) -> tuple[str | None, list[str]]:
    errors: list[str] = []
    if not data.endswith(b"\n"):
        errors.append("missing final LF")
    if b"\r\n" in data:
        errors.append("contains CRLF")
    try:
        text = data.decode("utf-8")
    except UnicodeDecodeError:
        return None, errors + ["is not UTF-8"]

    lines = text.splitlines()
    for number, line in enumerate(lines, 1):
        if line.rstrip() != line:
            errors.append(f"line {number}: trailing whitespace")
        if "\t" in line:
            errors.append(f"line {number}: tab character")
    return text, errors


def audit_guard(lines: list[str]) -> tuple[str | None, list[str]]:
    errors: list[str] = []

    guard_index = next(
        (index for index, line in enumerate(lines) if line.startswith("#ifndef ")),
        None,
    )
    if guard_index is None:
        return None, ["missing #ifndef guard"]
    guard = lines[guard_index].split(maxsplit=1)[1]
    if not guard.startswith("CANN_ASC_STL_"):
        errors.append(f"guard lacks CANN_ASC_STL_ prefix: {guard}")
    define_index = guard_index + 1
    if define_index >= len(lines) or lines[define_index] != f"#define {guard}":
        errors.append("guard #define does not immediately match #ifndef")
    elif define_index + 1 >= len(lines) or lines[define_index + 1] != "":
        errors.append(f"line {define_index + 2}: expected blank line after guard #define")
    return guard, errors


def audit_system_header(path: Path, include_root: Path, lines: list[str]) -> list[str]:
    errors: list[str] = []

    relative = path.relative_to(include_root).as_posix()
    if relative not in SHARED_ROOTS:
        anchor = (
            "#include <asc/__detail/compiler.h>"
            if relative == "asc/__config"
            else "#include <asc/__config>"
        )
        if anchor not in lines:
            errors.append(f"missing system-header anchor: {anchor}")
        elif SYSTEM_HEADER_BLOCK[0] not in lines:
            errors.append("missing conditional system-header block")
        else:
            anchor_index = lines.index(anchor)
            block_index = lines.index(SYSTEM_HEADER_BLOCK[0])
            if block_index != anchor_index + 2 or lines[anchor_index + 1] != "":
                errors.append("system-header block must immediately follow its anchor and one blank line")
            if lines[block_index:block_index + len(SYSTEM_HEADER_BLOCK)] != SYSTEM_HEADER_BLOCK:
                errors.append("conditional system-header block does not match the canonical form")
            block_end = block_index + len(SYSTEM_HEADER_BLOCK)
            if block_end >= len(lines) or lines[block_end] != "":
                errors.append("expected blank line after conditional system-header block")
    return errors


def audit_namespace(lines: list[str]) -> list[str]:
    errors: list[str] = []
    for index, line in enumerate(lines):
        if line == "CANN_ASC_STL_BEGIN_NAMESPACE":
            if index == 0 or lines[index - 1] != "":
                errors.append(f"line {index + 1}: expected blank line before namespace begin")
            if index + 1 >= len(lines) or lines[index + 1] != "":
                errors.append(f"line {index + 1}: expected blank line after namespace begin")
        if line == "CANN_ASC_STL_END_NAMESPACE":
            if index == 0 or lines[index - 1] != "":
                errors.append(f"line {index + 1}: expected blank line before namespace end")
            if index + 1 >= len(lines) or lines[index + 1] != "":
                errors.append(f"line {index + 1}: expected blank line after namespace end")
    return errors


def audit(path: Path, include_root: Path) -> list[str]:
    text, errors = audit_bytes(path.read_bytes())
    if text is None:
        return errors
    lines = text.splitlines()
    guard, guard_errors = audit_guard(lines)
    errors.extend(guard_errors)
    if guard is None:
        return errors
    errors.extend(audit_system_header(path, include_root, lines))

    expected_end = f"#endif  // {guard}"
    if not lines or lines[-1] != expected_end:
        errors.append(f"final line must be: {expected_end}")
    elif len(lines) < 2 or lines[-2] != "":
        errors.append(f"line {len(lines)}: expected blank line before final #endif")

    errors.extend(audit_namespace(lines))
    return errors


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser()
    parser.add_argument("include_root", type=Path)
    parser.add_argument("--report-only", action="store_true")
    args = parser.parse_args()

    candidates = sorted(
        path
        for path in args.include_root.rglob("*")
        if path.is_file() and not path.name.startswith(".")
    )
    violations: list[str] = []
    seen_guards: dict[str, Path] = {}
    for path in candidates:
        text = path.read_text(encoding="utf-8", errors="ignore")
        if "#ifndef " not in text:
            continue
        guard = next(
            line.split(maxsplit=1)[1]
            for line in text.splitlines()
            if line.startswith("#ifndef ")
        )
        if guard in seen_guards:
            violations.append(
                f"{path}: duplicate guard also used by {seen_guards[guard]}"
            )
        else:
            seen_guards[guard] = path
        violations.extend(
            f"{path}: {message}" for message in audit(path, args.include_root)
        )

    if violations and not args.report_only:
        raise ValueError("\n".join(violations))
    for violation in violations:
        LOGGER.info("%s", violation)
    LOGGER.info(
        f"audited={len(seen_guards)} violations={len(violations)} "
        f"include_root={args.include_root}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
