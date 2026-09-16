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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_COMMON_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_COMMON_ITERATOR_H

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
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__fwd/common_iterator.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__iterator/variant_like.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator Iter, sentinel_for<Iter> Sent>
    requires(!same_as<Iter, Sent> && copyable<Iter>)
#else
template <class Iter, class Sent, class Enable>
#endif
class common_iterator {
public:
    CANN_ASC_STL_API constexpr common_iterator() noexcept(is_nothrow_default_constructible_v<Iter>) = default;
    CANN_ASC_STL_API constexpr common_iterator(Iter value) noexcept(is_nothrow_move_constructible_v<Iter>)
        : storage_(__construct_first{}, ::asc::std::move(value))
    {}
    CANN_ASC_STL_API constexpr common_iterator(Sent value) noexcept(is_nothrow_move_constructible_v<Sent>)
        : storage_(__construct_second{}, ::asc::std::move(value))  // NOLINT(build/include_what_you_use)
    {}
    common_iterator(const common_iterator&) = default;
    common_iterator(common_iterator&&) = default;
    common_iterator& operator=(const common_iterator&) = default;
    common_iterator& operator=(common_iterator&&) = default;
    template <class I2, class S2>
    CANN_ASC_STL_API common_iterator(const common_iterator<I2, S2>& other) noexcept(
        is_nothrow_constructible_v<Iter, const I2&> && is_nothrow_constructible_v<Sent, const S2&>)
        : storage_(__convert(other))
    {}
    template <class I2, class S2>
    CANN_ASC_STL_API common_iterator& operator=(const common_iterator<I2, S2>& other)
    {
        *this = common_iterator(other);
        return *this;
    }
    CANN_ASC_STL_API constexpr decltype(auto) operator*()
    {
        return *storage_.__first_;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr decltype(auto) operator*() const
    {
        return *storage_.__first_;
    }
    template <class I2 = Iter>
    CANN_ASC_STL_API constexpr decltype(auto) operator->() const
    {
        return ::asc::std::addressof(*storage_.__first_);
    }
    CANN_ASC_STL_API constexpr common_iterator& operator++()
    {
        ++storage_.__first_;
        return *this;
    }
    CANN_ASC_STL_API constexpr common_iterator operator++(int)
    {
        common_iterator old(*this);
        ++*this;
        return old;
    }
    CANN_ASC_STL_API constexpr const __variant_like<Iter, Sent>& __get_hold() const noexcept
    {
        return storage_;
    }
    CANN_ASC_STL_API constexpr __variant_like<Iter, Sent>& __get_hold() noexcept
    {
        return storage_;
    }

private:
    template <class I2, class S2>
    CANN_ASC_STL_API static __variant_like<Iter, Sent> __convert(const common_iterator<I2, S2>& other)
    {
        const auto& source = other.__get_hold();
        return source.__holds_first() ? __variant_like<Iter, Sent>(__construct_first{}, source.__first_) :
                                        __variant_like<Iter, Sent>(__construct_second{}, source.__second_);
    }
    __variant_like<Iter, Sent> storage_;
};

template <class I1, class S1, class I2, class S2>
CANN_ASC_STL_API constexpr bool operator==(const common_iterator<I1, S1>& left, const common_iterator<I2, S2>& right)
{
    const auto& lhs = left.__get_hold();
    const auto& rhs = right.__get_hold();
    if (lhs.__holds_second() && rhs.__holds_second()) {
        return true;
    }
    if (lhs.__holds_first() && rhs.__holds_first()) {
        return lhs.__first_ == rhs.__first_;
    }
    return lhs.__holds_first() ? lhs.__first_ == rhs.__second_ : lhs.__second_ == rhs.__first_;
}
template <class I1, class S1, class I2, class S2>
CANN_ASC_STL_API constexpr bool operator!=(const common_iterator<I1, S1>& left, const common_iterator<I2, S2>& right)
{
    return !(left == right);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_COMMON_ITERATOR_H
