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

"""Run metadata-driven C++17/C++20 D-SIMD and D-SIMT compile gates with BiSheng."""

from __future__ import annotations

import argparse
import json
import logging
import shutil
import subprocess
import tempfile
import time
from collections import Counter, deque
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass, replace
from pathlib import Path


LOGGER = logging.getLogger(__name__)
ERROR_MARKERS = ("error:", "fatal error:")


@dataclass(frozen=True)
class CompileOptions:
    standard: str
    simt: bool
    expect_failure: bool = False


@dataclass(frozen=True)
class CompileTask:
    order: int
    kind: str
    label: str
    source: Path
    output: Path
    options: CompileOptions
    target: str
    negative_name: str = ""


@dataclass(frozen=True)
class CompileResult:
    task: CompileTask
    command: list[str]
    returncode: int
    output: str
    duration_seconds: float
    timed_out: bool = False


@dataclass(frozen=True)
class DeviceCompiler:
    executable: str
    include_root: Path
    test_root: Path
    npu_arch: str
    task_timeout_seconds: int

    def command(self, task: CompileTask) -> list[str]:
        command = [
            self.executable,
            "--asc-aicore-lang",
            f"--npu-arch={self.npu_arch}",
            f"-std={task.options.standard}",
            "-Werror",
            f"-I{self.include_root}",
            f"-I{self.test_root}",
        ]
        if task.options.simt:
            # Keep CANN SDK attribute warnings visible without relaxing other diagnostics.
            command.extend(["--enable-simt", "-Wno-error=ignored-attributes"])
        command.append(f"-DCANN_ASC_STL_USE_SIMT_LAUNCH={int(task.options.simt)}")
        return command + ["-c", str(task.source), "-o", str(task.output)]

    def compile(self, task: CompileTask) -> CompileResult:
        command = self.command(task)
        started = time.monotonic()
        try:
            process = subprocess.run(
                command,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                check=False,
                timeout=self.task_timeout_seconds,
            )
            return CompileResult(
                task, command, process.returncode, process.stdout, time.monotonic() - started
            )
        except subprocess.TimeoutExpired as error:
            output = error.stdout or ""
            if isinstance(output, bytes):
                output = output.decode(errors="replace")
            return CompileResult(
                task, command, 124, output, time.monotonic() - started, timed_out=True
            )


def case_root(test_root: Path, target: str) -> Path:
    relative = target[:-2] if target.endswith(".h") else target
    return test_root / "cases" / relative


NEGATIVE_DIAGNOSTIC_MARKERS = {
    "block_value_type_simt.fail.asc": "unsupported block collective value type",
    "seed_sequence.fail.cpp": "no viable conversion",
    "value.fail.cpp": "deleted",
    "void.fail.cpp": "undefined template",
    "bool.fail.cpp": "static assertion",
    "floating.fail.cpp": "static assertion",
    "format_float.fail.asc": "static assertion",
    "cxx17_absent.fail.cpp": "no template named",
    "invalid_spec.fail.cpp": "__builtin_trap",
    "repeat_unbounded.fail.cpp": "no matching function",
    "zip_three.fail.cpp": "no matching function",
    "simt_excluded.fail.asc": "call to __host__ function",
    "e_v_double_excluded.fail.asc": "static assertion",
    "e_v_long_double_excluded.fail.asc": "static assertion",
    "runtime_double.fail.asc": "double precision operation is not allowed in aicore function",
    "initializer_list_excluded.fail.asc": "no matching function",
    "simd_excluded.fail.asc": "__host__ function",
    "ub_span_dsimt.fail.asc": "ub_span",
    "pipeline_dsimt.fail.asc": "no member named 'make_pipeline'",
    "pipeline_element_type.fail.asc": "approved int8",
    "simt_only.fail.asc": "call to __host__ function",
    "excluded_policy_overload.fail.cpp": "no member named",
    "comparison_category_excluded.fail.cpp": "no type named",
    "function_excluded.fail.cpp": "no template named",
    "hash_unsupported_type.fail.cpp": "hash unsupported type must remain unavailable",
    "searcher_excluded.fail.cpp": "no member named",
    "timed_excluded.fail.cpp": "no member named",
    "default_priority_queue.fail.cpp": "too few template arguments",
    "default_queue.fail.cpp": "too few template arguments",
    "default_allocator.fail.cpp": "too few template arguments",
    "back_insert_iterator_spaceship.fail.cpp": "no matching constructor",
    "iter_const_reference.fail.cpp": "no template named",
    "initializer_list_data.fail.cpp": "no matching function",
    "initializer_list_empty.fail.cpp": "cannot deduce type",
    "initializer_list_advance.fail.cpp": "cannot deduce type",
    "expected_value.fail.cpp": "deleted member function",
    "variant_emplace_type_initializer_list.fail.cpp": "no member named 'initializer_list'",
    "variant_emplace_index_initializer_list.fail.cpp": "no member named 'initializer_list'",
    "variant_ctor_in_place_type_initializer_list.fail.cpp": "no member named 'initializer_list'",
    "variant_ctor_in_place_index_initializer_list.fail.cpp": "no member named 'initializer_list'",
    "reference_alternative.fail.asc": "static assertion",
    "unsupported_double.fail.asc": "static assertion",
    "invalid_requirement_type.fail.asc": "no matching function",
    "optional_reference.fail.cpp": "no matching constructor",
    "nontrivial_element.fail.cpp": "static assertion",
    "native_adopt_excluded.fail.cpp": "no member named",
    "system_clock_runtime.fail.cpp": "no member named 'now'",
    "system_clock_to_time_t.fail.cpp": "no member named 'to_time_t'",
    "system_clock_from_time_t.fail.cpp": "no member named 'from_time_t'",
    "int128_excluded.fail.asc": "static assertion",
    "simd_scalar_sincos.fail.asc": "sincos",
    "simt_double_sincos.fail.asc": "cannot initialize",
    "cancel_excluded.fail.asc": "no member named",
    "chars_format.fail.asc": "chars_format",
    "chars_format.fail.cpp": "chars_format",
    "result_bool.fail.cpp": "convertible",
    "unsupported_type.fail.cpp": "static assertion",
    "position_access.fail.cpp": "too many arguments",
    "oversized_conversion.fail.cpp": "requirement",
    "string_constructor.fail.cpp": "no matching constructor",
    "bool_excluded.fail.cpp": "static assertion",
    "excluded_surface.fail.cpp": "no member named",
    "owning_range.fail.cpp": "no template named",
    "dlpack_absent.fail.cpp": "dlpack bridge unavailable",
    "managed_mdspan.fail.cpp": "no template named",
    "calendar_runtime.fail.cpp": "no type named",
    "spaceship.fail.cpp": "invalid operands",
    "invalid_alignment.fail.cpp": "static assertion",
    "invalid_slice.fail.cpp": "no matching function",
    "multi_index_cxx20.fail.cpp": "comma",
    "owning_pointer.fail.cpp": "no template named",
    "standard_mutex.fail.cpp": "no type named",
    "default_stack.fail.cpp": "too few template arguments",
    "bad_variant_access.fail.cpp": "no type named",
    "variant_get.fail.cpp": "no matching function",
    "variant_get_index_const_lvalue.fail.cpp": "no matching function",
    "variant_get_index_rvalue.fail.cpp": "no matching function",
    "variant_get_index_const_rvalue.fail.cpp": "no matching function",
    "variant_get_type_lvalue.fail.cpp": "no matching function",
    "variant_get_type_const_lvalue.fail.cpp": "no matching function",
    "variant_get_type_rvalue.fail.cpp": "no matching function",
    "variant_get_type_const_rvalue.fail.cpp": "no matching function",
    "initializer_list_ctor.fail.cpp": "no matching constructor",
    "initializer_list_emplace.fail.cpp": "no matching member function",
    "reference_alternative.fail.cpp": "static assertion",
    "arrive_tx.fail.asc": "no member named",
    "reset.fail.asc": "no member named",
    "timed_wait.fail.asc": "no member named",
    "scoped_sync_simd.fail.asc": "deleted",
    "unsupported_width.fail.cpp": "static assertion",
    "byteswap_bool.fail.cpp": "static assertion",
    "strong_order.fail.cpp": "no member named",
    "exception_ptr.fail.cpp": "no type named",
    "blas_algorithm.fail.cpp": "no member named",
    "saturating_bool.fail.cpp": "static assertion",
    "uniform_double.fail.cpp": "implicit instantiation of undefined template",
    "double_excluded.fail.asc": "implicit instantiation of undefined template",
    "random_device.fail.cpp": "no type named",
    "error_code.fail.cpp": "no type named",
    "layout_compatible.fail.cpp": "no member named",
    "is_swappable_internal_parameter.fail.cpp": "template argument",
    "is_nothrow_swappable_internal_parameter.fail.cpp": "template argument",
    "compare_cxx17_absent.fail.cpp": "no type named",
    "string_view_constructor.fail.cpp": "no matching constructor",
    "reset_position.fail.cpp": "too many arguments",
    "flip_position.fail.cpp": "too many arguments",
    "test_position.fail.cpp": "no member named",
    "to_ulong_overflow.fail.cpp": "no matching",
    "chars_format_precision.fail.cpp": "chars_format",
    "to_chars_bool.fail.cpp": "deleted",
    "and_then_lvalue.fail.cpp": "no member named",
    "and_then_rvalue.fail.cpp": "no member named",
    "and_then_const_lvalue.fail.cpp": "no member named",
    "and_then_const_rvalue.fail.cpp": "no member named",
    "transform_lvalue.fail.cpp": "no member named",
    "transform_rvalue.fail.cpp": "no member named",
    "transform_const_lvalue.fail.cpp": "no member named",
    "transform_const_rvalue.fail.cpp": "no member named",
    "or_else_rvalue.fail.cpp": "no member named",
    "or_else_const_lvalue.fail.cpp": "no member named",
    "value_lvalue.fail.cpp": "no member named",
    "value_rvalue.fail.cpp": "no member named",
    "value_const_lvalue.fail.cpp": "no member named",
    "value_const_rvalue.fail.cpp": "no member named",
    "min_initializer.fail.cpp": "no matching function",
    "min_initializer_compare.fail.cpp": "no matching function",
    "max_initializer.fail.cpp": "no matching function",
    "max_initializer_compare.fail.cpp": "no matching function",
    "minmax_initializer.fail.cpp": "no matching function",
    "minmax_initializer_compare.fail.cpp": "no matching function",
}

NEGATIVE_DIAGNOSTIC_OVERRIDES = {
    ("asc/__atomic/scoped_atomic.h", "unsupported_type.fail.asc"): ("supports exactly",),
    ("asc/collectives", "simd_excluded.fail.asc"): ("no member named 'block_reduce_add'",),
    ("asc/collectives", "ub_span_dsimt.fail.asc"): ("no member named 'ub_reduce_add'",),
    ("asc/std/scoped_allocator", "default_allocator.fail.cpp"): ("base specifier must name a class",),
    ("asc/iterator", "address_space_erasure.fail.asc"): ("cannot initialize",),
    ("asc/mdspan", "ub_dsimt.fail.asc"): ("no template named", "no member named"),
    ("asc/std/random", "seed_sequence.fail.cpp"): ("no matching constructor",),
}

COMPLEX_SCALAR_NEGATIVE_CASES = {
    "scalar_double.fail.cpp",
    "scalar_integral.fail.cpp",
    "scalar_long_double.fail.cpp",
}


def negative_modes(target: str, name: str) -> tuple[tuple[str, bool], ...]:
    simd_only = (
        "simd_excluded.fail.asc", "simt_only.fail.asc",
        "store_excluded.fail.asc", "scoped_sync_simd.fail.asc",
    )
    if name in simd_only or target == "asc/std/source_location":
        return (("simd", False),)
    if name == "simt_excluded.fail.asc":
        return (("simt", True),)
    if name in ("ub_span_dsimt.fail.asc", "pipeline_dsimt.fail.asc", "block_value_type_simt.fail.asc"):
        return (("simt", True),)
    if name == "ub_dsimt.fail.asc":
        return (("simt", True),)
    if name == "address_space_erasure.fail.asc":
        return (("simd", False),)
    if name == "pipeline_element_type.fail.asc":
        return (("simd", False),)
    if name == "simd_scalar_sincos.fail.asc":
        return (("simd", False),)
    if name == "simt_double_sincos.fail.asc":
        return (("simt", True),)
    return (("simd", False), ("simt", True))


def header_tasks(rows: list[dict], standards: list[str], build_root: Path) -> list[CompileTask]:
    tasks: list[CompileTask] = []
    for index, row in enumerate(rows):
        source = build_root / f"header-{index}.asc"
        source.write_text(f"#include <{row['target']}>\n#include <{row['target']}>\n", encoding="utf-8")
        for standard in standards:
            for mode, simt in (("simd", False), ("simt", True)):
                suffix = standard.replace("+", "x")
                tasks.append(
                    CompileTask(
                        len(tasks), "header", f"header:{row['target']}:{standard}:{mode}",
                        source, build_root / f"header-{index}-{suffix}-{mode}.o",
                        CompileOptions(standard, simt), row["target"],
                    )
                )
    return tasks


def append_semantic_case(
    context: tuple[list[CompileTask], list[str], Path, Path], row: dict, target: str, name: str,
) -> None:
    tasks, standards, build_root, test_root = context
    source = case_root(test_root, target) / name
    applicable = ["c++20"] if row["target"].startswith("asc/std/__concepts/") else standards
    for standard in applicable:
        for mode, simt in (("simd", False), ("simt", True)):
            suffix = standard.replace("+", "x")
            tasks.append(
                CompileTask(
                    len(tasks), "semantic", f"semantic:{target}:{name}:{standard}:{mode}",
                    source, build_root / f"semantic-{len(tasks)}-{suffix}-{mode}.o",
                    CompileOptions(standard, simt), target,
                )
            )


def semantic_tasks(
    rows: list[dict], standards: list[str], build_root: Path, test_root: Path
) -> list[CompileTask]:
    tasks: list[CompileTask] = []
    context = (tasks, standards, build_root, test_root)
    seen: set[tuple[str, str]] = set()
    for row in rows:
        if not row["applicability"]["device_compile"]:
            continue
        target = row.get("semantic_case", row["target"])
        for name in row.get("device_compile_cases", ["device.compile.asc"]):
            identity = (target, name)
            if identity not in seen:
                seen.add(identity)
                append_semantic_case(context, row, target, name)
    return tasks


def append_negative_case(
    context: tuple[list[CompileTask], Path], target: str, name: str, standard: str, source: Path,
) -> None:
    tasks, build_root = context
    for mode, simt in negative_modes(target, name):
        suffix = standard.replace("+", "x")
        tasks.append(
            CompileTask(
                len(tasks), "negative", f"negative:{target}:{name}:{standard}:{mode}",
                source, build_root / f"negative-{len(tasks)}-{suffix}-{mode}.o",
                CompileOptions(standard, simt, expect_failure=True), target, name,
            )
        )


def negative_tasks(rows: list[dict], test_root: Path, build_root: Path) -> list[CompileTask]:
    tasks: list[CompileTask] = []
    context = (tasks, build_root)
    for row in rows:
        target = row["target"]
        for name in row.get("negative_cases", []):
            source = case_root(test_root, target) / name
            applicable_standards = (
                ["c++17"] if name in {"cxx17_absent.fail.cpp", "compare_cxx17_absent.fail.cpp"} else
                row.get("negative_case_languages", {}).get(name, ["c++17", "c++20"])
            )
            for standard in applicable_standards:
                append_negative_case(context, target, name, standard, source)
    return tasks


def build_tasks(
    rows: list[dict], standards: list[str], build_root: Path, test_root: Path
) -> list[CompileTask]:
    groups = (
        header_tasks(rows, standards, build_root),
        semantic_tasks(rows, standards, build_root, test_root),
        negative_tasks(rows, test_root, build_root),
    )
    tasks = [task for group in groups for task in group]
    return [replace(task, order=index) for index, task in enumerate(tasks)]


def load_changed_targets(path: Path) -> list[str]:
    targets = [
        line.strip().removeprefix("<").removesuffix(">")
        for line in path.read_text(encoding="utf-8").splitlines()
        if line.strip() and not line.lstrip().startswith("#")
    ]
    if not targets:
        raise ValueError(f"changed-targets file is empty: {path}")
    return sorted(set(targets))


def select_rows(rows: list[dict], changed_path: Path | None) -> tuple[list[dict], list[str]]:
    if changed_path is None:
        return rows, []
    changed = load_changed_targets(changed_path)
    known = {row["target"] for row in rows}
    unknown = sorted(set(changed) - known)
    if unknown:
        raise ValueError(f"changed targets are absent from the candidate manifest: {unknown}")
    reverse: dict[str, set[str]] = {target: set() for target in known}
    for row in rows:
        for dependency in row.get("dependencies", []):
            if dependency in reverse:
                reverse[dependency].add(row["target"])
    affected = set(changed)
    pending = deque(changed)
    while pending:
        for target in sorted(reverse[pending.popleft()] - affected):
            affected.add(target)
            pending.append(target)
    return [row for row in rows if row["target"] in affected], changed


def expected_negative_diagnostic(task: CompileTask, output: str) -> bool:
    lowered = output.lower()
    marker = NEGATIVE_DIAGNOSTIC_MARKERS.get(task.negative_name, "deleted")
    expected = marker.lower() in lowered
    key = (task.target, task.negative_name)
    override_markers = NEGATIVE_DIAGNOSTIC_OVERRIDES.get(key)
    if override_markers is not None:
        return any(item in lowered for item in override_markers)
    if key == ("asc/__atomic/scoped_atomic.h", "simd_excluded.fail.asc"):
        return expected or "deleted" in lowered
    if task.target == "asc/std/complex" and task.negative_name in COMPLEX_SCALAR_NEGATIVE_CASES:
        return "no matching function for call to 'arg'" in lowered if task.options.simt else expected
    if task.target == "asc/std/source_location":
        return "cannot initialize a parameter" in output and "const char *" in output
    if task.target == "asc/launch" and task.negative_name == "device_call.fail.asc":
        marker = (
            "call to __host__ function from __device__ function"
            if task.options.simt else "reference to __global__"
        )
        return marker in lowered
    return expected


def failure_for_result(result: CompileResult) -> str | None:
    task = result.task
    has_error = any(marker in result.output.lower() for marker in ERROR_MARKERS)
    output_exists = task.output.is_file() and task.output.stat().st_size > 0
    if result.timed_out:
        return f"Device compile timed out after {result.duration_seconds:.2f}s: {task.label}"
    if task.options.expect_failure:
        if not has_error or not expected_negative_diagnostic(task, result.output) or output_exists:
            return f"unexpected Device negative result: {task.label}\n{result.output}"
        return None
    if result.returncode != 0 or has_error or not output_exists:
        return f"Device compile failed: {' '.join(result.command)}\n{result.output}"
    return None


def run_tasks(device: DeviceCompiler, tasks: list[CompileTask], jobs: int) -> list[CompileResult]:
    if jobs == 1:
        return [device.compile(task) for task in tasks]
    with ThreadPoolExecutor(max_workers=jobs, thread_name_prefix="asc-stl-device") as executor:
        return list(executor.map(device.compile, tasks))


def result_record(result: CompileResult) -> dict[str, object]:
    task = result.task
    failure = failure_for_result(result)
    return {
        "command": result.command,
        "duration_seconds": round(result.duration_seconds, 3),
        "expected_failure": task.options.expect_failure,
        "kind": task.kind,
        "label": task.label,
        "mode": "simt" if task.options.simt else "simd",
        "returncode": result.returncode,
        "standard": task.options.standard,
        "status": "passed" if failure is None else "failed",
        "target": task.target,
        "timed_out": result.timed_out,
        "failure": failure or "",
    }


def write_report(path: Path, report: dict[str, object]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    value = json.dumps(report, ensure_ascii=False, indent=2, sort_keys=True) + "\n"
    path.write_text(value, encoding="utf-8")


def positive_integer(value: str) -> int:
    parsed = int(value)
    if parsed < 1:
        raise argparse.ArgumentTypeError("value must be a positive integer")
    return parsed


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--include-root", type=Path, required=True)
    parser.add_argument("--test-root", type=Path, required=True)
    parser.add_argument("--npu-arch", required=True)
    parser.add_argument("--standards", nargs="+", default=["c++17", "c++20"])
    parser.add_argument("--jobs", type=positive_integer, default=4)
    parser.add_argument("--task-timeout-seconds", type=positive_integer, default=600)
    parser.add_argument("--changed-targets-file", type=Path)
    parser.add_argument("--report", type=Path)
    return parser.parse_args()


def execute(args: argparse.Namespace, compiler: str) -> tuple[dict[str, object], list[str]]:
    all_rows = json.loads(args.manifest.read_text(encoding="utf-8"))["headers"]
    rows, changed = select_rows(all_rows, args.changed_targets_file)
    started = time.monotonic()
    with tempfile.TemporaryDirectory(prefix="asc-stl-device-") as value:
        tasks = build_tasks(rows, args.standards, Path(value), args.test_root)
        device = DeviceCompiler(
            compiler, args.include_root, args.test_root, args.npu_arch, args.task_timeout_seconds
        )
        results = run_tasks(device, tasks, args.jobs)
        failures = [failure for result in results if (failure := failure_for_result(result))]
        report = {
            "changed_targets": changed,
            "duration_seconds": round(time.monotonic() - started, 3),
            "jobs": args.jobs,
            "manifest_header_count": len(all_rows),
            "mode": "affected" if changed else "full",
            "passed": not failures,
            "results": [result_record(result) for result in results],
            "schema_version": 1,
            "selected_header_count": len(rows),
            "selected_targets": [row["target"] for row in rows],
            "task_counts": dict(sorted(Counter(task.kind for task in tasks).items())),
            "task_timeout_seconds": args.task_timeout_seconds,
        }
    return report, failures


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    args = parse_args()
    compiler = shutil.which("bisheng")
    if compiler is None:
        raise RuntimeError("BiSheng compiler is unavailable in the loaded CANN environment")
    try:
        report, failures = execute(args, compiler)
    except ValueError as error:
        LOGGER.error("%s", error)
        return 2
    if args.report is not None:
        write_report(args.report, report)
    if failures:
        for failure in failures:
            LOGGER.error("%s", failure)
        return 1
    counts = report["task_counts"]
    LOGGER.info(
        "PASS: %d/%d Headers, %d tasks (%s), jobs=%d, duration=%.3fs",
        report["selected_header_count"], report["manifest_header_count"], sum(counts.values()),
        ", ".join(f"{name}={count}" for name, count in counts.items()), report["jobs"],
        report["duration_seconds"],
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
