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
#include <asc/std/scoped_allocator>
#include <asc/std/type_traits>

struct basic_allocator {
    using value_type = int;
    using pointer = int*;
    using size_type = __SIZE_TYPE__;
    using difference_type = __PTRDIFF_TYPE__;
    template <class>
    struct rebind {
        using other = basic_allocator;
    };
};

struct outer_allocator : basic_allocator {
    int identity = 0;
    using propagate_on_container_copy_assignment = asc::std::true_type;
    using propagate_on_container_move_assignment = asc::std::false_type;
    using propagate_on_container_swap = asc::std::false_type;
    using is_always_equal = asc::std::true_type;
};

struct inner_allocator : basic_allocator {
    int identity = 0;
    using propagate_on_container_copy_assignment = asc::std::false_type;
    using propagate_on_container_move_assignment = asc::std::true_type;
    using propagate_on_container_swap = asc::std::true_type;
    using is_always_equal = asc::std::false_type;
};

int main()
{
    using traits = asc::std::allocator_traits<basic_allocator>;
    // 无嵌套声明时，三个传播特征默认为 false；空分配器的 is_always_equal 为 true。
    static_assert(!traits::propagate_on_container_copy_assignment::value);
    static_assert(!traits::propagate_on_container_move_assignment::value);
    static_assert(!traits::propagate_on_container_swap::value);
    static_assert(traits::is_always_equal::value);

    using nested = asc::std::scoped_allocator_adaptor<outer_allocator, inner_allocator>;
    static_assert(asc::std::is_same_v<nested::outer_allocator_type, outer_allocator>);
    static_assert(
        asc::std::is_same_v<nested::inner_allocator_type, asc::std::scoped_allocator_adaptor<inner_allocator>>);
    // Query each allocator explicitly; the current adaptor does not merge propagation traits.
    using outer_traits = asc::std::allocator_traits<outer_allocator>;
    using inner_traits = asc::std::allocator_traits<inner_allocator>;
    static_assert(outer_traits::propagate_on_container_copy_assignment::value);
    static_assert(!outer_traits::propagate_on_container_move_assignment::value);
    static_assert(!outer_traits::propagate_on_container_swap::value);
    static_assert(outer_traits::is_always_equal::value);
    static_assert(inner_traits::propagate_on_container_move_assignment::value);
    static_assert(inner_traits::propagate_on_container_swap::value);
    static_assert(!inner_traits::is_always_equal::value);

    nested allocator;
    allocator.outer_allocator().identity = 7;
    allocator.inner_allocator().outer_allocator().identity = 9;
    const nested& view = allocator;
    return view.outer_allocator().identity == 7 && view.inner_allocator().outer_allocator().identity == 9 ? 0 : 1;
}
