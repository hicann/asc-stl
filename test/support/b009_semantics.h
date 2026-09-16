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

#ifndef CANN_ASC_STL_TEST_SUPPORT_B009_SEMANTICS_H
#define CANN_ASC_STL_TEST_SUPPORT_B009_SEMANTICS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__cmath/neg.h>
#include <asc/std/__iterator/access.h>
#include <asc/std/__iterator/data.h>
#include <asc/std/__iterator/empty.h>
#include <asc/std/__iterator/iterator.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/allocator_arg_t.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__tuple/make_tuple_types.h>
#include <asc/std/__tuple/sfinae_helpers.h>
#include <asc/std/concepts>

namespace asc_stl_b009_test {
namespace adl_swap_probe {
struct value {
    int payload;
    value(const value&) = delete;
    value& operator=(const value&) = delete;
};
CANN_ASC_STL_API constexpr void swap(value& left, value& right) noexcept  // NOLINT(build/include_what_you_use)
{
    int temporary = left.payload;
    left.payload = right.payload;
    right.payload = temporary;
}
}  // namespace adl_swap_probe

struct range {
    int values[3] = {1, 2, 3};
    CANN_ASC_STL_API constexpr int* begin() noexcept
    {
        return values;
    }
    CANN_ASC_STL_API constexpr const int* begin() const noexcept
    {
        return values;
    }
    CANN_ASC_STL_API constexpr int* end() noexcept
    {
        return values + 3;
    }
    CANN_ASC_STL_API constexpr const int* end() const noexcept
    {
        return values + 3;
    }
    CANN_ASC_STL_API constexpr int* data() noexcept
    {
        return values;
    }
    CANN_ASC_STL_API constexpr const int* data() const noexcept
    {
        return values;
    }
    CANN_ASC_STL_API constexpr bool empty() const noexcept
    {
        return false;
    }
};
struct iterator_type : asc::std::iterator<asc::std::forward_iterator_tag, int> {};
struct allocator {};
struct allocator_aware {
    using allocator_type = allocator;
};
template <class T>
struct pointer {
    using element_type = T;
    T* value;
    CANN_ASC_STL_API constexpr T* operator->() const noexcept
    {
        return value;
    }
    CANN_ASC_STL_API static constexpr pointer pointer_to(T& input) noexcept
    {
        return {&input};
    }
};
struct traits_pointer {
    int* value;
};
struct relation {
    CANN_ASC_STL_API constexpr bool operator()(int left, int right) const noexcept
    {
        return left < right;
    }
};
static_assert(asc::std::is_same_v<asc::std::iterator_traits<int*>::value_type, int>);
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
static_assert(asc::std::is_same_v<asc::std::input_iterator_tag, ::std::input_iterator_tag>);
static_assert(asc::std::is_same_v<asc::std::random_access_iterator_tag, ::std::random_access_iterator_tag>);
#endif
static_assert(asc::std::is_same_v<asc::std::iterator_traits<iterator_type>::difference_type, asc::std::ptrdiff_t>);
static_assert(asc::std::is_same_v<asc::std::pointer_traits<pointer<int>>::rebind<long>, pointer<long>>);
static_assert(asc::std::is_same_v<asc::std::pointer_traits<void*>::element_type, void>);
static_assert(asc::std::uses_allocator_v<allocator_aware, allocator>);
static_assert(asc::std::tuple_size<asc::std::__tuple_types<int, long>>::value == 2);
static_assert(asc::std::is_same_v<asc::std::tuple_element_t<1, asc::std::__tuple_types<int, long>>, long>);
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
static_assert(asc::std::assignable_from<int&, int> && !asc::std::assignable_from<int, int>);
static_assert(asc::std::common_with<int, long> && asc::std::copyable<int> && asc::std::regular<int>);
static_assert(asc::std::equality_comparable<int> && asc::std::totally_ordered<int>);
static_assert(asc::std::movable<int> && asc::std::semiregular<int> && asc::std::swappable<int>);
static_assert(asc::std::swappable<adl_swap_probe::value>);
static_assert(asc::std::swappable<int[2]>);
static_assert(asc::std::relation<relation, int, int> && asc::std::strict_weak_order<relation, int, int>);
#endif
CANN_ASC_STL_API constexpr int evaluate()
{
    range value{};
    int scalar = 9;
    pointer<int> fancy{&scalar};
    return *asc::std::begin(value) == 1 && asc::std::end(value) - asc::std::begin(value) == 3 &&
            asc::std::data(value)[2] == 3 && !asc::std::empty(value) && asc::std::to_address(fancy) == &scalar &&
            asc::std::__neg(5) == -5 && asc::std::__neg(-5) == 5 ?
        0 :
        1;
}
}  // namespace asc_stl_b009_test

namespace asc::std {
template <>
struct pointer_traits<asc_stl_b009_test::traits_pointer> {
    CANN_ASC_STL_API static constexpr int* to_address(const asc_stl_b009_test::traits_pointer& pointer) noexcept
    {
        return pointer.value;
    }
};
}  // namespace asc::std

namespace asc_stl_b009_test {
CANN_ASC_STL_API constexpr bool custom_to_address_works()
{
    int value = 0;
    return asc::std::to_address(traits_pointer{&value}) == &value;
}
static_assert(custom_to_address_works());
}  // namespace asc_stl_b009_test

#endif  // CANN_ASC_STL_TEST_SUPPORT_B009_SEMANTICS_H
