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
project(asc_stl_foundation_cannsim LANGUAGES CXX)
set(ASC_STL_CXX_STANDARD "17" CACHE STRING "C++ language mode")
set(CMAKE_CXX_STANDARD ${ASC_STL_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(ASC_STL_INCLUDE_DIR "" CACHE PATH "ASC-STL include directory")
set(ASC_STL_TARGET_SOC "Ascend950PR_9599" CACHE STRING "AscendC target SoC")
set(ASCEND_CANN_PACKAGE_PATH "$ENV{ASCEND_HOME_PATH}" CACHE PATH "" FORCE)
set(SOC_VERSION "${ASC_STL_TARGET_SOC}" CACHE STRING "" FORCE)
set(RUN_MODE npu CACHE STRING "" FORCE)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/ascendc-install" CACHE PATH "" FORCE)
set(candidates "$ENV{ASCEND_HOME_PATH}/compiler/tikcpp/ascendc_kernel_cmake/ascendc.cmake"
               "$ENV{ASCEND_HOME_PATH}/tools/tikcpp/ascendc_kernel_cmake/ascendc.cmake")
foreach(candidate IN LISTS candidates)
    if(EXISTS "${candidate}")
        include("${candidate}")
        break()
    endif()
endforeach()
ascendc_library(asc_stl_foundation_cannsim_kernel SHARED kernel.cpp)
ascendc_compile_options(asc_stl_foundation_cannsim_kernel PRIVATE -std=c++${ASC_STL_CXX_STANDARD} -forward-options-to-host-compiler -std=c++${ASC_STL_CXX_STANDARD})
ascendc_compile_definitions(asc_stl_foundation_cannsim_kernel PRIVATE __ASCENDC_SUPER_KERNEL_ENABLE_GM_GET_SET_VALUE_DCCI__)
ascendc_include_directories(asc_stl_foundation_cannsim_kernel PRIVATE "${ASC_STL_INCLUDE_DIR}")
add_executable(asc_stl_foundation_cannsim launcher.cpp main.cpp)
target_link_libraries(asc_stl_foundation_cannsim PRIVATE host_intf_pub asc_stl_foundation_cannsim_kernel)
target_compile_options(asc_stl_foundation_cannsim PRIVATE -Wall -Wextra -Werror)
