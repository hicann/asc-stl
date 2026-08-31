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

option(ASC_STL_ENABLE_HOST_TESTS "Enable Host header and semantic gates" ON)
option(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS "Enable real AscendC Device compile gates" OFF)
option(ASC_STL_ENABLE_CANNSIM_TESTS "Enable formal cannsim runtime gates" OFF)
set(ASC_STL_CANN_PACKAGE_PATH "$ENV{ASCEND_HOME_PATH}" CACHE PATH "Installed CANN package root")
set(ASC_STL_TARGET_SOC "" CACHE STRING "AscendC target SoC, for example Ascend950PR_9599")
set(ASC_STL_CANNSIM_EXECUTABLE "" CACHE FILEPATH "cannsim executable")
set(ASC_STL_CANNSIM_SOC "Ascend950" CACHE STRING "cannsim target SoC")

set(ASC_STL_TEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(ASC_STL_MANIFEST "${ASC_STL_TEST_ROOT}/metadata/headers.json")
set(ASC_STL_EXCLUSIONS "${ASC_STL_TEST_ROOT}/metadata/header_exclusions.json")
set(ASC_STL_INCLUDE_ROOT "${PROJECT_SOURCE_DIR}/include")
set(ASC_STL_CASES_ROOT "${ASC_STL_TEST_ROOT}/cases")
set(ASC_STL_CANNSIM_INFRASTRUCTURE "${ASC_STL_TEST_ROOT}/infrastructure/cannsim")
set(ASC_STL_HEADER_HOST_TEMPLATE "${ASC_STL_TEST_ROOT}/infrastructure/header/header_host.cpp.in")
set(ASC_STL_HEADER_DEVICE_TEMPLATE "${ASC_STL_TEST_ROOT}/infrastructure/header/header_device.cpp.in")

function(asc_stl_get_case_identity header_path case_relative_out case_id_out)
    if(header_path MATCHES "^asc/std/")
        string(REGEX REPLACE "^asc/std/" "" case_relative "${header_path}")
        string(REGEX REPLACE "\\.h$" "" case_relative "${case_relative}")
        string(FIND "${case_relative}" "/" separator)
        if(separator EQUAL -1 AND NOT case_relative MATCHES "^_")
            set(case_relative "public/${case_relative}")
        endif()
    elseif(header_path MATCHES "^asc/")
        string(REGEX REPLACE "^asc/" "" case_relative "${header_path}")
        string(REGEX REPLACE "\\.h$" "" case_relative "${case_relative}")
        string(FIND "${case_relative}" "/" separator)
        if(separator EQUAL -1 AND NOT case_relative MATCHES "^_")
            set(case_relative "public_entry/${case_relative}")
        else()
            set(case_relative "extension/${case_relative}")
        endif()
    elseif(header_path MATCHES "^hw/")
        string(REGEX REPLACE "^hw/" "" case_relative "${header_path}")
        string(REGEX REPLACE "\\.h$" "" case_relative "${case_relative}")
        string(FIND "${case_relative}" "/" separator)
        if(separator EQUAL -1 AND NOT case_relative MATCHES "^_")
            set(case_relative "public_entry/${case_relative}")
        else()
            set(case_relative "hw/${case_relative}")
        endif()
    else()
        message(FATAL_ERROR "Unsupported ASC-STL header domain: ${header_path}")
    endif()
    string(REPLACE "/" "." case_id "${case_relative}")
    set("${case_relative_out}" "${case_relative}" PARENT_SCOPE)
    set("${case_id_out}" "${case_id}" PARENT_SCOPE)
endfunction()

execute_process(
    COMMAND
        "${Python3_EXECUTABLE}" "${ASC_STL_TEST_ROOT}/scripts/validate_metadata.py"
        --manifest "${ASC_STL_MANIFEST}"
        --exclusions "${ASC_STL_EXCLUSIONS}"
        --include-root "${ASC_STL_INCLUDE_ROOT}"
        --test-root "${ASC_STL_TEST_ROOT}"
    RESULT_VARIABLE metadata_result
    OUTPUT_VARIABLE metadata_output
    ERROR_VARIABLE metadata_error
)
if(NOT metadata_result EQUAL 0)
    message(FATAL_ERROR "Header gate metadata validation failed:\n${metadata_output}${metadata_error}")
endif()

add_test(
    NAME gate.static-rules
    COMMAND
        "${Python3_EXECUTABLE}" "${ASC_STL_TEST_ROOT}/scripts/validate_metadata.py"
        --manifest "${ASC_STL_MANIFEST}"
        --exclusions "${ASC_STL_EXCLUSIONS}"
        --include-root "${ASC_STL_INCLUDE_ROOT}"
        --test-root "${ASC_STL_TEST_ROOT}"
)
set_tests_properties(gate.static-rules PROPERTIES LABELS "metadata;static-rules;affected-regression;nightly")

file(READ "${ASC_STL_MANIFEST}" manifest_json)
string(JSON header_count LENGTH "${manifest_json}" headers)
if(header_count EQUAL 0)
    message(FATAL_ERROR "The header gate manifest must register at least one header")
endif()
math(EXPR last_header_index "${header_count} - 1")
set(host_semantic_entries "")
set(device_compile_entries "")
set(cannsim_runtime_entries "")

include("${PROJECT_SOURCE_DIR}/cmake/AscStlHeaderTesting.cmake")
if(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS OR ASC_STL_ENABLE_CANNSIM_TESTS)
    include("${PROJECT_SOURCE_DIR}/cmake/AscStlDeviceTesting.cmake")
    asc_stl_initialize_device_testing()
endif()

foreach(index RANGE 0 ${last_header_index})
    string(JSON header_id GET "${manifest_json}" headers ${index} id)
    string(JSON header_path GET "${manifest_json}" headers ${index} target)
    asc_stl_get_case_identity("${header_path}" case_relative case_id)
    string(JSON host_header_applicable GET "${manifest_json}" headers ${index} applicability host_header)
    string(JSON device_header_applicable GET "${manifest_json}" headers ${index} applicability device_header)

    if(ASC_STL_ENABLE_HOST_TESTS AND host_header_applicable)
        string(JSON host_header_test GET "${manifest_json}" headers ${index} tests host_header)
        asc_stl_add_host_header_test("${host_header_test}" "${header_id}" "${header_path}")
    endif()
    if(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS AND device_header_applicable)
        string(JSON device_header_test GET "${manifest_json}" headers ${index} tests device_header)
        asc_stl_add_device_header_test("${device_header_test}" "${header_id}" "${header_path}")
    endif()

    string(JSON host_semantic_applicable GET "${manifest_json}" headers ${index} applicability host_semantic)
    if(ASC_STL_ENABLE_HOST_TESTS AND host_semantic_applicable)
        string(JSON host_semantic_test GET "${manifest_json}" headers ${index} tests host_semantic)
        list(APPEND host_semantic_entries "${header_id}|${case_relative}|${case_id}|${host_semantic_test}")
    endif()
    string(JSON device_compile_applicable GET "${manifest_json}" headers ${index} applicability device_compile)
    if(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS AND device_compile_applicable)
        string(JSON device_compile_test GET "${manifest_json}" headers ${index} tests device_compile)
        list(APPEND device_compile_entries "${header_id}|${case_relative}|${case_id}|${device_compile_test}")
    endif()
    string(JSON cannsim_runtime_applicable GET "${manifest_json}" headers ${index} applicability cannsim_runtime)
    if(ASC_STL_ENABLE_CANNSIM_TESTS AND cannsim_runtime_applicable)
        string(JSON cannsim_runtime_test GET "${manifest_json}" headers ${index} tests cannsim_runtime)
        list(APPEND cannsim_runtime_entries "${header_id}|${case_relative}|${case_id}|${cannsim_runtime_test}")
    endif()
endforeach()

foreach(entry IN LISTS host_semantic_entries)
    string(REPLACE "|" ";" entry_parts "${entry}")
    list(GET entry_parts 0 header_id)
    list(GET entry_parts 1 case_relative)
    list(GET entry_parts 2 case_id)
    list(GET entry_parts 3 test_name)
    set(case_root "${ASC_STL_CASES_ROOT}/${case_relative}")
    set(source "${case_root}/host.pass.cpp")
    if(NOT EXISTS "${source}")
        message(FATAL_ERROR "Host semantic test ${test_name} is missing source ${source}")
    endif()
    string(MAKE_C_IDENTIFIER "${case_id}" target_suffix)
    set(target "asc_stl_semantic_host_${target_suffix}")
    add_executable("${target}" "${source}")
    target_link_libraries("${target}" PRIVATE asc_stl::asc_stl)
    target_include_directories("${target}" PRIVATE "${case_root}" "${case_root}/support")
    if(MSVC)
        target_compile_options("${target}" PRIVATE /W4 /WX)
    else()
        target_compile_options("${target}" PRIVATE -Wall -Wextra -Werror -Wno-deprecated-declarations)
    endif()
    add_test(NAME "${test_name}" COMMAND "${target}")
    set_tests_properties("${test_name}" PROPERTIES LABELS "semantic-host;affected-regression;nightly")
endforeach()

foreach(entry IN LISTS device_compile_entries)
    string(REPLACE "|" ";" entry_parts "${entry}")
    list(GET entry_parts 0 header_id)
    list(GET entry_parts 1 case_relative)
    list(GET entry_parts 2 case_id)
    list(GET entry_parts 3 test_name)
    set(case_root "${ASC_STL_CASES_ROOT}/${case_relative}")
    set(source "${case_root}/device.compile.cpp")
    if(NOT EXISTS "${source}")
        message(FATAL_ERROR "Device semantic test ${test_name} is missing source ${source}")
    endif()
    string(MAKE_C_IDENTIFIER "${case_id}" target_suffix)
    asc_stl_add_device_compile_test(
        "${test_name}"
        "asc_stl_semantic_device_${target_suffix}"
        "${source}"
        "device-compile"
        "${case_root}"
    )
endforeach()

if(ASC_STL_ENABLE_CANNSIM_TESTS)
    include("${PROJECT_SOURCE_DIR}/cmake/AscStlCannsimTesting.cmake")
    asc_stl_register_cannsim_smoke()

    foreach(entry IN LISTS cannsim_runtime_entries)
        string(REPLACE "|" ";" entry_parts "${entry}")
        list(GET entry_parts 0 header_id)
        list(GET entry_parts 1 case_relative)
        list(GET entry_parts 2 case_id)
        list(GET entry_parts 3 test_name)
        set(cannsim_root "${ASC_STL_CASES_ROOT}/${case_relative}/cannsim")
        string(MAKE_C_IDENTIFIER "${case_id}" target_suffix)
        set(kernel_target "asc_stl_cannsim_${target_suffix}_kernel")
        set(runner_target "asc_stl_cannsim_${target_suffix}")

        ascendc_library("${kernel_target}" SHARED "${cannsim_root}/kernel.cpp")
        ascendc_compile_options("${kernel_target}" PRIVATE -std=c++17)
        ascendc_include_directories(
            "${kernel_target}"
            PRIVATE
            "${PROJECT_SOURCE_DIR}/include"
        )
        add_executable(
            "${runner_target}"
            "${cannsim_root}/launcher.cpp"
            "${cannsim_root}/main.cpp"
        )
        target_include_directories(
            "${runner_target}"
            PRIVATE "${cannsim_root}" "${ASC_STL_CANNSIM_INFRASTRUCTURE}"
        )
        target_link_libraries(
            "${runner_target}"
            PRIVATE host_intf_pub "${kernel_target}"
        )
        if(MSVC)
            target_compile_options("${runner_target}" PRIVATE /W4 /WX)
        else()
            target_compile_options("${runner_target}" PRIVATE -Wall -Wextra -Werror)
        endif()
        string(TOUPPER "${header_id}" marker_id)
        asc_stl_add_cannsim_semantic_test(
            "${test_name}"
            "${runner_target}"
            "ASC_STL_CANNSIM_${marker_id}_PASS"
        )
    endforeach()

    get_property(cannsim_runner_targets GLOBAL PROPERTY ASC_STL_CANNSIM_RUNNER_TARGETS)
    if(NOT cannsim_runner_targets)
        message(FATAL_ERROR "Cannsim testing is enabled without any registered runner targets")
    endif()
    add_custom_target(asc_stl_cannsim_tests DEPENDS ${cannsim_runner_targets})
    asc_stl_validate_cannsim_manifest()
endif()
