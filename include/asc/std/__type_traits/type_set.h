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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_TYPE_SET_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_TYPE_SET_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/conjunction.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class...>
struct __type_list;

template <class Set, class... Ty>
struct __type_set_contains : __fold_and<is_base_of_v<type_identity<Ty>, Set>...> {};

template <class Set, class... Ty>
inline constexpr bool __type_set_contains_v = __fold_and_v<is_base_of_v<type_identity<Ty>, Set>...>;

namespace __set {
template <class... Ts>
struct __tupl;

template <>
struct __tupl<> {
    template <class Ty>
    using __maybe_insert = __tupl<Ty>;

    static CANN_ASC_STL_API constexpr size_t __size() noexcept
    {
        return 0;
    }
};

template <class Ty, class... Ts>
struct __tupl<Ty, Ts...> : type_identity<Ty>, __tupl<Ts...> {
    template <class Uy>
    using __maybe_insert = conditional_t<__type_set_contains_v<__tupl, Uy>, __tupl, __tupl<Uy, Ty, Ts...>>;

    static CANN_ASC_STL_API constexpr size_t __size() noexcept
    {
        return sizeof...(Ts) + 1;
    }
};

template <bool Empty>
struct __bulk_insert {
    template <class Set, class...>
    using __call = Set;
};

template <>
struct __bulk_insert<false> {
    template <class Set, class Ty, class... Us>
    using __call =
        typename __bulk_insert<sizeof...(Us) == 0>::template __call<typename Set::template __maybe_insert<Ty>, Us...>;
};
}  // namespace __set

// When comparing sets for equality, use conjunction<> to short-circuit the set
// comparison if the sizes are different.
template <class ExpectedSet, class... Ts>
using __type_set_eq =
    conjunction<bool_constant<sizeof...(Ts) == ExpectedSet::__size()>, __type_set_contains<ExpectedSet, Ts...>>;

template <class ExpectedSet, class... Ts>
inline constexpr bool __type_set_eq_v = __type_set_eq<ExpectedSet, Ts...>::value;

template <class... Ts>
using __type_set = __set::__tupl<Ts...>;

template <class Set, class... Ts>
using __type_set_insert = typename __set::__bulk_insert<sizeof...(Ts) == 0>::template __call<Set, Ts...>;

template <class... Ts>
using __make_type_set = __type_set_insert<__type_set<>, Ts...>;

template <class Ty, class... Ts>
struct __is_included_in : __fold_or<is_same_v<Ty, Ts>...> {};

template <class Ty, class... Ts>
inline constexpr bool __is_included_in_v = (is_same_v<Ty, Ts> || ...);

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_TYPE_SET_H
