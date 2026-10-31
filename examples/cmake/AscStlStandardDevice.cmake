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

function(asc_stl_add_standard_device_example name)
    set(common "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../common")
    add_executable(asc_stl_${name}_device
        "${common}/standard_device_main.cpp" "${common}/standard_kernel.asc")
    set_target_properties(asc_stl_${name}_device PROPERTIES LINKER_LANGUAGE ASC)
    asc_stl_configure_host_example(asc_stl_${name}_device)
    target_compile_definitions(asc_stl_${name}_device PRIVATE
        ASC_STL_EXAMPLE_NAME="${name}" ASC_STL_EXAMPLE_LANGUAGE=${ASC_STL_EXAMPLE_STANDARD})
    target_compile_options(asc_stl_${name}_device PRIVATE
        $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES} --enable-simt
            -std=c++${ASC_STL_EXAMPLE_STANDARD} -Werror -Wno-error=ignored-attributes>)
    target_include_directories(asc_stl_${name}_device PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}" "${common}" "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc"
        "${ASCEND_CANN_PACKAGE_LINUX_PATH}/asc/include" "$ENV{ASCEND_HOME_PATH}/include")
    find_library(ASC_STL_EXAMPLE_ACL_LIBRARY ascendcl HINTS "$ENV{ASCEND_HOME_PATH}/lib64")
    if(NOT ASC_STL_EXAMPLE_ACL_LIBRARY)
        message(FATAL_ERROR "CANN Runtime libascendcl is required for Device examples")
    endif()
    target_link_libraries(asc_stl_${name}_device PRIVATE "${ASC_STL_EXAMPLE_ACL_LIBRARY}")
endfunction()
