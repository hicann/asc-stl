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

if(ASC_STL_ENABLE_HOST_TESTS)
    foreach(standard IN ITEMS 17 20)
        set(target "asc_stl_random_oracle_cxx${standard}")
        add_executable(${target} "${ASC_STL_CASES_ROOT}/asc/random/oracle.cpp")
        target_link_libraries(${target} PRIVATE asc_stl::asc_stl)
        set_target_properties(${target} PROPERTIES
            CXX_STANDARD ${standard} CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
        target_compile_options(${target} PRIVATE -Wall -Wextra -Werror -pedantic)
        add_test(NAME semantic.host.cxx${standard}.asc.random.reference
            COMMAND ${Python3_EXECUTABLE} "${ASC_STL_CASES_ROOT}/asc/random/reference.py"
                    --executable $<TARGET_FILE:${target}>)
        set_tests_properties(semantic.host.cxx${standard}.asc.random.reference PROPERTIES
            LABELS "semantic-host;affected-regression;nightly" TIMEOUT 90)
    endforeach()
endif()

if(ASC_STL_ENABLE_CANNSIM_TESTS)
    set(random_build "${CMAKE_CURRENT_BINARY_DIR}/random-runtime")
    add_custom_target(asc_stl_random_runtime
        COMMAND ${CMAKE_COMMAND} -S "${ASC_STL_CASES_ROOT}/asc/random/runtime" -B "${random_build}"
                -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
                -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
                -DASC_STL_RANDOM_SIMULATION=ON -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build "${random_build}" -j2)
    add_dependencies(asc_stl_cannsim_tests asc_stl_random_runtime)
    foreach(mode IN ITEMS simd simt)
        if(mode STREQUAL "simt")
            set(seed_groups 0 1 2 3 4 5)
        else()
            set(seed_groups all)
        endif()
        foreach(seed IN LISTS seed_groups)
            set(test_name runtime.cannsim.random.${mode}.${seed})
            add_test(NAME ${test_name}
                COMMAND bash "${ASC_STL_TEST_ROOT}/scripts/run_cannsim_test.sh"
                        "${ASC_STL_CANNSIM_EXECUTABLE}" "${random_build}/asc_stl_random_${mode}"
                        "${ASC_STL_CANNSIM_SOC}" "${CMAKE_CURRENT_BINARY_DIR}/random-${mode}-${seed}-results"
                        "${ASC_STL_CANN_PACKAGE_PATH}/lib64" "ASC_STL_RANDOM_RUNTIME_PASS")
            set_tests_properties(${test_name} PROPERTIES
                LABELS "cannsim-runtime;affected-regression;nightly" TIMEOUT ${ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS}
                FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
            if(mode STREQUAL "simt")
                # Keep all 54 vectors, split by seed to bound SIMT emulation cost.
                set_tests_properties(${test_name} PROPERTIES ENVIRONMENT "ASC_STL_RANDOM_SEED_INDEX=${seed}")
            endif()
        endforeach()
    endforeach()
endif()
