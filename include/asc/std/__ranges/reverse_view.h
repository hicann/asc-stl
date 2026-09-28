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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_REVERSE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_REVERSE_VIEW_H

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
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/non_propagating_cache.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/subrange.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
template <class View>
class reverse_view : public view_interface<reverse_view<View>> {
public:
    CANN_ASC_STL_API constexpr reverse_view() = default;
    CANN_ASC_STL_API constexpr explicit reverse_view(View view) : view_(::asc::std::move(view))
    {}
    CANN_ASC_STL_API constexpr auto begin()
    {
        return reverse_iterator<iterator_t<View>>(ranges::end(view_));
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto begin() const
    {
        return reverse_iterator<iterator_t<const View>>(ranges::end(view_));
    }
    CANN_ASC_STL_API constexpr auto end()
    {
        return reverse_iterator<iterator_t<View>>(ranges::begin(view_));
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto end() const
    {
        return reverse_iterator<iterator_t<const View>>(ranges::begin(view_));
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto size()
    {
        return ranges::size(view_);
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ranges::size(view_);
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr View base() const& noexcept(is_nothrow_copy_constructible_v<View2>)
    {
        return view_;
    }
    CANN_ASC_STL_API constexpr View base() && noexcept(is_nothrow_move_constructible_v<View>)
    {
        return ::asc::std::move(view_);
    }

private:
    View view_{};
};
namespace views {
struct __reverse_fn {
    template <class Range>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return reverse_view<decltype(view)>(::asc::std::move(view));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __reverse_fn reverse{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_REVERSE_VIEW_H
