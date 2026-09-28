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

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Value, class Error>
class expected : private __expected_move_assign<Value, Error> {
    using base = __expected_move_assign<Value, Error>;
    template <class, class>
    friend class expected;

public:
    using value_type = Value;
    using error_type = Error;
    using unexpected_type = unexpected<Error>;

    CANN_ASC_STL_API constexpr expected(const Value& value) : base(in_place, value)
    {}
    CANN_ASC_STL_API constexpr expected(const unexpected<Error>& error) : base(unexpect, error.error())
    {}
    CANN_ASC_STL_API constexpr expected(unexpect_t, const Error& error) : base(unexpect, error)
    {}
    CANN_ASC_STL_API constexpr expected(const expected& other) : base(static_cast<const base&>(other))
    {}
    CANN_ASC_STL_API ~expected() = default;

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

    // Throwing value() access stays outside the frozen product boundary.
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
        return this->__has_val_ ? _Result(::asc::std::move(this->__value())) :  // NOLINT(build/include_what_you_use)
                                  ::asc::std::forward<_Fun>(function)(this->__error());
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
        return this->__has_val_ ? _Result(::asc::std::move(this->__value())) :  // NOLINT(build/include_what_you_use)
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
};

template <class Error>
class expected<void, Error>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___EXPECTED_EXPECTED_H
