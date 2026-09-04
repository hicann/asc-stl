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

#ifndef CANN_ASC_STL_STD_DETAIL_EXPECTED_UNEXPECTED_H
#define CANN_ASC_STL_STD_DETAIL_EXPECTED_UNEXPECTED_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

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
#include <asc/std/__utility/swap.h>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __unexpected {
template <class _Tp>
inline constexpr bool __valid_unexpected =
    is_object_v<_Tp> && !is_array_v<_Tp> && !__is_asc_std_unexpected<_Tp> && !is_const_v<_Tp> && !is_volatile_v<_Tp>;
}  // namespace __unexpected

// [expected.un.general]
template <class _Err>
class unexpected {
    static_assert(__unexpected::__valid_unexpected<_Err>,
        "[expected.un.general] states a program that instantiates std::unexpected for a non-object type, an "
        "array type, a specialization of unexpected, or a cv-qualified type is ill-formed.");

    template <class, class>
    friend class expected;

public:
    // [expected.un.ctor]
    unexpected(const unexpected&) = default;
    unexpected(unexpected&&) = default;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Error = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_same_v<remove_cvref_t<_Error>, unexpected> &&
        !is_same_v<remove_cvref_t<_Error>, in_place_t> && is_constructible_v<_Err, _Error>))
    CANN_ASC_STL_API constexpr explicit unexpected(_Error&& __error) noexcept(is_nothrow_constructible_v<_Err, _Error>)
        : __unex_(::asc::std::forward<_Error>(__error))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, _Args...>)
    CANN_ASC_STL_API constexpr explicit unexpected(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)
        : __unex_(::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, initializer_list<_Up>&, _Args...>)
    CANN_ASC_STL_API constexpr explicit unexpected(in_place_t, initializer_list<_Up> __il, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, initializer_list<_Up>&, _Args...>)
        : __unex_(__il, ::asc::std::forward<_Args>(__args)...)
    {}

    constexpr unexpected& operator=(const unexpected&) = default;
    constexpr unexpected& operator=(unexpected&&) = default;

    // [expected.un.obs]
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Err& error() const& noexcept
    {
        return __unex_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr _Err& error() & noexcept
    {
        return __unex_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr const _Err&& error() const&& noexcept
    {
        return ::asc::std::move(__unex_);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr _Err&& error() && noexcept
    {
        return ::asc::std::move(__unex_);
    }

    // [expected.un.swap]
    CANN_ASC_STL_API constexpr void swap(unexpected& __other) noexcept(is_nothrow_swappable_v<_Err>)
    {
        static_assert(is_swappable_v<_Err>, "E must be swappable");
        using ::asc::std::swap;
        swap(__unex_, __other.__unex_);  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_swappable_v<_Err2>)
    CANN_ASC_STL_API friend constexpr void swap(
        unexpected& __lhs, unexpected& __rhs) noexcept(  // NOLINT(build/include_what_you_use)
        is_nothrow_swappable_v<_Err2>)
    {
        __lhs.swap(__rhs);
        return;
    }

    // [expected.un.eq]
    template <class _UErr>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(const unexpected& __lhs,
        const unexpected<_UErr>& __rhs) noexcept(noexcept(static_cast<bool>(__lhs.error() == __rhs.error())))
    {
        return __lhs.error() == __rhs.error();
    }
#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    template <class _UErr>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(const unexpected& __lhs,
        const unexpected<_UErr>& __rhs) noexcept(noexcept(static_cast<bool>(__lhs.error() != __rhs.error())))
    {
        return __lhs.error() != __rhs.error();
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020

private:
    _Err __unex_;
};

template <class _Err>
unexpected(_Err) -> unexpected<_Err>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_EXPECTED_UNEXPECTED_H
