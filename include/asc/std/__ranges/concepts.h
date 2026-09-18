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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_CONCEPTS_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_CONCEPTS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/data.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/enable_view.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

// [range.range]

template <class _Tp>
concept range = requires(_Tp& __t) {
    ::asc::std::ranges::__begin_cpo{}(__t);  // sometimes equality-preserving
    ::asc::std::ranges::__end_cpo{}(__t);
};

template <class _Tp>
concept input_range = range<_Tp> && input_iterator<iterator_t<_Tp>>;

template <class _Range>
concept borrowed_range =
    range<_Range> && (is_lvalue_reference_v<_Range> || enable_borrowed_range<remove_cvref_t<_Range>>);

// `iterator_t` defined in <__ranges/access.h>

template <range _Rp>
using sentinel_t = decltype(::asc::std::ranges::__end_cpo{}(::asc::std::declval<_Rp&>()));

template <range _Rp>
using range_difference_t = iter_difference_t<iterator_t<_Rp>>;

template <range _Rp>
using range_value_t = iter_value_t<iterator_t<_Rp>>;

template <range _Rp>
using range_reference_t = iter_reference_t<iterator_t<_Rp>>;

template <range _Rp>
using range_rvalue_reference_t = iter_rvalue_reference_t<iterator_t<_Rp>>;

template <range _Rp>
using range_common_reference_t = iter_common_reference_t<iterator_t<_Rp>>;

// [range.sized]
template <class _Tp>
concept sized_range = range<_Tp> && requires(_Tp& __t) { ::asc::std::ranges::__size_cpo{}(__t); };

template <sized_range _Rp>
using range_size_t = decltype(::asc::std::ranges::__size_cpo{}(::asc::std::declval<_Rp&>()));

// `disable_sized_range` defined in `<__ranges/size.h>`

// [range.view], views

// `enable_view` defined in <__ranges/enable_view.h>
// `view_base` defined in <__ranges/enable_view.h>

template <class _Tp>
concept view = range<_Tp> && movable<_Tp> && enable_view<_Tp>;

template <class _Range>
concept __simple_view = view<_Range> && range<const _Range> && same_as<iterator_t<_Range>, iterator_t<const _Range>> &&
    same_as<sentinel_t<_Range>, sentinel_t<const _Range>>;

// [range.refinements], other range refinements
template <class _Rp, class _Tp>
concept output_range = range<_Rp> && output_iterator<iterator_t<_Rp>, _Tp>;

template <class _Tp>
concept forward_range = input_range<_Tp> && forward_iterator<iterator_t<_Tp>>;

template <class _Tp>
concept bidirectional_range = forward_range<_Tp> && bidirectional_iterator<iterator_t<_Tp>>;

template <class _Tp>
concept random_access_range = bidirectional_range<_Tp> && random_access_iterator<iterator_t<_Tp>>;

template <class _Tp>
concept contiguous_range = random_access_range<_Tp> && contiguous_iterator<iterator_t<_Tp>> && requires(_Tp& __t) {
    { ::asc::std::ranges::__data_cpo{}(__t) } -> same_as<add_pointer_t<range_reference_t<_Tp>>>;
};

template <class _Tp>
concept common_range = range<_Tp> && same_as<iterator_t<_Tp>, sentinel_t<_Tp>>;

template <class _Tp>
concept viewable_range = range<_Tp> &&
    ((view<remove_cvref_t<_Tp>> && constructible_from<remove_cvref_t<_Tp>, _Tp>) ||
        (!view<remove_cvref_t<_Tp>> &&
            (is_lvalue_reference_v<_Tp> ||
                (movable<remove_reference_t<_Tp>> && !__is_asc_std_initializer_list<remove_cvref_t<_Tp>>))));

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !concepts vvv

// [range.range]

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT range = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Tp), _Tp& __t)(
    void(::asc::std::ranges::__begin_cpo{}(__t)), void(::asc::std::ranges::__end_cpo{}(__t)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT input_range =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Tp))(requires(range<_Tp>), requires(input_iterator<iterator_t<_Tp>>));

template <class _Range>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__borrowed_range_,
    requires()(requires(range<_Range>),
        requires((is_lvalue_reference_v<_Range> || enable_borrowed_range<remove_cvref_t<_Range>>))));

template <class _Range>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT borrowed_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__borrowed_range_, _Range);

// `iterator_t` defined in <__ranges/access.h>

template <class _Rp>
using sentinel_t = enable_if_t<range<_Rp>, decltype(::asc::std::ranges::__end_cpo{}(::asc::std::declval<_Rp&>()))>;

template <class _Rp>
using range_difference_t = enable_if_t<range<_Rp>, iter_difference_t<iterator_t<_Rp>>>;

template <class _Rp>
using range_value_t = enable_if_t<range<_Rp>, iter_value_t<iterator_t<_Rp>>>;

template <class _Rp>
using range_reference_t = enable_if_t<range<_Rp>, iter_reference_t<iterator_t<_Rp>>>;

template <class _Rp>
using range_rvalue_reference_t = enable_if_t<range<_Rp>, iter_rvalue_reference_t<iterator_t<_Rp>>>;

template <class _Rp>
using range_common_reference_t = enable_if_t<range<_Rp>, iter_common_reference_t<iterator_t<_Rp>>>;

// [range.sized]
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__sized_range_,
    requires(_Tp& __t)(requires(range<_Tp>), typename(decltype(::asc::std::ranges::__size_cpo{}(__t)))));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT sized_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__sized_range_, _Tp);

template <class _Rp>
using range_size_t =
    enable_if_t<sized_range<_Rp>, decltype(::asc::std::ranges::__size_cpo{}(::asc::std::declval<_Rp&>()))>;

// `disable_sized_range` defined in `<__ranges/size.h>`

// [range.view], views

// `enable_view` defined in <__ranges/enable_view.h>
// `view_base` defined in <__ranges/enable_view.h>

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(
    __view_, requires()(requires(range<_Tp>), requires(movable<_Tp>), requires(enable_view<_Tp>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT view = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__view_, _Tp);

template <class _Range>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__simple_view_,
    requires()(requires(view<_Range>), requires(range<const _Range>),
        requires(same_as<iterator_t<_Range>, iterator_t<const _Range>>),
        requires(same_as<sentinel_t<_Range>, sentinel_t<const _Range>>)));

template <class _Range>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __simple_view = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__simple_view_, _Range);

// [range.refinements], other range refinements
template <class _Rp, class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(
    __output_range_, requires()(requires(range<_Rp>), requires(output_iterator<iterator_t<_Rp>, _Tp>)));

template <class _Rp, class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT output_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__output_range_, _Rp, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(
    __forward_range_, requires()(requires(input_range<_Tp>), requires(forward_iterator<iterator_t<_Tp>>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT forward_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__forward_range_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__bidirectional_range_,
    requires()(requires(forward_range<_Tp>), requires(bidirectional_iterator<iterator_t<_Tp>>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT bidirectional_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__bidirectional_range_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__random_access_range_,
    requires()(requires(bidirectional_range<_Tp>), requires(random_access_iterator<iterator_t<_Tp>>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT random_access_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__random_access_range_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__contiguous_range_,
    requires(_Tp& __t)(requires(random_access_range<_Tp>), requires(contiguous_iterator<iterator_t<_Tp>>),
        requires(same_as<decltype(::asc::std::ranges::__data_cpo{}(__t)), add_pointer_t<range_reference_t<_Tp>>>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT contiguous_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__contiguous_range_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(
    __common_range_, requires()(requires(range<_Tp>), requires(same_as<iterator_t<_Tp>, sentinel_t<_Tp>>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT common_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__common_range_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__viewable_range_,
    requires()(requires(range<_Tp>),
        requires(((view<remove_cvref_t<_Tp>> && constructible_from<remove_cvref_t<_Tp>, _Tp>) ||
            (!view<remove_cvref_t<_Tp>> &&
                (is_lvalue_reference_v<_Tp> ||
                    (movable<remove_reference_t<_Tp>> && !__is_asc_std_initializer_list<remove_cvref_t<_Tp>>)))))));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT viewable_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__viewable_range_, _Tp);

#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

// [container.intro.reqmts]
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Range, class _Tp>
concept __container_compatible_range = input_range<_Range> && convertible_to<range_reference_t<_Range>, _Tp>;
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
template <class _Range, class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__container_compatible_range_,
    requires()(requires(input_range<_Range>), requires(convertible_to<range_reference_t<_Range>, _Tp>)));

template <class _Range, class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __container_compatible_range =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__container_compatible_range_, _Range, _Tp);
#endif  // !concepts

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_CONCEPTS_H
