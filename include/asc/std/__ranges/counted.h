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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_COUNTED_H
#define CANN_ASC_STL_ASC_STD___RANGES_COUNTED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/counted_iterator.h>
#include <asc/std/__iterator/default_sentinel.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/subrange.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/span>
namespace asc::std::ranges::views {
struct __counted_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class Iterator)
    CANN_ASC_STL_DETAIL_REQUIRES((contiguous_iterator<Iterator>))
    CANN_ASC_STL_API static constexpr auto __go(Iterator it, iter_difference_t<Iterator> count) noexcept(
        noexcept(span(::asc::std::to_address(it), static_cast<size_t>(count))))
    // Deliberately omit return-type SFINAE, because to_address is not SFINAE-friendly
    {
        return span(::asc::std::to_address(it), static_cast<size_t>(count));
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Iterator)
    CANN_ASC_STL_DETAIL_REQUIRES(((!contiguous_iterator<Iterator> && random_access_iterator<Iterator>)))
    CANN_ASC_STL_API static constexpr auto __go(Iterator it, iter_difference_t<Iterator> count) noexcept(
        noexcept(subrange(it, it + count))) -> subrange<Iterator>
    {
        return subrange(it, it + count);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Iterator)
    CANN_ASC_STL_DETAIL_REQUIRES(((!contiguous_iterator<Iterator> && !random_access_iterator<Iterator>)))
    CANN_ASC_STL_API static constexpr auto __go(Iterator it, iter_difference_t<Iterator> count) noexcept(
        noexcept(subrange(counted_iterator(::asc::std::move(it), count), default_sentinel,
            static_cast<make_unsigned_t<iter_difference_t<Iterator>>>(
                count)))) -> subrange<counted_iterator<Iterator>, default_sentinel_t>
    {
        // default_sentinel difference sign conventions are inconsistent across the
        // dependencies, so the size is passed explicitly; this keeps size() equal to
        // count on this path instead of relying on a sign convention.
        return subrange(counted_iterator(::asc::std::move(it), count), default_sentinel,
            static_cast<make_unsigned_t<iter_difference_t<Iterator>>>(count));
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Iterator, class Difference)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<Difference, iter_difference_t<decay_t<Iterator>>> &&
        input_or_output_iterator<decay_t<Iterator>>))
    CANN_ASC_STL_API constexpr auto operator()(Iterator&& it, Difference&& count) const
        noexcept(noexcept(__go(::asc::std::forward<Iterator>(it), ::asc::std::forward<Difference>(count))))
            -> decltype(__go(::asc::std::forward<Iterator>(it), ::asc::std::forward<Difference>(count)))
    {
        return __go(::asc::std::forward<Iterator>(it),
            ::asc::std::forward<Difference>(count));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __counted_fn counted{};
}  // namespace asc::std::ranges::views

#endif  // CANN_ASC_STL_ASC_STD___RANGES_COUNTED_H
