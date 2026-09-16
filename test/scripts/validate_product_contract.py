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

import logging
import re
import sys
from pathlib import Path


LOGGER = logging.getLogger(__name__)


FORBIDDEN = (
    "_" + "ACCL_",
    "__" + "accl",
    "_" + "CCCL_",
    "__" + "cccl",
    "cu" + "da::",
    "cu" + "da/std",
    "NVI" + "DIA",
    "lib" + "ascendcxx",
)


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    product_root = Path(sys.argv[1])
    include_root = product_root / "include"
    violations: list[str] = []
    guards: dict[str, str] = {}
    for path in sorted(item for item in include_root.rglob("*") if item.is_file() and not item.name.startswith(".")):
        text = path.read_text(encoding="utf-8")
        relative = path.relative_to(include_root).as_posix()
        for token in FORBIDDEN:
            if token in text:
                violations.append(f"{relative}: forbidden token {token}")
        first_guard = next((line.split(maxsplit=1)[1] for line in text.splitlines() if line.startswith("#ifndef ")), "")
        if not first_guard.startswith("CANN_ASC_STL_"):
            violations.append(f"{relative}: invalid include guard {first_guard!r}")
        if first_guard in guards:
            violations.append(f"{relative}: duplicate include guard also used by {guards[first_guard]}")
        guards[first_guard] = relative

    execution_coordinate = re.compile(r"\bW\d{2}[-_]B\d{3}\b", re.IGNORECASE)
    source_paths = [product_root / "CMakeLists.txt", product_root / "README.md"]
    for source_root in ("cmake", "include", "scripts", "test"):
        source_paths.extend(item for item in (product_root / source_root).rglob("*") if item.is_file())
    for path in sorted(source_paths):
        relative = path.relative_to(product_root).as_posix()
        if execution_coordinate.search(relative):
            violations.append(f"{relative}: implementation execution coordinate leaked into product path")
            continue
        text = path.read_text(encoding="utf-8", errors="ignore")
        if execution_coordinate.search(text):
            violations.append(f"{relative}: implementation execution coordinate leaked into product content")
        if "lib" + "ascendcxx" in relative or "lib" + "ascendcxx" in text:
            violations.append(f"{relative}: retired intermediate product identity")
    if violations:
        raise ValueError("\n".join(violations))
    LOGGER.info("PASS: %d product Headers use ASC-STL identity and unique guards", len(guards))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
