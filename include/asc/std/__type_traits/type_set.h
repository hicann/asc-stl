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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_TYPE_SET_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_TYPE_SET_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/conjunction.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class...>
struct __type_list;

template <class _Set, class... _Ty>
struct __type_set_contains : __fold_and<is_base_of_v<type_identity<_Ty>, _Set>...> {};

template <class _Set, class... _Ty>
inline constexpr bool __type_set_contains_v = __fold_and_v<is_base_of_v<type_identity<_Ty>, _Set>...>;

namespace __set {
template <class... _Ts>
struct __tupl;

template <>
struct __tupl<> {
    template <class _Ty>
    using __maybe_insert = __tupl<_Ty>;

    CANN_ASC_STL_API static constexpr size_t __size() noexcept
    {
        return 0;
    }
};

template <class _Ty, class... _Ts>
struct __tupl<_Ty, _Ts...> : type_identity<_Ty>, __tupl<_Ts...> {
    template <class _Uy>
    using __maybe_insert = _If<__type_set_contains_v<__tupl, _Uy>, __tupl, __tupl<_Uy, _Ty, _Ts...>>;

    CANN_ASC_STL_API static constexpr size_t __size() noexcept
    {
        return sizeof...(_Ts) + 1;
    }
};

template <bool _Empty>
struct __bulk_insert {
    template <class _Set, class...>
    using __call = _Set;
};

template <>
struct __bulk_insert<false> {
#if CANN_ASC_STL_DETAIL_COMPILER(MSVC, <, 19, 20)
    template <class _Set, class _Ty, class... _Us>
    CANN_ASC_STL_API static auto __insert_fn(__type_list<_Ty, _Us...>*) ->
        typename __bulk_insert<sizeof...(_Us) == 0>::template __call<typename _Set::template __maybe_insert<_Ty>,
            _Us...>;

    template <class _Set, class... _Us>
    using __call = decltype(__insert_fn<_Set>(static_cast<__type_list<_Us...>*>(nullptr)));
#else
    template <class _Set, class _Ty, class... _Us>
    using __call = typename __bulk_insert<sizeof...(_Us) ==
        0>::template __call<typename _Set::template __maybe_insert<_Ty>, _Us...>;
#endif
};
}  // namespace __set

// When comparing sets for equality, use conjunction<> to short-circuit the set
// comparison if the sizes are different.
template <class _ExpectedSet, class... _Ts>
using __type_set_eq =
    conjunction<bool_constant<sizeof...(_Ts) == _ExpectedSet::__size()>, __type_set_contains<_ExpectedSet, _Ts...>>;

template <class _ExpectedSet, class... _Ts>
inline constexpr bool __type_set_eq_v = __type_set_eq<_ExpectedSet, _Ts...>::value;

template <class... _Ts>
using __type_set = __set::__tupl<_Ts...>;

template <class _Set, class... _Ts>
using __type_set_insert = typename __set::__bulk_insert<sizeof...(_Ts) == 0>::template __call<_Set, _Ts...>;

template <class... _Ts>
using __make_type_set = __type_set_insert<__type_set<>, _Ts...>;

template <class _Ty, class... _Ts>
struct __is_included_in : __fold_or<is_same_v<_Ty, _Ts>...> {};

template <class _Ty, class... _Ts>
inline constexpr bool __is_included_in_v = (is_same_v<_Ty, _Ts> || ...);

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_TYPE_SET_H
