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

#define CANN_ASC_STL_ENABLE_LEGACY_STD_FEATURE_MACROS 1
#include <asc/std/version>

int main()
{
    static_assert(__cpp_lib_source_location == 201907L);
    static_assert(__cpp_lib_unreachable == 202202L);
    static_assert(CANN_ASC_STL_HAS_SOURCE_LOCATION && CANN_ASC_STL_HAS_UNREACHABLE);
    return 0;
}
