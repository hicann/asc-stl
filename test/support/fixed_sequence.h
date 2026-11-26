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

#ifndef ASC_STL_TEST_FIXED_SEQUENCE_H
#define ASC_STL_TEST_FIXED_SEQUENCE_H

#include <asc/__config>

namespace asc_stl_test {
template <class T, __SIZE_TYPE__ Capacity>
class fixed_sequence {
public:
    using value_type = T;
    using size_type = __SIZE_TYPE__;
    using reference = T&;
    using const_reference = const T&;
    CANN_ASC_STL_API bool empty() const
    {
        return size_ == 0;
    }
    CANN_ASC_STL_API size_type size() const
    {
        return size_;
    }
    CANN_ASC_STL_API reference front()
    {
        return values_[0];
    }
    CANN_ASC_STL_API const_reference front() const
    {
        return values_[0];
    }
    CANN_ASC_STL_API reference back()
    {
        return values_[size_ - 1];
    }
    CANN_ASC_STL_API const_reference back() const
    {
        return values_[size_ - 1];
    }
    CANN_ASC_STL_API reference operator[](size_type index)
    {
        return values_[index];
    }
    CANN_ASC_STL_API const_reference operator[](size_type index) const
    {
        return values_[index];
    }
    CANN_ASC_STL_API void push_back(const T& value)
    {
        values_[size_++] = value;
    }
    CANN_ASC_STL_API void push_back(T&& value)
    {
        values_[size_++] = static_cast<T&&>(value);
    }
    template <class... Args>
    CANN_ASC_STL_API reference emplace_back(Args&&... args)
    {
        values_[size_] = T(static_cast<Args&&>(args)...);
        return values_[size_++];
    }
    CANN_ASC_STL_API void pop_back()
    {
        --size_;
    }
    CANN_ASC_STL_API void pop_front()
    {
        for (size_type index = 1; index < size_; ++index)
            values_[index - 1] = values_[index];
        --size_;
    }
    CANN_ASC_STL_API void swap(fixed_sequence& other)  // NOLINT(build/include_what_you_use)
    {
        fixed_sequence temporary(*this);
        *this = other;
        other = temporary;
    }

private:
    T values_[Capacity]{};
    size_type size_ = 0;
};
}  // namespace asc_stl_test

#endif  // ASC_STL_TEST_FIXED_SEQUENCE_H
