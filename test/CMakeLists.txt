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

find_package(Python3 REQUIRED COMPONENTS Interpreter)

option(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS "Enable Device compile tests" OFF)
option(ASC_STL_ENABLE_CANNSIM_TESTS "Enable cannsim runtime tests" OFF)
set(ASC_STL_TEST_CXX_STANDARD "17" CACHE STRING "C++ standard used by ASC-STL tests")
set(ASC_STL_CANN_PACKAGE_PATH "" CACHE PATH "Path to the installed CANN package")
set(ASC_STL_TARGET_SOC "Ascend950PR_9599" CACHE STRING "Target SoC used by Device tests")
set(ASC_STL_NPU_ARCH "dav-3510" CACHE STRING "NPU architecture used by Device tests")
set(ASC_STL_CANNSIM_EXECUTABLE "" CACHE FILEPATH "Path to the cannsim executable")
set(ASC_STL_CANNSIM_SOC "Ascend950" CACHE STRING "SoC model used by cannsim")
set_property(CACHE ASC_STL_TEST_CXX_STANDARD PROPERTY STRINGS 17 20)

if(NOT ASC_STL_TEST_CXX_STANDARD MATCHES "^(17|20)$")
    message(FATAL_ERROR "ASC_STL_TEST_CXX_STANDARD must be 17 or 20")
endif()

set(ASC_STL_TEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(ASC_STL_MANIFEST "${ASC_STL_TEST_ROOT}/metadata/headers.json")
set(ASC_STL_INCLUDE_ROOT "${PROJECT_SOURCE_DIR}/include")
set(ASC_STL_CASES_ROOT "${ASC_STL_TEST_ROOT}/cases")

add_test(
    NAME gate.metadata
    COMMAND
        "${Python3_EXECUTABLE}"
        "${ASC_STL_TEST_ROOT}/scripts/validate_metadata.py"
        --manifest "${ASC_STL_MANIFEST}"
        --include-root "${ASC_STL_INCLUDE_ROOT}"
        --test-root "${ASC_STL_TEST_ROOT}"
)
set_tests_properties(gate.metadata PROPERTIES LABELS "metadata;static-rules;affected-regression")

add_test(
    NAME gate.product-contract
    COMMAND
        "${Python3_EXECUTABLE}"
        "${ASC_STL_TEST_ROOT}/scripts/validate_product_contract.py"
        "${PROJECT_SOURCE_DIR}"
)
set_tests_properties(gate.product-contract PROPERTIES LABELS "metadata;static-rules;affected-regression")

add_test(
    NAME gate.dependencies
    COMMAND
        "${Python3_EXECUTABLE}"
        "${ASC_STL_TEST_ROOT}/scripts/validate_observed_dependencies.py"
        --headers "${ASC_STL_MANIFEST}"
        --include "${ASC_STL_INCLUDE_ROOT}"
)
set_tests_properties(gate.dependencies PROPERTIES LABELS "metadata;static-rules;affected-regression")

add_test(
    NAME header.host.all
    COMMAND
        "${Python3_EXECUTABLE}"
        "${ASC_STL_TEST_ROOT}/scripts/run_header_self_contained.py"
        --metadata "${ASC_STL_MANIFEST}"
        --include "${ASC_STL_INCLUDE_ROOT}"
        --compiler "${CMAKE_CXX_COMPILER}"
)
set_tests_properties(header.host.all PROPERTIES LABELS "header-host;affected-regression")

add_test(
    NAME integration.installed-consumer
    COMMAND
        "${Python3_EXECUTABLE}"
        "${ASC_STL_TEST_ROOT}/scripts/run_installed_consumer.py"
        --source "${PROJECT_SOURCE_DIR}"
        --consumer "${ASC_STL_TEST_ROOT}/consumer"
        --metadata "${ASC_STL_MANIFEST}"
        --compiler "${CMAKE_CXX_COMPILER}"
)
set_tests_properties(
    integration.installed-consumer
    PROPERTIES LABELS "installed-tree;consumer;semantic-host;affected-regression"
)

add_test(
    NAME boundary.host
    COMMAND
        "${Python3_EXECUTABLE}"
        "${ASC_STL_TEST_ROOT}/scripts/validate_negative_boundaries.py"
        --include "${ASC_STL_INCLUDE_ROOT}"
        --test-root "${ASC_STL_TEST_ROOT}"
        --compiler "${CMAKE_CXX_COMPILER}"
)
set_tests_properties(boundary.host PROPERTIES LABELS "negative-boundary;static-rules;affected-regression")

function(asc_stl_add_host_case case_id source)
    set(case_standards 17 20)
    if(case_id MATCHES "^asc\\.std\\.__concepts\\.")
        set(case_standards 20)
    endif()
    foreach(standard IN LISTS case_standards)
        string(MAKE_C_IDENTIFIER "${case_id}_cxx${standard}" target_suffix)
        set(target "asc_stl_host_${target_suffix}")
        add_executable("${target}" "${ASC_STL_CASES_ROOT}/${source}")
        target_link_libraries("${target}" PRIVATE asc_stl::asc_stl)
        set_target_properties(
            "${target}"
            PROPERTIES CXX_STANDARD "${standard}" CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
        )
        target_include_directories("${target}" PRIVATE "${ASC_STL_TEST_ROOT}")
        target_compile_options("${target}" PRIVATE -Wall -Wextra -Werror -pedantic -UNDEBUG)
        add_test(NAME "semantic.host.cxx${standard}.${case_id}" COMMAND "${target}")
        set_tests_properties(
            "semantic.host.cxx${standard}.${case_id}"
            PROPERTIES LABELS "semantic-host;cxx${standard};affected-regression"
        )
    endforeach()
endfunction()

asc_stl_add_host_case("asc.__config" "asc/__config/host.pass.cpp")

add_executable(asc_stl_host_cxx17_baseline "${ASC_STL_CASES_ROOT}/asc/__config/cxx17.pass.cpp")
target_link_libraries(asc_stl_host_cxx17_baseline PRIVATE asc_stl::asc_stl)
set_target_properties(
    asc_stl_host_cxx17_baseline
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
)
target_compile_options(asc_stl_host_cxx17_baseline PRIVATE -Wall -Wextra -Werror -pedantic -UNDEBUG)
add_test(NAME semantic.host.cxx17-baseline COMMAND asc_stl_host_cxx17_baseline)
set_tests_properties(
    semantic.host.cxx17-baseline
    PROPERTIES LABELS "semantic-host;cxx17;affected-regression"
)

asc_stl_add_host_case("asc.execution.determinism" "asc/execution.determinism/host.pass.cpp")
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
asc_stl_add_host_case("asc.std.version" "asc/std/version/host.pass.cpp")
asc_stl_add_host_case("asc.execution.output_ordering" "asc/execution.output_ordering/host.pass.cpp")
asc_stl_add_host_case("asc.std.__cstring.memcpy" "asc/std/__cstring/memcpy/host.pass.cpp")
asc_stl_add_host_case("asc.std.__cstring.memset" "asc/std/__cstring/memset/host.pass.cpp")
asc_stl_add_host_case("asc.std.__memory.addressof" "asc/std/__memory/addressof/host.pass.cpp")
asc_stl_add_host_case("asc.std.__tuple.tuple_element" "asc/std/__tuple/tuple_element/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.add_const" "asc/std/__type_traits/add_const/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.add_cv" "asc/std/__type_traits/add_cv/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.add_volatile" "asc/std/__type_traits/add_volatile/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.always_false" "asc/std/__type_traits/always_false/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.conditional" "asc/std/__type_traits/conditional/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.dependent_type" "asc/std/__type_traits/dependent_type/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.enable_if" "asc/std/__type_traits/enable_if/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.integral_constant" "asc/std/__type_traits/integral_constant/host.pass.cpp")
asc_stl_add_host_case(
    "asc.std.__type_traits.is_constant_evaluated"
    "asc/std/__type_traits/is_constant_evaluated/host.pass.cpp"
)
asc_stl_add_host_case("asc.std.__type_traits.lazy" "asc/std/__type_traits/lazy/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.nat" "asc/std/__type_traits/nat/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.remove_const" "asc/std/__type_traits/remove_const/host.pass.cpp")
asc_stl_add_host_case(
    "asc.std.__type_traits.remove_pointer" "asc/std/__type_traits/remove_pointer/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__type_traits.remove_volatile" "asc/std/__type_traits/remove_volatile/host.pass.cpp"
)
asc_stl_add_host_case("asc.std.__type_traits.type_identity" "asc/std/__type_traits/type_identity/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.void_t" "asc/std/__type_traits/void_t/host.pass.cpp")
asc_stl_add_host_case("asc.std.__utility.as_const" "asc/std/__utility/as_const/host.pass.cpp")
asc_stl_add_host_case("asc.std.__utility.declval" "asc/std/__utility/declval/host.pass.cpp")
asc_stl_add_host_case("asc.std.cstdint" "asc/std/cstdint/host.pass.cpp")
asc_stl_add_host_case("asc.std.ratio" "asc/std/ratio/host.pass.cpp")
asc_stl_add_host_case("asc.std.source_location" "asc/std/source_location/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.conjunction" "asc/std/__type_traits/conjunction/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.disjunction" "asc/std/__type_traits/disjunction/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.fold" "asc/std/__type_traits/fold/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_abstract" "asc/std/__type_traits/is_abstract/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_base_of" "asc/std/__type_traits/is_base_of/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_class" "asc/std/__type_traits/is_class/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_complete" "asc/std/__type_traits/is_complete/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_const" "asc/std/__type_traits/is_const/host.pass.cpp")
asc_stl_add_host_case(
    "asc.std.__type_traits.is_core_convertible" "asc/std/__type_traits/is_core_convertible/host.pass.cpp"
)
asc_stl_add_host_case("asc.std.__type_traits.is_empty" "asc/std/__type_traits/is_empty/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_enum" "asc/std/__type_traits/is_enum/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_final" "asc/std/__type_traits/is_final/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_reference" "asc/std/__type_traits/is_reference/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_same" "asc/std/__type_traits/is_same/host.pass.cpp")
asc_stl_add_host_case(
    "asc.std.__type_traits.is_standard_layout" "asc/std/__type_traits/is_standard_layout/host.pass.cpp"
)
asc_stl_add_host_case("asc.std.__type_traits.is_trivial" "asc/std/__type_traits/is_trivial/host.pass.cpp")
asc_stl_add_host_case(
    "asc.std.__type_traits.is_trivially_assignable"
    "asc/std/__type_traits/is_trivially_assignable/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__type_traits.is_trivially_constructible"
    "asc/std/__type_traits/is_trivially_constructible/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__type_traits.is_trivially_copyable"
    "asc/std/__type_traits/is_trivially_copyable/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__type_traits.is_unbounded_array" "asc/std/__type_traits/is_unbounded_array/host.pass.cpp"
)
asc_stl_add_host_case("asc.std.__type_traits.is_union" "asc/std/__type_traits/is_union/host.pass.cpp")
asc_stl_add_host_case(
    "asc.std.__type_traits.is_valid_expansion" "asc/std/__type_traits/is_valid_expansion/host.pass.cpp"
)
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
asc_stl_add_host_case(
    "asc.std.__type_traits.is_extended_floating_point"
    "asc/std/__type_traits/is_extended_floating_point/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__type_traits.is_floating_point" "asc/std/__type_traits/is_floating_point/host.pass.cpp"
)
asc_stl_add_host_case("asc.std.__type_traits.is_function" "asc/std/__type_traits/is_function/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_integral" "asc/std/__type_traits/is_integral/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.is_pointer" "asc/std/__type_traits/is_pointer/host.pass.cpp")
asc_stl_add_host_case(
    "asc.std.__type_traits.is_referenceable" "asc/std/__type_traits/is_referenceable/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__type_traits.is_signed_integer" "asc/std/__type_traits/is_signed_integer/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__type_traits.is_trivially_default_constructible"
    "asc/std/__type_traits/is_trivially_default_constructible/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__type_traits.is_unsigned_integer" "asc/std/__type_traits/is_unsigned_integer/host.pass.cpp"
)
asc_stl_add_host_case("asc.std.__type_traits.make_nbit_int" "asc/std/__type_traits/make_nbit_int/host.pass.cpp")
asc_stl_add_host_case("asc.std.__type_traits.promote" "asc/std/__type_traits/promote/host.pass.cpp")
asc_stl_add_host_case(
    "asc.std.__type_traits.underlying_type" "asc/std/__type_traits/underlying_type/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__utility.convert_to_integral" "asc/std/__utility/convert_to_integral/host.pass.cpp"
)
asc_stl_add_host_case(
    "asc.std.__utility.integer_sequence" "asc/std/__utility/integer_sequence/host.pass.cpp"
)
asc_stl_add_host_case("asc.std.__utility.priority_tag" "asc/std/__utility/priority_tag/host.pass.cpp")
asc_stl_add_host_case("asc.std.__utility.to_underlying" "asc/std/__utility/to_underlying/host.pass.cpp")
asc_stl_add_host_case("asc.std.cstddef" "asc/std/cstddef/host.pass.cpp")
asc_stl_add_host_case(
    "asc.std.cstddef.deprecated_names" "asc/std/cstddef/deprecated_names.absence.pass.cpp"
)

foreach(standard IN ITEMS 17 20)
    add_executable(
        asc_stl_host_cassert_ndebug_cxx${standard}
        "${ASC_STL_CASES_ROOT}/asc/std/cassert/ndebug.pass.cpp"
    )
    target_link_libraries(asc_stl_host_cassert_ndebug_cxx${standard} PRIVATE asc_stl::asc_stl)
    set_target_properties(
        asc_stl_host_cassert_ndebug_cxx${standard}
        PROPERTIES CXX_STANDARD "${standard}" CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
    )
    target_compile_definitions(asc_stl_host_cassert_ndebug_cxx${standard} PRIVATE NDEBUG)
    target_compile_options(
        asc_stl_host_cassert_ndebug_cxx${standard} PRIVATE -Wall -Wextra -Werror -pedantic
    )
    add_test(
        NAME semantic.host.cxx${standard}.asc.std.cassert.ndebug
        COMMAND asc_stl_host_cassert_ndebug_cxx${standard}
    )
    set_tests_properties(
        semantic.host.cxx${standard}.asc.std.cassert.ndebug
        PROPERTIES LABELS "semantic-host;cxx${standard};negative-boundary;affected-regression"
    )

    add_executable(
        asc_stl_host_cassert_failure_cxx${standard}
        "${ASC_STL_CASES_ROOT}/asc/std/cassert/failure.fail.cpp"
    )
    target_link_libraries(asc_stl_host_cassert_failure_cxx${standard} PRIVATE asc_stl::asc_stl)
    set_target_properties(
        asc_stl_host_cassert_failure_cxx${standard}
        PROPERTIES CXX_STANDARD "${standard}" CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
    )
    target_compile_options(
        asc_stl_host_cassert_failure_cxx${standard} PRIVATE -Wall -Wextra -Werror -pedantic -UNDEBUG
    )
    add_test(
        NAME semantic.host.cxx${standard}.asc.std.cassert.failure
        COMMAND
            "${Python3_EXECUTABLE}"
            "${ASC_STL_TEST_ROOT}/scripts/run_assert_failure.py"
            $<TARGET_FILE:asc_stl_host_cassert_failure_cxx${standard}>
    )
    set_tests_properties(
        semantic.host.cxx${standard}.asc.std.cassert.failure
        PROPERTIES LABELS "semantic-host;cxx${standard};negative-boundary;affected-regression"
    )
endforeach()

if(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS)
    add_test(
        NAME gate.device.compile
        COMMAND
            "${Python3_EXECUTABLE}"
            "${ASC_STL_TEST_ROOT}/scripts/run_device_compile.py"
            --manifest "${ASC_STL_MANIFEST}"
            --include-root "${ASC_STL_INCLUDE_ROOT}"
            --test-root "${ASC_STL_TEST_ROOT}"
            --npu-arch "${ASC_STL_NPU_ARCH}"
    )
    set_tests_properties(
        gate.device.compile
        PROPERTIES LABELS "header-device;device-compile" RUN_SERIAL TRUE TIMEOUT 3600
    )
endif()

if(ASC_STL_ENABLE_CANNSIM_TESTS)
    set(
        source_location_cannsim_case_root
        "${ASC_STL_CASES_ROOT}/asc/std/source_location/runtime/cannsim"
    )
    set(source_location_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/source-location-cannsim")
    set(
        foundation_cannsim_case_root
        "${ASC_STL_CASES_ROOT}/asc/std/__cstring/memcpy/runtime/cannsim"
    )
    set(foundation_cannsim_build_root "${CMAKE_CURRENT_BINARY_DIR}/foundation-cannsim")
    add_custom_target(
        asc_stl_cannsim_tests
        COMMAND
            "${CMAKE_COMMAND}" -S "${source_location_cannsim_case_root}"
            -B "${source_location_cannsim_build_root}"
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND
            "${CMAKE_COMMAND}" --build "${source_location_cannsim_build_root}"
            --target asc_stl_source_location_cannsim -j2
        COMMAND
            "${CMAKE_COMMAND}" -S "${foundation_cannsim_case_root}"
            -B "${foundation_cannsim_build_root}"
            -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
            -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
            -DASC_STL_TARGET_SOC=${ASC_STL_TARGET_SOC}
            -DCMAKE_BUILD_TYPE=Release
        COMMAND
            "${CMAKE_COMMAND}" --build "${foundation_cannsim_build_root}"
            --target asc_stl_foundation_cannsim -j2
        VERBATIM
    )
    add_test(
        NAME semantic.cannsim.asc.std.source-location
        COMMAND
            "${ASC_STL_TEST_ROOT}/scripts/run_cannsim_test.sh"
            "${ASC_STL_CANNSIM_EXECUTABLE}"
            "${source_location_cannsim_build_root}/asc_stl_source_location_cannsim"
            "${ASC_STL_CANNSIM_SOC}"
            "${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/source-location"
            "${source_location_cannsim_build_root}/lib"
            ASC_STL_CANNSIM_ASC_STD_SOURCE_LOCATION_PASS
    )
    set_tests_properties(
        semantic.cannsim.asc.std.source-location
        PROPERTIES LABELS "cannsim-smoke;cannsim-runtime" RUN_SERIAL TRUE
    )
    add_test(
        NAME semantic.cannsim.asc.std.foundation-runtime
        COMMAND
            "${ASC_STL_TEST_ROOT}/scripts/run_cannsim_test.sh"
            "${ASC_STL_CANNSIM_EXECUTABLE}"
            "${foundation_cannsim_build_root}/asc_stl_foundation_cannsim"
            "${ASC_STL_CANNSIM_SOC}"
            "${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/foundation"
            "${foundation_cannsim_build_root}/lib"
            ASC_STL_CANNSIM_FOUNDATION_PASS
    )
    set_tests_properties(
        semantic.cannsim.asc.std.foundation-runtime
        PROPERTIES LABELS "cannsim-smoke;cannsim-runtime" RUN_SERIAL TRUE
    )
endif()
