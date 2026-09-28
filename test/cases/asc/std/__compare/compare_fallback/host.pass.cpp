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

#include <asc/std/__compare/compare_fallback.h>
#include <asc/std/__compare/compare_three_way.h>
#include <asc/std/__compare/ordering.h>

#include <cassert>

#if CANN_ASC_STL_DETAIL_HAS_CXX20()
// Built-in three-way operands produce the compiler's own category type; the
// standard vocabulary declares it on the Host side.
#include <compare>
#endif

namespace {

struct Plain {
    int value;
    friend bool operator==(const Plain& left, const Plain& right)
    {
        return left.value == right.value;
    }
    friend bool operator<(const Plain& left, const Plain& right)
    {
        return left.value < right.value;
    }
};

#if CANN_ASC_STL_DETAIL_HAS_CXX20()
struct ThreeWayCapable {
    int value;
    friend asc::std::strong_ordering operator<=>(const ThreeWayCapable& left, const ThreeWayCapable& right)
    {
        return left.value < right.value ? asc::std::strong_ordering::less :
            left.value > right.value    ? asc::std::strong_ordering::greater :
                                          asc::std::strong_ordering::equal;
    }
};
#endif

struct Unorderable {
    int value;
    friend bool operator==(const Unorderable&, const Unorderable& other)
    {
        return other.value == 0;
    }
    friend bool operator<(const Unorderable&, const Unorderable&)
    {
        return false;
    }
};

}  // namespace

int main()
{
    // Synthesized fallback over operator== and operator< in every language mode.
    const Plain low{1};
    const Plain high{2};
    assert(asc::std::compare_strong_order_fallback(low, high) == asc::std::strong_ordering::less);
    assert(asc::std::compare_strong_order_fallback(high, low) == asc::std::strong_ordering::greater);
    assert(asc::std::compare_strong_order_fallback(low, low) == asc::std::strong_ordering::equal);
    assert(asc::std::compare_weak_order_fallback(low, high) == asc::std::weak_ordering::less);
    assert(asc::std::compare_weak_order_fallback(low, low) == asc::std::weak_ordering::equivalent);
    assert(asc::std::compare_partial_order_fallback(low, high) == asc::std::partial_ordering::less);
    assert(asc::std::compare_partial_order_fallback(low, low) == asc::std::partial_ordering::equivalent);

    // The unordered partial state is reachable through the fallback synthesis.
    const Unorderable first{1};
    const Unorderable second{2};
    assert(asc::std::compare_partial_order_fallback(first, second) == asc::std::partial_ordering::unordered);

#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    // In C++20 the fallback prefers a real three-way comparison.
    const ThreeWayCapable capable_low{1};
    const ThreeWayCapable capable_high{2};
    assert(asc::std::compare_strong_order_fallback(capable_low, capable_high) == asc::std::strong_ordering::less);
    assert(asc::std::compare_strong_order_fallback(capable_low, capable_low) == asc::std::strong_ordering::equal);

    // The language-level three-way callable exists only in C++20. Built-in
    // operands produce the compiler's own category type, compared with the
    // standard idiom; user types returning the ASC vocabulary compare
    // directly.
    static_assert(asc::std::compare_three_way{}(1, 2) < 0);
    static_assert(asc::std::compare_three_way{}(2, 1) > 0);
    static_assert(asc::std::compare_three_way{}(1, 1) == 0);
    assert((asc::std::compare_three_way{}(1.0F, 2.0F) < 0));
    assert(asc::std::compare_three_way{}(capable_low, capable_high) == asc::std::strong_ordering::less);
    assert(asc::std::compare_three_way{}(capable_low, capable_low) == asc::std::strong_ordering::equal);
#endif

    constexpr auto constant_evaluated = asc::std::compare_strong_order_fallback(1, 2);
    static_assert(constant_evaluated == asc::std::strong_ordering::less);
    return 0;
}
