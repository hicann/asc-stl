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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_IOTA_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_IOTA_ITERATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_integral.h>

namespace asc::std {
template <class Value>
class __iota_iterator {
public:
    using value_type = Value;
    using difference_type = __PTRDIFF_TYPE__;
    using reference = Value;
    using pointer = void;
    // Integral counters expose the full random-access surface below; other
    // weakly-incrementable values conservatively degrade to input iterators.
    using iterator_concept = conditional_t<is_integral_v<Value>, random_access_iterator_tag, input_iterator_tag>;
    using iterator_category = iterator_concept;
    CANN_ASC_STL_API constexpr __iota_iterator() noexcept : value_{}
    {}
    CANN_ASC_STL_API constexpr explicit __iota_iterator(Value value) noexcept : value_(value)
    {}
    CANN_ASC_STL_API constexpr Value operator*() const noexcept
    {
        return value_;
    }
    // Precondition, matching std::counting_iterator: the mathematical result
    // of value_ + offset must be representable in Value. The addition itself
    // is computed in difference_type, so the operation never exhibits signed
    // overflow before the (implementation-defined) narrowing cast.
    CANN_ASC_STL_API constexpr Value operator[](difference_type offset) const noexcept
    {
        return static_cast<Value>(value_ + offset);
    }
    CANN_ASC_STL_API constexpr __iota_iterator& operator++() noexcept
    {
        ++value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr __iota_iterator operator++(int) noexcept
    {
        auto copy = *this;
        ++*this;
        return copy;
    }
    CANN_ASC_STL_API constexpr __iota_iterator& operator--() noexcept
    {
        --value_;
        return *this;
    }
    CANN_ASC_STL_API constexpr __iota_iterator operator--(int) noexcept
    {
        auto copy = *this;
        --*this;
        return copy;
    }
    // Precondition, matching std::counting_iterator: the mathematical result
    // of value_ + value must be representable in Value.
    CANN_ASC_STL_API constexpr __iota_iterator& operator+=(difference_type value) noexcept
    {
        value_ = static_cast<Value>(value_ + value);
        return *this;
    }
    // The subtraction is evaluated in difference_type instead of negating
    // the offset: `-value` on the difference_type minimum would be undefined
    // before the addition even starts. Precondition, matching
    // std::counting_iterator: the mathematical result must be representable
    // in Value.
    CANN_ASC_STL_API constexpr __iota_iterator& operator-=(difference_type value) noexcept
    {
        value_ = static_cast<Value>(static_cast<difference_type>(value_) - value);
        return *this;
    }
    friend CANN_ASC_STL_API constexpr __iota_iterator operator+(__iota_iterator value, difference_type offset) noexcept
    {
        value += offset;
        return value;
    }
    friend CANN_ASC_STL_API constexpr __iota_iterator operator+(difference_type offset, __iota_iterator value) noexcept
    {
        value += offset;
        return value;
    }
    friend CANN_ASC_STL_API constexpr __iota_iterator operator-(__iota_iterator value, difference_type offset) noexcept
    {
        value -= offset;
        return value;
    }
    // Widened before subtracting so the difference is computed in
    // difference_type; the Value-domain subtraction could overflow a narrow
    // integral counter even when the true distance is representable.
    friend CANN_ASC_STL_API constexpr difference_type operator-(__iota_iterator left, __iota_iterator right) noexcept
    {
        return static_cast<difference_type>(left.value_) - static_cast<difference_type>(right.value_);
    }
    friend CANN_ASC_STL_API constexpr bool operator==(__iota_iterator left, __iota_iterator right) noexcept
    {
        return left.value_ == right.value_;
    }
    friend CANN_ASC_STL_API constexpr bool operator!=(__iota_iterator left, __iota_iterator right) noexcept
    {
        return !(left == right);
    }
    friend CANN_ASC_STL_API constexpr bool operator<(__iota_iterator left, __iota_iterator right) noexcept
    {
        return left.value_ < right.value_;
    }
    friend CANN_ASC_STL_API constexpr bool operator<=(__iota_iterator left, __iota_iterator right) noexcept
    {
        return !(right < left);
    }
    friend CANN_ASC_STL_API constexpr bool operator>(__iota_iterator left, __iota_iterator right) noexcept
    {
        return right < left;
    }
    friend CANN_ASC_STL_API constexpr bool operator>=(__iota_iterator left, __iota_iterator right) noexcept
    {
        return !(left < right);
    }

private:
    Value value_;
};
}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_IOTA_ITERATOR_H
