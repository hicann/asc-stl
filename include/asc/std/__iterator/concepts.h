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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_CONCEPTS_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_CONCEPTS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
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

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Sentinel, class Iter>
inline constexpr bool disable_sized_sentinel_for = false;

template <class F, class... Its>
using indirect_result_t = invoke_result_t<F, iter_reference_t<Its>...>;

template <class T>
using iter_common_reference_t = common_reference_t<iter_reference_t<T>, iter_value_t<T>&>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class T>
using __with_reference = T&;

template <class T>
concept __can_reference = requires { typename __with_reference<T>; };

// [iterator.concept.readable]
template <class In>
concept __indirectly_readable_impl =
    requires(const In input) {
        typename iter_value_t<In>;
        typename iter_reference_t<In>;
        typename iter_rvalue_reference_t<In>;
        { *input } -> same_as<iter_reference_t<In>>;
        { iter_move(input) } -> same_as<iter_rvalue_reference_t<In>>;
    } && common_reference_with<iter_reference_t<In>&&, iter_value_t<In>&> &&
    common_reference_with<iter_reference_t<In>&&, iter_rvalue_reference_t<In>&&> &&
    common_reference_with<iter_rvalue_reference_t<In>&&, const iter_value_t<In>&>;

template <class In>
concept indirectly_readable = __indirectly_readable_impl<remove_cvref_t<In>>;

template <class Out, class T>
concept indirectly_writable = requires(Out&& output, T&& value) {
    *output = ::asc::std::forward<T>(value);
    *::asc::std::forward<Out>(output) = ::asc::std::forward<T>(value);
    const_cast<const iter_reference_t<Out>&&>(*output) = ::asc::std::forward<T>(value);
    const_cast<const iter_reference_t<Out>&&>(*::asc::std::forward<Out>(output)) = ::asc::std::forward<T>(value);
};

// [iterator.concept.winc]
template <class It>
concept weakly_incrementable = !same_as<It, bool> &&  // 部分编译器对 bool 的自增处理有缺陷，显式排除
    movable<It> && requires(It value) {
        typename iter_difference_t<It>;
        requires signed_integral<iter_difference_t<It>>;
        { ++value } -> same_as<It&>;
        value++;
    };

template <class It>
concept incrementable = regular<It> && weakly_incrementable<It> && requires(It value) {
    { value++ } -> same_as<It>;
};

template <class It>
concept input_or_output_iterator = requires(It value) {
    { *value } -> __can_reference;
} && weakly_incrementable<It>;

template <class Sent, class It>
concept sentinel_for = semiregular<Sent> && input_or_output_iterator<It> && __weakly_equality_comparable_with<Sent, It>;

template <class Sent, class It>
concept sized_sentinel_for = sentinel_for<Sent, It> &&
    !disable_sized_sentinel_for<remove_cv_t<Sent>, remove_cv_t<It>> && requires(const It& iter, const Sent& sent) {
        { sent - iter } -> same_as<iter_difference_t<It>>;
        { iter - sent } -> same_as<iter_difference_t<It>>;
    };

// [iterator.concept.input]
template <class It>
concept input_iterator = input_or_output_iterator<It> && indirectly_readable<It> &&
    requires { typename _ITER_CONCEPT<It>; } && derived_from<_ITER_CONCEPT<It>, input_iterator_tag>;

template <class It, class T>
concept output_iterator = input_or_output_iterator<It> && indirectly_writable<It, T> &&
    requires(It iter, T&& value) { *iter++ = ::asc::std::forward<T>(value); };  // NOLINT(build/include_what_you_use)

// [iterator.concept.forward]
template <class It>
concept forward_iterator = input_iterator<It> && derived_from<_ITER_CONCEPT<It>, forward_iterator_tag> &&
    incrementable<It> && sentinel_for<It, It>;

// [iterator.concept.bidir]
template <class It>
concept __iter_can_decrement = requires(It value) {
    { --value } -> same_as<It&>;
    { value-- } -> same_as<It>;
};

template <class It>
concept bidirectional_iterator =
    forward_iterator<It> && derived_from<_ITER_CONCEPT<It>, bidirectional_iterator_tag> && __iter_can_decrement<It>;

template <class It>
concept __iter_can_plus_equal = requires(It value, const iter_difference_t<It> count) {
    { value += count } -> same_as<It&>;
};

template <class It>
concept __iter_can_plus = requires(const It value, const iter_difference_t<It> count) {
    { value + count } -> same_as<It>;
    { count + value } -> same_as<It>;
};

template <class It>
concept __iter_can_minus_equal = requires(It value, const iter_difference_t<It> count) {
    { value -= count } -> same_as<It&>;
};

template <class It>
concept __iter_can_minus = requires(const It value, const iter_difference_t<It> count) {
    { value - count } -> same_as<It>;
};

template <class It>
concept __iter_can_subscript = requires(const It value, const iter_difference_t<It> count) {
    { value[count] } -> same_as<iter_reference_t<It>>;
};

template <class It>
concept __random_access_operations = __iter_can_plus_equal<It> && __iter_can_plus<It> && __iter_can_minus_equal<It> &&
    __iter_can_minus<It> && __iter_can_subscript<It>;

// [iterator.concept.random.access]
template <class It>
concept random_access_iterator =
    bidirectional_iterator<It> && derived_from<_ITER_CONCEPT<It>, random_access_iterator_tag> && totally_ordered<It> &&
    sized_sentinel_for<It, It> && __random_access_operations<It>;

// [iterator.concept.contiguous]
template <class It>
concept contiguous_iterator = random_access_iterator<It> && derived_from<_ITER_CONCEPT<It>, contiguous_iterator_tag> &&
    is_lvalue_reference_v<iter_reference_t<It>> && same_as<iter_value_t<It>, remove_cvref_t<iter_reference_t<It>>> &&
    requires(const It& value) {
        { ::asc::std::to_address(value) } -> same_as<add_pointer_t<iter_reference_t<It>>>;
    };

template <class F, class It>
concept indirectly_unary_invocable =
    indirectly_readable<It> && copy_constructible<F> && invocable<F&, iter_value_t<It>&> &&
    invocable<F&, iter_reference_t<It>> && invocable<F&, iter_common_reference_t<It>> &&
    common_reference_with<invoke_result_t<F&, iter_value_t<It>&>, invoke_result_t<F&, iter_reference_t<It>>>;

template <class F, class It>
concept indirectly_regular_unary_invocable =
    indirectly_readable<It> && copy_constructible<F> && regular_invocable<F&, iter_value_t<It>&> &&
    regular_invocable<F&, iter_reference_t<It>> && regular_invocable<F&, iter_common_reference_t<It>> &&
    common_reference_with<invoke_result_t<F&, iter_value_t<It>&>, invoke_result_t<F&, iter_reference_t<It>>>;

template <class F, class It>
concept indirect_unary_predicate =
    indirectly_readable<It> && copy_constructible<F> && predicate<F&, iter_value_t<It>&> &&
    predicate<F&, iter_reference_t<It>> && predicate<F&, iter_common_reference_t<It>>;

template <class F, class It1, class It2>
concept indirect_binary_predicate = indirectly_readable<It1> && indirectly_readable<It2> && copy_constructible<F> &&
    predicate<F&, iter_value_t<It1>&, iter_value_t<It2>&> && predicate<F&, iter_value_t<It1>&, iter_reference_t<It2>> &&
    predicate<F&, iter_reference_t<It1>, iter_value_t<It2>&> &&
    predicate<F&, iter_reference_t<It1>, iter_reference_t<It2>> &&
    predicate<F&, iter_common_reference_t<It1>, iter_common_reference_t<It2>>;

template <class F, class It1, class It2 = It1>
concept indirect_equivalence_relation = indirectly_readable<It1> && indirectly_readable<It2> && copy_constructible<F> &&
    equivalence_relation<F&, iter_value_t<It1>&, iter_value_t<It2>&> &&
    equivalence_relation<F&, iter_value_t<It1>&, iter_reference_t<It2>> &&
    equivalence_relation<F&, iter_reference_t<It1>, iter_value_t<It2>&> &&
    equivalence_relation<F&, iter_reference_t<It1>, iter_reference_t<It2>> &&
    equivalence_relation<F&, iter_common_reference_t<It1>, iter_common_reference_t<It2>>;

template <class F, class It1, class It2 = It1>
concept indirect_strict_weak_order = indirectly_readable<It1> && indirectly_readable<It2> && copy_constructible<F> &&
    strict_weak_order<F&, iter_value_t<It1>&, iter_value_t<It2>&> &&
    strict_weak_order<F&, iter_value_t<It1>&, iter_reference_t<It2>> &&
    strict_weak_order<F&, iter_reference_t<It1>, iter_value_t<It2>&> &&
    strict_weak_order<F&, iter_reference_t<It1>, iter_reference_t<It2>> &&
    strict_weak_order<F&, iter_common_reference_t<It1>, iter_common_reference_t<It2>>;

template <class In, class Out>
concept indirectly_movable = indirectly_readable<In> && indirectly_writable<Out, iter_rvalue_reference_t<In>>;

template <class In, class Out>
concept indirectly_movable_storable = indirectly_movable<In, Out> && indirectly_writable<Out, iter_value_t<In>> &&
    movable<iter_value_t<In>> && constructible_from<iter_value_t<In>, iter_rvalue_reference_t<In>> &&
    assignable_from<iter_value_t<In>&, iter_rvalue_reference_t<In>>;

template <class In, class Out>
concept indirectly_copyable = indirectly_readable<In> && indirectly_writable<Out, iter_reference_t<In>>;

template <class In, class Out>
concept indirectly_copyable_storable = indirectly_copyable<In, Out> && indirectly_writable<Out, iter_value_t<In>&> &&
    indirectly_writable<Out, const iter_value_t<In>&> && indirectly_writable<Out, iter_value_t<In>&&> &&
    indirectly_writable<Out, const iter_value_t<In>&&> && copyable<iter_value_t<In>> &&
    constructible_from<iter_value_t<In>, iter_reference_t<In>> &&
    assignable_from<iter_value_t<In>&, iter_reference_t<In>>;
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_CONCEPTS_H
