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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_VARIANT_LIKE_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_VARIANT_LIKE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__concepts/swappable.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>

// Conditionally enable constexpr special members per language dialect.
#ifndef CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#if __cplusplus >= 202002L
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 constexpr
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#endif
#endif  // CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20

CANN_ASC_STL_BEGIN_NAMESPACE

// A type swapped through its own (hidden-friend or namespace-scope) swap
// instead of the generic move-exchange opts out of the trivial swap path.
// The probe reuses the library-wide deleted-template poison.
template <class T>
inline constexpr bool __vl_is_trivially_swappable =
    is_trivially_destructible_v<T> && is_trivially_move_constructible_v<T> && is_trivially_move_assignable_v<T> &&
    !__detect_adl_swap::__has_no_adl_swap<T>::value;

// __variant_like is a simplified variant with just two alternatives that does not need all the complexity of variant

enum class __variant_like_state : unsigned char { __nothing, __holds_first, __holds_second };

struct __construct_first {};
struct __construct_second {};

template <class T, class U, bool = is_trivially_destructible_v<T> && is_trivially_destructible_v<U>>
struct __vl_destruct_base {
    union {
        CANN_ASC_STL_NO_UNIQUE_ADDRESS T __first_;
        CANN_ASC_STL_NO_UNIQUE_ADDRESS U __second_;
    };
    __variant_like_state __contains_;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class T2 = T>
        requires default_initializable<T2>
    CANN_ASC_STL_API constexpr __vl_destruct_base() noexcept(is_nothrow_default_constructible_v<T2>)
        : __first_(), __contains_{__variant_like_state::__holds_first}
    {}
#else
    template <class T2 = T, enable_if_t<is_default_constructible_v<T2>, int> = 0>
    CANN_ASC_STL_API constexpr __vl_destruct_base() noexcept(is_nothrow_default_constructible_v<T2>)
        : __first_(), __contains_{__variant_like_state::__holds_first}
    {}
#endif

    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__variant_like_state state) noexcept : __contains_{state}
    {}

    template <class... Types>
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_first, Types&&... args) noexcept(
        is_nothrow_constructible_v<T, Types...>)
        : __first_{::asc::std::forward<Types>(args)...}, __contains_{__variant_like_state::__holds_first}
    {}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class... Types>
        requires(!same_as<T, U>)
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_second, Types&&... args) noexcept(
        is_nothrow_constructible_v<U, Types...>)
        : __second_{::asc::std::forward<Types>(args)...}, __contains_{__variant_like_state::__holds_second}
    {}
#else
    template <class... Types, bool Tv = true, enable_if_t<!is_same_v<T, U> && Tv, int> = 0>
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_second, Types&&... args) noexcept(
        is_nothrow_constructible_v<U, Types...>)
        : __second_{::asc::std::forward<Types>(args)...}, __contains_{__variant_like_state::__holds_second}
    {}
#endif

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

template <class T, class U>
struct __vl_destruct_base<T, U, true> {
    union {
        CANN_ASC_STL_NO_UNIQUE_ADDRESS T __first_;
        CANN_ASC_STL_NO_UNIQUE_ADDRESS U __second_;
    };
    __variant_like_state __contains_;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class T2 = T>
        requires default_initializable<T2>
    CANN_ASC_STL_API constexpr __vl_destruct_base() noexcept(is_nothrow_default_constructible_v<T2>)
        : __first_(), __contains_{__variant_like_state::__holds_first}
    {}
#else
    template <class T2 = T, enable_if_t<is_default_constructible_v<T2>, int> = 0>
    CANN_ASC_STL_API constexpr __vl_destruct_base() noexcept(is_nothrow_default_constructible_v<T2>)
        : __first_(), __contains_{__variant_like_state::__holds_first}
    {}
#endif

    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__variant_like_state state) noexcept : __contains_{state}
    {}

    template <class... Types>
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_first, Types&&... args) noexcept(
        is_nothrow_constructible_v<T, Types...>)
        : __first_{::asc::std::forward<Types>(args)...}, __contains_{__variant_like_state::__holds_first}
    {}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class... Types>
        requires(!same_as<T, U>)
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_second, Types&&... args) noexcept(
        is_nothrow_constructible_v<U, Types...>)
        : __second_{::asc::std::forward<Types>(args)...}, __contains_{__variant_like_state::__holds_second}
    {}
#else
    template <class... Types, bool Tv = true, enable_if_t<!is_same_v<T, U> && Tv, int> = 0>
    CANN_ASC_STL_API constexpr explicit __vl_destruct_base(__construct_second, Types&&... args) noexcept(
        is_nothrow_constructible_v<U, Types...>)
        : __second_{::asc::std::forward<Types>(args)...}, __contains_{__variant_like_state::__holds_second}
    {}
#endif

protected:
    CANN_ASC_STL_API constexpr void __clear() noexcept
    {
        __contains_ = __variant_like_state::__nothing;
    }
};

template <class T, class U>
class __variant_like : public __vl_destruct_base<T, U> {
public:
    using __base = __vl_destruct_base<T, U>;
    using __base::__base;
    CANN_ASC_STL_API constexpr __variant_like() noexcept(is_nothrow_default_constructible_v<__base>) = default;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    constexpr __variant_like(const __variant_like&)
        requires is_trivially_copy_constructible_v<T> && is_trivially_copy_constructible_v<U>
    = default;
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like(const __variant_like& other) noexcept(
        is_nothrow_copy_constructible_v<T> && is_nothrow_copy_constructible_v<U>)
        : __base{other.__contains_}
    {
        switch (this->__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class OT, class OU>
        requires(!same_as<__variant_like<OT, OU>, __variant_like>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like(const __variant_like<OT, OU>& other) noexcept(
        is_nothrow_constructible_v<T, const OT&> && is_nothrow_constructible_v<U, const OU&>)
        : __base{other.__contains_}
    {
        switch (other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }
    }
#else
    template <class OT, class OU, bool Tv = true,
        enable_if_t<!is_same_v<__variant_like<OT, OU>, __variant_like> && Tv, int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like(const __variant_like<OT, OU>& other) noexcept(
        is_nothrow_constructible_v<T, const OT&> && is_nothrow_constructible_v<U, const OU&>)
        : __base{other.__contains_}
    {
        switch (other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    constexpr __variant_like(__variant_like&&)
        requires is_trivially_move_constructible_v<T> && is_trivially_move_constructible_v<U>
    = default;
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like(__variant_like&& other) noexcept(
        is_nothrow_move_constructible_v<T> && is_nothrow_move_constructible_v<U>)
        : __base{other.__contains_}
    {
        switch (this->__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), ::asc::std::move(other.__first_));
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), ::asc::std::move(other.__second_));
                break;
            case __variant_like_state::__nothing:
                break;
        }
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    constexpr __variant_like& operator=(const __variant_like&)
        requires is_trivially_destructible_v<T> && is_trivially_destructible_v<U> &&
        is_trivially_copy_constructible_v<T> && is_trivially_copy_constructible_v<U> &&
        is_trivially_copy_assignable_v<T> && is_trivially_copy_assignable_v<U>
    = default;
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like& operator=(
        const __variant_like& other) noexcept(is_nothrow_copy_constructible_v<T> &&
        is_nothrow_copy_constructible_v<U> && is_nothrow_copy_assignable_v<T> && is_nothrow_copy_assignable_v<U>)
    {
        if (this->__contains_ == other.__contains_) {
            switch (this->__contains_) {
                case __variant_like_state::__holds_first:
                    this->__first_ = other.__first_;
                    break;
                case __variant_like_state::__holds_second:
                    this->__second_ = other.__second_;
                    break;
                case __variant_like_state::__nothing:
                    break;
            }

            return *this;
        }

        this->__clear();

        switch (other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }

        this->__contains_ = other.__contains_;

        return *this;
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    constexpr __variant_like& operator=(__variant_like&&)
        requires is_trivially_destructible_v<T> && is_trivially_destructible_v<U> &&
        is_trivially_move_constructible_v<T> && is_trivially_move_constructible_v<U> &&
        is_trivially_move_assignable_v<T> && is_trivially_move_assignable_v<U>
    = default;
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like& operator=(__variant_like&& other) noexcept(
        is_nothrow_move_constructible_v<T> && is_nothrow_move_constructible_v<U> && is_nothrow_move_assignable_v<T> &&
        is_nothrow_move_assignable_v<U>)
    {
        if (this->__contains_ == other.__contains_) {
            switch (this->__contains_) {
                case __variant_like_state::__holds_first:
                    this->__first_ = ::asc::std::move(other.__first_);
                    break;
                case __variant_like_state::__holds_second:
                    this->__second_ = ::asc::std::move(other.__second_);
                    break;
                case __variant_like_state::__nothing:
                    break;
            }

            return *this;
        }

        this->__clear();

        switch (other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }

        this->__contains_ = other.__contains_;

        return *this;
    }

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class OT, class OU>
        requires(!same_as<__variant_like<OT, OU>, __variant_like>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like& operator=(
        const __variant_like<OT, OU>& other) noexcept(is_nothrow_constructible_v<T, const OT&> &&
        is_nothrow_constructible_v<U, const OU&> && is_nothrow_assignable_v<T&, const OT&> &&
        is_nothrow_assignable_v<U&, const OU&>)
    {
        if (this->__contains_ == other.__contains_) {
            switch (this->__contains_) {
                case __variant_like_state::__holds_first:
                    this->__first_ = other.__first_;
                    break;
                case __variant_like_state::__holds_second:
                    this->__second_ = other.__second_;
                    break;
                case __variant_like_state::__nothing:
                    break;
            }
            return *this;
        }

        this->__clear();

        switch (other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }

        this->__contains_ = other.__contains_;
        return *this;
    }
#else
    template <class OT, class OU, bool Tv = true,
        enable_if_t<!is_same_v<__variant_like<OT, OU>, __variant_like> && Tv, int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __variant_like& operator=(
        const __variant_like<OT, OU>& other) noexcept(is_nothrow_constructible_v<T, const OT&> &&
        is_nothrow_constructible_v<U, const OU&> && is_nothrow_assignable_v<T&, const OT&> &&
        is_nothrow_assignable_v<U&, const OU&>)
    {
        if (this->__contains_ == other.__contains_) {
            switch (this->__contains_) {
                case __variant_like_state::__holds_first:
                    this->__first_ = other.__first_;
                    break;
                case __variant_like_state::__holds_second:
                    this->__second_ = other.__second_;
                    break;
                case __variant_like_state::__nothing:
                    break;
            }
            return *this;
        }

        this->__clear();

        switch (other.__contains_) {
            case __variant_like_state::__holds_first:
                ::asc::std::__construct_at(::asc::std::addressof(this->__first_), other.__first_);
                break;
            case __variant_like_state::__holds_second:
                ::asc::std::__construct_at(::asc::std::addressof(this->__second_), other.__second_);
                break;
            case __variant_like_state::__nothing:
                break;
        }

        this->__contains_ = other.__contains_;
        return *this;
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class T2 = T>
        requires(!__vl_is_trivially_swappable<T2> || !__vl_is_trivially_swappable<U>)
    friend CANN_ASC_STL_API constexpr void swap(__variant_like& x, __variant_like& y) noexcept(
        is_nothrow_move_constructible_v<T2> && is_nothrow_move_constructible_v<U> && is_nothrow_swappable_v<T2> &&
        is_nothrow_swappable_v<U>)
    {
        if (x.__contains_ == y.__contains_) {
            switch (x.__contains_) {
                case __variant_like_state::__holds_first: {
                    using ::asc::std::swap;
                    swap(x.__first_, y.__first_);
                    break;
                }
                case __variant_like_state::__holds_second: {
                    using ::asc::std::swap;
                    swap(x.__second_, y.__second_);
                    break;
                }
                case __variant_like_state::__nothing:
                    break;
            }
        } else {
            auto tmp = ::asc::std::move(x);
            x = ::asc::std::move(y);
            y = ::asc::std::move(tmp);
        }
    }
#else
    template <class T2 = T, bool Tv = true,
        enable_if_t<(!__vl_is_trivially_swappable<T2> || !__vl_is_trivially_swappable<U>) && Tv, int> = 0>
    friend CANN_ASC_STL_API constexpr void swap(__variant_like& x, __variant_like& y) noexcept(
        is_nothrow_move_constructible_v<T2> && is_nothrow_move_constructible_v<U> && is_nothrow_swappable_v<T2> &&
        is_nothrow_swappable_v<U>)
    {
        if (x.__contains_ == y.__contains_) {
            switch (x.__contains_) {
                case __variant_like_state::__holds_first: {
                    using ::asc::std::swap;
                    swap(x.__first_, y.__first_);
                    break;
                }
                case __variant_like_state::__holds_second: {
                    using ::asc::std::swap;
                    swap(x.__second_, y.__second_);
                    break;
                }
                case __variant_like_state::__nothing:
                    break;
            }
        } else {
            auto tmp = ::asc::std::move(x);
            x = ::asc::std::move(y);
            y = ::asc::std::move(tmp);
        }
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    template <class... Types>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __emplace_first(Types&&... args) noexcept(
        is_nothrow_constructible_v<T, Types...>)
    {
        this->__clear();
        ::asc::std::__construct_at(::asc::std::addressof(this->__first_), ::asc::std::forward<Types>(args)...);
        this->__contains_ = __variant_like_state::__holds_first;
    }

    template <class... Types>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __emplace_second(Types&&... args) noexcept(
        is_nothrow_constructible_v<U, Types...>)
    {
        this->__clear();
        ::asc::std::__construct_at(::asc::std::addressof(this->__second_),
            ::asc::std::forward<Types>(args)...);  // NOLINT(build/include_what_you_use)
        this->__contains_ = __variant_like_state::__holds_second;
    }

    CANN_ASC_STL_API constexpr bool __valueless_by_exception() const noexcept
    {
        return this->__contains_ == __variant_like_state::__nothing;
    }
    CANN_ASC_STL_API constexpr bool __holds_first() const noexcept
    {
        return this->__contains_ == __variant_like_state::__holds_first;
    }
    CANN_ASC_STL_API constexpr bool __holds_second() const noexcept
    {
        return this->__contains_ == __variant_like_state::__holds_second;
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_VARIANT_LIKE_H
