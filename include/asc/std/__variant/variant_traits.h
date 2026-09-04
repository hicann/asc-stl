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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_TRAITS_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_TRAITS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/add_const.h>
#include <asc/std/__type_traits/add_cv.h>
#include <asc/std/__type_traits/add_volatile.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_destructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
struct variant_size<const _Tp> : variant_size<_Tp> {};
template <class _Tp>
struct variant_size<volatile _Tp> : variant_size<_Tp> {};
template <class _Tp>
struct variant_size<const volatile _Tp> : variant_size<_Tp> {};
template <class... _Types>
struct variant_size<variant<_Types...>> : integral_constant<size_t, sizeof...(_Types)> {};

template <size_t _Ip, class _Tp>
struct variant_alternative<_Ip, const _Tp> : add_const<variant_alternative_t<_Ip, _Tp>> {};
template <size_t _Ip, class _Tp>
struct variant_alternative<_Ip, volatile _Tp> : add_volatile<variant_alternative_t<_Ip, _Tp>> {};
template <size_t _Ip, class _Tp>
struct variant_alternative<_Ip, const volatile _Tp> : add_cv<variant_alternative_t<_Ip, _Tp>> {};

template <size_t _Ip, class... _Types>
struct variant_alternative<_Ip, variant<_Types...>> {
    static_assert(_Ip < sizeof...(_Types), "Index out of bounds in asc::std::variant_alternative<>");
    using type = __type_index_c<_Ip, _Types...>;
};

[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEVAL int __choose_index_type(unsigned int __num_elem) noexcept
{
    constexpr unsigned char __small = static_cast<unsigned char>(-1);
    constexpr unsigned short __medium = static_cast<unsigned short>(-1);
    if (__num_elem < static_cast<unsigned int>(__small))
        return 0;
    if (__num_elem < static_cast<unsigned int>(__medium))
        return 1;
    return 2;
}

template <size_t _NumAlts>
using __variant_index_t = conditional_t<::asc::std::__choose_index_type(_NumAlts) == 0, unsigned char,
    conditional_t<::asc::std::__choose_index_type(_NumAlts) == 1, unsigned short, unsigned int>>;

namespace __variant_detail {
struct __valueless_t {};
enum class _Trait { _TriviallyAvailable, _Available, _Unavailable };

template <typename... _Types>
struct __traits {
    [[nodiscard]] CANN_ASC_STL_API static CANN_ASC_STL_DETAIL_CONSTEVAL _Trait __common_trait(
        initializer_list<_Trait> __traits) noexcept
    {
        _Trait __result = _Trait::_TriviallyAvailable;
        for (_Trait __t : __traits)
            if (static_cast<int>(__t) > static_cast<int>(__result))
                __result = __t;
        return __result;
    }

    template <class _Type>
    static constexpr _Trait __copy_constructible_trait_ =
        is_trivially_copy_constructible_v<_Type> ? _Trait::_TriviallyAvailable :
        is_copy_constructible_v<_Type>           ? _Trait::_Available :
                                                   _Trait::_Unavailable;
    static constexpr _Trait __copy_constructible_trait = __common_trait({__copy_constructible_trait_<_Types>...});

    template <class _Type>
    static constexpr _Trait __move_constructible_trait_ =
        is_trivially_move_constructible_v<_Type> ? _Trait::_TriviallyAvailable :
        is_move_constructible_v<_Type>           ? _Trait::_Available :
                                                   _Trait::_Unavailable;
    static constexpr _Trait __move_constructible_trait = __common_trait({__move_constructible_trait_<_Types>...});

    template <class _Type>
    static constexpr _Trait __copy_assignable_trait_ =
        is_trivially_copy_assignable_v<_Type> ? _Trait::_TriviallyAvailable :
        is_copy_assignable_v<_Type>           ? _Trait::_Available :
                                                _Trait::_Unavailable;
    static constexpr _Trait __copy_assignable_trait =
        __common_trait({__copy_constructible_trait, __copy_assignable_trait_<_Types>...});

    template <class _Type>
    static constexpr _Trait __move_assignable_trait_ =
        is_trivially_move_assignable_v<_Type> ? _Trait::_TriviallyAvailable :
        is_move_assignable_v<_Type>           ? _Trait::_Available :
                                                _Trait::_Unavailable;
    static constexpr _Trait __move_assignable_trait =
        __common_trait({__move_constructible_trait, __move_assignable_trait_<_Types>...});

    template <class _Type>
    static constexpr _Trait __destructible_trait_ = is_trivially_destructible_v<_Type> ? _Trait::_TriviallyAvailable :
        is_destructible_v<_Type>                                                       ? _Trait::_Available :
                                                                                         _Trait::_Unavailable;
    static constexpr _Trait __destructible_trait = __common_trait({__destructible_trait_<_Types>...});
};
}  // namespace __variant_detail

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif
