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

#ifndef ASC_STL_TEST_SUPPORT_VOCABULARY_COPY_TEST_H
#define ASC_STL_TEST_SUPPORT_VOCABULARY_COPY_TEST_H

#include <asc/std/type_traits>

namespace asc_stl_copy_test {

struct move_only {
    int value;
    CANN_ASC_STL_API constexpr explicit move_only(int input) : value(input)
    {}
    CANN_ASC_STL_API move_only(move_only&&) = default;
    CANN_ASC_STL_API move_only& operator=(move_only&&) = default;
};

struct construct_only {
    construct_only(const construct_only&) = default;
    construct_only& operator=(const construct_only&) = delete;
};

struct assign_only {
    assign_only(const assign_only&) = delete;
    assign_only& operator=(const assign_only&) = default;
};

struct custom_assignment {
    int value;
    CANN_ASC_STL_API custom_assignment(const custom_assignment&) = default;
    CANN_ASC_STL_API custom_assignment& operator=(const custom_assignment& other)
    {
        value = other.value;
        return *this;
    }
};

struct counts {
    int live = 0;
    int copies = 0;
    int assignments = 0;
};

struct payload {
    counts& operations;
    int value;

    CANN_ASC_STL_API payload(counts& counter, int input) noexcept : operations(counter), value(input)
    {
        ++operations.live;
    }
    CANN_ASC_STL_API payload(const payload& other) noexcept : payload(other.operations, other.value)
    {
        ++operations.copies;
    }
    CANN_ASC_STL_API payload& operator=(const payload& other) noexcept
    {
        value = other.value;
        ++operations.assignments;
        return *this;
    }
    CANN_ASC_STL_API ~payload()
    {
        --operations.live;
    }
};

template <template <class> class Wrapper>
constexpr bool check_traits()
{
    using M = Wrapper<move_only>;
    static_assert(!asc::std::is_copy_constructible_v<M> && !asc::std::is_copy_assignable_v<M>);
    static_assert(!asc::std::is_constructible_v<M, M&> && !asc::std::is_assignable_v<M&, M&>);
    static_assert(asc::std::is_move_constructible_v<M> && asc::std::is_move_assignable_v<M>);
    static_assert(asc::std::is_trivially_copy_constructible_v<Wrapper<int>> &&
        asc::std::is_trivially_copy_assignable_v<Wrapper<int>>);
    static_assert(asc::std::is_trivially_copyable_v<Wrapper<int>>);
    static_assert(asc::std::is_trivially_copy_constructible_v<Wrapper<construct_only>> &&
        !asc::std::is_copy_assignable_v<Wrapper<construct_only>>);
    static_assert(!asc::std::is_copy_constructible_v<Wrapper<assign_only>> &&
        !asc::std::is_copy_assignable_v<Wrapper<assign_only>>);
    static_assert(asc::std::is_trivially_copy_constructible_v<Wrapper<custom_assignment>> &&
        asc::std::is_copy_assignable_v<Wrapper<custom_assignment>> &&
        !asc::std::is_trivially_copy_assignable_v<Wrapper<custom_assignment>>);
    static_assert(asc::std::is_copy_constructible_v<Wrapper<payload>> &&
        !asc::std::is_trivially_copy_constructible_v<Wrapper<payload>>);
    return true;
}

}  // namespace asc_stl_copy_test

#endif  // ASC_STL_TEST_SUPPORT_VOCABULARY_COPY_TEST_H
