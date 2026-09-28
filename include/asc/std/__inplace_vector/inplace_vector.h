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

#ifndef CANN_ASC_STL_ASC_STD___INPLACE_VECTOR_INPLACE_VECTOR_H
#define CANN_ASC_STL_ASC_STD___INPLACE_VECTOR_INPLACE_VECTOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__fwd/inplace_vector.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__optional/optional.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace detail {

// Fixed-capacity inline storage.  The union keeps the zero-capacity
// specialization empty and preserves trivial destruction for element types
// whose destructor is trivial.
template <class T, size_t Capacity, bool TrivialDestruction = is_trivially_destructible_v<T>>
union inplace_vector_storage {
    CANN_ASC_STL_API constexpr inplace_vector_storage() noexcept : empty()
    {}
    CANN_ASC_STL_API ~inplace_vector_storage() noexcept
    {}

    char empty;
    T elements[Capacity];
};

template <class T, size_t Capacity>
union inplace_vector_storage<T, Capacity, true> {
    CANN_ASC_STL_API constexpr inplace_vector_storage() noexcept : empty()
    {}
    CANN_ASC_STL_API ~inplace_vector_storage() noexcept = default;

    char empty;
    T elements[Capacity];
};

// The zero-capacity storage is empty and trivial in both destruction modes.
template <class T>
union inplace_vector_storage<T, 0, false> {
    CANN_ASC_STL_API constexpr inplace_vector_storage() noexcept : empty()
    {}
    CANN_ASC_STL_API ~inplace_vector_storage() noexcept
    {}

    char empty;
};

template <class T>
union inplace_vector_storage<T, 0, true> {
    CANN_ASC_STL_API constexpr inplace_vector_storage() noexcept : empty()
    {}
    CANN_ASC_STL_API ~inplace_vector_storage() noexcept = default;

    char empty;
};

}  // namespace detail

// Final-C++26 fixed-capacity vector.  Host delivers the full nonthrowing
// member contract; Device delivers the fixed-capacity inline-storage
// nonthrowing subset.  try_emplace_back/try_push_back return optional<T&>
// (P3981R2); throwing members such as at/push_back/emplace_back/resize and
// the P4022R0-removed try_append_range stay outside the delivered boundary.
template <class T, size_t Capacity>
class inplace_vector {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator = T*;
    using const_iterator = const T*;

    CANN_ASC_STL_API constexpr inplace_vector() noexcept : size_(0)
    {}

    CANN_ASC_STL_API constexpr inplace_vector(const inplace_vector& other) : size_(0)
    {
        while (size_ < other.size_) {
            unchecked_emplace_back(other.storage_.elements[size_]);
        }
    }

    CANN_ASC_STL_API constexpr inplace_vector(inplace_vector&& other) : size_(0)
    {
        while (size_ < other.size_) {
            unchecked_emplace_back(
                ::asc::std::move(other.storage_.elements[size_]));  // NOLINT(build/include_what_you_use)
        }
    }

    CANN_ASC_STL_API constexpr inplace_vector& operator=(const inplace_vector& other)
    {
        if (this != &other) {
            const size_type common = size_ < other.size_ ? size_ : other.size_;
            for (size_type index = 0; index < common; ++index) {
                storage_.elements[index] = other.storage_.elements[index];
            }
            while (size_ > other.size_) {
                pop_back();
            }
            while (size_ < other.size_) {
                unchecked_emplace_back(other.storage_.elements[size_]);
            }
        }
        return *this;
    }

    CANN_ASC_STL_API constexpr inplace_vector& operator=(inplace_vector&& other)
    {
        if (this != &other) {
            const size_type common = size_ < other.size_ ? size_ : other.size_;
            for (size_type index = 0; index < common; ++index) {
                storage_.elements[index] =
                    ::asc::std::move(other.storage_.elements[index]);  // NOLINT(build/include_what_you_use)
            }
            while (size_ > other.size_) {
                pop_back();
            }
            while (size_ < other.size_) {
                unchecked_emplace_back(
                    ::asc::std::move(other.storage_.elements[size_]));  // NOLINT(build/include_what_you_use)
            }
        }
        return *this;
    }

    CANN_ASC_STL_API ~inplace_vector()
    {
        if constexpr (!is_trivially_destructible_v<T>) {
            while (size_ != 0) {
                pop_back();
            }
        }
    }

    CANN_ASC_STL_API constexpr size_type size() const noexcept
    {
        return size_;
    }
    CANN_ASC_STL_API static constexpr size_type max_size() noexcept
    {
        return Capacity;
    }
    CANN_ASC_STL_API static constexpr size_type capacity() noexcept
    {
        return Capacity;
    }
    CANN_ASC_STL_API constexpr bool empty() const noexcept
    {
        return size_ == 0;
    }

    CANN_ASC_STL_API constexpr pointer data() noexcept
    {
        if constexpr (Capacity == 0) {
            return nullptr;
        } else {
            return storage_.elements;
        }
    }
    CANN_ASC_STL_API constexpr const_pointer data() const noexcept
    {
        if constexpr (Capacity == 0) {
            return nullptr;
        } else {
            return storage_.elements;
        }
    }

    CANN_ASC_STL_API constexpr iterator begin() noexcept
    {
        return data();
    }
    CANN_ASC_STL_API constexpr const_iterator begin() const noexcept
    {
        return data();
    }
    CANN_ASC_STL_API constexpr const_iterator cbegin() const noexcept
    {
        return data();
    }
    CANN_ASC_STL_API constexpr iterator end() noexcept
    {
        return data() + size_;
    }
    CANN_ASC_STL_API constexpr const_iterator end() const noexcept
    {
        return data() + size_;
    }
    CANN_ASC_STL_API constexpr const_iterator cend() const noexcept
    {
        return data() + size_;
    }

    CANN_ASC_STL_API constexpr reference front() noexcept
    {
        return data()[0];
    }
    CANN_ASC_STL_API constexpr const_reference front() const noexcept
    {
        return data()[0];
    }
    CANN_ASC_STL_API constexpr reference back() noexcept
    {
        return data()[size_ - 1];
    }
    CANN_ASC_STL_API constexpr const_reference back() const noexcept
    {
        return data()[size_ - 1];
    }

    CANN_ASC_STL_API constexpr reference operator[](size_type index) noexcept
    {
        return data()[index];
    }
    CANN_ASC_STL_API constexpr const_reference operator[](size_type index) const noexcept
    {
        return data()[index];
    }

    template <class... Args>
    CANN_ASC_STL_API constexpr reference unchecked_emplace_back(Args&&... args)
    {
        pointer result = ::asc::std::construct_at(
            data() + size_, ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
        ++size_;
        return *result;
    }

    template <class... Args>
    CANN_ASC_STL_API constexpr optional<reference> try_emplace_back(Args&&... args)
    {
        if (size_ == Capacity) {
            return nullopt;
        }
        return optional<reference>(
            unchecked_emplace_back(::asc::std::forward<Args>(args)...));  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_API constexpr optional<reference> try_push_back(const T& value)
    {
        return try_emplace_back(value);
    }

    CANN_ASC_STL_API constexpr optional<reference> try_push_back(T&& value)
    {
        return try_emplace_back(::asc::std::move(value));  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_API constexpr reference unchecked_push_back(const T& value)
    {
        return unchecked_emplace_back(value);
    }

    CANN_ASC_STL_API constexpr reference unchecked_push_back(T&& value)
    {
        return unchecked_emplace_back(::asc::std::move(value));  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_API constexpr void pop_back() noexcept
    {
        --size_;
        ::asc::std::__destroy_at(data() + size_);
    }

    CANN_ASC_STL_API constexpr void clear() noexcept
    {
        while (size_ != 0) {
            pop_back();
        }
    }

    CANN_ASC_STL_API constexpr iterator erase(const_iterator position)
    {
        iterator where = data() + (position - data());
        for (iterator moved = where + 1; moved != end(); ++moved) {
            *(moved - 1) = ::asc::std::move(*moved);  // NOLINT(build/include_what_you_use)
        }
        pop_back();
        return where;
    }

    CANN_ASC_STL_API constexpr iterator erase(const_iterator first, const_iterator last)
    {
        iterator head = data() + (first - data());
        const size_type removed = static_cast<size_type>(last - first);
        if (removed == 0) {
            return head;
        }
        for (iterator moved = data() + (last - data()); moved != end(); ++moved) {
            *head = ::asc::std::move(*moved);  // NOLINT(build/include_what_you_use)
            ++head;
        }
        for (size_type index = 0; index < removed; ++index) {
            pop_back();
        }
        return data() + (first - data());
    }

    template <class Predicate>
    CANN_ASC_STL_API constexpr size_type erase_if(Predicate predicate)
    {
        const size_type original = size_;
        size_type kept = 0;
        for (size_type index = 0; index < original; ++index) {
            if (!predicate(storage_.elements[index])) {
                if (index != kept) {
                    storage_.elements[kept] =
                        ::asc::std::move(storage_.elements[index]);  // NOLINT(build/include_what_you_use)
                }
                ++kept;
            }
        }
        while (size_ > kept) {
            pop_back();
        }
        return original - kept;
    }

    CANN_ASC_STL_API constexpr void swap(inplace_vector& other)
    {
        if (this == &other) {
            return;
        }
        const size_type common = size_ < other.size_ ? size_ : other.size_;
        for (size_type index = 0; index < common; ++index) {
            T temporary = ::asc::std::move(storage_.elements[index]);  // NOLINT(build/include_what_you_use)
            storage_.elements[index] =
                ::asc::std::move(other.storage_.elements[index]);          // NOLINT(build/include_what_you_use)
            other.storage_.elements[index] = ::asc::std::move(temporary);  // NOLINT(build/include_what_you_use)
        }
        inplace_vector& smaller = size_ < other.size_ ? *this : other;
        inplace_vector& larger = size_ < other.size_ ? other : *this;
        const size_type smaller_original = smaller.size_;
        for (size_type index = smaller_original; index < larger.size_; ++index) {
            smaller.unchecked_emplace_back(
                ::asc::std::move(larger.storage_.elements[index]));  // NOLINT(build/include_what_you_use)
        }
        while (larger.size_ > smaller_original) {
            larger.pop_back();
        }
    }

private:
    detail::inplace_vector_storage<T, Capacity> storage_;
    size_type size_;
};

template <class T, size_t Capacity, class U = T>
CANN_ASC_STL_API constexpr typename inplace_vector<T, Capacity>::size_type erase(
    inplace_vector<T, Capacity>& values, const U& value)
{
    return values.erase_if([&value](const T& element) { return element == value; });
}

template <class T, size_t Capacity, class Predicate>
CANN_ASC_STL_API constexpr typename inplace_vector<T, Capacity>::size_type erase_if(
    inplace_vector<T, Capacity>& values, Predicate predicate)
{
    return values.erase_if(predicate);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___INPLACE_VECTOR_INPLACE_VECTOR_H
