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

#ifndef ASC_STL_TEST_BIT_CONTRACTS_H
#define ASC_STL_TEST_BIT_CONTRACTS_H

#include <asc/bit>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

#include "bit_reference.h"

namespace bit_test {

template <class T, class = void>
struct accepts_all : asc::std::false_type {};

template <class T>
struct accepts_all<T,
    asc::std::void_t<decltype(asc::bit_reverse<T>(asc::std::declval<T>())),
        decltype(asc::bitfield_extract<T>(asc::std::declval<T>(), 0, 1)),
        decltype(asc::bitfield_insert<T>(asc::std::declval<T>(), asc::std::declval<T>(), 0, 1)),
        decltype(asc::bitmask<T>(0, 1))>> : asc::std::true_type {};

template <class A, class B, class = void>
struct accepts_insert : asc::std::false_type {};

template <class A, class B>
struct accepts_insert<A, B,
    asc::std::void_t<decltype(asc::bitfield_insert(asc::std::declval<A>(), asc::std::declval<B>(), 0, 1))>>
    : asc::std::true_type {};

// Check every operation separately: rejection by just one is insufficient.
template <class T, class = void>
struct has_reverse : asc::std::false_type {};
template <class T>
struct has_reverse<T, asc::std::void_t<decltype(asc::bit_reverse<T>(asc::std::declval<T>()))>> : asc::std::true_type {};
template <class T, class = void>
struct has_extract : asc::std::false_type {};
template <class T>
struct has_extract<T, asc::std::void_t<decltype(asc::bitfield_extract<T>(asc::std::declval<T>(), 0, 1))>>
    : asc::std::true_type {};
template <class T, class = void>
struct has_insert : asc::std::false_type {};
template <class T>
struct has_insert<T,
    asc::std::void_t<decltype(asc::bitfield_insert<T>(asc::std::declval<T>(), asc::std::declval<T>(), 0, 1))>>
    : asc::std::true_type {};
template <class T, class = void>
struct has_mask : asc::std::false_type {};
template <class T>
struct has_mask<T, asc::std::void_t<decltype(asc::bitmask<T>(0, 1))>> : asc::std::true_type {};

template <class T>
inline constexpr bool rejected =
    !has_reverse<T>::value && !has_extract<T>::value && !has_insert<T>::value && !has_mask<T>::value;

enum class scoped_bits : unsigned { one = 1 };
enum plain_bits : unsigned { one = 1 };
struct convertible {
    CANN_ASC_STL_API operator u32() const;
};

static_assert(accepts_all<u32>::value && accepts_all<u64>::value);
static_assert(rejected<bool> && rejected<int> && rejected<asc::std::int64_t>);
static_assert(rejected<asc::std::uint8_t> && rejected<asc::std::uint16_t>);
static_assert(rejected<float> && rejected<double> && rejected<scoped_bits> && rejected<plain_bits>);
static_assert(rejected<convertible> && rejected<void*>);
static_assert(rejected<const u32> && rejected<volatile u64> && rejected<u32&> && rejected<u64&&>);
static_assert((asc::std::is_same_v<unsigned long long, u32> || asc::std::is_same_v<unsigned long long, u64>) ?
        accepts_all<unsigned long long>::value :
        rejected<unsigned long long>);
static_assert(accepts_insert<u32, u32>::value && accepts_insert<const u64&, volatile u64&>::value);
static_assert(!accepts_insert<u32, u64>::value && !accepts_insert<u32, int>::value);
static_assert(asc::std::is_same_v<decltype(asc::bit_reverse(asc::std::declval<const u32&>())), u32>);
static_assert(asc::std::is_same_v<decltype(asc::bitfield_extract(u64{1}, 0, 1)), u64>);
static_assert(asc::std::is_same_v<decltype(asc::bitfield_insert<u32>(-1, 1, 0, 1)), u32>);
static_assert(asc::std::is_same_v<decltype(asc::bitmask(0, 1)), u32>);
static_assert(noexcept(asc::bit_reverse(u32{1})) && noexcept(asc::bitfield_extract(u64{1}, 0, 1)));
static_assert(noexcept(asc::bitfield_insert(u32{1}, u32{0}, 0, 1)) && noexcept(asc::bitmask<u64>(0, 1)));

template <class T>
CANN_ASC_STL_API constexpr bool value_contract()
{
    return asc::std::is_same_v<decltype(asc::bit_reverse(T{1})), T> &&
        asc::std::is_same_v<decltype(asc::bitfield_extract(T{1}, 0, 1)), T> &&
        asc::std::is_same_v<decltype(asc::bitfield_insert(T{1}, T{0}, 0, 1)), T> &&
        asc::std::is_same_v<decltype(asc::bitmask<T>(0, 1)), T> && noexcept(asc::bit_reverse(T{1})) &&
        noexcept(asc::bitfield_extract(T{1}, 0, 1)) && noexcept(asc::bitfield_insert(T{1}, T{0}, 0, 1)) &&
        noexcept(asc::bitmask<T>(0, 1));
}

static_assert(value_contract<u32>() && value_contract<u64>());

template <class T>
CANN_ASC_STL_API constexpr unsigned check_window(T destination, T source, int start, int width)
{
    const T extracted = asc::bitfield_extract(destination, start, width);
    const T inserted = asc::bitfield_insert(destination, source, start, width);
    const T mask = asc::bitmask<T>(start, width);
    unsigned failures = (extracted != reference_extract(destination, start, width)) +
        (inserted != reference_insert(destination, source, start, width)) + (mask != reference_mask<T>(start, width));
    failures += ((inserted ^ destination) & static_cast<T>(~reference_mask<T>(start, width))) != T{0};
    if (reference_window<T>(start, width)) {
        failures += asc::bitfield_extract(inserted, start, width) != reference_extract(source, 0, width);
    }
    return failures;
}

template <class T>
CANN_ASC_STL_API constexpr bool constant_contract()
{
    constexpr int width = digits<T>;
    constexpr T all = static_cast<T>(~T{0});
    constexpr T high = static_cast<T>(1ULL << (width - 1));
    return asc::bit_reverse(T{1}) == high && asc::bit_reverse(high) == T{1} && asc::bit_reverse(all) == all &&
        asc::bit_reverse(T{0}) == T{0} && check_window(all, T{0}, 0, width) == 0 &&
        check_window(all, T{1}, width - 1, 1) == 0 && check_window(all, T{1}, width - 4, 4) == 0 &&
        check_window(all, T{1}, 0, 0) == 0 && check_window(all, T{1}, width, 0) == 0 &&
        check_window(all, T{1}, -1, 1) == 0 && check_window(all, T{1}, 0, -1) == 0 &&
        check_window(all, T{1}, width + 1, 0) == 0 && check_window(all, T{1}, 0, width + 1) == 0 &&
        check_window(all, T{1}, width - 1, 2) == 0 && check_window(all, T{1}, INT_MAX, INT_MAX) == 0 &&
        check_window(all, T{1}, INT_MIN, INT_MAX) == 0 && check_window(all, T{1}, 1, INT_MAX) == 0 &&
        check_window(all, T{1}, 0, INT_MIN) == 0;
}

static_assert(constant_contract<u32>() && constant_contract<u64>());
static_assert(asc::bit_reverse(u32{0x0000000D}) == u32{0xB0000000});
static_assert(asc::bitfield_insert(u32{0xA5A50000}, u32{0x1AB}, 4, 8) == u32{0xA5A50AB0});
static_assert(asc::bitfield_extract(u32{0xA5A50AB0}, 4, 8) == u32{0xAB});
static_assert(asc::bitmask(4, 8) == u32{0xFF0});

}  // namespace bit_test

#endif  // ASC_STL_TEST_BIT_CONTRACTS_H
