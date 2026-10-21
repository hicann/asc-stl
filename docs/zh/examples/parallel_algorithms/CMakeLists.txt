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

cmake_minimum_required(VERSION 3.16)
set(CMAKE_ASC_ARCHITECTURES "dav-3510" CACHE STRING "NPU architecture")
find_package(ASC REQUIRED)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
project(asc_stl_parallel_algorithms LANGUAGES ASC CXX)
set(ASC_STL_EXAMPLE_STANDARD 17 CACHE STRING "C++ standard (17 or20)")
if(NOT ASC_STL_EXAMPLE_STANDARD MATCHES "^(17|20)$")
    message(FATAL_ERROR "ASC_STL_EXAMPLE_STANDARD must be17 or20")
endif()
set(ASC_STL_INCLUDE_DIR "" CACHE PATH "ASC-STL include directory")
# The CANN pure-SIMT runtime emits strong launch/registration definitions per TU.
# The grouped ASC files are textual inputs of parallel_cases.asc, not separate TUs.
add_executable(asc_stl_parallel_algorithms main.cpp parallel_cases.asc)
set_target_properties(asc_stl_parallel_algorithms PROPERTIES LINKER_LANGUAGE ASC CXX_EXTENSIONS OFF)
target_compile_features(asc_stl_parallel_algorithms PRIVATE cxx_std_${ASC_STL_EXAMPLE_STANDARD})
target_compile_definitions(asc_stl_parallel_algorithms PRIVATE CANN_ASC_STL_USE_SIMT_LAUNCH=1)
target_compile_options(asc_stl_parallel_algorithms PRIVATE
    $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES} --enable-simt
        -std=c++${ASC_STL_EXAMPLE_STANDARD} -Werror -Wno-error=ignored-attributes>)
target_include_directories(asc_stl_parallel_algorithms PRIVATE "${ASC_STL_INCLUDE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}" "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc"
    "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc/include" "$ENV{ASCEND_HOME_PATH}/include")
find_library(ascendcl_library ascendcl HINTS "$ENV{ASCEND_HOME_PATH}/lib64")
if(NOT ascendcl_library)
    message(FATAL_ERROR "The configured CANN Runtime library ascendcl is required")
endif()
target_link_libraries(asc_stl_parallel_algorithms PRIVATE "${ascendcl_library}")
