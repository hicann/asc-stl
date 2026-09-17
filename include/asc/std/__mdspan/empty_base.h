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

#ifndef CANN_ASC_STL_STD_DETAIL_MDSPAN_EMPTY_BASE_H
#define CANN_ASC_STL_STD_DETAIL_MDSPAN_EMPTY_BASE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <size_t _Index, class _Elem, bool = is_empty_v<_Elem>>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __mdspan_ebco_impl {
    _Elem __elem_;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Elem_ = _Elem)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_default_constructible_v<_Elem_>)
    CANN_ASC_STL_API constexpr __mdspan_ebco_impl() noexcept(is_nothrow_default_constructible_v<_Elem_>) : __elem_()
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (sizeof...(_Args) != 0) CANN_ASC_STL_DETAIL_ACCL_AND is_constructible_v<_Elem, _Args...>)
    CANN_ASC_STL_API constexpr __mdspan_ebco_impl(_Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Elem, _Args...>)
        : __elem_(::asc::std::forward<_Args>(__args)...)
    {}

    [[nodiscard]] CANN_ASC_STL_API constexpr _Elem& __get() noexcept
    {
        return __elem_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Elem& __get() const noexcept
    {
        return __elem_;
    }
};

template <size_t _Index, class _Elem>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __mdspan_ebco_impl<_Index, _Elem, true> : _Elem {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Elem_ = _Elem)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_default_constructible_v<_Elem_>)
    CANN_ASC_STL_API constexpr __mdspan_ebco_impl() noexcept(is_nothrow_default_constructible_v<_Elem_>) : _Elem()
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (sizeof...(_Args) != 0) CANN_ASC_STL_DETAIL_ACCL_AND is_constructible_v<_Elem, _Args...>)
    CANN_ASC_STL_API constexpr __mdspan_ebco_impl(_Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Elem, _Args...>)
        : _Elem(::asc::std::forward<_Args>(__args)...)
    {}

    [[nodiscard]] CANN_ASC_STL_API constexpr _Elem& __get() noexcept
    {
        return *static_cast<_Elem*>(this);
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Elem& __get() const noexcept
    {
        return *static_cast<const _Elem*>(this);
    }
};

template <class...>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __mdspan_ebco;

template <class _Elem1>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __mdspan_ebco<_Elem1> : __mdspan_ebco_impl<0, _Elem1> {
    using __base1 = __mdspan_ebco_impl<0, _Elem1>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Elem1_ = _Elem1)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_default_constructible_v<_Elem1_>)
    CANN_ASC_STL_API constexpr __mdspan_ebco() noexcept(is_nothrow_default_constructible_v<_Elem1_>) : __base1()
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (sizeof...(_Args) != 0) CANN_ASC_STL_DETAIL_ACCL_AND is_constructible_v<_Elem1, _Args...>)
    CANN_ASC_STL_API constexpr __mdspan_ebco(_Args&&... __args) noexcept(is_nothrow_constructible_v<_Elem1, _Args...>)
        : __base1(::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(size_t _Index)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((_Index < 1))
    [[nodiscard]] CANN_ASC_STL_API constexpr _Elem1& __get() noexcept
    {
        return static_cast<__base1*>(this)->__get();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(size_t _Index)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((_Index < 1))
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Elem1& __get() const noexcept
    {
        return static_cast<const __base1*>(this)->__get();
    }

    CANN_ASC_STL_API friend constexpr void swap(__mdspan_ebco& __x, __mdspan_ebco& __y) noexcept(
        is_nothrow_swappable_v<_Elem1>)
    {
        swap(__x.__get<0>(), __y.__get<0>());
    }
};

template <class _Elem1, class _Elem2>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __mdspan_ebco<_Elem1, _Elem2> : __mdspan_ebco_impl<0, _Elem1>,
                                                                                __mdspan_ebco_impl<1, _Elem2> {
    using __base1 = __mdspan_ebco_impl<0, _Elem1>;
    using __base2 = __mdspan_ebco_impl<1, _Elem2>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Elem1_ = _Elem1, class _Elem2_ = _Elem2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_default_constructible_v<_Elem1_> CANN_ASC_STL_DETAIL_ACCL_AND is_default_constructible_v<_Elem2_>)
    CANN_ASC_STL_API constexpr __mdspan_ebco() noexcept(
        is_nothrow_default_constructible_v<_Elem1_> && is_nothrow_default_constructible_v<_Elem2_>)
        : __base1(), __base2()
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __mdspan_ebco(const __mdspan_ebco&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __mdspan_ebco(__mdspan_ebco&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __mdspan_ebco& operator=(const __mdspan_ebco&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __mdspan_ebco& operator=(__mdspan_ebco&&) = default;

    template <class _Arg1>
    static constexpr bool __is_constructible_from_one_arg =
        is_constructible_v<_Elem1, _Arg1> && is_default_constructible_v<_Elem2>;

    template <class _Arg1>
    static constexpr bool __is_nothrow_constructible_from_one_arg =
        is_nothrow_constructible_v<_Elem1, _Arg1> && is_nothrow_default_constructible_v<_Elem2>;

    // The converting constructor's constraint __is_constructible_from_one_arg<const __mdspan_ebco&> creates a circular
    // dependency in C++20 concepts evaluation on Clang
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Arg1)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_same_v<__mdspan_ebco, remove_cvref_t<_Arg1>>)
            CANN_ASC_STL_DETAIL_ACCL_AND __is_constructible_from_one_arg<_Arg1>)
    CANN_ASC_STL_API constexpr __mdspan_ebco(_Arg1&& __arg1) noexcept(__is_nothrow_constructible_from_one_arg<_Arg1>)
        : __base1(::asc::std::forward<_Arg1>(__arg1)), __base2()
    {}

    template <class _Arg1, class _Arg2>
    static constexpr bool __is_constructible_from_two_args =
        is_constructible_v<_Elem1, _Arg1> && is_constructible_v<_Elem2, _Arg2>;

    template <class _Arg1, class _Arg2>
    static constexpr bool __is_nothrow_constructible_from_two_args =
        is_nothrow_constructible_v<_Elem1, _Arg1> && is_nothrow_constructible_v<_Elem2, _Arg2>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Arg1, class _Arg2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constructible_from_two_args<_Arg1, _Arg2>)
    CANN_ASC_STL_API constexpr __mdspan_ebco(_Arg1&& __arg1, _Arg2&& __arg2) noexcept(
        __is_nothrow_constructible_from_two_args<_Arg1, _Arg2>)
        : __base1(::asc::std::forward<_Arg1>(__arg1)), __base2(::asc::std::forward<_Arg2>(__arg2))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(size_t _Index)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((_Index < 2))
    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) __get() noexcept
    {
        if constexpr (_Index == 0) {
            return static_cast<__base1*>(this)->__get();
        } else {  // if constexpr (_Index == 1)
            return static_cast<__base2*>(this)->__get();
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(size_t _Index)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((_Index < 2))
    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) __get() const noexcept
    {
        if constexpr (_Index == 0) {
            return static_cast<const __base1*>(this)->__get();
        } else {  // if constexpr (_Index == 1)
            return static_cast<const __base2*>(this)->__get();
        }
    }

    CANN_ASC_STL_API friend constexpr void swap(__mdspan_ebco& __x, __mdspan_ebco& __y) noexcept(
        is_nothrow_swappable_v<_Elem1> && is_nothrow_swappable_v<_Elem2>)
    {
        swap(__x.__get<0>(), __y.__get<0>());
        swap(__x.__get<1>(), __y.__get<1>());
    }
};

template <class _Elem1, class _Elem2, class _Elem3>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __mdspan_ebco<_Elem1, _Elem2, _Elem3>
    : __mdspan_ebco_impl<0, _Elem1>, __mdspan_ebco_impl<1, _Elem2>, __mdspan_ebco_impl<2, _Elem3> {
    using __base1 = __mdspan_ebco_impl<0, _Elem1>;
    using __base2 = __mdspan_ebco_impl<1, _Elem2>;
    using __base3 = __mdspan_ebco_impl<2, _Elem3>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Elem1_ = _Elem1, class _Elem2_ = _Elem2, class _Elem3_ = _Elem3)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_default_constructible_v<_Elem1_> CANN_ASC_STL_DETAIL_ACCL_AND is_default_constructible_v<_Elem2_>
            CANN_ASC_STL_DETAIL_ACCL_AND is_default_constructible_v<_Elem3_>)
    CANN_ASC_STL_API constexpr __mdspan_ebco() noexcept(is_nothrow_default_constructible_v<_Elem1_> &&
        is_nothrow_default_constructible_v<_Elem2_> && is_nothrow_default_constructible_v<_Elem3_>)
        : __base1(), __base2(), __base3()
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __mdspan_ebco(const __mdspan_ebco&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __mdspan_ebco(__mdspan_ebco&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __mdspan_ebco& operator=(const __mdspan_ebco&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __mdspan_ebco& operator=(__mdspan_ebco&&) = default;

    template <class _Arg1>
    static constexpr bool __is_constructible_from_one_arg =
        is_constructible_v<_Elem1, _Arg1> && is_default_constructible_v<_Elem2> && is_default_constructible_v<_Elem3>;

    template <class _Arg1>
    static constexpr bool __is_nothrow_constructible_from_one_arg = is_nothrow_constructible_v<_Elem1, _Arg1> &&
        is_nothrow_default_constructible_v<_Elem2> && is_nothrow_default_constructible_v<_Elem3>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Arg1)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_same_v<__mdspan_ebco, remove_cvref_t<_Arg1>>)
            CANN_ASC_STL_DETAIL_ACCL_AND __is_constructible_from_one_arg<_Arg1>)
    CANN_ASC_STL_API constexpr __mdspan_ebco(_Arg1&& __arg1) noexcept(__is_nothrow_constructible_from_one_arg<_Arg1>)
        : __base1(::asc::std::forward<_Arg1>(__arg1)), __base2(), __base3()
    {}

    template <class _Arg1, class _Arg2>
    static constexpr bool __is_constructible_from_two_args =
        is_constructible_v<_Elem1, _Arg1> && is_constructible_v<_Elem2, _Arg2> && is_default_constructible_v<_Elem3>;

    template <class _Arg1, class _Arg2>
    static constexpr bool __is_nothrow_constructible_from_two_args = is_nothrow_constructible_v<_Elem1, _Arg1> &&
        is_nothrow_constructible_v<_Elem2, _Arg2> && is_nothrow_default_constructible_v<_Elem3>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Arg1, class _Arg2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constructible_from_two_args<_Arg1, _Arg2>)
    CANN_ASC_STL_API constexpr __mdspan_ebco(_Arg1&& __arg1, _Arg2&& __arg2) noexcept(
        __is_nothrow_constructible_from_two_args<_Arg1, _Arg2>)
        : __base1(::asc::std::forward<_Arg1>(__arg1)), __base2(::asc::std::forward<_Arg2>(__arg2)), __base3()
    {}

    template <class _Arg1, class _Arg2, class _Arg3>
    static constexpr bool __is_constructible_from_three_args =
        is_constructible_v<_Elem1, _Arg1> && is_constructible_v<_Elem2, _Arg2> && is_constructible_v<_Elem3, _Arg3>;

    template <class _Arg1, class _Arg2, class _Arg3>
    static constexpr bool __is_nothrow_constructible_from_three_args = is_nothrow_constructible_v<_Elem1, _Arg1> &&
        is_nothrow_constructible_v<_Elem2, _Arg2> && is_nothrow_constructible_v<_Elem3, _Arg3>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Arg1, class _Arg2, class _Arg3)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constructible_from_three_args<_Arg1, _Arg2, _Arg3>)
    CANN_ASC_STL_API constexpr __mdspan_ebco(_Arg1&& __arg1, _Arg2&& __arg2, _Arg3&& __arg3) noexcept(
        __is_nothrow_constructible_from_three_args<_Arg1, _Arg2, _Arg3>)
        : __base1(::asc::std::forward<_Arg1>(__arg1)),
          __base2(::asc::std::forward<_Arg2>(__arg2)),
          __base3(::asc::std::forward<_Arg3>(__arg3))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(size_t _Index)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((_Index < 3))
    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) __get() noexcept
    {
        if constexpr (_Index == 0) {
            return static_cast<__base1*>(this)->__get();
        } else if constexpr (_Index == 1) {
            return static_cast<__base2*>(this)->__get();
        } else {  // if constexpr (_Index == 2)
            return static_cast<__base3*>(this)->__get();
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(size_t _Index)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((_Index < 3))
    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) __get() const noexcept
    {
        if constexpr (_Index == 0) {
            return static_cast<const __base1*>(this)->__get();
        } else if constexpr (_Index == 1) {
            return static_cast<const __base2*>(this)->__get();
        } else {  // if constexpr (_Index == 2)
            return static_cast<const __base3*>(this)->__get();
        }
    }

    CANN_ASC_STL_API friend constexpr void swap(__mdspan_ebco& __x, __mdspan_ebco& __y) noexcept(
        is_nothrow_swappable_v<_Elem1> && is_nothrow_swappable_v<_Elem2> && is_nothrow_swappable_v<_Elem3>)
    {
        swap(__x.__get<0>(), __y.__get<0>());
        swap(__x.__get<1>(), __y.__get<1>());
        swap(__x.__get<2>(), __y.__get<2>());  // NOLINT(build/include_what_you_use)
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MDSPAN_EMPTY_BASE_H
