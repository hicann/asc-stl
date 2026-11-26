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

#ifndef ASC_STL_TEST_NEW_DEVICE_CHECKS_H
#define ASC_STL_TEST_NEW_DEVICE_CHECKS_H

#include <asc/std/new>
#include <asc/std/type_traits>

namespace asc_stl_test_new {
struct record {
    const int value;
};
CANN_ASC_STL_API int check(int seed = 7)
{
    static_assert(asc::std::is_enum_v<asc::std::align_val_t>);
    static_assert(asc::std::is_same_v<decltype(asc::std::destroying_delete), const asc::std::destroying_delete_t>);
    static_assert(asc::std::is_same_v<decltype(asc::std::nothrow), const asc::std::nothrow_t>);
    alignas(record) unsigned char storage[sizeof(record)];
    auto* first = ::new (static_cast<void*>(storage)) record{2};
    first->~record();
    auto* second = ::new (static_cast<void*>(storage)) record{seed + 10};
    auto* p = asc::std::launder(first);
    const bool correct = p == second && p->value == 17;
    second->~record();
    return correct ? 0 : 1;
}
}  // namespace asc_stl_test_new

#endif  // ASC_STL_TEST_NEW_DEVICE_CHECKS_H
