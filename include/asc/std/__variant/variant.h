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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/dependent_type.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__variant/sfinae_helpers.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/__variant/variant_base.h>
#include <asc/std/__variant/variant_constraints.h>
#include <asc/std/__variant/variant_visit.h>
#include <asc/std/cstddef>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class... _Types>
class variant : private __variant_base<__fold_and_v<is_copy_constructible_v<_Types>...>,
                    __fold_and_v<is_move_constructible_v<_Types>...>,
                    __fold_and_v<(is_copy_constructible_v<_Types> && is_copy_assignable_v<_Types>)...>,
                    __fold_and_v<(is_move_constructible_v<_Types> && is_move_assignable_v<_Types>)...>> {
    static_assert(0 < sizeof...(_Types), "variant must consist of at least one alternative.");

    static_assert((!is_array_v<_Types> && ...), "variant can not have an array type as an alternative.");

    static_assert((!is_reference_v<_Types> && ...), "variant can not have a reference type as an alternative.");

    static_assert((!is_void_v<_Types> && ...), "variant can not have a void type as an alternative.");

    using __first_type = variant_alternative_t<0, variant>;
    using __constraints = __variant_detail::__variant_constraints<_Types...>;

public:
    // Needs to be dependent to guard against incomplete types
    template <bool _Dummy = true,
        class = enable_if_t<__dependent_type<is_default_constructible<__first_type>, _Dummy>::value>>
    CANN_ASC_STL_API constexpr variant() noexcept(is_nothrow_default_constructible_v<__first_type>)
        : __impl_(in_place_index<0>)
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr variant(const variant&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr variant(variant&&) = default;

    template <class _Arg>
    using __match_construct = conditional_t<!is_same_v<remove_cvref_t<_Arg>, variant> &&
            !__is_asc_std_inplace_type_v<remove_cvref_t<_Arg>>  //
            && !__is_asc_std_inplace_index_v<remove_cvref_t<_Arg>>,
        typename __constraints::template __match_construct<_Arg>, __variant_detail::__invalid_variant_constraints>;

    // CTAD fails if we do not SFINAE the empty variant away first
    template <class _Arg, class = enable_if_t<sizeof...(_Types) != 0>, class _Constraints = __match_construct<_Arg>,
        class = enable_if_t<_Constraints::__constructible>>
    CANN_ASC_STL_API constexpr variant(_Arg&& __arg) noexcept(_Constraints::__nothrow_constructible)
        : __impl_(in_place_index<_Constraints::_Ip>, ::asc::std::forward<_Arg>(__arg))
    {}

    template <size_t _Ip, class... _Args>
    using __variadic_construct =
        conditional_t<(_Ip < sizeof...(_Types)), typename __constraints::template __variadic_construct<_Ip, _Args...>,
            __variant_detail::__invalid_variant_constraints>;

    template <size_t _Ip, class... _Args, class _Constraints = __variadic_construct<_Ip, _Args...>,
        class = enable_if_t<_Constraints::__constructible>>
    CANN_ASC_STL_API explicit constexpr variant(in_place_index_t<_Ip>, _Args&&... __args) noexcept(
        _Constraints::__nothrow_constructible)
        : __impl_(in_place_index<_Ip>, ::asc::std::forward<_Args>(__args)...)
    {}

    template <size_t _Ip, class _Up, class... _Args>
    using __variadic_ilist_construct = conditional_t<(_Ip < sizeof...(_Types)),
        typename __constraints::template __variadic_ilist_construct<_Ip, _Up, _Args...>,
        __variant_detail::__invalid_variant_constraints>;

    template <size_t _Ip, class _Up, class... _Args,
        class _Constraints = __variadic_ilist_construct<_Ip, _Up, _Args...>,
        class = enable_if_t<_Constraints::__constructible>>
    CANN_ASC_STL_API explicit constexpr variant(in_place_index_t<_Ip>, initializer_list<_Up> __il,
        _Args&&... __args) noexcept(_Constraints::__nothrow_constructible)
        : __impl_(in_place_index<_Ip>, __il, ::asc::std::forward<_Args>(__args)...)
    {}

    template <class _Tp, class... _Args,
        size_t _Ip = __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
        class _Constraints = __variadic_construct<_Ip, _Args...>, class = enable_if_t<_Constraints::__constructible>>
    CANN_ASC_STL_API explicit constexpr variant(in_place_type_t<_Tp>, _Args&&... __args) noexcept(
        _Constraints::__nothrow_constructible)
        : __impl_(in_place_index<_Ip>, ::asc::std::forward<_Args>(__args)...)
    {}

    template <class _Tp, class _Up, class... _Args,
        size_t _Ip = __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
        class _Constraints = __variadic_ilist_construct<_Ip, _Up, _Args...>,
        class = enable_if_t<_Constraints::__constructible>>
    CANN_ASC_STL_API explicit constexpr variant(in_place_type_t<_Tp>, initializer_list<_Up> __il,
        _Args&&... __args) noexcept(_Constraints::__nothrow_constructible)
        : __impl_(in_place_index<_Ip>, __il, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI ~variant() = default;

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr variant& operator=(const variant&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr variant& operator=(variant&&) = default;

    template <class _Arg>
    using __match_assign = conditional_t<!is_same_v<remove_cvref_t<_Arg>, variant>,
        typename __constraints::template __match_assign<_Arg>, __variant_detail::__invalid_variant_constraints>;

    template <class _Arg, class _Constraints = __match_assign<_Arg>, class = enable_if_t<_Constraints::__assignable>>
    CANN_ASC_STL_API variant& operator=(_Arg&& __arg) noexcept(_Constraints::__nothrow_assignable)
    {
        __impl_.template __assign<_Constraints::_Ip>(::asc::std::forward<_Arg>(__arg));
        return *this;
    }

    template <size_t _Ip, class... _Args, class _Constraints = __variadic_construct<_Ip, _Args...>,
        class = enable_if_t<_Constraints::__constructible>>
    CANN_ASC_STL_API typename _Constraints::_Tp& emplace(_Args&&... __args)
    {
        return __impl_.template __emplace<_Ip>(::asc::std::forward<_Args>(__args)...);
    }

    template <size_t _Ip, class _Up, class... _Args,
        class _Constraints = __variadic_ilist_construct<_Ip, _Up, _Args...>,
        class = enable_if_t<_Constraints::__constructible>>
    CANN_ASC_STL_API typename _Constraints::_Tp& emplace(initializer_list<_Up> __il, _Args&&... __args)
    {
        return __impl_.template __emplace<_Ip>(__il, ::asc::std::forward<_Args>(__args)...);
    }

    template <class _Tp, class... _Args,
        size_t _Ip = __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
        enable_if_t<is_constructible_v<_Tp, _Args...>, int> = 0>
    CANN_ASC_STL_API _Tp& emplace(_Args&&... __args)
    {
        return __impl_.template __emplace<_Ip>(::asc::std::forward<_Args>(__args)...);
    }

    template <class _Tp, class _Up, class... _Args,
        size_t _Ip = __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value,
        enable_if_t<is_constructible_v<_Tp, initializer_list<_Up>&, _Args...>, int> = 0>
    CANN_ASC_STL_API _Tp& emplace(initializer_list<_Up> __il, _Args&&... __args)
    {
        return __impl_.template __emplace<_Ip>(__il, ::asc::std::forward<_Args>(__args)...);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr bool valueless_by_exception() const noexcept
    {
        return __impl_.valueless_by_exception();
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr size_t index() const noexcept
    {
        return __impl_.index();
    }

    // Needs to be dependent to guard against incomplete types
    template <bool _Dummy>
    using __swap_constraint =
        __dependent_type<typename __variant_detail::__variant_constraints<_Types...>::template __swappable<_Dummy>,
            _Dummy>;

    template <bool _Dummy = true, class _Constraint = __swap_constraint<_Dummy>,
        class = enable_if_t<_Constraint::__is_swappable_v>>
    CANN_ASC_STL_API void swap(variant& __that) noexcept(  // NOLINT(build/include_what_you_use)
        _Constraint::__is_nothrow_swappable_v)             // NOLINT(build/include_what_you_use)
    {
        __impl_.__swap(__that.__impl_);
    }

    CANN_ASC_STL_API static constexpr size_t __size() noexcept
    {
        return sizeof...(_Types);
    }

private:
    __variant_detail::__impl<_Types...> __impl_;

    friend struct __variant_detail::__access::__variant;
    friend struct __variant_detail::__visitation::__variant;
};

template <class... _Types>
CANN_ASC_STL_API auto swap(
    variant<_Types...>& __lhs, variant<_Types...>& __rhs) noexcept(  // NOLINT(build/include_what_you_use)
    noexcept(__lhs.swap(__rhs))) -> decltype(__lhs.swap(__rhs))
{
    return __lhs.swap(__rhs);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_H
