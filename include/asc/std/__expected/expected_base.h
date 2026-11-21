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

#ifndef CANN_ASC_STL_ASC_STD___EXPECTED_EXPECTED_BASE_H
#define CANN_ASC_STL_ASC_STD___EXPECTED_EXPECTED_BASE_H

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
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__expected/unexpect.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__tuple/sfinae_helpers.h>
#include <asc/std/__type_traits/enable_if.h>
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
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/exception_guard.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>

// asc/__detail/visibility.h provides no such macro, so define it here,
// keeping only the inline semantics for hiding from the ABI.
#ifndef CANN_ASC_STL_DETAIL_HIDE_FROM_ABI
#define CANN_ASC_STL_DETAIL_HIDE_FROM_ABI inline
#endif

// asc/__config provides no standard-version level macro, so key this on its
// feature detection helper instead.
#ifndef CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 constexpr
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#endif
#endif  // CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20

CANN_ASC_STL_BEGIN_NAMESPACE

struct __expected_construct_from_invoke_tag {
    explicit __expected_construct_from_invoke_tag() = default;
};

// Construct the selected member while the union itself is being initialized. If
// construction throws, the enclosing destructor has no active member to release.
template <class Destination, class Source>
CANN_ASC_STL_API constexpr void __expected_construct_active(Destination& destination, bool has_value, Source&& source)
{
    if (has_value) {
        ::asc::std::__construct_at(
            ::asc::std::addressof(destination.__val_), ::asc::std::forward<Source>(source).__val_);
    } else {
        ::asc::std::__construct_at(
            ::asc::std::addressof(destination.__unex_), ::asc::std::forward<Source>(source).__unex_);
    }
}

template <class T, class E, bool = is_trivially_destructible_v<T> && is_trivially_destructible_v<E>>
union __expected_union_t {
    struct __empty_cpo {};
    template <class Source>
    CANN_ASC_STL_API constexpr __expected_union_t(bool has_value, Source&& source) : __empty_{}
    {
        ::asc::std::__expected_construct_active(*this, has_value, ::asc::std::forward<Source>(source));
    }

    template <class T2 = T, enable_if_t<is_default_constructible_v<T2>, int> = 0>
    CANN_ASC_STL_API constexpr __expected_union_t() noexcept(is_nothrow_default_constructible_v<T2>) : __val_()
    {}
    template <class T2 = T, enable_if_t<!is_default_constructible_v<T2>, int> = 0>
    CANN_ASC_STL_API constexpr __expected_union_t() noexcept : __empty_()
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_union_t(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : __val_(::asc::std::forward<Args>(args)...)
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_union_t(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<E, Args...>)
        : __unex_(::asc::std::forward<Args>(args)...)
    {}
    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, in_place_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<T, invoke_result_t<Fun, Args...>>)
        : __val_(::asc::std::invoke(::asc::std::forward<Fun>(fun), ::asc::std::forward<Args>(args)...))
    {}
    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
        : __unex_(::asc::std::invoke(::asc::std::forward<Fun>(fun), ::asc::std::forward<Args>(args)...))
    {}

    // the __expected_destruct's destructor handles this
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_union_t()
    {}

    CANN_ASC_STL_NO_UNIQUE_ADDRESS __empty_cpo __empty_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS T __val_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS E __unex_;
};

template <class T, class E>
union __expected_union_t<T, E, true> {
    struct __empty_cpo {};
    template <class Source>
    CANN_ASC_STL_API constexpr __expected_union_t(bool has_value, Source&& source) : __empty_{}
    {
        ::asc::std::__expected_construct_active(*this, has_value, ::asc::std::forward<Source>(source));
    }

    template <class T2 = T, enable_if_t<is_default_constructible_v<T2>, int> = 0>
    CANN_ASC_STL_API constexpr __expected_union_t() noexcept(is_nothrow_default_constructible_v<T2>) : __val_()
    {}
    template <class T2 = T, enable_if_t<!is_default_constructible_v<T2>, int> = 0>
    CANN_ASC_STL_API constexpr __expected_union_t() noexcept : __empty_()
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_union_t(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : __val_(::asc::std::forward<Args>(args)...)
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_union_t(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<E, Args...>)
        : __unex_(::asc::std::forward<Args>(args)...)
    {}
    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, in_place_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<T, invoke_result_t<Fun, Args...>>)
        : __val_(::asc::std::invoke(::asc::std::forward<Fun>(fun), ::asc::std::forward<Args>(args)...))
    {}
    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
        : __unex_(::asc::std::invoke(::asc::std::forward<Fun>(fun), ::asc::std::forward<Args>(args)...))
    {}

    CANN_ASC_STL_NO_UNIQUE_ADDRESS __empty_cpo __empty_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS T __val_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS E __unex_;
};

template <class T, class E, bool = is_trivially_destructible_v<T>, bool = is_trivially_destructible_v<E>>
struct __expected_destruct;

template <class T, class E>
struct __expected_destruct<T, E, false, false> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __expected_union_t<T, E> __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    template <class Source>
    CANN_ASC_STL_API constexpr __expected_destruct(bool has_value, Source&& source)
        : __union_(has_value, ::asc::std::forward<Source>(source)), __has_val_(has_value)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : __union_(in_place_t{}, ::asc::std::forward<Args>(args)...)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<E, Args...>)
        : __union_(unexpect, ::asc::std::forward<Args>(args)...), __has_val_(false)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, in_place_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<T, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...),
          __has_val_(false)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_destruct()
    {
        if (__has_val_) {
            __union_.__val_.~T();
        } else {
            __union_.__unex_.~E();
        }
    }
};

template <class T, class E>
struct __expected_destruct<T, E, true, false> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __expected_union_t<T, E> __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    template <class Source>
    CANN_ASC_STL_API constexpr __expected_destruct(bool has_value, Source&& source)
        : __union_(has_value, ::asc::std::forward<Source>(source)), __has_val_(has_value)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : __union_(in_place_t{}, ::asc::std::forward<Args>(args)...)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<E, Args...>)
        : __union_(unexpect, ::asc::std::forward<Args>(args)...), __has_val_(false)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, in_place_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<T, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...),
          __has_val_(false)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_destruct()
    {
        if (!__has_val_) {
            __union_.__unex_.~E();
        }
    }
};

template <class T, class E>
struct __expected_destruct<T, E, false, true> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __expected_union_t<T, E> __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    template <class Source>
    CANN_ASC_STL_API constexpr __expected_destruct(bool has_value, Source&& source)
        : __union_(has_value, ::asc::std::forward<Source>(source)), __has_val_(has_value)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : __union_(in_place_t{}, ::asc::std::forward<Args>(args)...)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<E, Args...>)
        : __union_(unexpect, ::asc::std::forward<Args>(args)...), __has_val_(false)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, in_place_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<T, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...),
          __has_val_(false)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_destruct()
    {
        if (__has_val_) {
            __union_.__val_.~T();
        }
    }
};

template <class T, class E>
struct __expected_destruct<T, E, true, true> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __expected_union_t<T, E> __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    template <class Source>
    CANN_ASC_STL_API constexpr __expected_destruct(bool has_value, Source&& source)
        : __union_(has_value, ::asc::std::forward<Source>(source)), __has_val_(has_value)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : __union_(in_place_t{}, ::asc::std::forward<Args>(args)...)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<E, Args...>)
        : __union_(unexpect, ::asc::std::forward<Args>(args)...), __has_val_(false)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, in_place_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<T, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...),
          __has_val_(false)
    {}
};

template <class T, class E>
struct __expected_storage : __expected_destruct<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_storage, __expected_destruct, T, E);
    template <class T1, class T2, class... Args, enable_if_t<is_nothrow_constructible_v<T1, Args...>, int> = 0>
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __reinit_expected(
        T1& newval, T2& oldval, Args&&... args) noexcept
    {
        ::asc::std::__destroy_at(::asc::std::addressof(oldval));
        ::asc::std::__construct_at(::asc::std::addressof(newval), ::asc::std::forward<Args>(args)...);
    }
    template <class T1, class T2, class... Args,
        enable_if_t<!is_nothrow_constructible_v<T1, Args...> && is_nothrow_move_constructible_v<T1>, int> = 0>
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __reinit_expected(
        T1& newval, T2& oldval, Args&&... args)
    {
        T1 tmp(::asc::std::forward<Args>(args)...);
        ::asc::std::__destroy_at(::asc::std::addressof(oldval));
        ::asc::std::__construct_at(::asc::std::addressof(newval), ::asc::std::move(tmp));
    }
    template <class T1, class T2, class... Args,
        enable_if_t<!is_nothrow_constructible_v<T1, Args...> && !is_nothrow_move_constructible_v<T1>, int> = 0>
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __reinit_expected(
        T1& newval, T2& oldval, Args&&... args)
    {
        static_assert(is_nothrow_move_constructible_v<T2>,
            "To provide strong exception guarantee, T2 has to satisfy `is_nothrow_move_constructible_v` so that it can "
            "be reverted to the previous state in case an exception is thrown during the assignment.");
        T2 tmp(::asc::std::move(oldval));
        ::asc::std::__destroy_at(::asc::std::addressof(oldval));
        auto trans = ::asc::std::__make_exception_guard(
            [&] { ::asc::std::__construct_at(::asc::std::addressof(oldval), ::asc::std::move(tmp)); });
        ::asc::std::__construct_at(::asc::std::addressof(newval), ::asc::std::forward<Args>(args)...);
        trans.__complete();
    }
    template <class E2 = E, enable_if_t<is_nothrow_move_constructible_v<E2>, int> = 0>
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __swap_val_unex_impl(
        __expected_storage<T, E2>& with_val, __expected_storage& with_err)
    {
        E tmp(::asc::std::move(with_err.__union_.__unex_));
        ::asc::std::__destroy_at(::asc::std::addressof(with_err.__union_.__unex_));
        auto trans = ::asc::std::__make_exception_guard([&] {
            ::asc::std::__construct_at(::asc::std::addressof(with_err.__union_.__unex_), ::asc::std::move(tmp));
        });
        ::asc::std::__construct_at(
            ::asc::std::addressof(with_err.__union_.__val_), ::asc::std::move(with_val.__union_.__val_));
        trans.__complete();
        ::asc::std::__destroy_at(::asc::std::addressof(with_val.__union_.__val_));
        ::asc::std::__construct_at(::asc::std::addressof(with_val.__union_.__unex_), ::asc::std::move(tmp));
        with_val.__has_val_ = false;
        with_err.__has_val_ = true;
    }
    template <class E2 = E, enable_if_t<!is_nothrow_move_constructible_v<E2>, int> = 0>
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __swap_val_unex_impl(
        __expected_storage<T, E2>& with_val, __expected_storage& with_err)
    {
        static_assert(is_nothrow_move_constructible_v<T>,
            "To provide strong exception guarantee, T has to satisfy `is_nothrow_move_constructible_v` so "
            "that it can be reverted to the previous state in case an exception is thrown during swap.");
        T tmp(::asc::std::move(with_val.__union_.__val_));
        ::asc::std::__destroy_at(::asc::std::addressof(with_val.__union_.__val_));
        auto trans = ::asc::std::__make_exception_guard([&] {
            ::asc::std::__construct_at(::asc::std::addressof(with_val.__union_.__val_), ::asc::std::move(tmp));
        });
        ::asc::std::__construct_at(
            ::asc::std::addressof(with_val.__union_.__unex_), ::asc::std::move(with_err.__union_.__unex_));
        trans.__complete();
        ::asc::std::__destroy_at(::asc::std::addressof(with_err.__union_.__unex_));
        ::asc::std::__construct_at(::asc::std::addressof(with_err.__union_.__val_), ::asc::std::move(tmp));
        with_val.__has_val_ = false;
        with_err.__has_val_ = true;
    }

    CANN_ASC_STL_API constexpr T& __value() noexcept
    {
        return this->__union_.__val_;
    }
    CANN_ASC_STL_API constexpr const T& __value() const noexcept
    {
        return this->__union_.__val_;
    }
    CANN_ASC_STL_API constexpr E& __error() noexcept
    {
        return this->__union_.__unex_;
    }
    CANN_ASC_STL_API constexpr const E& __error() const noexcept
    {
        return this->__union_.__unex_;
    }
};

template <class T, class E>
inline constexpr __smf_availability __expected_can_copy_construct =
    (is_trivially_copy_constructible_v<T> || is_same_v<T, void>) && is_trivially_copy_constructible_v<E> ?
    __smf_availability::__trivial :
    (is_copy_constructible_v<T> || is_same_v<T, void>) && is_copy_constructible_v<E> ? __smf_availability::__available :
                                                                                       __smf_availability::__deleted;

template <class T, class E, __smf_availability = __expected_can_copy_construct<T, E>>
struct __expected_copy : __expected_storage<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_copy, __expected_storage, T, E);
};

template <class T, class E>
struct __expected_copy<T, E, __smf_availability::__available> : __expected_storage<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_copy, __expected_storage, T, E);

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_copy(const __expected_copy& other) noexcept(
        is_nothrow_copy_constructible_v<T> && is_nothrow_copy_constructible_v<E>)
        : __base(other.__has_val_, other.__union_)
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy(__expected_copy&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(const __expected_copy&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(__expected_copy&&) = default;
};

template <class T, class E>
struct __expected_copy<T, E, __smf_availability::__deleted> : __expected_storage<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_copy, __expected_storage, T, E);

    __expected_copy(const __expected_copy&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy(__expected_copy&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(const __expected_copy&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(__expected_copy&&) = default;
};

template <class T, class E>
inline constexpr __smf_availability __expected_can_move_construct =
    (is_trivially_move_constructible_v<T> || is_same_v<T, void>) && is_trivially_move_constructible_v<E> ?
    __smf_availability::__trivial :
    (is_move_constructible_v<T> || is_same_v<T, void>) && is_move_constructible_v<E> ? __smf_availability::__available :
                                                                                       __smf_availability::__deleted;

template <class T, class E, __smf_availability = __expected_can_move_construct<T, E>>
struct __expected_move : __expected_copy<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_move, __expected_copy, T, E);
};

template <class T, class E>
struct __expected_move<T, E, __smf_availability::__available> : __expected_copy<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_move, __expected_copy, T, E);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move(const __expected_move&) = default;

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_move(__expected_move&& other) noexcept(
        is_nothrow_move_constructible_v<T> && is_nothrow_move_constructible_v<E>)
        : __base(other.__has_val_, ::asc::std::move(other.__union_))
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(const __expected_move&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(__expected_move&&) = default;
};

template <class T, class E>
struct __expected_move<T, E, __smf_availability::__deleted> : __expected_copy<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_move, __expected_copy, T, E);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move(const __expected_move&) = default;
    __expected_move(__expected_move&&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(const __expected_move&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(__expected_move&&) = default;
};

// The trivial case must also check is_nothrow_move_constructible because the
// wording places that requirement in the constraints.
template <class T, class E>
inline constexpr __smf_availability __expected_can_copy_assign =
    (is_trivially_destructible_v<T> || is_same_v<T, void>) && is_trivially_destructible_v<E> &&
        (is_trivially_copy_constructible_v<T> || is_same_v<T, void>) && is_trivially_copy_constructible_v<E> &&
        (is_trivially_copy_assignable_v<T> || is_same_v<T, void>) && is_trivially_copy_assignable_v<E> &&
        (is_nothrow_move_constructible_v<T> || is_same_v<T, void> || is_nothrow_move_constructible_v<E>) ?
    __smf_availability::__trivial :
    (is_copy_constructible_v<T> || is_same_v<T, void>) && is_copy_constructible_v<E> &&
        (is_copy_assignable_v<T> || is_same_v<T, void>) && is_copy_assignable_v<E> &&
        (is_nothrow_move_constructible_v<T> || is_same_v<T, void> || is_nothrow_move_constructible_v<E>) ?
    __smf_availability::__available :
    __smf_availability::__deleted;

template <class T, class E, __smf_availability = __expected_can_copy_assign<T, E>>
struct __expected_copy_assign : __expected_move<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_copy_assign, __expected_move, T, E);
};

template <class T, class E>
struct __expected_copy_assign<T, E, __smf_availability::__available> : __expected_move<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_copy_assign, __expected_move, T, E);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(const __expected_copy_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(__expected_copy_assign&&) = default;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_copy_assign& operator=(
        const __expected_copy_assign& other) noexcept(is_nothrow_copy_assignable_v<T> &&
        is_nothrow_copy_constructible_v<T> && is_nothrow_copy_assignable_v<E> &&
        is_nothrow_copy_constructible_v<E>)  // strengthened
    {
        if (this->__has_val_ && other.__has_val_) {
            this->__union_.__val_ = other.__union_.__val_;
        } else if (this->__has_val_ && !other.__has_val_) {
            this->__reinit_expected(this->__union_.__unex_, this->__union_.__val_, other.__union_.__unex_);
            this->__has_val_ = false;
        } else if (!this->__has_val_ && other.__has_val_) {
            this->__reinit_expected(this->__union_.__val_, this->__union_.__unex_, other.__union_.__val_);
            this->__has_val_ = true;
        } else {  // !this->__has_val_ && !other.__has_val_
            this->__union_.__unex_ = other.__union_.__unex_;
        }
        return *this;
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign& operator=(__expected_copy_assign&&) = default;
};

template <class T, class E>
struct __expected_copy_assign<T, E, __smf_availability::__deleted> : __expected_move<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_copy_assign, __expected_move, T, E);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(const __expected_copy_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(__expected_copy_assign&&) = default;
    __expected_copy_assign& operator=(const __expected_copy_assign&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign& operator=(__expected_copy_assign&&) = default;
};

template <class T, class E>
inline constexpr __smf_availability __expected_can_move_assign =
    (is_trivially_destructible_v<T> || is_same_v<T, void>) && is_trivially_destructible_v<E> &&
        (is_trivially_move_constructible_v<T> || is_same_v<T, void>) && is_trivially_move_constructible_v<E> &&
        (is_trivially_move_assignable_v<T> || is_same_v<T, void>) && is_trivially_move_assignable_v<E> ?
    __smf_availability::__trivial :
    (is_move_constructible_v<T> || is_same_v<T, void>) && is_move_constructible_v<E> &&
        (is_move_assignable_v<T> || is_same_v<T, void>) && is_move_assignable_v<E> &&
        (is_nothrow_move_constructible_v<T> || is_same_v<T, void> || is_nothrow_move_constructible_v<E>) ?
    __smf_availability::__available :
    __smf_availability::__deleted;

template <class T, class E, __smf_availability = __expected_can_move_assign<T, E>>
struct __expected_move_assign : __expected_copy_assign<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_move_assign, __expected_copy_assign, T, E);
};

template <class T, class E>
struct __expected_move_assign<T, E, __smf_availability::__available> : __expected_copy_assign<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_move_assign, __expected_copy_assign, T, E);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(const __expected_move_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(__expected_move_assign&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign& operator=(const __expected_move_assign&) = default;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_move_assign& operator=(
        __expected_move_assign&& other) noexcept(is_nothrow_move_assignable_v<T> &&
        is_nothrow_move_constructible_v<T> && is_nothrow_move_assignable_v<E> &&
        is_nothrow_move_constructible_v<E>)  // strengthened
    {
        if (this->__has_val_ && other.__has_val_) {
            this->__union_.__val_ = ::asc::std::move(other.__union_.__val_);
        } else if (this->__has_val_ && !other.__has_val_) {
            this->__reinit_expected(
                this->__union_.__unex_, this->__union_.__val_, ::asc::std::move(other.__union_.__unex_));
            this->__has_val_ = false;
        } else if (!this->__has_val_ && other.__has_val_) {
            this->__reinit_expected(
                this->__union_.__val_, this->__union_.__unex_, ::asc::std::move(other.__union_.__val_));
            this->__has_val_ = true;
        } else {  // !this->__has_val_ && !other.__has_val_
            this->__union_.__unex_ = ::asc::std::move(other.__union_.__unex_);
        }
        return *this;
    }
};

template <class T, class E>
struct __expected_move_assign<T, E, __smf_availability::__deleted> : __expected_copy_assign<T, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_move_assign, __expected_copy_assign, T, E);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(const __expected_move_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(__expected_move_assign&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign& operator=(const __expected_move_assign&) = default;
    __expected_move_assign& operator=(__expected_move_assign&&) = delete;
};

// expected<void, E> base class
template <class E>
struct __expected_destruct<void, E, false, false> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS union __expected_union_t {
        struct __empty_cpo {};

        CANN_ASC_STL_API constexpr __expected_union_t() noexcept : __empty_()
        {}
        template <class... Args>
        CANN_ASC_STL_API constexpr __expected_union_t(unexpect_t, Args&&... args) noexcept(
            is_nothrow_constructible_v<E, Args...>)
            : __unex_(::asc::std::forward<Args>(args)...)
        {}
        template <class Fun, class... Args>
        CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
            Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
            : __unex_(::asc::std::invoke(::asc::std::forward<Fun>(fun), ::asc::std::forward<Args>(args)...))
        {}

        // the __expected_destruct's destructor handles this
        CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_union_t()
        {}

        CANN_ASC_STL_NO_UNIQUE_ADDRESS __empty_cpo __empty_;
        CANN_ASC_STL_NO_UNIQUE_ADDRESS E __unex_;
    } __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;

    CANN_ASC_STL_API constexpr __expected_destruct(const bool __has_val) noexcept : __has_val_(__has_val)
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<E, Args...>)
        : __union_(unexpect, ::asc::std::forward<Args>(args)...), __has_val_(false)
    {}
    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...),
          __has_val_(false)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__expected_destruct()
    {
        if (!__has_val_) {
            __union_.__unex_.~E();
        }
    }
};

template <class E>
struct __expected_destruct<void, E, false, true> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS union __expected_union_t {
        struct __empty_cpo {};

        CANN_ASC_STL_API constexpr __expected_union_t() noexcept : __empty_()
        {}
        template <class... Args>
        CANN_ASC_STL_API constexpr __expected_union_t(unexpect_t, Args&&... args) noexcept(
            is_nothrow_constructible_v<E, Args...>)
            : __unex_(::asc::std::forward<Args>(args)...)
        {}
        template <class Fun, class... Args>
        CANN_ASC_STL_API constexpr __expected_union_t(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
            Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
            : __unex_(::asc::std::invoke(::asc::std::forward<Fun>(fun), ::asc::std::forward<Args>(args)...))
        {}

        CANN_ASC_STL_NO_UNIQUE_ADDRESS __empty_cpo __empty_;
        CANN_ASC_STL_NO_UNIQUE_ADDRESS E __unex_;
    } __union_{};
    bool __has_val_{true};

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __expected_destruct() = default;
    CANN_ASC_STL_API constexpr __expected_destruct(in_place_t) noexcept : __union_()
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<E, Args...>)
        : __union_(unexpect, ::asc::std::forward<Args>(args)...), __has_val_(false)
    {}
    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __expected_destruct(__expected_construct_from_invoke_tag, unexpect_t, Fun&& fun,
        Args&&... args) noexcept(is_nothrow_constructible_v<E, invoke_result_t<Fun, Args...>>)
        : __union_(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...),
          __has_val_(false)
    {}

    CANN_ASC_STL_API constexpr __expected_destruct(const bool __has_val) noexcept : __has_val_(__has_val)
    {}
};

template <class E>
struct __expected_storage<void, E> : __expected_destruct<void, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_storage, __expected_destruct, void, E);
    static CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __swap_val_unex_impl(
        __expected_storage& with_val, __expected_storage& with_err) noexcept(is_nothrow_move_constructible_v<E>)
    {
        ::asc::std::__construct_at(
            ::asc::std::addressof(with_val.__union_.__unex_), ::asc::std::move(with_err.__union_.__unex_));
        ::asc::std::__destroy_at(::asc::std::addressof(with_err.__union_.__unex_));
        with_val.__has_val_ = false;
        with_err.__has_val_ = true;
    }

    CANN_ASC_STL_API constexpr E& __error() noexcept
    {
        return this->__union_.__unex_;
    }
    CANN_ASC_STL_API constexpr const E& __error() const noexcept
    {
        return this->__union_.__unex_;
    }
};

template <class E>
struct __expected_copy<void, E, __smf_availability::__available> : __expected_storage<void, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_copy, __expected_storage, void, E);

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_copy(const __expected_copy& other) noexcept(
        is_nothrow_copy_constructible_v<E>)
        : __base(other.__has_val_)
    {
        if (!other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), other.__union_.__unex_);
        }
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy(__expected_copy&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(const __expected_copy&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy& operator=(__expected_copy&&) = default;
};

template <class E>
struct __expected_move<void, E, __smf_availability::__available> : __expected_copy<void, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_move, __expected_copy, void, E);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move(const __expected_move&) = default;

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_move(__expected_move&& other) noexcept(
        is_nothrow_move_constructible_v<E>)
        : __base(other.__has_val_)
    {
        if (!other.__has_val_) {
            ::asc::std::__construct_at(
                ::asc::std::addressof(this->__union_.__unex_), ::asc::std::move(other.__union_.__unex_));
        }
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(const __expected_move&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move& operator=(__expected_move&&) = default;
};

template <class E>
struct __expected_copy_assign<void, E, __smf_availability::__available> : __expected_move<void, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_copy_assign, __expected_move, void, E);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(const __expected_copy_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign(__expected_copy_assign&&) = default;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_copy_assign& operator=(
        const __expected_copy_assign& other) noexcept(is_nothrow_copy_assignable_v<E> &&
        is_nothrow_copy_constructible_v<E>)  // strengthened
    {
        if (this->__has_val_ && other.__has_val_) {
            // nothing to do
        } else if (this->__has_val_ && !other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), other.__union_.__unex_);
            this->__has_val_ = false;
        } else if (!this->__has_val_ && other.__has_val_) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__union_.__unex_));
            this->__has_val_ = true;
        } else {  // !this->__has_val_ && !other.__has_val_
            this->__union_.__unex_ = other.__union_.__unex_;
        }
        return *this;
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_copy_assign& operator=(__expected_copy_assign&&) = default;
};

template <class E>
struct __expected_move_assign<void, E, __smf_availability::__available> : __expected_copy_assign<void, E> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__expected_move_assign, __expected_copy_assign, void, E);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(const __expected_move_assign&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign(__expected_move_assign&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __expected_move_assign& operator=(const __expected_move_assign&) = default;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __expected_move_assign& operator=(
        __expected_move_assign&& other) noexcept(is_nothrow_move_assignable_v<E> &&
        is_nothrow_move_constructible_v<E>)  // strengthened
    {
        if (this->__has_val_ && other.__has_val_) {
            // nothing to do
        } else if (this->__has_val_ && !other.__has_val_) {
            ::asc::std::__construct_at(
                ::asc::std::addressof(this->__union_.__unex_), ::asc::std::move(other.__union_.__unex_));
            this->__has_val_ = false;
        } else if (!this->__has_val_ && other.__has_val_) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__union_.__unex_));
            this->__has_val_ = true;
        } else {  // !this->__has_val_ && !other.__has_val_
            this->__union_.__unex_ = ::asc::std::move(other.__union_.__unex_);  // NOLINT(build/include_what_you_use)
        }
        return *this;
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___EXPECTED_EXPECTED_BASE_H
