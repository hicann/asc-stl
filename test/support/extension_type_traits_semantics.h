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

#ifndef ASC_STL_TEST_EXTENSION_TYPE_TRAITS_SEMANTICS_H
#define ASC_STL_TEST_EXTENSION_TYPE_TRAITS_SEMANTICS_H

#include <asc/type_traits>

namespace traits_test {
struct Forward;
union ForwardUnion;
struct Plain {
    unsigned value;
};
struct Resource {
    ~Resource()
    {}
};
struct SelfReference {
    int value;
    int* self;
    SelfReference() : value(0), self(&value)
    {}
};
struct DeletedMove {
    DeletedMove() = default;
    DeletedMove(const DeletedMove&) = default;
    DeletedMove(DeletedMove&&) = delete;
};
struct UserId {
    unsigned value;
    friend CANN_ASC_STL_API constexpr bool operator==(const UserId& a, const UserId& b) noexcept
    {
        return a.value == b.value;
    }
};
struct UserValue {
    unsigned value;
};
enum class Enum : unsigned { zero, one };
using Function = void();
}  // namespace traits_test

namespace asc {
template <>
struct is_bitwise_comparable<traits_test::UserId> : std::true_type {};
template <>
struct is_trivially_relocatable<traits_test::UserValue> : std::true_type {};
}  // namespace asc

namespace traits_test {

// The Host launch/preparation phase in a pure-SIMT unit can also use the
// documented Boolean object operations, rather than just reading ::value.
constexpr bool host_boolean_form()
{
    return asc::is_low_precision<asc::float16>{}() && static_cast<bool>(asc::is_low_precision<asc::float16>{}) &&
        !asc::is_low_precision<int>{}();
}
static_assert(host_boolean_form());

template <class T, bool Floating, bool Packed>
CANN_ASC_STL_HOST_DEVICE constexpr bool wrapper()
{
    static_assert(asc::is_low_precision_v<T>);
    static_assert(asc::is_low_precision_v<const volatile T>);
    static_assert(!asc::is_low_precision_v<T&> && !asc::is_low_precision_v<T&&>);
    static_assert(!asc::is_low_precision_v<T*> && !asc::is_low_precision_v<T[2]>);
    static_assert(asc::is_extended_floating_point_v<T> == Floating);
    static_assert(asc::is_extended_floating_point_v<const volatile T> == Floating);
    static_assert(!asc::is_extended_floating_point_v<T&>);
    static_assert(asc::is_packed_numeric_v<T> == Packed);
    static_assert(asc::is_packed_numeric_v<const volatile T> == Packed);
    static_assert(!asc::is_packed_numeric_v<T[]>);
    static_assert(!asc::is_bitwise_comparable_v<T>);
    static_assert(asc::is_trivially_relocatable_v<T>);
    static_assert(!asc::is_trivially_relocatable_v<const T>);
    static_assert(!asc::is_trivially_relocatable_v<volatile T>);
    static_assert(!asc::is_trivially_relocatable_v<T&>);
    static_assert(asc::std::is_same_v<typename asc::is_low_precision<T>::value_type, bool>);
    static_assert(asc::std::is_same_v<typename asc::is_low_precision<T>::type, asc::std::true_type>);
    static_assert(asc::is_low_precision<T>{}() && static_cast<bool>(asc::is_low_precision<T>{}));
    static_assert(asc::is_low_precision_v<T> == asc::is_low_precision<T>::value);
    static_assert(asc::is_extended_floating_point_v<T> == asc::is_extended_floating_point<T>::value);
    static_assert(asc::is_packed_numeric_v<T> == asc::is_packed_numeric<T>::value);
    static_assert(asc::is_bitwise_comparable_v<T> == asc::is_bitwise_comparable<T>::value);
    static_assert(asc::is_trivially_relocatable_v<T> == asc::is_trivially_relocatable<T>::value);
    return true;
}

static_assert(wrapper<asc::float16, true, false>());
static_assert(wrapper<asc::bfloat16, true, false>());
static_assert(wrapper<asc::float8_e4m3fn, true, false>());
static_assert(wrapper<asc::float8_e5m2, true, false>());
static_assert(wrapper<asc::hifloat8, true, false>());
static_assert(wrapper<asc::float8_e8m0, false, false>());
static_assert(wrapper<asc::float4_e2m1x2, false, true>());
static_assert(wrapper<asc::float4_e1m2x2, false, true>());
static_assert(wrapper<asc::int4, false, false>());
static_assert(wrapper<asc::int4x2, false, true>());

template <class T>
CANN_ASC_STL_HOST_DEVICE constexpr bool excluded()
{
    static_assert(!asc::is_low_precision_v<T>);
    static_assert(!asc::is_extended_floating_point_v<T>);
    static_assert(!asc::is_packed_numeric_v<T>);
    static_assert(!asc::is_address_space_qualified_v<T>);
    return true;
}
static_assert(excluded<bool>() && excluded<char>() && excluded<int>() && excluded<unsigned char>());
static_assert(excluded<float>() && excluded<double>() && excluded<long double>());
static_assert(excluded<Enum>() && excluded<Plain>() && excluded<Forward>() && excluded<ForwardUnion>());
static_assert(excluded<void>() && excluded<Function>() && excluded<asc::float16[2]>());

static_assert(asc::is_bitwise_comparable_v<unsigned char>);
static_assert(asc::is_bitwise_comparable_v<const unsigned char>);
static_assert(!asc::is_bitwise_comparable_v<bool>);
static_assert(!asc::is_bitwise_comparable_v<float> && !asc::is_bitwise_comparable_v<Enum>);
static_assert(!asc::is_bitwise_comparable_v<Plain> && !asc::is_bitwise_comparable_v<Function>);
static_assert(!asc::is_bitwise_comparable_v<volatile unsigned char>);
static_assert(!asc::is_bitwise_comparable_v<const volatile unsigned char>);
static_assert(!asc::is_bitwise_comparable_v<int&> && !asc::is_bitwise_comparable_v<int*>);
static_assert(!asc::is_bitwise_comparable_v<Forward*> && !asc::is_bitwise_comparable_v<Forward&>);
static_assert(!asc::is_bitwise_comparable_v<Forward[]> && !asc::is_bitwise_comparable_v<void>);

static_assert(asc::is_trivially_relocatable_v<int> && asc::is_trivially_relocatable_v<float>);
static_assert(asc::is_trivially_relocatable_v<Enum> && asc::is_trivially_relocatable_v<decltype(nullptr)>);
static_assert(asc::is_trivially_relocatable_v<Forward*>);
static_assert(asc::is_trivially_relocatable_v<int Plain::*>);
static_assert(asc::std::is_trivially_copyable_v<Plain> && !asc::is_trivially_relocatable_v<Plain>);
static_assert(asc::std::is_trivially_copyable_v<SelfReference> && !asc::is_trivially_relocatable_v<SelfReference>);
static_assert(asc::std::is_trivially_copyable_v<DeletedMove>);
static_assert(!asc::std::is_trivially_move_constructible_v<DeletedMove>);
static_assert(!asc::is_trivially_relocatable_v<DeletedMove> && !asc::is_trivially_relocatable_v<Resource>);
static_assert(!asc::is_trivially_relocatable_v<const int> && !asc::is_trivially_relocatable_v<volatile int>);
static_assert(!asc::is_trivially_relocatable_v<int&> && !asc::is_trivially_relocatable_v<int[3]>);
static_assert(!asc::is_trivially_relocatable_v<Forward&> && !asc::is_trivially_relocatable_v<Forward[]>);
static_assert(!asc::is_trivially_relocatable_v<void> && !asc::is_trivially_relocatable_v<Function>);
static_assert(asc::is_bitwise_comparable_v<const UserId> && !asc::is_bitwise_comparable_v<volatile UserId>);
static_assert(asc::is_trivially_relocatable_v<UserValue> && !asc::is_trivially_relocatable_v<const UserValue>);
static_assert(asc::std::is_trivially_copyable_v<UserValue>);
static_assert(asc::std::is_trivially_move_constructible_v<UserValue>);
static_assert(asc::std::is_trivially_destructible_v<UserValue>);
static_assert(asc::std::has_unique_object_representations_v<UserId>);

// No completeness-dependent classification is cached while Forward is incomplete.
struct Forward {
    unsigned value;
};
union ForwardUnion {
    unsigned value;
};
static_assert(excluded<Forward>() && excluded<ForwardUnion>());
static_assert(!asc::is_trivially_relocatable_v<Forward>);
static_assert(!asc::is_bitwise_comparable_v<ForwardUnion>);

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && defined(__NPU_ARCH__) && __NPU_ARCH__ == 3510 && \
    defined(__BISHENG_CCEC__) && __clang_major__ == 15
template <class T, bool Floating, bool Packed>
CANN_ASC_STL_HOST_DEVICE constexpr bool native()
{
    static_assert(asc::is_low_precision_v<T>);
    static_assert(asc::is_extended_floating_point_v<T> == Floating);
    static_assert(asc::is_packed_numeric_v<T> == Packed);
    static_assert(!asc::is_bitwise_comparable_v<T>);
    return true;
}
static_assert(native<half, true, false>() && native<bfloat16_t, true, false>());
static_assert(native<float8_e4m3_t, true, false>() && native<float8_e5m2_t, true, false>());
static_assert(native<hifloat8_t, true, false>() && native<float8_e8m0_t, false, false>());
static_assert(native<float4_e2m1x2_t, false, true>() && native<float4_e1m2x2_t, false, true>());
static_assert(asc::is_trivially_relocatable_v<half> && asc::is_trivially_relocatable_v<float8_e4m3_t>);
static_assert(!asc::is_low_precision_v<::int4>);
#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
static_assert(native<int4x2_t, false, true>());
// SDK 9.2 uses a nontrivial class; newer SDKs expose a distinct builtin.
static_assert(asc::is_trivially_relocatable_v<int4x2_t> == !asc::std::is_class_v<int4x2_t>);
#endif
#endif

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION() && defined(__NPU_ARCH__) && __NPU_ARCH__ == 3510 && \
    defined(__BISHENG_CCEC__) && __clang_major__ == 15
using Gm = __gm__ int*;
using Ub = const volatile __ubuf__ int*;
static_assert(asc::is_address_space_qualified_v<Gm>);
static_assert(asc::is_trivially_relocatable_v<Gm>);
static_assert(!asc::is_bitwise_comparable_v<Gm>);
static_assert(!asc::is_low_precision_v<Gm>);
static_assert(asc::is_address_space_qualified_v<const Gm&>);
static_assert(asc::is_address_space_qualified_v<volatile Gm&&>);
static_assert(asc::is_address_space_qualified_v<Ub>);
static_assert(asc::is_address_space_qualified_v<__gm__ void*>);
static_assert(asc::is_address_space_qualified_v<__ubuf__ Forward*>);
static_assert(!asc::is_address_space_qualified_v<Gm*>);
static_assert(asc::is_address_space_qualified_v<__gm__ Gm*>);
static_assert(!asc::is_address_space_qualified_v<__gm__ int>);
static_assert(asc::is_address_space_qualified<Gm>::value == asc::is_address_space_qualified_v<Gm>);
#else
static_assert(!asc::is_address_space_qualified_v<int*>);
#endif

}  // namespace traits_test
#endif  // ASC_STL_TEST_EXTENSION_TYPE_TRAITS_SEMANTICS_H
