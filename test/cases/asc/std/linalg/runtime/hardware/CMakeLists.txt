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
project(asc_stl_w13_w14_hardware LANGUAGES ASC CXX)
set(ASC_STL_CXX_STANDARD "17" CACHE STRING "C++ language mode")
set(ASC_STL_INCLUDE_DIR "" CACHE PATH "ASC-STL include directory")
foreach(mode IN ITEMS simd simt)
    add_executable(asc_stl_w13_w14_${mode} kernel_${mode}.asc main.cpp)
    set_target_properties(asc_stl_w13_w14_${mode} PROPERTIES LINKER_LANGUAGE ASC)
    target_compile_features(asc_stl_w13_w14_${mode} PRIVATE cxx_std_${ASC_STL_CXX_STANDARD})
    target_compile_options(asc_stl_w13_w14_${mode} PRIVATE
        $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES} -std=c++${ASC_STL_CXX_STANDARD} -Werror>)
    if(mode STREQUAL "simt")
        target_compile_options(asc_stl_w13_w14_${mode} PRIVATE $<$<COMPILE_LANGUAGE:ASC>:--enable-simt -Wno-error=ignored-attributes>)
        target_compile_definitions(asc_stl_w13_w14_${mode} PRIVATE ASC_STL_W13_W14_SIMT=1)
    else()
        target_compile_definitions(asc_stl_w13_w14_${mode} PRIVATE ASC_STL_W13_W14_SIMD=1)
    endif()
    target_include_directories(asc_stl_w13_w14_${mode} PRIVATE "${ASC_STL_INCLUDE_DIR}"
        "${CMAKE_CURRENT_LIST_DIR}/../../../../../.."
        "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc" "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc/include"
        "$ENV{ASCEND_HOME_PATH}/include")
endforeach()

foreach(diagnostic IN ITEMS common_only sync_only)
    add_executable(asc_stl_w13_w14_${diagnostic} kernel_simt.asc main.cpp)
    set_target_properties(asc_stl_w13_w14_${diagnostic} PROPERTIES LINKER_LANGUAGE ASC)
    target_compile_features(asc_stl_w13_w14_${diagnostic} PRIVATE cxx_std_${ASC_STL_CXX_STANDARD})
    target_compile_options(asc_stl_w13_w14_${diagnostic} PRIVATE
        $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES} --enable-simt -Wno-error=ignored-attributes
        -std=c++${ASC_STL_CXX_STANDARD} -Werror>)
    string(TOUPPER ${diagnostic} diagnostic_macro)
    target_compile_definitions(asc_stl_w13_w14_${diagnostic} PRIVATE ASC_STL_W13_W14_${diagnostic_macro}=1)
    target_include_directories(asc_stl_w13_w14_${diagnostic} PRIVATE "${ASC_STL_INCLUDE_DIR}"
        "${CMAKE_CURRENT_LIST_DIR}/../../../../../.."
        "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc" "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc/include"
        "$ENV{ASCEND_HOME_PATH}/include")
endforeach()
