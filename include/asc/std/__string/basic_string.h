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

#ifndef CANN_ASC_STL_ASC_STD___STRING_BASIC_STRING_H
#define CANN_ASC_STL_ASC_STD___STRING_BASIC_STRING_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

template <class CharT>
struct arena_char_traits {
    using char_type = CharT;
};

template <class CharT, class Traits, class Allocator>
class basic_string {
public:
    using traits_type = Traits;
    using value_type = CharT;
    using allocator_type = Allocator;
    using size_type = __SIZE_TYPE__;
    using reference = CharT&;
    using const_reference = const CharT&;
    using pointer = CharT*;
    using const_pointer = const CharT*;
    using iterator = CharT*;
    using const_iterator = const CharT*;

    CANN_ASC_STL_API explicit basic_string(const Allocator& allocator) noexcept : allocator_(allocator)
    {
        reserve(0);
    }
    CANN_ASC_STL_API basic_string(const CharT* text, const Allocator& allocator) : allocator_(allocator)
    {
        reserve(0);
        append(text);
    }
    basic_string(const basic_string&) = delete;
    basic_string& operator=(const basic_string&) = delete;
    basic_string(basic_string&&) = delete;
    basic_string& operator=(basic_string&&) = delete;
    CANN_ASC_STL_API ~basic_string()
    {
        if (data_ != nullptr) {
            allocator_.deallocate(data_, capacity_ + 1);
        }
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
    CANN_ASC_STL_API size_type length() const noexcept
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
    CANN_ASC_STL_API const_pointer c_str() const noexcept
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
        if (data_ != nullptr && requested <= capacity_) {
            return;
        }
        const size_type next_capacity = requested > capacity_ ? requested : capacity_;
        pointer replacement = allocator_.allocate(next_capacity + 1);
        if (replacement == nullptr) {
            return;
        }
        for (size_type index = 0; index < size_; ++index) {
            replacement[index] = data_[index];
        }
        replacement[size_] = CharT{};
        if (data_ != nullptr) {
            allocator_.deallocate(data_, capacity_ + 1);
        }
        data_ = replacement;
        capacity_ = next_capacity;
    }
    CANN_ASC_STL_API void push_back(CharT value)
    {
        ensure(size_ + 1);
        data_[size_++] = value;
        data_[size_] = CharT{};
    }
    CANN_ASC_STL_API basic_string& append(const CharT* text)
    {
        size_type count = 0;
        while (text[count] != CharT{}) {
            ++count;
        }
        ensure(size_ + count);
        for (size_type index = 0; index < count; ++index) {
            data_[size_ + index] = text[index];
        }
        size_ += count;
        data_[size_] = CharT{};
        return *this;
    }
    CANN_ASC_STL_API basic_string& operator+=(const CharT* text)
    {
        return append(text);
    }
    CANN_ASC_STL_API basic_string& operator+=(CharT value)
    {
        push_back(value);
        return *this;
    }
    CANN_ASC_STL_API void clear() noexcept
    {
        size_ = 0;
        data_[0] = CharT{};
    }

private:
    CANN_ASC_STL_API void ensure(size_type requested)
    {
        if (requested > capacity_) {
            reserve(capacity_ == 0 ? requested : (requested > capacity_ * 2 ? requested : capacity_ * 2));
        }
    }

    Allocator allocator_;
    pointer data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___STRING_BASIC_STRING_H
