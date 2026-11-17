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
set(CMAKE_ASC_ARCHITECTURES "dav-3510" CACHE STRING "NPU architecture")
find_package(ASC REQUIRED)
project(asc_stl_numeric_types_runtime LANGUAGES ASC CXX)
set(ASC_STL_CXX_STANDARD "17" CACHE STRING "C++ language mode")
set(ASC_STL_INCLUDE_DIR "" CACHE PATH "ASC-STL include directory")
option(ASC_STL_NUMERIC_TYPES_SIMULATION "Build the cannsim entry instead of the hardware entry" OFF)
foreach(mode IN ITEMS simd simt)
    add_executable(asc_stl_numeric_types_${mode} kernel_${mode}.asc main.cpp)
    set_target_properties(asc_stl_numeric_types_${mode} PROPERTIES LINKER_LANGUAGE CXX)
    target_link_directories(asc_stl_numeric_types_${mode} PRIVATE "$ENV{ASCEND_HOME_PATH}/lib64")
    target_link_libraries(asc_stl_numeric_types_${mode} PRIVATE ascendc_runtime ascendcl runtime register error_manager profapi
        ge_common_base unified_dlog mmpa dl ascend_dump c_sec)
    if(ASC_STL_NUMERIC_TYPES_SIMULATION)
        target_compile_definitions(asc_stl_numeric_types_${mode} PRIVATE ASC_STL_NUMERIC_TYPES_SIMULATION=1)
    endif()
    target_compile_features(asc_stl_numeric_types_${mode} PRIVATE cxx_std_${ASC_STL_CXX_STANDARD})
    target_compile_options(asc_stl_numeric_types_${mode} PRIVATE
        $<$<COMPILE_LANGUAGE:ASC>:--asc-aicore-lang --npu-arch=dav-3510 -std=c++${ASC_STL_CXX_STANDARD} -O2 -fno-fast-math -Werror>)
    if(mode STREQUAL "simt")
        target_compile_options(asc_stl_numeric_types_${mode} PRIVATE
            $<$<COMPILE_LANGUAGE:ASC>:--enable-simt -Wno-error=ignored-attributes>)
    endif()
    target_include_directories(asc_stl_numeric_types_${mode} PRIVATE
        "${ASC_STL_INCLUDE_DIR}" "$ENV{ASCEND_HOME_PATH}/include")
endforeach()
