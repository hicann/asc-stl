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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_CONCEPTS_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_CONCEPTS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/arithmetic.h>
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/common_reference_with.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__concepts/predicate.h>
#include <asc/std/__concepts/regular.h>
#include <asc/std/__concepts/relation.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__concepts/semiregular.h>
#include <asc/std/__concepts/totally_ordered.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/conjunction.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

// [iterator.concept.readable]
template <class _In>
concept __indirectly_readable_impl =
    requires(const _In __i) {
        typename iter_value_t<_In>;
        typename iter_reference_t<_In>;
        typename iter_rvalue_reference_t<_In>;
        { *__i } -> same_as<iter_reference_t<_In>>;
        { ::asc::std::ranges::__iter_move_cpo{}(__i) } -> same_as<iter_rvalue_reference_t<_In>>;
    } && common_reference_with<iter_reference_t<_In>&&, iter_value_t<_In>&> &&
    common_reference_with<iter_reference_t<_In>&&, iter_rvalue_reference_t<_In>&&> &&
    common_reference_with<iter_rvalue_reference_t<_In>&&, const iter_value_t<_In>&>;

template <class _In>
concept indirectly_readable = __indirectly_readable_impl<remove_cvref_t<_In>>;

template <indirectly_readable _Tp>
using iter_common_reference_t = common_reference_t<iter_reference_t<_Tp>, iter_value_t<_Tp>&>;

// [iterator.concept.writable]
template <class _Out, class _Tp>
concept indirectly_writable = requires(_Out&& __o, _Tp&& __t) {
    *__o = static_cast<_Tp&&>(__t);                       // not required to be equality-preserving
    *static_cast<_Out&&>(__o) = static_cast<_Tp&&>(__t);  // not required to be equality-preserving
    const_cast<const iter_reference_t<_Out>&&>(*__o) = static_cast<_Tp&&>(__t);  // not required to be
                                                                                 // equality-preserving
    const_cast<const iter_reference_t<_Out>&&>(*static_cast<_Out&&>(__o)) =
        static_cast<_Tp&&>(__t);  // not required to be equality-preserving
};

// [iterator.concept.winc]
template <class _Tp>
concept __integer_like = integral<_Tp> && !same_as<_Tp, bool>;

template <class _Tp>
concept __signed_integer_like = signed_integral<_Tp>;

template <class _Ip>
concept weakly_incrementable =
    // TODO: remove this once the clang bug is fixed (bugs.llvm.org/PR48173).
    !same_as<_Ip, bool> &&  // Currently, clang does not handle bool correctly.
    movable<_Ip> && requires(_Ip __i) {
        typename iter_difference_t<_Ip>;
        requires __signed_integer_like<iter_difference_t<_Ip>>;
        { ++__i } -> same_as<_Ip&>;  // not required to be equality-preserving
        __i++;                       // not required to be equality-preserving
    };

// [iterator.concept.inc]
template <class _Ip>
concept incrementable = regular<_Ip> && weakly_incrementable<_Ip> && requires(_Ip __i) {
    { __i++ } -> same_as<_Ip>;
};

// [iterator.concept.iterator]
template <class _Ip>
concept input_or_output_iterator = requires(_Ip __i) {
    { *__i } -> __can_reference;
} && weakly_incrementable<_Ip>;

// [iterator.concept.sentinel]
template <class _Sp, class _Ip>
concept sentinel_for = semiregular<_Sp> && input_or_output_iterator<_Ip> && __weakly_equality_comparable_with<_Sp, _Ip>;

template <class, class>
inline constexpr bool disable_sized_sentinel_for = false;

template <class _Sp, class _Ip>
concept sized_sentinel_for = sentinel_for<_Sp, _Ip> &&
    !disable_sized_sentinel_for<remove_cv_t<_Sp>, remove_cv_t<_Ip>> && requires(const _Ip& __i, const _Sp& __s) {
        { __s - __i } -> same_as<iter_difference_t<_Ip>>;
        { __i - __s } -> same_as<iter_difference_t<_Ip>>;
    };

// [iterator.concept.input]
template <class _Ip>
concept input_iterator = input_or_output_iterator<_Ip> && indirectly_readable<_Ip> &&
    requires { typename _ITER_CONCEPT<_Ip>; } && derived_from<_ITER_CONCEPT<_Ip>, input_iterator_tag>;

// [iterator.concept.output]
template <class _Ip, class _Tp>
concept output_iterator =
    input_or_output_iterator<_Ip> && indirectly_writable<_Ip, _Tp> && requires(_Ip __it, _Tp&& __t) {
        *__it++ = static_cast<_Tp&&>(__t);  // not required to be equality-preserving
    };

// [iterator.concept.forward]
template <class _Ip>
concept forward_iterator = input_iterator<_Ip> && derived_from<_ITER_CONCEPT<_Ip>, forward_iterator_tag> &&
    incrementable<_Ip> && sentinel_for<_Ip, _Ip>;

// [iterator.concept.bidir]
template <class _Iter>
concept __iter_can_decrement = requires(_Iter __iter) {
    { --__iter } -> same_as<_Iter&>;
    { __iter-- } -> same_as<_Iter>;
};

template <class _Iter>
concept bidirectional_iterator = forward_iterator<_Iter> &&
    derived_from<_ITER_CONCEPT<_Iter>, bidirectional_iterator_tag> && __iter_can_decrement<_Iter>;

template <class _Iter>
concept __iter_can_plus_equal = requires(_Iter __iter, const iter_difference_t<_Iter> __n) {
    { __iter += __n } -> same_as<_Iter&>;
};

template <class _Iter>
concept __iter_can_plus = requires(const _Iter __iter, const iter_difference_t<_Iter> __n) {
    { __iter + __n } -> same_as<_Iter>;
    { __n + __iter } -> same_as<_Iter>;
};

template <class _Iter>
concept __iter_can_minus_equal = requires(_Iter __iter, const iter_difference_t<_Iter> __n) {
    { __iter -= __n } -> same_as<_Iter&>;
};

template <class _Iter>
concept __iter_can_minus = requires(const _Iter __iter, const iter_difference_t<_Iter> __n) {
    { __iter - __n } -> same_as<_Iter>;
};

template <class _Iter>
concept __iter_can_subscript = requires(const _Iter __iter, const iter_difference_t<_Iter> __n) {
    { __iter[__n] } -> same_as<iter_reference_t<_Iter>>;
};

template <class _Iter>
concept __random_access_operations = __iter_can_plus_equal<_Iter> && __iter_can_plus<_Iter> &&
    __iter_can_minus_equal<_Iter> && __iter_can_minus<_Iter> && __iter_can_subscript<_Iter>;

template <class _Iter>
concept random_access_iterator =
    bidirectional_iterator<_Iter> && derived_from<_ITER_CONCEPT<_Iter>, random_access_iterator_tag> &&
    totally_ordered<_Iter> && sized_sentinel_for<_Iter, _Iter> && __random_access_operations<_Iter>;

template <class _Ip>
concept contiguous_iterator = random_access_iterator<_Ip> &&
    derived_from<_ITER_CONCEPT<_Ip>, contiguous_iterator_tag> && is_lvalue_reference_v<iter_reference_t<_Ip>> &&
    same_as<iter_value_t<_Ip>, remove_cvref_t<iter_reference_t<_Ip>>> && requires(const _Ip& __i) {
        { ::asc::std::to_address(__i) } -> same_as<add_pointer_t<iter_reference_t<_Ip>>>;
    };

template <class _Ip>
concept __has_arrow = input_iterator<_Ip> && (is_pointer_v<_Ip> || requires(_Ip __i) { __i.operator->(); });

template <class _Ip>
concept __has_const_arrow = (is_pointer_v<_Ip> || requires(const _Ip __i) { __i.operator->(); });

// [indirectcallable.indirectinvocable]
template <class _Fp, class _It>
concept indirectly_unary_invocable =
    indirectly_readable<_It> && copy_constructible<_Fp> && invocable<_Fp&, iter_value_t<_It>&> &&
    invocable<_Fp&, iter_reference_t<_It>> && invocable<_Fp&, iter_common_reference_t<_It>> &&
    common_reference_with<invoke_result_t<_Fp&, iter_value_t<_It>&>, invoke_result_t<_Fp&, iter_reference_t<_It>>>;

template <class _Fp, class _It>
concept indirectly_regular_unary_invocable =
    indirectly_readable<_It> && copy_constructible<_Fp> && regular_invocable<_Fp&, iter_value_t<_It>&> &&
    regular_invocable<_Fp&, iter_reference_t<_It>> && regular_invocable<_Fp&, iter_common_reference_t<_It>> &&
    common_reference_with<invoke_result_t<_Fp&, iter_value_t<_It>&>, invoke_result_t<_Fp&, iter_reference_t<_It>>>;

template <class _Fp, class _It>
concept indirect_unary_predicate =
    indirectly_readable<_It> && copy_constructible<_Fp> && predicate<_Fp&, iter_value_t<_It>&> &&
    predicate<_Fp&, iter_reference_t<_It>> && predicate<_Fp&, iter_common_reference_t<_It>>;

template <class _Fp, class _It1, class _It2>
concept indirect_binary_predicate = indirectly_readable<_It1> && indirectly_readable<_It2> && copy_constructible<_Fp> &&
    predicate<_Fp&, iter_value_t<_It1>&, iter_value_t<_It2>&> &&
    predicate<_Fp&, iter_value_t<_It1>&, iter_reference_t<_It2>> &&
    predicate<_Fp&, iter_reference_t<_It1>, iter_value_t<_It2>&> &&
    predicate<_Fp&, iter_reference_t<_It1>, iter_reference_t<_It2>> &&
    predicate<_Fp&, iter_common_reference_t<_It1>, iter_common_reference_t<_It2>>;

template <class _Fp, class _It1, class _It2 = _It1>
concept indirect_equivalence_relation = indirectly_readable<_It1> && indirectly_readable<_It2> &&
    copy_constructible<_Fp> && equivalence_relation<_Fp&, iter_value_t<_It1>&, iter_value_t<_It2>&> &&
    equivalence_relation<_Fp&, iter_value_t<_It1>&, iter_reference_t<_It2>> &&
    equivalence_relation<_Fp&, iter_reference_t<_It1>, iter_value_t<_It2>&> &&
    equivalence_relation<_Fp&, iter_reference_t<_It1>, iter_reference_t<_It2>> &&
    equivalence_relation<_Fp&, iter_common_reference_t<_It1>, iter_common_reference_t<_It2>>;

template <class _Fp, class _It1, class _It2 = _It1>
concept indirect_strict_weak_order = indirectly_readable<_It1> && indirectly_readable<_It2> &&
    copy_constructible<_Fp> && strict_weak_order<_Fp&, iter_value_t<_It1>&, iter_value_t<_It2>&> &&
    strict_weak_order<_Fp&, iter_value_t<_It1>&, iter_reference_t<_It2>> &&
    strict_weak_order<_Fp&, iter_reference_t<_It1>, iter_value_t<_It2>&> &&
    strict_weak_order<_Fp&, iter_reference_t<_It1>, iter_reference_t<_It2>> &&
    strict_weak_order<_Fp&, iter_common_reference_t<_It1>, iter_common_reference_t<_It2>>;

template <class _Fp, class... _Its>
    requires(indirectly_readable<_Its> && ...) && invocable<_Fp, iter_reference_t<_Its>...>
using indirect_result_t = invoke_result_t<_Fp, iter_reference_t<_Its>...>;

template <class _In, class _Out>
concept indirectly_movable = indirectly_readable<_In> && indirectly_writable<_Out, iter_rvalue_reference_t<_In>>;

template <class _In, class _Out>
concept indirectly_movable_storable = indirectly_movable<_In, _Out> && indirectly_writable<_Out, iter_value_t<_In>> &&
    movable<iter_value_t<_In>> && constructible_from<iter_value_t<_In>, iter_rvalue_reference_t<_In>> &&
    assignable_from<iter_value_t<_In>&, iter_rvalue_reference_t<_In>>;

template <class _In, class _Out>
concept indirectly_copyable = indirectly_readable<_In> && indirectly_writable<_Out, iter_reference_t<_In>>;

template <class _In, class _Out>
concept indirectly_copyable_storable = indirectly_copyable<_In, _Out> &&
    indirectly_writable<_Out, iter_value_t<_In>&> && indirectly_writable<_Out, const iter_value_t<_In>&> &&
    indirectly_writable<_Out, iter_value_t<_In>&&> && indirectly_writable<_Out, const iter_value_t<_In>&&> &&
    copyable<iter_value_t<_In>> && constructible_from<iter_value_t<_In>, iter_reference_t<_In>> &&
    assignable_from<iter_value_t<_In>&, iter_reference_t<_In>>;

// Note: indirectly_swappable is located in iter_swap.h to prevent a dependency cycle
// (both iter_swap and indirectly_swappable require indirectly_readable).

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

// [iterator.concept.readable]
template <class _In>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirectly_readable_impl_,
    requires(const _In __i)(typename(iter_value_t<_In>), typename(iter_reference_t<_In>),
        typename(iter_rvalue_reference_t<_In>), requires(same_as<iter_reference_t<_In>, decltype(*__i)>),
        requires(same_as<iter_rvalue_reference_t<_In>, decltype(::asc::std::ranges::__iter_move_cpo{}(__i))>),
        requires(common_reference_with<iter_reference_t<_In>&&, iter_value_t<_In>&>),
        requires(common_reference_with<iter_reference_t<_In>&&, iter_rvalue_reference_t<_In>&&>),
        requires(common_reference_with<iter_rvalue_reference_t<_In>&&, const iter_value_t<_In>&>)));

template <class _In>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_readable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirectly_readable_impl_, remove_cvref_t<_In>);

template <class _Tp>
using iter_common_reference_t =
    enable_if_t<indirectly_readable<_Tp>, common_reference_t<iter_reference_t<_Tp>, iter_value_t<_Tp>&>>;

// [iterator.concept.writable]
template <class _Out, class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_writable = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Out, _Tp), _Out&& __o,
    _Tp&& __t)((*__o = static_cast<_Tp&&>(__t)), (*static_cast<_Out&&>(__o) = static_cast<_Tp&&>(__t)),
    (const_cast<const iter_reference_t<_Out>&&>(*__o) = static_cast<_Tp&&>(__t)),
    (const_cast<const iter_reference_t<_Out>&&>(*static_cast<_Out&&>(__o)) = static_cast<_Tp&&>(__t)));

// [iterator.concept.winc]
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __integer_like = integral<_Tp> && !same_as<_Tp, bool>;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __signed_integer_like = signed_integral<_Tp>;

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__weakly_incrementable_,
    requires(_Ip __i)(typename(iter_difference_t<_Ip>), requires(!same_as<_Ip, bool>), requires(movable<_Ip>),
        requires(__signed_integer_like<iter_difference_t<_Ip>>), requires(same_as<_Ip&, decltype(++__i)>), (__i++)));

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT weakly_incrementable = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__weakly_incrementable_, _Ip);

// [iterator.concept.inc]
template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__incrementable_,
    requires(_Ip __i)(
        requires(regular<_Ip>), requires(weakly_incrementable<_Ip>), requires(same_as<_Ip, decltype(__i++)>)));

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT incrementable = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__incrementable_, _Ip);

// [iterator.concept.iterator]
template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__input_or_output_iterator_,
    requires(_Ip __i)(requires(weakly_incrementable<_Ip>), requires(__can_reference<decltype(*__i)>)));

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT input_or_output_iterator =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__input_or_output_iterator_, _Ip);

// [iterator.concept.sentinel]
template <class _Sp, class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__sentinel_for_,
    requires()(requires(semiregular<_Sp>), requires(input_or_output_iterator<_Ip>),
        requires(__weakly_equality_comparable_with<_Sp, _Ip>)));

template <class _Sp, class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT sentinel_for = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__sentinel_for_, _Sp, _Ip);

template <class, class>
inline constexpr bool disable_sized_sentinel_for = false;

template <class _Sp, class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__sized_sentinel_for_,
    requires(const _Ip& __i, const _Sp& __s)(requires(sentinel_for<_Sp, _Ip>),
        requires(!disable_sized_sentinel_for<remove_cv_t<_Sp>, remove_cv_t<_Ip>>),
        requires(same_as<iter_difference_t<_Ip>, decltype(__s - __i)>),
        requires(same_as<iter_difference_t<_Ip>, decltype(__i - __s)>)));

template <class _Sp, class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT sized_sentinel_for =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__sized_sentinel_for_, _Sp, _Ip);

// [iterator.concept.input]
// NOTE: The ordering here is load bearing. MSVC has issues with finding iterator_traits
//       We can work around this by checking other constraints first
template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__input_iterator_,
    requires()(requires(input_or_output_iterator<_Ip>), requires(indirectly_readable<_Ip>),
        typename(_ITER_CONCEPT<_Ip>), requires(derived_from<_ITER_CONCEPT<_Ip>, input_iterator_tag>)));

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT input_iterator = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__input_iterator_, _Ip);

// [iterator.concept.output]
template <class _Ip, class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__output_iterator_,
    requires(_Ip __it, _Tp&& __t)(requires(input_or_output_iterator<_Ip>), requires(indirectly_writable<_Ip, _Tp>),
        (*__it++ = static_cast<_Tp&&>(__t))));

template <class _Ip, class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT output_iterator = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__output_iterator_, _Ip, _Tp);

// [iterator.concept.forward]
template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__forward_iterator_,
    requires()(requires(input_iterator<_Ip>), requires(derived_from<_ITER_CONCEPT<_Ip>, forward_iterator_tag>),
        requires(incrementable<_Ip>), requires(sentinel_for<_Ip, _Ip>)));

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT forward_iterator = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__forward_iterator_, _Ip);

// [iterator.concept.bidir]
template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __iter_can_decrement =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Iter), _Iter __iter)(_Same_as(_Iter&)(--__iter), _Same_as(_Iter) __iter--);

template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT bidirectional_iterator = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Iter))(
    requires(forward_iterator<_Iter>), requires(derived_from<_ITER_CONCEPT<_Iter>, bidirectional_iterator_tag>),
    requires(__iter_can_decrement<_Iter>));

// [iterator.concept.random.access]
template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __iter_can_plus_equal = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR(
    (_Iter), _Iter __iter, const iter_difference_t<_Iter> __n)(_Same_as(_Iter&) __iter += __n);

template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __iter_can_plus = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Iter), const _Iter __iter,
    const iter_difference_t<_Iter> __n)(_Same_as(_Iter) __iter + __n, _Same_as(_Iter) __n + __iter);

template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __iter_can_minus_equal = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR(
    (_Iter), _Iter __iter, const iter_difference_t<_Iter> __n)(_Same_as(_Iter&) __iter -= __n);

template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __iter_can_minus = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR(
    (_Iter), const _Iter __iter, const iter_difference_t<_Iter> __n)(_Same_as(_Iter) __iter - __n);

template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __iter_can_subscript = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR(
    (_Iter), const _Iter __iter, const iter_difference_t<_Iter> __n)(_Same_as(iter_reference_t<_Iter>) __iter[__n]);

template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __random_access_iterator_operations = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Iter))(
    requires(__iter_can_plus_equal<_Iter>), requires(__iter_can_plus<_Iter>), requires(__iter_can_minus_equal<_Iter>),
    requires(__iter_can_minus<_Iter>), requires(__iter_can_subscript<_Iter>));

template <class _Iter>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT random_access_iterator =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Iter))(requires(bidirectional_iterator<_Iter>),
        requires(derived_from<_ITER_CONCEPT<_Iter>, random_access_iterator_tag>), requires(totally_ordered<_Iter>),
        requires(sized_sentinel_for<_Iter, _Iter>), requires(__random_access_iterator_operations<_Iter>));

// [iterator.concept.contiguous]
template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__contiguous_iterator_,
    requires(const _Ip& __i)(requires(random_access_iterator<_Ip>),
        requires(derived_from<_ITER_CONCEPT<_Ip>, contiguous_iterator_tag>),
        requires(is_lvalue_reference_v<iter_reference_t<_Ip>>),
        requires(same_as<iter_value_t<_Ip>, remove_cvref_t<iter_reference_t<_Ip>>>),
        requires(same_as<add_pointer_t<iter_reference_t<_Ip>>, decltype(::asc::std::to_address(__i))>)));

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT contiguous_iterator = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__contiguous_iterator_, _Ip);

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__has_arrow_, requires(_Ip __i)((__i.operator->())));

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __has_arrow =
    input_iterator<_Ip> && (is_pointer_v<_Ip> || CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__has_arrow_, _Ip));

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__has_const_arrow_, requires(const _Ip __i)((__i.operator->())));

template <class _Ip>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __has_const_arrow =
    (is_pointer_v<_Ip> || CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__has_const_arrow_, _Ip));

// [indirectcallable.indirectinvocable]
template <class _Fp, class _It>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirectly_unary_invocable,
    requires()(requires(indirectly_readable<_It>), requires(copy_constructible<_Fp>),
        requires(invocable<_Fp&, iter_value_t<_It>&>), requires(invocable<_Fp&, iter_reference_t<_It>>),
        requires(invocable<_Fp&, iter_common_reference_t<_It>>),
        requires(common_reference_with<invoke_result_t<_Fp&, iter_value_t<_It>&>,
            invoke_result_t<_Fp&, iter_reference_t<_It>>>)));

template <class _Fp, class _It>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_unary_invocable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirectly_unary_invocable, _Fp, _It);

template <class _Fp, class _It>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirectly_regular_unary_invocable_,
    requires()(requires(indirectly_readable<_It>), requires(copy_constructible<_Fp>),
        requires(regular_invocable<_Fp&, iter_value_t<_It>&>), requires(regular_invocable<_Fp&, iter_reference_t<_It>>),
        requires(regular_invocable<_Fp&, iter_common_reference_t<_It>>),
        requires(common_reference_with<invoke_result_t<_Fp&, iter_value_t<_It>&>,
            invoke_result_t<_Fp&, iter_reference_t<_It>>>)));

template <class _Fp, class _It>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_regular_unary_invocable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirectly_regular_unary_invocable_, _Fp, _It);

template <class _Fp, class _It>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirect_unary_predicate_,
    requires()(requires(indirectly_readable<_It>), requires(copy_constructible<_Fp>),
        requires(predicate<_Fp&, iter_value_t<_It>&>), requires(predicate<_Fp&, iter_reference_t<_It>>),
        requires(predicate<_Fp&, iter_common_reference_t<_It>>)));

template <class _Fp, class _It>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirect_unary_predicate =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirect_unary_predicate_, _Fp, _It);

template <class _Fp, class _It1, class _It2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirect_binary_predicate_,
    requires()(requires(indirectly_readable<_It1>), requires(indirectly_readable<_It2>),
        requires(copy_constructible<_Fp>), requires(predicate<_Fp&, iter_value_t<_It1>&, iter_value_t<_It2>&>),
        requires(predicate<_Fp&, iter_value_t<_It1>&, iter_reference_t<_It2>>),
        requires(predicate<_Fp&, iter_reference_t<_It1>, iter_value_t<_It2>&>),
        requires(predicate<_Fp&, iter_reference_t<_It1>, iter_reference_t<_It2>>),
        requires(predicate<_Fp&, iter_common_reference_t<_It1>, iter_common_reference_t<_It2>>)));

template <class _Fp, class _It1, class _It2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirect_binary_predicate =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirect_binary_predicate_, _Fp, _It1, _It2);

template <class _Fp, class _It1, class _It2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirect_equivalence_relation_,
    requires()(requires(indirectly_readable<_It1>), requires(indirectly_readable<_It2>),
        requires(copy_constructible<_Fp>),
        requires(equivalence_relation<_Fp&, iter_value_t<_It1>&, iter_value_t<_It2>&>),
        requires(equivalence_relation<_Fp&, iter_value_t<_It1>&, iter_reference_t<_It2>>),
        requires(equivalence_relation<_Fp&, iter_reference_t<_It1>, iter_value_t<_It2>&>),
        requires(equivalence_relation<_Fp&, iter_reference_t<_It1>, iter_reference_t<_It2>>),
        requires(equivalence_relation<_Fp&, iter_common_reference_t<_It1>, iter_common_reference_t<_It2>>)));

template <class _Fp, class _It1, class _It2 = _It1>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirect_equivalence_relation =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirect_equivalence_relation_, _Fp, _It1, _It2);

template <class _Fp, class _It1, class _It2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirect_strict_weak_order_,
    requires()(requires(indirectly_readable<_It1>), requires(indirectly_readable<_It2>),
        requires(copy_constructible<_Fp>), requires(strict_weak_order<_Fp&, iter_value_t<_It1>&, iter_value_t<_It2>&>),
        requires(strict_weak_order<_Fp&, iter_value_t<_It1>&, iter_reference_t<_It2>>),
        requires(strict_weak_order<_Fp&, iter_reference_t<_It1>, iter_value_t<_It2>&>),
        requires(strict_weak_order<_Fp&, iter_reference_t<_It1>, iter_reference_t<_It2>>),
        requires(strict_weak_order<_Fp&, iter_common_reference_t<_It1>, iter_common_reference_t<_It2>>)));

template <class _Fp, class _It1, class _It2 = _It1>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirect_strict_weak_order =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirect_strict_weak_order_, _Fp, _It1, _It2);

template <class _Fp, class... _Its>
using indirect_result_t = enable_if_t<(indirectly_readable<_Its> && ...) && invocable<_Fp, iter_reference_t<_Its>...>,
    invoke_result_t<_Fp, iter_reference_t<_Its>...>>;

template <class _In, class _Out>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirectly_movable_,
    requires()(requires(indirectly_readable<_In>), requires(indirectly_writable<_Out, iter_rvalue_reference_t<_In>>)));

template <class _In, class _Out>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_movable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirectly_movable_, _In, _Out);

template <class _In, class _Out>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirectly_movable_storable_,
    requires()(requires(indirectly_movable<_In, _Out>), requires(indirectly_writable<_Out, iter_value_t<_In>>),
        requires(movable<iter_value_t<_In>>),
        requires(constructible_from<iter_value_t<_In>, iter_rvalue_reference_t<_In>>),
        requires(assignable_from<iter_value_t<_In>&, iter_rvalue_reference_t<_In>>)));

template <class _In, class _Out>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_movable_storable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirectly_movable_storable_, _In, _Out);

template <class _In, class _Out>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirectly_copyable_,
    requires()(requires(indirectly_readable<_In>), requires(indirectly_writable<_Out, iter_reference_t<_In>>)));

template <class _In, class _Out>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_copyable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirectly_copyable_, _In, _Out);

template <class _In, class _Out>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirectly_copyable_storable_,
    requires()(requires(indirectly_copyable<_In, _Out>), requires(indirectly_writable<_Out, iter_value_t<_In>&>),
        requires(indirectly_writable<_Out, const iter_value_t<_In>&>),
        requires(indirectly_writable<_Out, iter_value_t<_In>&&>),
        requires(indirectly_writable<_Out, const iter_value_t<_In>&&>), requires(copyable<iter_value_t<_In>>),
        requires(constructible_from<iter_value_t<_In>, iter_reference_t<_In>>),
        requires(assignable_from<iter_value_t<_In>&, iter_reference_t<_In>>)));

template <class _In, class _Out>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_copyable_storable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirectly_copyable_storable_, _In, _Out);

template <class _Ip, class = void>
inline constexpr bool __has_iter_category = false;

template <class _Ip>
inline constexpr bool __has_iter_category<_Ip, void_t<typename _Ip::iterator_category>> = true;

template <class _Ip, class = void>
inline constexpr bool __has_iter_concept = false;

template <class _Ip>
inline constexpr bool __has_iter_concept<_Ip, void_t<typename _Ip::iterator_concept>> = true;

#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_CONCEPTS_H
