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
import subprocess
import tempfile


LOGGER = logging.getLogger(__name__)
SOURCE = """#include <asc/__hierarchy/query.h>
#ifdef ASC_STL_TEST_SELECTED_CURRENT
int selected_current;
#endif
#ifdef ASC_STL_TEST_SELECTED_LEGACY
int selected_legacy;
#endif
"""


def check_layout(compiler, include_root, standard, layout):
    """Test preprocessing only; Device compilation remains a separate gate."""
    with tempfile.TemporaryDirectory(prefix="asc-stl-sdk-layout-") as directory:
        sdk = Path(directory)
        for name, folder in (("current", "utils"), ("legacy", "sys_var")):
            if layout in (name, "both"):
                header = sdk / "c_api" / folder / "sys_var.h"
                header.parent.mkdir(parents=True)
                header.write_text(f"#define ASC_STL_TEST_SELECTED_{name.upper()} 1\n", encoding="utf-8")
        result = subprocess.run(
            [compiler, f"-std=c++{standard}", "-D__CCE__=1", "-nostdinc", "-E", "-P", "-x", "c++", "-",
             "-I", str(sdk), "-I", str(include_root)],
            input=SOURCE, capture_output=True, text=True, check=False, timeout=10,
        )
    if layout == "missing":
        passed = result.returncode != 0 and "requires a CANN SDK providing" in result.stderr
    else:
        selected = "legacy" if layout == "legacy" else "current"
        rejected = "current" if selected == "legacy" else "legacy"
        passed = (result.returncode == 0 and f"int selected_{selected};" in result.stdout
                  and f"int selected_{rejected};" not in result.stdout)
    if not passed:
        raise RuntimeError(f"C++{standard} / {layout}: unexpected SDK selection\n{result.stderr}")
    LOGGER.info("PASS: C++%s / %s", standard, layout)


def main():
    parser = argparse.ArgumentParser(description="Verify new/legacy CANN query Header selection")
    parser.add_argument("--include-root", type=Path, required=True)
    parser.add_argument("--compiler", required=True)
    args = parser.parse_args()
    for standard in (17, 20):
        for layout in ("current", "legacy", "both", "missing"):
            check_layout(args.compiler, args.include_root, standard, layout)
    return 0


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    raise SystemExit(main())
