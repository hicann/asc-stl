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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_AGGREGATE_MEMBERS_ALL_OF_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_AGGREGATE_MEMBERS_ALL_OF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_aggregate.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/integer_sequence.h>

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_CLANG("-Wmissing-field-initializers")
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_CLANG("-Wmissing-braces")

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// provide a generic way to initialize an aggregate member
struct __any_aggregate_member {
    template <typename _Tp>
    CANN_ASC_STL_API constexpr operator _Tp&&() const;
};

// Computes the number of aggregate members
template <typename _Tp>
struct __aggregate_arity_impl {
    // N == 0: skip _Up{} to avoid inconsistencies across compilers (deleted default constructor)
    template <typename _Self = __aggregate_arity_impl>
    CANN_ASC_STL_API auto operator()() -> decltype(_Self{}(__any_aggregate_member{}));

    // N >= 1: SFINAE on _Up{_A0{}, _Args{}...}
    template <typename _A0, typename... _Args, typename _Up = _Tp, typename = decltype(_Up{_A0{}, (_Args{})...}),
        typename _Self = __aggregate_arity_impl>
    CANN_ASC_STL_API auto operator()(
        _A0, _Args... __args) -> decltype(_Self{}(_A0{}, __args..., __any_aggregate_member{}));

    template <typename... _Args>
    CANN_ASC_STL_API auto operator()(
        _Args...) const -> char (*)[sizeof...(_Args) + 1];  // return the number of members + 1
};

// Returns the number of aggregate members. Only meaningful when is_aggregate_v<_Tp> is true.
template <typename _Tp>
inline constexpr int __aggregate_arity_v = int{sizeof(*__aggregate_arity_impl<_Tp>{}())} - 2;

// Apply a Predicate to every aggregate member

// provide a generic way to initialize an aggregate member but only if the Predicate is true
template <template <typename> class _Predicate>
struct __aggregate_member_if {
    template <typename _Tp, typename = enable_if_t<_Predicate<remove_cvref_t<_Tp>>::value>>
    CANN_ASC_STL_API constexpr operator _Tp&&() const;
};

inline constexpr int __aggregate_max_arity = 8;

// Apply the Predicate to every member
template <int _Arity>
struct __aggregate_all_of_fn {
    template <template <typename> class _Predicate, typename _Tp, size_t... _Is>
    CANN_ASC_STL_API static auto __test(
        index_sequence<_Is...>, int) -> decltype(_Tp{((void)_Is, __aggregate_member_if<_Predicate>{})...}, true_type{});

    // BiSheng CCE does not support a C-style variadic function. Keep the
    // overload-priority SFINAE fallback with a regular parameter instead.
    template <template <typename> class, typename, size_t... _Is>
    CANN_ASC_STL_API static auto __test(index_sequence<_Is...>, long) -> false_type;

    template <template <typename> class _Predicate, typename _Tp>
    CANN_ASC_STL_API static auto __call(int) -> decltype(__test<_Predicate, _Tp>(make_index_sequence<_Arity>{}, 0));
};

// (aggregate-only trait) Dispatch based on the aggregate arity for non-empty aggregates. Returns:
// - false: _Arity out of [1, __aggregate_max_arity]
// - true:  if the unary predicate is true for all members
template <template <typename> class _Predicate, typename _Tp, int _Arity = __aggregate_arity_v<_Tp>,
    bool = (_Arity > 0) && (_Arity <= __aggregate_max_arity)>
inline constexpr bool __aggregate_all_of_dispatch_v = false;

template <template <typename> class _Predicate, typename _Tp, int _Arity>
inline constexpr bool __aggregate_all_of_dispatch_v<_Predicate, _Tp, _Arity, true> =
    decltype(__aggregate_all_of_fn<_Arity>::template __call<_Predicate, _Tp>(0))::value;

// if _Tp is not an aggregate, return false.
// Empty aggregates are true for any predicate.
// The specialization is needed to skip computing the arity and save compile time.
template <template <typename> class _Predicate, typename _Tp, bool = is_aggregate_v<_Tp>, bool = is_empty_v<_Tp>>
inline constexpr bool __aggregate_all_of_v = false;

// (non-empty) aggregate
template <template <typename> class _Predicate, typename _Tp>
inline constexpr bool __aggregate_all_of_v<_Predicate, _Tp, true, false> =
    __aggregate_all_of_dispatch_v<_Predicate, _Tp>;

// Empty aggregate (true for any predicate)
template <template <typename> class _Predicate, typename _Tp>
inline constexpr bool __aggregate_all_of_v<_Predicate, _Tp, true, true> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_DIAG_POP

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_AGGREGATE_MEMBERS_ALL_OF_H
