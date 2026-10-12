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
import csv
import json
import logging
from pathlib import Path


LOGGER = logging.getLogger(__name__)
SIMT_ONLY_TARGETS = {"asc/atomic", "asc/std/atomic", "asc/std/iterator", "asc/std/list", "asc/warp"}


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--results", type=Path, required=True)
    parser.add_argument("--runs", type=int, required=True)
    args = parser.parse_args()
    rows = json.loads(args.manifest.read_text(encoding="utf-8"))["headers"]
    expected_targets = {
        row.get("runtime_case", row["target"])
        for row in rows
        if row["applicability"]["hardware_runtime"]
    }
    with args.results.open(encoding="utf-8", newline="") as stream:
        results = list(csv.reader(stream))
    observed_targets = {row[0] for row in results if len(row) == 5 and row[4] == "PASS"}
    missing = sorted(expected_targets - observed_targets)
    extra = sorted(observed_targets - expected_targets)
    bad_counts = {}
    for target in sorted(expected_targets):
        expected_modes = {"simt"} if target in SIMT_ONLY_TARGETS else {"simd", "simt"}
        expected_combinations = {
            (standard, mode, str(run_index))
            for standard in ("17", "20")
            for mode in expected_modes
            for run_index in range(1, args.runs + 1)
        }
        observed_combinations = [
            (row[1], row[2], row[3]) for row in results if row[0] == target and row[4] == "PASS"
        ]
        if set(observed_combinations) != expected_combinations or len(observed_combinations) != len(
            expected_combinations
        ):
            bad_counts[target] = {
                "missing": sorted(expected_combinations - set(observed_combinations)),
                "extra": sorted(set(observed_combinations) - expected_combinations),
                "duplicates": len(observed_combinations) - len(set(observed_combinations)),
            }
    if missing or extra or bad_counts:
        LOGGER.error(json.dumps({"missing": missing, "extra": extra, "bad_counts": bad_counts}, indent=2))
        return 1
    LOGGER.info("PASS: %d hardware runtime_case targets have explicit per-language/run results", len(expected_targets))
    return 0


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    raise SystemExit(main())
