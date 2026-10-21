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

#ifndef CANN_ASC_STL_ASC_STD___EXPECTED_EXPECTED_H
#define CANN_ASC_STL_ASC_STD___EXPECTED_EXPECTED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__expected/expected_base.h>
#include <asc/std/__expected/unexpect.h>
#include <asc/std/__expected/unexpected.h>
#include <asc/std/__fwd/expected.h>
#include <asc/std/__fwd/unexpected.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__type_traits/conjunction.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/lazy.h>
#include <asc/std/__type_traits/negation.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/as_const.h>
#include <asc/std/__utility/exception_guard.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// In-place list construction/emplace overloads go through the host initializer_list
// (the device side does not participate).
#include <initializer_list>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// [expected.object.general]: instantiating expected is ill-formed when the
// value type is a reference, a function type, in_place_t, unexpect_t, or a
// specialization of unexpected, or when the error type is not a valid
// template argument for unexpected.
template <class T, class E>
inline constexpr bool __expected_valid_v =
    !is_reference_v<T> && !is_function_v<T> && !is_same_v<remove_cv_t<T>, in_place_t> &&
    !is_same_v<remove_cv_t<T>, unexpect_t> && !__is_asc_std_unexpected<remove_cv_t<T>> && __valid_unexpected<E>;

// Strong exception-safety precondition of member swap: both sides swappable
// and move constructible, with at least one of the value or error sides
// nothrow move constructible ([expected.object.swap] constraints).
template <class T, class E>
inline constexpr bool __expected_can_swap_v = is_swappable_v<T> && is_swappable_v<E> && is_move_constructible_v<T> &&
    is_move_constructible_v<E> && (is_nothrow_move_constructible_v<T> || is_nothrow_move_constructible_v<E>);

template <class Value, class Error>
class expected : private __expected_move_assign<Value, Error> {
    using base = __expected_move_assign<Value, Error>;
    template <class, class>
    friend class expected;

    static_assert(__expected_valid_v<Value, Error>,
        "instantiating expected for a reference, a function type, in_place_t, unexpect_t, a specialization "
        "of unexpected as the value type, or an invalid error type is ill-formed");

public:
    using value_type = Value;
    using error_type = Error;
    using unexpected_type = unexpected<Error>;

    template <class Value2 = Value, enable_if_t<is_default_constructible_v<Value2>, int> = 0>
    CANN_ASC_STL_API constexpr expected() noexcept(is_nothrow_default_constructible_v<Value2>) : base(true)
    {}

    CANN_ASC_STL_API constexpr expected(const Value& value) : base(in_place, value)
    {}
    CANN_ASC_STL_API constexpr expected(const unexpected<Error>& error) : base(unexpect, error.error())
    {}
    CANN_ASC_STL_API constexpr expected(unexpect_t, const Error& error) : base(unexpect, error)
    {}
    CANN_ASC_STL_API constexpr expected(const expected& other) : base(static_cast<const base&>(other))
    {}
    // Move construction/move assignment propagate automatically through the
    // layered (available/deleted) dispatch: the member is deleted when either
    // the value or the error is not movable, matching the [expected.object]
    // special-member constraints.
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected(expected&&) = default;
    CANN_ASC_STL_API ~expected() = default;

private:
    // Cross-type converting construction is legal when both the value and
    // error sides are constructible from the other specialization's
    // arguments, and no construction/conversion path exists between the two
    // expected specializations ([expected.object.ctor] constraints).
    template <class Up, class OtherErr, class UpQual, class OtherErrQual>
    static constexpr bool __can_convert =
        is_constructible_v<Value, UpQual> && is_constructible_v<Error, OtherErrQual> &&
        !is_constructible_v<Value, expected<Up, OtherErr>&> && !is_constructible_v<Value, expected<Up, OtherErr>> &&
        !is_constructible_v<Value, const expected<Up, OtherErr>&> &&
        !is_constructible_v<Value, const expected<Up, OtherErr>> && !is_convertible_v<expected<Up, OtherErr>&, Value> &&
        !is_convertible_v<expected<Up, OtherErr>, Value> && !is_convertible_v<const expected<Up, OtherErr>&, Value> &&
        !is_convertible_v<const expected<Up, OtherErr>, Value> &&
        !is_constructible_v<unexpected<Error>, expected<Up, OtherErr>&> &&
        !is_constructible_v<unexpected<Error>, expected<Up, OtherErr>> &&
        !is_constructible_v<unexpected<Error>, const expected<Up, OtherErr>&> &&
        !is_constructible_v<unexpected<Error>, const expected<Up, OtherErr>>;

public:
    template <class Up, class OtherErr,
        enable_if_t<__can_convert<Up, OtherErr, const Up&, const OtherErr&> && is_convertible_v<const Up&, Value> &&
                is_convertible_v<const OtherErr&, Error>,
            int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected(const expected<Up, OtherErr>& other) noexcept(
        is_nothrow_constructible_v<Value, const Up&> && is_nothrow_constructible_v<Error, const OtherErr&>)
        : base(other.__has_val_)
    {
        if (other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__value()), other.__value());
        } else {
            ::asc::std::__construct_at(::asc::std::addressof(this->__error()), other.__error());
        }
    }

    template <class Up, class OtherErr,
        enable_if_t<__can_convert<Up, OtherErr, const Up&, const OtherErr&> &&
                (!is_convertible_v<const Up&, Value> || !is_convertible_v<const OtherErr&, Error>),
            int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 explicit expected(
        const expected<Up, OtherErr>& other) noexcept(is_nothrow_constructible_v<Value, const Up&> &&
        is_nothrow_constructible_v<Error, const OtherErr&>)
        : base(other.__has_val_)
    {
        if (other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__value()), other.__value());
        } else {
            ::asc::std::__construct_at(::asc::std::addressof(this->__error()), other.__error());
        }
    }

    template <class Up, class OtherErr,
        enable_if_t<__can_convert<Up, OtherErr, Up, OtherErr> && is_convertible_v<Up, Value> &&
                is_convertible_v<OtherErr, Error>,
            int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected(expected<Up, OtherErr>&& other) noexcept(
        is_nothrow_constructible_v<Value, Up> && is_nothrow_constructible_v<Error, OtherErr>)
        : base(other.__has_val_)
    {
        if (other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__value()), ::asc::std::move(other.__value()));
        } else {
            ::asc::std::__construct_at(::asc::std::addressof(this->__error()), ::asc::std::move(other.__error()));
        }
    }

    template <class Up, class OtherErr,
        enable_if_t<__can_convert<Up, OtherErr, Up, OtherErr> &&
                (!is_convertible_v<Up, Value> || !is_convertible_v<OtherErr, Error>),
            int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 explicit expected(expected<Up, OtherErr>&& other) noexcept(
        is_nothrow_constructible_v<Value, Up> && is_nothrow_constructible_v<Error, OtherErr>)
        : base(other.__has_val_)
    {
        if (other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__value()), ::asc::std::move(other.__value()));
        } else {
            ::asc::std::__construct_at(::asc::std::addressof(this->__error()), ::asc::std::move(other.__error()));
        }
    }

    template <class Up = Value,
        enable_if_t<!is_same_v<remove_cvref_t<Up>, in_place_t> && !is_same_v<remove_cvref_t<Up>, expected> &&
                !__is_asc_std_unexpected<remove_cvref_t<Up>> && is_constructible_v<Value, Up> &&
                is_convertible_v<Up, Value>,
            int> = 0>
    CANN_ASC_STL_API constexpr expected(Up&& value) noexcept(is_nothrow_constructible_v<Value, Up>)
        : base(in_place, ::asc::std::forward<Up>(value))
    {}

    template <class Up = Value,
        enable_if_t<!is_same_v<remove_cvref_t<Up>, in_place_t> && !is_same_v<remove_cvref_t<Up>, expected> &&
                !__is_asc_std_unexpected<remove_cvref_t<Up>> && is_constructible_v<Value, Up> &&
                !is_convertible_v<Up, Value>,
            int> = 0>
    CANN_ASC_STL_API constexpr explicit expected(Up&& value) noexcept(is_nothrow_constructible_v<Value, Up>)
        : base(in_place, ::asc::std::forward<Up>(value))
    {}

    template <class OtherErr,
        enable_if_t<is_constructible_v<Error, const OtherErr&> && is_convertible_v<const OtherErr&, Error>, int> = 0>
    CANN_ASC_STL_API constexpr expected(const unexpected<OtherErr>& error) noexcept(
        is_nothrow_constructible_v<Error, const OtherErr&>)
        : base(unexpect, error.error())
    {}

    template <class OtherErr,
        enable_if_t<is_constructible_v<Error, const OtherErr&> && !is_convertible_v<const OtherErr&, Error>, int> = 0>
    CANN_ASC_STL_API constexpr explicit expected(const unexpected<OtherErr>& error) noexcept(
        is_nothrow_constructible_v<Error, const OtherErr&>)
        : base(unexpect, error.error())
    {}

    template <class OtherErr,
        enable_if_t<is_constructible_v<Error, OtherErr> && is_convertible_v<OtherErr, Error>, int> = 0>
    CANN_ASC_STL_API constexpr expected(unexpected<OtherErr>&& error) noexcept(
        is_nothrow_constructible_v<Error, OtherErr>)
        : base(unexpect, ::asc::std::move(error).error())
    {}

    template <class OtherErr,
        enable_if_t<is_constructible_v<Error, OtherErr> && !is_convertible_v<OtherErr, Error>, int> = 0>
    CANN_ASC_STL_API constexpr explicit expected(unexpected<OtherErr>&& error) noexcept(
        is_nothrow_constructible_v<Error, OtherErr>)
        : base(unexpect, ::asc::std::move(error).error())
    {}

    template <class... Args, enable_if_t<is_constructible_v<Value, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr explicit expected(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<Value, Args...>)
        : base(in_place, ::asc::std::forward<Args>(args)...)
    {}
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class Up, class... Args,
        enable_if_t<is_constructible_v<Value, ::std::initializer_list<Up>&, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr explicit expected(in_place_t, ::std::initializer_list<Up> list, Args&&... args) noexcept(
        is_nothrow_constructible_v<Value, ::std::initializer_list<Up>&, Args...>)
        : base(in_place, list, ::asc::std::forward<Args>(args)...)
    {}
#endif

    template <class... Args, enable_if_t<is_constructible_v<Error, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr explicit expected(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<Error, Args...>)
        : base(unexpect, ::asc::std::forward<Args>(args)...)
    {}
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class Up, class... Args,
        enable_if_t<is_constructible_v<Error, ::std::initializer_list<Up>&, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr explicit expected(unexpect_t, ::std::initializer_list<Up> list, Args&&... args) noexcept(
        is_nothrow_constructible_v<Error, ::std::initializer_list<Up>&, Args...>)
        : base(unexpect, list, ::asc::std::forward<Args>(args)...)
    {}
#endif

    // Copy/move assignment propagates automatically through the layered
    // (available/deleted) dispatch: the explicitly defaulted copy assignment
    // counteracts the move-member declaration's suppression of the implicit
    // copy assignment, with deleted states matching the [expected.object]
    // constraints.
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(const expected&) = default;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(expected&&) = default;

    template <class Up = Value,
        enable_if_t<!is_same_v<remove_cvref_t<Up>, expected> && !__is_asc_std_unexpected<remove_cvref_t<Up>> &&
                is_constructible_v<Value, Up> && is_assignable_v<Value&, Up> &&
                (is_nothrow_constructible_v<Value, Up> || is_nothrow_move_constructible_v<Value> ||
                    is_nothrow_move_constructible_v<Error>),
            int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(Up&& value)
    {
        if (this->__has_val_) {
            this->__value() = ::asc::std::forward<Up>(value);
        } else {
            this->__reinit_expected(this->__value(), this->__error(), ::asc::std::forward<Up>(value));
            this->__has_val_ = true;
        }
        return *this;
    }

    template <class OtherErr,
        enable_if_t<is_constructible_v<Error, const OtherErr&> && is_assignable_v<Error&, const OtherErr&> &&
                (is_nothrow_constructible_v<Error, const OtherErr&> || is_nothrow_move_constructible_v<Value> ||
                    is_nothrow_move_constructible_v<Error>),
            int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(const unexpected<OtherErr>& error)
    {
        if (this->__has_val_) {
            this->__reinit_expected(this->__error(), this->__value(), error.error());
            this->__has_val_ = false;
        } else {
            this->__error() = error.error();
        }
        return *this;
    }

    template <class OtherErr,
        enable_if_t<is_constructible_v<Error, OtherErr> && is_assignable_v<Error&, OtherErr> &&
                (is_nothrow_constructible_v<Error, OtherErr> || is_nothrow_move_constructible_v<Value> ||
                    is_nothrow_move_constructible_v<Error>),
            int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(unexpected<OtherErr>&& error)
    {
        if (this->__has_val_) {
            this->__reinit_expected(this->__error(), this->__value(),
                ::asc::std::move(error).error());  // NOLINT(build/include_what_you_use)
            this->__has_val_ = false;
        } else {
            this->__error() = ::asc::std::move(error).error();  // NOLINT(build/include_what_you_use)
        }
        return *this;
    }

    template <class... Args, enable_if_t<is_nothrow_constructible_v<Value, Args...>, int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 Value& emplace(Args&&... args) noexcept
    {
        if (this->__has_val_) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__value()));
        } else {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__error()));
            this->__has_val_ = true;
        }
        return *(
            ::asc::std::__construct_at(::asc::std::addressof(this->__value()), ::asc::std::forward<Args>(args)...));
    }
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class Up, class... Args,
        enable_if_t<is_nothrow_constructible_v<Value, ::std::initializer_list<Up>&, Args...>, int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 Value& emplace(
        ::std::initializer_list<Up> list, Args&&... args) noexcept
    {
        if (this->__has_val_) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__value()));
        } else {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__error()));
            this->__has_val_ = true;
        }
        return *(::asc::std::__construct_at(
            ::asc::std::addressof(this->__value()), list, ::asc::std::forward<Args>(args)...));
    }
#endif

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void swap(expected& other) noexcept(
        is_nothrow_move_constructible_v<Value> && is_nothrow_swappable_v<Value> &&
        is_nothrow_move_constructible_v<Error> && is_nothrow_swappable_v<Error>)
    {
        static_assert(__expected_can_swap_v<Value, Error>,
            "expected::swap requires both alternatives to be swappable and move constructible, with at "
            "least one nothrow move constructible");
        if (this->__has_val_) {
            if (other.__has_val_) {
                ::asc::std::swap(this->__value(), other.__value());
            } else {
                this->__swap_val_unex_impl(*this, other);
            }
        } else {
            if (other.__has_val_) {
                this->__swap_val_unex_impl(other, *this);
            } else {
                ::asc::std::swap(this->__error(), other.__error());
            }
        }
    }
    template <class Value2 = Value, class Error2 = Error, enable_if_t<__expected_can_swap_v<Value2, Error2>, int> = 0>
    CANN_ASC_STL_API friend CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void swap(expected& left, expected& right) noexcept(
        is_nothrow_move_constructible_v<Value2> && is_nothrow_swappable_v<Value2> &&
        is_nothrow_move_constructible_v<Error2> && is_nothrow_swappable_v<Error2>)
    {
        left.swap(right);
    }

    CANN_ASC_STL_API constexpr explicit operator bool() const noexcept
    {
        return this->__has_val_;
    }
    CANN_ASC_STL_API constexpr bool has_value() const noexcept
    {
        return this->__has_val_;
    }

    CANN_ASC_STL_API constexpr Value& operator*() & noexcept
    {
        return this->__value();
    }
    CANN_ASC_STL_API constexpr const Value& operator*() const& noexcept
    {
        return this->__value();
    }
    CANN_ASC_STL_API constexpr Value&& operator*() && noexcept
    {
        return ::asc::std::move(this->__value());  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API constexpr const Value&& operator*() const&& noexcept
    {
        return ::asc::std::move(this->__value());  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API constexpr Value* operator->() noexcept
    {
        return ::asc::std::addressof(this->__value());
    }
    CANN_ASC_STL_API constexpr const Value* operator->() const noexcept
    {
        return ::asc::std::addressof(this->__value());
    }

    // The throwing value() access stays outside the delivered product scope.
    Value& value() & = delete;
    const Value& value() const& = delete;

    CANN_ASC_STL_API constexpr Error& error() & noexcept
    {
        return this->__error();
    }
    CANN_ASC_STL_API constexpr const Error& error() const& noexcept
    {
        return this->__error();
    }
    CANN_ASC_STL_API constexpr Error&& error() && noexcept
    {
        return ::asc::std::move(this->__error());  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API constexpr const Error&& error() const&& noexcept
    {
        return ::asc::std::move(this->__error());  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_API constexpr Value value_or(const Value& fallback) const
    {
        return this->__has_val_ ? this->__value() : fallback;
    }
    template <class _Up>
    CANN_ASC_STL_API constexpr Value value_or(_Up&& fallback) const&
    {
        return this->__has_val_ ? this->__value() : static_cast<Value>(::asc::std::forward<_Up>(fallback));
    }
    template <class _Up>
    CANN_ASC_STL_API constexpr Value value_or(_Up&& fallback) &&
    {
        return this->__has_val_ ? ::asc::std::move(this->__value()) :  // NOLINT(build/include_what_you_use)
                                  static_cast<Value>(::asc::std::forward<_Up>(fallback));
    }

    template <class G>
    CANN_ASC_STL_API constexpr Error error_or(G&& default_error) const&
    {
        return this->__has_val_ ? static_cast<Error>(::asc::std::forward<G>(default_error)) : this->__error();
    }
    template <class G>
    CANN_ASC_STL_API constexpr Error error_or(G&& default_error) &&
    {
        return this->__has_val_ ? static_cast<Error>(::asc::std::forward<G>(default_error)) :
                                  ::asc::std::move(this->__error());  // NOLINT(build/include_what_you_use)
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& function) &
    {
        using _Result = decltype(::asc::std::forward<_Fun>(function)(this->__value()));
        return this->__has_val_ ? ::asc::std::forward<_Fun>(function)(this->__value()) :
                                  _Result(unexpect, this->__error());
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& function) const&
    {
        using _Result = decltype(::asc::std::forward<_Fun>(function)(::asc::std::as_const(this->__value())));
        return this->__has_val_ ? ::asc::std::forward<_Fun>(function)(::asc::std::as_const(this->__value())) :
                                  _Result(unexpect, this->__error());
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& function) &&
    {
        using _Result = decltype(::asc::std::forward<_Fun>(function)(
            ::asc::std::move(this->__value())));  // NOLINT(build/include_what_you_use)
        return this->__has_val_ ? ::asc::std::forward<_Fun>(function)(
                                      ::asc::std::move(this->__value())) :  // NOLINT(build/include_what_you_use)
            _Result(unexpect, ::asc::std::move(this->__error()));           // NOLINT(build/include_what_you_use)
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& function) const&&
    {
        using _Result = decltype(::asc::std::forward<_Fun>(function)(
            ::asc::std::move(::asc::std::as_const(this->__value()))));  // NOLINT(build/include_what_you_use)
        return this->__has_val_ ? ::asc::std::forward<_Fun>(function)(::asc::std::move(
                                      ::asc::std::as_const(this->__value()))) :  // NOLINT(build/include_what_you_use)
            _Result(unexpect, ::asc::std::move(this->__error()));                // NOLINT(build/include_what_you_use)
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& function) &
    {
        using _Result = decltype(::asc::std::forward<_Fun>(function)(this->__error()));
        return this->__has_val_ ? _Result(this->__value()) : ::asc::std::forward<_Fun>(function)(this->__error());
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& function) const&
    {
        using _Result = decltype(::asc::std::forward<_Fun>(function)(::asc::std::as_const(this->__error())));
        return this->__has_val_ ? _Result(this->__value()) :
                                  ::asc::std::forward<_Fun>(function)(::asc::std::as_const(this->__error()));
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& function) &&
    {
        using _Result = decltype(::asc::std::forward<_Fun>(function)(
            ::asc::std::move(this->__error())));                                // NOLINT(build/include_what_you_use)
        return this->__has_val_ ? _Result(::asc::std::move(this->__value())) :  // NOLINT(build/include_what_you_use)
                                  ::asc::std::forward<_Fun>(function)(
                ::asc::std::move(this->__error()));  // NOLINT(build/include_what_you_use)
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& function) const&&
    {
        using _Result = decltype(::asc::std::forward<_Fun>(function)(
            ::asc::std::move(::asc::std::as_const(this->__error()))));  // NOLINT(build/include_what_you_use)
        return this->__has_val_ ? _Result(this->__value()) :
                                  ::asc::std::forward<_Fun>(function)(::asc::std::move(
                                      ::asc::std::as_const(this->__error())));  // NOLINT(build/include_what_you_use)
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform(_Fun&& function) &  // NOLINT(build/include_what_you_use)
    {
        using _Result = expected<decltype(::asc::std::forward<_Fun>(function)(this->__value())), Error>;
        return this->__has_val_ ? _Result(::asc::std::forward<_Fun>(function)(this->__value())) :
                                  _Result(unexpect, this->__error());
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform(_Fun&& function) const&
    {
        using _Result =
            expected<decltype(::asc::std::forward<_Fun>(function)(::asc::std::as_const(this->__value()))), Error>;
        return this->__has_val_ ? _Result(::asc::std::forward<_Fun>(function)(::asc::std::as_const(this->__value()))) :
                                  _Result(unexpect, this->__error());
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform(_Fun&& function) &&
    {
        using _Result = expected<decltype(::asc::std::forward<_Fun>(function)(
                                     ::asc::std::move(this->__value()))),  // NOLINT(build/include_what_you_use)
            Error>;
        return this->__has_val_ ? _Result(::asc::std::forward<_Fun>(function)(
                                      ::asc::std::move(this->__value()))) :  // NOLINT(build/include_what_you_use)
            _Result(unexpect, ::asc::std::move(this->__error()));            // NOLINT(build/include_what_you_use)
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform(_Fun&& function) const&&  // NOLINT(build/include_what_you_use)
    {
        using _Result = expected<decltype(::asc::std::forward<_Fun>(function)(::asc::std::move(
                                     ::asc::std::as_const(this->__value())))),  // NOLINT(build/include_what_you_use)
            Error>;
        return this->__has_val_ ? _Result(::asc::std::forward<_Fun>(function)(::asc::std::move(
                                      ::asc::std::as_const(this->__value())))) :  // NOLINT(build/include_what_you_use)
            _Result(unexpect, ::asc::std::move(this->__error()));                 // NOLINT(build/include_what_you_use)
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& function) &
    {
        using _Result = expected<Value, decltype(::asc::std::forward<_Fun>(function)(this->__error()))>;
        return this->__has_val_ ? _Result(this->__value()) :
                                  _Result(unexpect, ::asc::std::forward<_Fun>(function)(this->__error()));
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& function) const&
    {
        using _Result =
            expected<Value, decltype(::asc::std::forward<_Fun>(function)(::asc::std::as_const(this->__error())))>;
        return this->__has_val_ ?
            _Result(this->__value()) :
            _Result(unexpect, ::asc::std::forward<_Fun>(function)(::asc::std::as_const(this->__error())));
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& function) &&
    {
        using _Result = expected<Value,
            decltype(::asc::std::forward<_Fun>(function)(
                ::asc::std::move(this->__error())))>;                           // NOLINT(build/include_what_you_use)
        return this->__has_val_ ? _Result(::asc::std::move(this->__value())) :  // NOLINT(build/include_what_you_use)
                                  _Result(unexpect,
                                      ::asc::std::forward<_Fun>(function)(
                    ::asc::std::move(this->__error())));  // NOLINT(build/include_what_you_use)
    }
    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& function) const&&
    {
        using _Result = expected<Value,
            decltype(::asc::std::forward<_Fun>(function)(
                ::asc::std::move(::asc::std::as_const(this->__error()))))>;  // NOLINT(build/include_what_you_use)
        return this->__has_val_ ?
            _Result(this->__value()) :
            _Result(unexpect,
                ::asc::std::forward<_Fun>(function)(
                    ::asc::std::move(::asc::std::as_const(this->__error()))));  // NOLINT(build/include_what_you_use)
    }

    // [expected.object.eq]: value states compare values, error states compare
    // errors; a mixed value/error comparison holds only between same-state operands.
    friend CANN_ASC_STL_API constexpr bool operator==(const expected& left, const expected& right) noexcept(
        noexcept(static_cast<bool>(left.__value() == right.__value())) &&
        noexcept(static_cast<bool>(left.__error() == right.__error())))
    {
        if (left.__has_val_ != right.__has_val_) {
            return false;
        }
        return left.__has_val_ ? static_cast<bool>(left.__value() == right.__value()) :
                                 static_cast<bool>(left.__error() == right.__error());
    }
#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    friend CANN_ASC_STL_API constexpr bool operator!=(const expected& left, const expected& right) noexcept(
        noexcept(static_cast<bool>(left.__value() == right.__value())) &&
        noexcept(static_cast<bool>(left.__error() == right.__error())))
    {
        return !(left == right);
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    template <class T2, class E2, enable_if_t<!is_void_v<T2>, int> = 0>
    friend CANN_ASC_STL_API constexpr bool operator==(const expected& left, const expected<T2, E2>& right) noexcept(
        noexcept(static_cast<bool>(left.__value() == right.__value())) &&
        noexcept(static_cast<bool>(left.__error() == right.__error())))
    {
        if (left.__has_val_ != right.__has_val_) {
            return false;
        }
        return left.__has_val_ ? static_cast<bool>(left.__value() == right.__value()) :
                                 static_cast<bool>(left.__error() == right.__error());
    }
#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    template <class T2, class E2, enable_if_t<!is_void_v<T2>, int> = 0>
    friend CANN_ASC_STL_API constexpr bool operator!=(const expected& left, const expected<T2, E2>& right) noexcept(
        noexcept(static_cast<bool>(left.__value() == right.__value())) &&
        noexcept(static_cast<bool>(left.__error() == right.__error())))
    {
        return !(left == right);
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    template <class T2, enable_if_t<!__is_asc_std_expected_nonvoid_v<T2>, int> = 0>
    friend CANN_ASC_STL_API constexpr bool operator==(const expected& left, const T2& value) noexcept(
        noexcept(static_cast<bool>(left.__value() == value)))
    {
        return left.__has_val_ && static_cast<bool>(left.__value() == value);
    }
#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    template <class T2, enable_if_t<!__is_asc_std_expected_nonvoid_v<T2>, int> = 0>
    friend CANN_ASC_STL_API constexpr bool operator==(const T2& value, const expected& left) noexcept(
        noexcept(static_cast<bool>(left.__value() == value)))
    {
        return left == value;
    }
    template <class T2, enable_if_t<!__is_asc_std_expected_nonvoid_v<T2>, int> = 0>
    friend CANN_ASC_STL_API constexpr bool operator!=(const expected& left, const T2& value) noexcept(
        noexcept(static_cast<bool>(left.__value() == value)))
    {
        return !left.__has_val_ || static_cast<bool>(left.__value() != value);
    }
    template <class T2, enable_if_t<!__is_asc_std_expected_nonvoid_v<T2>, int> = 0>
    friend CANN_ASC_STL_API constexpr bool operator!=(const T2& value, const expected& left) noexcept(
        noexcept(static_cast<bool>(left.__value() == value)))
    {
        return !(left == value);
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()

    template <class E2>
    friend CANN_ASC_STL_API constexpr bool operator==(const expected& left, const unexpected<E2>& error) noexcept(
        noexcept(static_cast<bool>(left.__error() == error.error())))
    {
        return !left.__has_val_ && static_cast<bool>(left.__error() == error.error());
    }
#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
    template <class E2>
    friend CANN_ASC_STL_API constexpr bool operator==(const unexpected<E2>& error, const expected& left) noexcept(
        noexcept(static_cast<bool>(left.__error() == error.error())))
    {
        return left == error;
    }
    template <class E2>
    friend CANN_ASC_STL_API constexpr bool operator!=(const expected& left, const unexpected<E2>& error) noexcept(
        noexcept(static_cast<bool>(left.__error() != error.error())))
    {
        return left.__has_val_ || static_cast<bool>(left.__error() != error.error());
    }
    template <class E2>
    friend CANN_ASC_STL_API constexpr bool operator!=(const unexpected<E2>& error, const expected& left) noexcept(
        noexcept(static_cast<bool>(left.__error() != error.error())))
    {
        return !(left == error);
    }
#endif  // !CANN_ASC_STL_DETAIL_HAS_CXX20()
};

template <class Error>
class expected<void, Error>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___EXPECTED_EXPECTED_H
