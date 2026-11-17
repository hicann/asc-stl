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

#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__tuple/tuple.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

// Registered contract: zip_view zips exactly two random-access, sized views
// (views::zip wraps its operands with views::all first). begin()/end()/size()
// pin that contract with static assertions at instantiation time, and the
// const overloads additionally require const iterability whose iterator
// types are identical to the non-const ones.
namespace asc::std::ranges {
namespace __zip_detail {
// Underlying iterator category, read through iterator_traits. Iterators whose
// traits fall back to the empty primary template conservatively degrade to
// input_iterator_tag.
template <class Iter, class = void>
struct __iterator_category_of {
    using type = input_iterator_tag;
};
template <class Iter>
struct __iterator_category_of<Iter, void_t<typename iterator_traits<Iter>::iterator_category>> {
    using type = typename iterator_traits<Iter>::iterator_category;
};
template <class Iter>
using __iterator_category_of_t = typename __iterator_category_of<Iter>::type;

// A transform view returning values retains random-access traversal even
// though its legacy iterator_category is input_iterator_tag.
template <class Iter, class = void>
struct __iterator_concept_of : __iterator_category_of<Iter> {};
template <class Iter>
struct __iterator_concept_of<Iter, void_t<_ITER_CONCEPT<Iter>>> {
    using type = _ITER_CONCEPT<Iter>;
};

// The weaker of two tag types: Left converts to Right exactly when Left is the
// more derived (stronger) tag, so the weaker one is Right in that case.
template <class Left, class Right>
using __weaker_category = conditional_t<is_convertible_v<Left, Right>, Right, Left>;

// Zip category: the weakest of the two underlying categories, weakened further
// to random_access_iterator_tag at most, since zipping never preserves
// contiguity.
template <class First, class Second>
using __zip_category =
    __weaker_category<__weaker_category<__iterator_category_of_t<First>, __iterator_category_of_t<Second>>,
        random_access_iterator_tag>;

template <class First, class Second>
using __zip_concept = __weaker_category<
    __weaker_category<typename __iterator_concept_of<First>::type, typename __iterator_concept_of<Second>::type>,
    random_access_iterator_tag>;

// Sized-range probe backing the registered contract checks in the members.
template <class View, class = void>
struct __is_sized_range {
    static constexpr bool value = false;
};
template <class View>
struct __is_sized_range<View, void_t<decltype(ranges::size(::asc::std::declval<View&>()))>> {
    static constexpr bool value = true;
};
}  // namespace __zip_detail

template <class FirstView, class SecondView>
class zip_view : public view_interface<zip_view<FirstView, SecondView>> {
    using first_iterator = iterator_t<FirstView>;
    using second_iterator = iterator_t<SecondView>;
    // The iterator type is deliberately private: the registered zip_view
    // surface is the constructors plus begin/end/size, and callers name the
    // iterator only through auto/decltype. Do not widen this exposure.
    class iterator {
    public:
        using difference_type = __PTRDIFF_TYPE__;
        using reference = ::asc::std::tuple<decltype(*::asc::std::declval<const first_iterator&>()),
            decltype(*::asc::std::declval<const second_iterator&>())>;
        using value_type = ::asc::std::tuple<remove_cvref_t<decltype(*::asc::std::declval<const first_iterator&>())>,
            remove_cvref_t<decltype(*::asc::std::declval<const second_iterator&>())>>;
        using pointer = void;
        using iterator_concept = __zip_detail::__zip_concept<first_iterator, second_iterator>;
        using iterator_category = __zip_detail::__zip_category<first_iterator, second_iterator>;
        CANN_ASC_STL_API constexpr iterator() = default;
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
        CANN_ASC_STL_API constexpr iterator operator++(int)
        {
            auto copy = *this;
            ++*this;
            return copy;
        }
        CANN_ASC_STL_API constexpr iterator& operator--()
        {
            --first_;
            --second_;
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator operator--(int)
        {
            auto copy = *this;
            --*this;
            return copy;
        }
        CANN_ASC_STL_API constexpr iterator& operator+=(difference_type amount)
        {
            first_ += amount;
            second_ += amount;
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator& operator-=(difference_type amount)
        {
            first_ -= amount;
            second_ -= amount;
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
        friend CANN_ASC_STL_API constexpr iterator operator+(difference_type amount, iterator value)
        {
            value += amount;
            return value;
        }
        friend CANN_ASC_STL_API constexpr iterator operator-(iterator value, difference_type amount)
        {
            value -= amount;
            return value;
        }
        friend CANN_ASC_STL_API constexpr difference_type operator-(const iterator& left, const iterator& right)
        {
            return left.first_ - right.first_;
        }
        // Lockstep invariant: both lanes are advanced by identical amounts
        // and every iterator of this view is produced by begin()/end()
        // (end() == begin() + min(sizes)), so the lanes never diverge and
        // comparing the first lane is sufficient. Iterators originating from
        // different zip_view objects are not comparable by contract.
        friend CANN_ASC_STL_API constexpr bool operator==(const iterator& left, const iterator& right)
        {
            return left.first_ == right.first_;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(const iterator& left, const iterator& right)
        {
            return !(left == right);
        }
        friend CANN_ASC_STL_API constexpr bool operator<(const iterator& left, const iterator& right)
        {
            return left.first_ < right.first_;
        }
        friend CANN_ASC_STL_API constexpr bool operator<=(const iterator& left, const iterator& right)
        {
            return !(right < left);
        }
        friend CANN_ASC_STL_API constexpr bool operator>(const iterator& left, const iterator& right)
        {
            return right < left;
        }
        friend CANN_ASC_STL_API constexpr bool operator>=(const iterator& left, const iterator& right)
        {
            return !(left < right);
        }

    private:
        first_iterator first_{};
        second_iterator second_{};
    };

public:
    CANN_ASC_STL_API constexpr zip_view() = default;
    CANN_ASC_STL_API constexpr zip_view(FirstView first, SecondView second)
        : first_(::asc::std::move(first)), second_(::asc::std::move(second))
    {}
    CANN_ASC_STL_API constexpr iterator begin()
    {
        static_assert(is_convertible<__zip_detail::__zip_concept<first_iterator, second_iterator>,
                          random_access_iterator_tag>::value,
            "asc::std::ranges::zip_view requires random-access underlying iterators "
            "(registered contract: two-way random-access zip)");
        return {ranges::begin(first_), ranges::begin(second_)};
    }
    CANN_ASC_STL_API constexpr iterator begin() const
    {
        static_assert(is_convertible<__zip_detail::__zip_concept<first_iterator, second_iterator>,
                          random_access_iterator_tag>::value,
            "asc::std::ranges::zip_view requires random-access underlying iterators "
            "(registered contract: two-way random-access zip)");
        static_assert(
            is_same<decltype(ranges::begin(::asc::std::declval<const FirstView&>())), first_iterator>::value &&
                is_same<decltype(ranges::begin(::asc::std::declval<const SecondView&>())), second_iterator>::value,
            "asc::std::ranges::zip_view const iteration requires const-iterable views whose "
            "iterator types are identical to the non-const ones");
        return {ranges::begin(first_), ranges::begin(second_)};
    }
    CANN_ASC_STL_API constexpr iterator end()
    {
        static_assert(
            __zip_detail::__is_sized_range<FirstView>::value && __zip_detail::__is_sized_range<SecondView>::value,
            "asc::std::ranges::zip_view requires sized underlying views (registered contract)");
        return begin() + static_cast<__PTRDIFF_TYPE__>(size());
    }
    CANN_ASC_STL_API constexpr iterator end() const
    {
        static_assert(
            __zip_detail::__is_sized_range<FirstView>::value && __zip_detail::__is_sized_range<SecondView>::value,
            "asc::std::ranges::zip_view requires sized underlying views (registered contract)");
        return begin() + static_cast<__PTRDIFF_TYPE__>(size());
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ size() noexcept(
        noexcept(ranges::size(::asc::std::declval<FirstView&>())) &&
        noexcept(ranges::size(::asc::std::declval<SecondView&>())))
    {
        const auto left = ranges::size(first_);
        const auto right = ranges::size(second_);
        return left < right ? left : right;
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ size() const
        noexcept(noexcept(ranges::size(::asc::std::declval<const FirstView&>())) &&
            noexcept(ranges::size(::asc::std::declval<const SecondView&>())))
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
