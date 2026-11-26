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
import json
import logging
from pathlib import Path


LOGGER = logging.getLogger(__name__)


def case_source(target: str) -> str:
    relative = target[:-2] if target.endswith(".h") else target
    return f"{relative}/host.pass.cpp"


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--registered", type=Path, required=True)
    parser.add_argument("--test-root", type=Path, required=True)
    args = parser.parse_args()

    rows = json.loads(args.manifest.read_text(encoding="utf-8"))["headers"]
    registered = {
        line.strip() for line in args.registered.read_text(encoding="utf-8").splitlines() if line.strip()
    }
    expected = {
        case_source(row.get("semantic_case", row["target"]))
        for row in rows
        if row["applicability"]["host_semantic"]
    }
    public_headers = [row["target"] for row in rows if row["visibility"] == "public"
                      and row["target"].startswith("asc/std/") and row["target"].count("/") == 2]
    missing_local = []
    for target in public_headers:
        sources = sorted((args.test_root / "cases" / target).glob("*.pass.cpp"))
        if not sources:
            missing_local.append(target)
        expected.update(f"{target}/{source.name}" for source in sources)
    missing_files = sorted(source for source in expected if not (args.test_root / "cases" / source).is_file())
    missing_registration = sorted(expected - registered)
    extra_registration = sorted(registered - expected)
    if missing_files or missing_registration or missing_local:
        LOGGER.error(json.dumps({
            "missing_files": missing_files,
            "public_headers_without_local_tests": missing_local,
            "missing_registration": missing_registration,
            "extra_registration": extra_registration,
        }, indent=2))
        return 1
    LOGGER.info(
        f"PASS: {len(expected)} metadata Host semantic sources are registered; "
        f"{len(extra_registration)} explicit boundary sources are also registered"
    )
    return 0


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    raise SystemExit(main())
