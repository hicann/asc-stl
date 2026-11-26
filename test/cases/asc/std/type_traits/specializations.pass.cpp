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

#include <asc/std/type_traits>
#include <type_traits>

namespace s = asc::std;

template <class Trait, class = void>
struct has_type : std::false_type {};
template <class Trait>
struct has_type<Trait, std::void_t<typename Trait::type>> : std::true_type {};

template <s::size_t Align>
constexpr bool storage()
{
    using exact = typename s::aligned_storage<Align, Align>::type;
    using padded = s::aligned_storage_t<Align + 1, Align>;
    return alignof(exact) == Align && sizeof(exact) >= Align && alignof(padded) == Align &&
        sizeof(padded) >= Align + 1 && sizeof(padded) % Align == 0;
}
static_assert(storage<1>() && storage<2>() && storage<4>() && storage<8>() && storage<16>() && storage<32>() &&
    storage<64>() && storage<128>() && storage<256>() && storage<512>() && storage<1024>() && storage<2048>() &&
    storage<4096>() && storage<8192>() && storage<16384>());
static_assert(storage<32768>());
static_assert(alignof(s::aligned_storage_t<sizeof(double)>) >= alignof(double));
static_assert(!has_type<s::common_reference<>>::value && !has_type<s::common_type<>>::value);
static_assert(std::is_same_v<typename s::common_reference<const int&>::type, const int&>);
static_assert(std::is_same_v<s::common_reference_t<int&, const int&>, const int&>);
static_assert(std::is_same_v<s::common_reference_t<int&, const int&, const volatile int&>, const volatile int&>);
static_assert(std::is_same_v<typename s::common_type<const short&>::type, short>);
static_assert(std::is_same_v<s::common_type_t<int, double>, double>);
static_assert(std::is_same_v<s::common_type_t<short, int, long, double>, double>);
static_assert(std::is_same_v<typename s::conditional<false, long, int>::type, int>);
static_assert(!has_type<s::enable_if<false, int>>::value && std::is_same_v<s::enable_if_t<true, int>, int>);
static_assert(s::conjunction<>::value && s::conjunction<s::true_type>::value);
static_assert(!s::conjunction<s::true_type, s::false_type>::value);
using matrix = const int[][3];
static_assert(s::extent_v<matrix> == 0 && s::extent<matrix, 1>::value == 3 && s::extent_v<matrix, 2> == 0);
static_assert(!s::is_bounded_array_v<matrix> && s::is_bounded_array_v<s::remove_extent_t<matrix>>);
static_assert(std::is_same_v<typename s::remove_all_extents<matrix>::type, const int>);
static_assert(std::is_same_v<s::remove_extent_t<int[]>, int> && std::is_same_v<s::remove_extent_t<int[3]>, int>);
static_assert(std::is_same_v<s::remove_pointer_t<const int* const volatile>, const int>);
static_assert(
    std::is_same_v<s::remove_pointer_t<int* volatile>, int> && std::is_same_v<s::remove_pointer_t<int* const>, int>);
static_assert(!s::is_destructible<void>::value && !s::is_destructible_v<int[]> && s::is_destructible_v<int[3]>);
static_assert(
    s::is_nothrow_destructible_v<int[2]> && s::is_nothrow_destructible_v<int&> && s::is_nothrow_destructible_v<int&&>);
enum class scoped : unsigned { entry };
enum ordinary { entry };
static_assert(s::is_scoped_enum<scoped>::value && s::is_scoped_enum_v<const scoped>);
static_assert(!s::is_scoped_enum<ordinary>::value && !s::is_scoped_enum_v<int>);
static_assert(s::is_convertible<int, long>::value && !s::is_convertible_v<void*, int*>);
static_assert(s::is_convertible_v<int&, const int&> && !s::is_convertible<const int&, int&>::value);
static_assert(
    std::is_same_v<s::remove_reference_t<int&>, int> && std::is_same_v<s::remove_reference_t<const int&&>, const int>);
static_assert(std::is_same_v<s::remove_const_t<const volatile int>, volatile int> &&
    std::is_same_v<s::remove_volatile_t<const volatile int>, const int>);
int main()
{}
