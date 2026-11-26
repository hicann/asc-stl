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

#ifndef ASC_STL_TEST_SCOPED_ALLOCATOR_DEVICE_CHECKS_H
#define ASC_STL_TEST_SCOPED_ALLOCATOR_DEVICE_CHECKS_H

#include <asc/std/scoped_allocator>

namespace asc_stl_test_scoped_allocator {
template <class T>
struct local {
    using value_type = T;
    using pointer = T*;
    using size_type = __SIZE_TYPE__;
    using difference_type = __PTRDIFF_TYPE__;
    template <class U>
    struct rebind {
        using other = local<U>;
    };

    int id = 0;
    pointer buffer = nullptr;
    int* balance = nullptr;
    CANN_ASC_STL_API pointer allocate(size_type n)
    {
        *balance += static_cast<int>(n);
        return buffer;
    }
    CANN_ASC_STL_API void deallocate(pointer, size_type n)
    {
        *balance -= static_cast<int>(n);
    }
    CANN_ASC_STL_API size_type max_size() const
    {
        return 1;
    }
    CANN_ASC_STL_API bool operator==(const local& other) const
    {
        return id == other.id;
    }
};
CANN_ASC_STL_API int check(int seed = 7)
{
    using alloc = local<int>;
    using single = asc::std::scoped_allocator_adaptor<alloc>;
    using nested = asc::std::scoped_allocator_adaptor<alloc, alloc>;
    alignas(int) unsigned char raw[sizeof(int)];
    auto* slot = reinterpret_cast<int*>(raw);
    int balance = 0;
    const alloc a{1, slot, &balance};
    const alloc b{2, slot, &balance};
    single outer(a);
    const single& c = outer;
    single from_temporary(alloc{1, slot, &balance});
    nested inner(a, b);
    const nested& ci = inner;
    if (c.max_size() != 1 || ci.max_size() != 1 || outer != from_temporary || !(inner == nested(a, b)) ||
        inner == nested(a, a) || c.outer_allocator().id != 1 || &outer.inner_allocator() != &outer ||
        &c.inner_allocator() != &outer || ci.outer_allocator().id != 1 ||
        ci.inner_allocator().outer_allocator().id != 2 || inner.inner_allocator().outer_allocator().id != 2)
        return 1;
    int* p = outer.allocate(1);
    outer.construct(p, seed + 4);
    if (p != slot || *p != 11 || balance != 1)
        return 2;
    outer.destroy(p);
    outer.deallocate(p, 1);
    p = inner.allocate(1);
    inner.construct(p, -4);
    if (*p != -4 || balance != 1)
        return 3;
    inner.destroy(p);
    inner.deallocate(p, 1);
    return balance == 0 ? 0 : 4;
}
}  // namespace asc_stl_test_scoped_allocator

#endif  // ASC_STL_TEST_SCOPED_ALLOCATOR_DEVICE_CHECKS_H
