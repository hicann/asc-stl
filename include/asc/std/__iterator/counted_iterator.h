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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_COUNTED_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_COUNTED_ITERATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/common_with.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/default_sentinel.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/exception_guard.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Iter>
class counted_iterator {
public:
    using iterator_type = Iter;
    using difference_type = iter_difference_t<Iter>;
    using value_type = iter_value_t<Iter>;
    using pointer = add_pointer_t<iter_reference_t<Iter>>;
    using reference = iter_reference_t<Iter>;
    using iterator_category = typename iterator_traits<Iter>::iterator_category;

    CANN_ASC_STL_API constexpr counted_iterator() = default;
    CANN_ASC_STL_API constexpr counted_iterator(Iter value, difference_type count) noexcept(
        is_nothrow_move_constructible_v<Iter>)
        : current_(::asc::std::move(value)), count_(count)
    {}
    template <class I2>
    CANN_ASC_STL_API constexpr counted_iterator(const counted_iterator<I2>& other) noexcept(
        is_nothrow_constructible_v<Iter, const I2&>)
        : current_(other.base()), count_(other.count())
    {}
    template <class I2>
    CANN_ASC_STL_API constexpr counted_iterator& operator=(const counted_iterator<I2>& other) noexcept(
        is_nothrow_assignable_v<Iter&, const I2&>)
    {
        current_ = other.base();
        count_ = other.count();
        return *this;
    }
    CANN_ASC_STL_API constexpr const Iter& base() const& noexcept
    {
        return current_;
    }
    CANN_ASC_STL_API constexpr Iter base() &&
    {
        return ::asc::std::move(current_);  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API constexpr difference_type count() const noexcept
    {
        return count_;
    }
    CANN_ASC_STL_API constexpr decltype(auto) operator*()
    {
        return *current_;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr decltype(auto) operator*() const
    {
        return *current_;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr auto operator->() const noexcept
    {
        return current_;
    }
    CANN_ASC_STL_API constexpr counted_iterator& operator++()
    {
        ++current_;
        --count_;
        return *this;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr counted_iterator operator++(int)
    {
        counted_iterator old(*this);
        ++*this;
        return old;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr counted_iterator& operator--()
    {
        --current_;
        ++count_;
        return *this;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr counted_iterator operator--(int)
    {
        counted_iterator old(*this);
        --*this;
        return old;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr counted_iterator& operator+=(iter_difference_t<I2> count)
    {
        current_ += count;
        count_ -= count;
        return *this;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr counted_iterator& operator-=(iter_difference_t<I2> count)
    {
        return *this += -count;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr counted_iterator operator+(iter_difference_t<I2> count) const
    {
        counted_iterator result(*this);
        return result += count;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr counted_iterator operator-(iter_difference_t<I2> count) const
    {
        counted_iterator result(*this);
        return result -= count;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](iter_difference_t<I2> count) const
    {
        return current_[count];
    }

private:
    Iter current_{};
    difference_type count_{};
};

template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator==(const counted_iterator<I1>& left, const counted_iterator<I2>& right)
{
    return left.count() == right.count();
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator!=(const counted_iterator<I1>& left, const counted_iterator<I2>& right)
{
    return !(left == right);
}
template <class Iter>
CANN_ASC_STL_API constexpr bool operator==(const counted_iterator<Iter>& value, default_sentinel_t) noexcept
{
    return value.count() == 0;
}
template <class Iter>
CANN_ASC_STL_API constexpr bool operator==(default_sentinel_t, const counted_iterator<Iter>& value) noexcept
{
    return value.count() == 0;
}
template <class Iter>
CANN_ASC_STL_API constexpr bool operator!=(const counted_iterator<Iter>& value, default_sentinel_t sentinel) noexcept
{
    return !(value == sentinel);
}
template <class Iter>
CANN_ASC_STL_API constexpr bool operator!=(default_sentinel_t sentinel, const counted_iterator<Iter>& value) noexcept
{
    return !(sentinel == value);
}
template <class Iter>
CANN_ASC_STL_API constexpr iter_difference_t<Iter> operator-(
    default_sentinel_t, const counted_iterator<Iter>& value) noexcept
{
    return -value.count();
}
template <class Iter>
CANN_ASC_STL_API constexpr iter_difference_t<Iter> operator-(
    const counted_iterator<Iter>& value, default_sentinel_t) noexcept
{
    return value.count();
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_COUNTED_ITERATOR_H
