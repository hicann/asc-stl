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
project(asc_stl_stream_event_example LANGUAGES CXX)
include(../../cmake/AscStlExample.cmake)
find_path(ASC_STL_ACL_INCLUDE_DIR acl/acl.h HINTS "$ENV{ASCEND_HOME_PATH}/include")
find_library(ASC_STL_ACL_LIBRARY ascendcl HINTS "$ENV{ASCEND_HOME_PATH}/lib64")
if(NOT ASC_STL_ACL_INCLUDE_DIR OR NOT ASC_STL_ACL_LIBRARY)
    message(FATAL_ERROR "Source CANN set_env.sh: acl/acl.h and libascendcl are required")
endif()
add_executable(asc_stl_stream_event main.cpp)
asc_stl_configure_host_example(asc_stl_stream_event)
target_include_directories(asc_stl_stream_event PRIVATE "${ASC_STL_ACL_INCLUDE_DIR}")
target_link_libraries(asc_stl_stream_event PRIVATE "${ASC_STL_ACL_LIBRARY}")
# Runtime examples execute only when the user explicitly launches the program.
