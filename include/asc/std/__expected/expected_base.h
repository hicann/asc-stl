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
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/exception_guard.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

struct __expected_construct_from_invoke_tag {};

template <class T, class E>
struct __expected_storage {
    union storage_type {
        char empty;
        T value;
        E error;
        CANN_ASC_STL_API constexpr storage_type() : empty()
        {}
        CANN_ASC_STL_API ~storage_type()
        {}
    } storage_;
    bool __has_val_;

    CANN_ASC_STL_API constexpr __expected_storage() noexcept(is_nothrow_default_constructible_v<T>)
        : storage_(), __has_val_(true)
    {
        ::asc::std::__construct_at(::asc::std::addressof(storage_.value));
    }
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __expected_storage(in_place_t, Args&&... args) : storage_(), __has_val_(true)
    {
        ::asc::std::__construct_at(::asc::std::addressof(storage_.value), ::asc::std::forward<Args>(args)...);
    }
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __expected_storage(unexpect_t, Args&&... args) : storage_(), __has_val_(false)
    {
        ::asc::std::__construct_at(::asc::std::addressof(storage_.error), ::asc::std::forward<Args>(args)...);
    }
    CANN_ASC_STL_API __expected_storage(const __expected_storage& other) : storage_(), __has_val_(other.__has_val_)
    {
        if (__has_val_)
            ::asc::std::__construct_at(::asc::std::addressof(storage_.value), other.storage_.value);
        else
            ::asc::std::__construct_at(::asc::std::addressof(storage_.error), other.storage_.error);
    }
    CANN_ASC_STL_API __expected_storage(__expected_storage&& other) : storage_(), __has_val_(other.__has_val_)
    {
        if (__has_val_)
            ::asc::std::__construct_at(::asc::std::addressof(storage_.value), ::asc::std::move(other.storage_.value));
        else
            ::asc::std::__construct_at(::asc::std::addressof(storage_.error), ::asc::std::move(other.storage_.error));
    }
    CANN_ASC_STL_API ~__expected_storage()
    {
        __destroy();
    }
    CANN_ASC_STL_API void __destroy() noexcept
    {
        if (__has_val_)
            ::asc::std::__destroy_at(::asc::std::addressof(storage_.value));
        else
            ::asc::std::__destroy_at(::asc::std::addressof(storage_.error));
    }
    CANN_ASC_STL_API T& __value() noexcept
    {
        return storage_.value;
    }
    CANN_ASC_STL_API const T& __value() const noexcept
    {
        return storage_.value;
    }
    CANN_ASC_STL_API E& __error() noexcept
    {
        return storage_.error;
    }
    CANN_ASC_STL_API const E& __error() const noexcept
    {
        return storage_.error;
    }
};

template <class E>
struct __expected_storage<void, E> {
    union storage_type {
        char empty;
        E error;
        CANN_ASC_STL_API constexpr storage_type() : empty()
        {}
        CANN_ASC_STL_API ~storage_type()
        {}
    } storage_;
    bool __has_val_;
    CANN_ASC_STL_API constexpr __expected_storage() noexcept : storage_(), __has_val_(true)
    {}
    CANN_ASC_STL_API constexpr explicit __expected_storage(in_place_t) noexcept : storage_(), __has_val_(true)
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __expected_storage(unexpect_t, Args&&... args) : storage_(), __has_val_(false)
    {
        // NOLINTNEXTLINE(build/include_what_you_use)
        ::asc::std::__construct_at(::asc::std::addressof(storage_.error), ::asc::std::forward<Args>(args)...);
    }
    CANN_ASC_STL_API ~__expected_storage()
    {
        if (!__has_val_)
            ::asc::std::__destroy_at(::asc::std::addressof(storage_.error));
    }
    CANN_ASC_STL_API E& __error() noexcept
    {
        return storage_.error;
    }
    CANN_ASC_STL_API const E& __error() const noexcept
    {
        return storage_.error;
    }
};

template <class T, class E, __smf_availability = __smf_availability::__available>
struct __expected_copy : __expected_storage<T, E> {
    using __expected_storage<T, E>::__expected_storage;
};
template <class T, class E, __smf_availability = __smf_availability::__available>
struct __expected_move : __expected_copy<T, E> {
    using __expected_copy<T, E>::__expected_copy;
};
template <class T, class E, __smf_availability = __smf_availability::__available>
struct __expected_copy_assign : __expected_move<T, E> {
    using __expected_move<T, E>::__expected_move;
};
template <class T, class E, __smf_availability = __smf_availability::__available>
struct __expected_move_assign : __expected_copy_assign<T, E> {
    using __expected_copy_assign<T, E>::__expected_copy_assign;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___EXPECTED_EXPECTED_BASE_H
