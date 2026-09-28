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
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/counted_iterator.h>
#include <asc/std/__iterator/default_sentinel.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/subrange.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/span>
namespace asc::std::ranges::views {
struct __counted_fn {
    template <class Iterator>
    CANN_ASC_STL_API constexpr auto operator()(
        Iterator first, iter_difference_t<Iterator> count) const -> subrange<Iterator, Iterator, subrange_kind::sized>
    {
        return {first, first + count, static_cast<__SIZE_TYPE__>(count)};
    }
};
inline constexpr __counted_fn counted{};
}  // namespace asc::std::ranges::views

#endif  // CANN_ASC_STL_ASC_STD___RANGES_COUNTED_H
