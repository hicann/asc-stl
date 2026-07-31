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

#include <asc/std/__algorithm/clamp.h>

#include <type_traits>

namespace {

struct TaggedValue {
    int key;
    int identity;
};

constexpr bool operator<(const TaggedValue& left, const TaggedValue& right)
{
    return left.key < right.key;
}

struct Greater {
    constexpr bool operator()(int left, int right) const
    {
        return left > right;
    }
};

constexpr bool CheckDefaultClamp()
{
    const int low = 0;
    const int high = 10;
    const int below = -4;
    const int exact_low = 0;
    const int middle = 6;
    const int exact_high = 10;
    const int above = 14;

    return &asc::std::clamp(below, low, high) == &low && &asc::std::clamp(exact_low, low, high) == &exact_low &&
        &asc::std::clamp(middle, low, high) == &middle && &asc::std::clamp(exact_high, low, high) == &exact_high &&
        &asc::std::clamp(above, low, high) == &high;
}

constexpr bool CheckComparatorClamp()
{
    const int low = 10;
    const int high = 0;
    const int below = 14;
    const int exact_low = 10;
    const int middle = 6;
    const int exact_high = 0;
    const int above = -4;
    const Greater compare;

    return &asc::std::clamp(below, low, high, compare) == &low &&
        &asc::std::clamp(exact_low, low, high, compare) == &exact_low &&
        &asc::std::clamp(middle, low, high, compare) == &middle &&
        &asc::std::clamp(exact_high, low, high, compare) == &exact_high &&
        &asc::std::clamp(above, low, high, compare) == &high;
}

constexpr bool CheckTaggedClamp()
{
    const TaggedValue low{0, 1};
    const TaggedValue middle{5, 2};
    const TaggedValue high{10, 3};
    const TaggedValue below{-3, 4};
    const TaggedValue above{17, 5};

    return &asc::std::clamp(below, low, high) == &low && &asc::std::clamp(middle, low, high) == &middle &&
        &asc::std::clamp(above, low, high) == &high;
}

constexpr bool CheckFloatingPointClamp()
{
    const float low = -2.5F;
    const float middle = 1.25F;
    const float high = 4.5F;
    const float below = -8.0F;
    const float above = 9.0F;

    return &asc::std::clamp(below, low, high) == &low && &asc::std::clamp(middle, low, high) == &middle &&
        &asc::std::clamp(above, low, high) == &high;
}

constexpr int kValue = 5;
constexpr int kLow = 0;
constexpr int kHigh = 10;

static_assert(std::is_same_v<decltype(asc::std::clamp(kValue, kLow, kHigh)), const int&>);
static_assert(std::is_same_v<decltype(asc::std::clamp(kValue, kLow, kHigh, Greater{})), const int&>);
static_assert(CheckDefaultClamp());
static_assert(CheckComparatorClamp());
static_assert(CheckTaggedClamp());
static_assert(CheckFloatingPointClamp());

}  // namespace

int main()
{
    return CheckDefaultClamp() && CheckComparatorClamp() && CheckTaggedClamp() && CheckFloatingPointClamp() ? 0 : 1;
}
