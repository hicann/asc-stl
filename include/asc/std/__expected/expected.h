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

#ifndef CANN_ASC_STL_STD_DETAIL_EXPECTED_EXPECTED_H
#define CANN_ASC_STL_STD_DETAIL_EXPECTED_EXPECTED_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/invocable.h>
#include <asc/std/__expected/bad_expected_access.h>
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
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __expected {
template <class _Tp, class _Err>
inline constexpr bool __valid_expected = !is_reference_v<_Tp> && !is_function_v<_Tp> &&
    !is_same_v<remove_cv_t<_Tp>, in_place_t> && !is_same_v<remove_cv_t<_Tp>, unexpect_t> &&
    !__is_asc_std_unexpected<remove_cv_t<_Tp>> && __unexpected::__valid_unexpected<_Err>;

template <class _Tp, class _Err>
inline constexpr bool __can_swap = is_swappable_v<_Tp> && is_swappable_v<_Err> && is_move_constructible_v<_Tp> &&
    is_move_constructible_v<_Err> && (is_nothrow_move_constructible_v<_Tp> || is_nothrow_move_constructible_v<_Err>);

template <class _Err>
inline constexpr bool __can_swap<void, _Err> = is_swappable_v<_Err> && is_move_constructible_v<_Err>;
}  // namespace __expected

template <class _Tp, class _Err>
class expected : private __expected_move_assign<_Tp, _Err> {
    using __base = __expected_move_assign<_Tp, _Err>;

    static_assert(__expected::__valid_expected<_Tp, _Err>,
        "[expected.object.general] A program that instantiates the definition of template expected<T, E> for a "
        "reference type, a function type, or for possibly cv-qualified types in_place_t, unexpect_t, or a "
        "specialization of unexpected for the T parameter is ill-formed. A program that instantiates the "
        "definition of the template expected<T, E> with a type for the E parameter that is not a valid "
        "template argument for unexpected is ill-formed.");

    template <class, class>
    friend class expected;

public:
    using value_type = _Tp;
    using error_type = _Err;
    using unexpected_type = unexpected<_Err>;

    template <class _Up>
    using rebind = expected<_Up, error_type>;

    // [expected.object.ctor], constructors
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_default_constructible_v<_Tp2>)
    CANN_ASC_STL_API constexpr expected() noexcept(is_nothrow_default_constructible_v<_Tp2>) : __base(true)
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr expected(const expected&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr expected(expected&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr expected& operator=(const expected&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr expected& operator=(expected&&) = default;

private:
    template <class _Up, class _OtherErr, class _UfQual, class _OtherErrQual>
    static constexpr bool __can_convert = is_constructible_v<_Tp, _UfQual> && is_constructible_v<_Err, _OtherErrQual> &&
        !is_constructible_v<_Tp, expected<_Up, _OtherErr>&>    //
        && !is_constructible_v<_Tp, expected<_Up, _OtherErr>>  //
        && !is_constructible_v<_Tp, const expected<_Up, _OtherErr>&> &&
        !is_constructible_v<_Tp, const expected<_Up, _OtherErr>>  //
        && !is_convertible_v<expected<_Up, _OtherErr>&, _Tp>      //
        && !is_convertible_v<expected<_Up, _OtherErr>&&, _Tp>     //
        && !is_convertible_v<const expected<_Up, _OtherErr>&, _Tp> &&
        !is_convertible_v<const expected<_Up, _OtherErr>&&, _Tp> &&
        !is_constructible_v<unexpected<_Err>, expected<_Up, _OtherErr>&> &&
        !is_constructible_v<unexpected<_Err>, expected<_Up, _OtherErr>> &&
        !is_constructible_v<unexpected<_Err>, const expected<_Up, _OtherErr>&> &&
        !is_constructible_v<unexpected<_Err>, const expected<_Up, _OtherErr>>;

public:
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert<_Up, _OtherErr, const _Up&, const _OtherErr&> CANN_ASC_STL_DETAIL_ACCL_AND
            is_convertible_v<const _Up&, _Tp>
                CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<const _OtherErr&, _Err>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected(const expected<_Up, _OtherErr>& __other) noexcept(
        is_nothrow_constructible_v<_Tp, const _Up&> &&
        is_nothrow_constructible_v<_Err, const _OtherErr&>)  // strengthened
        : __base(__other.__has_val_)
    {
        if (__other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__val_), __other.__union_.__val_);
        } else {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), __other.__union_.__unex_);
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert<_Up, _OtherErr, const _Up&, const _OtherErr&> CANN_ASC_STL_DETAIL_ACCL_AND(
            !is_convertible_v<const _Up&, _Tp> || !is_convertible_v<const _OtherErr&, _Err>))
    CANN_ASC_STL_API
    CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 explicit expected(const expected<_Up, _OtherErr>& __other) noexcept(
        is_nothrow_constructible_v<_Tp, const _Up&> &&
        is_nothrow_constructible_v<_Err, const _OtherErr&>)  // strengthened
        : __base(__other.__has_val_)
    {
        if (__other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__val_), __other.__union_.__val_);
        } else {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), __other.__union_.__unex_);
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert<_Up, _OtherErr, _Up, _OtherErr> CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_Up, _Tp>
            CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_OtherErr, _Err>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected(expected<_Up, _OtherErr>&& __other) noexcept(
        is_nothrow_constructible_v<_Tp, _Up> && is_nothrow_constructible_v<_Err, _OtherErr>)  // strengthened
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

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_convert<_Up, _OtherErr, _Up, _OtherErr> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_convertible_v<_Up, _Tp> || !is_convertible_v<_OtherErr, _Err>))
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 explicit expected(expected<_Up, _OtherErr>&& __other) noexcept(
        is_nothrow_constructible_v<_Tp, _Up> && is_nothrow_constructible_v<_Err, _OtherErr>)  // strengthened
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

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_same_v<remove_cvref_t<_Up>, in_place_t>)CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<expected, remove_cvref_t<_Up>>)
            CANN_ASC_STL_DETAIL_ACCL_AND(!__is_asc_std_unexpected<remove_cvref_t<_Up>>)
                CANN_ASC_STL_DETAIL_ACCL_AND is_constructible_v<_Tp, _Up>
                    CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_Up, _Tp>)
    CANN_ASC_STL_API constexpr expected(_Up&& __u) noexcept(is_nothrow_constructible_v<_Tp, _Up>)  // strengthened
        : __base(in_place_t{}, ::asc::std::forward<_Up>(__u))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_same_v<remove_cvref_t<_Up>, in_place_t>)CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<expected, remove_cvref_t<_Up>>)
            CANN_ASC_STL_DETAIL_ACCL_AND(!__is_asc_std_unexpected<remove_cvref_t<_Up>>)
                CANN_ASC_STL_DETAIL_ACCL_AND is_constructible_v<_Tp, _Up>
                    CANN_ASC_STL_DETAIL_ACCL_AND(!is_convertible_v<_Up, _Tp>))
    CANN_ASC_STL_API constexpr explicit expected(_Up&& __u) noexcept(
        is_nothrow_constructible_v<_Tp, _Up>)  // strengthened
        : __base(in_place_t{}, ::asc::std::forward<_Up>(__u))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, const _OtherErr&> CANN_ASC_STL_DETAIL_ACCL_AND
            is_convertible_v<const _OtherErr&, _Err>)
    CANN_ASC_STL_API constexpr expected(const unexpected<_OtherErr>& __unex) noexcept(
        is_nothrow_constructible_v<_Err, const _OtherErr&>)  // strengthened
        : __base(unexpect, __unex.error())
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, const _OtherErr&> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_convertible_v<const _OtherErr&, _Err>))
    CANN_ASC_STL_API constexpr explicit expected(const unexpected<_OtherErr>& __unex) noexcept(
        is_nothrow_constructible_v<_Err, const _OtherErr&>)  // strengthened
        : __base(unexpect, __unex.error())
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_constructible_v<_Err, _OtherErr> CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_OtherErr, _Err>)
    CANN_ASC_STL_API constexpr expected(unexpected<_OtherErr>&& __unex) noexcept(
        is_nothrow_constructible_v<_Err, _OtherErr>)  // strengthened
        : __base(unexpect, ::asc::std::move(__unex.error()))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_constructible_v<_Err, _OtherErr> CANN_ASC_STL_DETAIL_ACCL_AND(!is_convertible_v<_OtherErr, _Err>))
    CANN_ASC_STL_API constexpr explicit expected(unexpected<_OtherErr>&& __unex) noexcept(
        is_nothrow_constructible_v<_Err, _OtherErr>)  // strengthened
        : __base(unexpect, ::asc::std::move(__unex.error()))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit expected(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)  // strengthened
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, initializer_list<_Up>&, _Args...>)
    CANN_ASC_STL_API constexpr explicit expected(in_place_t, initializer_list<_Up> __il, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, initializer_list<_Up>&, _Args...>)  // strengthened
        : __base(in_place_t{}, __il, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, _Args...>)
    CANN_ASC_STL_API constexpr explicit expected(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)  // strengthened
        : __base(unexpect, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, initializer_list<_Up>&, _Args...>)
    CANN_ASC_STL_API constexpr explicit expected(unexpect_t, initializer_list<_Up> __il, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, initializer_list<_Up>&, _Args...>)  // strengthened
        : __base(unexpect, __il, ::asc::std::forward<_Args>(__args)...)
    {}

private:
    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr expected(__expected_construct_from_invoke_tag, in_place_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Tp, invoke_result_t<_Fun, _Args...>>)
        : __base(__expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...)
    {}

    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr expected(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __base(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...)
    {}

public:
    // [expected.object.assign], assignment
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_same_v<expected, remove_cvref_t<_Up>>)CANN_ASC_STL_DETAIL_ACCL_AND(
        !__is_asc_std_unexpected<remove_cvref_t<_Up>>) CANN_ASC_STL_DETAIL_ACCL_AND is_constructible_v<_Tp, _Up>
            CANN_ASC_STL_DETAIL_ACCL_AND is_assignable_v<_Tp&, _Up>
                CANN_ASC_STL_DETAIL_ACCL_AND(is_nothrow_constructible_v<_Tp, _Up> ||
                    is_nothrow_move_constructible_v<_Tp> || is_nothrow_move_constructible_v<_Err>))
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(_Up&& __v)
    {
        if (this->__has_val_) {
            this->__union_.__val_ = ::asc::std::forward<_Up>(__v);
        } else {
            this->__reinit_expected(this->__union_.__val_, this->__union_.__unex_, ::asc::std::forward<_Up>(__v));
            this->__has_val_ = true;
        }
        return *this;
    }

private:
    template <class _OtherErrQual>
    static constexpr bool __can_assign_from_unexpected =
        is_constructible_v<_Err, _OtherErrQual> && is_assignable_v<_Err&, _OtherErrQual> &&
        (is_nothrow_constructible_v<_Err, _OtherErrQual> || is_nothrow_move_constructible_v<_Tp> ||
            is_nothrow_move_constructible_v<_Err>);

public:
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_assign_from_unexpected<const _OtherErr&>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(const unexpected<_OtherErr>& __un)
    {
        if (this->__has_val_) {
            this->__reinit_expected(this->__union_.__unex_, this->__union_.__val_, __un.error());
            this->__has_val_ = false;
        } else {
            this->__union_.__unex_ = __un.error();
        }
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_assign_from_unexpected<_OtherErr>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(unexpected<_OtherErr>&& __un)
    {
        if (this->__has_val_) {
            this->__reinit_expected(this->__union_.__unex_, this->__union_.__val_, ::asc::std::move(__un.error()));
            this->__has_val_ = false;
        } else {
            this->__union_.__unex_ = ::asc::std::move(__un.error());
        }
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_nothrow_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 _Tp& emplace(_Args&&... __args) noexcept
    {
        if (this->__has_val_) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__union_.__val_));
        } else {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__union_.__unex_));
            this->__has_val_ = true;
        }
        return *::asc::std::__construct_at(
            ::asc::std::addressof(this->__union_.__val_), ::asc::std::forward<_Args>(__args)...);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_nothrow_constructible_v<_Tp, initializer_list<_Up>&, _Args...>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 _Tp& emplace(
        initializer_list<_Up> __il, _Args&&... __args) noexcept
    {
        if (this->__has_val_) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__union_.__val_));
        } else {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__union_.__unex_));
            this->__has_val_ = true;
        }
        return *::asc::std::__construct_at(
            ::asc::std::addressof(this->__union_.__val_), __il, ::asc::std::forward<_Args>(__args)...);
    }

public:
    // [expected.object.swap], swap
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp2 = _Tp, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__expected::__can_swap<_Tp2, _Err2>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void swap(expected<_Tp2, _Err>& __rhs) noexcept(
        is_nothrow_move_constructible_v<_Tp2> && is_nothrow_swappable_v<_Tp2> &&
        is_nothrow_move_constructible_v<_Err> && is_nothrow_swappable_v<_Err>)
    {
        if (this->__has_val_) {
            if (__rhs.__has_val_) {
                using ::asc::std::swap;
                swap(this->__union_.__val_, __rhs.__union_.__val_);
            } else {
                this->__swap_val_unex_impl(*this, __rhs);
            }
        } else {
            if (__rhs.__has_val_) {
                this->__swap_val_unex_impl(__rhs, *this);
            } else {
                using ::asc::std::swap;
                swap(this->__union_.__unex_, __rhs.__union_.__unex_);
            }
        }
    }

    template <class _Tp2 = _Tp, class _Err2 = _Err>
    CANN_ASC_STL_API friend CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 auto swap(expected& __x, expected& __y) noexcept(
        is_nothrow_move_constructible_v<_Tp2> && is_nothrow_swappable_v<_Tp2> &&
        is_nothrow_move_constructible_v<_Err2> && is_nothrow_swappable_v<_Err2>)
        CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES(void)(__expected::__can_swap<_Tp2, _Err2>)
    {
        return __x.swap(__y);  // some compiler warn about non void function without return
    }

    // [expected.object.obs], observers
    CANN_ASC_STL_API constexpr const _Tp* operator->() const noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(this->__has_val_, "expected::operator-> requires the expected to contain a value");
        return ::asc::std::addressof(this->__union_.__val_);
    }

    CANN_ASC_STL_API constexpr _Tp* operator->() noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(this->__has_val_, "expected::operator-> requires the expected to contain a value");
        return ::asc::std::addressof(this->__union_.__val_);
    }

    CANN_ASC_STL_API constexpr const _Tp& operator*() const& noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(this->__has_val_, "expected::operator* requires the expected to contain a value");
        return this->__union_.__val_;
    }

    CANN_ASC_STL_API constexpr _Tp& operator*() & noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(this->__has_val_, "expected::operator* requires the expected to contain a value");
        return this->__union_.__val_;
    }

    CANN_ASC_STL_API constexpr const _Tp&& operator*() const&& noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(this->__has_val_, "expected::operator* requires the expected to contain a value");
        return ::asc::std::move(this->__union_.__val_);
    }

    CANN_ASC_STL_API constexpr _Tp&& operator*() && noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(this->__has_val_, "expected::operator* requires the expected to contain a value");
        return ::asc::std::move(this->__union_.__val_);
    }

    CANN_ASC_STL_API constexpr explicit operator bool() const noexcept
    {
        return this->__has_val_;
    }

    CANN_ASC_STL_API constexpr bool has_value() const noexcept
    {
        return this->__has_val_;
    }

    CANN_ASC_STL_API constexpr const _Tp& value() const&
    {
        static_assert(is_copy_constructible_v<_Err>, "expected::value() const& requires is_copy_constructible_v<E>");
        if (!this->__has_val_) {
            __throw_bad_expected_access<_Err>(this->__union_.__unex_);
        }
        return this->__union_.__val_;
    }

    CANN_ASC_STL_API constexpr _Tp& value() &
    {
        static_assert(is_copy_constructible_v<_Err>, "expected::value() & requires is_copy_constructible_v<E>");
        if (!this->__has_val_) {
            __throw_bad_expected_access<_Err>(::asc::std::as_const(this->__union_.__unex_));
        }
        return this->__union_.__val_;
    }

    CANN_ASC_STL_API constexpr const _Tp&& value() const&&
    {
        static_assert(is_copy_constructible_v<_Err>, "expected::value() const&& requires is_copy_constructible_v<E>");
        static_assert(is_constructible_v<_Err, decltype(::asc::std::move(error()))>,
            "expected::value() const&& requires is_constructible_v<E, decltype(::asc::std::move(error()))>");
        if (!this->__has_val_) {
            __throw_bad_expected_access<_Err>(::asc::std::move(this->__union_.__unex_));
        }
        return ::asc::std::move(this->__union_.__val_);
    }

    CANN_ASC_STL_API constexpr _Tp&& value() &&
    {
        static_assert(is_copy_constructible_v<_Err>, "expected::value() && requires is_copy_constructible_v<E>");
        static_assert(is_constructible_v<_Err, decltype(::asc::std::move(error()))>,
            "expected::value() && requires is_constructible_v<E, decltype(::asc::std::move(error()))>");
        if (!this->__has_val_) {
            __throw_bad_expected_access<_Err>(::asc::std::move(this->__union_.__unex_));
        }
        return ::asc::std::move(this->__union_.__val_);
    }

    CANN_ASC_STL_API constexpr const _Err& error() const& noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(!this->__has_val_, "expected::error requires the expected to contain an error");
        return this->__union_.__unex_;
    }

    CANN_ASC_STL_API constexpr _Err& error() & noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(!this->__has_val_, "expected::error requires the expected to contain an error");
        return this->__union_.__unex_;
    }

    CANN_ASC_STL_API constexpr const _Err&& error() const&& noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(!this->__has_val_, "expected::error requires the expected to contain an error");
        return ::asc::std::move(this->__union_.__unex_);
    }

    CANN_ASC_STL_API constexpr _Err&& error() && noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(!this->__has_val_, "expected::error requires the expected to contain an error");
        return ::asc::std::move(this->__union_.__unex_);
    }

    template <class _Up>
    CANN_ASC_STL_API constexpr _Tp value_or(_Up&& __v) const&
    {
        static_assert(is_copy_constructible_v<_Tp>, "value_type has to be copy constructible");
        static_assert(is_convertible_v<_Up, _Tp>, "argument has to be convertible to value_type");
        return this->__has_val_ ? this->__union_.__val_ : static_cast<_Tp>(::asc::std::forward<_Up>(__v));
    }

    template <class _Up>
    CANN_ASC_STL_API constexpr _Tp value_or(_Up&& __v) &&
    {
        static_assert(is_move_constructible_v<_Tp>, "value_type has to be move constructible");
        static_assert(is_convertible_v<_Up, _Tp>, "argument has to be convertible to value_type");
        return this->__has_val_ ? ::asc::std::move(this->__union_.__val_) :
                                  static_cast<_Tp>(::asc::std::forward<_Up>(__v));
    }

    // [expected.object.monadic]
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, _Err2&>)
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& __fun) &
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, _Tp&>>;

        static_assert(__is_asc_std_expected_v<_Res>, "Result of f(value()) must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::error_type, _Err>,
            "The error type of the result of f(value()) must be the same as that of std::expected");

        if (this->__has_val_) {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), this->__union_.__val_);
        } else {
            return _Res{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_copy_constructible_v<_Err2>)
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& __fun) const&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, const _Tp&>>;

        static_assert(__is_asc_std_expected_v<_Res>, "Result of f(value()) must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::error_type, _Err>,
            "The error type of the result of f(value()) must be the same as that of std::expected");

        if (this->__has_val_) {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), this->__union_.__val_);
        } else {
            return _Res{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_move_constructible_v<_Err2>)
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& __fun) &&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, _Tp>>;

        static_assert(__is_asc_std_expected_v<_Res>, "Result of f(value()) must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::error_type, _Err>,
            "The error type of the result of f(value()) must be the same as that of std::expected");

        if (this->__has_val_) {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__val_));
        } else {
            return _Res{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, const _Err2>)
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& __fun) const&&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, const _Tp>>;

        static_assert(__is_asc_std_expected_v<_Res>, "Result of f(value()) must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::error_type, _Err>,
            "The error type of the result of f(value()) must be the same as that of std::expected");

        if (this->__has_val_) {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__val_));
        } else {
            return _Res{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp2, _Tp2&>)
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& __fun) &
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, _Err&>>;

        static_assert(__is_asc_std_expected_v<_Res>,
            "Result of std::expected::or_else must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::value_type, _Tp>,
            "The value type of the result of std::expected::or_else must be the same as that of std::expected");

        if (this->__has_val_) {
            return _Res{in_place_t{}, this->__union_.__val_};
        } else {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), this->__union_.__unex_);
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_copy_constructible_v<_Tp2>)
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& __fun) const&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, const _Err&>>;

        static_assert(__is_asc_std_expected_v<_Res>,
            "Result of std::expected::or_else must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::value_type, _Tp>,
            "The value type of the result of std::expected::or_else must be the same as that of std::expected");

        if (this->__has_val_) {
            return _Res{in_place_t{}, this->__union_.__val_};
        } else {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), this->__union_.__unex_);
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_move_constructible_v<_Tp2>)
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& __fun) &&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, _Err>>;

        static_assert(__is_asc_std_expected_v<_Res>,
            "Result of std::expected::or_else must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::value_type, _Tp>,
            "The value type of the result of std::expected::or_else must be the same as that of std::expected");

        if (this->__has_val_) {
            return _Res{in_place_t{}, ::asc::std::move(this->__union_.__val_)};
        } else {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__unex_));
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp2, const _Tp2>)
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& __fun) const&&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, const _Err>>;

        static_assert(__is_asc_std_expected_v<_Res>,
            "Result of std::expected::or_else must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::value_type, _Tp>,
            "The value type of the result of std::expected::or_else must be the same as that of std::expected");

        if (this->__has_val_) {
            return _Res{in_place_t{}, ::asc::std::move(this->__union_.__val_)};
        } else {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__unex_));
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, _Err2&> CANN_ASC_STL_DETAIL_ACCL_AND
            is_same_v<remove_cv_t<invoke_result_t<_Fun, _Tp2&>>, void>)
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) &
    {
        static_assert(invocable<_Fun, _Tp&>, "std::expected::transform requires that F must be invocable with T.");
        using _Res = remove_cv_t<invoke_result_t<_Fun, _Tp&>>;

        if (this->__has_val_) {
            ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), this->__union_.__val_);
            return expected<void, _Err>{};
        } else {
            return expected<_Res, _Err>{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, _Err2&> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<remove_cv_t<invoke_result_t<_Fun, _Tp2&>>, void>))
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) &
    {
        static_assert(invocable<_Fun, _Tp&>, "std::expected::transform requires that F must be invocable with T.");
        using _Res = remove_cv_t<invoke_result_t<_Fun, _Tp&>>;

        static_assert(__invoke_constructible<_Fun, _Tp&>,
            "std::expected::transform requires that the return type of F is constructible with the result of "
            "invoking F");
        static_assert(__expected::__valid_expected<_Res, _Err>,
            "std::expected::transform requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Res, _Err>{__expected_construct_from_invoke_tag{}, in_place_t{},
                ::asc::std::forward<_Fun>(__fun), this->__union_.__val_};
        } else {
            return expected<_Res, _Err>{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_copy_constructible_v<_Err2> CANN_ASC_STL_DETAIL_ACCL_AND
            is_same_v<remove_cv_t<invoke_result_t<_Fun, const _Tp2&>>, void>)
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) const&
    {
        static_assert(
            invocable<_Fun, const _Tp&>, "std::expected::transform requires that F must be invocable with T.");
        using _Res = remove_cv_t<invoke_result_t<_Fun, const _Tp&>>;

        if (this->__has_val_) {
            ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), this->__union_.__val_);
            return expected<_Res, _Err>{};
        } else {
            return expected<_Res, _Err>{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_copy_constructible_v<_Err2> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<remove_cv_t<invoke_result_t<_Fun, const _Tp2&>>, void>))
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) const&
    {
        static_assert(invocable<_Fun, const _Tp&>, "std::expected::transform requires that F must be invocable with T");
        using _Res = remove_cv_t<invoke_result_t<_Fun, const _Tp&>>;

        static_assert(__invoke_constructible<_Fun, const _Tp&>,
            "std::expected::transform requires that the return type of F is constructible with the result of "
            "invoking F");
        static_assert(__expected::__valid_expected<_Res, _Err>,
            "std::expected::transform requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Res, _Err>{__expected_construct_from_invoke_tag{}, in_place_t{},
                ::asc::std::forward<_Fun>(__fun), this->__union_.__val_};
        } else {
            return expected<_Res, _Err>{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_move_constructible_v<_Err2> CANN_ASC_STL_DETAIL_ACCL_AND
            is_same_v<remove_cv_t<invoke_result_t<_Fun, _Tp2>>, void>)
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) &&
    {
        static_assert(invocable<_Fun, _Tp>, "std::expected::transform requires that F must be invocable with T.");
        using _Res = remove_cv_t<invoke_result_t<_Fun, _Tp>>;

        if (this->__has_val_) {
            ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__val_));
            return expected<_Res, _Err>{};
        } else {
            return expected<_Res, _Err>{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_move_constructible_v<_Err2> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<remove_cv_t<invoke_result_t<_Fun, _Tp2>>, void>))
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) &&
    {
        static_assert(invocable<_Fun, _Tp>, "std::expected::transform requires that F must be invocable with T");
        using _Res = remove_cv_t<invoke_result_t<_Fun, _Tp>>;

        static_assert(__invoke_constructible<_Fun, _Tp>,
            "std::expected::transform requires that the return type of F is constructible with the result of "
            "invoking F");
        static_assert(__expected::__valid_expected<_Res, _Err>,
            "std::expected::transform requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Res, _Err>{__expected_construct_from_invoke_tag{}, in_place_t{},
                ::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__val_)};
        } else {
            return expected<_Res, _Err>{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, const _Err2> CANN_ASC_STL_DETAIL_ACCL_AND
            is_same_v<remove_cv_t<invoke_result_t<_Fun, const _Tp2>>, void>)
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) const&&
    {
        static_assert(invocable<_Fun, const _Tp>, "std::expected::transform requires that F must be invocable with T.");
        using _Res = remove_cv_t<invoke_result_t<_Fun, const _Tp>>;

        if (this->__has_val_) {
            ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__val_));
            return expected<_Res, _Err>{};
        } else {
            return expected<_Res, _Err>{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, const _Err2> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<remove_cv_t<invoke_result_t<_Fun, const _Tp2>>, void>))
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) const&&
    {
        static_assert(invocable<_Fun, const _Tp>, "std::expected::transform requires that F must be invocable with T");
        using _Res = remove_cv_t<invoke_result_t<_Fun, const _Tp>>;

        static_assert(__invoke_constructible<_Fun, const _Tp>,
            "std::expected::transform requires that the return type of F is constructible with the result of "
            "invoking F");
        static_assert(__expected::__valid_expected<_Res, _Err>,
            "std::expected::transform requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Res, _Err>{__expected_construct_from_invoke_tag{}, in_place_t{},
                ::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__val_)};
        } else {
            return expected<_Res, _Err>{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp2, _Tp2&>)
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& __fun) &
    {
        static_assert(
            invocable<_Fun, _Err&>, "std::expected::transform_error requires that F must be invocable with E");
        using _Res = remove_cv_t<invoke_result_t<_Fun, _Err&>>;

        static_assert(__invoke_constructible<_Fun, _Err&>,
            "std::expected::transform_error requires that the return type of F is constructible with the result "
            "of invoking F");
        static_assert(__expected::__valid_expected<_Tp, _Res>,
            "std::expected::transform_error requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Tp, _Res>{in_place_t{}, this->__union_.__val_};
        } else {
            return expected<_Tp, _Res>{__expected_construct_from_invoke_tag{}, unexpect,
                ::asc::std::forward<_Fun>(__fun), this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_copy_constructible_v<_Tp2>)
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& __fun) const&
    {
        static_assert(
            invocable<_Fun, const _Err&>, "std::expected::transform_error requires that F must be invocable with E");
        using _Res = remove_cv_t<invoke_result_t<_Fun, const _Err&>>;

        static_assert(__invoke_constructible<_Fun, const _Err&>,
            "std::expected::transform_error requires that the return type of F is constructible with the result "
            "of invoking F");
        static_assert(__expected::__valid_expected<_Tp, _Res>,
            "std::expected::transform_error requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Tp, _Res>{in_place_t{}, this->__union_.__val_};
        } else {
            return expected<_Tp, _Res>{__expected_construct_from_invoke_tag{}, unexpect,
                ::asc::std::forward<_Fun>(__fun), this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_move_constructible_v<_Tp2>)
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& __fun) &&
    {
        static_assert(invocable<_Fun, _Err>, "std::expected::transform_error requires that F must be invocable with E");
        using _Res = remove_cv_t<invoke_result_t<_Fun, _Err>>;

        static_assert(__invoke_constructible<_Fun, _Err>,
            "std::expected::transform_error requires that the return type of F is constructible with the result "
            "of invoking F");
        static_assert(__expected::__valid_expected<_Tp, _Res>,
            "std::expected::transform_error requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Tp, _Res>{in_place_t{}, ::asc::std::move(this->__union_.__val_)};
        } else {
            return expected<_Tp, _Res>{__expected_construct_from_invoke_tag{}, unexpect,
                ::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__unex_)};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp2, const _Tp2>)
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& __fun) const&&
    {
        static_assert(
            invocable<_Fun, const _Err>, "std::expected::transform_error requires that F must be invocable with E");
        using _Res = remove_cv_t<invoke_result_t<_Fun, const _Err>>;

        static_assert(__invoke_constructible<_Fun, const _Err>,
            "std::expected::transform_error requires that the return type of F is constructible with the result "
            "of invoking F");
        static_assert(__expected::__valid_expected<_Tp, _Res>,
            "std::expected::transform_error requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Tp, _Res>{in_place_t{}, ::asc::std::move(this->__union_.__val_)};
        } else {
            return expected<_Tp, _Res>{__expected_construct_from_invoke_tag{}, unexpect,
                ::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__unex_)};
        }
    }

    // [expected.object.eq], equality operators
    CANN_ASC_STL_API friend constexpr bool operator==(const expected& __x, const expected& __y)
    {
        if (__x.__has_val_ != __y.has_value()) {
            return false;
        } else {
            if (__x.__has_val_) {
                return __x.__union_.__val_ == __y.value();
            } else {
                return __x.__union_.__unex_ == __y.error();
            }
        }
    }

#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    CANN_ASC_STL_API friend constexpr bool operator!=(const expected& __x, const expected& __y)
    {
        return !(__x == __y);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T2, class _E2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_void_v<_T2>))
    CANN_ASC_STL_API friend constexpr bool operator==(const expected& __x, const expected<_T2, _E2>& __y)
    {
        if (__x.__has_val_ != __y.has_value()) {
            return false;
        } else {
            if (__x.__has_val_) {
                return __x.__union_.__val_ == __y.value();
            } else {
                return __x.__union_.__unex_ == __y.error();
            }
        }
    }

#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T2, class _E2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!is_void_v<_T2>))
    CANN_ASC_STL_API friend constexpr bool operator!=(const expected& __x, const expected<_T2, _E2>& __y)
    {
        return !(__x == __y);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__is_asc_std_expected_nonvoid_v<_T2>))
    CANN_ASC_STL_API friend constexpr bool operator==(const expected& __x, const _T2& __v)
    {
        return __x.__has_val_ && static_cast<bool>(__x.__union_.__val_ == __v);
    }
#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__is_asc_std_expected_nonvoid_v<_T2>))
    CANN_ASC_STL_API friend constexpr bool operator==(const _T2& __v, const expected& __x)
    {
        return __x.__has_val_ && static_cast<bool>(__x.__union_.__val_ == __v);
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__is_asc_std_expected_nonvoid_v<_T2>))
    CANN_ASC_STL_API friend constexpr bool operator!=(const expected& __x, const _T2& __v)
    {
        return !__x.__has_val_ || static_cast<bool>(__x.__union_.__val_ != __v);
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__is_asc_std_expected_nonvoid_v<_T2>))
    CANN_ASC_STL_API friend constexpr bool operator!=(const _T2& __v, const expected& __x)
    {
        return !__x.__has_val_ || static_cast<bool>(__x.__union_.__val_ != __v);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020

    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator==(const expected& __x, const unexpected<_E2>& __e)
    {
        return !__x.__has_val_ && static_cast<bool>(__x.__union_.__unex_ == __e.error());
    }
#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator==(const unexpected<_E2>& __e, const expected& __x)
    {
        return !__x.__has_val_ && static_cast<bool>(__x.__union_.__unex_ == __e.error());
    }
    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator!=(const expected& __x, const unexpected<_E2>& __e)
    {
        return __x.__has_val_ || static_cast<bool>(__x.__union_.__unex_ != __e.error());
    }
    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator!=(const unexpected<_E2>& __e, const expected& __x)
    {
        return __x.__has_val_ || static_cast<bool>(__x.__union_.__unex_ != __e.error());
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020
};

template <class _Err>
class expected<void, _Err> : private __expected_move_assign<void, _Err> {
    using __base = __expected_move_assign<void, _Err>;
    static_assert(__unexpected::__valid_unexpected<_Err>,
        "[expected.void.general] A program that instantiates expected<T, E> with a E that is not a "
        "valid argument for unexpected<E> is ill-formed");

    template <class, class>
    friend class expected;

    template <class _Up, class _OtherErr, class _OtherErrQual>
    static constexpr bool __can_convert = is_void_v<_Up> && is_constructible_v<_Err, _OtherErrQual> &&
        !is_constructible_v<unexpected<_Err>, expected<_Up, _OtherErr>&> &&
        !is_constructible_v<unexpected<_Err>, expected<_Up, _OtherErr>> &&
        !is_constructible_v<unexpected<_Err>, const expected<_Up, _OtherErr>&> &&
        !is_constructible_v<unexpected<_Err>, const expected<_Up, _OtherErr>>;

public:
    using value_type = void;
    using error_type = _Err;
    using unexpected_type = unexpected<_Err>;

    template <class _Up>
    using rebind = expected<_Up, error_type>;

    // [expected.void.ctor], constructors
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr expected() = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr expected(const expected&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr expected(expected&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr expected& operator=(const expected&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr expected& operator=(expected&&) = default;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_convert<_Up, _OtherErr, const _OtherErr&> CANN_ASC_STL_DETAIL_ACCL_AND
            is_convertible_v<const _OtherErr&, _Err>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected(const expected<_Up, _OtherErr>& __other) noexcept(
        is_nothrow_constructible_v<_Err, const _OtherErr&>)  // strengthened
        : __base(__other.__has_val_)
    {
        if (!__other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), __other.__union_.__unex_);
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_convert<_Up, _OtherErr, const _OtherErr&> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_convertible_v<const _OtherErr&, _Err>))
    CANN_ASC_STL_API
    CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 explicit expected(const expected<_Up, _OtherErr>& __other) noexcept(
        is_nothrow_constructible_v<_Err, const _OtherErr&>)  // strengthened
        : __base(__other.__has_val_)
    {
        if (!__other.__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), __other.__union_.__unex_);
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert<_Up, _OtherErr, _OtherErr> CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_OtherErr, _Err>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected(expected<_Up, _OtherErr>&& __other) noexcept(
        is_nothrow_constructible_v<_Err, _OtherErr>)  // strengthened
        : __base(__other.__has_val_)
    {
        if (!__other.__has_val_) {
            ::asc::std::__construct_at(
                ::asc::std::addressof(this->__union_.__unex_), ::asc::std::move(__other.__union_.__unex_));
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __can_convert<_Up, _OtherErr, _OtherErr> CANN_ASC_STL_DETAIL_ACCL_AND(!is_convertible_v<_OtherErr, _Err>))
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 explicit expected(expected<_Up, _OtherErr>&& __other) noexcept(
        is_nothrow_constructible_v<_Err, _OtherErr>)  // strengthened
        : __base(__other.__has_val_)
    {
        if (!__other.__has_val_) {
            ::asc::std::__construct_at(
                ::asc::std::addressof(this->__union_.__unex_), ::asc::std::move(__other.__union_.__unex_));
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, const _OtherErr&> CANN_ASC_STL_DETAIL_ACCL_AND
            is_convertible_v<const _OtherErr&, _Err>)
    CANN_ASC_STL_API constexpr expected(const unexpected<_OtherErr>& __unex) noexcept(
        is_nothrow_constructible_v<_Err, const _OtherErr&>)  // strengthened
        : __base(unexpect, __unex.error())
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, const _OtherErr&> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_convertible_v<const _OtherErr&, _Err>))
    CANN_ASC_STL_API constexpr explicit expected(const unexpected<_OtherErr>& __unex) noexcept(
        is_nothrow_constructible_v<_Err, const _OtherErr&>)  // strengthened
        : __base(unexpect, __unex.error())
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_constructible_v<_Err, _OtherErr> CANN_ASC_STL_DETAIL_ACCL_AND is_convertible_v<_OtherErr, _Err>)
    CANN_ASC_STL_API constexpr expected(unexpected<_OtherErr>&& __unex) noexcept(
        is_nothrow_constructible_v<_Err, _OtherErr>)  // strengthened
        : __base(unexpect, ::asc::std::move(__unex.error()))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_constructible_v<_Err, _OtherErr> CANN_ASC_STL_DETAIL_ACCL_AND(!is_convertible_v<_OtherErr, _Err>))
    CANN_ASC_STL_API constexpr explicit expected(unexpected<_OtherErr>&& __unex) noexcept(
        is_nothrow_constructible_v<_Err, _OtherErr>)  // strengthened
        : __base(unexpect, ::asc::std::move(__unex.error()))
    {}

    CANN_ASC_STL_API constexpr explicit expected(in_place_t) noexcept : __base(true)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, _Args...>)
    CANN_ASC_STL_API constexpr explicit expected(unexpect_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, _Args...>)  // strengthened
        : __base(unexpect, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up, class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, initializer_list<_Up>&, _Args...>)
    CANN_ASC_STL_API constexpr explicit expected(unexpect_t, initializer_list<_Up> __il, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Err, initializer_list<_Up>, _Args...>)  // strengthened
        : __base(unexpect, __il, ::asc::std::forward<_Args>(__args)...)
    {}

private:
    template <class _Fun, class... _Args>
    CANN_ASC_STL_API constexpr expected(__expected_construct_from_invoke_tag, unexpect_t, _Fun&& __fun,
        _Args&&... __args) noexcept(is_nothrow_constructible_v<_Err, invoke_result_t<_Fun, _Args...>>)
        : __base(__expected_construct_from_invoke_tag{}, unexpect, ::asc::std::forward<_Fun>(__fun),
              ::asc::std::forward<_Args>(__args)...)
    {}

public:
    // [expected.void.dtor], destructor
    // [expected.void.assign], assignment
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err, const _OtherErr&> CANN_ASC_STL_DETAIL_ACCL_AND
            is_assignable_v<_Err&, const _OtherErr&>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(
        const unexpected<_OtherErr>& __un) noexcept(is_nothrow_assignable_v<_Err&, const _OtherErr&> &&
        is_nothrow_constructible_v<_Err, const _OtherErr&>)  // strengthened
    {
        if (this->__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), __un.error());
            this->__has_val_ = false;
        } else {
            this->__union_.__unex_ = __un.error();
        }
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherErr)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_constructible_v<_Err, _OtherErr> CANN_ASC_STL_DETAIL_ACCL_AND is_assignable_v<_Err&, _OtherErr>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 expected& operator=(unexpected<_OtherErr>&& __un) noexcept(
        is_nothrow_assignable_v<_Err&, _OtherErr> && is_nothrow_constructible_v<_Err, _OtherErr>)
    {
        if (this->__has_val_) {
            ::asc::std::__construct_at(::asc::std::addressof(this->__union_.__unex_), ::asc::std::move(__un.error()));
            this->__has_val_ = false;
        } else {
            this->__union_.__unex_ = ::asc::std::move(__un.error());
        }
        return *this;
    }

    CANN_ASC_STL_API constexpr void emplace() noexcept
    {
        if (!this->__has_val_) {
            this->__union_.__unex_.~_Err();
            this->__has_val_ = true;
        }
    }

    // [expected.void.swap], swap
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__expected::__can_swap<void, _Err2>)
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void swap(expected<void, _Err2>& __rhs) noexcept(
        is_nothrow_move_constructible_v<_Err2> && is_nothrow_swappable_v<_Err2>)
    {
        if (this->__has_val_) {
            if (!__rhs.__has_val_) {
                this->__swap_val_unex_impl(*this, __rhs);
            }
        } else {
            if (__rhs.__has_val_) {
                this->__swap_val_unex_impl(__rhs, *this);
            } else {
                using ::asc::std::swap;
                swap(this->__union_.__unex_, __rhs.__union_.__unex_);
            }
        }
    }

    template <class _Err2 = _Err>
    CANN_ASC_STL_API friend CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 auto swap(expected& __x, expected& __y) noexcept(
        is_nothrow_move_constructible_v<_Err2> && is_nothrow_swappable_v<_Err2>)
        CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES(void)(__expected::__can_swap<void, _Err2>)
    {
        return __x.swap(__y);  // some compiler warn about non void function without return
    }

    // [expected.void.obs], observers
    CANN_ASC_STL_API constexpr explicit operator bool() const noexcept
    {
        return this->__has_val_;
    }

    CANN_ASC_STL_API constexpr bool has_value() const noexcept
    {
        return this->__has_val_;
    }

    CANN_ASC_STL_API constexpr void operator*() const noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(this->__has_val_, "expected::operator* requires the expected to contain a value");
    }

    CANN_ASC_STL_API constexpr void value() const&
    {
        static_assert(is_copy_constructible_v<_Err>, "expected::value() const& requires is_copy_constructible_v<E>");
        if (!this->__has_val_) {
            __throw_bad_expected_access<_Err>(this->__union_.__unex_);
        }
    }

    CANN_ASC_STL_API constexpr void value() &&
    {
        static_assert(is_copy_constructible_v<_Err>, "expected::value() && requires is_copy_constructible_v<E>");
        static_assert(is_move_constructible_v<_Err>, "expected::value() && requires is_move_constructible_v<E>");
        if (!this->__has_val_) {
            __throw_bad_expected_access<_Err>(::asc::std::move(this->__union_.__unex_));
        }
    }

    CANN_ASC_STL_API constexpr const _Err& error() const& noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(!this->__has_val_, "expected::error requires the expected to contain an error");
        return this->__union_.__unex_;
    }

    CANN_ASC_STL_API constexpr _Err& error() & noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(!this->__has_val_, "expected::error requires the expected to contain an error");
        return this->__union_.__unex_;
    }

    CANN_ASC_STL_API constexpr const _Err&& error() const&& noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(!this->__has_val_, "expected::error requires the expected to contain an error");
        return ::asc::std::move(this->__union_.__unex_);
    }

    CANN_ASC_STL_API constexpr _Err&& error() && noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(!this->__has_val_, "expected::error requires the expected to contain an error");
        return ::asc::std::move(this->__union_.__unex_);
    }

    // [expected.void.monadic]
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, _Err2&>)
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& __fun) &
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun>>;

        static_assert(__is_asc_std_expected_v<_Res>, "Result of f(value()) must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::error_type, _Err>,
            "The error type of the result of f(value()) must be the same as that of std::expected");

        if (this->__has_val_) {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun));
        } else {
            return _Res{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_copy_constructible_v<_Err2>)
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& __fun) const&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun>>;

        static_assert(__is_asc_std_expected_v<_Res>, "Result of f(value()) must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::error_type, _Err>,
            "The error type of the result of f(value()) must be the same as that of std::expected");

        if (this->__has_val_) {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun));
        } else {
            return _Res{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_move_constructible_v<_Err2>)
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& __fun) &&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun>>;

        static_assert(__is_asc_std_expected_v<_Res>, "Result of f(value()) must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::error_type, _Err>,
            "The error type of the result of f(value()) must be the same as that of std::expected");

        if (this->__has_val_) {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun));
        } else {
            return _Res{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, const _Err2>)
    CANN_ASC_STL_API constexpr auto and_then(_Fun&& __fun) const&&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun>>;

        static_assert(__is_asc_std_expected_v<_Res>, "Result of f(value()) must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::error_type, _Err>,
            "The error type of the result of f(value()) must be the same as that of std::expected");

        if (this->__has_val_) {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun));
        } else {
            return _Res{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& __fun) &
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, _Err&>>;

        static_assert(__is_asc_std_expected_v<_Res>,
            "Result of std::expected::or_else must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::value_type, void>,
            "The value type of the result of std::expected::or_else must be the same as that of std::expected");

        if (this->__has_val_) {
            return _Res{};
        } else {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), this->__union_.__unex_);
        }
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& __fun) const&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, const _Err&>>;

        static_assert(__is_asc_std_expected_v<_Res>,
            "Result of std::expected::or_else must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::value_type, void>,
            "The value type of the result of std::expected::or_else must be the same as that of std::expected");

        if (this->__has_val_) {
            return _Res{};
        } else {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), this->__union_.__unex_);
        }
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& __fun) &&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, _Err>>;

        static_assert(__is_asc_std_expected_v<_Res>,
            "Result of std::expected::or_else must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::value_type, void>,
            "The value type of the result of std::expected::or_else must be the same as that of std::expected");

        if (this->__has_val_) {
            return _Res{};
        } else {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__unex_));
        }
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto or_else(_Fun&& __fun) const&&
    {
        using _Res = remove_cvref_t<invoke_result_t<_Fun, const _Err>>;

        static_assert(__is_asc_std_expected_v<_Res>,
            "Result of std::expected::or_else must be a specialization of std::expected");
        static_assert(is_same_v<typename _Res::value_type, void>,
            "The value type of the result of std::expected::or_else must be the same as that of std::expected");

        if (this->__has_val_) {
            return _Res{};
        } else {
            return ::asc::std::invoke(::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__unex_));
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, _Err2&> CANN_ASC_STL_DETAIL_ACCL_AND
            is_same_v<remove_cv_t<invoke_result_t<_Fun>>, void>)
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) &
    {
        static_assert(invocable<_Fun>, "std::expected::transform requires that F must be invocable with T.");
        if (this->__has_val_) {
            ::asc::std::invoke(::asc::std::forward<_Fun>(__fun));
            return expected<void, _Err>{};
        } else {
            return expected<void, _Err>{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, _Err2&> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<remove_cv_t<invoke_result_t<_Fun>>, void>))
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) &
    {
        static_assert(invocable<_Fun>, "std::expected::transform requires that F must be invocable with T.");
        using _Res = remove_cv_t<invoke_result_t<_Fun>>;

        static_assert(__invoke_constructible<_Fun>,
            "std::expected::transform requires that the return type of F is constructible with the result of "
            "invoking F");
        static_assert(__expected::__valid_expected<_Res, _Err>,
            "std::expected::transform requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Res, _Err>{
                __expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<_Fun>(__fun)};
        } else {
            return expected<_Res, _Err>{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_copy_constructible_v<_Err2> CANN_ASC_STL_DETAIL_ACCL_AND is_same_v<remove_cv_t<invoke_result_t<_Fun>>, void>)
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) const&
    {
        static_assert(invocable<_Fun>, "std::expected::transform requires that F must be invocable with T.");
        if (this->__has_val_) {
            ::asc::std::invoke(::asc::std::forward<_Fun>(__fun));
            return expected<void, _Err>{};
        } else {
            return expected<void, _Err>{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_copy_constructible_v<_Err2> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<remove_cv_t<invoke_result_t<_Fun>>, void>))
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) const&
    {
        static_assert(invocable<_Fun>, "std::expected::transform requires that F must be invocable with T");
        using _Res = remove_cv_t<invoke_result_t<_Fun>>;

        static_assert(__invoke_constructible<_Fun>,
            "std::expected::transform requires that the return type of F is constructible with the result of "
            "invoking F");
        static_assert(__expected::__valid_expected<_Res, _Err>,
            "std::expected::transform requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Res, _Err>{
                __expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<_Fun>(__fun)};
        } else {
            return expected<_Res, _Err>{unexpect, this->__union_.__unex_};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        is_move_constructible_v<_Err2> CANN_ASC_STL_DETAIL_ACCL_AND is_same_v<remove_cv_t<invoke_result_t<_Fun>>, void>)
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) &&
    {
        static_assert(invocable<_Fun>, "std::expected::transform requires that F must be invocable with T.");
        if (this->__has_val_) {
            ::asc::std::invoke(::asc::std::forward<_Fun>(__fun));
            return expected<void, _Err>{};
        } else {
            return expected<void, _Err>{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_move_constructible_v<_Err2> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<remove_cv_t<invoke_result_t<_Fun>>, void>))
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) &&
    {
        static_assert(invocable<_Fun>, "std::expected::transform requires that F must be invocable with T");
        using _Res = remove_cv_t<invoke_result_t<_Fun>>;

        static_assert(__invoke_constructible<_Fun>,
            "std::expected::transform requires that the return type of F is constructible with the result of "
            "invoking F");
        static_assert(__expected::__valid_expected<_Res, _Err>,
            "std::expected::transform requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Res, _Err>{
                __expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<_Fun>(__fun)};
        } else {
            return expected<_Res, _Err>{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, const _Err2> CANN_ASC_STL_DETAIL_ACCL_AND
            is_same_v<remove_cv_t<invoke_result_t<_Fun>>, void>)
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) const&&
    {
        static_assert(invocable<_Fun>, "std::expected::transform requires that F must be invocable with T.");
        if (this->__has_val_) {
            ::asc::std::invoke(::asc::std::forward<_Fun>(__fun));
            return expected<void, _Err>{};
        } else {
            return expected<void, _Err>{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Fun, class _Err2 = _Err)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Err2, const _Err2> CANN_ASC_STL_DETAIL_ACCL_AND(
        !is_same_v<remove_cv_t<invoke_result_t<_Fun>>, void>))
    CANN_ASC_STL_API constexpr auto transform(_Fun&& __fun) const&&  // NOLINT(build/include_what_you_use)
    {
        static_assert(invocable<_Fun>, "std::expected::transform requires that F must be invocable with T");
        using _Res = remove_cv_t<invoke_result_t<_Fun>>;

        static_assert(__invoke_constructible<_Fun>,
            "std::expected::transform requires that the return type of F is constructible with the result of "
            "invoking F");
        static_assert(__expected::__valid_expected<_Res, _Err>,
            "std::expected::transform requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<_Res, _Err>{
                __expected_construct_from_invoke_tag{}, in_place_t{}, ::asc::std::forward<_Fun>(__fun)};
        } else {
            return expected<_Res, _Err>{unexpect, ::asc::std::move(this->__union_.__unex_)};
        }
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& __fun) &
    {
        static_assert(
            invocable<_Fun, _Err&>, "std::expected::transform_error requires that F must be invocable with E");
        using _Res = remove_cv_t<invoke_result_t<_Fun, _Err&>>;

        static_assert(__invoke_constructible<_Fun, _Err&>,
            "std::expected::transform_error requires that the return type of F is constructible with the result "
            "of invoking F");
        static_assert(__expected::__valid_expected<void, _Res>,
            "std::expected::transform_error requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<void, _Res>{};
        } else {
            return expected<void, _Res>{__expected_construct_from_invoke_tag{}, unexpect,
                ::asc::std::forward<_Fun>(__fun), this->__union_.__unex_};
        }
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& __fun) const&
    {
        static_assert(
            invocable<_Fun, const _Err&>, "std::expected::transform_error requires that F must be invocable with E");
        using _Res = remove_cv_t<invoke_result_t<_Fun, const _Err&>>;

        static_assert(__invoke_constructible<_Fun, const _Err&>,
            "std::expected::transform_error requires that the return type of F is constructible with the result "
            "of invoking F");
        static_assert(__expected::__valid_expected<void, _Res>,
            "std::expected::transform_error requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<void, _Res>{};
        } else {
            return expected<void, _Res>{__expected_construct_from_invoke_tag{}, unexpect,
                ::asc::std::forward<_Fun>(__fun), this->__union_.__unex_};
        }
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& __fun) &&
    {
        static_assert(invocable<_Fun, _Err>, "std::expected::transform_error requires that F must be invocable with E");
        using _Res = remove_cv_t<invoke_result_t<_Fun, _Err>>;

        static_assert(__invoke_constructible<_Fun, _Err>,
            "std::expected::transform_error requires that the return type of F is constructible with the result "
            "of invoking F");
        static_assert(__expected::__valid_expected<void, _Res>,
            "std::expected::transform_error requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<void, _Res>{};
        } else {
            return expected<void, _Res>{__expected_construct_from_invoke_tag{}, unexpect,
                ::asc::std::forward<_Fun>(__fun), ::asc::std::move(this->__union_.__unex_)};
        }
    }

    template <class _Fun>
    CANN_ASC_STL_API constexpr auto transform_error(_Fun&& __fun) const&&
    {
        static_assert(
            invocable<_Fun, const _Err>, "std::expected::transform_error requires that F must be invocable with E");
        using _Res = remove_cv_t<invoke_result_t<_Fun, const _Err>>;

        static_assert(__invoke_constructible<_Fun, const _Err>,
            "std::expected::transform_error requires that the return type of F is constructible with the result "
            "of invoking F");
        static_assert(__expected::__valid_expected<void, _Res>,
            "std::expected::transform_error requires that the return type of F must be a valid argument for "
            "std::expected");

        if (this->__has_val_) {
            return expected<void, _Res>{};
        } else {
            return expected<void, _Res>{__expected_construct_from_invoke_tag{}, unexpect,
                ::asc::std::forward<_Fun>(__fun),
                ::asc::std::move(this->__union_.__unex_)};  // NOLINT(build/include_what_you_use)
        }
    }

    // [expected.void.eq], equality operators
    CANN_ASC_STL_API friend constexpr bool operator==(const expected& __x, const expected& __y) noexcept
    {
        if (__x.__has_val_ != __y.has_value()) {
            return false;
        } else {
            return __x.__has_val_ || static_cast<bool>(__x.__union_.__unex_ == __y.error());
        }
    }
#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    CANN_ASC_STL_API friend constexpr bool operator!=(const expected& __x, const expected& __y) noexcept
    {
        return !(__x == __y);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020

    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator==(const expected& __x, const expected<void, _E2>& __y) noexcept
    {
        if (__x.__has_val_ != __y.has_value()) {
            return false;
        } else {
            return __x.__has_val_ || static_cast<bool>(__x.__union_.__unex_ == __y.error());
        }
    }
#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator!=(const expected& __x, const expected<void, _E2>& __y) noexcept
    {
        return !(__x == __y);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020

    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator==(const expected& __x, const unexpected<_E2>& __y) noexcept
    {
        return !__x.__has_val_ && static_cast<bool>(__x.__union_.__unex_ == __y.error());
    }
#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator==(const unexpected<_E2>& __y, const expected& __x) noexcept
    {
        return !__x.__has_val_ && static_cast<bool>(__x.__union_.__unex_ == __y.error());
    }
    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator!=(const expected& __x, const unexpected<_E2>& __y) noexcept
    {
        return __x.__has_val_ || static_cast<bool>(__x.__union_.__unex_ != __y.error());
    }
    template <class _E2>
    CANN_ASC_STL_API friend constexpr bool operator!=(const unexpected<_E2>& __y, const expected& __x) noexcept
    {
        return __x.__has_val_ || static_cast<bool>(__x.__union_.__unex_ != __y.error());
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_EXPECTED_EXPECTED_H
