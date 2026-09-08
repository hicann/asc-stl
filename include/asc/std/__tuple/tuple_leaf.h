/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_LEAF_H
#define CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_LEAF_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__memory/allocator_arg_t.h>
#include <asc/std/__tuple/make_tuple_types.h>
#include <asc/std/__tuple/sfinae_helpers.h>
#include <asc/std/__tuple/tuple_constraints.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_types.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_final.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <__SIZE_TYPE__ Index, class T>
class __tuple_leaf {
public:
    CANN_ASC_STL_API constexpr __tuple_leaf() = default;

    template <class U>
    CANN_ASC_STL_API constexpr explicit __tuple_leaf(U&& value) : value_(::asc::std::forward<U>(value))
    {}

    CANN_ASC_STL_API constexpr T& get() noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr const T& get() const noexcept
    {
        return value_;
    }
    CANN_ASC_STL_API constexpr void swap(__tuple_leaf& other) noexcept(is_nothrow_swappable_v<T>)
    {
        ::asc::std::swap(value_, other.value_);  // NOLINT(build/include_what_you_use)
    }

private:
    T value_;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_LEAF_H
