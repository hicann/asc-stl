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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_VARIANT_LIKE_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_VARIANT_LIKE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

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

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __is_trivially_swappable_v =
    is_trivially_destructible_v<_Tp> && is_trivially_move_constructible_v<_Tp> && is_trivially_move_assignable_v<_Tp> &&
    !::asc::std::ranges::__swap::__unqualified_swappable_with<_Tp, _Tp>;

// __variant_like is a simplified variant with just two alternatives that does not need all the complexity of variant

enum class __variant_like_state : unsigned char { __nothing, __holds_first, __holds_second };

struct __construct_first {};
struct __construct_second {};

template <class _Tp, class _Up, bool = is_trivially_destructible_v<_Tp> && is_trivially_destructible_v<_Up>>
struct __vl_destruct_base {
    union {
        CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp __first_;
        CANN_ASC_STL_NO_UNIQUE_ADDRESS _Up __second_;
    };
    __variant_like_state __contains_;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(default_initializable<_Tp2>)
    CANN_ASC_STL_API constexpr __vl_destruct_base() noexcept(is_nothrow_default_constructible_v<_Tp2>)
        : __first_(), __contains_{__variant_like_state::__holds_first}
    {}

    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__variant_like_state __state) noexcept : __contains_{__state}
    {}

    template <class... _Types>
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_first, _Types&&... _Args) noexcept(
        is_nothrow_constructible_v<_Tp, _Types...>)
        : __first_{::asc::std::forward<_Types>(_Args)...}, __contains_{__variant_like_state::__holds_first}
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Types)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!same_as<_Tp, _Up>))
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_second, _Types&&... _Args) noexcept(
        is_nothrow_constructible_v<_Up, _Types...>)
        : __second_{::asc::std::forward<_Types>(_Args)...}, __contains_{__variant_like_state::__holds_second}
    {}

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__vl_destruct_base() noexcept
    {
        __clear();
    }

protected:
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __clear() noexcept
    {
        switch (__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::destroy_at(::asc::std::addressof(__first_));
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::destroy_at(::asc::std::addressof(__second_));
                break;
            case __variant_like_state::__nothing:
                break;
        }
        __contains_ = __variant_like_state::__nothing;
    }
};

template <class _Tp, class _Up>
struct __vl_destruct_base<_Tp, _Up, true> {
    union {
        CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp __first_;
        CANN_ASC_STL_NO_UNIQUE_ADDRESS _Up __second_;
    };
    __variant_like_state __contains_;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(default_initializable<_Tp2>)
    CANN_ASC_STL_API constexpr __vl_destruct_base() noexcept(is_nothrow_default_constructible_v<_Tp2>)
        : __first_(), __contains_{__variant_like_state::__holds_first}
    {}

    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__variant_like_state __state) noexcept : __contains_{__state}
    {}

    template <class... _Types>
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_first, _Types&&... _Args) noexcept(
        is_nothrow_constructible_v<_Tp, _Types...>)
        : __first_{::asc::std::forward<_Types>(_Args)...}, __contains_{__variant_like_state::__holds_first}
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Types)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!same_as<_Tp, _Up>))
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_second, _Types&&... _Args) noexcept(
        is_nothrow_constructible_v<_Up, _Types...>)
        : __second_{::asc::std::forward<_Types>(_Args)...}, __contains_{__variant_like_state::__holds_second}
    {}

protected:
    CANN_ASC_STL_API constexpr void __clear() noexcept
    {
        __contains_ = __variant_like_state::__nothing;
    }
};

template <class _Tp, class _Up>
class __variant_like : public __vl_destruct_base<_Tp, _Up> {
public:
    using __base = __vl_destruct_base<_Tp, _Up>;
    using __base::__base;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __variant_like() noexcept(
        ::asc::std::is_nothrow_default_constructible_v<__base>) = default;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __variant_like(const __variant_like&)
        requires is_trivially_copy_constructible_v<_Tp> && is_trivially_copy_constructible_v<_Up>
    = default;
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like(const __variant_like& __other) noexcept(
        is_nothrow_copy_constructible_v<_Tp> && is_nothrow_copy_constructible_v<_Up>)
        : __base{__other.__contains_}
    {
        switch (this->__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), __other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), __other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OTp, class _OUp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!same_as<__variant_like<_OTp, _OUp>, __variant_like>))
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like(
        const __variant_like<_OTp, _OUp>& __other) noexcept(is_nothrow_constructible_v<_Tp, const _OTp&> &&
        is_nothrow_constructible_v<_Up, const _OUp&>)
        : __base{__other.__contains_}
    {
        switch (__other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), __other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), __other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __variant_like(__variant_like&&)
        requires is_trivially_move_constructible_v<_Tp> && is_trivially_move_constructible_v<_Up>
    = default;
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like(__variant_like&& __other) noexcept(
        is_nothrow_move_constructible_v<_Tp> && is_nothrow_move_constructible_v<_Up>)
        : __base{__other.__contains_}
    {
        switch (this->__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), ::asc::std::move(__other.__first_));
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), ::asc::std::move(__other.__second_));
                break;
            case __variant_like_state::__nothing:
                break;
        }
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __variant_like& operator=(const __variant_like&)
        requires is_trivially_destructible_v<_Tp> && is_trivially_destructible_v<_Up> &&
        is_trivially_copy_constructible_v<_Tp> && is_trivially_copy_constructible_v<_Up> &&
        is_trivially_copy_assignable_v<_Tp> && is_trivially_copy_assignable_v<_Up>
    = default;
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like& operator=(
        const __variant_like& __other) noexcept(is_nothrow_copy_constructible_v<_Tp> &&
        is_nothrow_copy_constructible_v<_Up> && is_nothrow_copy_assignable_v<_Tp> && is_nothrow_copy_assignable_v<_Up>)
    {
        if (this->__contains_ == __other.__contains_) {
            switch (this->__contains_) {
                case __variant_like_state::__holds_first:
                    this->__first_ = __other.__first_;
                    break;
                case __variant_like_state::__holds_second:
                    this->__second_ = __other.__second_;
                    break;
                case __variant_like_state::__nothing:
                    break;
            }

            return *this;
        }

        this->__clear();

        switch (__other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), __other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), __other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }

        this->__contains_ = __other.__contains_;

        return *this;
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __variant_like& operator=(__variant_like&&)
        requires is_trivially_destructible_v<_Tp> && is_trivially_destructible_v<_Up> &&
        is_trivially_move_constructible_v<_Tp> && is_trivially_move_constructible_v<_Up> &&
        is_trivially_move_assignable_v<_Tp> && is_trivially_move_assignable_v<_Up>
    = default;
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like& operator=(__variant_like&& __other) noexcept(
        is_nothrow_move_constructible_v<_Tp> && is_nothrow_move_constructible_v<_Up> &&
        is_nothrow_move_assignable_v<_Tp> && is_nothrow_move_assignable_v<_Up>)
    {
        if (this->__contains_ == __other.__contains_) {
            switch (this->__contains_) {
                case __variant_like_state::__holds_first:
                    this->__first_ = ::asc::std::move(__other.__first_);
                    break;
                case __variant_like_state::__holds_second:
                    this->__second_ = ::asc::std::move(__other.__second_);
                    break;
                case __variant_like_state::__nothing:
                    break;
            }

            return *this;
        }

        this->__clear();

        switch (__other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), __other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), __other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }

        this->__contains_ = __other.__contains_;

        return *this;
    }

    CANN_ASC_STL_DETAIL_DIAG_PUSH
    // MSVC hallucinates that
    //
    // this->__second_ = __other.__second_;
    //
    // is unreachable.
    CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4702)

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OTp, class _OUp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!same_as<__variant_like<_OTp, _OUp>, __variant_like>))
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like& operator=(
        const __variant_like<_OTp, _OUp>& __other) noexcept(is_nothrow_constructible_v<_Tp, const _OTp&> &&
        is_nothrow_constructible_v<_Up, const _OUp&> && is_nothrow_assignable_v<_Tp&, const _OTp&> &&
        is_nothrow_assignable_v<_Up&, const _OUp&>)
    {
        if (this->__contains_ == __other.__contains_) {
            switch (this->__contains_) {
                case __variant_like_state::__holds_first:
                    this->__first_ = __other.__first_;
                    break;
                case __variant_like_state::__holds_second:
                    this->__second_ = __other.__second_;
                    break;
                case __variant_like_state::__nothing:
                    break;
            }
            return *this;
        }

        this->__clear();

        switch (__other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), __other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), __other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }

        this->__contains_ = __other.__contains_;
        return *this;
    }

    CANN_ASC_STL_DETAIL_DIAG_POP

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__is_trivially_swappable_v<_Tp2> || !__is_trivially_swappable_v<_Up>))
    CANN_ASC_STL_API friend constexpr void swap(__variant_like& __x, __variant_like& __y) noexcept(
        is_nothrow_move_constructible_v<_Tp2> && is_nothrow_move_constructible_v<_Up> && is_nothrow_swappable_v<_Tp2> &&
        is_nothrow_swappable_v<_Up>)
    {
        if (__x.__contains_ == __y.__contains_) {
            switch (__x.__contains_) {
                case __variant_like_state::__holds_first:
                    ::asc::std::ranges::__swap_cpo{}(__x.__first_, __y.__first_);
                    break;
                case __variant_like_state::__holds_second:
                    ::asc::std::ranges::__swap_cpo{}(__x.__second_, __y.__second_);
                    break;
                case __variant_like_state::__nothing:
                    break;
            }
        } else {
            auto __tmp = ::asc::std::move(__x);
            __x = ::asc::std::move(__y);
            __y = ::asc::std::move(__tmp);
        }
    }

    template <class... _Types>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __emplace_first(_Types&&... _Args) noexcept(
        is_nothrow_constructible_v<_Tp, _Types...>)
    {
        this->__clear();
        ::asc::std::__construct_at(::asc::std::addressof(this->__first_), ::asc::std::forward<_Types>(_Args)...);
        this->__contains_ = __variant_like_state::__holds_first;
    }

    template <class... _Types>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __emplace_second(_Types&&... _Args) noexcept(
        is_nothrow_constructible_v<_Up, _Types...>)
    {
        this->__clear();
        ::asc::std::__construct_at(::asc::std::addressof(this->__second_),
            ::asc::std::forward<_Types>(_Args)...);  // NOLINT(build/include_what_you_use)
        this->__contains_ = __variant_like_state::__holds_second;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr bool __valueless_by_exception() const noexcept
    {
        return this->__contains_ == __variant_like_state::__nothing;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr bool __holds_first() const noexcept
    {
        return this->__contains_ == __variant_like_state::__holds_first;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr bool __holds_second() const noexcept
    {
        return this->__contains_ == __variant_like_state::__holds_second;
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_VARIANT_LIKE_H
