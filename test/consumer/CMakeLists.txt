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

project(asc_stl_installed_consumer LANGUAGES CXX)

find_package(asc_stl CONFIG REQUIRED)

add_executable(
    asc_stl_installed_consumer
    main.cpp
    type_traits_a.cpp
    type_traits_b.cpp
    core_a.cpp
    core_b.cpp
    vocabulary_a.cpp
    vocabulary_b.cpp
    type_transform_a.cpp
    type_transform_b.cpp
    constructibility_a.cpp
    constructibility_b.cpp
    execution_properties_a.cpp
    execution_properties_b.cpp
    concepts_limits_a.cpp
    concepts_limits_b.cpp
    memory_a.cpp
    memory_b.cpp
    b016_a.cpp
    b016_b.cpp
    b017_a.cpp
    b017_b.cpp
    b018_a.cpp
    b018_b.cpp
    b019_a.cpp
    b019_b.cpp
)
target_link_libraries(asc_stl_installed_consumer PRIVATE asc_stl::asc_stl)
target_compile_options(asc_stl_installed_consumer PRIVATE -Wall -Wextra -Werror -pedantic)
