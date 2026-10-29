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

cmake_minimum_required(VERSION 3.20)
project(asc_stl_quick_start LANGUAGES C CXX)

set(ASC_STL_EXAMPLE_STANDARD 17 CACHE STRING "C++ standard (17 or 20)")
if(NOT ASC_STL_EXAMPLE_STANDARD MATCHES "^(17|20)$")
    message(FATAL_ERROR "ASC_STL_EXAMPLE_STANDARD must be 17 or 20")
endif()
set(CMAKE_CXX_STANDARD ${ASC_STL_EXAMPLE_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
get_filename_component(default_include "${CMAKE_CURRENT_SOURCE_DIR}/../../../../include" ABSOLUTE)
set(ASC_STL_INCLUDE_DIR "${default_include}" CACHE PATH "ASC-STL include directory")
if(NOT EXISTS "${ASC_STL_INCLUDE_DIR}/asc/std/algorithm")
    message(FATAL_ERROR "ASC_STL_INCLUDE_DIR must name the ASC-STL include tree")
endif()
if(NOT DEFINED ENV{ASCEND_HOME_PATH})
    message(FATAL_ERROR "Source the CANN set_env.sh before configuring this example")
endif()
set(ASCEND_CANN_PACKAGE_PATH "$ENV{ASCEND_HOME_PATH}" CACHE PATH "CANN package")
set(SOC_VERSION "Ascend950PR_9599" CACHE STRING "Target SoC")
set(RUN_MODE npu CACHE STRING "AscendC run mode")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/ascendc-install" CACHE PATH "Install prefix")
set(ascendc_cmake "")
foreach(directory compiler tools)
    set(candidate "${ASCEND_CANN_PACKAGE_PATH}/${directory}/tikcpp/ascendc_kernel_cmake/ascendc.cmake")
    if(EXISTS "${candidate}")
        set(ascendc_cmake "${candidate}")
        break()
    endif()
endforeach()
if(NOT ascendc_cmake)
    message(FATAL_ERROR "CANN ascendc.cmake was not found")
endif()
include("${ascendc_cmake}")
ascendc_library(quick_start_kernel SHARED add_relu_kernel.cpp)
# Some CANN 9.2 helpers replace preprocessing object inputs with linked files.
# Recreate this project's temporary objects before their next preprocessing build.
# The SDK installation and source files remain unchanged.
if(TARGET quick_start_kernel_preprocess)
    ExternalProject_Add_Step(quick_start_kernel_preprocess refresh_compile_objects
        COMMAND "${CMAKE_COMMAND}" --build <BINARY_DIR> --target clean
        DEPENDEES configure DEPENDERS build ALWAYS 1)
endif()
ascendc_compile_options(quick_start_kernel PRIVATE
    -std=c++${ASC_STL_EXAMPLE_STANDARD} -forward-options-to-host-compiler -std=c++${ASC_STL_EXAMPLE_STANDARD})
ascendc_include_directories(quick_start_kernel PRIVATE "${ASC_STL_INCLUDE_DIR}")

add_executable(asc_stl_quick_start main.cpp)
add_dependencies(asc_stl_quick_start quick_start_kernel)
target_include_directories(asc_stl_quick_start PRIVATE "${CMAKE_BINARY_DIR}/include/quick_start_kernel")
target_link_libraries(asc_stl_quick_start PRIVATE host_intf_pub quick_start_kernel)
target_compile_options(asc_stl_quick_start PRIVATE -Wall -Wextra -Werror)
# CANN's helper sets CMAKE_SKIP_RPATH, so request this executable's relative
# kernel-library search path directly without changing SDK target behavior.
target_link_options(asc_stl_quick_start PRIVATE "LINKER:-rpath,$ORIGIN/lib")
