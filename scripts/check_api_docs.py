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

"""Check public Markdown and compile the registered API examples."""
from __future__ import annotations

import argparse
import concurrent.futures
import json
import logging
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile

from check_doc_writing import check_writing

FENCE = re.compile(r"^```")
CPP = re.compile(r"```cpp\n(.*?)\n```", re.DOTALL)
LINK = re.compile(r"\]\(([^)\s]+)\)")
TABLE_SEPARATOR = re.compile(r"^\s*\|(?:\s*:?-{3,}:?\s*\|)+\s*$")
PLACEHOLDERS = (
    "本接口处理或保存的值类型；须满足原型中的类型约束",
    "所选原型使用的类型参数；其可用操作由约束说明限定",
    "参与操作或用于初始化、比较的值",
    "参与本页所述数学运算的输入值",
)
INVALID_IDENTIFIERS = (
    "Asccomplexvaluetype", "Builtinoffsetof", "PTRDIFFMAX", "Copycvreft<",
    "Ascinternal::Isnonnarrowingconvertible", "Zvfunctors::Viewsize", "Detail::Scaledelementtype", "DECIMALDIG",
    "Makesignedimpl<", "Makeunsignedimpl<", "Makeintegersequence<", "Propagateoncontainerswa<",
)
LOGGER = logging.getLogger(__name__)


def table_columns(line: str) -> int:
    value = line.strip().removeprefix("|")
    if value.endswith("|") and not value.endswith("\\|"):
        value = value[:-1]
    return len(re.split(r"(?<!\\)\|", value))


def structure_errors(path: Path) -> list[str]:
    lines = path.read_text(encoding="utf-8").splitlines()
    errors = []
    fenced = False
    columns = None
    for index, line in enumerate(lines):
        if FENCE.match(line):
            fenced = not fenced
            columns = None
            continue
        if fenced:
            continue
        if TABLE_SEPARATOR.fullmatch(line) and index:
            if table_columns(lines[index - 1]) != table_columns(line):
                errors.append(f"{path}:{index + 1}: table header/separator column mismatch")
            columns = table_columns(line)
        elif columns is not None and line.startswith("|"):
            if table_columns(line) != columns:
                errors.append(f"{path}:{index + 1}: table data row column mismatch")
        else:
            columns = None
        for target in LINK.findall(line):
            if "://" in target or target.startswith(("#", "mailto:")):
                continue
            destination = path.parent / target.split("#", 1)[0]
            if not destination.exists():
                errors.append(f"{path}:{index + 1}: missing relative link: {target}")
    if fenced:
        errors.append(f"{path}: unclosed code fence")
    return errors


def example_source(path: Path) -> str:
    text = path.read_text(encoding="utf-8")
    if "## 调用示例" not in text:
        raise ValueError(f"missing example section: {path}")
    section = text.split("## 调用示例", 1)[1].split("\n## ", 1)[0]
    match = CPP.search(section)
    if match is None:
        raise ValueError(f"missing C++ example: {path}")
    return match.group(1)


def content_errors(path: Path) -> list[str]:
    text = path.read_text(encoding="utf-8")
    errors = []
    if "## 调用示例" in text:
        try:
            source = example_source(path)
            if re.search(r"\(void\)\s*sizeof\s*\(", source):
                errors.append(f"{path}: example only demonstrates sizeof")
            if "is_same_v<selected, selected>" in source:
                errors.append(f"{path}: tautological type assertion")
        except ValueError as error:
            errors.append(str(error))
    for name in INVALID_IDENTIFIERS:
        if name in text:
            errors.append(f"{path}: corrupted identifier: {name}")
    for phrase in PLACEHOLDERS:
        if phrase in text:
            errors.append(f"{path}: parameter placeholder: {phrase}")
    return errors


def check_structure(root: Path) -> list[str]:
    errors = check_writing(root)
    for path in sorted((root / "docs").rglob("*.md")):
        errors.extend(structure_errors(path))
        if "api" in path.parts:
            errors.extend(content_errors(path))
    return errors


def prepared_spec(spec: dict) -> dict:
    spec = dict(spec)
    if spec.get("sdk") != "cann":
        return spec
    sdk = Path(os.environ.get("ASCEND_HOME_PATH", "/usr/local/Ascend/ascend-toolkit/latest"))
    driver = Path(os.environ.get("ASCEND_DRIVER_PATH", "/usr/local/Ascend/driver"))
    directories = [sdk / "lib64", driver / "lib64/driver", driver / "lib64/common"]
    spec["include_flags"] = ["-I", str(sdk / "include")]
    flags = ["-Wl,--disable-new-dtags"]
    for directory in directories:
        if directory.is_dir():
            flags += ["-L", str(directory), "-Wl,-rpath," + str(directory), "-Wl,-rpath-link," + str(directory)]
    spec["link_flags"] = flags + ["-lascendcl"]
    spec["required_headers"] = ["acl/acl.h"]
    return spec


def example_command(root: Path, spec: dict, standard: int, compiler: str, source_path: Path) -> list[str]:
    command = [compiler, f"-std=c++{standard}", "-O2", "-I", str(root / "include")]
    command += spec.get("include_flags", [])
    if spec.get("mode", "host") not in ("host", "runtime"):
        command += ["--asc-aicore-lang", f"--npu-arch={spec['npu_arch']}", "-Werror", "-c"]
        if spec.get("mode") == "simt":
            command += ["--enable-simt", "-Wno-error=ignored-attributes"]
    command += [str(source_path), "-o", str(source_path.with_suffix(""))]
    command += spec.get("link_flags", [])
    return command


def prepare_example_source(source: str, spec: dict) -> tuple[str, str]:
    """Add the Host entry point and identify what the source actually checks."""
    expression = spec.get("expression")
    if spec.get("include_only"):
        source = "\n".join(line for line in source.splitlines() if line.startswith("#include"))
        expression = None
    has_main = bool(re.search(r"\bint\s+main\s*\(", source))
    if not has_main and spec.get("mode", "host") in ("host", "runtime"):
        body = f"return ({expression}) ? 0 : 1;" if expression else "return 0;"
        source += "\nint main() { " + body + " }\n"
    if spec.get("include_only"):
        return source, "header_parse"
    if expression or has_main:
        return source, "run"
    if "static_assert" in source:
        return source, "static_assert"
    return source, "compile_only"


def run_example(binary: Path, record: dict, kind: str) -> dict:
    result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=30, check=False)
    status = "PASS" if result.returncode == 0 else "FAIL"
    return dict(record, status=status, stage=kind, returncode=result.returncode, diagnostic=result.stderr)


def compile_example(task: tuple) -> dict:
    root, relative, spec, standard, compiler, directory = task
    mode = spec.get("mode", "host")
    host_mode = mode in ("host", "runtime")
    spec = prepared_spec(spec)
    record = {"page": relative, "standard": standard, "mode": mode}
    if not shutil.which(compiler):
        return dict(record, status="FAIL", diagnostic=f"compiler unavailable: {compiler}")
    try:
        missing = missing_headers(spec, compiler)
    except (OSError, subprocess.TimeoutExpired) as error:
        return dict(record, status="FAIL", diagnostic=str(error))
    if missing:
        return dict(record, status="NOT_APPLICABLE", diagnostic=f"required external headers unavailable: {missing}")
    try:
        source, kind = prepare_example_source(example_source(root / relative), spec)
    except ValueError as error:
        return dict(record, status="FAIL", diagnostic=str(error))
    index = spec["task_index"]
    suffix = "cpp" if host_mode else "asc"
    source_path = directory / f"example-{index}.{suffix}"
    binary = directory / f"example-{index}"
    source_path.write_text(source, encoding="utf-8")
    command = example_command(root, spec, standard, compiler, source_path)
    try:
        result = subprocess.run(command, capture_output=True, text=True, timeout=120, check=False)
        if result.returncode:
            return dict(record, status="FAIL", stage="compile", diagnostic=result.stderr)
        if not host_mode:
            return dict(record, status="PASS", stage="device_compile", command=command)
        return run_example(binary, record, kind)
    except (OSError, subprocess.TimeoutExpired) as error:
        return dict(record, status="FAIL", diagnostic=str(error))


def missing_headers(spec: dict, compiler: str) -> list[str]:
    missing = []
    for header in spec.get("required_headers", []):
        command = [compiler, "-E", "-x", "c++", "-", *spec.get("include_flags", [])]
        result = subprocess.run(command, input=f"#include <{header}>\n",
                                capture_output=True, text=True, timeout=30, check=False)
        if result.returncode:
            missing.append(header)
    return missing


def check_examples(args: argparse.Namespace) -> list[dict]:
    registry = json.loads((args.root / "test/docs/examples.json").read_text(encoding="utf-8"))
    records = []
    with tempfile.TemporaryDirectory(prefix="asc-stl-doc-examples-") as temporary:
        tasks = []
        for index, (path, spec) in enumerate(sorted(registry.items())):
            include_only = args.standard in spec.get("header_standards", [])
            if spec.get("mode", "host") != args.mode:
                continue
            if args.standard not in spec["standards"] and not include_only:
                continue
            flags = [flag for path in args.extra_include for flag in ("-I", str(path))]
            spec = dict(spec, task_index=index, include_only=include_only, npu_arch=args.npu_arch, include_flags=flags)
            tasks.append((args.root, path, spec, args.standard, args.compiler, Path(temporary)))
        with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as executor:
            records.extend(executor.map(compile_example, tasks))
    return records


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--examples", action="store_true")
    parser.add_argument("--standard", type=int, choices=(17, 20, 23), default=17)
    parser.add_argument("--compiler", default=os.environ.get("CXX", "c++"))
    parser.add_argument("--mode", choices=("host", "runtime", "simd", "simt"), default="host")
    parser.add_argument("--npu-arch", default="dav-3510")
    parser.add_argument("--extra-include", type=Path, action="append", default=[])
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    args.root = args.root.resolve()
    if args.jobs < 1:
        parser.error("--jobs must be positive")
    if args.examples:
        records = check_examples(args)
        failed = [record for record in records if record["status"] == "FAIL"]
        passed = sum(record["status"] == "PASS" for record in records)
        skipped = sum(record["status"] == "NOT_APPLICABLE" for record in records)
        report = {"examples": records, "passed": passed, "failed": len(failed), "not_applicable": skipped}
        for record in failed[:20]:
            LOGGER.error("%s %s", record["page"], record.get("diagnostic", "")[:1200])
        LOGGER.info("API examples C++%s %s: %s/%s passed, %s not applicable",
                    args.standard, args.mode, passed, len(records), skipped)
        errors = failed
    else:
        errors = check_structure(args.root)
        report = {"errors": errors}
        for error in errors[:30]:
            LOGGER.error("%s", error)
        LOGGER.info("Documentation findings: %s", len(errors))
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    return bool(errors)


if __name__ == "__main__":
    raise SystemExit(main())
