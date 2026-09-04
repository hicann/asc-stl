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

#ifndef CANN_ASC_STL_STD_DETAIL_EXPECTED_EXPECTED_BASE_H
#define CANN_ASC_STL_STD_DETAIL_EXPECTED_EXPECTED_BASE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__expected/unexpect.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__tuple_dir/sfinae_helpers.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__utility/exception_guard.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#define CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__class, __baseclass, ...) \
    using __base = __baseclass<__VA_ARGS__>;                                          \
    using __base::__base;                                                             \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __class() noexcept(                   \
        ::asc::std::is_nothrow_default_constructible_v<__base>) = default;

struct __expected_construct_from_invoke_tag {
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI explicit __expected_construct_from_invoke_tag() = default;
};

template <class _Tp, class _Err, bool = is_trivially_destructible_v<_Tp> && is_trivially_destructible_v<_Err>>
union __expected_union_t {
    struct __empty_cpo {};
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_default_constructible_v<_Tp2>)
    CANN_ASC_STL_API constexpr __expected_union_t() noexcept(is_nothrow_default_constructible_v<_Tp2>) : __val_()
    {}
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_default_constructible_v<_Tp2>))
    CANN_ASC_STL_API constexpr __expected_union_t() noexcept : __empty_()
    {}
    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_union_t(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __val_(::asc::std::forward<_Args>(__args)...)
    {}
    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_union_t(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)
        : __unex_(::asc::std::forward<_Args>(__args)...)
    {}
    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, in_place_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Tp, invoke_result_t<_Fun, _Args...>>)
        : __val_(::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::forward<_Args>(__args)...))
    {}
    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __unex_(::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::forward<_Args>(__args)...))
    {}

    // the __expected_destruct's destructor handles this
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_union_t()
    {}

    CANN_ASC_STL_NO_UNIQUE_ADDRESS __empty_cpo __empty_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp __val_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Err __unex_;
};

template <class _Tp, class _Err>
union __expected_union_t<_Tp, _Err, true> {
    struct __empty_cpo {};
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_default_constructible_v<_Tp2>)
    CANN_ASC_STL_API constexpr __expected_union_t() noexcept(is_nothrow_default_constructible_v<_Tp2>) : __val_()
    {}
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_default_constructible_v<_Tp2>))
    CANN_ASC_STL_API constexpr __expected_union_t() noexcept : __empty_()
    {}
    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_union_t(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __val_(::asc::std::forward<_Args>(__args)...)
    {}
    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_union_t(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)
        : __unex_(::asc::std::forward<_Args>(__args)...)
    {}
    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, in_place_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Tp, invoke_result_t<_Fun, _Args...>>)
        : __val_(::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::forward<_Args>(__args)...))
    {}
    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __unex_(::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::forward<_Args>(__args)...))
    {}

    CANN_ASC_STL_NO_UNIQUE_ADDRESS __empty_cpo __empty_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp __val_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Err __unex_;
};

template <class _Tp, class _Err, bool = is_trivially_destructible_v<_Tp>, bool = is_trivially_destructible_v<_Err>>
struct __expected_destruct;

template <class _Tp, class _Err>
struct __expected_destruct<_Tp, _Err, false, false> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __expected_union_t<_Tp, _Err> __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    CANN_ASC_STL_API constexpr __expected_destruct(const bool __has_val) noexcept(
        is_nothrow_default_constructible_v<_Tp>)
        : __has_val_(__has_val)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __union_(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)
        : __union_(unexpect, ::asc::std::forward<_Args>(__args)...), __has_val_(false)
    {}

    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, in_place_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Tp, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...)
    {}

    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...),
          __has_val_(false)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_destruct()
    {
        if (__has_val_) {
            __union_.__val_.~_Tp();
        } else {
            __union_.__unex_.~_Err();
        }
    }
};

template <class _Tp, class _Err>
struct __expected_destruct<_Tp, _Err, true, false> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __expected_union_t<_Tp, _Err> __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    CANN_ASC_STL_API constexpr __expected_destruct(const bool __has_val) noexcept(
        is_nothrow_default_constructible_v<_Tp>)
        : __has_val_(__has_val)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __union_(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)
        : __union_(unexpect, ::asc::std::forward<_Args>(__args)...), __has_val_(false)
    {}

    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, in_place_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Tp, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...)
    {}

    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...),
          __has_val_(false)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_destruct()
    {
        if (!__has_val_) {
            __union_.__unex_.~_Err();
        }
    }
};

template <class _Tp, class _Err>
struct __expected_destruct<_Tp, _Err, false, true> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __expected_union_t<_Tp, _Err> __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    CANN_ASC_STL_API constexpr __expected_destruct(const bool __has_val) noexcept(
        is_nothrow_default_constructible_v<_Tp>)
        : __has_val_(__has_val)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __union_(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)
        : __union_(unexpect, ::asc::std::forward<_Args>(__args)...), __has_val_(false)
    {}

    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, in_place_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Tp, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...)
    {}

    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...),
          __has_val_(false)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_destruct()
    {
        if (__has_val_) {
            __union_.__val_.~_Tp();
        }
    }
};

template <class _Tp, class _Err>
struct __expected_destruct<_Tp, _Err, true, true> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __expected_union_t<_Tp, _Err> __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    CANN_ASC_STL_API constexpr __expected_destruct(const bool __has_val) noexcept(
        is_nothrow_default_constructible_v<_Tp>)
        : __has_val_(__has_val)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __union_(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)
        : __union_(unexpect, ::asc::std::forward<_Args>(__args)...), __has_val_(false)
    {}

    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, in_place_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Tp, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...)
    {}

    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...),
          __has_val_(false)
    {}
};

template <class _Tp, class _Err>
struct __expected_storage : __expected_destruct<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_storage, __expected_destruct, _Tp, _Err);
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T1, class _T2, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_nothrow_constructible_v<_T1, _Args...>)
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __reinit_expected(
        _T1& __newval, _T2& __oldval, _Args&&... __args) noexcept
    {
        ::asc::std::__destroy_at(::asc::std::addressof(__oldval));
        ::asc::std::__construct_at(::asc::std::addressof(__newval), ::asc::std::forward<_Args>(__args)...);
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T1, class _T2, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (!is_nothrow_constructible_v<_T1, _Args...>)CANN_ASC_STL_DETAIL_ACCL_AND is_nothrow_move_constructible_v<_T1>)
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __reinit_expected(
        _T1& __newval, _T2& __oldval, _Args&&... __args)
    {
        _T1 __tmp(::asc::std::forward<_Args>(__args)...);
        ::asc::std::__destroy_at(::asc::std::addressof(__oldval));
        ::asc::std::__construct_at(::asc::std::addressof(__newval), ::asc::std::move(__tmp));
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T1, class _T2, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (!is_nothrow_constructible_v<_T1, _Args...>)CANN_ASC_STL_DETAIL_ACCL_AND(!is_nothrow_move_constructible_v<_T1>))
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __reinit_expected(
        _T1& __newval, _T2& __oldval, _Args&&... __args)
    {
        static_assert(is_nothrow_move_constructible_v<_T2>,
            "To provide strong exception guarantee, T2 has to satisfy `is_nothrow_move_constructible_v` so that it can "
            "be reverted to the previous state in case an exception is thrown during the assignment.");
        _T2 __tmp(::asc::std::move(__oldval));
        ::asc::std::__destroy_at(::asc::std::addressof(__oldval));
        auto __trans = ::asc::std::__make_exception_guard(
            [&] { ::asc::std::__construct_at(::asc::std::addressof(__oldval), ::asc::std::move(__tmp)); });
        ::asc::std::__construct_at(::asc::std::addressof(__newval), ::asc::std::forward<_Args>(__args)...);
        __trans.__complete();
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_nothrow_move_constructible_v<_Err2>)
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __swap_val_unex_impl(
        __expected_storage<_Tp, _Err2>& __with_val, __expected_storage& __with_err)
    {
        _Err __tmp(::asc::std::move(__with_err.__union_.__unex_));
        ::asc::std::__destroy_at(::asc::std::addressof(__with_err.__union_.__unex_));
        auto __trans = ::asc::std::__make_exception_guard([&] {
            ::asc::std::__construct_at(::asc::std::addressof(__with_err.__union_.__unex_), ::asc::std::move(__tmp));
        });
        ::asc::std::__construct_at(
            ::asc::std::addressof(__with_err.__union_.__val_), ::asc::std::move(__with_val.__union_.__val_));
        __trans.__complete();
        ::asc::std::__destroy_at(::asc::std::addressof(__with_val.__union_.__val_));
        ::asc::std::__construct_at(::asc::std::addressof(__with_val.__union_.__unex_), ::asc::std::move(__tmp));
        __with_val.__has_val_ = false;
        __with_err.__has_val_ = true;
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_nothrow_move_constructible_v<_Err2>))
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __swap_val_unex_impl(
        __expected_storage<_Tp, _Err2>& __with_val, __expected_storage& __with_err)
    {
        static_assert(is_nothrow_move_constructible_v<_Tp>,
            "To provide strong exception guarantee, Tp has to satisfy `is_nothrow_move_constructible_v` so "
            "that it can be reverted to the previous state in case an exception is thrown during swap.");
        _Tp __tmp(::asc::std::move(__with_val.__union_.__val_));
        ::asc::std::__destroy_at(::asc::std::addressof(__with_val.__union_.__val_));
        auto __trans = ::asc::std::__make_exception_guard([&] {
            ::asc::std::__construct_at(::asc::std::addressof(__with_val.__union_.__val_), ::asc::std::move(__tmp));
        });
        ::asc::std::__construct_at(
            ::asc::std::addressof(__with_val.__union_.__unex_), ::asc::std::move(__with_err.__union_.__unex_));
        __trans.__complete();
        ::asc::std::__destroy_at(::asc::std::addressof(__with_err.__union_.__unex_));
        ::asc::std::__construct_at(::asc::std::addressof(__with_err.__union_.__val_), ::asc::std::move(__tmp));
        __with_val.__has_val_ = false;
        __with_err.__has_val_ = true;
    }
};

template <class _Tp, class _Err>
inline constexpr __smf_availability __expected_can_copy_construct =
    (is_trivially_copy_constructible_v<_Tp> || is_same_v<_Tp, void>) && is_trivially_copy_constructible_v<_Err> ?
    __smf_availability::__trivial :
    (is_copy_constructible_v<_Tp> || is_same_v<_Tp, void>) && is_copy_constructible_v<_Err> ?
    __smf_availability::__available :
    __smf_availability::__deleted;

template <class _Tp, class _Err, __smf_availability = __expected_can_copy_construct<_Tp, _Err>>
struct __expected_copy : __expected_storage<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_copy, __expected_storage, _Tp, _Err);
};

template <class _Tp, class _Err>
struct __expected_copy<_Tp, _Err, __smf_availability::__available> : __expected_storage<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_copy, __expected_storage, _Tp, _Err);

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_copy(const __expected_copy& __other) noexcept(
        is_nothrow_copy_constructible_v<_Tp> && is_nothrow_copy_constructible_v<_Err>)
        : __base(__other.__has_val_)
    {
        if (__other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__val_), __other.__union_.__val_);
        } else {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), __other.__union_.__unex_);
        }
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy(__expected_copy&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(const __expected_copy&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(__expected_copy&&) = default;
};

template <class _Tp, class _Err>
struct __expected_copy<_Tp, _Err, __smf_availability::__deleted> : __expected_storage<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_copy, __expected_storage, _Tp, _Err);

    __expected_copy(const __expected_copy&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy(__expected_copy&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(const __expected_copy&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(__expected_copy&&) = default;
};

template <class _Tp, class _Err>
inline constexpr __smf_availability __expected_can_move_construct =
    (is_trivially_move_constructible_v<_Tp> || is_same_v<_Tp, void>) && is_trivially_move_constructible_v<_Err> ?
    __smf_availability::__trivial :
    (is_move_constructible_v<_Tp> || is_same_v<_Tp, void>) && is_move_constructible_v<_Err> ?
    __smf_availability::__available :
    __smf_availability::__deleted;

template <class _Tp, class _Err, __smf_availability = __expected_can_move_construct<_Tp, _Err>>
struct __expected_move : __expected_copy<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_move, __expected_copy, _Tp, _Err);
};

template <class _Tp, class _Err>
struct __expected_move<_Tp, _Err, __smf_availability::__available> : __expected_copy<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_move, __expected_copy, _Tp, _Err);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move(const __expected_move&) = default;

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_move(__expected_move&& __other) noexcept(
        is_nothrow_move_constructible_v<_Tp> && is_nothrow_move_constructible_v<_Err>)
        : __base(__other.__has_val_)
    {
        if (__other.__has_val_) {
            ::asc::std::__construct_at(
                ::asc::std::addressof(this->__union_.__val_), ::asc::std::move(__other.__union_.__val_));
        } else {
            ::asc::std::__construct_at(
                ::asc::std::addressof(this->__union_.__unex_), ::asc::std::move(__other.__union_.__unex_));
        }
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(const __expected_move&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(__expected_move&&) = default;
};

template <class _Tp, class _Err>
struct __expected_move<_Tp, _Err, __smf_availability::__deleted> : __expected_copy<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_move, __expected_copy, _Tp, _Err);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move(const __expected_move&) = default;
    __expected_move(__expected_move&&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(const __expected_move&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(__expected_move&&) = default;
};

// Need to also check against is_nothrow_move_constructible in the trivial case as that is stupidly in the constraints
template <class _Tp, class _Err>
inline constexpr __smf_availability __expected_can_copy_assign =
    (is_trivially_destructible_v<_Tp> || is_same_v<_Tp, void>) && is_trivially_destructible_v<_Err> &&
        (is_trivially_copy_constructible_v<_Tp> || is_same_v<_Tp, void>) && is_trivially_copy_constructible_v<_Err> &&
        (is_trivially_copy_assignable_v<_Tp> || is_same_v<_Tp, void>) && is_trivially_copy_assignable_v<_Err> &&
        (is_nothrow_move_constructible_v<_Tp> || is_same_v<_Tp, void> || is_nothrow_move_constructible_v<_Err>) ?
    __smf_availability::__trivial :
    (is_copy_constructible_v<_Tp> || is_same_v<_Tp, void>) && is_copy_constructible_v<_Err> &&
        (is_copy_assignable_v<_Tp> || is_same_v<_Tp, void>) && is_copy_assignable_v<_Err> &&
        (is_nothrow_move_constructible_v<_Tp> || is_same_v<_Tp, void> || is_nothrow_move_constructible_v<_Err>) ?
    __smf_availability::__available :
    __smf_availability::__deleted;

template <class _Tp, class _Err, __smf_availability = __expected_can_copy_assign<_Tp, _Err>>
struct __expected_copy_assign : __expected_move<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_copy_assign, __expected_move, _Tp, _Err);
};

template <class _Tp, class _Err>
struct __expected_copy_assign<_Tp, _Err, __smf_availability::__available> : __expected_move<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_copy_assign, __expected_move, _Tp, _Err);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(const __expected_copy_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(__expected_copy_assign&&) = default;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_copy_assign& operator=(
        const __expected_copy_assign& __other) noexcept(is_nothrow_copy_assignable_v<_Tp> &&
        is_nothrow_copy_constructible_v<_Tp> && is_nothrow_copy_assignable_v<_Err> &&
        is_nothrow_copy_constructible_v<_Err>)  // strengthened
    {
        if (this->__has_val_ && __other.__has_val_) {
            this->__union_.__val_ = __other.__union_.__val_;
        } else if (this->__has_val_ && !__other.__has_val_) {
            this->__reinit_expected(this->__union_.__unex_, this->__union_.__val_, __other.__union_.__unex_);
            this->__has_val_ = false;
        } else if (!this->__has_val_ && __other.__has_val_) {
            this->__reinit_expected(this->__union_.__val_, this->__union_.__unex_, __other.__union_.__val_);
            this->__has_val_ = true;
        } else {  // !this->__has_val_ && !__other.__has_val_
            this->__union_.__unex_ = __other.__union_.__unex_;
        }
        return *this;
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign& operator=(__expected_copy_assign&&) = default;
};

template <class _Tp, class _Err>
struct __expected_copy_assign<_Tp, _Err, __smf_availability::__deleted> : __expected_move<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_copy_assign, __expected_move, _Tp, _Err);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(const __expected_copy_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(__expected_copy_assign&&) = default;
    __expected_copy_assign& operator=(const __expected_copy_assign&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign& operator=(__expected_copy_assign&&) = default;
};

template <class _Tp, class _Err>
inline constexpr __smf_availability __expected_can_move_assign =
    (is_trivially_destructible_v<_Tp> || is_same_v<_Tp, void>) && is_trivially_destructible_v<_Err> &&
        (is_trivially_move_constructible_v<_Tp> || is_same_v<_Tp, void>) && is_trivially_move_constructible_v<_Err> &&
        (is_trivially_move_assignable_v<_Tp> || is_same_v<_Tp, void>) && is_trivially_move_assignable_v<_Err> ?
    __smf_availability::__trivial :
    (is_move_constructible_v<_Tp> || is_same_v<_Tp, void>) && is_move_constructible_v<_Err> &&
        (is_move_assignable_v<_Tp> || is_same_v<_Tp, void>) && is_move_assignable_v<_Err> &&
        (is_nothrow_move_constructible_v<_Tp> || is_same_v<_Tp, void> || is_nothrow_move_constructible_v<_Err>) ?
    __smf_availability::__available :
    __smf_availability::__deleted;

template <class _Tp, class _Err, __smf_availability = __expected_can_move_assign<_Tp, _Err>>
struct __expected_move_assign : __expected_copy_assign<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_move_assign, __expected_copy_assign, _Tp, _Err);
};

template <class _Tp, class _Err>
struct __expected_move_assign<_Tp, _Err, __smf_availability::__available> : __expected_copy_assign<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_move_assign, __expected_copy_assign, _Tp, _Err);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(const __expected_move_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(__expected_move_assign&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign& operator=(const __expected_move_assign&) = default;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_move_assign& operator=(
        __expected_move_assign&& __other) noexcept(is_nothrow_move_assignable_v<_Tp> &&
        is_nothrow_move_constructible_v<_Tp> && is_nothrow_move_assignable_v<_Err> &&
        is_nothrow_move_constructible_v<_Err>)  // strengthened
    {
        if (this->__has_val_ && __other.__has_val_) {
            this->__union_.__val_ = ::asc::std::move(__other.__union_.__val_);
        } else if (this->__has_val_ && !__other.__has_val_) {
            this->__reinit_expected(
                this->__union_.__unex_, this->__union_.__val_, ::asc::std::move(__other.__union_.__unex_));
            this->__has_val_ = false;
        } else if (!this->__has_val_ && __other.__has_val_) {
            this->__reinit_expected(
                this->__union_.__val_, this->__union_.__unex_, ::asc::std::move(__other.__union_.__val_));
            this->__has_val_ = true;
        } else {  // !this->__has_val_ && !__other.__has_val_
            this->__union_.__unex_ = ::asc::std::move(__other.__union_.__unex_);
        }
        return *this;
    }
};

template <class _Tp, class _Err>
struct __expected_move_assign<_Tp, _Err, __smf_availability::__deleted> : __expected_copy_assign<_Tp, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_move_assign, __expected_copy_assign, _Tp, _Err);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(const __expected_move_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(__expected_move_assign&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign& operator=(const __expected_move_assign&) = default;
    __expected_move_assign& operator=(__expected_move_assign&&) = delete;
};

// expected<void, E> base classtemplate <class _Tp, class _Err>

template <class _Err>
struct __expected_destruct<void, _Err, false, false> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS union __expected_union_t {
        struct __empty_cpo {};

        CANN_ASC_STL_API constexpr __expected_union_t() noexcept : __empty_()
        {}
        template <class... _Args>
        CANN_ASC_STL_API constexpr __expected_union_t(unexpect_t, _Args&&... __args) noexcept(
            is_nothrow_constructible_v<_Err, _Args...>)
            : __unex_(::asc::std::forward<_Args>(__args)...)
        {}
        template <class _Fun, class... _Args>
        CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
            _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
            : __unex_(::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::forward<_Args>(__args)...))
        {}

        // the __expected_destruct's destructor handles this
        CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_union_t()
        {}

        CANN_ASC_STL_NO_UNIQUE_ADDRESS __empty_cpo __empty_;
        CANN_ASC_STL_NO_UNIQUE_ADDRESS _Err __unex_;
    } __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    CANN_ASC_STL_API constexpr __expected_destruct(const bool __has_val) noexcept : __has_val_(__has_val)
    {}
    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)
        : __union_(unexpect, ::asc::std::forward<_Args>(__args)...), __has_val_(false)
    {}
    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...),
          __has_val_(false)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_destruct()
    {
        if (!__has_val_) {
            __union_.__unex_.~_Err();
        }
    }
};

template <class _Err>
struct __expected_destruct<void, _Err, false, true> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS union __expected_union_t {
        struct __empty_cpo {};

        CANN_ASC_STL_API constexpr __expected_union_t() noexcept : __empty_()
        {}
        template <class... _Args>
        CANN_ASC_STL_API constexpr __expected_union_t(unexpect_t, _Args&&... __args) noexcept(
            is_nothrow_constructible_v<_Err, _Args...>)
            : __unex_(::asc::std::forward<_Args>(__args)...)
        {}
        template <class _Fun, class... _Args>
        CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
            _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
            : __unex_(::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::forward<_Args>(__args)...))
        {}

        CANN_ASC_STL_NO_UNIQUE_ADDRESS __empty_cpo __empty_;
        CANN_ASC_STL_NO_UNIQUE_ADDRESS _Err __unex_;
    } __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;
    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t) noexcept(is_nothrow_constructible_v<_Err, _Args...>)
        : __union_()
    {}
    template <class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)
        : __union_(unexpect, ::asc::std::forward<_Args>(__args)...), __has_val_(false)
    {}
    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...),
          __has_val_(false)
    {}

    CANN_ASC_STL_API constexpr __expected_destruct(const bool __has_val) noexcept : __has_val_(__has_val)
    {}
};

template <class _Err>
struct __expected_storage<void, _Err> : __expected_destruct<void, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_storage, __expected_destruct, void, _Err);
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __swap_val_unex_impl(
        __expected_storage& __with_val, __expected_storage& __with_err) noexcept(is_nothrow_move_constructible_v<_Err>)
    {
        ::asc::std::__construct_at(
            ::asc::std::addressof(__with_val.__union_.__unex_), ::asc::std::move(__with_err.__union_.__unex_));
        ::asc::std::__destroy_at(::asc::std::addressof(__with_err.__union_.__unex_));
        __with_val.__has_val_ = false;
        __with_err.__has_val_ = true;
    }
};

template <class _Err>
struct __expected_copy<void, _Err, __smf_availability::__available> : __expected_storage<void, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_copy, __expected_storage, void, _Err);

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_copy(const __expected_copy& __other) noexcept(
        is_nothrow_copy_constructible_v<_Err>)
        : __base(__other.__has_val_)
    {
        if (!__other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), __other.__union_.__unex_);
        }
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy(__expected_copy&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(const __expected_copy&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(__expected_copy&&) = default;
};

template <class _Err>
struct __expected_move<void, _Err, __smf_availability::__available> : __expected_copy<void, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_move, __expected_copy, void, _Err);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move(const __expected_move&) = default;

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_move(__expected_move&& __other) noexcept(
        is_nothrow_move_constructible_v<_Err>)
        : __base(__other.__has_val_)
    {
        if (!__other.__has_val_) {
            ::asc::std::__construct_at(
                ::asc::std::addressof(this->__union_.__unex_), ::asc::std::move(__other.__union_.__unex_));
        }
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(const __expected_move&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(__expected_move&&) = default;
};

template <class _Err>
struct __expected_copy_assign<void, _Err, __smf_availability::__available> : __expected_move<void, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_copy_assign, __expected_move, void, _Err);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(const __expected_copy_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(__expected_copy_assign&&) = default;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_copy_assign& operator=(
        const __expected_copy_assign& __other) noexcept(is_nothrow_copy_assignable_v<_Err> &&
        is_nothrow_copy_constructible_v<_Err>)  // strengthened
    {
        if (this->__has_val_ && __other.__has_val_) {
            // nothing to do
        } else if (this->__has_val_ && !__other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), __other.__union_.__unex_);
            this->__has_val_ = false;
        } else if (!this->__has_val_ && __other.__has_val_) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__union_.__unex_));
            this->__has_val_ = true;
        } else {  // !this->__has_val_ && !__other.__has_val_
            this->__union_.__unex_ = __other.__union_.__unex_;
        }
        return *this;
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign& operator=(__expected_copy_assign&&) = default;
};

template <class _Err>
struct __expected_move_assign<void, _Err, __smf_availability::__available> : __expected_copy_assign<void, _Err> {
    CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS(__expected_move_assign, __expected_copy_assign, void, _Err);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(const __expected_move_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(__expected_move_assign&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign& operator=(const __expected_move_assign&) = default;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_move_assign& operator=(
        __expected_move_assign&& __other) noexcept(is_nothrow_move_assignable_v<_Err> &&
        is_nothrow_move_constructible_v<_Err>)  // strengthened
    {
        if (this->__has_val_ && __other.__has_val_) {
            // nothing to do
        } else if (this->__has_val_ && !__other.__has_val_) {
            ::asc::std::__construct_at(
                ::asc::std::addressof(this->__union_.__unex_), ::asc::std::move(__other.__union_.__unex_));
            this->__has_val_ = false;
        } else if (!this->__has_val_ && __other.__has_val_) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__union_.__unex_));
            this->__has_val_ = true;
        } else {  // !this->__has_val_ && !__other.__has_val_
            this->__union_.__unex_ = ::asc::std::move(__other.__union_.__unex_);  // NOLINT(build/include_what_you_use)
        }
        return *this;
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#undef CANN_ASC_STL_DETAIL_EXPECTED_DELEGATE_CONSTRUCTORS

#endif  // CANN_ASC_STL_STD_DETAIL_EXPECTED_EXPECTED_BASE_H
