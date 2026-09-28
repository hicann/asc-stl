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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_DROP_WHILE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_DROP_WHILE_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/ranges_find_if_not.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__functional/reference_wrapper.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/non_propagating_cache.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
template <class View, class Predicate>
class drop_while_view : public view_interface<drop_while_view<View, Predicate>> {
public:
    CANN_ASC_STL_API constexpr drop_while_view() = default;
    CANN_ASC_STL_API constexpr drop_while_view(View view, Predicate predicate)
        : view_(::asc::std::move(view)), predicate_(::asc::std::move(predicate))
    {}
    CANN_ASC_STL_API constexpr auto begin()
    {
        auto value = ranges::begin(view_);
        const auto last = ranges::end(view_);
        while (value != last && predicate_(*value))
            ++value;
        return value;
    }
    CANN_ASC_STL_API constexpr auto end()
    {
        return ranges::end(view_);
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
    CANN_ASC_STL_API constexpr const Predicate& pred() const
    {
        return predicate_;
    }

private:
    View view_{};
    Predicate predicate_{};
};
namespace views {
template <class Predicate>
class __drop_while_closure : public range_adaptor_closure<__drop_while_closure<Predicate>> {
public:
    CANN_ASC_STL_API constexpr explicit __drop_while_closure(Predicate value) : predicate_(::asc::std::move(value))
    {}
    template <class Range>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return drop_while_view<decltype(view), Predicate>(::asc::std::move(view), predicate_);
    }

private:
    Predicate predicate_;
};
struct __drop_while_fn {
    template <class Range, class Predicate>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range, Predicate predicate) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return drop_while_view<decltype(view), Predicate>(::asc::std::move(view), ::asc::std::move(predicate));
    }
    template <class Predicate>
    CANN_ASC_STL_API constexpr auto operator()(Predicate predicate) const
    {
        return __drop_while_closure<Predicate>(::asc::std::move(predicate));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __drop_while_fn drop_while{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_DROP_WHILE_VIEW_H
