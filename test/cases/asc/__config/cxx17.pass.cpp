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

#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__concepts/arithmetic.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__cstddef/byte.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__limits/numeric_limits.h>
#include <asc/std/__type_traits/is_comparable.h>
#include <asc/std/__type_traits/is_swappable.h>

#if !defined(CANN_ASC_STL_DETAIL_CONCEPT) || !defined(CANN_ASC_STL_DETAIL_TEMPLATE) || \
    !defined(CANN_ASC_STL_DETAIL_REQUIRES)
#error "C++17 library constraints require the portable bool and SFINAE bridge"
#endif

namespace {

template <class T>
CANN_ASC_STL_DETAIL_CONCEPT integer_type = asc::std::integral<T>;

struct constrained_callable {
    CANN_ASC_STL_DETAIL_TEMPLATE(class T)
    CANN_ASC_STL_DETAIL_REQUIRES(integer_type<T>)
    constexpr int operator()(T value) const noexcept
    {
        return value + 1;
    }
};

struct readable {
    using value_type = const int;
};

struct callable {
    constexpr int operator()(int value) const noexcept
    {
        return value + 1;
    }
};

}  // namespace

int main()
{
    static_assert(CANN_ASC_STL_DETAIL_HAS_CXX17());
    static_assert(!CANN_ASC_STL_DETAIL_HAS_CXX20());
    static_assert(!CANN_ASC_STL_DETAIL_HAS_CONCEPTS());
    static_assert(!CANN_ASC_STL_DETAIL_HAS_CHAR8_T());
    static_assert(!CANN_ASC_STL_DETAIL_HAS_CONSTEVAL());
    // The bridge exposes bool predicates and constrained ordinary templates;
    // it does not enable native concept / requires syntax in this mode.
    static_assert(asc::std::is_same_v<decltype(integer_type<int>), const bool>);
    static_assert(integer_type<int> && !integer_type<double>);
    static_assert(asc::std::is_invocable_v<constrained_callable, int>);
    static_assert(!asc::std::is_invocable_v<constrained_callable, double>);
    static_assert(constrained_callable{}(3) == 4);
    static_assert(asc::std::is_invocable_v<callable, int>);
    static_assert(asc::std::is_same_v<asc::std::incrementable_traits<int*>::difference_type, asc::std::ptrdiff_t>);
    static_assert(asc::std::is_same_v<asc::std::indirectly_readable_traits<readable>::value_type, int>);
    static_assert(asc::std::numeric_limits<char16_t>::is_specialized);

    asc::std::byte value = static_cast<asc::std::byte>(1);
    value <<= 2;
    const auto bits = asc::std::bit_cast<unsigned int>(4.0F);
    return asc::std::invoke(callable{}, asc::std::to_integer<int>(value)) == 5 && bits != 0 ? 0 : 1;
}
