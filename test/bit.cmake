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
    set(bit_runtime_build "${CMAKE_CURRENT_BINARY_DIR}/bit-runtime")
    add_custom_target(asc_stl_bit_runtime
        COMMAND ${CMAKE_COMMAND} -S "${ASC_STL_CASES_ROOT}/asc/bit/runtime" -B "${bit_runtime_build}"
                -DASC_STL_INCLUDE_DIR=${ASC_STL_INCLUDE_ROOT}
                -DASC_STL_CXX_STANDARD=${ASC_STL_TEST_CXX_STANDARD}
                -DASC_STL_BIT_SIMULATION=ON -DCMAKE_BUILD_TYPE=Release
        COMMAND ${CMAKE_COMMAND} --build "${bit_runtime_build}" -j2)
    add_dependencies(asc_stl_cannsim_tests asc_stl_bit_runtime)
    foreach(mode IN ITEMS simd simt)
        add_test(NAME runtime.cannsim.bit.${mode}
            COMMAND bash "${ASC_STL_TEST_ROOT}/scripts/run_cannsim_test.sh"
                    "${ASC_STL_CANNSIM_EXECUTABLE}" "${bit_runtime_build}/asc_stl_bit_${mode}"
                    "${ASC_STL_CANNSIM_SOC}" "${CMAKE_CURRENT_BINARY_DIR}/bit-${mode}-results"
                    "${ASC_STL_CANN_PACKAGE_PATH}/lib64" "ASC_STL_BIT_RUNTIME_PASS")
        set_tests_properties(runtime.cannsim.bit.${mode}
            PROPERTIES LABELS "cannsim-runtime;affected-regression;nightly" TIMEOUT ${ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS}
                       FIXTURES_REQUIRED asc_stl_cannsim_ready RUN_SERIAL TRUE)
    endforeach()
endif()
