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

function(asc_stl_add_host_header_test test_name header_id header)
    set(HEADER "${header}")
    set(output_dir "${CMAKE_CURRENT_BINARY_DIR}/generated/header_host")
    set(source "${output_dir}/${header_id}.cpp")
    file(MAKE_DIRECTORY "${output_dir}")
    configure_file("${ASC_STL_HEADER_HOST_TEMPLATE}" "${source}" @ONLY)

    set(target "asc_stl_header_host_${header_id}")
    add_executable("${target}" "${source}")
    target_link_libraries("${target}" PRIVATE asc_stl::asc_stl)
    if(MSVC)
        target_compile_options("${target}" PRIVATE /W4 /WX)
    else()
        target_compile_options("${target}" PRIVATE -Wall -Wextra -Werror)
    endif()

    add_test(NAME "${test_name}" COMMAND "${target}")
    set_tests_properties(
        "${test_name}"
        PROPERTIES LABELS "header-host;affected-regression;nightly"
    )
endfunction()
