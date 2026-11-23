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

"""Validate language-baseline and explicitly empty compatibility boundaries."""

from __future__ import annotations

import argparse
import logging
import subprocess
import tempfile
from pathlib import Path


LOGGER = logging.getLogger(__name__)


def compile_source(
    compiler: str, include: Path, source: Path, output: Path, standard: str
) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        [
            compiler, f"-std={standard}", "-Wall", "-Wextra", "-Werror",
            f"-I{include}", "-c", str(source), "-o", str(output),
        ],
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        check=False,
    )


def validate_language_baseline(compiler: str, include: Path, temporary: Path) -> None:
    source = temporary / "cxx17.cpp"
    source.write_text("#include <asc/__config>\nint main() { return 0; }\n", encoding="utf-8")
    process = compile_source(compiler, include, source, source.with_suffix(".o"), "c++17")
    if process.returncode != 0:
        raise RuntimeError(f"C++17 consumer was rejected by the minimum baseline:\n{process.stdout}")
    process = compile_source(compiler, include, source, source.with_suffix(".o"), "c++14")
    if process.returncode == 0 or "ASC-STL requires C++17 or newer" not in process.stdout:
        raise RuntimeError("pre-C++17 consumer was not rejected by the frozen baseline")


def validate_concept_absence(compiler: str, include: Path, temporary: Path) -> None:
    source = temporary / "cxx17_predicate.cpp"
    source.write_text(
        "#include <asc/std/__concepts/same_as.h>\nstatic_assert(asc::std::same_as<int, int>);\n",
        encoding="utf-8",
    )
    process = compile_source(compiler, include, source, source.with_suffix(".o"), "c++17")
    if process.returncode != 0:
        raise RuntimeError(f"C++17 concept predicate backport failed:\n{process.stdout}")
    source.write_text(
        "#include <asc/std/__concepts/same_as.h>\n"
        "template<class T> concept native_concept = asc::std::same_as<T, int>;\n",
        encoding="utf-8",
    )
    process = compile_source(compiler, include, source, source.with_suffix(".o"), "c++17")
    if process.returncode == 0 or "concept" not in process.stdout:
        raise RuntimeError(f"native concept syntax unexpectedly compiled in C++17:\n{process.stdout}")


def validate_empty_headers(compiler: str, include: Path, temporary: Path) -> None:
    source = temporary / "empty_compat.cpp"
    source.write_text(
        """
#include <asc/std/ciso646>
#include <asc/std/cstdalign>
#include <asc/std/cstdbool>
#if defined(__alignas_is_defined) || defined(__bool_true_false_are_defined)
#error "legacy C compatibility macro leaked into C++20"
#endif
int main() {
    return 0; }
""",
        encoding="utf-8",
    )
    subprocess.run(
        [
            compiler, "-std=c++20", "-Wall", "-Wextra", "-Werror",
            f"-I{include}", str(source), "-o", str(temporary / "empty_compat"),
        ],
        check=True,
    )


COMPILE_FAILURE_CASES = (
    ("cases/asc/utility/zero_step.fail.cpp", "static_for step must be nonzero"),
    ("cases/asc/numeric_types/invalid_int4.fail.cpp", "terminate"),
    ("cases/asc/numeric_types/invalid_pack.fail.cpp", "terminate"),
    ("cases/asc/numeric_types/invalid_index.fail.cpp", "terminate"),
    ("cases/asc/numeric_types/ordinary_integer.fail.cpp", "no matching function"),
    ("cases/asc/numeric_types/scalar_pack.fail.cpp", "no matching function"),
    ("cases/asc/numeric_types/unchecked_int4.fail.cpp", "no matching function"),
    ("cases/asc/numeric_types/unsupported.fail.cpp", "no matching function"),
    ("cases/asc/numeric_types/host_native.fail.cpp", "native_type"),
    ("cases/asc/random/seed_sequence.fail.cpp", "cannot convert"),
    ("cases/asc/std/expected/value.fail.cpp", "deleted"),
    ("cases/asc/std/expected/void.fail.cpp", "incomplete type"),
    ("cases/asc/numeric/bool.fail.cpp", "static assertion"),
    ("cases/asc/numeric/floating.fail.cpp", "static assertion"),
    ("cases/asc/std/format/format_float_host.fail.cpp", "static assertion"),
    ("cases/asc/std/format/invalid_spec.fail.cpp", "__builtin_trap"),
    ("cases/asc/std/format/runtime_format.fail.cpp", "constant expression"),
    ("cases/asc/std/format/invalid_literal.fail.cpp", "constant expression"),
    ("cases/asc/std/ranges/repeat_unbounded.fail.cpp", "no match for call"),
    ("cases/asc/std/ranges/zip_three.fail.cpp", "no match for call"),
    ("cases/asc/std/__utility/as_const/rvalue.fail.cpp", "deleted"),
    ("cases/asc/std/__memory/addressof/rvalue.fail.cpp", "deleted"),
    ("cases/asc/std/numbers/e_v_double_excluded.fail.cpp", "static assertion"),
    ("cases/asc/std/numbers/e_v_long_double_excluded.fail.cpp", "static assertion"),
    ("cases/asc/std/__iterator/data/initializer_list_excluded.fail.cpp", "no matching function"),
    ("cases/asc/std/__iterator/empty/initializer_list_excluded.fail.cpp", "no matching function"),
    ("cases/asc/__memory/views/implicit_allocation.fail.cpp", "deleted"),
    ("cases/asc/__memory/views/raw_pointer_classification.fail.cpp", "incomplete"),
    ("cases/asc/__memory/views/managed_view.fail.cpp", "managed_span"),
    ("cases/asc/__atomic/scoped_atomic/unsupported_type.fail.cpp", "supports exactly"),
    ("cases/asc/atomic/host_call.fail.cpp", "deleted"),
    ("cases/asc/std/__functional/reference_wrapper/rvalue.fail.cpp", "deleted"),
    ("cases/asc/std/__variant/variant_constraints/reference_alternative.fail.cpp", "static assertion"),
    ("cases/asc/std/__complex/arg/unsupported_double.fail.cpp", "static assertion"),
    ("cases/asc/execution.require/invalid_requirement_type.fail.cpp", "no matching function"),
    ("cases/asc/execution.policy/implicit_resource.fail.cpp", "no matching function"),
    ("cases/asc/hierarchy/host_query.fail.cpp", "block_index"),
    ("cases/asc/launch/ordinary_cpp_launch.fail.cpp", "launch"),
    ("cases/asc/std/__charconv/to_chars/float.fail.cpp", "ambiguous"),
    ("cases/asc/std/__charconv/to_chars/chars_format.fail.cpp", "chars_format"),
    ("cases/asc/cmath/int128_excluded.fail.cpp", "static assertion"),
    ("cases/asc/work_queue/cancel_excluded.fail.cpp", "no member named"),
    ("cases/asc/std/__charconv/from_chars/chars_format.fail.cpp", "chars_format"),
    ("cases/asc/std/array/get_out_of_bounds.fail.cpp", "static assertion"),
    ("cases/asc/std/array/at_excluded.fail.cpp", "no member named"),
    ("cases/asc/std/span/writable_const_span.fail.cpp", "no matching function"),
    ("cases/asc/std/span/fixed_extent_mismatch.fail.cpp", "no matching"),
    ("cases/asc/std/span/at_excluded.fail.cpp", "no member named"),
    ("cases/asc/std/span/fixed_default.fail.cpp", "no matching function"),
    ("cases/asc/std/optional/optional_reference.fail.cpp", "rvalue"),
    ("cases/asc/std/iterator/initializer_list_data.fail.cpp", "no matching function"),
    ("cases/asc/std/iterator/initializer_list_empty.fail.cpp", "no matching function"),
    ("cases/asc/std/iterator/initializer_list_advance.fail.cpp", "no type named"),
    ("cases/asc/std/iterator/back_insert_iterator_spaceship.fail.cpp", "no matching function"),
    ("cases/asc/std/iterator/iter_const_reference.fail.cpp", "is not a member"),
    ("cases/asc/std/__expected/expected/expected_value.fail.cpp", "use of deleted function"),
    ("cases/asc/std/__variant/comparison/variant_emplace_type_initializer_list.fail.cpp", "is not a member"),
    ("cases/asc/std/__variant/comparison/variant_emplace_index_initializer_list.fail.cpp", "is not a member"),
    ("cases/asc/std/__variant/comparison/variant_ctor_in_place_type_initializer_list.fail.cpp", "is not a member"),
    ("cases/asc/std/__variant/comparison/variant_ctor_in_place_index_initializer_list.fail.cpp", "is not a member"),
    ("cases/asc/std/__chrono/system_clock/system_clock_runtime.fail.cpp", "not a member"),
    ("cases/asc/std/__chrono/system_clock/system_clock_to_time_t.fail.cpp", "not a member"),
    ("cases/asc/std/__chrono/system_clock/system_clock_from_time_t.fail.cpp", "not a member"),
    ("cases/asc/std/atomic/unsupported_type.fail.cpp", "supports exactly"),
    ("cases/asc/std/atomic/copy_deleted.fail.cpp", "deleted"),
    ("cases/asc/buffer/nontrivial_element.fail.cpp", "static assertion"),
    ("cases/asc/memory_pool/native_adopt_excluded.fail.cpp", "is not a member"),
    ("cases/asc/std/list/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/list/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/list/excluded_surface.fail.cpp", "no member named"),
    ("cases/asc/std/map/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/map/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/map/excluded_surface.fail.cpp", "no member named"),
    ("cases/asc/std/__bit/byteswap/bool_excluded.fail.cpp", "static assertion"),
    ("cases/asc/std/execution/excluded_policy_overload.fail.cpp", "for_each"),
    ("cases/asc/std/functional/comparison_category_excluded.fail.cpp", "compare_three_way"),
    ("cases/asc/std/functional/cref_rvalue.fail.cpp", "deleted"),
    ("cases/asc/std/functional/function_excluded.fail.cpp", "function"),
    ("cases/asc/std/functional/ref_rvalue.fail.cpp", "deleted"),
    ("cases/asc/std/functional/searcher_excluded.fail.cpp", "boyer_moore_searcher"),
    ("cases/asc/std/latch/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/latch/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/shared_mutex/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/shared_mutex/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/shared_mutex/timed_excluded.fail.cpp", "try_lock_for"),
    ("cases/asc/std/queue/default_priority_queue.fail.cpp", "wrong number"),
    ("cases/asc/std/queue/default_queue.fail.cpp", "wrong number"),
    ("cases/asc/std/deque/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/deque/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/deque/default_allocator.fail.cpp", "wrong number"),
    ("cases/asc/std/deque/move_assign.fail.cpp", "deleted"),
    ("cases/asc/std/deque/move_construct.fail.cpp", "deleted"),
    ("cases/asc/iterator/owning_range.fail.cpp", "does not name"),
    ("cases/asc/mdspan/dlpack_absent.boundary.cpp", "dlpack bridge unavailable"),
    ("cases/asc/mdspan/managed_mdspan.fail.cpp", "does not name"),
    ("cases/asc/std/barrier/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/barrier/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/chrono/calendar_runtime.fail.cpp", "does not name"),
    ("cases/asc/std/chrono/spaceship.fail.cpp", "operator<=>"),
    ("cases/asc/std/chrono/system_clock_runtime.fail.cpp", "not a member"),
    ("cases/asc/std/forward_list/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/forward_list/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/forward_list/excluded_surface.fail.cpp", "no member"),
    ("cases/asc/std/mdspan/invalid_alignment.fail.cpp", "static assertion"),
    ("cases/asc/std/mdspan/invalid_slice.fail.cpp", "no matching"),
    ("cases/asc/std/mdspan/multi_index_cxx20.fail.cpp", "comma"),
    ("cases/asc/std/memory/addressof_rvalue.fail.cpp", "deleted"),
    ("cases/asc/std/memory/owning_pointer.fail.cpp", "does not name"),
    ("cases/asc/std/mutex/copy_unique_lock.fail.cpp", "deleted"),
    ("cases/asc/std/mutex/standard_mutex.fail.cpp", "does not name"),
    ("cases/asc/std/mutex/timed_excluded.fail.cpp", "try_lock_for"),
    ("cases/asc/std/scoped_allocator/default_allocator.fail.cpp", "base type"),
    ("cases/asc/std/set/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/set/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/set/excluded_surface.fail.cpp", "no member"),
    ("cases/asc/std/stack/default_stack.fail.cpp", "wrong number"),
    ("cases/asc/std/string/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/string/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/string/move_construct.fail.cpp", "deleted"),
    ("cases/asc/std/unordered_map/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/unordered_map/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/unordered_map/excluded_surface.fail.cpp", "no member"),
    ("cases/asc/std/unordered_set/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/unordered_set/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/unordered_set/excluded_surface.fail.cpp", "no member"),
    ("cases/asc/std/variant/bad_variant_access.fail.cpp", "does not name"),
    ("cases/asc/std/variant/initializer_list_ctor.fail.cpp", "no matching"),
    ("cases/asc/std/variant/initializer_list_emplace.fail.cpp", "no matching"),
    ("cases/asc/std/variant/reference_alternative.fail.cpp", "static assertion"),
    ("cases/asc/std/variant/spaceship.fail.cpp", "operator<=>"),
    ("cases/asc/std/vector/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/vector/copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/vector/default_allocator.fail.cpp", "wrong number"),
    ("cases/asc/bit/unsupported_width.fail.cpp", "no matching"),
    ("cases/asc/std/bit/byteswap_bool.fail.cpp", "static assertion"),
    ("cases/asc/std/compare/strong_order.fail.cpp", "not a member"),
    ("cases/asc/std/exception/exception_ptr.fail.cpp", "does not name"),
    ("cases/asc/std/linalg/blas_algorithm.fail.cpp", "not a member"),
    ("cases/asc/std/numeric/saturating_bool.fail.cpp", "static assertion"),
    ("cases/asc/std/random/seed_sequence.fail.cpp", "no matching function"),
    ("cases/asc/std/random/uniform_double.fail.cpp", "incomplete type"),
    ("cases/asc/std/__random/generate_canonical/double_excluded.fail.cpp", "incomplete type"),
    ("cases/asc/std/random/random_device.fail.cpp", "does not name"),
    ("cases/asc/std/system_error/error_code.fail.cpp", "does not name"),
    ("cases/asc/std/type_traits/layout_compatible.fail.cpp", "not a member"),
    ("cases/asc/std/string/move_assign.fail.cpp", "deleted"),
    ("cases/asc/std/bitset/string_view_constructor.fail.cpp", "no matching"),
    ("cases/asc/std/bitset/reset_position.fail.cpp", "no matching"),
    ("cases/asc/std/bitset/flip_position.fail.cpp", "no matching"),
    ("cases/asc/std/bitset/test_position.fail.cpp", "no member"),
    ("cases/asc/std/bitset/to_ulong_overflow.fail.cpp", "no matching"),
    ("cases/asc/std/atomic/copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/atomic/flag_copy_construct.fail.cpp", "deleted"),
    ("cases/asc/std/atomic/flag_copy_assign.fail.cpp", "deleted"),
    ("cases/asc/std/__charconv/to_chars/to_chars_bool.fail.cpp", "deleted"),
    ("cases/asc/std/__charconv/to_chars/chars_format_precision.fail.cpp", "chars_format"),
    ("cases/asc/std/mutex/copy_assign_unique_lock.fail.cpp", "deleted"),
    ("cases/asc/std/optional/and_then_lvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/and_then_rvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/and_then_const_lvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/and_then_const_rvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/transform_lvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/transform_rvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/transform_const_lvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/transform_const_rvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/or_else_rvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/or_else_const_lvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/value_lvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/value_rvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/value_const_lvalue.fail.cpp", "no member"),
    ("cases/asc/std/optional/value_const_rvalue.fail.cpp", "no member"),
    ("cases/asc/std/algorithm/min_initializer.fail.cpp", "no matching"),
    ("cases/asc/std/algorithm/min_initializer_compare.fail.cpp", "no matching"),
    ("cases/asc/std/algorithm/max_initializer.fail.cpp", "no matching"),
    ("cases/asc/std/algorithm/max_initializer_compare.fail.cpp", "no matching"),
    ("cases/asc/std/algorithm/minmax_initializer.fail.cpp", "no matching"),
    ("cases/asc/std/algorithm/minmax_initializer_compare.fail.cpp", "no matching"),
)


def validate_compile_failures(compiler: str, include: Path, test_root: Path, temporary: Path) -> None:
    cases = COMPILE_FAILURE_CASES
    cxx20_only = {
        "cases/asc/std/format/format_float_host.fail.cpp",
        "cases/asc/std/format/invalid_spec.fail.cpp",
        "cases/asc/std/format/runtime_format.fail.cpp",
        "cases/asc/std/format/invalid_literal.fail.cpp",
        "cases/asc/std/compare/strong_order.fail.cpp",
        "cases/asc/std/bitset/spaceship.fail.cpp",
        "cases/asc/std/chrono/spaceship.fail.cpp",
        "cases/asc/std/deque/spaceship.fail.cpp",
        "cases/asc/std/inplace_vector/spaceship.fail.cpp",
        "cases/asc/std/iterator/back_insert_iterator_spaceship.fail.cpp",
        "cases/asc/std/list/spaceship.fail.cpp",
        "cases/asc/std/map/spaceship.fail.cpp",
        "cases/asc/std/string/spaceship.fail.cpp",
        "cases/asc/std/variant/spaceship.fail.cpp",
    }
    for relative, marker in cases:
        negative = test_root / relative
        standards = ("c++20",) if relative in cxx20_only else ("c++17", "c++20")
        for standard in standards:
            output = temporary / f"{negative.parent.name}-{standard}.o"
            process = compile_source(compiler, include, negative, output, standard)
            if process.returncode == 0 or marker not in process.stdout.lower():
                raise RuntimeError(
                    f"negative boundary was not rejected in {standard} ({marker}): {negative}\n{process.stdout}"
                )


def validate_format_cxx17_absence(compiler: str, include: Path, test_root: Path, temporary: Path) -> None:
    negative = test_root / "cases/asc/std/format/cxx17_absent.fail.cpp"
    process = compile_source(compiler, include, negative, temporary / "format-cxx17.o", "c++17")
    if process.returncode == 0 or "format_string" not in process.stdout:
        raise RuntimeError(f"C++17 format surface was not absent: {negative}\n{process.stdout}")

    negative = test_root / "cases/asc/std/compare/compare_cxx17_absent.fail.cpp"
    process = compile_source(compiler, include, negative, temporary / "compare-cxx17.o", "c++17")
    if process.returncode == 0 or "compare_three_way" not in process.stdout:
        raise RuntimeError(f"C++17 comparison callable was not absent: {negative}\n{process.stdout}")


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser()
    parser.add_argument("--include", type=Path, required=True)
    parser.add_argument("--test-root", type=Path, required=True)
    parser.add_argument("--compiler", required=True)
    args = parser.parse_args()

    with tempfile.TemporaryDirectory(prefix="asc-stl-negative-") as value:
        temporary = Path(value)
        validate_language_baseline(args.compiler, args.include, temporary)
        validate_concept_absence(args.compiler, args.include, temporary)
        validate_empty_headers(args.compiler, args.include, temporary)
        validate_compile_failures(args.compiler, args.include, args.test_root, temporary)
        validate_format_cxx17_absence(args.compiler, args.include, args.test_root, temporary)

    LOGGER.info(
        "PASS: C++17 baseline, pre-C++17 rejection, concept predicates and native-syntax gating, "
        "empty compatibility, and compile-failure boundaries"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
