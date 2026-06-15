#!/usr/bin/env python3
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

import argparse
from pathlib import Path
import logging


SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".h", ".hpp", ".cuh"}
SCRIPT_SUFFIXES = {".py", ".sh", ".bash", ".cmake"}


def read_author(root_dir: Path) -> str:
    author_file = root_dir / ".author"
    if not author_file.exists():
        return "湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)"
    author = author_file.read_text(encoding="utf-8").strip()
    return author or "湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)"


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
    return "Copyright 2026 EJaven" in text and "Apache License, Version 2.0" in text


def comment_header(text: str, path: Path) -> str:
    lines = text.splitlines()
    suffix = path.suffix.lower()

    if suffix in SOURCE_SUFFIXES:
        body = ["/*"]
        body.extend(f" * {line}" if line else " *" for line in lines)
        body.append(" */")
        return "\n".join(body)

    if suffix in SCRIPT_SUFFIXES or path.name == "CMakeLists.txt":
        return "\n".join(f"# {line}" if line else "#" for line in lines)

    return "\n".join(f"# {line}" if line else "#" for line in lines)


def add_header(path: Path, header: str) -> bool:
    if not path.exists() or not path.is_file():
        return False

    try:
        content = path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        return False

    if has_license_header(content):
        return False

    wrapped = comment_header(header, path)
    if path.suffix == ".sh" and content.startswith("#!"):
        lines = content.splitlines()
        new_content = "\n".join([lines[0], "", wrapped, *lines[1:]])
    else:
        new_content = wrapped + ("\n\n" if content.strip() else "") + content

    path.write_text(new_content, encoding="utf-8")
    return True


def main() -> int:
    logging.basicConfig(level=logging.INFO)
    logger = logging.getLogger(__name__)

    parser = argparse.ArgumentParser(description="Add asc-stl Apache-2.0 license headers.")
    parser.add_argument("files", nargs="+")
    args = parser.parse_args()

    root_dir = Path(__file__).resolve().parent.parent
    header = plain_header(read_author(root_dir))

    changed = 0
    for item in args.files:
        if add_header(Path(item), header):
            changed += 1
            logger.info(f"Added license header: {item}")

    logger.info(f"License header update complete, changed={changed}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
