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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_CONCEPTS_H
#define CANN_ASC_STL_ASC_STD___RANGES_CONCEPTS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
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

// 设备编译不引入宿主 initializer_list（保持负向合同的诊断面）：宿主侧内联
// 最小等价探测，设备侧恒 false（viewable_range 不做花括号列表排除）。
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <initializer_list>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class T>
inline constexpr bool __is_asc_std_initializer_list = false;

template <class E>
inline constexpr bool __is_asc_std_initializer_list<::std::initializer_list<E>> = true;
#else
template <class T>
inline constexpr bool __is_asc_std_initializer_list = false;
#endif

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class T>
concept range = requires(T& value) {
    __begin_cpo{}(value);  // 有时保持相等性
    __end_cpo{}(value);
};
template <range R>
using sentinel_t = decltype(__end_cpo{}(::asc::std::declval<R&>()));
template <range R>
using range_difference_t = iter_difference_t<iterator_t<R>>;
template <range R>
using range_value_t = iter_value_t<iterator_t<R>>;
template <range R>
using range_reference_t = iter_reference_t<iterator_t<R>>;
template <range R>
using range_rvalue_reference_t = iter_rvalue_reference_t<iterator_t<R>>;
template <range R>
using range_common_reference_t = iter_common_reference_t<iterator_t<R>>;
template <class T>
concept borrowed_range = range<T> && (is_lvalue_reference_v<T> || enable_borrowed_range<remove_cvref_t<T>>);
template <class T>
concept sized_range = range<T> && requires(T& value) { __size_cpo{}(value); };
template <sized_range R>
using range_size_t = decltype(__size_cpo{}(::asc::std::declval<R&>()));
template <class T>
concept input_range = range<T> && input_iterator<iterator_t<T>>;
template <class T, class U>
concept output_range = range<T> && output_iterator<iterator_t<T>, U>;
template <class T>
concept forward_range = input_range<T> && forward_iterator<iterator_t<T>>;
template <class T>
concept bidirectional_range = forward_range<T> && bidirectional_iterator<iterator_t<T>>;
template <class T>
concept random_access_range = bidirectional_range<T> && random_access_iterator<iterator_t<T>>;
template <class T>
concept contiguous_range = random_access_range<T> && contiguous_iterator<iterator_t<T>> && requires(T& value) {
    { __data_cpo{}(value) } -> same_as<add_pointer_t<range_reference_t<T>>>;
};
template <class T>
concept common_range = range<T> && same_as<iterator_t<T>, sentinel_t<T>>;
template <class T>
concept view = range<T> && movable<T> && enable_view<T>;
template <class T>
concept __simple_view = view<T> && range<const T> && same_as<iterator_t<T>, iterator_t<const T>> &&
    same_as<sentinel_t<T>, sentinel_t<const T>>;
template <class T>
concept viewable_range = range<T> &&
    ((view<remove_cvref_t<T>> && constructible_from<remove_cvref_t<T>, T>) ||
        (!view<remove_cvref_t<T>> &&
            (is_lvalue_reference_v<T> ||
                (movable<remove_reference_t<T>> && !__is_asc_std_initializer_list<remove_cvref_t<T>>))));

// [container.intro.reqmts]
template <class R, class T>
concept __container_compatible_range = input_range<R> && convertible_to<range_reference_t<R>, T>;

#else

template <class R>
using sentinel_t = decltype(__end_cpo{}(::asc::std::declval<R&>()));
template <class R>
using range_difference_t = iter_difference_t<iterator_t<R>>;
template <class R>
using range_value_t = iter_value_t<iterator_t<R>>;
template <class R>
using range_reference_t = iter_reference_t<iterator_t<R>>;
template <class R>
using range_rvalue_reference_t = iter_rvalue_reference_t<iterator_t<R>>;
template <class R>
using range_common_reference_t = iter_common_reference_t<iterator_t<R>>;
template <class R>
using range_size_t = decltype(__size_cpo{}(::asc::std::declval<R&>()));

#endif
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_CONCEPTS_H
