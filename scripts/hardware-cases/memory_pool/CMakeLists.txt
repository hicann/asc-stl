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
project(asc_stl_b025_memory_pool_hardware LANGUAGES CXX)

set(ASC_STL_INCLUDE_DIR "" CACHE PATH "ASC-STL include directory")
set(ASC_STL_CXX_STANDARD "17" CACHE STRING "C++ language mode")
if(NOT EXISTS "${ASC_STL_INCLUDE_DIR}/asc/memory_pool")
    message(FATAL_ERROR "ASC_STL_INCLUDE_DIR must name an installed ASC-STL include tree")
endif()

find_library(
    ASCENDCL_LIBRARY
    NAMES ascendcl
    HINTS "$ENV{ASCEND_HOME_PATH}/lib64" "$ENV{ASCEND_HOME_PATH}/lib"
    REQUIRED)

add_executable(asc_stl_b025_memory_pool main.cpp)
target_compile_features(asc_stl_b025_memory_pool PRIVATE cxx_std_${ASC_STL_CXX_STANDARD})
target_compile_options(asc_stl_b025_memory_pool PRIVATE -Werror)
target_include_directories(asc_stl_b025_memory_pool PRIVATE "${ASC_STL_INCLUDE_DIR}" "$ENV{ASCEND_HOME_PATH}/include")
target_link_libraries(asc_stl_b025_memory_pool PRIVATE "${ASCENDCL_LIBRARY}")
