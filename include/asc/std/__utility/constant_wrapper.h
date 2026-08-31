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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_CONSTANT_WRAPPER_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_CONSTANT_WRAPPER_H

#include <asc/std/detail/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif  // no system header

#if CANN_ASC_STL_DETAIL_STD_VER >= 2020

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/integer_sequence.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
struct __cw_fixed_value {
    using type = _Tp;
    CANN_ASC_STL_API consteval __cw_fixed_value(_Tp __v) noexcept : __data(__v)
    {}
    _Tp __data;
};

template <class _Tp, size_t _Extent>
struct __cw_fixed_value<_Tp[_Extent]> {
    using type = _Tp[_Extent];
    _Tp __data[_Extent];

    CANN_ASC_STL_API consteval __cw_fixed_value(_Tp (&__arr)[_Extent]) noexcept
        : __cw_fixed_value(__arr, make_index_sequence<_Extent>{})
    {}

private:
    template <size_t... _Idxs>
    CANN_ASC_STL_API consteval __cw_fixed_value(_Tp (&__arr)[_Extent], index_sequence<_Idxs...>) noexcept
        : __data{__arr[_Idxs]...}
    {}
};

template <class _Tp, size_t _Extent>
__cw_fixed_value(_Tp (&)[_Extent]) -> __cw_fixed_value<_Tp[_Extent]>;

template <__cw_fixed_value _Xp, class = typename decltype(__cw_fixed_value(_Xp))::type>
struct __constant_wrapper;

template <class _Tp, class = void>
inline constexpr bool __is_constexpr_param_v = false;
template <class _Tp>
inline constexpr bool __is_constexpr_param_v<_Tp, void_t<__constant_wrapper<__cw_fixed_value(_Tp::value)>>> = true;

template <__cw_fixed_value _Xp>
inline constexpr __constant_wrapper<_Xp> __cw;

struct __cw_operators {
    // unary operators
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval decltype(__constant_wrapper<__cw_fixed_value(+_Tp::value)>{})
    operator+(_Tp) noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval decltype(__constant_wrapper<__cw_fixed_value(-_Tp::value)>{})
    operator-(_Tp) noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval decltype(__constant_wrapper<__cw_fixed_value(~_Tp::value)>{})
    operator~(_Tp) noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval decltype(__constant_wrapper<__cw_fixed_value(!_Tp::value)>{})
    operator!(_Tp) noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Tp> CANN_ASC_STL_DETAIL_ACCL_AND requires {
        typename __constant_wrapper<(&_Tp::value)>;
    })
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator&(_Tp) noexcept
    {
        return __constant_wrapper<(&_Tp::value)>{};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval decltype(__constant_wrapper<__cw_fixed_value(*_Tp::value)>{})
    operator*(_Tp) noexcept
    {
        return {};
    }

    // binary operators
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator+(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value + _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator-(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value - _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator*(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value* _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator/(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value / _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator%(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value % _Rp::value)>{})
    {
        return {};
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator<<(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value << _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator>>(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value >> _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator&(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value& _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator|(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value | _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator^(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value ^ _Rp::value)>{})
    {
        return {};
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>
            CANN_ASC_STL_DETAIL_ACCL_AND(
                !is_constructible_v<bool, decltype(_Lp::value)> || !is_constructible_v<bool, decltype(_Rp::value)>))
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator&&(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value&& _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>
            CANN_ASC_STL_DETAIL_ACCL_AND(
                !is_constructible_v<bool, decltype(_Lp::value)> || !is_constructible_v<bool, decltype(_Rp::value)>))
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator||(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value || _Rp::value)>{})
    {
        return {};
    }

    // comparisons
#if CANN_ASC_STL_DETAIL_ACCL_HAS_SPACESHIP_OPERATOR()
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator<=>(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value <=> _Rp::value)>{})
    {
        return {};
    }
#endif  // CANN_ASC_STL_DETAIL_ACCL_HAS_SPACESHIP_OPERATOR()
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator<(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value < _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator<=(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value <= _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator==(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value == _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator!=(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value != _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator>(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value > _Rp::value)>{})
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator>=(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value >= _Rp::value)>{})
    {
        return {};
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    friend auto operator,(_Lp, _Rp) = delete;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Lp, class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __is_constexpr_param_v<_Lp> CANN_ASC_STL_DETAIL_ACCL_AND __is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API friend consteval auto operator->*(
        _Lp, _Rp) noexcept -> decltype(__constant_wrapper<__cw_fixed_value(_Lp::value->*_Rp::value)>{})
    {
        return {};
    }
};

template <class _Fn, class _Void, class... _Args>
inline constexpr bool __cw_is_constexpr_callable_v = false;
template <class _Fn, class... _Args>
inline constexpr bool __cw_is_constexpr_callable_v<_Fn,
    void_t<__constant_wrapper<__cw_fixed_value(::asc::std::invoke(_Fn::value, _Args::value...))>>, _Args...> = true;

template <class _Vp, class _Void, class... _Args>
inline constexpr bool __cw_is_constexpr_indexable_v = false;
#if CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS()
template <class _Vp, class... _Args>
inline constexpr bool __cw_is_constexpr_indexable_v<_Vp,
    void_t<__constant_wrapper<__cw_fixed_value(_Vp::value[_Args::value...])>>, _Args...> = true;
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() vvv
template <class _Vp, class _Arg>
inline constexpr bool
    __cw_is_constexpr_indexable_v<_Vp, void_t<__constant_wrapper<__cw_fixed_value(_Vp::value[_Arg::value])>>, _Arg> =
        true;
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() ^^^

template <class _Vp, class _Void, class... _Args>
inline constexpr bool __cw_is_indexable_v = false;
#if CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS()
template <class _Vp, class... _Args>
inline constexpr bool
    __cw_is_indexable_v<_Vp, void_t<decltype(_Vp::value[::asc::std::declval<_Args>()...])>, _Args...> = true;
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() vvv
template <class _Vp, class _Arg>
inline constexpr bool __cw_is_indexable_v<_Vp, void_t<decltype(_Vp::value[::asc::std::declval<_Arg>()])>, _Arg> = true;
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() ^^^

template <__cw_fixed_value _Xp, class _Tp>
struct __constant_wrapper : __cw_operators {
    static constexpr const auto& value = _Xp.__data;
    using __cw_fixed_value_type = remove_cvref_t<decltype(_Xp)>;
    using type = __constant_wrapper;
    using value_type = _Tp;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value = _Rp::value)>{})
    operator=(_Rp) const noexcept
    {
        return {};
    }

    CANN_ASC_STL_API constexpr operator const _Tp&() const noexcept
    {
        return _Xp.__data;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __fold_and_v<__is_constexpr_param_v<remove_cvref_t<_Args>>...> CANN_ASC_STL_DETAIL_ACCL_AND
            __cw_is_constexpr_callable_v<__constant_wrapper, void, remove_cvref_t<_Args>...>)
#if CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR()
    CANN_ASC_STL_API static constexpr auto operator()(_Args&&...) noexcept
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR()
        // vvv
    CANN_ASC_STL_API constexpr auto operator()(_Args&&...) const noexcept
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR() ^^^
    {
        return __constant_wrapper<__cw_fixed_value(::asc::std::invoke(value, remove_cvref_t<_Args>::value...))>{};
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!(__fold_and_v<__is_constexpr_param_v<remove_cvref_t<_Args>>...> &&
        __cw_is_constexpr_callable_v<__constant_wrapper, void, remove_cvref_t<_Args>...>))
            CANN_ASC_STL_DETAIL_ACCL_AND is_invocable_v<const _Tp&, _Args&&...>)
#if CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR()
    CANN_ASC_STL_API static constexpr decltype(auto) operator()(_Args&&... __args)
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR()
        // vvv
    CANN_ASC_STL_API constexpr decltype(auto) operator()(_Args&&... __args) const
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_STATIC_CALL_OPERATOR() ^^^
        noexcept(::asc::std::is_nothrow_invocable_v<const _Tp&, _Args...>)
    {
        return ::asc::std::invoke(value, ::asc::std::forward<_Args>(__args)...);
    }

#if CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS()
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __fold_and_v<__is_constexpr_param_v<remove_cvref_t<_Args>>...> CANN_ASC_STL_DETAIL_ACCL_AND
            __cw_is_constexpr_indexable_v<__constant_wrapper, void, remove_cvref_t<_Args>...>)
#if CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR()
    [[nodiscard]]
    CANN_ASC_STL_API consteval static __constant_wrapper<__cw_fixed_value(value[remove_cvref_t<_Args>::value...])>
    operator[](_Args&&...) noexcept
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() vvv
    [[nodiscard]] CANN_ASC_STL_API consteval __constant_wrapper<__cw_fixed_value(
        value[remove_cvref_t<_Args>::value...])>
    operator[](_Args&&...) const noexcept
#endif  // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() ^^^
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!(__fold_and_v<__is_constexpr_param_v<remove_cvref_t<_Args>>...> &&
        __cw_is_constexpr_indexable_v<__constant_wrapper, void, remove_cvref_t<_Args>...>))
            CANN_ASC_STL_DETAIL_ACCL_AND __cw_is_indexable_v<__constant_wrapper, void, _Args...>)
#if CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR()
    CANN_ASC_STL_API static constexpr decltype(auto) operator[](_Args&&... __args)
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() vvv
    CANN_ASC_STL_API constexpr decltype(auto) operator[](_Args&&... __args) const
#endif  // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() ^^^
        noexcept(noexcept(value[::asc::std::forward<_Args>(__args)...]))
    {
        return value[::asc::std::forward<_Args>(__args)...];
    }
#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() ^^^ / vvv
       // !CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() vvv
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Arg)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<remove_cvref_t<_Arg>> CANN_ASC_STL_DETAIL_ACCL_AND
            __cw_is_constexpr_indexable_v<__constant_wrapper, void, remove_cvref_t<_Arg>>)
#if CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR()
    [[nodiscard]]
    CANN_ASC_STL_API consteval static __constant_wrapper<__cw_fixed_value(value[remove_cvref_t<_Arg>::value])>
    operator[](_Arg&&) noexcept
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() vvv
    [[nodiscard]] CANN_ASC_STL_API consteval __constant_wrapper<__cw_fixed_value(value[remove_cvref_t<_Arg>::value])>
    operator[](_Arg&&) const noexcept
#endif  // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() ^^^
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Arg)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!(__is_constexpr_param_v<remove_cvref_t<_Arg>> &&
        __cw_is_constexpr_indexable_v<__constant_wrapper, void, remove_cvref_t<_Arg>>))
            CANN_ASC_STL_DETAIL_ACCL_AND __cw_is_indexable_v<__constant_wrapper, void, _Arg>)
#if CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR()
    CANN_ASC_STL_API static constexpr decltype(auto) operator[](_Arg&& __arg)
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() vvv
    CANN_ASC_STL_API constexpr decltype(auto) operator[](_Arg&& __arg) const
#endif  // ^^^ CANN_ASC_STL_DETAIL_HAS_STATIC_SUBSCRIPT_OPERATOR() ^^^
        noexcept(noexcept(value[::asc::std::forward<_Arg>(__arg)]))
    {
        return value[::asc::std::forward<_Arg>(__arg)];  // NOLINT(build/include_what_you_use)
    }
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_MULTIARG_OPERATOR_BRACKETS() ^^^

    // pseudo-mutators
    template <class _This = __constant_wrapper>
    [[nodiscard]] CANN_ASC_STL_API consteval __constant_wrapper<__cw_fixed_value(++_This::value)> operator++()
        const noexcept
    {
        return {};
    }
    template <class _This = __constant_wrapper>
    [[nodiscard]] CANN_ASC_STL_API consteval __constant_wrapper<__cw_fixed_value(_This::value++)> operator++(
        int) const noexcept
    {
        return {};
    }
    template <class _This = __constant_wrapper>
    [[nodiscard]] CANN_ASC_STL_API consteval __constant_wrapper<__cw_fixed_value(--_This::value)> operator--()
        const noexcept
    {
        return {};
    }
    template <class _This = __constant_wrapper>
    [[nodiscard]] CANN_ASC_STL_API consteval __constant_wrapper<__cw_fixed_value(_This::value--)> operator--(
        int) const noexcept
    {
        return {};
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value += _Rp::value)>{})
    operator+=(_Rp) const noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value -= _Rp::value)>{})
    operator-=(_Rp) const noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value *= _Rp::value)>{})
    operator*=(_Rp) const noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value /= _Rp::value)>{})
    operator/=(_Rp) const noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value %= _Rp::value)>{})
    operator%=(_Rp) const noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value &= _Rp::value)>{})
    operator&=(_Rp) const noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value |= _Rp::value)>{})
    operator|=(_Rp) const noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value ^= _Rp::value)>{})
    operator^=(_Rp) const noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value <<= _Rp::value)>{})
    operator<<=(_Rp) const noexcept
    {
        return {};
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__is_constexpr_param_v<_Rp>)
    [[nodiscard]] CANN_ASC_STL_API consteval decltype(__constant_wrapper<__cw_fixed_value(value >>= _Rp::value)>{})
    operator>>=(_Rp) const noexcept
    {
        return {};
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_DETAIL_STD_VER >= 2020

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_CONSTANT_WRAPPER_H
