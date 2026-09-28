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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_TRANSFORM_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_TRANSFORM_VIEW_H

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
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/maybe_const.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
template <class View, class Function>
class transform_view : public view_interface<transform_view<View, Function>> {
    using base_iterator = iterator_t<View>;
    using base_sentinel = sentinel_t<View>;
    class iterator {
    public:
        using difference_type = iter_difference_t<base_iterator>;
        using value_type =
            remove_cvref_t<decltype(::asc::std::declval<const Function&>()(*::asc::std::declval<base_iterator&>()))>;
        using pointer = void;
        using reference = decltype(::asc::std::declval<const Function&>()(*::asc::std::declval<base_iterator&>()));
        using iterator_category = input_iterator_tag;

        CANN_ASC_STL_API constexpr iterator(base_iterator current, const Function* function)
            : current_(current), function_(function)
        {}
        CANN_ASC_STL_API constexpr decltype(auto) operator*() const
        {
            return (*function_)(*current_);
        }
        CANN_ASC_STL_API constexpr iterator& operator++()
        {
            ++current_;
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
        base_iterator current_;
        const Function* function_;
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
    CANN_ASC_STL_API constexpr transform_view() = default;
    CANN_ASC_STL_API constexpr transform_view(View view, Function function)
        : view_(::asc::std::move(view)), function_(::asc::std::move(function))
    {}
    CANN_ASC_STL_API constexpr iterator begin()
    {
        return {ranges::begin(view_), &function_};
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr iterator begin() const
    {
        return {ranges::begin(view_), &function_};
    }
    CANN_ASC_STL_API constexpr sentinel end()
    {
        return sentinel(ranges::end(view_));
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr sentinel end() const
    {
        return sentinel(ranges::end(view_));
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
    Function function_{};
};
namespace views {
template <class Function>
class __transform_closure : public range_adaptor_closure<__transform_closure<Function>> {
public:
    CANN_ASC_STL_API constexpr explicit __transform_closure(Function value) : function_(::asc::std::move(value))
    {}
    template <class Range>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return transform_view<decltype(view), Function>(::asc::std::move(view), function_);
    }

private:
    Function function_;
};
struct __transform_fn {
    template <class Range, class Function>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range, Function function) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return transform_view<decltype(view), Function>(::asc::std::move(view), ::asc::std::move(function));
    }
    template <class Function>
    CANN_ASC_STL_API constexpr auto operator()(Function function) const
    {
        return __transform_closure<Function>(::asc::std::move(function));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __transform_fn transform{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_TRANSFORM_VIEW_H
