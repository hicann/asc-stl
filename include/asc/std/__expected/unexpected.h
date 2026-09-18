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

#ifndef CANN_ASC_STL_ASC_STD___EXPECTED_UNEXPECTED_H
#define CANN_ASC_STL_ASC_STD___EXPECTED_UNEXPECTED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__fwd/unexpected.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/is_volatile.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Error>
class unexpected {
public:
    using error_type = Error;
    CANN_ASC_STL_API constexpr explicit unexpected(const Error& error) : error_(error)
    {}
    CANN_ASC_STL_API constexpr explicit unexpected(Error&& error) noexcept(is_nothrow_move_constructible_v<Error>)
        : error_(::asc::std::move(error))
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit unexpected(in_place_t, Args&&... args)
        : error_(::asc::std::forward<Args>(args)...)
    {}
    CANN_ASC_STL_API constexpr const Error& error() const& noexcept
    {
        return error_;
    }
    CANN_ASC_STL_API constexpr Error& error() & noexcept
    {
        return error_;
    }
    CANN_ASC_STL_API constexpr Error&& error() && noexcept
    {
        return ::asc::std::move(error_);  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API constexpr const Error&& error() const&& noexcept
    {
        return ::asc::std::move(error_);  // NOLINT(build/include_what_you_use)
    }

private:
    Error error_;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___EXPECTED_UNEXPECTED_H
