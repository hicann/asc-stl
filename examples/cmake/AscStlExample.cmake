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

include_guard(GLOBAL)

set(ASC_STL_EXAMPLE_STANDARD 17 CACHE STRING "Example C++ standard (17 or 20)")
set_property(CACHE ASC_STL_EXAMPLE_STANDARD PROPERTY STRINGS 17 20)
if(NOT ASC_STL_EXAMPLE_STANDARD MATCHES "^(17|20)$")
    message(FATAL_ERROR "ASC_STL_EXAMPLE_STANDARD must be 17 or 20")
endif()
get_filename_component(default_include "${CMAKE_CURRENT_LIST_DIR}/../../include" ABSOLUTE)
set(ASC_STL_INCLUDE_DIR "${default_include}" CACHE PATH "ASC-STL include directory")
if(NOT EXISTS "${ASC_STL_INCLUDE_DIR}/asc/std/algorithm")
    message(FATAL_ERROR "ASC_STL_INCLUDE_DIR must name the ASC-STL include tree")
endif()

function(asc_stl_configure_host_example target)
    target_include_directories(${target} PRIVATE "${ASC_STL_INCLUDE_DIR}")
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD ${ASC_STL_EXAMPLE_STANDARD}
        CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
endfunction()

function(asc_stl_add_host_example name)
    set(sources ${ARGN})
    if(NOT sources)
        set(sources main.cpp)
    endif()
    add_executable(asc_stl_${name} ${sources})
    asc_stl_configure_host_example(asc_stl_${name})
    target_include_directories(asc_stl_${name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
    if(BUILD_TESTING)
        add_test(NAME examples.standard.${name} COMMAND asc_stl_${name})
        set_tests_properties(examples.standard.${name} PROPERTIES LABELS "examples;host" TIMEOUT 30)
    endif()
endfunction()
