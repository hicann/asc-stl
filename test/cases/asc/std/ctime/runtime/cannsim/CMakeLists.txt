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
project(asc_stl_b021_cannsim LANGUAGES ASC CXX)
set(ASC_STL_CXX_STANDARD "17" CACHE STRING "C++ language mode")
set(CMAKE_CXX_STANDARD ${ASC_STL_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ASC_STL_INCLUDE_DIR "" CACHE PATH "ASC-STL include directory")
set_source_files_properties(kernel.cpp PROPERTIES LANGUAGE ASC)
add_executable(asc_stl_b021_cannsim kernel.cpp launcher.cpp main.cpp)
set_target_properties(asc_stl_b021_cannsim PROPERTIES LINKER_LANGUAGE ASC)
target_compile_options(asc_stl_b021_cannsim PRIVATE $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES} --enable-simt -std=c++${ASC_STL_CXX_STANDARD} -Werror -Wno-error=ignored-attributes>)
target_include_directories(asc_stl_b021_cannsim PRIVATE "${ASC_STL_INCLUDE_DIR}" "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc" "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc/include" "$ENV{ASCEND_HOME_PATH}/include")
