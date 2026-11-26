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


if(ASC_STL_ENABLE_CANNSIM_TESTS)
    foreach(mode IN ITEMS simd simt)
        set(build_dir "${CMAKE_CURRENT_BINARY_DIR}/standard-${mode}-cannsim")
        add_custom_target(asc_stl_standard_${mode}_cannsim_build
            COMMAND ${CMAKE_COMMAND}
                -S "${ASC_STL_CASES_ROOT}/asc/std/array/runtime/cannsim" -B "${build_dir}"
                -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
                -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
                -DASC_STL_STANDARD_RUNTIME_MODE=${mode}
                -DCMAKE_BUILD_TYPE=Release
            COMMAND ${CMAKE_COMMAND} --build "${build_dir}" -j2
            VERBATIM)
        add_dependencies(asc_stl_cannsim_tests asc_stl_standard_${mode}_cannsim_build)
        set(standard_groups core)
        if(mode STREQUAL "simt")
            list(APPEND standard_groups sequences ordered_set unordered_set unordered_map scoped_allocator adaptors synchronization)
        endif()
        foreach(group IN LISTS standard_groups)
            set(application asc_stl_standard_cannsim)
            if(NOT group STREQUAL "core")
                set(application asc_stl_standard_profiles_cannsim)
            endif()
            set(test_name semantic.cannsim.asc.std.standard.${mode}.${group})
            add_test(NAME ${test_name}
                COMMAND "${ASC_STL_TEST_ROOT}/scripts/run_cannsim_test.sh"
                    "${ASC_STL_CANNSIM_EXECUTABLE}" "${build_dir}/${application}"
                    "${ASC_STL_CANNSIM_SOC}" "${CMAKE_CURRENT_BINARY_DIR}/cannsim-results/standard-${mode}-${group}"
                    "${build_dir}" "ASC_STL_STANDARD_RUNTIME_PASS ${group}")
            set_tests_properties(${test_name} PROPERTIES
                ENVIRONMENT "ASC_STL_STANDARD_RUNTIME_CASE=${group}"
                LABELS "cannsim-runtime;affected-regression;nightly"
                FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE
                TIMEOUT ${ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS})
        endforeach()
    endforeach()
endif()
