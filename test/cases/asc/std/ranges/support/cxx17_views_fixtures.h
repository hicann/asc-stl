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

#ifndef ASC_STL_TEST_CXX17_VIEWS_FIXTURES_H
#define ASC_STL_TEST_CXX17_VIEWS_FIXTURES_H

#include <asc/std/ranges>
#include <asc/std/type_traits>

namespace asc_stl_cxx17_views_test {

struct reconstructible {
    int value;
    CANN_ASC_STL_API constexpr explicit reconstructible(int input) noexcept : value(input)
    {}
    CANN_ASC_STL_API constexpr reconstructible(const reconstructible&) noexcept = default;
    CANN_ASC_STL_API constexpr reconstructible(reconstructible&&) noexcept = default;
    reconstructible& operator=(const reconstructible&) = delete;
    reconstructible& operator=(reconstructible&&) = delete;
};

struct move_reconstructible {
    int value;
    CANN_ASC_STL_API constexpr explicit move_reconstructible(int input) noexcept : value(input)
    {}
    move_reconstructible(const move_reconstructible&) = delete;
    CANN_ASC_STL_API move_reconstructible(move_reconstructible&& other) : value(other.value)
    {
        other.value = -1;
    }
    move_reconstructible& operator=(const move_reconstructible&) = delete;
    move_reconstructible& operator=(move_reconstructible&&) = delete;
};

template <class T, class = void>
inline constexpr bool has_const_begin = false;
template <class T>
inline constexpr bool has_const_begin<T, asc::std::void_t<decltype(asc::std::declval<const T&>().begin())>> = true;

template <class T, class = void>
inline constexpr bool has_size = false;
template <class T>
inline constexpr bool has_size<T, asc::std::void_t<decltype(asc::std::declval<const T&>().size())>> = true;

template <class Category>
struct cursor {
    using iterator_concept = Category;
    using iterator_category = Category;
    using value_type = int;
    using difference_type = __PTRDIFF_TYPE__;
    using pointer = int*;
    using reference = int&;
    int* position = nullptr;
    int* increments = nullptr;
    CANN_ASC_STL_API constexpr cursor() = default;
    CANN_ASC_STL_API constexpr cursor(int* value, int* count) : position(value), increments(count)
    {}
    CANN_ASC_STL_API constexpr int& operator*() const
    {
        return *position;
    }
    CANN_ASC_STL_API constexpr int* operator->() const
    {
        return position;
    }
    CANN_ASC_STL_API constexpr cursor& operator++()
    {
        ++position;
        if (increments != nullptr)
            ++*increments;
        return *this;
    }
    CANN_ASC_STL_API constexpr cursor operator++(int)
    {
        auto old = *this;
        ++*this;
        return old;
    }
    CANN_ASC_STL_API constexpr cursor& operator--()
    {
        --position;
        return *this;
    }
    CANN_ASC_STL_API constexpr cursor operator--(int)
    {
        auto old = *this;
        --*this;
        return old;
    }
    CANN_ASC_STL_API constexpr cursor& operator+=(difference_type n)
    {
        position += n;
        return *this;
    }
    CANN_ASC_STL_API constexpr cursor& operator-=(difference_type n)
    {
        position -= n;
        return *this;
    }
    CANN_ASC_STL_API constexpr int& operator[](difference_type n) const
    {
        return position[n];
    }
    CANN_ASC_STL_API friend constexpr cursor operator+(cursor value, difference_type n)
    {
        return value += n;
    }
    CANN_ASC_STL_API friend constexpr cursor operator+(difference_type n, cursor value)
    {
        return value += n;
    }
    CANN_ASC_STL_API friend constexpr cursor operator-(cursor value, difference_type n)
    {
        return value -= n;
    }
    CANN_ASC_STL_API friend constexpr difference_type operator-(cursor left, cursor right)
    {
        return left.position - right.position;
    }
    CANN_ASC_STL_API friend constexpr bool operator==(cursor left, cursor right)
    {
        return left.position == right.position;
    }
    CANN_ASC_STL_API friend constexpr bool operator!=(cursor left, cursor right)
    {
        return !(left == right);
    }
    CANN_ASC_STL_API friend constexpr bool operator<(cursor left, cursor right)
    {
        return left.position < right.position;
    }
    CANN_ASC_STL_API friend constexpr bool operator>(cursor left, cursor right)
    {
        return right < left;
    }
    CANN_ASC_STL_API friend constexpr bool operator<=(cursor left, cursor right)
    {
        return !(right < left);
    }
    CANN_ASC_STL_API friend constexpr bool operator>=(cursor left, cursor right)
    {
        return !(left < right);
    }
};

template <class Iterator>
struct unsized_end {
    int* position = nullptr;
    CANN_ASC_STL_API friend constexpr bool operator==(const Iterator& value, unsized_end last)
    {
        return value.position == last.position;
    }
    CANN_ASC_STL_API friend constexpr bool operator==(unsized_end last, const Iterator& value)
    {
        return value == last;
    }
    CANN_ASC_STL_API friend constexpr bool operator!=(const Iterator& value, unsized_end last)
    {
        return !(value == last);
    }
    CANN_ASC_STL_API friend constexpr bool operator!=(unsized_end last, const Iterator& value)
    {
        return !(value == last);
    }
};

template <class Category>
struct noncommon_range {
    using iterator = cursor<Category>;
    int* first;
    int* last;
    int* increments;
    CANN_ASC_STL_API constexpr iterator begin() const
    {
        return {first, increments};
    }
    CANN_ASC_STL_API constexpr unsized_end<iterator> end() const
    {
        return {last};
    }
};

struct input_cursor {
    using iterator_concept = asc::std::input_iterator_tag;
    using iterator_category = asc::std::input_iterator_tag;
    using value_type = int;
    using difference_type = __PTRDIFF_TYPE__;
    using pointer = int*;
    using reference = int&;
    int* values = nullptr;
    int* position = nullptr;
    CANN_ASC_STL_API int& operator*() const
    {
        return values[*position];
    }
    CANN_ASC_STL_API input_cursor& operator++()
    {
        ++*position;
        return *this;
    }
    CANN_ASC_STL_API void operator++(int)
    {
        ++*this;
    }
};
struct input_end {
    int count;
    CANN_ASC_STL_API friend bool operator==(input_cursor value, input_end last)
    {
        return *value.position == last.count;
    }
    CANN_ASC_STL_API friend bool operator==(input_end last, input_cursor value)
    {
        return value == last;
    }
    CANN_ASC_STL_API friend bool operator!=(input_cursor value, input_end last)
    {
        return !(value == last);
    }
    CANN_ASC_STL_API friend bool operator!=(input_end last, input_cursor value)
    {
        return !(value == last);
    }
};
struct single_pass_range {
    int* values;
    int* position;
    int count;
    CANN_ASC_STL_API input_cursor begin() const
    {
        return {values, position};
    }
    CANN_ASC_STL_API input_end end() const
    {
        return {count};
    }
};

struct count_even {
    int* calls = nullptr;
    CANN_ASC_STL_API bool operator()(int value) const
    {
        ++*calls;
        return value % 2 == 0;
    }
};
struct count_less_than_three {
    int* calls = nullptr;
    CANN_ASC_STL_API bool operator()(int value) const
    {
        ++*calls;
        return value < 3;
    }
};
struct non_const_twice {
    CANN_ASC_STL_API constexpr int operator()(int value)
    {
        return value * 2;
    }
};
struct nonassign_operation {
    int amount;
    CANN_ASC_STL_API constexpr explicit nonassign_operation(int value) noexcept : amount(value)
    {}
    CANN_ASC_STL_API constexpr nonassign_operation(const nonassign_operation&) noexcept = default;
    CANN_ASC_STL_API constexpr nonassign_operation(nonassign_operation&&) noexcept = default;
    nonassign_operation& operator=(const nonassign_operation&) = delete;
    nonassign_operation& operator=(nonassign_operation&&) = delete;
    CANN_ASC_STL_API constexpr int operator()(int value) const
    {
        return value + amount;
    }
};
struct nonassign_predicate {
    int threshold;
    CANN_ASC_STL_API constexpr explicit nonassign_predicate(int value) noexcept : threshold(value)
    {}
    CANN_ASC_STL_API constexpr nonassign_predicate(const nonassign_predicate&) noexcept = default;
    CANN_ASC_STL_API constexpr nonassign_predicate(nonassign_predicate&&) noexcept = default;
    nonassign_predicate& operator=(const nonassign_predicate&) = delete;
    nonassign_predicate& operator=(nonassign_predicate&&) = delete;
    CANN_ASC_STL_API constexpr bool operator()(int value) const
    {
        return value < threshold;
    }
};
struct move_only_cursor {
    using iterator_concept = asc::std::input_iterator_tag;
    using iterator_category = asc::std::input_iterator_tag;
    using value_type = int;
    using difference_type = __PTRDIFF_TYPE__;
    using reference = int&;
    using pointer = int*;
    int* position = nullptr;
    CANN_ASC_STL_API constexpr move_only_cursor() = default;
    CANN_ASC_STL_API constexpr explicit move_only_cursor(int* value) : position(value)
    {}
    move_only_cursor(const move_only_cursor&) = delete;
    CANN_ASC_STL_API constexpr move_only_cursor(move_only_cursor&&) = default;
    move_only_cursor& operator=(const move_only_cursor&) = delete;
    CANN_ASC_STL_API constexpr move_only_cursor& operator=(move_only_cursor&&) = default;
    CANN_ASC_STL_API constexpr int& operator*() const
    {
        return *position;
    }
    CANN_ASC_STL_API constexpr move_only_cursor& operator++()
    {
        ++position;
        return *this;
    }
    CANN_ASC_STL_API constexpr void operator++(int)
    {
        ++*this;
    }
};

struct item {
    int value;
    bool enabled;
};

struct invalid_argument {};
struct void_operation {
    CANN_ASC_STL_API void operator()(int) const
    {}
};
struct immovable_value {
    CANN_ASC_STL_API immovable_value() = default;
    immovable_value(const immovable_value&) = delete;
    immovable_value(immovable_value&&) = delete;
    immovable_value& operator=(const immovable_value&) = delete;
    immovable_value& operator=(immovable_value&&) = delete;
};

struct explicit_copy_operation {
    CANN_ASC_STL_API constexpr explicit_copy_operation() = default;
    CANN_ASC_STL_API constexpr explicit explicit_copy_operation(const explicit_copy_operation&) = default;
    CANN_ASC_STL_API constexpr explicit_copy_operation(explicit_copy_operation&&) = default;
    CANN_ASC_STL_API constexpr int operator()(int value) const
    {
        return value + 1;
    }
};

struct move_only_count {
    int value;
    CANN_ASC_STL_API constexpr explicit move_only_count(int input) : value(input)
    {}
    move_only_count(const move_only_count&) = delete;
    CANN_ASC_STL_API constexpr move_only_count(move_only_count&&) = default;
    CANN_ASC_STL_API constexpr operator __PTRDIFF_TYPE__() const noexcept
    {
        return value;
    }
};
struct mutable_count {
    int value;
    CANN_ASC_STL_API constexpr explicit mutable_count(int input) : value(input)
    {}
    CANN_ASC_STL_API constexpr operator __PTRDIFF_TYPE__() & noexcept
    {
        return value;
    }
};
struct rvalue_count {
    int value;
    CANN_ASC_STL_API constexpr explicit rvalue_count(int input) : value(input)
    {}
    CANN_ASC_STL_API constexpr operator __PTRDIFF_TYPE__() && noexcept
    {
        return value;
    }
};

}  // namespace asc_stl_cxx17_views_test

#endif  // ASC_STL_TEST_CXX17_VIEWS_FIXTURES_H
