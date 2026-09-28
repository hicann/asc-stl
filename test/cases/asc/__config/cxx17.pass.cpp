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

#ifdef CANN_ASC_STL_DETAIL_CONCEPT
#error "C++20 concept syntax macros must not be exposed in C++17"
#endif

namespace {

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
    static_assert(asc::std::is_invocable_v<callable, int>);
    static_assert(asc::std::is_same_v<asc::std::incrementable_traits<int*>::difference_type, asc::std::ptrdiff_t>);
    static_assert(asc::std::is_same_v<asc::std::indirectly_readable_traits<readable>::value_type, int>);
    static_assert(asc::std::numeric_limits<char16_t>::is_specialized);

    asc::std::byte value = static_cast<asc::std::byte>(1);
    value <<= 2;
    const auto bits = asc::std::bit_cast<unsigned int>(4.0F);
    return asc::std::invoke(callable{}, asc::std::to_integer<int>(value)) == 5 && bits != 0 ? 0 : 1;
}
