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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_UNWRAP_ITER_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_UNWRAP_ITER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __unwrap_iter_detail {

// Minimal local contiguous-traversal probes: the dual category/concept probes
// are SFINAE-friendly under C++17; the pointer specialization is always
// contiguous.
template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_category_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool
    __has_iterator_category_convertible_to<Iter, Tag, void_t<typename iterator_traits<Iter>::iterator_category>> =
        is_convertible_v<typename iterator_traits<Iter>::iterator_category, Tag>;

template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_concept_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool __has_iterator_concept_convertible_to<Iter, Tag, void_t<typename Iter::iterator_concept>> =
    is_convertible_v<typename Iter::iterator_concept, Tag>;

template <class Iter>
inline constexpr bool __has_contiguous_traversal =
    __has_iterator_category_convertible_to<Iter, contiguous_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, contiguous_iterator_tag>;

template <class Tp>
inline constexpr bool __has_contiguous_traversal<Tp*> = true;

}  // namespace __unwrap_iter_detail

// __unwrap_iter strips iterator wrappers (reverse_iterator/__wrap_iter etc.),
// reducing the number of template instantiations and enabling pointer-based
// fast paths for copy/sort and the like; __rewrap_iter restores the unwrapped
// result to the original iterator type.
template <class Iterator, bool = __unwrap_iter_detail::__has_contiguous_traversal<Iterator>>
struct __unwrap_iter_impl {
    // Non-contiguous iterators: returned unchanged.
    static CANN_ASC_STL_API constexpr Iterator __rewrap(Iterator, Iterator __iter)
    {
        return __iter;
    }
    static CANN_ASC_STL_API constexpr Iterator __unwrap(Iterator __i) noexcept
    {
        return __i;
    }
};

// Contiguous iterators: unwrap to a raw pointer.
template <class Iterator>
struct __unwrap_iter_impl<Iterator, true> {
    using __to_address_t = decltype(::asc::std::__to_address(::asc::std::declval<Iterator>()));

    static CANN_ASC_STL_API constexpr Iterator __rewrap(Iterator __orig_iter, __to_address_t __unwrapped_iter)
    {
        return __orig_iter + (__unwrapped_iter - ::asc::std::__to_address(__orig_iter));
    }

    static CANN_ASC_STL_API constexpr __to_address_t __unwrap(Iterator __i) noexcept
    {
        return ::asc::std::__to_address(__i);
    }
};

template <class Iterator, class Impl = __unwrap_iter_impl<Iterator>,
    enable_if_t<is_copy_constructible_v<Iterator>, int> = 0>
CANN_ASC_STL_API constexpr decltype(Impl::__unwrap(::asc::std::declval<Iterator>())) __unwrap_iter(
    Iterator __i) noexcept
{
    return Impl::__unwrap(__i);
}

template <class OrigIterator, class Iterator, class Impl = __unwrap_iter_impl<OrigIterator>>
CANN_ASC_STL_API constexpr OrigIterator __rewrap_iter(OrigIterator __orig_iter, Iterator __iter) noexcept
{
    return Impl::__rewrap(
        ::asc::std::move(__orig_iter), ::asc::std::move(__iter));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_UNWRAP_ITER_H
