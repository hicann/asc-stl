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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_REF_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_REF_VIEW_H

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
#include <asc/std/__concepts/different_from.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/data.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__utility/forward.h>
namespace asc::std::ranges {
template <class Range>
class ref_view : public view_interface<ref_view<Range>> {
public:
    CANN_ASC_STL_API constexpr explicit ref_view(Range& range) noexcept : range_(::asc::std::addressof(range))
    {}
    CANN_ASC_STL_API constexpr auto begin() const
    {
        return ranges::begin(*range_);
    }
    CANN_ASC_STL_API constexpr auto end() const
    {
        return ranges::end(*range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr auto empty() const
    {
        return ranges::empty(*range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ranges::size(*range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr auto data() const
    {
        return ranges::data(*range_);
    }
    CANN_ASC_STL_API constexpr Range& base() const noexcept
    {
        return *range_;
    }

private:
    Range* range_;
};
template <class R>
inline constexpr bool enable_borrowed_range<ref_view<R>> = true;
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_REF_VIEW_H
