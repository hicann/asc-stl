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

#include <asc/std/memory>

#include <memory>
#include <type_traits>

namespace {
struct counting : std::allocator<int> {
    using value_type = int;
    const void* expected_hint = nullptr;
    bool saw_hint = false;
    int constructs = 0;
    int destroys = 0;
    int identity = 7;
    int* allocate(std::size_t n)
    {
        return std::allocator<int>::allocate(n);
    }
    int* allocate(std::size_t n, const void* hint)
    {
        saw_hint = hint == expected_hint;
        return allocate(n);
    }
    asc::std::allocation_result<int*> allocate_at_least(std::size_t n)
    {
        return {allocate(n + 1), n + 1};
    }
    void construct(int* p, int x)
    {
        ++constructs;
        ::new (static_cast<void*>(p)) int{x + 1};
    }
    void destroy(int* p)
    {
        ++destroys;
        using T = int;
        p->~T();
    }
    std::size_t max_size() const
    {
        return 31;
    }
    counting select_on_container_copy_construction() const
    {
        auto copy = *this;
        ++copy.identity;
        return copy;
    }
};
}  // namespace

int main()
{
    using traits = asc::std::allocator_traits<counting>;
    static_assert(std::is_same_v<traits::value_type, int> && std::is_same_v<traits::pointer, int*>);
    counting alloc;
    alloc.expected_hint = &alloc;
    auto* p = traits::allocate(alloc, 1, &alloc);
    traits::construct(alloc, p, 7);
    const bool customized = alloc.saw_hint && alloc.constructs == 1 && *p == 8 && traits::max_size(alloc) == 31 &&
        traits::select_on_container_copy_construction(alloc).identity == 8;
    traits::destroy(alloc, p);
    traits::deallocate(alloc, p, 1);
    auto expanded = asc::std::allocate_at_least(alloc, 4);
    alloc.deallocate(expanded.ptr, expanded.count);
    if (!customized || alloc.destroys != 1 || expanded.count != 5)
        return 1;
    using plain = std::allocator<int>;
    using fallback = asc::std::allocator_traits<plain>;
    plain ordinary;
    auto exact = asc::std::allocate_at_least(ordinary, 2);
    fallback::construct(ordinary, exact.ptr, 4);
    const bool normal = exact.count >= 2 && *exact.ptr == 4 && fallback::max_size(ordinary) >= 2;
    fallback::destroy(ordinary, exact.ptr);
    fallback::deallocate(ordinary, exact.ptr, exact.count);
    return normal ? 0 : 2;
}
