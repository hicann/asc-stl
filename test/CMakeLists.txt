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

add_test(
    NAME asc_stl.metadata
    COMMAND
        "${Python3_EXECUTABLE}"
        "${CMAKE_CURRENT_SOURCE_DIR}/scripts/validate_metadata.py"
        --include-root "${PROJECT_SOURCE_DIR}/include/asc"
        --metadata "${CMAKE_CURRENT_SOURCE_DIR}/metadata/headers.json"
)
set_tests_properties(
    asc_stl.metadata
    PROPERTIES LABELS "metadata;static-rules;affected-regression"
)

add_executable(asc_stl_framework_consumer framework/consumer.cpp)
target_link_libraries(asc_stl_framework_consumer PRIVATE asc_stl::asc_stl)
set_target_properties(
    asc_stl_framework_consumer
    PROPERTIES
        CXX_STANDARD "${ASC_STL_TEST_CXX_STANDARD}"
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
add_test(NAME asc_stl.framework.consumer COMMAND asc_stl_framework_consumer)
set_tests_properties(
    asc_stl.framework.consumer
    PROPERTIES LABELS "semantic-host;affected-regression"
)

add_test(
    NAME asc_stl.header.host.not_applicable
    COMMAND
        "${Python3_EXECUTABLE}"
        "${CMAKE_CURRENT_SOURCE_DIR}/scripts/report_not_applicable.py"
        "Host Header"
)
set_tests_properties(
    asc_stl.header.host.not_applicable
    PROPERTIES LABELS "header-host;affected-regression"
)

if(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS)
    add_test(
        NAME asc_stl.header.device.not_applicable
        COMMAND
            "${Python3_EXECUTABLE}"
            "${CMAKE_CURRENT_SOURCE_DIR}/scripts/report_not_applicable.py"
            "Device compile"
    )
    set_tests_properties(
        asc_stl.header.device.not_applicable
        PROPERTIES LABELS "header-device;device-compile"
    )
endif()

if(ASC_STL_ENABLE_CANNSIM_TESTS)
    add_custom_target(asc_stl_cannsim_tests)
    add_test(
        NAME asc_stl.cannsim.not_applicable
        COMMAND
            "${Python3_EXECUTABLE}"
            "${CMAKE_CURRENT_SOURCE_DIR}/scripts/report_not_applicable.py"
            "cannsim runtime"
    )
    set_tests_properties(
        asc_stl.cannsim.not_applicable
        PROPERTIES LABELS "cannsim-smoke;cannsim-runtime"
    )
endif()
