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

include(version.cmake)

project(asc_stl VERSION ${ASC_STL_VERSION} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CMakePackageConfigHelpers)

add_library(asc_stl INTERFACE)
add_library(asc_stl::asc_stl ALIAS asc_stl)

target_compile_features(asc_stl INTERFACE cxx_std_17)
target_include_directories(
    asc_stl
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

option(ASC_STL_BUILD_EXAMPLES "Build the user examples" OFF)
if(ASC_STL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

install(
    DIRECTORY include/
    DESTINATION include
    PATTERN ".*" EXCLUDE)
install(DIRECTORY docs/release/ DESTINATION share/asc_stl/docs/release)
install(FILES docs/zh/guide/product_version.md DESTINATION share/asc_stl/docs/zh/guide)
install(FILES docs/en/guide/product_version.md DESTINATION share/asc_stl/docs/en/guide)
install(TARGETS asc_stl EXPORT asc_stlTargets)
install(
    EXPORT asc_stlTargets
    FILE asc_stlTargets.cmake
    NAMESPACE asc_stl::
    DESTINATION lib/cmake/asc_stl)

configure_package_config_file(
    cmake/asc_stlConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/asc_stlConfig.cmake"
    INSTALL_DESTINATION lib/cmake/asc_stl)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/asc_stlConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/asc_stlConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/asc_stlConfigVersion.cmake"
    DESTINATION lib/cmake/asc_stl)
