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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_ALL_H
#define CANN_ASC_STL_ASC_STD___RANGES_ALL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/owning_view.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/ref_view.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
namespace asc::std::ranges::views {
struct __all_fn {
    template <class Range>
    CANN_ASC_STL_API constexpr ref_view<Range> operator()(Range& range) const noexcept
    {
        return ref_view<Range>(range);
    }
    template <class Range>
    CANN_ASC_STL_API constexpr owning_view<decay_t<Range>> operator()(Range&& range) const
    {
        return owning_view<decay_t<Range>>(::asc::std::forward<Range>(range));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __all_fn all{};
template <class Range>
using all_t = decltype(all(::asc::std::declval<Range>()));
}  // namespace asc::std::ranges::views

#endif  // CANN_ASC_STL_ASC_STD___RANGES_ALL_H
