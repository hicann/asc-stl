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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_FILTER_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_FILTER_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/ranges_find_if.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/reference_wrapper.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/non_propagating_cache.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
template <class View, class Predicate>
class filter_view : public view_interface<filter_view<View, Predicate>> {
    using base_iterator = iterator_t<View>;
    using base_sentinel = sentinel_t<View>;
    class iterator {
    public:
        using difference_type = iter_difference_t<base_iterator>;
        using value_type = iter_value_t<base_iterator>;
        using pointer = void;
        using reference = iter_reference_t<base_iterator>;
        using iterator_category = input_iterator_tag;

        CANN_ASC_STL_API constexpr iterator(base_iterator current, base_sentinel last, Predicate* predicate)
            : current_(current), last_(last), predicate_(predicate)
        {
            satisfy();
        }
        CANN_ASC_STL_API constexpr decltype(auto) operator*() const
        {
            return *current_;
        }
        CANN_ASC_STL_API constexpr iterator& operator++()
        {
            ++current_;
            satisfy();
            return *this;
        }
        CANN_ASC_STL_API constexpr void operator++(int)
        {
            ++*this;
        }
        CANN_ASC_STL_API constexpr const base_iterator& base() const noexcept
        {
            return current_;
        }
        friend CANN_ASC_STL_API constexpr bool operator==(const iterator& left, const iterator& right)
        {
            return left.current_ == right.current_;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(const iterator& left, const iterator& right)
        {
            return !(left == right);
        }

    private:
        CANN_ASC_STL_API constexpr void satisfy()
        {
            while (current_ != last_ && !(*predicate_)(*current_))
                ++current_;
        }
        base_iterator current_;
        base_sentinel last_;
        Predicate* predicate_;
    };
    class sentinel {
    public:
        CANN_ASC_STL_API constexpr explicit sentinel(base_sentinel last) : last_(last)
        {}
        friend CANN_ASC_STL_API constexpr bool operator==(const iterator& value, const sentinel& last)
        {
            return value.base() == last.last_;
        }
        friend CANN_ASC_STL_API constexpr bool operator==(const sentinel& last, const iterator& value)
        {
            return value == last;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(const iterator& value, const sentinel& last)
        {
            return !(value == last);
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(const sentinel& last, const iterator& value)
        {
            return !(last == value);
        }

    private:
        base_sentinel last_;
    };

public:
    template <class View2 = View, class Predicate2 = Predicate>
    CANN_ASC_STL_API constexpr filter_view() noexcept(
        is_nothrow_default_constructible_v<View2> && is_nothrow_default_constructible_v<Predicate2>)
        : view_(), predicate_()
    {}
    CANN_ASC_STL_API constexpr filter_view(View view, Predicate predicate) noexcept(
        is_nothrow_move_constructible_v<View> && is_nothrow_move_constructible_v<Predicate>)
        : view_(::asc::std::move(view)), predicate_(::asc::std::move(predicate))
    {}
    CANN_ASC_STL_API constexpr iterator begin()
    {
        return {ranges::begin(view_), ranges::end(view_), &predicate_};
    }
    CANN_ASC_STL_API constexpr sentinel end()
    {
        return sentinel(ranges::end(view_));
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
class __filter_closure : public range_adaptor_closure<__filter_closure<Predicate>> {
public:
    CANN_ASC_STL_API constexpr explicit __filter_closure(Predicate value) : predicate_(::asc::std::move(value))
    {}
    template <class Range>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return filter_view<decltype(view), Predicate>(::asc::std::move(view), predicate_);
    }

private:
    Predicate predicate_;
};
struct __filter_fn {
    template <class Range, class Predicate>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range, Predicate predicate) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return filter_view<decltype(view), Predicate>(::asc::std::move(view), ::asc::std::move(predicate));
    }
    template <class Predicate>
    CANN_ASC_STL_API constexpr auto operator()(Predicate predicate) const
    {
        return __filter_closure<Predicate>(::asc::std::move(predicate));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __filter_fn filter{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_FILTER_VIEW_H
