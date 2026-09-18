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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_MOVE_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_MOVE_ITERATOR_H

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
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/move_sentinel.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_convertible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Iter>
class move_iterator {
public:
    using iterator_type = Iter;
    using iterator_category = typename iterator_traits<Iter>::iterator_category;
    using iterator_concept = iterator_category;
    using value_type = iter_value_t<Iter>;
    using difference_type = iter_difference_t<Iter>;
    using pointer = Iter;
    using reference = iter_rvalue_reference_t<Iter>;

    template <class It = Iter>
    CANN_ASC_STL_API constexpr move_iterator() noexcept(is_nothrow_default_constructible_v<It>) : current_()
    {}
    CANN_ASC_STL_API constexpr explicit move_iterator(Iter iterator) noexcept(is_nothrow_move_constructible_v<Iter>)
        : current_(::asc::std::move(iterator))
    {}
    template <class Other>
    CANN_ASC_STL_API constexpr move_iterator(const move_iterator<Other>& other) noexcept(
        is_nothrow_convertible_v<const Other&, Iter>)
        : current_(other.base())
    {}
    template <class Other>
    CANN_ASC_STL_API constexpr move_iterator& operator=(const move_iterator<Other>& other) noexcept(
        noexcept(current_ = other.base()))
    {
        current_ = other.base();
        return *this;
    }

    CANN_ASC_STL_API constexpr const Iter& base() const& noexcept
    {
        return current_;
    }
    CANN_ASC_STL_API constexpr Iter base() &&
    {
        return ::asc::std::move(current_);
    }
    CANN_ASC_STL_API constexpr reference operator*() const
    {
        return ::asc::std::iter_move(current_);
    }
    CANN_ASC_STL_API constexpr pointer operator->() const
    {
        return current_;
    }
    CANN_ASC_STL_API constexpr reference operator[](difference_type count) const
    {
        return ::asc::std::iter_move(current_ + count);
    }
    CANN_ASC_STL_API constexpr move_iterator& operator++()
    {
        ++current_;
        return *this;
    }
    CANN_ASC_STL_API constexpr move_iterator operator++(int)
    {
        move_iterator result(*this);
        ++current_;
        return result;
    }
    CANN_ASC_STL_API constexpr move_iterator& operator--()
    {
        --current_;
        return *this;
    }
    CANN_ASC_STL_API constexpr move_iterator operator--(int)
    {
        move_iterator result(*this);
        --current_;
        return result;
    }
    CANN_ASC_STL_API constexpr move_iterator operator+(difference_type count) const
    {
        return move_iterator(current_ + count);
    }
    CANN_ASC_STL_API constexpr move_iterator operator-(difference_type count) const
    {
        return move_iterator(current_ - count);
    }
    CANN_ASC_STL_API constexpr move_iterator& operator+=(difference_type count)
    {
        current_ += count;
        return *this;
    }
    CANN_ASC_STL_API constexpr move_iterator& operator-=(difference_type count)
    {
        current_ -= count;
        return *this;
    }

private:
    template <class>
    friend class move_iterator;
    Iter current_{};
};

template <class Iter>
CANN_ASC_STL_API constexpr move_iterator<Iter> operator+(
    typename move_iterator<Iter>::difference_type count, const move_iterator<Iter>& iterator)
{
    return iterator + count;
}

template <class Left, class Right>
CANN_ASC_STL_API constexpr auto operator-(
    const move_iterator<Left>& left, const move_iterator<Right>& right) -> decltype(left.base() - right.base())
{
    return left.base() - right.base();
}

#define CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(op)                                                               \
    template <class Left, class Right>                                                                              \
    CANN_ASC_STL_API constexpr auto operator op(const move_iterator<Left>& left, const move_iterator<Right>& right) \
        ->decltype(static_cast<bool>(left.base() op right.base()))                                                  \
    {                                                                                                               \
        return left.base() op right.base();                                                                         \
    }

CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(==)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(!=)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(<)  // NOLINT(whitespace/operators)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(>)  // NOLINT(whitespace/operators)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(<=)
CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE(>=)

#undef CANN_ASC_STL_DETAIL_MOVE_ITERATOR_COMPARE

template <class Iter, class Sentinel>
CANN_ASC_STL_API constexpr bool operator==(const move_iterator<Iter>& iterator, const move_sentinel<Sentinel>& sentinel)
{
    return iterator.base() == sentinel.base();
}
template <class Iter, class Sentinel>
CANN_ASC_STL_API constexpr bool operator!=(const move_iterator<Iter>& iterator, const move_sentinel<Sentinel>& sentinel)
{
    return !(iterator == sentinel);
}

template <class Iter>
CANN_ASC_STL_API constexpr move_iterator<Iter> make_move_iterator(Iter iterator) noexcept(
    is_nothrow_move_constructible_v<Iter>)
{
    return move_iterator<Iter>(::asc::std::move(iterator));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_MOVE_ITERATOR_H
