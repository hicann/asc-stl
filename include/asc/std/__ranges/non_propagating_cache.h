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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_NON_PROPAGATING_CACHE_H
#define CANN_ASC_STL_ASC_STD___RANGES_NON_PROPAGATING_CACHE_H

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
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/forward.h>

// Destructors can be constexpr only since C++20. This relies on
// CANN_ASC_STL_DETAIL_CPLUSPLUS from __config (_MSVC_LANG under MSVC, __cplusplus
// otherwise).
#ifndef CANN_ASC_STL_DETAIL_STD_VER
#if CANN_ASC_STL_DETAIL_CPLUSPLUS <= 199711L
#define CANN_ASC_STL_DETAIL_STD_VER 2003
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201103L
#define CANN_ASC_STL_DETAIL_STD_VER 2011
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201402L
#define CANN_ASC_STL_DETAIL_STD_VER 2014
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201703L
#define CANN_ASC_STL_DETAIL_STD_VER 2017
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202002L
#define CANN_ASC_STL_DETAIL_STD_VER 2020
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202302L
#define CANN_ASC_STL_DETAIL_STD_VER 2023
#else
#define CANN_ASC_STL_DETAIL_STD_VER 2024
#endif
#endif  // CANN_ASC_STL_DETAIL_STD_VER

#ifndef CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#if CANN_ASC_STL_DETAIL_STD_VER >= 2020
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 constexpr
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#endif
#endif  // CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

struct __forward_tag {};
struct __from_tag {};
// This helper class is needed to perform copy and move elision when constructing the contained type from an iterator.
template <class T>
struct __npc_wrapper {
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __npc_wrapper(__forward_tag, Args&&... args)
        : __t_(::asc::std::forward<Args>(args)...)
    {}

    template <class Fn>
    CANN_ASC_STL_API constexpr explicit __npc_wrapper(__from_tag, const Fn& fun) : __t_(fun())
    {}

    T __t_;
};

template <class T, class = void>
struct __npc_destruct_base {
    union {
        CANN_ASC_STL_NO_UNIQUE_ADDRESS __npc_wrapper<T> __val_;
    };
    bool __engaged_ = false;

    // The union member is left uninitialized by the default constructor. Workaround
    // shapes (initialized union member / dummy char / plain member storage) once
    // existed for a bisheng device-side miscompilation; it no longer reproduces, so
    // the plain union form stands.
    CANN_ASC_STL_API constexpr __npc_destruct_base() noexcept
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __npc_destruct_base(__forward_tag, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : __val_(__forward_tag{}, ::asc::std::forward<Args>(args)...), __engaged_(true)
    {}

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__npc_destruct_base() noexcept
    {
        if (__engaged_) {
            __val_.~__npc_wrapper<T>();
        }
    }

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __reset() noexcept
    {
        if (__engaged_) {
            __val_.~__npc_wrapper<T>();
            __engaged_ = false;
        }
    }
};

template <class T>
struct __npc_destruct_base<T, enable_if_t<is_trivially_destructible_v<T>>> {
    union {
        CANN_ASC_STL_NO_UNIQUE_ADDRESS __npc_wrapper<T> __val_;
    };
    bool __engaged_ = false;

    CANN_ASC_STL_API constexpr __npc_destruct_base() noexcept
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __npc_destruct_base(__forward_tag, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : __val_(__forward_tag{}, ::asc::std::forward<Args>(args)...), __engaged_(true)
    {}

    CANN_ASC_STL_API constexpr void __reset() noexcept
    {
        if (__engaged_) {
            __engaged_ = false;
        }
    }
};

// __non_propagating_cache is a helper type that allows storing an optional value in it,
// but which does not copy the source's value when it is copy constructed/assigned to,
// and which resets the source's value when it is moved-from.
//
// This type is used as an implementation detail of some views that need to cache the
// result of `begin()` in order to provide an amortized O(1) begin() method. Typically,
// we don't want to propagate the value of the cache upon copy because the cached iterator
// may refer to internal details of the source view.
template <class T, enable_if_t<is_object_v<T>, int> = 0>
class __non_propagating_cache : public __npc_destruct_base<T> {
public:
    using __base = __npc_destruct_base<T>;
    using __base::__base;
    CANN_ASC_STL_API constexpr __non_propagating_cache() noexcept(is_nothrow_default_constructible_v<__base>) = default;

    CANN_ASC_STL_API constexpr __non_propagating_cache(const __non_propagating_cache&) noexcept : __base()
    {}

    CANN_ASC_STL_API constexpr __non_propagating_cache(__non_propagating_cache&& other) noexcept : __base()
    {
        other.__reset();
    }

    CANN_ASC_STL_API constexpr __non_propagating_cache& operator=(const __non_propagating_cache& other) noexcept
    {
        if (this != ::asc::std::addressof(other)) {
            this->__reset();
        }
        return *this;
    }

    CANN_ASC_STL_API constexpr __non_propagating_cache& operator=(__non_propagating_cache&& other) noexcept
    {
        this->__reset();
        other.__reset();
        return *this;
    }

    CANN_ASC_STL_API constexpr T& operator*() noexcept
    {
        return this->__val_.__t_;
    }
    CANN_ASC_STL_API constexpr const T& operator*() const noexcept
    {
        return this->__val_.__t_;
    }

    CANN_ASC_STL_API constexpr bool __has_value() const noexcept
    {
        return this->__engaged_;
    }

    template <class... Args>
    CANN_ASC_STL_API constexpr T& __emplace(Args&&... args) noexcept(is_nothrow_constructible_v<T, Args...>)
    {
        ::asc::std::__construct_at(::asc::std::addressof(this->__val_), __forward_tag{},
            ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
        this->__engaged_ = true;
        return this->__val_.__t_;
    }

    template <class Fn>
    CANN_ASC_STL_API constexpr T& __emplace_from(const Fn& fun) noexcept(
        is_nothrow_constructible_v<T, invoke_result_t<Fn>>)
    {
        ::asc::std::__construct_at(::asc::std::addressof(this->__val_), __from_tag{}, fun);
        this->__engaged_ = true;
        return this->__val_.__t_;
    }
};

struct __empty_cache {};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_NON_PROPAGATING_CACHE_H
