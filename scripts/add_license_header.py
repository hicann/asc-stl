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

import argparse
import logging
from pathlib import Path
import re


SOURCE_SUFFIXES = {".asc", ".c", ".cc", ".cpp", ".cxx", ".h", ".hpp", ".cuh"}
SCRIPT_SUFFIXES = {".py", ".sh", ".bash", ".cmake"}
SOURCE_TEMPLATE_SUFFIXES = (".cpp.in",)


def is_product_header(path: Path) -> bool:
    parts = path.as_posix().split("/")
    return any(parts[index:index + 2] == ["include", "asc"] for index in range(len(parts) - 1))


def read_author(root_dir: Path) -> str:
    author_file = root_dir / ".author"
    if not author_file.exists():
        return "湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)"
    author = author_file.read_text(encoding="utf-8").strip()
    return author or "湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)"


def plain_header(author: str) -> str:
    return (
        f"Copyright 2026 {author}\n\n"
        'Licensed under the Apache License, Version 2.0 (the "License");\n'
        "you may not use this file except in compliance with the License.\n"
        "You may obtain a copy of the License at\n\n"
        "http://www.apache.org/licenses/LICENSE-2.0\n\n"
        "Unless required by applicable law or agreed to in writing, software\n"
        'distributed under the License is distributed on an "AS IS" BASIS,\n'
        "WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n"
        "See the License for the specific language governing permissions and\n"
        "limitations under the License."
    )


def has_license_header(text: str) -> bool:
    return "Copyright 2026" in text and "Apache License, Version 2.0" in text


def comment_header(text: str, path: Path) -> str:
    lines = text.splitlines()
    suffix = path.suffix.lower()

    if (
        suffix in SOURCE_SUFFIXES
        or is_product_header(path)
        or path.name.endswith(SOURCE_TEMPLATE_SUFFIXES)
    ):
        body = ["/*"]
        body.extend(f" * {line}" if line else " *" for line in lines)
        body.append(" */")
        return "\n".join(body)

    if suffix in SCRIPT_SUFFIXES or path.name == "CMakeLists.txt":
        return "\n".join(f"# {line}" if line else "#" for line in lines)

    return "\n".join(f"# {line}" if line else "#" for line in lines)


def split_shebang(content: str, path: Path) -> tuple[str, str]:
    if content.startswith("#!"):
        first, separator, remainder = content.partition("\n")
        return first + separator + "\n", remainder.lstrip("\n")
    return "", content


def strip_leading_license(content: str, path: Path) -> str:
    suffix = path.suffix.lower()
    if (
        suffix in SOURCE_SUFFIXES
        or is_product_header(path)
        or path.name.endswith(SOURCE_TEMPLATE_SUFFIXES)
    ):
        match = re.match(r"\A\s*(/\*.*?\*/\s*)", content, re.DOTALL)
        if match and has_license_header(match.group(1)):
            return content[match.end():].lstrip()
        return content

    lines = content.splitlines(keepends=True)
    index = 0
    while index < len(lines) and lines[index].startswith("#"):
        index += 1
    candidate = "".join(lines[:index])
    return "".join(lines[index:]).lstrip() if has_license_header(candidate) else content


def strip_leading_licenses(content: str, path: Path) -> str:
    while True:
        stripped = strip_leading_license(content, path)
        if stripped == content:
            return content
        content = stripped


def canonical_content(path: Path, content: str, header: str) -> str:
    prefix, body = split_shebang(content, path)
    wrapped = comment_header(header, path)
    if body.startswith(wrapped):
        remainder = body[len(wrapped):].lstrip()
        cleaned = strip_leading_licenses(remainder, path)
        if cleaned == remainder:
            return content
        body = cleaned
    else:
        body = strip_leading_licenses(body, path)
    return prefix + wrapped + ("\n\n" if body.strip() else "") + body


def has_canonical_header(path: Path, content: str, header: str) -> bool:
    _, body = split_shebang(content, path)
    wrapped = comment_header(header, path)
    if not body.startswith(wrapped):
        return False
    remainder = body[len(wrapped):].lstrip()
    return strip_leading_license(remainder, path) == remainder


def add_header(path: Path, header: str) -> bool:
    if not path.exists() or not path.is_file():
        return False

    try:
        content = path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        return False

    new_content = canonical_content(path, content, header)
    if new_content == content:
        return False

    path.write_text(new_content, encoding="utf-8")
    return True


def parse_args():
    parser = argparse.ArgumentParser(description="Add asc-stl Apache-2.0 license headers.")
    parser.add_argument("--check", action="store_true", help="Fail if any file lacks the canonical header.")
    parser.add_argument("files", nargs="+")
    return parser.parse_args()


def check_header(path: Path, header: str, logger) -> bool:
    try:
        content = path.read_text(encoding="utf-8")
    except (OSError, UnicodeDecodeError):
        logger.error("Cannot inspect license header: %s", path)
        return False
    if has_canonical_header(path, content, header):
        return True
    logger.error("Non-canonical license header: %s", path)
    return False


def process_path(path: Path, header: str, check: bool, logger) -> bool:
    if check:
        return not check_header(path, header, logger)
    if not add_header(path, header):
        return False
    logger.info("Normalized license header: %s", path)
    return True


def main() -> int:
    logging.basicConfig(level=logging.INFO)
    logger = logging.getLogger(__name__)
    args = parse_args()

    root_dir = Path(__file__).resolve().parent.parent
    header = plain_header(read_author(root_dir))
    changed = sum(process_path(Path(item), header, args.check, logger) for item in args.files)

    if args.check:
        logger.info("License header check complete, errors=%d", changed)
        return 1 if changed else 0
    logger.info("License header update complete, changed=%d", changed)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
