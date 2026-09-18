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

#ifndef CANN_ASC_STL_ASC_STD___OPTIONAL_OPTIONAL_BASE_H
#define CANN_ASC_STL_ASC_STD___OPTIONAL_OPTIONAL_BASE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__tuple/sfinae_helpers.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_destructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
union __optional_union {
    unsigned char empty_;
    T value_;
    CANN_ASC_STL_API constexpr __optional_union() noexcept : empty_{}
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __optional_union(in_place_t, Args&&... args)
        : value_(::asc::std::forward<Args>(args)...)
    {}
    CANN_ASC_STL_API ~__optional_union()
    {}
};

template <class T>
class __optional_base {
protected:
    CANN_ASC_STL_API constexpr __optional_base() noexcept = default;
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __optional_base(in_place_t, Args&&... args)
        : storage_(in_place, ::asc::std::forward<Args>(args)...), engaged_(true)
    {}
    CANN_ASC_STL_API ~__optional_base()
    {
        reset();
    }

    template <class... Args>
    CANN_ASC_STL_API constexpr T& construct(Args&&... args)
    {
        ::asc::std::construct_at(  // NOLINT(build/include_what_you_use)
            &storage_.value_,
            ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
        engaged_ = true;
        return storage_.value_;
    }
    CANN_ASC_STL_API constexpr void reset() noexcept
    {
        if (engaged_) {
            ::asc::std::destroy_at(&storage_.value_);
            engaged_ = false;
        }
    }

    __optional_union<T> storage_{};
    bool engaged_{};
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___OPTIONAL_OPTIONAL_BASE_H
