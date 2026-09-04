/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_BOUNDED_ITER_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_BOUNDED_ITER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Iter, class = void>
class __bounded_iter {
public:
    using value_type = typename iterator_traits<Iter>::value_type;
    using difference_type = typename iterator_traits<Iter>::difference_type;
    using pointer = typename iterator_traits<Iter>::pointer;
    using reference = typename iterator_traits<Iter>::reference;
    using iterator_category = typename iterator_traits<Iter>::iterator_category;
    using iterator_concept = contiguous_iterator_tag;

    CANN_ASC_STL_API constexpr __bounded_iter() : current_(), begin_(), end_()
    {}

    template <class Other, class OtherEnable, enable_if_t<is_convertible_v<Other, Iter>, int> = 0>
    CANN_ASC_STL_API constexpr __bounded_iter(const __bounded_iter<Other, OtherEnable>& other) noexcept
        : current_(other.current_), begin_(other.begin_), end_(other.end_)
    {}

    CANN_ASC_STL_API constexpr reference operator*() const noexcept
    {
        return *current_;
    }
    CANN_ASC_STL_API constexpr pointer operator->() const noexcept
    {
        return ::asc::std::to_address(current_);
    }
    CANN_ASC_STL_API constexpr reference operator[](difference_type n) const noexcept
    {
        return current_[n];
    }
    CANN_ASC_STL_API constexpr __bounded_iter& operator++() noexcept
    {
        ++current_;
        return *this;
    }
    CANN_ASC_STL_API constexpr __bounded_iter operator++(int) noexcept
    {
        auto result = *this;
        ++*this;
        return result;
    }
    CANN_ASC_STL_API constexpr __bounded_iter& operator--() noexcept
    {
        --current_;
        return *this;
    }
    CANN_ASC_STL_API constexpr __bounded_iter operator--(int) noexcept
    {
        auto result = *this;
        --*this;
        return result;
    }
    CANN_ASC_STL_API constexpr __bounded_iter& operator+=(difference_type n) noexcept
    {
        current_ += n;
        return *this;
    }
    CANN_ASC_STL_API constexpr __bounded_iter& operator-=(difference_type n) noexcept
    {
        current_ -= n;
        return *this;
    }

    friend CANN_ASC_STL_API constexpr __bounded_iter operator+(__bounded_iter value, difference_type n) noexcept
    {
        return value += n;
    }
    friend CANN_ASC_STL_API constexpr __bounded_iter operator+(difference_type n, __bounded_iter value) noexcept
    {
        return value += n;
    }
    friend CANN_ASC_STL_API constexpr __bounded_iter operator-(__bounded_iter value, difference_type n) noexcept
    {
        return value -= n;
    }
    friend CANN_ASC_STL_API constexpr difference_type operator-(
        const __bounded_iter& left, const __bounded_iter& right) noexcept
    {
        return left.current_ - right.current_;
    }
    friend CANN_ASC_STL_API constexpr bool operator==(const __bounded_iter& left, const __bounded_iter& right) noexcept
    {
        return left.current_ == right.current_;
    }
    friend CANN_ASC_STL_API constexpr bool operator!=(const __bounded_iter& left, const __bounded_iter& right) noexcept
    {
        return !(left == right);
    }
    friend CANN_ASC_STL_API constexpr bool operator<(const __bounded_iter& left, const __bounded_iter& right) noexcept
    {
        return left.current_ < right.current_;
    }
    friend CANN_ASC_STL_API constexpr bool operator>(const __bounded_iter& left, const __bounded_iter& right) noexcept
    {
        return right < left;
    }
    friend CANN_ASC_STL_API constexpr bool operator<=(const __bounded_iter& left, const __bounded_iter& right) noexcept
    {
        return !(right < left);
    }
    friend CANN_ASC_STL_API constexpr bool operator>=(const __bounded_iter& left, const __bounded_iter& right) noexcept
    {
        return !(left < right);
    }

private:
    CANN_ASC_STL_API constexpr __bounded_iter(Iter current, Iter begin, Iter end)
        : current_(::asc::std::move(current)), begin_(::asc::std::move(begin)), end_(::asc::std::move(end))
    {}

    template <class, class>
    friend class __bounded_iter;
    template <class I>
    friend CANN_ASC_STL_API constexpr __bounded_iter<I> __make_bounded_iter(I, I, I);
    template <class, class>
    friend struct pointer_traits;
    Iter current_;
    Iter begin_;
    Iter end_;
};

template <class Iter>
CANN_ASC_STL_API constexpr __bounded_iter<Iter> __make_bounded_iter(Iter current, Iter begin, Iter end)
{
    return __bounded_iter<Iter>(::asc::std::move(current),
        ::asc::std::move(begin),  // NOLINT(build/include_what_you_use)
        ::asc::std::move(end));   // NOLINT(build/include_what_you_use)
}

template <class Iter, class Enable>
struct pointer_traits<__bounded_iter<Iter, Enable>> {
    using pointer = __bounded_iter<Iter, Enable>;
    using element_type = typename pointer_traits<Iter>::element_type;
    using difference_type = typename pointer_traits<Iter>::difference_type;
    CANN_ASC_STL_API static constexpr element_type* to_address(pointer value) noexcept
    {
        return ::asc::std::to_address(value.current_);
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_BOUNDED_ITER_H
