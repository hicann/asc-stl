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
project(asc_stl_ranges_hardware LANGUAGES ASC CXX)
set(ASC_STL_INCLUDE_DIR "" CACHE PATH "ASC-STL include directory")
set(ASC_STL_CXX_STANDARD "17" CACHE STRING "C++ language mode")
add_executable(asc_stl_ranges_simt ../kernel.asc ../main.cpp)
set_target_properties(asc_stl_ranges_simt PROPERTIES LINKER_LANGUAGE ASC CXX_STANDARD ${ASC_STL_CXX_STANDARD})
# The AIV wrapper uses kernel_operator.h and invokes SIMT VFs through asc_vf_call.
# Do not enable pure-SIMT mode (--enable-simt), which rejects kernel_operator.h.
target_compile_options(asc_stl_ranges_simt PRIVATE $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES} -std=c++${ASC_STL_CXX_STANDARD} -Werror -Wno-error=deprecated-volatile -Wno-error=ignored-attributes>)
target_include_directories(asc_stl_ranges_simt PRIVATE "${ASC_STL_INCLUDE_DIR}" "${ASC_STL_INCLUDE_DIR}/../test" "$ENV{ASCEND_HOME_PATH}/include")
target_link_directories(asc_stl_ranges_simt PRIVATE "$ENV{ASCEND_HOME_PATH}/lib64")
target_link_libraries(asc_stl_ranges_simt PRIVATE ascendcl)
target_compile_definitions(asc_stl_ranges_simt PRIVATE ASC_STL_RANGES_HARDWARE=1)
