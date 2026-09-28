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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_REVERSE_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_REVERSE_ITERATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__fwd/iterator.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__iterator/prev.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_convertible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Iter>
class reverse_iterator {
public:
    using iterator_type = Iter;
    using difference_type = iter_difference_t<Iter>;
    using value_type = iter_value_t<Iter>;
    using pointer = typename iterator_traits<Iter>::pointer;
    using reference = iter_reference_t<Iter>;
    using iterator_category = typename iterator_traits<Iter>::iterator_category;
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    using iterator_concept =
        conditional_t<random_access_iterator<Iter>, random_access_iterator_tag, bidirectional_iterator_tag>;
#else
    using iterator_concept =
        conditional_t<is_convertible_v<typename iterator_traits<Iter>::iterator_category, random_access_iterator_tag>,
            random_access_iterator_tag, bidirectional_iterator_tag>;
#endif

    CANN_ASC_STL_API constexpr reverse_iterator() noexcept(is_nothrow_default_constructible_v<Iter>) = default;
    CANN_ASC_STL_API explicit constexpr reverse_iterator(Iter value) noexcept(is_nothrow_copy_constructible_v<Iter>)
        : current(value)
    {}
    template <class U, enable_if_t<is_convertible_v<const U&, Iter>, int> = 0>
    CANN_ASC_STL_API constexpr reverse_iterator(const reverse_iterator<U>& other) noexcept(
        is_nothrow_convertible_v<const U&, Iter>)
        : current(other.base())
    {}
    template <class U, enable_if_t<is_assignable_v<Iter&, const U&>, int> = 0>
    CANN_ASC_STL_API constexpr reverse_iterator& operator=(const reverse_iterator<U>& other) noexcept(
        is_nothrow_assignable_v<Iter&, const U&>)
    {
        current = other.base();
        return *this;
    }
    CANN_ASC_STL_API constexpr Iter base() const noexcept(is_nothrow_copy_constructible_v<Iter>)
    {
        return current;
    }
    CANN_ASC_STL_API constexpr reference operator*() const
    {
        Iter value = current;
        return *--value;
    }
    CANN_ASC_STL_API constexpr pointer operator->() const
    {
        return ::asc::std::addressof(operator*());
    }
    CANN_ASC_STL_API constexpr reference operator[](difference_type count) const
    {
        return current[-count - 1];
    }
    CANN_ASC_STL_API constexpr reverse_iterator& operator++()
    {
        --current;
        return *this;
    }
    CANN_ASC_STL_API constexpr reverse_iterator operator++(int)
    {
        reverse_iterator old(*this);
        --current;
        return old;
    }
    CANN_ASC_STL_API constexpr reverse_iterator& operator--()
    {
        ++current;
        return *this;
    }
    CANN_ASC_STL_API constexpr reverse_iterator operator--(int)
    {
        reverse_iterator old(*this);
        ++current;
        return old;
    }
    CANN_ASC_STL_API constexpr reverse_iterator operator+(difference_type count) const
    {
        return reverse_iterator(current - count);
    }
    CANN_ASC_STL_API constexpr reverse_iterator operator-(difference_type count) const
    {
        return reverse_iterator(current + count);
    }
    CANN_ASC_STL_API constexpr reverse_iterator& operator+=(difference_type count)
    {
        current -= count;
        return *this;
    }
    CANN_ASC_STL_API constexpr reverse_iterator& operator-=(difference_type count)
    {
        current += count;
        return *this;
    }

private:
    Iter current{};
};

template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator==(const reverse_iterator<I1>& left, const reverse_iterator<I2>& right)
{
    return left.base() == right.base();
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator!=(const reverse_iterator<I1>& left, const reverse_iterator<I2>& right)
{
    return !(left == right);
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator<(const reverse_iterator<I1>& left, const reverse_iterator<I2>& right)
{
    return right.base() < left.base();
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator>(const reverse_iterator<I1>& left, const reverse_iterator<I2>& right)
{
    return right < left;
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator<=(const reverse_iterator<I1>& left, const reverse_iterator<I2>& right)
{
    return !(right < left);
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator>=(const reverse_iterator<I1>& left, const reverse_iterator<I2>& right)
{
    return !(left < right);
}
template <class Iter>
CANN_ASC_STL_API constexpr reverse_iterator<Iter> operator+(
    typename reverse_iterator<Iter>::difference_type count, const reverse_iterator<Iter>& value)
{
    return value + count;
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr auto operator-(
    const reverse_iterator<I1>& left, const reverse_iterator<I2>& right) -> decltype(right.base() - left.base())
{
    return right.base() - left.base();
}
template <class Iter>
CANN_ASC_STL_API constexpr reverse_iterator<Iter> make_reverse_iterator(Iter value) noexcept(
    is_nothrow_copy_constructible_v<Iter>)
{
    return reverse_iterator<Iter>(value);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_REVERSE_ITERATOR_H
