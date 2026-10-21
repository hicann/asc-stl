/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ASC_STL_TEST_B027_STAGE_API_H
#define ASC_STL_TEST_B027_STAGE_API_H
#include <acl/acl.h>
namespace asc_stl_b027_staged {
struct stage_result {
    unsigned code;
    unsigned allocations;
    unsigned deallocations;
    unsigned used;
    unsigned allocation_sizes[3];
    unsigned sso_allocations;
    unsigned sso_deallocations;
};
using launcher = void (*)(stage_result*, char*, void*, void*, aclrtStream);
}  // namespace asc_stl_b027_staged
#define ASC_STL_B027_STAGE(name) \
    extern "C" void asc_stl_b027_launch_##name(asc_stl_b027_staged::stage_result*, char*, void*, void*, aclrtStream);
#include "stage_table.def"
#undef ASC_STL_B027_STAGE
#endif  // ASC_STL_TEST_B027_STAGE_API_H
