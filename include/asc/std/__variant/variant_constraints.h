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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_CONSTRAINTS_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_CONSTRAINTS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/variant.h>
#include <asc/std/__tuple_dir/get.h>
#include <asc/std/__tuple_dir/sfinae_helpers.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__variant/variant_match.h>
#include <asc/std/cstddef>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __find_detail {
// The sentinel constant is provided centrally by __find_detail in __tuple_dir/get.h (included by this header).

template <class _Tp, class... _Types>
CANN_ASC_STL_API constexpr size_t __find_index()
{
    constexpr bool __matches[] = {is_same_v<_Tp, _Types>...};
    size_t __result = __not_found;
    for (size_t __i = 0; __i < sizeof...(_Types); ++__i) {
        if (__matches[__i]) {
            if (__result != __not_found) {
                __result = __ambiguous;
                break;
            }
            __result = __i;
        }
    }
    return __result;
}

template <class _Tp, class... _Types>
using __find_unambiguous_index_sfinae = enable_if_t<::asc::std::__find_detail::__find_index<_Tp, _Types...>() !=
        __not_found&& ::asc::std::__find_detail::__find_index<_Tp, _Types...>() != __ambiguous,
    integral_constant<size_t, ::asc::std::__find_detail::__find_index<_Tp, _Types...>()>>;
}  // namespace __find_detail

namespace __variant_detail {
struct __invalid_variant_constraints {
    static constexpr bool __constructible = false;
    static constexpr bool __nothrow_constructible = false;
    static constexpr bool __assignable = false;
    static constexpr bool __nothrow_assignable = false;
};

template <class... _Types>
struct __variant_constraints {
    template <class _Arg, class _Tp = __best_match_t<_Arg, _Types...>>
    struct __match_construct {
        static constexpr size_t _Ip = __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value;

        static constexpr bool __constructible = is_constructible_v<_Tp, _Arg>;
        static constexpr bool __nothrow_constructible = is_nothrow_constructible_v<_Tp, _Arg>;
    };

    template <size_t _Ip, class... _Args>
    struct __variadic_construct {
        using _Tp = variant_alternative_t<_Ip, variant<_Types...>>;

        static constexpr bool __constructible = is_constructible_v<_Tp, _Args...>;
        static constexpr bool __nothrow_constructible = is_nothrow_constructible_v<_Tp, _Args...>;
    };

    template <size_t _Ip, class _Up, class... _Args>
    struct __variadic_ilist_construct {
        using _Tp = variant_alternative_t<_Ip, variant<_Types...>>;

        static constexpr bool __constructible = is_constructible_v<_Tp, initializer_list<_Up>&, _Args...>;
        static constexpr bool __nothrow_constructible =
            is_nothrow_constructible_v<_Tp, initializer_list<_Up>&, _Args...>;
    };

    template <class _Arg, class _Tp = __best_match_t<_Arg, _Types...>>
    struct __match_assign {
        static constexpr size_t _Ip = __find_detail::__find_unambiguous_index_sfinae<_Tp, _Types...>::value;

        static constexpr bool __assignable = is_assignable_v<_Tp&, _Arg> && is_constructible_v<_Tp, _Arg>;
        static constexpr bool __nothrow_assignable =
            is_nothrow_assignable_v<_Tp&, _Arg> && is_nothrow_constructible_v<_Tp, _Arg>;
    };

    template <bool>
    struct __swappable {
        static constexpr bool __is_swappable_v = ((is_move_constructible_v<_Types> && is_swappable_v<_Types>) && ...);

        static constexpr bool __is_nothrow_swappable_v =
            ((is_nothrow_move_constructible_v<_Types> && is_nothrow_swappable_v<_Types>) && ...);
    };
};
}  // namespace __variant_detail

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_CONSTRAINTS_H
