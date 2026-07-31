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

macro(asc_stl_initialize_device_testing)
    if(NOT ASC_STL_TARGET_SOC)
        message(FATAL_ERROR "ASC_STL_TARGET_SOC is required for real AscendC Device compilation")
    endif()
    if(NOT ASC_STL_CANN_PACKAGE_PATH OR NOT IS_DIRECTORY "${ASC_STL_CANN_PACKAGE_PATH}")
        message(
            FATAL_ERROR
            "ASC_STL_CANN_PACKAGE_PATH must name an installed CANN package when "
            "Device compile or cannsim tests are enabled"
        )
    endif()

    set(candidates
        "${ASC_STL_CANN_PACKAGE_PATH}/compiler/tikcpp/ascendc_kernel_cmake"
        "${ASC_STL_CANN_PACKAGE_PATH}/tools/tikcpp/ascendc_kernel_cmake"
    )
    set(ascendc_cmake "")
    foreach(candidate IN LISTS candidates)
        if(EXISTS "${candidate}/ascendc.cmake")
            set(ascendc_cmake "${candidate}/ascendc.cmake")
            break()
        endif()
    endforeach()
    if(NOT ascendc_cmake)
        message(
            FATAL_ERROR
            "The official CANN ascendc_kernel_cmake/ascendc.cmake was not found below "
            "ASC_STL_CANN_PACKAGE_PATH=${ASC_STL_CANN_PACKAGE_PATH}"
        )
    endif()

    set(ASCEND_CANN_PACKAGE_PATH "${ASC_STL_CANN_PACKAGE_PATH}" CACHE PATH "CANN package used by AscendC" FORCE)
    set(SOC_VERSION "${ASC_STL_TARGET_SOC}" CACHE STRING "AscendC target SoC" FORCE)
    set(RUN_MODE npu CACHE STRING "AscendC gate run mode" FORCE)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/ascendc-install" CACHE PATH "AscendC gate output root" FORCE)
    include("${ascendc_cmake}")
    message(STATUS "ASC-STL Device gate uses official AscendC module: ${ascendc_cmake}")

    if(
        NOT COMMAND ascendc_library
        OR NOT COMMAND ascendc_include_directories
        OR NOT COMMAND ascendc_compile_options
    )
        message(FATAL_ERROR "The selected official AscendC CMake module lacks required build commands")
    endif()
endmacro()

function(asc_stl_add_device_compile_test test_name target source label support_root)
    ascendc_library("${target}" OBJECT "${source}")
    ascendc_compile_options("${target}" PRIVATE -std=c++17)
    ascendc_include_directories("${target}" PRIVATE "${PROJECT_SOURCE_DIR}/libascendcxx/include")
    if(support_root)
        ascendc_include_directories("${target}" PRIVATE "${support_root}" "${support_root}/support")
    endif()

    if(TARGET "${target}_device_obj")
        set(device_build_target "${target}_device_obj")
    elseif(TARGET "${target}")
        set(device_build_target "${target}")
    else()
        message(FATAL_ERROR "ascendc_library did not create a buildable Device target for ${target}")
    endif()

    set(build_command "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}")
    get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(is_multi_config)
        list(APPEND build_command --config "$<CONFIG>")
    endif()
    list(APPEND build_command --target "${device_build_target}")
    add_test(NAME "${test_name}" COMMAND ${build_command})
    set_tests_properties(
        "${test_name}"
        PROPERTIES LABELS "${label};affected-regression;nightly" RUN_SERIAL TRUE
    )
endfunction()

function(asc_stl_add_device_header_test test_name header_id header)
    set(HEADER "${header}")
    set(output_dir "${CMAKE_CURRENT_BINARY_DIR}/generated/header_device")
    set(source "${output_dir}/${header_id}.cpp")
    file(MAKE_DIRECTORY "${output_dir}")
    configure_file("${ASC_STL_HEADER_DEVICE_TEMPLATE}" "${source}" @ONLY)
    asc_stl_add_device_compile_test(
        "${test_name}"
        "asc_stl_header_device_${header_id}"
        "${source}"
        "header-device"
        ""
    )
endfunction()
