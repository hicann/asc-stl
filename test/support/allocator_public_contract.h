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

#ifndef ASC_STL_TEST_ALLOCATOR_PUBLIC_CONTRACT_H
#define ASC_STL_TEST_ALLOCATOR_PUBLIC_CONTRACT_H

#include <asc/std/memory>
#include <asc/std/scoped_allocator>
#include <asc/std/type_traits>

namespace asc_stl_allocator_public_test {

struct plain_allocator {
    using value_type = int;
    using pointer = int*;
    using size_type = __SIZE_TYPE__;
    using difference_type = __PTRDIFF_TYPE__;
    template <class>
    struct rebind {
        using other = plain_allocator;
    };
};

struct stateful_allocator : plain_allocator {
    int state{};
};

struct source_outer_allocator : plain_allocator {
    int state{};
};

struct outer_allocator : plain_allocator {
    int state{};
    int constructions{};
    int destructions{};
    CANN_ASC_STL_API outer_allocator() = default;
    CANN_ASC_STL_API outer_allocator(const source_outer_allocator& source) : state(source.state)
    {}
    template <class T, class... Args>
    CANN_ASC_STL_API void construct(T* address, Args&&... args)
    {
        ++constructions;
        ::new (static_cast<void*>(address)) T(static_cast<Args&&>(args)...);
    }
    template <class T>
    CANN_ASC_STL_API void destroy(T* address)
    {
        ++destructions;
        address->~T();
    }
    using propagate_on_container_copy_assignment = asc::std::true_type;
    using propagate_on_container_move_assignment = asc::std::false_type;
    using propagate_on_container_swap = asc::std::false_type;
    using is_always_equal = asc::std::true_type;
    CANN_ASC_STL_API outer_allocator select_on_container_copy_construction() const
    {
        outer_allocator result = *this;
        result.state += 10;
        return result;
    }
};

struct inner_allocator : plain_allocator {
    int state{};
    using propagate_on_container_copy_assignment = asc::std::false_type;
    using propagate_on_container_move_assignment = asc::std::true_type;
    using propagate_on_container_swap = asc::std::true_type;
    using is_always_equal = asc::std::false_type;
    CANN_ASC_STL_API inner_allocator select_on_container_copy_construction() const
    {
        inner_allocator result = *this;
        result.state += 20;
        return result;
    }
};

struct allocator_aware_value {
    using allocator_type = inner_allocator;
    int value;
    CANN_ASC_STL_API allocator_aware_value(asc::std::allocator_arg_t, const inner_allocator& allocator, int input)
        : value(input + allocator.state)
    {}
};

struct trailing_allocator_aware_value {
    using allocator_type = inner_allocator;
    int value;
    CANN_ASC_STL_API trailing_allocator_aware_value(int input, const inner_allocator& allocator)
        : value(input + allocator.state)
    {}
};

struct allocating_allocator : plain_allocator {
    pointer storage{};
    CANN_ASC_STL_API pointer allocate(size_type)
    {
        return storage;
    }
    CANN_ASC_STL_API void deallocate(pointer, size_type) noexcept
    {}
    CANN_ASC_STL_API size_type max_size() const noexcept
    {
        return 4;
    }
};

struct bulk_allocator : allocating_allocator {
    CANN_ASC_STL_API asc::std::allocation_result<pointer, size_type> allocate_at_least(size_type count)
    {
        return {storage, count + 1};
    }
};

using plain_traits = asc::std::allocator_traits<plain_allocator>;
static_assert(!plain_traits::propagate_on_container_copy_assignment::value);
static_assert(!plain_traits::propagate_on_container_move_assignment::value);
static_assert(!plain_traits::propagate_on_container_swap::value);
static_assert(plain_traits::is_always_equal::value);
static_assert(!asc::std::allocator_traits<stateful_allocator>::is_always_equal::value);

using single = asc::std::scoped_allocator_adaptor<plain_allocator>;
static_assert(asc::std::is_same_v<single::outer_traits, plain_traits>);
static_assert(!single::propagate_on_container_copy_assignment::value);
static_assert(!single::propagate_on_container_move_assignment::value);
static_assert(!single::propagate_on_container_swap::value);
static_assert(single::is_always_equal::value);
static_assert(asc::std::is_same_v<single::const_pointer, plain_traits::const_pointer>);
static_assert(asc::std::is_same_v<single::void_pointer, plain_traits::void_pointer>);
static_assert(asc::std::is_same_v<single::const_void_pointer, plain_traits::const_void_pointer>);

using nested = asc::std::scoped_allocator_adaptor<outer_allocator, inner_allocator>;
static_assert(asc::std::is_same_v<nested::outer_traits, asc::std::allocator_traits<outer_allocator>>);
static_assert(nested::propagate_on_container_copy_assignment::value);
static_assert(nested::propagate_on_container_move_assignment::value);
static_assert(nested::propagate_on_container_swap::value);
static_assert(!nested::is_always_equal::value);
static_assert(asc::std::is_same_v<nested::const_pointer, nested::outer_traits::const_pointer>);

CANN_ASC_STL_API int scoped_allocator_behavior()
{
    outer_allocator outer{};
    outer.state = 1;
    inner_allocator inner{};
    inner.state = 2;
    asc::std::scoped_allocator_adaptor original(outer, inner);
    static_assert(asc::std::is_same_v<decltype(original), nested>);
    auto selected = original.select_on_container_copy_construction();
    inner_allocator next_inner{};
    next_inner.state = 4;
    asc::std::scoped_allocator_adaptor<outer_allocator, inner_allocator, inner_allocator> triple(
        outer, inner, next_inner);
    auto selected_triple = triple.select_on_container_copy_construction();
    source_outer_allocator source{};
    source.state = 3;
    asc::std::scoped_allocator_adaptor<source_outer_allocator> source_single(source);
    asc::std::scoped_allocator_adaptor<outer_allocator> converted_single(source_single);
    asc::std::scoped_allocator_adaptor<source_outer_allocator, inner_allocator> source_nested(source, inner);
    nested converted_nested(source_nested);
    alignas(allocator_aware_value) unsigned char object_storage[sizeof(allocator_aware_value)];
    auto* object = reinterpret_cast<allocator_aware_value*>(object_storage);
    original.construct(object, 7);
    const bool constructed = object->value == 9 && original.outer_allocator().constructions == 1;
    original.destroy(object);
    using pair_type = asc::std::pair<allocator_aware_value, trailing_allocator_aware_value>;
    alignas(pair_type) unsigned char pair_storage[sizeof(pair_type)];
    auto* pair_object = reinterpret_cast<pair_type*>(pair_storage);
    original.construct(
        pair_object, asc::std::piecewise_construct, asc::std::forward_as_tuple(3), asc::std::forward_as_tuple(4));
    const bool pair_constructed = pair_object->first.value == 5 && pair_object->second.value == 6;
    original.destroy(pair_object);
    int storage = 0;
    allocating_allocator allocating{};
    allocating.storage = &storage;
    asc::std::scoped_allocator_adaptor<allocating_allocator> single_alloc(allocating);
    int* allocated = single_alloc.allocate(1, nullptr);
    single_alloc.deallocate(allocated, 1);
    return selected.outer_allocator().state == 11 && selected.inner_allocator().outer_allocator().state == 22 &&
            selected_triple.inner_allocator().inner_allocator().outer_allocator().state == 24 && constructed &&
            pair_constructed && original.outer_allocator().constructions == 2 &&
            original.outer_allocator().destructions == 2 && converted_single.outer_allocator().state == 3 &&
            converted_nested.outer_allocator().state == 3 &&
            converted_nested.inner_allocator().outer_allocator().state == 2 && allocated == &storage &&
            single_alloc.max_size() == 4 ?
        0 :
        1;
}

CANN_ASC_STL_API int allocator_bulk_behavior()
{
    int storage[4] = {};
    allocating_allocator fallback{};
    fallback.storage = storage;
    auto exact = asc::std::allocator_traits<allocating_allocator>::allocate_at_least(fallback, 2);
    bulk_allocator bulk{};
    bulk.storage = storage;
    auto expanded = asc::std::allocator_traits<bulk_allocator>::allocate_at_least(bulk, 2);
    return exact.ptr == storage && exact.count == 2 && expanded.ptr == storage && expanded.count == 3 ? 0 : 1;
}

}  // namespace asc_stl_allocator_public_test

#endif  // ASC_STL_TEST_ALLOCATOR_PUBLIC_CONTRACT_H
