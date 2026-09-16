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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_ITERATOR_TRAITS_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_ITERATOR_TRAITS_H

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
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__concepts/totally_ordered.h>
#include <asc/std/__fwd/iterator.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__type_traits/add_const.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_primary_template.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/priority_tag.h>
#include <asc/std/cstddef>
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <iterator>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
using iter_reference_t = decltype(*::asc::std::declval<T&>());

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};
#else
using input_iterator_tag = ::std::input_iterator_tag;
using output_iterator_tag = ::std::output_iterator_tag;
using forward_iterator_tag = ::std::forward_iterator_tag;
using bidirectional_iterator_tag = ::std::bidirectional_iterator_tag;
using random_access_iterator_tag = ::std::random_access_iterator_tag;
#endif
struct contiguous_iterator_tag : random_access_iterator_tag {};

template <class Iter, class>
struct iterator_traits {
    using __asc_primary_template = iterator_traits;
};

template <class Iter>
struct iterator_traits<Iter,
    void_t<typename Iter::difference_type, typename Iter::value_type, typename Iter::pointer, typename Iter::reference,
        typename Iter::iterator_category>> {
    using difference_type = typename Iter::difference_type;
    using value_type = typename Iter::value_type;
    using pointer = typename Iter::pointer;
    using reference = typename Iter::reference;
    using iterator_category = typename Iter::iterator_category;
};

template <class T>
struct iterator_traits<T*, enable_if_t<is_convertible_v<T (*)[], const volatile void*>>> {  // NOLINT(whitespace/parens)
    using difference_type = ptrdiff_t;
    using value_type = remove_cv_t<T>;
    using pointer = T*;
    using reference = T&;
    using iterator_category = random_access_iterator_tag;
    using iterator_concept = contiguous_iterator_tag;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_ITERATOR_TRAITS_H
