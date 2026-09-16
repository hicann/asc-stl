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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_VARIANT_LIKE_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_VARIANT_LIKE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/swappable.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

enum class __variant_like_state : unsigned char { __nothing, __holds_first, __holds_second };
struct __construct_first {};
struct __construct_second {};

template <class First, class Second>
class __variant_like {
public:
    union {
        First __first_;
        Second __second_;
    };
    __variant_like_state __contains_;

    CANN_ASC_STL_API constexpr __variant_like() noexcept(is_nothrow_default_constructible_v<First>)
        : __first_(), __contains_(__variant_like_state::__holds_first)
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __variant_like(__construct_first, Args&&... args) noexcept(
        is_nothrow_constructible_v<First, Args&&...>)
        : __first_(::asc::std::forward<Args>(args)...), __contains_(__variant_like_state::__holds_first)
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __variant_like(__construct_second, Args&&... args) noexcept(
        is_nothrow_constructible_v<Second, Args&&...>)
        : __second_(::asc::std::forward<Args>(args)...), __contains_(__variant_like_state::__holds_second)
    {}
    CANN_ASC_STL_API __variant_like(const __variant_like& other) : __contains_(__variant_like_state::__nothing)
    {
        __copy_from(other);
    }
    CANN_ASC_STL_API __variant_like(__variant_like&& other) : __contains_(__variant_like_state::__nothing)
    {
        __move_from(::asc::std::move(other));
    }
    CANN_ASC_STL_API __variant_like& operator=(const __variant_like& other)
    {
        if (this != &other) {
            __clear();
            __copy_from(other);
        }
        return *this;
    }
    CANN_ASC_STL_API __variant_like& operator=(__variant_like&& other)
    {
        if (this != &other) {
            __clear();
            __move_from(::asc::std::move(other));
        }
        return *this;
    }
    CANN_ASC_STL_API ~__variant_like()
    {
        __clear();
    }
    CANN_ASC_STL_API constexpr bool __holds_first() const noexcept
    {
        return __contains_ == __variant_like_state::__holds_first;
    }
    CANN_ASC_STL_API constexpr bool __holds_second() const noexcept
    {
        return __contains_ == __variant_like_state::__holds_second;
    }
    CANN_ASC_STL_API constexpr bool __valueless_by_exception() const noexcept
    {
        return __contains_ == __variant_like_state::__nothing;
    }

private:
    CANN_ASC_STL_API void __clear() noexcept
    {
        if (__holds_first()) {
            ::asc::std::destroy_at(::asc::std::addressof(__first_));
        }
        if (__holds_second()) {
            ::asc::std::destroy_at(::asc::std::addressof(__second_));
        }
        __contains_ = __variant_like_state::__nothing;
    }
    CANN_ASC_STL_API void __copy_from(const __variant_like& other)
    {
        if (other.__holds_first()) {
            ::asc::std::construct_at(::asc::std::addressof(__first_), other.__first_);
            __contains_ = __variant_like_state::__holds_first;
        } else if (other.__holds_second()) {
            ::asc::std::construct_at(::asc::std::addressof(__second_), other.__second_);
            __contains_ = __variant_like_state::__holds_second;
        }
    }
    CANN_ASC_STL_API void __move_from(__variant_like&& other)
    {
        if (other.__holds_first()) {
            ::asc::std::construct_at(::asc::std::addressof(__first_), ::asc::std::move(other.__first_));
            __contains_ = __variant_like_state::__holds_first;
        } else if (other.__holds_second()) {
            ::asc::std::construct_at(::asc::std::addressof(__second_),
                ::asc::std::move(other.__second_));  // NOLINT(build/include_what_you_use)
            __contains_ = __variant_like_state::__holds_second;
        }
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_VARIANT_LIKE_H
