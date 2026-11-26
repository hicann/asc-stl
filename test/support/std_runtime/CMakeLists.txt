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
project(asc_stl_std_runtime LANGUAGES ASC CXX)
set(ASC_STL_CXX_STANDARD "17" CACHE STRING "C++ language mode")
option(ASC_STL_TEST_CANNSIM "Run with the CANN simulator" OFF)
set(ASC_STL_STD_MODE "simt" CACHE STRING "Device execution mode (simt or simd)")
if(ASC_STL_STD_MODE STREQUAL "simd")
    set(kernel_source simd_kernels.asc)
    set(check_name simd_checks.h)
    set(shared_headers bit compare ctime)
elseif(ASC_STL_STD_MODE STREQUAL "simt")
    set(kernel_source kernels.asc)
    set(check_name device_checks.h)
    set(mode_flag --enable-simt)
else()
    message(FATAL_ERROR "ASC_STL_STD_MODE must be simt or simd")
endif()
set(test_root "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(ASC_STL_STD_HEADERS "" CACHE STRING "Comma- or semicolon-separated header names; leave empty to run every device check")
string(REPLACE "," ";" ASC_STL_STD_HEADERS "${ASC_STL_STD_HEADERS}")
if(ASC_STL_STD_HEADERS)
    foreach(header IN LISTS ASC_STL_STD_HEADERS)
        set(check "${test_root}/cases/asc/std/${header}/${check_name}")
        if(header IN_LIST shared_headers)
            set(check "${test_root}/cases/asc/std/${header}/device_checks.h")
        endif()
        if(NOT EXISTS "${check}")
            message(FATAL_ERROR "No ${ASC_STL_STD_MODE} device check for asc/std/${header}")
        endif()
        list(APPEND checks "${check}")
    endforeach()
    list(REMOVE_DUPLICATES checks)
else()
    file(GLOB checks CONFIGURE_DEPENDS "${test_root}/cases/asc/std/*/${check_name}")
    foreach(header IN LISTS shared_headers)
        list(APPEND checks "${test_root}/cases/asc/std/${header}/device_checks.h")
    endforeach()
    list(SORT checks)
endif()
if(NOT checks)
    message(FATAL_ERROR "No per-header device checks found")
endif()
add_executable(asc_stl_std_runtime main.cpp ${kernel_source})
set_target_properties(asc_stl_std_runtime PROPERTIES LINKER_LANGUAGE ASC CXX_STANDARD ${ASC_STL_CXX_STANDARD})
set(registrations "")
set(includes "")
foreach(check IN LISTS checks)
    get_filename_component(directory "${check}" DIRECTORY)
    get_filename_component(header "${directory}" NAME)
    get_filename_component(filename "${check}" NAME)
    if(ASC_STL_STD_MODE STREQUAL "simt" AND header MATCHES "^(bitset|cmath|random)$")
        string(TOUPPER "${header}" partitioned_header)
        target_compile_definitions(asc_stl_std_runtime PRIVATE
            $<$<COMPILE_LANGUAGE:ASC>:ASC_STL_TEST_PARTITION_${partitioned_header}=1>)
    endif()
    string(APPEND includes "#include \"cases/asc/std/${header}/${filename}\"\n")
    string(APPEND registrations "ASC_STL_REGISTER_CHECK(${header})\n")
endforeach()
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/check_headers.inc" CONTENT "${includes}")
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/checks.inc" CONTENT "${registrations}")
target_include_directories(asc_stl_std_runtime PRIVATE
    "${test_root}" "${test_root}/../include" "${CMAKE_CURRENT_BINARY_DIR}"
    "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc" "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc/include" "$ENV{ASCEND_HOME_PATH}/include")
target_compile_options(asc_stl_std_runtime PRIVATE
    $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES} ${mode_flag} -std=c++${ASC_STL_CXX_STANDARD}
    -Werror -Wno-error=ignored-attributes>)
if(ASC_STL_TEST_CANNSIM)
    target_compile_definitions(asc_stl_std_runtime PRIVATE ASC_STL_TEST_CANNSIM=1)
endif()
