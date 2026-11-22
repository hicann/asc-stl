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
    add_test(NAME compatibility.numeric-types.host
        COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/test_numeric_types_contract.py
                --compiler ${CMAKE_CXX_COMPILER})
    set_tests_properties(compatibility.numeric-types.host
        PROPERTIES LABELS "static-rules;affected-regression;nightly" TIMEOUT 180)
endif()
if(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS)
    foreach(mode IN ITEMS simd simt)
        add_test(NAME compatibility.numeric-types.${mode}
            COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/test_numeric_types_contract.py
                    --compiler bisheng --mode ${mode})
        set_tests_properties(compatibility.numeric-types.${mode}
            PROPERTIES LABELS "header-device;device-compile;affected-regression;nightly" TIMEOUT 300)
    endforeach()
endif()
if(ASC_STL_ENABLE_CANNSIM_TESTS)
    set(numeric_types_build "${CMAKE_CURRENT_BINARY_DIR}/numeric-types-runtime")
    add_custom_target(asc_stl_numeric_types_runtime
        COMMAND ${CMAKE_COMMAND} -S "${ASC_STL_CASES_ROOT}/asc/numeric_types/runtime" -B "${numeric_types_build}"
                -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
                -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
                -DASC_STL_NUMERIC_TYPES_SIMULATION=ON -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build "${numeric_types_build}" -j2)
    add_dependencies(asc_stl_cannsim_tests asc_stl_numeric_types_runtime)
    foreach(mode IN ITEMS simd simt)
        set(numeric_types_timeout ${ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS})
        if(mode STREQUAL "simt")
            # The SIMT conversion matrix can exceed the base budget on slower simulators.
            math(EXPR numeric_types_timeout "${ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS} * 3 / 2")
        endif()
        add_test(NAME runtime.cannsim.numeric-types.${mode}
            COMMAND bash "${ASC_STL_TEST_ROOT}/scripts/run_cannsim_test.sh"
                    "${ASC_STL_CANNSIM_EXECUTABLE}" "${numeric_types_build}/asc_stl_numeric_types_${mode}"
                    "${ASC_STL_CANNSIM_SOC}" "${CMAKE_CURRENT_BINARY_DIR}/numeric-types-${mode}-results"
                    "${ASC_STL_CANN_PACKAGE_PATH}/lib64" "ASC_STL_NUMERIC_TYPES_RUNTIME_PASS")
        set_tests_properties(runtime.cannsim.numeric-types.${mode}
            PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly" TIMEOUT ${numeric_types_timeout}
                       FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    endforeach()
endif()
