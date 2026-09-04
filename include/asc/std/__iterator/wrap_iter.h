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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_WRAP_ITER_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_WRAP_ITER_H

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
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Iter>
class __wrap_iter {
public:
    using iterator_type = Iter;
    using value_type = typename iterator_traits<Iter>::value_type;
    using difference_type = typename iterator_traits<Iter>::difference_type;
    using pointer = typename iterator_traits<Iter>::pointer;
    using reference = typename iterator_traits<Iter>::reference;
    using iterator_category = typename iterator_traits<Iter>::iterator_category;
    using iterator_concept = contiguous_iterator_tag;

    CANN_ASC_STL_API constexpr __wrap_iter() noexcept : iter_()
    {}
    template <class Other, enable_if_t<is_convertible_v<Other, Iter>, int> = 0>
    CANN_ASC_STL_API constexpr __wrap_iter(const __wrap_iter<Other>& other) noexcept : iter_(other.base())
    {}
    CANN_ASC_STL_API constexpr reference operator*() const noexcept
    {
        return *iter_;
    }
    CANN_ASC_STL_API constexpr pointer operator->() const noexcept
    {
        return ::asc::std::to_address(iter_);
    }
    CANN_ASC_STL_API constexpr reference operator[](difference_type n) const noexcept
    {
        return iter_[n];
    }
    CANN_ASC_STL_API constexpr __wrap_iter& operator++() noexcept
    {
        ++iter_;
        return *this;
    }
    CANN_ASC_STL_API constexpr __wrap_iter operator++(int) noexcept
    {
        auto result = *this;
        ++*this;
        return result;
    }
    CANN_ASC_STL_API constexpr __wrap_iter& operator--() noexcept
    {
        --iter_;
        return *this;
    }
    CANN_ASC_STL_API constexpr __wrap_iter operator--(int) noexcept
    {
        auto result = *this;
        --*this;
        return result;
    }
    CANN_ASC_STL_API constexpr __wrap_iter& operator+=(difference_type n) noexcept
    {
        iter_ += n;
        return *this;
    }
    CANN_ASC_STL_API constexpr __wrap_iter& operator-=(difference_type n) noexcept
    {
        iter_ -= n;
        return *this;
    }
    CANN_ASC_STL_API constexpr __wrap_iter operator+(difference_type n) const noexcept
    {
        auto result = *this;
        return result += n;
    }
    CANN_ASC_STL_API constexpr __wrap_iter operator-(difference_type n) const noexcept
    {
        auto result = *this;
        return result -= n;
    }
    CANN_ASC_STL_API constexpr iterator_type base() const noexcept
    {
        return iter_;
    }

private:
    CANN_ASC_STL_API constexpr explicit __wrap_iter(Iter value) noexcept : iter_(value)
    {}

    template <class, class>
    friend class __bounded_iter;
    template <class, class>
    friend struct pointer_traits;
    Iter iter_;
};

template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator==(const __wrap_iter<I1>& x, const __wrap_iter<I2>& y) noexcept
{
    return x.base() == y.base();
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator!=(const __wrap_iter<I1>& x, const __wrap_iter<I2>& y) noexcept
{
    return !(x == y);
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator<(const __wrap_iter<I1>& x, const __wrap_iter<I2>& y) noexcept
{
    return x.base() < y.base();
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator>(const __wrap_iter<I1>& x, const __wrap_iter<I2>& y) noexcept
{
    return y < x;
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator<=(const __wrap_iter<I1>& x, const __wrap_iter<I2>& y) noexcept
{
    return !(y < x);
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr bool operator>=(const __wrap_iter<I1>& x, const __wrap_iter<I2>& y) noexcept
{
    return !(x < y);
}
template <class I1, class I2>
CANN_ASC_STL_API constexpr auto operator-(
    const __wrap_iter<I1>& x, const __wrap_iter<I2>& y) noexcept -> decltype(x.base() - y.base())
{
    return x.base() - y.base();
}
template <class Iter>
CANN_ASC_STL_API constexpr __wrap_iter<Iter> operator+(
    typename __wrap_iter<Iter>::difference_type n, __wrap_iter<Iter> value) noexcept
{
    return value + n;
}

template <class Iter>
struct pointer_traits<__wrap_iter<Iter>> {
    using pointer = __wrap_iter<Iter>;
    using element_type = typename pointer_traits<Iter>::element_type;
    using difference_type = typename pointer_traits<Iter>::difference_type;
    CANN_ASC_STL_API static constexpr element_type* to_address(pointer value) noexcept
    {
        return ::asc::std::to_address(value.base());
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_WRAP_ITER_H
