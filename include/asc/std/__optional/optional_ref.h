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

//===----------------------------------------------------------------------===//
//
// Part of libcu++, the C++ Standard Library for your entire system,
// under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2025 ACCL Contributors.
//
//===----------------------------------------------------------------------===//

#ifndef CANN_ASC_STL_STD_DETAIL_OPTIONAL_OPTIONAL_REF_H
#define CANN_ASC_STL_STD_DETAIL_OPTIONAL_OPTIONAL_REF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__fwd/optional.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__optional/bad_optional_access.h>
#include <asc/std/__optional/nullopt.h>
#include <asc/std/__optional/optional_base.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/reference_constructs_from_temporary.h>
#include <asc/std/__type_traits/reference_converts_from_temporary.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
class optional<_Tp&> {
private:
    using __raw_type = remove_reference_t<_Tp>;
    __raw_type* __value_ = nullptr;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ref, class _Arg)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Ref, _Arg>)
    [[nodiscard]] CANN_ASC_STL_API static constexpr _Ref __make_reference(_Arg&& __arg) noexcept
    {
        static_assert(is_reference_v<_Ref>, "optional<T&>: make-reference requires a reference as argument");
        return _Ref(::asc::std::forward<_Arg>(__arg));
    }

    // Needed to interface with optional<T>
    template <class>
    friend struct __optional_storage_base;

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp& __get() noexcept
    {
        return *__value_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Tp& __get() const noexcept
    {
        return *__value_;
    }

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
    template <class _Up>
    static constexpr bool __from_temporary = reference_constructs_from_temporary_v<_Tp&, _Up>;
#else
    template <class _Up>
    static constexpr bool __from_temporary = false;
#endif  // !CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONSTRUCTS_FROM_TEMPORARY

public:
    using value_type = __raw_type&;

    // Use of {} vs = default is deliberate. = default may value-initialize, while {} is
    // guaranteed to do absolutely nothing.
    CANN_ASC_STL_API constexpr optional() noexcept
    {}  // NOLINT(modernize-use-equals-default)
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr optional(const optional&) noexcept = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr optional(optional&&) noexcept = default;
    CANN_ASC_STL_API constexpr optional(nullopt_t) noexcept
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Arg)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_constructible_v<_Tp&, _Arg> CANN_ASC_STL_DETAIL_ACCL_AND(!__from_temporary<_Arg>))
    CANN_ASC_STL_API explicit constexpr optional(in_place_t, _Arg&& __arg) noexcept
        : __value_(::asc::std::addressof(__make_reference<_Tp&>(::asc::std::forward<_Arg>(__arg))))
    {}

    // [optional.ref.ctor]-4
    template <class _Up>
    static constexpr bool __can_construct_from_rvalue = !__is_asc_std_optional_v<remove_cvref_t<_Up>> &&
        !is_same_v<remove_cvref_t<_Up>, in_place_t> && is_constructible_v<_Tp&, _Up> && !__from_temporary<_Up>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_construct_from_rvalue<_Up> CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_Up, _Tp&>)
    CANN_ASC_STL_API constexpr optional(_Up&& __u) noexcept(noexcept(static_cast<_Tp&>(::asc::std::declval<_Up>())))
        : __value_(::asc::std::addressof(static_cast<_Tp&>(::asc::std::forward<_Up>(__u))))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_construct_from_rvalue<_Up> CANN_ASC_STL_DETAIL_ACCL_AND(!is_convertible_v<_Up, _Tp&>))
    CANN_ASC_STL_API explicit constexpr optional(_Up&& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::declval<_Up>())))
        : __value_(::asc::std::addressof(static_cast<_Tp&>(::asc::std::forward<_Up>(__u))))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__from_temporary<_Up>)
    CANN_ASC_STL_API constexpr optional(_Up&&) = delete;

    // [optional.ref.ctor]-8
    template <class _Up>
    static constexpr bool __can_convert_from_optional_reference = !is_same_v<remove_cvref_t<_Tp>, optional<_Up>> &&
        !is_same_v<_Tp&, _Up> && is_constructible_v<_Tp&, _Up&> && !__from_temporary<_Up&>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert_from_optional_reference<_Up> CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_Up&, _Tp&>)
    CANN_ASC_STL_API constexpr optional(optional<_Up>& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::declval<_Up&>())))
        : __value_(__u.has_value() ? ::asc::std::addressof(static_cast<_Tp&>(__u.value())) : nullptr)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert_from_optional_reference<_Up> CANN_ASC_STL_DETAIL_ACCL_AND(!is_convertible_v<_Up&, _Tp&>))
    CANN_ASC_STL_API explicit constexpr optional(optional<_Up>& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::declval<_Up&>())))
        : __value_(__u.has_value() ? ::asc::std::addressof(static_cast<_Tp&>(__u.value())) : nullptr)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__from_temporary<_Up&>)
    CANN_ASC_STL_API constexpr optional(optional<_Up>&) = delete;

    // [optional.ref.ctor]-11
    template <class _Up>
    static constexpr bool __can_convert_from_optional_const_reference =
        !is_same_v<remove_cvref_t<_Tp>, optional<_Up>> && !is_same_v<_Tp&, _Up> &&
        is_constructible_v<_Tp&, const _Up&> && !__from_temporary<const _Up&>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_convert_from_optional_const_reference<_Up> CANN_ASC_STL_DETAIL_ACCL_AND
            is_convertible_v<const _Up&, _Tp&>)
    CANN_ASC_STL_API constexpr optional(const optional<_Up>& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::declval<const _Up&>())))
        : __value_(__u.has_value() ? ::asc::std::addressof(static_cast<_Tp&>(__u.value())) : nullptr)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_convert_from_optional_const_reference<_Up> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_convertible_v<const _Up&, _Tp&>))
    CANN_ASC_STL_API explicit constexpr optional(const optional<_Up>& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::declval<const _Up&>())))
        : __value_(__u.has_value() ? ::asc::std::addressof(static_cast<_Tp&>(__u.value())) : nullptr)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__from_temporary<const _Up&>)
    CANN_ASC_STL_API constexpr optional(const optional<_Up>&) = delete;

    // [optional.ref.ctor]-14
    template <class _Up>
    static constexpr bool __can_convert_from_optional_rvalue_reference =
        !is_same_v<remove_cvref_t<_Tp>, optional<_Up>> && !is_same_v<_Tp&, _Up> && is_constructible_v<_Tp&, _Up> &&
        !__from_temporary<_Up>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert_from_optional_rvalue_reference<_Up> CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_Up, _Tp&>)
    CANN_ASC_STL_API constexpr optional(optional<_Up>&& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::declval<_Up>())))
        : __value_(__u.has_value() ? ::asc::std::addressof(static_cast<_Tp&>(::asc::std::forward<_Up>(__u.value()))) :
                                     nullptr)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert_from_optional_rvalue_reference<_Up> CANN_ASC_STL_DETAIL_ACCL_AND(!is_convertible_v<_Up, _Tp&>))
    CANN_ASC_STL_API explicit constexpr optional(optional<_Up>&& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::declval<_Up>())))
        : __value_(__u.has_value() ? ::asc::std::addressof(static_cast<_Tp&>(::asc::std::forward<_Up>(__u.value()))) :
                                     nullptr)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__from_temporary<_Up>)
    CANN_ASC_STL_API constexpr optional(optional<_Up>&&) = delete;

    // [optional.ref.ctor]-17
    template <class _Up>
    static constexpr bool __can_convert_from_optional_const_rvalue_reference =
        !is_same_v<remove_cvref_t<_Tp>, optional<_Up>> && !is_same_v<_Tp&, _Up> &&
        is_constructible_v<_Tp&, const _Up> && !__from_temporary<const _Up>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert_from_optional_const_rvalue_reference<_Up> CANN_ASC_STL_DETAIL_ACCL_AND
            is_convertible_v<const _Up, _Tp&>)
    CANN_ASC_STL_API constexpr optional(const optional<_Up>&& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::declval<const _Up>())))
        : __value_(__u.has_value() ? ::asc::std::addressof(static_cast<_Tp&>(__u.value())) : nullptr)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert_from_optional_const_rvalue_reference<_Up> CANN_ASC_STL_DETAIL_ACCL_AND(
            !is_convertible_v<const _Up, _Tp&>))
    CANN_ASC_STL_API explicit constexpr optional(const optional<_Up>&& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::declval<const _Up>())))
        : __value_(__u.has_value() ? ::asc::std::addressof(static_cast<_Tp&>(__u.value())) : nullptr)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__from_temporary<const _Up>)
    CANN_ASC_STL_API constexpr optional(const optional<_Up>&&) = delete;

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr optional& operator=(const optional&) noexcept = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr optional& operator=(optional&&) noexcept = default;

    CANN_ASC_STL_API constexpr optional& operator=(nullopt_t) noexcept
    {
        __value_ = nullptr;
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_constructible_v<_Tp&, _Up> CANN_ASC_STL_DETAIL_ACCL_AND(!__from_temporary<_Up>))
    CANN_ASC_STL_API constexpr _Tp& emplace(_Up&& __u) noexcept(
        noexcept(static_cast<_Tp&>(::asc::std::forward<_Up>(__u))))
    {
        __value_ = ::asc::std::addressof(static_cast<_Tp&>(::asc::std::forward<_Up>(__u)));
        return *__value_;
    }

    CANN_ASC_STL_API constexpr void swap(optional& __rhs) noexcept
    {
        return ::asc::std::swap(__value_, __rhs.__value_);
    }

    CANN_ASC_STL_API constexpr _Tp* operator->() const noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(__value_ != nullptr, "optional operator-> called on a disengaged value");
        return __value_;
    }

    CANN_ASC_STL_API constexpr _Tp& operator*() const noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(__value_ != nullptr, "optional operator* called on a disengaged value");
        return *__value_;
    }

    CANN_ASC_STL_API constexpr explicit operator bool() const noexcept
    {
        return __value_ != nullptr;
    }

    CANN_ASC_STL_API constexpr bool has_value() const noexcept
    {
        return __value_ != nullptr;
    }

    CANN_ASC_STL_API constexpr _Tp& value() const noexcept
    {
        if (__value_ != nullptr) {
            return *__value_;
        } else {
            __throw_bad_optional_access();
        }
    }

    template <class _Up>
    CANN_ASC_STL_API constexpr remove_cvref_t<_Tp> value_or(_Up&& __v) const
    {
        static_assert(is_copy_constructible_v<_Tp>, "optional<T&>::value_or: T must be copy constructible");
        static_assert(is_convertible_v<_Up, _Tp>, "optional<T&>::value_or: U must be convertible to T");
        return __value_ != nullptr ? *__value_ : static_cast<_Tp>(::asc::std::forward<_Up>(__v));
    }

    template <class _Func>
    CANN_ASC_STL_API constexpr auto and_then(_Func&& __f) const
    {
        using _Up = invoke_result_t<_Func, _Tp&>;
        static_assert(__is_asc_std_optional_v<remove_cvref_t<_Up>>,
            "optional<T&>::and_then: Result of f(value()) must be a specialization of std::optional");
        if (__value_ != nullptr) {
            return ::asc::std::invoke(::asc::std::forward<_Func>(__f), *__value_);
        }
        return remove_cvref_t<_Up>();
    }

    template <class _Func>
    CANN_ASC_STL_API constexpr auto transform(_Func&& __f) const  // NOLINT(build/include_what_you_use)
    {
        using _Up = invoke_result_t<_Func, _Tp&>;
        static_assert(!is_array_v<_Up>, "optional<T&>::transform: Result of f(value()) should not be an Array");
        static_assert(
            !is_same_v<_Up, in_place_t>, "optional<T&>::transform: Result of f(value()) should not be std::in_place_t");
        static_assert(
            !is_same_v<_Up, nullopt_t>, "optional<T&>::transform: Result of f(value()) should not be std::nullopt_t");
        if (__value_ != nullptr) {
            if constexpr (is_lvalue_reference_v<_Up>) {
                return optional<_Up>(::asc::std::invoke(::asc::std::forward<_Func>(__f), *__value_));
            } else {
                return optional<_Up>(
                    __optional_construct_from_invoke_tag{}, ::asc::std::forward<_Func>(__f), *__value_);
            }
        }
        return optional<_Up>();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Func)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(invocable<_Func>)
    CANN_ASC_STL_API constexpr optional or_else(_Func&& __f) const
    {
        using _Up = invoke_result_t<_Func>;
        static_assert(is_same_v<remove_cvref_t<_Up>, optional>,
            "optional<T&>::or_else: Result of f() should be the same type as this optional");
        if (__value_ != nullptr) {
            return *this;
        }
        return ::asc::std::forward<_Func>(__f)();  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_API constexpr void reset() noexcept
    {
        __value_ = nullptr;
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_OPTIONAL_OPTIONAL_REF_H
