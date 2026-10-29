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

find_package(Python3 REQUIRED COMPONENTS Interpreter)

option(ASC_STL_ENABLE_HOST_TESTS "Enable Host Header and semantic gates" ON)
option(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS "Enable real CCE Device compile gates" OFF)
option(ASC_STL_ENABLE_CANNSIM_TESTS "Enable cannsim runtime gates" OFF)
set(ASC_STL_CANN_PACKAGE_PATH "$ENV{ASCEND_HOME_PATH}" CACHE PATH "Installed CANN package root")
set(ASC_STL_TARGET_SOC "" CACHE STRING "AscendC target SoC")
set(ASC_STL_NPU_ARCH "dav-3510" CACHE STRING "BiSheng --npu-arch value")
set(ASC_STL_DEVICE_COMPILE_JOBS "4" CACHE STRING "Maximum concurrent BiSheng compile tasks")
set(ASC_STL_DEVICE_TASK_TIMEOUT_SECONDS "600" CACHE STRING "Per-BiSheng task timeout")
set(ASC_STL_DEVICE_CHANGED_TARGETS_FILE "" CACHE FILEPATH "Changed target list for the affected Device gate")
set(ASC_STL_DEVICE_REPORT "${CMAKE_CURRENT_BINARY_DIR}/device-compile-report.json" CACHE FILEPATH "Device gate JSON report")
set(ASC_STL_CANNSIM_EXECUTABLE "" CACHE FILEPATH "cannsim executable")
set(ASC_STL_CANNSIM_SOC "Ascend950" CACHE STRING "cannsim target SoC")
set(ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS "600" CACHE STRING "Per-cannsim runtime case timeout")
set(ASC_STL_TEST_CXX_STANDARD "17" CACHE STRING "C++ standard used by Device runtime test builds")
set(ASC_STL_DOC_EXAMPLE_JOBS "4" CACHE STRING "Maximum concurrent API example compilers")

set(ASC_STL_TEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(ASC_STL_MANIFEST "${ASC_STL_TEST_ROOT}/metadata/headers.json")
set(ASC_STL_INCLUDE_ROOT "${PROJECT_SOURCE_DIR}/include")
set(ASC_STL_CASES_ROOT "${ASC_STL_TEST_ROOT}/cases")

add_test(
    NAME gate.metadata
    COMMAND
        ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/validate_metadata.py
        --manifest ${ASC_STL_MANIFEST}
        --include-root ${ASC_STL_INCLUDE_ROOT}
        --test-root ${ASC_STL_TEST_ROOT})
set_tests_properties(gate.metadata PROPERTIES LABELS "metadata;static-rules;affected-regression;nightly")

add_test(NAME gate.api-docs
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/check_api_docs.py)
add_test(NAME gate.api-docs-regressions
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/test_api_docs.py)
set_tests_properties(gate.api-docs gate.api-docs-regressions
    PROPERTIES LABELS "static-rules;affected-regression;nightly" TIMEOUT 120)

add_test(NAME compatibility.codecheck-worktree-isolation
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/test_codecheck_worktree.py
            --allow-missing-rsync)
set_tests_properties(compatibility.codecheck-worktree-isolation
    PROPERTIES LABELS "static-rules;affected-regression;nightly" TIMEOUT 30 SKIP_RETURN_CODE 77)

add_test(NAME compatibility.parallel-example-runner
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/test_parallel_example_runner.py)
set_tests_properties(compatibility.parallel-example-runner
    PROPERTIES LABELS "static-rules;affected-regression;nightly" TIMEOUT 120)

add_test(
    NAME gate.product-contract
    COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/validate_product_contract.py
            ${PROJECT_SOURCE_DIR})
set_tests_properties(gate.product-contract PROPERTIES LABELS "metadata;static-rules;affected-regression;nightly")

add_test(
    NAME gate.dependencies
    COMMAND
        ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/validate_observed_dependencies.py
        --headers ${ASC_STL_MANIFEST}
        --include ${ASC_STL_INCLUDE_ROOT})
set_tests_properties(gate.dependencies PROPERTIES LABELS "metadata;static-rules;affected-regression;nightly")

add_test(
    NAME compatibility.hardware-device-discovery
    COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/check_hardware_device.py)
set_tests_properties(
    compatibility.hardware-device-discovery
    PROPERTIES LABELS "static-rules;affected-regression;nightly" TIMEOUT 30)

if(ASC_STL_ENABLE_HOST_TESTS)
    foreach(standard IN ITEMS 17 20)
        foreach(dependencies IN ITEMS core optional)
            set(doc_test "docs.host.cxx${standard}.${dependencies}")
            add_test(NAME "${doc_test}"
                COMMAND ${Python3_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/check_api_docs.py
                    --examples --standard ${standard} --mode host --compiler ${CMAKE_CXX_COMPILER}
                    --dependencies ${dependencies} --require-all --jobs ${ASC_STL_DOC_EXAMPLE_JOBS}
                    --report ${CMAKE_CURRENT_BINARY_DIR}/docs-host-cxx${standard}-${dependencies}.json)
            set_tests_properties("${doc_test}" PROPERTIES
                LABELS "docs-examples;docs-host;affected-regression;nightly"
                RUN_SERIAL TRUE TIMEOUT 3600 SKIP_RETURN_CODE 77)
        endforeach()
    endforeach()

    add_test(
        NAME compatibility.hardware-timeout-safety
        COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/check_hardware_safety.py
                --compiler ${CMAKE_CXX_COMPILER})
    set_tests_properties(
        compatibility.hardware-timeout-safety
        PROPERTIES LABELS "static-rules;affected-regression;nightly" TIMEOUT 120)

    add_test(
        NAME compatibility.cann-sdk-layout
        COMMAND
            ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/check_cann_sdk_paths.py
            --include-root ${ASC_STL_INCLUDE_ROOT}
            --compiler ${CMAKE_CXX_COMPILER})
    set_tests_properties(
        compatibility.cann-sdk-layout
        PROPERTIES LABELS "static-rules;affected-regression;nightly" TIMEOUT 120)

    add_test(
        NAME compatibility.cann-runtime-bindings
        COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/check_runtime_sdk_bindings.py
                --compiler ${CMAKE_CXX_COMPILER})
    set_tests_properties(
        compatibility.cann-runtime-bindings
        PROPERTIES LABELS "static-rules;affected-regression;nightly" TIMEOUT 120)

    add_test(
        NAME header.host.all
        COMMAND
            ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/run_header_self_contained.py
            --metadata ${ASC_STL_MANIFEST}
            --include ${ASC_STL_INCLUDE_ROOT}
            --compiler ${CMAKE_CXX_COMPILER})
    set_tests_properties(header.host.all PROPERTIES LABELS "header-host;affected-regression;nightly")

    add_test(
        NAME integration.installed-consumer
        COMMAND
            ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/run_installed_consumer.py
            --source ${PROJECT_SOURCE_DIR}
            --consumer ${ASC_STL_TEST_ROOT}/consumer
            --metadata ${ASC_STL_MANIFEST}
            --compiler ${CMAKE_CXX_COMPILER})
    set_tests_properties(
        integration.installed-consumer
        PROPERTIES LABELS "installed-tree;consumer;semantic-host;affected-regression;nightly")

    add_test(
        NAME boundary.host
        COMMAND
            ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/validate_negative_boundaries.py
            --include ${ASC_STL_INCLUDE_ROOT}
            --test-root ${ASC_STL_TEST_ROOT}
            --compiler ${CMAKE_CXX_COMPILER})
    set_tests_properties(boundary.host PROPERTIES LABELS "negative-boundary;static-rules;affected-regression;nightly")

    function(asc_stl_add_host_case case_id source)
        set_property(GLOBAL APPEND PROPERTY ASC_STL_REGISTERED_HOST_CASE_SOURCES "${source}")
        set(case_standards 17 20)
        if(case_id STREQUAL "asc.std.__fwd.optional.value_members"
           OR case_id STREQUAL "asc.std.optional.excluded_members")
            set(case_standards 20)
        endif()
        foreach(standard IN LISTS case_standards)
            string(MAKE_C_IDENTIFIER "${case_id}_cxx${standard}" target_suffix)
            set(target "asc_stl_host_${target_suffix}")
            add_executable("${target}" "${ASC_STL_CASES_ROOT}/${source}")
            target_link_libraries("${target}" PRIVATE asc_stl::asc_stl)
            set_target_properties(
                "${target}"
                PROPERTIES CXX_STANDARD "${standard}" CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
            target_include_directories("${target}" PRIVATE "${ASC_STL_TEST_ROOT}")
            target_compile_options("${target}" PRIVATE -Wall -Wextra -Werror -pedantic -UNDEBUG)
            add_test(NAME "semantic.host.cxx${standard}.${case_id}" COMMAND "${target}")
            set_tests_properties(
                "semantic.host.cxx${standard}.${case_id}"
                PROPERTIES LABELS "semantic-host;cxx${standard};affected-regression;nightly")
        endforeach()
    endfunction()

    asc_stl_add_host_case("asc.std.expected.monads" "asc/std/expected/host.pass.cpp")
    asc_stl_add_host_case("asc.__config" "asc/__config/host.pass.cpp")
    add_executable(asc_stl_host_cxx17_baseline ${ASC_STL_CASES_ROOT}/asc/__config/cxx17.pass.cpp)
    target_link_libraries(asc_stl_host_cxx17_baseline PRIVATE asc_stl::asc_stl)
    set_target_properties(
        asc_stl_host_cxx17_baseline
        PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
    target_compile_options(asc_stl_host_cxx17_baseline PRIVATE -Wall -Wextra -Werror -pedantic -UNDEBUG)
    add_test(NAME semantic.host.cxx17-baseline COMMAND asc_stl_host_cxx17_baseline)
    set_tests_properties(
        semantic.host.cxx17-baseline
        PROPERTIES LABELS "semantic-host;cxx17;affected-regression;nightly")
    asc_stl_add_host_case("asc.execution.determinism" "asc/execution.determinism/host.pass.cpp")
    asc_stl_add_host_case("asc.execution.output_ordering" "asc/execution.output_ordering/host.pass.cpp")
    asc_stl_add_host_case("asc.execution.tie_break" "asc/execution.tie_break/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.concept_macros" "asc/std/__concepts/concept_macros/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cstddef.types" "asc/std/__cstddef/types/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.ctad_support" "asc/std/__utility/ctad_support/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.piecewise_construct" "asc/std/__utility/piecewise_construct/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.undefined" "asc/std/__utility/undefined/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.unreachable" "asc/std/__utility/unreachable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.cassert" "asc/std/cassert/host.pass.cpp")
    asc_stl_add_host_case("asc.std.cfloat" "asc/std/cfloat/host.pass.cpp")
    asc_stl_add_host_case("asc.std.climits" "asc/std/climits/host.pass.cpp")
    asc_stl_add_host_case("asc.std.cstdint" "asc/std/cstdint/host.pass.cpp")
    asc_stl_add_host_case("asc.std.source_location" "asc/std/source_location/host.pass.cpp")
    asc_stl_add_host_case("asc.std.version" "asc/std/version/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.add_const" "asc/std/__type_traits/add_const/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.add_cv" "asc/std/__type_traits/add_cv/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.add_volatile" "asc/std/__type_traits/add_volatile/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.always_false" "asc/std/__type_traits/always_false/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.conditional" "asc/std/__type_traits/conditional/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.dependent_type" "asc/std/__type_traits/dependent_type/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.enable_if" "asc/std/__type_traits/enable_if/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.integral_constant" "asc/std/__type_traits/integral_constant/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_constant_evaluated" "asc/std/__type_traits/is_constant_evaluated/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.lazy" "asc/std/__type_traits/lazy/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.nat" "asc/std/__type_traits/nat/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.remove_const" "asc/std/__type_traits/remove_const/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.remove_pointer" "asc/std/__type_traits/remove_pointer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.remove_volatile" "asc/std/__type_traits/remove_volatile/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.type_identity" "asc/std/__type_traits/type_identity/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.void_t" "asc/std/__type_traits/void_t/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.as_const" "asc/std/__utility/as_const/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.declval" "asc/std/__utility/declval/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__tuple.tuple_element" "asc/std/__tuple/tuple_element/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cstring.memcpy" "asc/std/__cstring/memcpy/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cstring.memset" "asc/std/__cstring/memset/host.pass.cpp")
    asc_stl_add_host_case("asc.atomic.b013" "asc/atomic/host.pass.cpp")
    asc_stl_add_host_case("asc.stream.b014" "asc/stream/host.pass.cpp")
    asc_stl_add_host_case("asc.execution.policy.b015" "asc/execution.policy/host.pass.cpp")
    asc_stl_add_host_case("asc.hierarchy.b016" "asc/hierarchy/host.pass.cpp")
    asc_stl_add_host_case("asc.warp.b017" "asc/warp/host.pass.cpp")
    asc_stl_add_host_case("asc.std.cstdlib.b014" "asc/std/cstdlib/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__memory.addressof" "asc/std/__memory/addressof/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__memory.voidify" "asc/std/__memory/voidify/host.pass.cpp")
    asc_stl_add_host_case("asc.algorithm.b023" "asc/algorithm/host.pass.cpp")
    asc_stl_add_host_case("asc.std.iterator.b024" "asc/std/iterator/host.pass.cpp")
    asc_stl_add_host_case("asc.buffer.b025" "asc/buffer/host.pass.cpp")
    asc_stl_add_host_case("asc.memory_pool.b025" "asc/memory_pool/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__functional.bind.b025" "asc/std/__functional/bind/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__functional.bind_front.b025" "asc/std/__functional/bind_front/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__numeric.accumulate.b025" "asc/std/__numeric/accumulate/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__compare.compare_fallback.b025" "asc/std/__compare/compare_fallback/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__compare.ordering" "asc/std/__compare/ordering/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cwchar.algorithms.b025" "asc/std/__cwchar/algorithms/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__bit.has_single_bit.b025" "asc/std/__bit/has_single_bit/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.monostate.b025" "asc/std/__utility/monostate/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.alignment_of.b025" "asc/std/__type_traits/alignment_of/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_char_like_type.b025" "asc/std/__type_traits/is_char_like_type/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.different_from" "asc/std/__concepts/different_from/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__exception.terminate.b025" "asc/std/__exception/terminate/host.pass.cpp")
    asc_stl_add_host_case("asc.__argument.wrappers.b025" "asc/__argument/wrappers/host.pass.cpp")
    asc_stl_add_host_case("asc.__bit.operations.b025" "asc/__bit/operations/host.pass.cpp")
    asc_stl_add_host_case("asc.__functional.metadata.b025" "asc/__functional/metadata/host.pass.cpp")
    asc_stl_add_host_case("asc.__numeric.checked.b025" "asc/__numeric/checked/host.pass.cpp")
    asc_stl_add_host_case("asc.__utility.static_for.b025" "asc/__utility/static_for/host.pass.cpp")
    asc_stl_add_host_case("asc.__version.product.b025" "asc/__version/product/host.pass.cpp")
    asc_stl_add_host_case("asc.cmath.b026" "asc/cmath/host.pass.cpp")
    asc_stl_add_host_case("asc.work_queue.b026" "asc/work_queue/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__numeric.reduce.b026" "asc/std/__numeric/reduce/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__numeric.saturating_add.b026" "asc/std/__numeric/saturating_add/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__charconv.from_chars.b026" "asc/std/__charconv/from_chars/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__bit.endian.b026" "asc/std/__bit/endian/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__bit.rotate.b026" "asc/std/__bit/rotate/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__bit.countl" "asc/std/__bit/countl/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__bit.reference.b026" "asc/std/__bit/reference/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_compound.b026" "asc/std/__type_traits/is_compound/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_scoped_enum.b026" "asc/std/__type_traits/is_scoped_enum/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.maybe_const.b026" "asc/std/__type_traits/maybe_const/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cctype.classification.b026" "asc/std/__cctype/classification/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cwctype.classification.b026" "asc/std/__cwctype/classification/host.pass.cpp")
    asc_stl_add_host_case("asc.__type_traits.extensions.b026" "asc/__type_traits/extensions/host.pass.cpp")
    asc_stl_add_host_case("asc.__tensor_copy.descriptor.b026" "asc/__tensor_copy/descriptor/host.pass.cpp")
    asc_stl_add_host_case("asc.std.ratio" "asc/std/ratio/host.pass.cpp")
    asc_stl_add_host_case("asc.std.linalg.w13_w14" "asc/std/linalg/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.conjunction" "asc/std/__type_traits/conjunction/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.disjunction" "asc/std/__type_traits/disjunction/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.fold" "asc/std/__type_traits/fold/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_abstract" "asc/std/__type_traits/is_abstract/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_base_of" "asc/std/__type_traits/is_base_of/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_class" "asc/std/__type_traits/is_class/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_complete" "asc/std/__type_traits/is_complete/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_const" "asc/std/__type_traits/is_const/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_core_convertible" "asc/std/__type_traits/is_core_convertible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_empty" "asc/std/__type_traits/is_empty/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_enum" "asc/std/__type_traits/is_enum/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_final" "asc/std/__type_traits/is_final/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_reference" "asc/std/__type_traits/is_reference/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_same" "asc/std/__type_traits/is_same/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_standard_layout" "asc/std/__type_traits/is_standard_layout/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivial" "asc/std/__type_traits/is_trivial/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivially_assignable" "asc/std/__type_traits/is_trivially_assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivially_constructible" "asc/std/__type_traits/is_trivially_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivially_copyable" "asc/std/__type_traits/is_trivially_copyable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_unbounded_array" "asc/std/__type_traits/is_unbounded_array/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_union" "asc/std/__type_traits/is_union/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_valid_expansion" "asc/std/__type_traits/is_valid_expansion/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_volatile" "asc/std/__type_traits/is_volatile/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.negation" "asc/std/__type_traits/negation/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.rank" "asc/std/__type_traits/rank/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.remove_cv" "asc/std/__type_traits/remove_cv/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.same_as" "asc/std/__concepts/same_as/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cstddef.byte" "asc/std/__cstddef/byte/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.array" "asc/std/__fwd/array/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.span" "asc/std/__fwd/span/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__tuple.tuple_indices" "asc/std/__tuple/tuple_indices/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__tuple.tuple_size" "asc/std/__tuple/tuple_size/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_callable" "asc/std/__type_traits/is_callable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_extended_floating_point" "asc/std/__type_traits/is_extended_floating_point/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_floating_point" "asc/std/__type_traits/is_floating_point/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_function" "asc/std/__type_traits/is_function/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_integral" "asc/std/__type_traits/is_integral/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_pointer" "asc/std/__type_traits/is_pointer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_referenceable" "asc/std/__type_traits/is_referenceable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_signed_integer" "asc/std/__type_traits/is_signed_integer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivially_default_constructible" "asc/std/__type_traits/is_trivially_default_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_unsigned_integer" "asc/std/__type_traits/is_unsigned_integer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.make_nbit_int" "asc/std/__type_traits/make_nbit_int/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.promote" "asc/std/__type_traits/promote/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.underlying_type" "asc/std/__type_traits/underlying_type/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.convert_to_integral" "asc/std/__utility/convert_to_integral/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.integer_sequence" "asc/std/__utility/integer_sequence/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.priority_tag" "asc/std/__utility/priority_tag/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.to_underlying" "asc/std/__utility/to_underlying/host.pass.cpp")
    asc_stl_add_host_case("asc.std.cstddef" "asc/std/cstddef/host.pass.cpp")
    asc_stl_add_host_case("asc.std.cstddef.deprecated_names" "asc/std/cstddef/deprecated_names.absence.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.char_traits" "asc/std/__fwd/char_traits/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.complex" "asc/std/__fwd/complex/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.fp" "asc/std/__fwd/fp/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.hash" "asc/std/__fwd/hash/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.iterator" "asc/std/__fwd/iterator/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.optional" "asc/std/__fwd/optional/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.optional.value_members" "asc/std/__fwd/optional/value_members.absence.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.pair" "asc/std/__fwd/pair/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.reference_wrapper" "asc/std/__fwd/reference_wrapper/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.tuple" "asc/std/__fwd/tuple/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.variant" "asc/std/__fwd/variant/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.add_lvalue_reference" "asc/std/__type_traits/add_lvalue_reference/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.add_rvalue_reference" "asc/std/__type_traits/add_rvalue_reference/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_arithmetic" "asc/std/__type_traits/is_arithmetic/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_integer" "asc/std/__type_traits/is_integer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_primary_template" "asc/std/__type_traits/is_primary_template/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.copy_cvref" "asc/std/__type_traits/copy_cvref/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_extended_arithmetic" "asc/std/__type_traits/is_extended_arithmetic/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_signed" "asc/std/__type_traits/is_signed/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivially_copy_assignable" "asc/std/__type_traits/is_trivially_copy_assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivially_copy_constructible" "asc/std/__type_traits/is_trivially_copy_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivially_move_assignable" "asc/std/__type_traits/is_trivially_move_assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivially_move_constructible" "asc/std/__type_traits/is_trivially_move_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_unsigned" "asc/std/__type_traits/is_unsigned/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.format" "asc/std/__floating_point/format/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.properties" "asc/std/__floating_point/properties/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.traits" "asc/std/__floating_point/traits/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.copy_cv" "asc/std/__type_traits/copy_cv/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.extent" "asc/std/__type_traits/extent/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_array" "asc/std/__type_traits/is_array/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_destructible" "asc/std/__type_traits/is_destructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_member_function_pointer" "asc/std/__type_traits/is_member_function_pointer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_member_object_pointer" "asc/std/__type_traits/is_member_object_pointer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_member_pointer" "asc/std/__type_traits/is_member_pointer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_null_pointer" "asc/std/__type_traits/is_null_pointer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_scalar" "asc/std/__type_traits/is_scalar/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_trivially_destructible" "asc/std/__type_traits/is_trivially_destructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_void" "asc/std/__type_traits/is_void/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.make_const_lvalue_ref" "asc/std/__type_traits/make_const_lvalue_ref/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.make_signed" "asc/std/__type_traits/make_signed/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.make_unsigned" "asc/std/__type_traits/make_unsigned/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.remove_all_extents" "asc/std/__type_traits/remove_all_extents/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.remove_cvref" "asc/std/__type_traits/remove_cvref/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.remove_extent" "asc/std/__type_traits/remove_extent/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.remove_reference" "asc/std/__type_traits/remove_reference/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.type_list" "asc/std/__type_traits/type_list/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.type_set" "asc/std/__type_traits/type_set/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.forward" "asc/std/__utility/forward/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.forward_like" "asc/std/__utility/forward_like/host.pass.cpp")
    asc_stl_add_host_case("asc.std.limits" "asc/std/limits/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.arithmetic" "asc/std/__concepts/arithmetic/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.boolean_testable" "asc/std/__concepts/boolean_testable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.class_or_enum" "asc/std/__concepts/class_or_enum/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.common_reference_with" "asc/std/__concepts/common_reference_with/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.constructible" "asc/std/__concepts/constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.convertible_to" "asc/std/__concepts/convertible_to/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.derived_from" "asc/std/__concepts/derived_from/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.destructible" "asc/std/__concepts/destructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.invocable" "asc/std/__concepts/invocable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.predicate" "asc/std/__concepts/predicate/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__functional.invoke" "asc/std/__functional/invoke/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__functional.unwrap_ref" "asc/std/__functional/unwrap_ref/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.incrementable_traits" "asc/std/__iterator/incrementable_traits/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.readable_traits" "asc/std/__iterator/readable_traits/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__limits.numeric_limits" "asc/std/__limits/numeric_limits/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__limits.numeric_limits_ext" "asc/std/__limits/numeric_limits_ext/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.common_reference" "asc/std/__type_traits/common_reference/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_comparable" "asc/std/__type_traits/is_comparable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_swappable" "asc/std/__type_traits/is_swappable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.delegate_constructors" "asc/std/__utility/delegate_constructors/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.exchange" "asc/std/__utility/exchange/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.move" "asc/std/__utility/move/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.swap" "asc/std/__utility/swap/host.pass.cpp")
    asc_stl_add_host_case("asc.memory_resource.b021" "asc/memory_resource/host.pass.cpp")
    asc_stl_add_host_case("asc.std.atomic.b022" "asc/std/atomic/host.pass.cpp")
    asc_stl_add_host_case("asc.std.ccomplex.b022" "asc/std/ccomplex/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.all_of.b022" "asc/std/__algorithm/all_of/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.rotate.b022" "asc/std/__algorithm/rotate/host.pass.cpp")

    asc_stl_add_host_case("asc.std.__type_traits.add_pointer" "asc/std/__type_traits/add_pointer/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_assignable" "asc/std/__type_traits/is_assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_assignable.fallback" "asc/std/__type_traits/is_assignable/fallback.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_constructible" "asc/std/__type_traits/is_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_constructible.fallback" "asc/std/__type_traits/is_constructible/fallback.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_convertible" "asc/std/__type_traits/is_convertible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_nothrow_destructible" "asc/std/__type_traits/is_nothrow_destructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_object" "asc/std/__type_traits/is_object/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.decay" "asc/std/__type_traits/decay/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_copy_assignable" "asc/std/__type_traits/is_copy_assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_copy_constructible" "asc/std/__type_traits/is_copy_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_default_constructible" "asc/std/__type_traits/is_default_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_move_assignable" "asc/std/__type_traits/is_move_assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_move_constructible" "asc/std/__type_traits/is_move_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_nothrow_assignable" "asc/std/__type_traits/is_nothrow_assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_nothrow_constructible" "asc/std/__type_traits/is_nothrow_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_nothrow_convertible" "asc/std/__type_traits/is_nothrow_convertible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__bit.bit_cast" "asc/std/__bit/bit_cast/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.common_type" "asc/std/__type_traits/common_type/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_implicitly_default_constructible" "asc/std/__type_traits/is_implicitly_default_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_nothrow_copy_assignable" "asc/std/__type_traits/is_nothrow_copy_assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_nothrow_copy_constructible" "asc/std/__type_traits/is_nothrow_copy_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_nothrow_default_constructible" "asc/std/__type_traits/is_nothrow_default_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_nothrow_move_assignable" "asc/std/__type_traits/is_nothrow_move_assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__type_traits.is_nothrow_move_constructible" "asc/std/__type_traits/is_nothrow_move_constructible/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.storage" "asc/std/__floating_point/storage/host.pass.cpp")
    asc_stl_add_host_case("asc.std.numbers" "asc/std/numbers/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.backend" "asc/std/__cmath/backend/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.neg" "asc/std/__cmath/neg/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.assignable" "asc/std/__concepts/assignable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.common_with" "asc/std/__concepts/common_with/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.copyable" "asc/std/__concepts/copyable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.equality_comparable" "asc/std/__concepts/equality_comparable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.movable" "asc/std/__concepts/movable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.regular" "asc/std/__concepts/regular/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.relation" "asc/std/__concepts/relation/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.semiregular" "asc/std/__concepts/semiregular/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.swappable" "asc/std/__concepts/swappable/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__concepts.totally_ordered" "asc/std/__concepts/totally_ordered/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.access" "asc/std/__iterator/access/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.data" "asc/std/__iterator/data/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.empty" "asc/std/__iterator/empty/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.iterator" "asc/std/__iterator/iterator/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.iterator_traits" "asc/std/__iterator/iterator_traits/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__memory.allocator_arg_t" "asc/std/__memory/allocator_arg_t/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__memory.pointer_traits" "asc/std/__memory/pointer_traits/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__memory.uses_allocator" "asc/std/__memory/uses_allocator/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__tuple.make_tuple_types" "asc/std/__tuple/make_tuple_types/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__tuple.sfinae_helpers" "asc/std/__tuple/sfinae_helpers/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__tuple.tuple_types" "asc/std/__tuple/tuple_types/host.pass.cpp")
    asc_stl_add_host_case("asc.std.concepts" "asc/std/concepts/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.comp" "asc/std/__algorithm/comp/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.sincos" "asc/std/__cmath/sincos/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.uabs" "asc/std/__cmath/uabs/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.common_iterator" "asc/std/__fwd/common_iterator/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.get" "asc/std/__fwd/get/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__fwd.subrange" "asc/std/__fwd/subrange/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.advance" "asc/std/__iterator/advance/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.bounded_iter" "asc/std/__iterator/bounded_iter/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.concepts" "asc/std/__iterator/concepts/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.iter_move" "asc/std/__iterator/iter_move/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.iter_swap" "asc/std/__iterator/iter_swap/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.projected" "asc/std/__iterator/projected/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.unreachable_sentinel" "asc/std/__iterator/unreachable_sentinel/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.wrap_iter" "asc/std/__iterator/wrap_iter/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__memory.construct_at" "asc/std/__memory/construct_at/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__ranges.access" "asc/std/__ranges/access/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__ranges.enable_borrowed_range" "asc/std/__ranges/enable_borrowed_range/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__ranges.size" "asc/std/__ranges/size/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__tuple.tuple_constraints" "asc/std/__tuple/tuple_constraints/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__tuple.tuple_like" "asc/std/__tuple/tuple_like/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__tuple.vector_types" "asc/std/__tuple/vector_types/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.auto_cast" "asc/std/__utility/auto_cast/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.pair" "asc/std/__utility/pair/host.pass.cpp")
    asc_stl_add_host_case("asc.__memory.views" "asc/__memory/views/host.pass.cpp")
    asc_stl_add_host_case("asc.memory" "asc/memory/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.comp_ref_type" "asc/std/__algorithm/comp_ref_type/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.find_first_of" "asc/std/__algorithm/find_first_of/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.iter_swap" "asc/std/__algorithm/iter_swap/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.ranges_find_if" "asc/std/__algorithm/ranges_find_if/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.ranges_find_if_not" "asc/std/__algorithm/ranges_find_if_not/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.reverse_iterator" "asc/std/__iterator/reverse_iterator/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.fma" "asc/std/__cmath/fma/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.gamma" "asc/std/__cmath/gamma/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.hyperbolic_functions" "asc/std/__cmath/hyperbolic_functions/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.inverse_hyperbolic_functions" "asc/std/__cmath/inverse_hyperbolic_functions/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.inverse_trigonometric_functions" "asc/std/__cmath/inverse_trigonometric_functions/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.remainder" "asc/std/__cmath/remainder/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.roots" "asc/std/__cmath/roots/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.rounding_functions" "asc/std/__cmath/rounding_functions/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.trigonometric_functions" "asc/std/__cmath/trigonometric_functions/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.arithmetic" "asc/std/__floating_point/arithmetic/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.cast" "asc/std/__floating_point/cast/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.constants" "asc/std/__floating_point/constants/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.conversion_rank_order" "asc/std/__floating_point/conversion_rank_order/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.decompose" "asc/std/__floating_point/decompose/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.mask" "asc/std/__floating_point/mask/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.native_type" "asc/std/__floating_point/native_type/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.overflow_handler" "asc/std/__floating_point/overflow_handler/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__iterator.size" "asc/std/__iterator/size/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__ranges.enable_view" "asc/std/__ranges/enable_view/host.pass.cpp")
    asc_stl_add_host_case("asc.__runtime.devices" "asc/__runtime/devices/host.pass.cpp")
    asc_stl_add_host_case("asc.devices" "asc/devices/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.ranges_iterator_concept" "asc/std/__algorithm/ranges_iterator_concept/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.abs" "asc/std/__cmath/abs/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.copysign" "asc/std/__cmath/copysign/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.error_functions" "asc/std/__cmath/error_functions/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.exponential_functions" "asc/std/__cmath/exponential_functions/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.fdim" "asc/std/__cmath/fdim/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.fpclassify" "asc/std/__cmath/fpclassify/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.hypot" "asc/std/__cmath/hypot/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.isfinite" "asc/std/__cmath/isfinite/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.isinf" "asc/std/__cmath/isinf/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.isnan" "asc/std/__cmath/isnan/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.isnormal" "asc/std/__cmath/isnormal/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.logarithms" "asc/std/__cmath/logarithms/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.min_max" "asc/std/__cmath/min_max/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.modulo" "asc/std/__cmath/modulo/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__cmath.signbit" "asc/std/__cmath/signbit/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__complex.complex" "asc/std/__complex/complex/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__complex.vector_support" "asc/std/__complex/vector_support/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.common_type" "asc/std/__floating_point/common_type/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__floating_point.fp" "asc/std/__floating_point/fp/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__utility.in_place" "asc/std/__utility/in_place/host.pass.cpp")
    asc_stl_add_host_case("asc.std.cmath" "asc/std/cmath/host.pass.cpp")
    asc_stl_add_host_case("asc.std.cmath.acos_precision" "asc/std/cmath/acos_precision.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.count_if.b020" "asc/std/__algorithm/count_if/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.minmax_element.b020" "asc/std/__algorithm/minmax_element/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__algorithm.lower_bound.b020" "asc/std/__algorithm/lower_bound/host.pass.cpp")
    asc_stl_add_host_case("asc.std.__functional.bind_back.b020" "asc/std/__functional/bind_back/host.pass.cpp")
    asc_stl_add_host_case("asc.std.optional.b020" "asc/std/optional/host.pass.cpp")
    asc_stl_add_host_case("asc.std.optional.excluded_members" "asc/std/optional/excluded_members.absence.pass.cpp")
    asc_stl_add_host_case("asc.std.__ranges.movable_box.b020" "asc/std/__ranges/movable_box/host.pass.cpp")
    asc_stl_add_host_case("asc.std.bitset.b027" "asc/std/bitset/host.pass.cpp")
    asc_stl_add_host_case("asc.std.vector.aliasing" "asc/std/vector/aliasing.pass.cpp")
    asc_stl_add_host_case("asc.std.list-map.b028" "asc/std/list/host.pass.cpp")
    asc_stl_add_host_case("asc.tensor-copy-execution.b029" "asc/tensor_copy/host.pass.cpp")
    asc_stl_add_host_case("asc.std.functional-semaphore.b030" "asc/std/semaphore/host.pass.cpp")
    asc_stl_add_host_case("asc.std.latch-shared-lock.b031" "asc/std/latch/host.pass.cpp")
    asc_stl_add_host_case("asc.std.deque-queue.b032" "asc/std/deque/host.pass.cpp")
    asc_stl_add_host_case("asc.std.barrier-mutex.b036" "asc/std/barrier/host.pass.cpp")
    asc_stl_add_host_case("asc.iterator.b038" "asc/iterator/host.pass.cpp")
    asc_stl_add_host_case("asc.std.chrono.b038" "asc/std/chrono/host.pass.cpp")
    asc_stl_add_host_case("asc.std.memory-align.b038" "asc/std/__memory/align/host.pass.cpp")
    asc_stl_add_host_case("asc.std.memory.b039" "asc/std/memory/host.pass.cpp")
    asc_stl_add_host_case("asc.std.variant.b039" "asc/std/variant/host.pass.cpp")
    asc_stl_add_host_case("asc.std.mdspan.b040" "asc/std/mdspan/host.pass.cpp")
    asc_stl_add_host_case("asc.mdspan.b040" "asc/mdspan/host.pass.cpp")
    asc_stl_add_host_case("asc.std.algorithm.w11" "asc/std/algorithm/host.pass.cpp")
    asc_stl_add_host_case("asc.random-expected.w11" "asc/random/host.pass.cpp")
    asc_stl_add_host_case("asc.std.format-numeric.w11" "asc/std/format/host.pass.cpp")
    asc_stl_add_host_case("asc.std.ranges.w12" "asc/std/ranges/host.pass.cpp")
    asc_stl_add_host_case("asc.argument-functional.w12" "asc/argument/host.pass.cpp")
    asc_stl_add_host_case("asc.functional.properties" "asc/functional/host.pass.cpp")
    asc_stl_add_host_case("asc.std.array.shared" "asc/std/array/host.pass.cpp")
    asc_stl_add_host_case("asc.collectives.shared" "asc/__collectives/block/host.pass.cpp")
    asc_stl_add_host_case("asc.algorithm.frontend.shared" "asc/__algorithm/frontend/host.pass.cpp")
    asc_stl_add_host_case("asc.parallel.find.shared" "asc/__parallel/find/host.pass.cpp")
    asc_stl_add_host_case("asc.parallel.for.shared" "asc/__parallel/for/host.pass.cpp")
    asc_stl_add_host_case("asc.parallel.partition.shared" "asc/__parallel/partition/host.pass.cpp")
    asc_stl_add_host_case("asc.parallel.reduce.shared" "asc/__parallel/reduce/host.pass.cpp")
    asc_stl_add_host_case("asc.parallel.transform.shared" "asc/__parallel/transform/host.pass.cpp")
    asc_stl_add_host_case("asc.execution.shared" "asc/execution/host.pass.cpp")
    asc_stl_add_host_case("asc.launch.shared" "asc/launch/host.pass.cpp")
    asc_stl_add_host_case("asc.std.move_iterator.shared" "asc/std/__iterator/move_iterator/host.pass.cpp")
    asc_stl_add_host_case("asc.std.concepts.backports" "asc/std/concepts/cxx17_backports.pass.cpp")
    asc_stl_add_host_case("asc.std.concepts.backports-iterator-first" "asc/std/concepts/cxx17_backports_iterator_first.pass.cpp")
    asc_stl_add_host_case("asc.std.span.backports" "asc/std/span/cxx17_backports.pass.cpp")
    asc_stl_add_host_case("asc.std.ranges.backports" "asc/std/ranges/cxx17_backports.pass.cpp")
    asc_stl_add_host_case("asc.std.ranges.access-constraints" "asc/std/ranges/access_constraints.pass.cpp")
    asc_stl_add_host_case("asc.std.ranges.repeat-piecewise-assertions" "asc/std/ranges/repeat_piecewise_assertions.pass.cpp")
    asc_stl_add_host_case("asc.std.version.legacy" "asc/std/version/legacy_feature_macros.pass.cpp")
    asc_stl_add_host_case("asc.std.version.host-coexistence" "asc/std/version/host_coexistence.pass.cpp")
    asc_stl_add_host_case("asc.std.format.portable-renderer" "asc/std/format/portable_renderer.pass.cpp")
    get_property(asc_stl_registered_host_sources GLOBAL PROPERTY ASC_STL_REGISTERED_HOST_CASE_SOURCES)
    string(JOIN "\n" asc_stl_registered_host_sources_text ${asc_stl_registered_host_sources})
    set(asc_stl_registered_host_sources_file "${CMAKE_CURRENT_BINARY_DIR}/registered-host-cases.txt")
    file(WRITE "${asc_stl_registered_host_sources_file}" "${asc_stl_registered_host_sources_text}\n")
    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/validate_host_registration.py
                --manifest ${ASC_STL_MANIFEST}
                --registered ${asc_stl_registered_host_sources_file}
                --test-root ${ASC_STL_TEST_ROOT}
        RESULT_VARIABLE asc_stl_host_registration_result
        OUTPUT_VARIABLE asc_stl_host_registration_output
        ERROR_VARIABLE asc_stl_host_registration_error)
    if(NOT asc_stl_host_registration_result EQUAL 0)
        message(FATAL_ERROR
            "Host semantic registration is incomplete:\n${asc_stl_host_registration_output}${asc_stl_host_registration_error}")
    endif()
    foreach(standard IN ITEMS 17 20)
        add_executable(
            asc_stl_host_cassert_ndebug_cxx${standard}
            ${ASC_STL_CASES_ROOT}/asc/std/cassert/ndebug.pass.cpp)
        target_link_libraries(asc_stl_host_cassert_ndebug_cxx${standard} PRIVATE asc_stl::asc_stl)
        set_target_properties(
            asc_stl_host_cassert_ndebug_cxx${standard}
            PROPERTIES CXX_STANDARD "${standard}" CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
        target_compile_definitions(asc_stl_host_cassert_ndebug_cxx${standard} PRIVATE NDEBUG)
        target_compile_options(
            asc_stl_host_cassert_ndebug_cxx${standard} PRIVATE -Wall -Wextra -Werror -pedantic)
        add_test(
            NAME semantic.host.cxx${standard}.asc.std.cassert.ndebug
            COMMAND asc_stl_host_cassert_ndebug_cxx${standard})
        set_tests_properties(
            semantic.host.cxx${standard}.asc.std.cassert.ndebug
            PROPERTIES LABELS "semantic-host;cxx${standard};negative-boundary;affected-regression;nightly")

        add_executable(
            asc_stl_host_cassert_failure_cxx${standard}
            ${ASC_STL_CASES_ROOT}/asc/std/cassert/failure.fail.cpp)
        target_link_libraries(asc_stl_host_cassert_failure_cxx${standard} PRIVATE asc_stl::asc_stl)
        set_target_properties(
            asc_stl_host_cassert_failure_cxx${standard}
            PROPERTIES CXX_STANDARD "${standard}" CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
        target_compile_options(
            asc_stl_host_cassert_failure_cxx${standard} PRIVATE -Wall -Wextra -Werror -pedantic -UNDEBUG)
        add_test(
            NAME semantic.host.cxx${standard}.asc.std.cassert.failure
            COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/run_assert_failure.py
                    $<TARGET_FILE:asc_stl_host_cassert_failure_cxx${standard}>)
        set_tests_properties(
            semantic.host.cxx${standard}.asc.std.cassert.failure
            PROPERTIES LABELS "semantic-host;cxx${standard};negative-boundary;affected-regression;nightly")
        add_executable(
            asc_stl_host_repeat_piecewise_negative_cxx${standard}
            ${ASC_STL_CASES_ROOT}/asc/std/ranges/repeat_piecewise_negative.assert.cpp)
        target_link_libraries(asc_stl_host_repeat_piecewise_negative_cxx${standard} PRIVATE asc_stl::asc_stl)
        set_target_properties(
            asc_stl_host_repeat_piecewise_negative_cxx${standard}
            PROPERTIES CXX_STANDARD "${standard}" CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
        target_compile_options(
            asc_stl_host_repeat_piecewise_negative_cxx${standard} PRIVATE -Wall -Wextra -Werror -pedantic)
        add_test(
            NAME semantic.host.cxx${standard}.asc.std.ranges.repeat-piecewise-negative
            COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/run_trap_failure.py
                    $<TARGET_FILE:asc_stl_host_repeat_piecewise_negative_cxx${standard}>)
        set_tests_properties(
            semantic.host.cxx${standard}.asc.std.ranges.repeat-piecewise-negative
            PROPERTIES LABELS "semantic-host;cxx${standard};negative-boundary;affected-regression;nightly" TIMEOUT 15)
    endforeach()
endif()

if(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS)
    if(NOT ASC_STL_CANN_PACKAGE_PATH OR NOT IS_DIRECTORY "${ASC_STL_CANN_PACKAGE_PATH}")
        message(FATAL_ERROR "ASC_STL_CANN_PACKAGE_PATH must name an installed CANN package")
    endif()
    set(
        asc_stl_device_compile_command
        ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/run_device_compile.py
        --manifest ${ASC_STL_MANIFEST}
        --include-root ${ASC_STL_INCLUDE_ROOT}
        --test-root ${ASC_STL_TEST_ROOT}
        --npu-arch ${ASC_STL_NPU_ARCH}
        --jobs ${ASC_STL_DEVICE_COMPILE_JOBS}
        --task-timeout-seconds ${ASC_STL_DEVICE_TASK_TIMEOUT_SECONDS}
        --report ${ASC_STL_DEVICE_REPORT})
    foreach(standard IN ITEMS 17 20)
        foreach(mode IN ITEMS simd simt)
            set(doc_test "docs.device.cxx${standard}.${mode}")
            add_test(NAME "${doc_test}"
                COMMAND ${Python3_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/check_api_docs.py
                    --examples --standard ${standard} --mode ${mode} --compiler bisheng
                    --npu-arch ${ASC_STL_NPU_ARCH} --require-all --jobs ${ASC_STL_DEVICE_COMPILE_JOBS}
                    --report ${CMAKE_CURRENT_BINARY_DIR}/docs-device-cxx${standard}-${mode}.json)
            set_tests_properties("${doc_test}" PROPERTIES
                LABELS "docs-examples;device-compile;nightly" RUN_SERIAL TRUE TIMEOUT 3600 SKIP_RETURN_CODE 77)
        endforeach()
    endforeach()
    if(ASC_STL_DEVICE_CHANGED_TARGETS_FILE)
        list(APPEND asc_stl_device_compile_command --changed-targets-file ${ASC_STL_DEVICE_CHANGED_TARGETS_FILE})
    endif()
    add_test(NAME gate.device.compile COMMAND ${asc_stl_device_compile_command})
    set_tests_properties(
        gate.device.compile
        PROPERTIES LABELS "header-device;device-compile;affected-regression;nightly" RUN_SERIAL TRUE TIMEOUT 14400)
endif()

if(ASC_STL_ENABLE_CANNSIM_TESTS)
    if(NOT ASC_STL_CANNSIM_EXECUTABLE OR NOT EXISTS "${ASC_STL_CANNSIM_EXECUTABLE}")
        message(FATAL_ERROR "ASC_STL_CANNSIM_EXECUTABLE must name the installed cannsim executable")
    endif()
    set(cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/source_location/runtime/cannsim")
    set(cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/source-location-cannsim")
    set(foundation_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/__cstring/memcpy/runtime/cannsim")
    set(foundation_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/foundation-cannsim")
    set(atomic_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/atomic/runtime/cannsim")
    set(atomic_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/atomic-cannsim")
    set(b014_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/cstdlib/runtime/cannsim")
    set(b014_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b014-cannsim")
    set(b015_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/__complex/logarithms/runtime/cannsim")
    set(b015_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b015-cannsim")
    set(b016_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/hierarchy/runtime/cannsim")
    set(b016_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b016-cannsim")
    set(b017_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/warp/runtime/cannsim")
    set(b017_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b017-cannsim")
    set(b018_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/__collectives/block/runtime/cannsim")
    set(b018_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b018-cannsim")
    set(b019_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/__algorithm/frontend/runtime/cannsim")
    set(b019_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b019-cannsim")
    set(b021_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/ctime/runtime/cannsim")
    set(b021_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b021-cannsim")
    set(b022_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/atomic/runtime/cannsim")
    set(b022_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b022-cannsim")
    set(b023_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/algorithm/runtime/cannsim")
    set(b023_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b023-cannsim")
    set(b024_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/iterator/runtime/cannsim")
    set(b024_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b024-cannsim")
    set(b026_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/work_queue/runtime/cannsim")
    set(b026_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b026-cannsim")
    set(b027_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/bitset/runtime/cannsim")
    set(b027_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b027-cannsim")
    set(b028_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/list/runtime/cannsim")
    set(b028_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/b028-cannsim")
    set(w08_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/tensor_copy/runtime/cannsim")
    set(w08_simd_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/w08-simd-cannsim")
    set(w08_simt_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/w08-simt-cannsim")
    set(w13_w14_cannsim_case_root "${ASC_STL_CASES_ROOT}/asc/std/linalg/runtime/cannsim")
    set(w13_w14_simd_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/w13-w14-simd-cannsim")
    set(w13_w14_simt_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/w13-w14-simt-cannsim")
    add_custom_target(
        asc_stl_cannsim_tests
        COMMAND
            ${CMAKE_COMMAND} -S ${cannsim_case_root} -B ${cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${cannsim_build_root} --target asc_stl_source_location_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${foundation_cannsim_case_root} -B ${foundation_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND
            ${CMAKE_COMMAND} --build ${foundation_cannsim_build_root}
            --target asc_stl_foundation_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${atomic_cannsim_case_root} -B ${atomic_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${atomic_cannsim_build_root} --target asc_stl_atomic_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b014_cannsim_case_root} -B ${b014_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b014_cannsim_build_root} --target asc_stl_b014_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b015_cannsim_case_root} -B ${b015_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b015_cannsim_build_root} --target asc_stl_b015_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b016_cannsim_case_root} -B ${b016_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b016_cannsim_build_root} --target asc_stl_b016_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b017_cannsim_case_root} -B ${b017_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b017_cannsim_build_root} --target asc_stl_b017_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b018_cannsim_case_root} -B ${b018_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b018_cannsim_build_root} --target asc_stl_b018_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b019_cannsim_case_root} -B ${b019_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b019_cannsim_build_root} --target asc_stl_b019_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b021_cannsim_case_root} -B ${b021_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b021_cannsim_build_root} --target asc_stl_b021_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b022_cannsim_case_root} -B ${b022_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b022_cannsim_build_root} --target asc_stl_b022_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b023_cannsim_case_root} -B ${b023_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b023_cannsim_build_root} --target asc_stl_b023_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b024_cannsim_case_root} -B ${b024_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b024_cannsim_build_root} --target asc_stl_b024_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b026_cannsim_case_root} -B ${b026_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b026_cannsim_build_root} --target asc_stl_b026_work_queue_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b027_cannsim_case_root} -B ${b027_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b027_cannsim_build_root} --target asc_stl_b027_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${b028_cannsim_case_root} -B ${b028_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${b028_cannsim_build_root} --target asc_stl_b028_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${w08_cannsim_case_root} -B ${w08_simd_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DASC_STL_W08_MODE=simd
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${w08_simd_cannsim_build_root} --target asc_stl_w08_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${w08_cannsim_case_root} -B ${w08_simt_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DASC_STL_W08_MODE=simt
            -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build ${w08_simt_cannsim_build_root} --target asc_stl_w08_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${w13_w14_cannsim_case_root} -B ${w13_w14_simd_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DASC_STL_W13_W14_MODE=simd
            -DCMAKE_BUILD_TYPE=Release
        COMMAND
            ${CMAKE_COMMAND} --build ${w13_w14_simd_cannsim_build_root}
            --target asc_stl_w13_w14_cannsim -j2
        COMMAND
            ${CMAKE_COMMAND} -S ${w13_w14_cannsim_case_root} -B ${w13_w14_simt_cannsim_build_root}
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DASC_STL_W13_W14_MODE=simt
            -DCMAKE_BUILD_TYPE=Release
        COMMAND
            ${CMAKE_COMMAND} --build ${w13_w14_simt_cannsim_build_root}
            --target asc_stl_w13_w14_cannsim -j2
        VERBATIM)

    set(cannsim_runner ${ASC_STL_TEST_ROOT}/scripts/run_cannsim_test.sh)
    set(cannsim_application ${cannsim_build_root}/asc_stl_source_location_cannsim)
    set(cannsim_library_dir ${cannsim_build_root}/lib)
    set(foundation_cannsim_application ${foundation_cannsim_build_root}/asc_stl_foundation_cannsim)
    set(foundation_cannsim_library_dir ${foundation_cannsim_build_root}/lib)
    set(atomic_cannsim_application ${atomic_cannsim_build_root}/asc_stl_atomic_cannsim)
    # The pure ASC D-SIMT executable links its kernel directly and therefore
    # has no generated shared-library subdirectory. The runner still needs an
    # existing directory for LD_LIBRARY_PATH, so bind the build root itself.
    set(atomic_cannsim_library_dir ${atomic_cannsim_build_root})
    set(b014_cannsim_application ${b014_cannsim_build_root}/asc_stl_b014_cannsim)
    set(b014_cannsim_library_dir ${b014_cannsim_build_root})
    set(b015_cannsim_application ${b015_cannsim_build_root}/asc_stl_b015_cannsim)
    set(b015_cannsim_library_dir ${b015_cannsim_build_root})
    set(b016_cannsim_application ${b016_cannsim_build_root}/asc_stl_b016_cannsim)
    set(b016_cannsim_library_dir ${b016_cannsim_build_root})
    set(b017_cannsim_application ${b017_cannsim_build_root}/asc_stl_b017_cannsim)
    set(b017_cannsim_library_dir ${b017_cannsim_build_root})
    set(b018_cannsim_application ${b018_cannsim_build_root}/asc_stl_b018_cannsim)
    set(b018_cannsim_library_dir ${b018_cannsim_build_root})
    set(b019_cannsim_application ${b019_cannsim_build_root}/asc_stl_b019_cannsim)
    set(b019_cannsim_library_dir ${b019_cannsim_build_root})
    set(b021_cannsim_application ${b021_cannsim_build_root}/asc_stl_b021_cannsim)
    set(b021_cannsim_library_dir ${b021_cannsim_build_root})
    set(b022_cannsim_application ${b022_cannsim_build_root}/asc_stl_b022_cannsim)
    set(b022_cannsim_library_dir ${b022_cannsim_build_root})
    set(b023_cannsim_application ${b023_cannsim_build_root}/asc_stl_b023_cannsim)
    set(b023_cannsim_library_dir ${b023_cannsim_build_root})
    set(b024_cannsim_application ${b024_cannsim_build_root}/asc_stl_b024_cannsim)
    set(b024_cannsim_library_dir ${b024_cannsim_build_root})
    set(b026_cannsim_application ${b026_cannsim_build_root}/asc_stl_b026_work_queue_cannsim)
    set(b026_cannsim_library_dir ${b026_cannsim_build_root})
    set(b027_cannsim_application ${b027_cannsim_build_root}/asc_stl_b027_cannsim)
    set(b027_cannsim_library_dir ${b027_cannsim_build_root})
    set(b028_cannsim_application ${b028_cannsim_build_root}/asc_stl_b028_cannsim)
    set(b028_cannsim_library_dir ${b028_cannsim_build_root})
    set(w08_simd_cannsim_application ${w08_simd_cannsim_build_root}/asc_stl_w08_cannsim)
    set(w08_simt_cannsim_application ${w08_simt_cannsim_build_root}/asc_stl_w08_cannsim)
    set(w13_w14_simd_cannsim_application ${w13_w14_simd_cannsim_build_root}/asc_stl_w13_w14_cannsim)
    set(w13_w14_simt_cannsim_application ${w13_w14_simt_cannsim_build_root}/asc_stl_w13_w14_cannsim)
    add_test(
        NAME cannsim.smoke
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/smoke
                ${cannsim_library_dir} ASC_STL_CANNSIM_ASC_STD_SOURCE_LOCATION_PASS)
    set_tests_properties(
        cannsim.smoke
        PROPERTIES LABELS "cannsim-smoke;affected-regression;nightly"
                   FIXTURES_SETUP asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.std.source_location
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/source-location
                ${cannsim_library_dir} ASC_STL_CANNSIM_ASC_STD_SOURCE_LOCATION_PASS)
    set_tests_properties(
        semantic.cannsim.asc.std.source_location
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.std.foundation-runtime
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${foundation_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/foundation
                ${foundation_cannsim_library_dir} ASC_STL_CANNSIM_FOUNDATION_PASS)
    set_tests_properties(
        semantic.cannsim.asc.std.foundation-runtime
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.atomic
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${atomic_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/atomic
                ${atomic_cannsim_library_dir} ASC_STL_CANNSIM_ATOMIC_PASS)
    set_tests_properties(
        semantic.cannsim.asc.atomic
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.std.b014
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b014_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b014
                ${b014_cannsim_library_dir} ASC_STL_CANNSIM_B014_PASS)
    set_tests_properties(
        semantic.cannsim.asc.std.b014
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.std.b015
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b015_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b015
                ${b015_cannsim_library_dir} ASC_STL_CANNSIM_B015_PASS)
    set_tests_properties(
        semantic.cannsim.asc.std.b015
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.hierarchy.b016
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b016_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b016
                ${b016_cannsim_library_dir} ASC_STL_CANNSIM_B016_PASS)
    set_tests_properties(
        semantic.cannsim.asc.hierarchy.b016
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.warp.b017
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b017_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b017
                ${b017_cannsim_library_dir} ASC_STL_CANNSIM_B017_PASS)
    set_tests_properties(
        semantic.cannsim.asc.warp.b017
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.warp.b017.failure-injection
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b017_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b017-failure-injection
                ${b017_cannsim_library_dir} ASC_STL_CANNSIM_B017_PASS)
    set_tests_properties(
        semantic.cannsim.asc.warp.b017.failure-injection
        PROPERTIES LABELS "cannsim-runtime;negative-boundary;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE WILL_FAIL TRUE
                   ENVIRONMENT "ASC_STL_WARP_INJECT_FAILURE=1")
    add_test(
        NAME semantic.cannsim.asc.collectives.b018
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b018_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b018
                ${b018_cannsim_library_dir} ASC_STL_CANNSIM_B018_PASS)
    set_tests_properties(
        semantic.cannsim.asc.collectives.b018
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.algorithm.b019
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b019_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b019
                ${b019_cannsim_library_dir} ASC_STL_CANNSIM_B019_PASS)
    set_tests_properties(
        semantic.cannsim.asc.algorithm.b019
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.std.ctime.b021
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b021_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b021
                ${b021_cannsim_library_dir} ASC_STL_CANNSIM_B021_PASS)
    set_tests_properties(
        semantic.cannsim.asc.std.ctime.b021
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.std.atomic.b022
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b022_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b022
                ${b022_cannsim_library_dir} ASC_STL_CANNSIM_B022_PASS)
    set_tests_properties(
        semantic.cannsim.asc.std.atomic.b022
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.algorithm.b023
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b023_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b023
                ${b023_cannsim_library_dir} ASC_STL_CANNSIM_B023_PASS)
    set_tests_properties(
        semantic.cannsim.asc.algorithm.b023
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.std.iterator.b024
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b024_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b024
                ${b024_cannsim_library_dir} ASC_STL_CANNSIM_B024_PASS)
    set_tests_properties(
        semantic.cannsim.asc.std.iterator.b024
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.work_queue.b026
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b026_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b026
                ${b026_cannsim_library_dir} ASC_STL_CANNSIM_B026_PASS)
    set_tests_properties(
        semantic.cannsim.asc.work_queue.b026
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.std.bitset.b027
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b027_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b027
                ${b027_cannsim_library_dir} ASC_STL_B027_CANNSIM_PASS)
    set_tests_properties(
        semantic.cannsim.asc.std.bitset.b027
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.asc.std.list-map.b028
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${b028_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/b028
                ${b028_cannsim_library_dir} ASC_STL_B028_CANNSIM_PASS)
    set_tests_properties(
        semantic.cannsim.asc.std.list-map.b028
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.w08.simd
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${w08_simd_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/w08-simd
                ${w08_simd_cannsim_build_root} ASC_STL_W08_CANNSIM_PASS)
    set_tests_properties(
        semantic.cannsim.w08.simd
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.w08.simt
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${w08_simt_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/w08-simt
                ${w08_simt_cannsim_build_root} ASC_STL_W08_CANNSIM_PASS)
    set_tests_properties(
        semantic.cannsim.w08.simt
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.w13_w14.simd
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${w13_w14_simd_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/w13-w14-simd
                ${w13_w14_simd_cannsim_build_root} ASC_STL_W13_W14_CANNSIM_PASS)
    set_tests_properties(
        semantic.cannsim.w13_w14.simd
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    add_test(
        NAME semantic.cannsim.w13_w14.simt
        COMMAND ${cannsim_runner} ${ASC_STL_CANNSIM_EXECUTABLE} ${w13_w14_simt_cannsim_application}
                ${ASC_STL_CANNSIM_SOC} ${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/w13-w14-simt
                ${w13_w14_simt_cannsim_build_root} ASC_STL_W13_W14_CANNSIM_PASS)
    set_tests_properties(
        semantic.cannsim.w13_w14.simt
        PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly"
                   FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)

    if(NOT ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS MATCHES "^[1-9][0-9]*$")
        message(FATAL_ERROR "ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS must be a positive integer")
    endif()
    # Bound a stalled model independently of the complete dual-language gate.
    # Timeout is a failed case; it never changes applicability or golden checks.
    get_property(asc_stl_registered_tests DIRECTORY PROPERTY TESTS)
    foreach(asc_stl_test_name IN LISTS asc_stl_registered_tests)
        if(asc_stl_test_name MATCHES "^semantic[.]cannsim[.]")
            set_tests_properties(${asc_stl_test_name}
                PROPERTIES TIMEOUT ${ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS})
        endif()
    endforeach()
endif()
