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

#ifndef CANN_ASC_STL_ASC_STD___VECTOR_VECTOR_H
#define CANN_ASC_STL_ASC_STD___VECTOR_VECTOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::std {

template <class T, class Allocator>
class vector {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = __SIZE_TYPE__;
    using difference_type = __PTRDIFF_TYPE__;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

    CANN_ASC_STL_API explicit vector(const Allocator& allocator) noexcept : allocator_(allocator)
    {}
    CANN_ASC_STL_API vector(vector&& other) noexcept
        : allocator_(other.allocator_), data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    vector(const vector&) = delete;
    vector& operator=(const vector&) = delete;
    CANN_ASC_STL_API vector& operator=(vector&& other) noexcept
    {
        if (this != &other) {
            release();
            allocator_ = other.allocator_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    CANN_ASC_STL_API ~vector()
    {
        release();
    }

    CANN_ASC_STL_API allocator_type get_allocator() const noexcept
    {
        return allocator_;
    }
    CANN_ASC_STL_API bool empty() const noexcept
    {
        return size_ == 0;
    }
    CANN_ASC_STL_API size_type size() const noexcept
    {
        return size_;
    }
    CANN_ASC_STL_API size_type capacity() const noexcept
    {
        return capacity_;
    }
    CANN_ASC_STL_API pointer data() noexcept
    {
        return data_;
    }
    CANN_ASC_STL_API const_pointer data() const noexcept
    {
        return data_;
    }
    CANN_ASC_STL_API iterator begin() noexcept
    {
        return data_;
    }
    CANN_ASC_STL_API const_iterator begin() const noexcept
    {
        return data_;
    }
    CANN_ASC_STL_API iterator end() noexcept
    {
        return data_ + size_;
    }
    CANN_ASC_STL_API const_iterator end() const noexcept
    {
        return data_ + size_;
    }
    CANN_ASC_STL_API reference operator[](size_type index) noexcept
    {
        return data_[index];
    }
    CANN_ASC_STL_API const_reference operator[](size_type index) const noexcept
    {
        return data_[index];
    }
    CANN_ASC_STL_API reference front() noexcept
    {
        return data_[0];
    }
    CANN_ASC_STL_API const_reference front() const noexcept
    {
        return data_[0];
    }
    CANN_ASC_STL_API reference back() noexcept
    {
        return data_[size_ - 1];
    }
    CANN_ASC_STL_API const_reference back() const noexcept
    {
        return data_[size_ - 1];
    }

    CANN_ASC_STL_API void reserve(size_type requested)
    {
        if (requested <= capacity_)
            return;
        pointer replacement = allocator_.allocate(requested);
        if (replacement == nullptr)
            return;
        for (size_type index = 0; index < size_; ++index) {
            ::new (static_cast<void*>(replacement + index)) T(static_cast<T&&>(data_[index]));
            data_[index].~T();
        }
        if (data_ != nullptr)
            allocator_.deallocate(data_, capacity_);
        data_ = replacement;
        capacity_ = requested;
    }
    CANN_ASC_STL_API void push_back(const T& value)
    {
        ensure_one_more();
        ::new (static_cast<void*>(data_ + size_)) T(value);
        ++size_;
    }
    CANN_ASC_STL_API void push_back(T&& value)
    {
        ensure_one_more();
        ::new (static_cast<void*>(data_ + size_)) T(static_cast<T&&>(value));
        ++size_;
    }
    template <class... Args>
    CANN_ASC_STL_API reference emplace_back(Args&&... args)
    {
        ensure_one_more();
        ::new (static_cast<void*>(data_ + size_)) T(static_cast<Args&&>(args)...);
        return data_[size_++];
    }
    CANN_ASC_STL_API void pop_back()
    {
        --size_;
        data_[size_].~T();
    }
    CANN_ASC_STL_API void clear() noexcept
    {
        while (size_ != 0)
            pop_back();
    }

private:
    CANN_ASC_STL_API void ensure_one_more()
    {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 2 : capacity_ * 2);
    }
    CANN_ASC_STL_API void release() noexcept
    {
        clear();
        if (data_ != nullptr)
            allocator_.deallocate(data_, capacity_);
        data_ = nullptr;
        capacity_ = 0;
    }

    Allocator allocator_;
    pointer data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC_STD___VECTOR_VECTOR_H
