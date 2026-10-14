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

#ifndef ASC_STL_TEST_SUPPORT_CORE_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_CORE_SEMANTICS_H

#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__cstddef/byte.h>
#include <asc/std/__fwd/array.h>
#include <asc/std/__fwd/span.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_referenceable.h>
#include <asc/std/__type_traits/is_signed_integer.h>
#include <asc/std/__type_traits/is_trivially_default_constructible.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__type_traits/promote.h>
#include <asc/std/__type_traits/underlying_type.h>
#include <asc/std/__utility/convert_to_integral.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/priority_tag.h>
#include <asc/std/__utility/to_underlying.h>
#include <asc/std/cstddef>

namespace asc_stl_core_test {

struct empty {};
struct nontrivial_default {
    CANN_ASC_STL_API nontrivial_default() : value(1)
    {}
    int value;
};
struct pair_like {
    int first;
    int second;
};
enum fixed_int_enum : int { fixed_int_zero = 0, fixed_int_two = 2 };
enum class fixed_byte_enum : unsigned char { fixed_byte_five = 5 };
enum plain_enum { plain_enum_a, plain_enum_b };

}  // namespace asc_stl_core_test

namespace asc {
namespace std {

template <>
struct tuple_size<asc_stl_core_test::pair_like> : integral_constant<size_t, 2> {};

}  // namespace std
}  // namespace asc

namespace asc_stl_core_test {

// __concepts/same_as.h: symmetric identity and rejection of distinct types.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
static_assert(asc::std::same_as<int, int>);
static_assert(asc::std::same_as<const void, const void>);
static_assert(!asc::std::same_as<int, const int>);
static_assert(!asc::std::same_as<int, long>);
#endif

// __cstddef/byte.h: independent integer-arithmetic goldens.
constexpr unsigned int golden_or = 0x0cu | 0x22u;
constexpr unsigned int golden_and = 0x0cu & 0x26u;
constexpr unsigned int golden_xor = 0x0cu ^ 0x26u;
constexpr unsigned char golden_not = static_cast<unsigned char>(~0x0cu);
static_assert(asc::std::to_integer<unsigned char>(asc::std::byte{0x0c} | asc::std::byte{0x22}) ==
    static_cast<unsigned char>(golden_or));
static_assert(asc::std::to_integer<unsigned char>(asc::std::byte{0x0c} & asc::std::byte{0x26}) ==
    static_cast<unsigned char>(golden_and));
static_assert(asc::std::to_integer<unsigned char>(asc::std::byte{0x0c} ^ asc::std::byte{0x26}) ==
    static_cast<unsigned char>(golden_xor));
static_assert(asc::std::to_integer<unsigned char>(~asc::std::byte{0x0c}) == golden_not);
static_assert(asc::std::to_integer<int>(asc::std::byte{0x03} << 4) == (0x03 << 4));
static_assert(asc::std::to_integer<int>(asc::std::byte{0x30} >> 4) == (0x30 >> 4));
CANN_ASC_STL_API constexpr asc::std::byte compound_assign(asc::std::byte value)
{
    return value |= asc::std::byte{0x22};
}
CANN_ASC_STL_API constexpr asc::std::byte compound_shift(asc::std::byte value)
{
    return value >>= 1;
}
static_assert(asc::std::to_integer<unsigned char>(compound_assign(asc::std::byte{0x0c})) ==
    static_cast<unsigned char>(golden_or));
static_assert(asc::std::to_integer<unsigned char>(compound_shift(asc::std::byte{0x0c})) == (0x0cu >> 1));
static_assert(asc::std::to_integer<long>(asc::std::byte{200}) == 200L);
static_assert(static_cast<int>(asc::std::byte{7}) == 7);

// __fwd/array.h: forward declaration vocabulary only.
static_assert(!asc::std::__is_asc_std_array_v<int>);
static_assert(asc::std::__is_asc_std_array_v<asc::std::array<int, 4>>);
static_assert(!asc::std::__is_asc_std_array_v<asc::std::array<int, 4>&>);

// __fwd/span.h: extent constant and forward declaration vocabulary.
static_assert(asc::std::dynamic_extent == static_cast<asc::std::size_t>(-1));
static_assert(asc::std::is_same_v<decltype(asc::std::dynamic_extent), const asc::std::size_t>);
static_assert(!asc::std::__is_asc_std_span_v<double>);
static_assert(asc::std::__is_asc_std_span_v<asc::std::span<double, 8>>);
static_assert(asc::std::__is_asc_std_span_v<asc::std::span<double>>);

// __tuple/tuple_indices.h: index pack generation.
static_assert(asc::std::is_same_v<asc::std::__make_tuple_indices_t<3>, asc::std::__tuple_indices<0, 1, 2>>);
static_assert(asc::std::is_same_v<asc::std::__make_tuple_indices_t<3, 1>, asc::std::__tuple_indices<1, 2>>);
static_assert(asc::std::is_same_v<asc::std::__make_tuple_indices_t<0>, asc::std::__tuple_indices<>>);

// __tuple/tuple_size.h: value passthrough and cv qualification.
static_assert(asc::std::tuple_size_v<asc_stl_core_test::pair_like> == 2);
static_assert(asc::std::tuple_size_v<const asc_stl_core_test::pair_like> == 2);
static_assert(asc::std::tuple_size_v<volatile asc_stl_core_test::pair_like> == 2);
static_assert(asc::std::tuple_size_v<const volatile asc_stl_core_test::pair_like> == 2);

// __type_traits/is_callable.h: callability and noexcept callability.
struct callable_sum {
    CANN_ASC_STL_API int operator()(int left, int right) const noexcept
    {
        return left + right;
    }
};
struct throwing_callable {
    CANN_ASC_STL_API int operator()(int value) const noexcept(false)
    {
        return value;
    }
};
static_assert(asc::std::__is_callable_v<callable_sum, int, int>);
static_assert(!asc::std::__is_callable_v<callable_sum, int>);
static_assert(!asc::std::__is_callable_v<int, int>);
static_assert(asc::std::__is_callable_v<int (*)(int), int>);
static_assert(asc::std::__is_nothrow_callable_v<callable_sum, int, int>);
static_assert(!asc::std::__is_nothrow_callable_v<throwing_callable, int>);
static_assert(asc::std::__is_callable<callable_sum, int, int>::value);
static_assert(!asc::std::__is_nothrow_callable<throwing_callable, int>::value);

// __type_traits/is_extended_floating_point.h: no Ascend extended type is delivered.
static_assert(!asc::std::__is_extended_floating_point_v<float>);
static_assert(!asc::std::__is_extended_floating_point_v<double>);
static_assert(!asc::std::__is_extended_floating_point_v<long double>);
static_assert(!asc::std::__is_extended_floating_point_v<int>);
static_assert(!asc::std::__is_cv_extended_floating_point_v<const volatile float>);

// __type_traits/is_floating_point.h
static_assert(asc::std::is_floating_point_v<float>);
static_assert(asc::std::is_floating_point_v<double>);
static_assert(asc::std::is_floating_point_v<long double>);
static_assert(asc::std::is_floating_point_v<const volatile double>);
static_assert(!asc::std::is_floating_point_v<int>);
static_assert(!asc::std::is_floating_point_v<double&>);
static_assert(asc::std::is_floating_point<const float>::value);

// __type_traits/is_function.h
static_assert(asc::std::is_function_v<int(int)>);
static_assert(asc::std::is_function_v<void(int, double)>);
static_assert(asc::std::is_function<int(char)>::value);
static_assert(!asc::std::is_function_v<int>);
static_assert(!asc::std::is_function_v<int*>);
static_assert(!asc::std::is_function_v<int&>);
static_assert(!asc::std::is_function_v<decltype(&callable_sum::operator())>);

// __type_traits/is_integral.h
static_assert(asc::std::is_integral_v<bool>);
static_assert(asc::std::is_integral_v<char>);
static_assert(asc::std::is_integral_v<wchar_t>);
static_assert(asc::std::is_integral_v<short>);
static_assert(asc::std::is_integral_v<int>);
static_assert(asc::std::is_integral_v<long>);
static_assert(asc::std::is_integral_v<long long>);
static_assert(asc::std::is_integral_v<unsigned long>);
static_assert(asc::std::is_integral_v<const int>);
static_assert(asc::std::is_integral_v<volatile bool>);
static_assert(!asc::std::is_integral_v<float>);
static_assert(!asc::std::is_integral_v<int*>);
static_assert(!asc::std::is_integral_v<fixed_int_enum>);
static_assert(asc::std::is_integral<long>::value);
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
static_assert(asc::std::is_integral_v<char8_t>);
#endif

// __type_traits/is_pointer.h
static_assert(asc::std::is_pointer_v<int*>);
static_assert(asc::std::is_pointer_v<const int*>);
static_assert(asc::std::is_pointer_v<int* const>);
static_assert(asc::std::is_pointer_v<void (*)(int)>);
static_assert(!asc::std::is_pointer_v<int>);
static_assert(!asc::std::is_pointer_v<int&>);
static_assert(!asc::std::is_pointer_v<int[3]>);
static_assert(asc::std::is_pointer<char*>::value);

// __type_traits/is_referenceable.h
static_assert(asc::std::__is_referenceable<int>::value);
static_assert(asc::std::__is_referenceable<int&>::value);
static_assert(asc::std::__is_referenceable<empty>::value);
static_assert(asc::std::__is_referenceable<int(int)>::value);
static_assert(!asc::std::__is_referenceable<void>::value);

// __type_traits/is_signed_integer.h
static_assert(asc::std::__is_signed_integer_v<signed char>);
static_assert(asc::std::__is_signed_integer_v<short>);
static_assert(asc::std::__is_signed_integer_v<int>);
static_assert(asc::std::__is_signed_integer_v<long>);
static_assert(asc::std::__is_signed_integer_v<long long>);
static_assert(asc::std::__is_cv_signed_integer_v<const long long>);
static_assert(!asc::std::__is_signed_integer_v<unsigned int>);
static_assert(!asc::std::__is_signed_integer_v<float>);
static_assert(!asc::std::__is_cv_signed_integer_v<volatile unsigned char>);

// __type_traits/is_trivially_default_constructible.h
static_assert(asc::std::is_trivially_default_constructible_v<empty>);
static_assert(asc::std::is_trivially_default_constructible_v<int>);
static_assert(!asc::std::is_trivially_default_constructible_v<nontrivial_default>);
static_assert(asc::std::is_trivially_default_constructible<empty>::value);

// __type_traits/is_unsigned_integer.h
static_assert(asc::std::__is_unsigned_integer_v<unsigned char>);
static_assert(asc::std::__is_unsigned_integer_v<unsigned short>);
static_assert(asc::std::__is_unsigned_integer_v<unsigned int>);
static_assert(asc::std::__is_unsigned_integer_v<unsigned long>);
static_assert(asc::std::__is_unsigned_integer_v<unsigned long long>);
static_assert(asc::std::__is_cv_unsigned_integer_v<const unsigned long>);
static_assert(!asc::std::__is_unsigned_integer_v<int>);
static_assert(!asc::std::__is_unsigned_integer_v<double>);
static_assert(!asc::std::__is_cv_unsigned_integer_v<volatile signed char>);

// __type_traits/make_nbit_int.h
static_assert(sizeof(asc::std::__make_nbit_int_t<8>) == 1);
static_assert(sizeof(asc::std::__make_nbit_int_t<16>) == 2);
static_assert(sizeof(asc::std::__make_nbit_int_t<32>) == 4);
static_assert(sizeof(asc::std::__make_nbit_int_t<64>) == 8);
static_assert(asc::std::is_same_v<asc::std::__make_nbit_int_t<32>, int>);
static_assert(asc::std::is_same_v<asc::std::__make_nbit_uint_t<32>, unsigned int>);

// __type_traits/promote.h
static_assert(asc::std::is_same_v<asc::std::__promote_t<int>, double>);
static_assert(asc::std::is_same_v<asc::std::__promote_t<float>, float>);
static_assert(asc::std::is_same_v<asc::std::__promote_t<long double>, long double>);
static_assert(asc::std::is_same_v<asc::std::__promote_t<int, float>, double>);
static_assert(asc::std::is_same_v<asc::std::__promote_t<float, float>, float>);
static_assert(asc::std::is_same_v<asc::std::__promote_t<int, int>, double>);
static_assert(asc::std::is_same_v<asc::std::__promote_t<int, float, double>, double>);
static_assert(asc::std::__promote<int>::value);
static_assert(asc::std::__promote<int, float>::value);
static_assert(!asc::std::__promote<int*, float>::value);

// __type_traits/underlying_type.h
static_assert(asc::std::is_same_v<asc::std::underlying_type_t<fixed_int_enum>, int>);
static_assert(asc::std::is_same_v<asc::std::underlying_type_t<fixed_byte_enum>, unsigned char>);
static_assert(asc::std::is_same_v<asc::std::underlying_type<fixed_int_enum>::type, int>);

// __utility/convert_to_integral.h
static_assert(asc::std::__convert_to_integral(7) == 7);
static_assert(asc::std::__convert_to_integral(7u) == 7u);
static_assert(asc::std::__convert_to_integral(7L) == 7L);
static_assert(asc::std::__convert_to_integral(7uL) == 7uL);
static_assert(asc::std::__convert_to_integral(7LL) == 7LL);
static_assert(asc::std::__convert_to_integral(7uLL) == 7uLL);
static_assert(asc::std::__convert_to_integral(3.5) == 3LL);
static_assert(asc::std::__convert_to_integral(3.5f) == 3LL);
static_assert(asc::std::__convert_to_integral(fixed_int_two) == 2);
static_assert(asc::std::__convert_to_integral(plain_enum_b) == 1);

// __utility/integer_sequence.h
static_assert(asc::std::integer_sequence<int, 0, 1, 2>::size() == 3);
static_assert(asc::std::integer_sequence<int>::size() == 0);
static_assert(asc::std::is_same_v<asc::std::integer_sequence<int, 0, 1, 2>::value_type, int>);
static_assert(asc::std::is_same_v<asc::std::index_sequence<0, 1>, asc::std::integer_sequence<asc::std::size_t, 0, 1>>);
static_assert(asc::std::is_same_v<asc::std::make_integer_sequence<int, 3>, asc::std::integer_sequence<int, 0, 1, 2>>);
static_assert(asc::std::is_same_v<asc::std::make_index_sequence<2>, asc::std::index_sequence<0, 1>>);
static_assert(asc::std::is_same_v<asc::std::make_index_sequence<0>, asc::std::index_sequence<>>);
static_assert(asc::std::is_same_v<asc::std::index_sequence_for<int, float, empty>, asc::std::index_sequence<0, 1, 2>>);
static_assert(asc::std::tuple_size_v<asc::std::integer_sequence<int, 4, 5, 6>> == 3);
static_assert(asc::std::is_same_v<asc::std::tuple_element_t<1, asc::std::integer_sequence<int, 4, 5, 6>>, int>);

// __utility/priority_tag.h
static_assert(asc::std::is_base_of_v<asc::std::__priority_tag<2>, asc::std::__priority_tag<5>>);
static_assert(asc::std::is_same_v<asc::std::__priority_tag<0>, asc::std::__priority_tag<0>>);

// __utility/to_underlying.h
static_assert(asc::std::to_underlying(fixed_int_two) == 2);
static_assert(asc::std::to_underlying(fixed_byte_enum::fixed_byte_five) == 5);
static_assert(noexcept(asc::std::to_underlying(fixed_int_two)));
static_assert(asc::std::is_same_v<decltype(asc::std::to_underlying(fixed_int_two)), int>);

// asc/std/cstddef public aggregation.
static_assert(sizeof(asc::std::byte) == 1);
static_assert(asc::std::to_integer<int>(asc::std::byte{0xff}) == 255);
static_assert(asc::std::is_same_v<asc::std::nullptr_t, decltype(nullptr)>);
static_assert(asc::std::is_same_v<asc::std::size_t, ::size_t>);
static_assert(asc::std::is_same_v<asc::std::ptrdiff_t, ::ptrdiff_t>);
static_assert(asc::std::is_same_v<asc::std::max_align_t, ::max_align_t>);
static_assert(alignof(asc::std::max_align_t) >= alignof(long double));
static_assert(asc::std::is_same_v<decltype(offsetof(pair_like, first)), asc::std::size_t>);
static_assert(offsetof(pair_like, second) == sizeof(int));

CANN_ASC_STL_API constexpr int evaluate() noexcept
{
    // Runtime independent golden: plain unsigned arithmetic mirrors the byte operators.
    const unsigned int lhs = 0x0cu;
    const unsigned int rhs = 0x26u;
    const unsigned char via_byte = asc::std::to_integer<unsigned char>(asc::std::byte{0x0c} & asc::std::byte{0x26});
    const unsigned char golden = static_cast<unsigned char>(lhs & rhs);
    const int shifted = asc::std::to_integer<int>(asc::std::byte{0x03} << 3);
    const int shifted_golden = 0x03 << 3;
    const int underlying_value = asc::std::to_underlying(fixed_int_two);
    return via_byte == golden && shifted == shifted_golden && underlying_value == 2 ? 0 : 1;
}

}  // namespace asc_stl_core_test
#endif
