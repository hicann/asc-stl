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

function(asc_stl_validate_cannsim_configuration)
    if(NOT ASC_STL_CANNSIM_SOC STREQUAL "Ascend950")
        message(FATAL_ERROR "ASC_STL_CANNSIM_SOC=${ASC_STL_CANNSIM_SOC} is unsupported; CANN 9.0.0 supports Ascend950")
    endif()

    if(NOT ASC_STL_CANNSIM_EXECUTABLE)
        unset(detected_cannsim CACHE)
        find_program(
            detected_cannsim
            NAMES cannsim
            HINTS "${ASC_STL_CANN_PACKAGE_PATH}/bin"
        )
        if(detected_cannsim)
            set(ASC_STL_CANNSIM_EXECUTABLE "${detected_cannsim}" CACHE FILEPATH "cannsim executable" FORCE)
        endif()
    endif()
    if(NOT ASC_STL_CANNSIM_EXECUTABLE OR NOT EXISTS "${ASC_STL_CANNSIM_EXECUTABLE}")
        message(FATAL_ERROR "ASC_STL_CANNSIM_EXECUTABLE must name the installed cannsim executable")
    endif()

    execute_process(
        COMMAND "${ASC_STL_CANNSIM_EXECUTABLE}" record --help
        RESULT_VARIABLE cannsim_help_result
        OUTPUT_QUIET
        ERROR_QUIET
    )
    if(NOT cannsim_help_result EQUAL 0)
        message(FATAL_ERROR "ASC_STL_CANNSIM_EXECUTABLE cannot start in the configured CANN environment")
    endif()
endfunction()

function(asc_stl_add_cannsim_test test_name runner_target labels pass_marker)
    if(NOT TARGET "${runner_target}")
        message(FATAL_ERROR "Cannsim test ${test_name} requires runner target ${runner_target}")
    endif()
    if(NOT pass_marker MATCHES "^ASC_STL_CANNSIM_[A-Z0-9_]+_PASS$")
        message(FATAL_ERROR "Cannsim test ${test_name} requires a stable, test-specific PASS marker")
    endif()

    add_test(
        NAME "${test_name}"
        COMMAND
            "${ASC_STL_TEST_ROOT}/scripts/run_cannsim_test.sh"
            "${ASC_STL_CANNSIM_EXECUTABLE}"
            "$<TARGET_FILE:${runner_target}>"
            "${ASC_STL_CANNSIM_SOC}"
            "${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/${test_name}"
            "$<TARGET_FILE_DIR:asc_stl_cannsim_smoke_kernel>"
            "${pass_marker}"
    )
    set_tests_properties("${test_name}" PROPERTIES LABELS "${labels}" RUN_SERIAL TRUE)
endfunction()

function(asc_stl_register_cannsim_smoke)
    asc_stl_validate_cannsim_configuration()

    set(smoke_root "${ASC_STL_TEST_ROOT}/infrastructure/cannsim/smoke")
    ascendc_library(asc_stl_cannsim_smoke_kernel SHARED "${smoke_root}/kernel.cpp")
    ascendc_compile_options(asc_stl_cannsim_smoke_kernel PRIVATE -std=c++17)

    add_executable(
        asc_stl_cannsim_smoke
        "${smoke_root}/launcher.cpp"
        "${smoke_root}/main.cpp"
    )
    target_include_directories(
        asc_stl_cannsim_smoke
        PRIVATE "${smoke_root}" "${ASC_STL_CANNSIM_INFRASTRUCTURE}"
    )
    target_link_libraries(
        asc_stl_cannsim_smoke
        PRIVATE host_intf_pub asc_stl_cannsim_smoke_kernel
    )
    if(MSVC)
        target_compile_options(asc_stl_cannsim_smoke PRIVATE /W4 /WX)
    else()
        target_compile_options(asc_stl_cannsim_smoke PRIVATE -Wall -Wextra -Werror)
    endif()

    asc_stl_add_cannsim_test(
        cannsim.smoke
        asc_stl_cannsim_smoke
        "cannsim-smoke;affected-regression;nightly"
        ASC_STL_CANNSIM_SMOKE_PASS
    )
    set_tests_properties(cannsim.smoke PROPERTIES FIXTURES_SETUP asc_stl_cannsim_ready)
    set_property(GLOBAL APPEND PROPERTY ASC_STL_CANNSIM_RUNNER_TARGETS asc_stl_cannsim_smoke)
endfunction()

function(asc_stl_validate_cannsim_manifest)
    if(NOT TEST cannsim.smoke OR NOT TARGET asc_stl_cannsim_smoke)
        message(FATAL_ERROR "The cannsim backend requires its smoke target and CTest")
    endif()
    get_test_property(cannsim.smoke FIXTURES_SETUP smoke_fixture)
    get_test_property(cannsim.smoke LABELS smoke_labels)
    if(NOT smoke_fixture STREQUAL "asc_stl_cannsim_ready")
        message(FATAL_ERROR "cannsim.smoke must set up the asc_stl_cannsim_ready fixture")
    endif()
    foreach(required_label IN ITEMS cannsim-smoke affected-regression nightly)
        if(NOT required_label IN_LIST smoke_labels)
            message(FATAL_ERROR "cannsim.smoke is missing required label ${required_label}")
        endif()
    endforeach()

    file(READ "${ASC_STL_MANIFEST}" cannsim_manifest_json)
    string(JSON cannsim_header_count LENGTH "${cannsim_manifest_json}" headers)
    math(EXPR cannsim_last_header_index "${cannsim_header_count} - 1")
    set(expected_runtime_tests "")
    foreach(index RANGE 0 ${cannsim_last_header_index})
        string(JSON header_id GET "${cannsim_manifest_json}" headers ${index} id)
        string(
            JSON runtime_applicable
            GET "${cannsim_manifest_json}" headers ${index} applicability cannsim_runtime
        )
        if(runtime_applicable)
            string(
                JSON runtime_test
                GET "${cannsim_manifest_json}" headers ${index} tests cannsim_runtime
            )
            list(APPEND expected_runtime_tests "${runtime_test}")
            if(NOT TEST "${runtime_test}")
                message(FATAL_ERROR "Applicable cannsim test is not registered: ${runtime_test}")
            endif()
            get_test_property("${runtime_test}" FIXTURES_REQUIRED runtime_fixture)
            get_test_property("${runtime_test}" LABELS runtime_labels)
            if(NOT runtime_fixture STREQUAL "asc_stl_cannsim_ready")
                message(FATAL_ERROR "${runtime_test} must require the cannsim smoke fixture")
            endif()
            foreach(required_label IN ITEMS cannsim-runtime affected-regression nightly)
                if(NOT required_label IN_LIST runtime_labels)
                    message(FATAL_ERROR "${runtime_test} is missing required label ${required_label}")
                endif()
            endforeach()
        endif()
    endforeach()

    get_property(registered_tests DIRECTORY PROPERTY TESTS)
    foreach(test_name IN LISTS registered_tests)
        if(test_name MATCHES "^semantic\\.cannsim\\.")
            if(NOT test_name IN_LIST expected_runtime_tests)
                message(FATAL_ERROR "Cannsim semantic CTest is not registered in metadata: ${test_name}")
            endif()
        endif()
    endforeach()
endfunction()

function(asc_stl_add_cannsim_semantic_test test_name runner_target pass_marker)
    if(NOT TEST cannsim.smoke OR NOT TARGET asc_stl_cannsim_smoke)
        message(FATAL_ERROR "${test_name} requires the registered cannsim smoke gate")
    endif()
    asc_stl_add_cannsim_test(
        "${test_name}"
        "${runner_target}"
        "cannsim-runtime;affected-regression;nightly"
        "${pass_marker}"
    )
    set_tests_properties(
        "${test_name}"
        PROPERTIES FIXTURES_REQUIRED asc_stl_cannsim_ready
    )
    set_property(GLOBAL APPEND PROPERTY ASC_STL_CANNSIM_RUNNER_TARGETS "${runner_target}")
endfunction()
