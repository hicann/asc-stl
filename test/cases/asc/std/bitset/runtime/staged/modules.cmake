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

# Each semantic stage owns one ASC TU and one independently registered module.
set(ASC_STL_B027_STAGE_DIR "${CMAKE_CURRENT_LIST_DIR}")
function(asc_stl_b027_staged_target target hardware)
    file(STRINGS "${ASC_STL_B027_STAGE_DIR}/stage_table.def" stage_rows REGEX "^ASC_STL_B027_STAGE[(]")
    foreach(row IN LISTS stage_rows)
        string(REGEX MATCH "[a-z]+" stage "${row}")
        set(module asc_stl_b027_${stage}_module)
        set(source "${ASC_STL_B027_STAGE_DIR}/${stage}.cpp")
        set_source_files_properties("${source}" PROPERTIES LANGUAGE ASC)
        add_library(${module} SHARED "${source}")
        set_target_properties(${module} PROPERTIES LINKER_LANGUAGE ASC)
        target_compile_options(${module} PRIVATE $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES} --enable-simt -std=c++${ASC_STL_CXX_STANDARD} -Werror -Wno-error=ignored-attributes>)
        target_include_directories(${module} PRIVATE "${ASC_STL_INCLUDE_DIR}" "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc" "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc/include" "$ENV{ASCEND_HOME_PATH}/include")
        set(exports "${CMAKE_CURRENT_BINARY_DIR}/exports-${stage}.map")
        file(WRITE "${exports}" "{
 global: asc_stl_b027_launch_${stage};
 local: *;
};
")
        target_link_options(${module} PRIVATE "-Wl,--version-script=${exports}")
    endforeach()
    add_executable(${target} "${ASC_STL_B027_STAGE_DIR}/main.cpp")
    target_compile_features(${target} PRIVATE cxx_std_${ASC_STL_CXX_STANDARD})
    target_compile_definitions(${target} PRIVATE ASC_STL_B027_MODULE_DIR="${CMAKE_CURRENT_BINARY_DIR}" ASC_STL_B027_HARDWARE=${hardware})
    target_include_directories(${target} PRIVATE "${ASC_STL_INCLUDE_DIR}" "$ENV{ASCEND_HOME_PATH}/include")
    target_link_directories(${target} PRIVATE "$ENV{ASCEND_HOME_PATH}/lib64")
    target_link_libraries(${target} PRIVATE ascendcl dl)
    # Keep the inherited Host runtime path while allowing cannsim to select camodel.
    set_target_properties(${target} PROPERTIES SKIP_BUILD_RPATH TRUE)
    foreach(row IN LISTS stage_rows)
        string(REGEX MATCH "[a-z]+" stage "${row}")
        add_dependencies(${target} asc_stl_b027_${stage}_module)
    endforeach()
endfunction()
