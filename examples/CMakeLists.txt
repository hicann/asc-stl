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
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(asc_stl_examples LANGUAGES CXX)
endif()
include(CTest)
include(cmake/AscStlExample.cmake)

add_subdirectory(standard/allocator_traits)
add_subdirectory(standard/explicit_allocator_vector)
add_subdirectory(standard/pointer_alignment)

option(ASC_STL_BUILD_RUNTIME_EXAMPLES "Build examples that require CANN Runtime" OFF)
if(ASC_STL_BUILD_RUNTIME_EXAMPLES)
    add_subdirectory(runtime/stream_event)
endif()

option(ASC_STL_BUILD_DEVICE_EXAMPLES "Build CANN Kernel examples without running them" OFF)
if(ASC_STL_BUILD_DEVICE_EXAMPLES)
    include(ExternalProject)
    set(CMAKE_ASC_ARCHITECTURES "dav-3510" CACHE STRING "NPU architecture")
    set(SOC_VERSION "Ascend950PR_9599" CACHE STRING "Target SoC for the AscendC quick start")
    # Isolate the SDK's ASC and AscendC build systems from the Host CMake project.
    foreach(name IN ITEMS quick_start atomic_operations warp_collectives pipeline_copy parallel_algorithms)
        if(name STREQUAL "quick_start")
            set(example_source "${CMAKE_CURRENT_SOURCE_DIR}/quick_start")
        else()
            set(example_source "${CMAKE_CURRENT_SOURCE_DIR}/extension/${name}")
        endif()
        ExternalProject_Add(asc_stl_example_${name}
            SOURCE_DIR "${example_source}"
            BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/device/${name}"
            CMAKE_ARGS
                "-DASC_STL_EXAMPLE_STANDARD=${ASC_STL_EXAMPLE_STANDARD}"
                "-DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_DIR}"
                "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
                "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
                "-DCMAKE_ASC_ARCHITECTURES=${CMAKE_ASC_ARCHITECTURES}"
                "-DSOC_VERSION=${SOC_VERSION}"
            BUILD_ALWAYS TRUE
            INSTALL_COMMAND ""
            TEST_COMMAND "")
    endforeach()
endif()
