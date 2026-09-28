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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_TAKE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_TAKE_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/min.h>
#include <asc/std/__algorithm/ranges_min.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__fwd/span.h>
#include <asc/std/__fwd/string_view.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/counted_iterator.h>
#include <asc/std/__iterator/default_sentinel.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/empty_view.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/iota_view.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/repeat_view.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/subrange.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/maybe_const.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/forward_like.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
template <class View>
class take_view : public view_interface<take_view<View>> {
public:
    CANN_ASC_STL_API constexpr take_view() = default;
    CANN_ASC_STL_API constexpr take_view(View view, range_difference_t<View> count)
        : view_(::asc::std::move(view)), count_(count)
    {}
    CANN_ASC_STL_API constexpr auto begin()
    {
        return ranges::begin(view_);
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto begin() const
    {
        return ranges::begin(view_);
    }
    CANN_ASC_STL_API constexpr auto end()
    {
        auto value = begin();
        auto last = ranges::end(view_);
        for (auto n = count_; n > 0 && value != last; --n)
            ++value;
        return value;
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto end() const
    {
        auto value = begin();
        auto last = ranges::end(view_);
        for (auto n = count_; n > 0 && value != last; --n)
            ++value;
        return value;
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto size()
    {
        const auto value = ranges::size(view_);
        return value < static_cast<decltype(value)>(count_) ? value : count_;
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto size() const
    {
        const auto value = ranges::size(view_);
        return value < static_cast<decltype(value)>(count_) ? value : count_;
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr View base() const&
    {
        return view_;
    }
    CANN_ASC_STL_API constexpr View base() &&
    {
        return ::asc::std::move(view_);
    }

private:
    View view_{};
    range_difference_t<View> count_{};
};
namespace views {
template <class Difference>
class __take_closure : public range_adaptor_closure<__take_closure<Difference>> {
public:
    CANN_ASC_STL_API constexpr explicit __take_closure(Difference count) : count_(count)
    {}
    template <class Range>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return take_view<decltype(view)>(::asc::std::move(view), count_);
    }

private:
    Difference count_;
};
struct __take_fn {
    template <class Range, class Difference>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range, Difference count) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return take_view<decltype(view)>(::asc::std::move(view), count);  // NOLINT(build/include_what_you_use)
    }
    template <class Difference>
    CANN_ASC_STL_API constexpr __take_closure<Difference> operator()(Difference count) const
    {
        return __take_closure<Difference>(count);
    }
};
inline constexpr __take_fn take{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_TAKE_VIEW_H
