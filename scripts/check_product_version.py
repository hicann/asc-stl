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

"""Reject inconsistent release dates, delivery flags and delivery evidence."""
import argparse
from datetime import date
import hashlib
import json
import logging
from pathlib import Path
import re

LOGGER = logging.getLogger(__name__)
ISSUES = {
    "CANN_ASC_STL_HAS_PIPELINE": 105,
    "CANN_ASC_STL_HAS_NUMERIC_TYPES": 85,
    "CANN_ASC_STL_HAS_CACHE": 99,
}


def integer(value):
    return isinstance(value, int) and not isinstance(value, bool)


def release_date(value):
    if not integer(value) or not 10000101 <= value <= 99991231:
        raise ValueError(f"Invalid YYYYMMDD release date: {value!r}")
    date(value // 10000, value // 100 % 100, value % 100)
    return value


def product_macros(root):
    source = (root / "include/asc/__version/product.h").read_text(encoding="utf-8")
    definitions = re.findall(r"^#define (CANN_ASC_STL\b|CANN_ASC_STL_\w+)[ \t]+([^\n]+)$", source, re.MULTILINE)
    expected = {"CANN_ASC_STL", *ISSUES}
    names = [name for name, value in definitions]
    if set(names) != expected or len(names) != len(expected):
        raise ValueError("Product version header must define exactly the four registered integer macros")
    values = {}
    for name, value in definitions:
        if not re.fullmatch(r"[1-9][0-9]*|0", value):
            raise ValueError(f"{name}: expected a fixed decimal integer")
        values[name] = int(value)
    release_date(values.get("CANN_ASC_STL"))
    if any(values[name] not in (0, 1) for name in ISSUES):
        raise ValueError("Delivery flags must be 0 or 1")
    return values


def verified_file(root, record):
    if not isinstance(record, dict):
        raise ValueError("Delivery evidence requires a registry-relative path and SHA256")
    relative = record.get("path")
    if not isinstance(relative, str) or not relative or Path(relative).is_absolute():
        raise ValueError("Delivery evidence requires a registry-relative path")
    path = (root / relative).resolve()
    path.relative_to(root.resolve())
    content = path.read_bytes()
    if hashlib.sha256(content).hexdigest() != record.get("sha256"):
        raise ValueError(f"Delivery evidence SHA256 mismatch: {relative}")
    return content


def acceptance_evidence(content, implementation):
    evidence = json.loads(content)
    if evidence.get("implementation_commit") != implementation:
        raise ValueError("Acceptance must identify the registered implementation commit")
    cases = evidence.get("cases")
    if not isinstance(cases, list) or not cases:
        raise ValueError("Acceptance requires nonempty applicable cases")
    names = set()
    for case in cases:
        if not isinstance(case, dict) or not isinstance(case.get("name"), str) or not case["name"]:
            raise ValueError("Each acceptance case requires a name")
        if case["name"] in names:
            raise ValueError("Duplicate acceptance case")
        names.add(case["name"])
        if case.get("status") != "PASS" or not integer(case.get("returncode")) or case["returncode"] != 0:
            raise ValueError("Every applicable acceptance case must pass; skipped cases cannot establish delivery")


def delivered_feature(root, row, package_date):
    records = root / "docs/release"
    verified_file(records, row.get("baseline"))
    implementation = row.get("implementation_commit")
    if not isinstance(implementation, str) or not re.fullmatch(r"[0-9a-f]{40}", implementation):
        raise ValueError("Delivered feature requires an implementation commit")
    acceptance_evidence(verified_file(records, row.get("acceptance")), implementation)
    if release_date(row.get("first_release_date")) > package_date:
        raise ValueError("First delivery date cannot follow the package date")


def check(root):
    values = product_macros(root)
    registry = json.loads((root / "docs/release/extension_features.json").read_text(encoding="utf-8"))
    if not integer(registry.get("schema_version")) or registry["schema_version"] != 1:
        raise ValueError("Unsupported extension delivery registry schema")
    package_date = release_date(registry.get("release_date"))
    if package_date != values["CANN_ASC_STL"]:
        raise ValueError("Release date disagrees with CANN_ASC_STL")
    features = registry.get("features")
    if not isinstance(features, dict) or set(features) != set(ISSUES):
        raise ValueError("Delivery registry must contain exactly the three extension features")
    for name, issue in ISSUES.items():
        row = features[name]
        if not isinstance(row, dict) or not integer(row.get("value")) or row["value"] != values[name]:
            raise ValueError(f"{name}: registry value disagrees with the header")
        if row.get("issue") != f"https://gitcode.com/cann/asc-stl/issues/{issue}":
            raise ValueError(f"{name}: incorrect module Issue")
        if row["value"] == 1:
            header = name.removeprefix("CANN_ASC_STL_HAS_").lower()
            if not (root / "include/asc" / header).is_file():
                raise ValueError(f"{name}: delivered feature requires its public module header")
            delivered_feature(root, row, package_date)
        elif not isinstance(row.get("reason"), str) or not row["reason"].strip():
            raise ValueError(f"{name}: undelivered feature requires an explanation")
    return values


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    args = parser.parse_args()
    try:
        values = check(args.root)
    except (ValueError, OSError, TypeError, AttributeError) as error:
        LOGGER.error("FAIL: product version: %s", error)
        return 1
    LOGGER.info("PASS: product date and all three delivery records agree: %s", values)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
