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
    add_test(NAME compatibility.extension-type-traits.host
        COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/test_extension_type_traits_contract.py
                --compiler ${CMAKE_CXX_COMPILER}
                --report ${CMAKE_CURRENT_BINARY_DIR}/type-traits-host.json)
    set_tests_properties(compatibility.extension-type-traits.host
        PROPERTIES LABELS "static-rules;affected-regression;nightly" TIMEOUT 180)
endif()
if(ASC_STL_ENABLE_DEVICE_COMPILE_TESTS)
    foreach(mode IN ITEMS simd simt)
        add_test(NAME compatibility.extension-type-traits.${mode}
            COMMAND ${Python3_EXECUTABLE} ${ASC_STL_TEST_ROOT}/scripts/test_extension_type_traits_contract.py
                    --compiler bisheng --mode ${mode} --npu-arch ${ASC_STL_NPU_ARCH}
                    --report ${CMAKE_CURRENT_BINARY_DIR}/type-traits-${mode}.json)
        set_tests_properties(compatibility.extension-type-traits.${mode}
            PROPERTIES LABELS "header-device;device-compile;affected-regression;nightly" TIMEOUT 300)
    endforeach()
endif()
