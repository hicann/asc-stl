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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_ZIP_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_ZIP_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/ranges_min.h>
#include <asc/std/__algorithm/ranges_min_element.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/empty_view.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__tuple/apply.h>
#include <asc/std/__tuple/get.h>
#include <asc/std/__tuple/tuple.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/maybe_const.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
template <class FirstView, class SecondView>
class zip_view : public view_interface<zip_view<FirstView, SecondView>> {
    using first_iterator = iterator_t<FirstView>;
    using second_iterator = iterator_t<SecondView>;
    class iterator {
    public:
        using difference_type = __PTRDIFF_TYPE__;
        CANN_ASC_STL_API constexpr iterator(first_iterator first, second_iterator second)
            : first_(first), second_(second)
        {}
        CANN_ASC_STL_API constexpr auto operator*() const
        {
            return ::asc::std::tuple<decltype(*first_), decltype(*second_)>(*first_, *second_);
        }
        CANN_ASC_STL_API constexpr iterator& operator++()
        {
            ++first_;
            ++second_;
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator& operator+=(difference_type amount)
        {
            first_ += amount;
            second_ += amount;
            return *this;
        }
        CANN_ASC_STL_API constexpr auto operator[](difference_type amount) const
        {
            return ::asc::std::tuple<decltype(first_[amount]), decltype(second_[amount])>(
                first_[amount], second_[amount]);
        }
        friend CANN_ASC_STL_API constexpr iterator operator+(iterator value, difference_type amount)
        {
            value += amount;
            return value;
        }
        friend CANN_ASC_STL_API constexpr difference_type operator-(const iterator& left, const iterator& right)
        {
            return left.first_ - right.first_;
        }
        friend CANN_ASC_STL_API constexpr bool operator==(const iterator& left, const iterator& right)
        {
            return left.first_ == right.first_;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(const iterator& left, const iterator& right)
        {
            return !(left == right);
        }

    private:
        first_iterator first_;
        second_iterator second_;
    };

public:
    CANN_ASC_STL_API constexpr zip_view() = default;
    CANN_ASC_STL_API constexpr zip_view(FirstView first, SecondView second)
        : first_(::asc::std::move(first)), second_(::asc::std::move(second))
    {}
    CANN_ASC_STL_API constexpr iterator begin()
    {
        return {ranges::begin(first_), ranges::begin(second_)};
    }
    CANN_ASC_STL_API constexpr iterator begin() const
    {
        return {ranges::begin(first_), ranges::begin(second_)};
    }
    CANN_ASC_STL_API constexpr iterator end()
    {
        const auto count = size();
        return begin() + static_cast<__PTRDIFF_TYPE__>(count);
    }
    CANN_ASC_STL_API constexpr iterator end() const
    {
        const auto count = size();
        return begin() + static_cast<__PTRDIFF_TYPE__>(count);
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ size() noexcept(
        noexcept(ranges::size(first_)) && noexcept(ranges::size(second_)))
    {
        const auto left = ranges::size(first_);
        const auto right = ranges::size(second_);
        return left < right ? left : right;
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ size() const
        noexcept(noexcept(ranges::size(first_)) && noexcept(ranges::size(second_)))
    {
        const auto left = ranges::size(first_);
        const auto right = ranges::size(second_);
        return left < right ? left : right;
    }

private:
    FirstView first_;
    SecondView second_;
};
namespace views {
struct __zip_fn {
    template <class First, class Second>
    CANN_ASC_STL_API constexpr auto operator()(First&& first, Second&& second) const
    {
        auto left = views::all(::asc::std::forward<First>(first));
        auto right = views::all(::asc::std::forward<Second>(second));
        return zip_view<decltype(left), decltype(right)>(
            ::asc::std::move(left), ::asc::std::move(right));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __zip_fn zip{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_ZIP_VIEW_H
