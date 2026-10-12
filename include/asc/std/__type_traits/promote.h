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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_PROMOTE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_PROMOTE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/declval.h>

// Inline equivalents of the dev extended-data-type capability gates (dev
// __asc/extended_data_types.h; the base __config does not provide them; same
// inline copies as __type_traits/is_extended_floating_point.h). half and
// bfloat16_t are baseline CCE scalar types, so they are available in every ASC
// device compilation mode.
#if !defined(CANN_ASC_STL_DETAIL_HAS_HALF)
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_HAS_HALF() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_HALF() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF

#if !defined(CANN_ASC_STL_DETAIL_HAS_BFLOAT16)
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_HAS_BFLOAT16() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_BFLOAT16() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16

// Inline equivalent of the dev CANN_ASC_STL_DETAIL_HAS_FLOAT128() gate:
// __float128 needs __int128, a Linux non-ARM64 target, a compiler that
// advertises the type, host compilation only (CCE device compilation does not
// support __float128), and GCC must not run strict-ANSI without extended
// numeric literals (no q/Q floating point literals under __STRICT_ANSI__).
#if !defined(CANN_ASC_STL_DETAIL_HAS_FLOAT128)
#define CANN_ASC_STL_DETAIL_HAS_FLOAT128() 0
#if (defined(__SIZEOF_FLOAT128__) || defined(__FLOAT128__)) && defined(__SIZEOF_INT128__) &&                         \
    (defined(__linux__) || defined(__LP64__)) &&                                                                     \
    !(defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC)) && !defined(ASC_DISABLE_FLOAT128_SUPPORT) && \
    !defined(ASC_DISABLE_INT128_SUPPORT) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() &&                             \
    !(defined(__GNUC__) && !defined(__clang__) && defined(__STRICT_ANSI__) &&                                        \
        !defined(ASC_GCC_HAS_EXTENDED_NUMERIC_LITERALS))
#undef CANN_ASC_STL_DETAIL_HAS_FLOAT128
#define CANN_ASC_STL_DETAIL_HAS_FLOAT128() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __numeric_type {
    // This fallback is used only in unevaluated overload resolution. CCE rejects
    // variadic AI Core functions, so it deliberately has no Device annotation.
    static void __test(...);
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    CANN_ASC_STL_API static float __test(half);
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF()
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
    CANN_ASC_STL_API static float __test(bfloat16_t);
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
    CANN_ASC_STL_API static float __test(float);
    CANN_ASC_STL_API static double __test(char);
    CANN_ASC_STL_API static double __test(int);
    CANN_ASC_STL_API static double __test(unsigned);
    CANN_ASC_STL_API static double __test(long);
    CANN_ASC_STL_API static double __test(unsigned long);
    CANN_ASC_STL_API static double __test(long long);
    CANN_ASC_STL_API static double __test(unsigned long long);
    CANN_ASC_STL_API static double __test(double);
    CANN_ASC_STL_API static long double __test(long double);
#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
    CANN_ASC_STL_API static __float128 __test(__float128);
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128()

    using type = decltype(__test(asc::std::declval<T>()));
    static const bool value = !is_same_v<type, void>;
};

template <>
struct __numeric_type<void> {
    static const bool value = true;
};

template <class A1, class A2, class A3>
struct __is_mixed_extended_floating_point {
    static constexpr bool value = false;
};

#if CANN_ASC_STL_DETAIL_HAS_HALF() && CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
template <class A1>
struct __is_mixed_extended_floating_point<A1, half, bfloat16_t> {
    static constexpr bool value = true;
};

template <class A1>
struct __is_mixed_extended_floating_point<A1, bfloat16_t, half> {
    static constexpr bool value = true;
};

template <class A1>
struct __is_mixed_extended_floating_point<half, A1, bfloat16_t> {
    static constexpr bool value = true;
};

template <class A1>
struct __is_mixed_extended_floating_point<bfloat16_t, A1, half> {
    static constexpr bool value = true;
};

template <class A1>
struct __is_mixed_extended_floating_point<half, bfloat16_t, A1> {
    static constexpr bool value = true;
};

template <class A1>
struct __is_mixed_extended_floating_point<bfloat16_t, half, A1> {
    static constexpr bool value = true;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF() && CANN_ASC_STL_DETAIL_HAS_BFLOAT16()

template <class A1, class A2 = void, class A3 = void,
    bool = __numeric_type<A1>::value && __numeric_type<A2>::value && __numeric_type<A3>::value &&
        !__is_mixed_extended_floating_point<A1, A2, A3>::value>
class __promote_imp {
public:
    static const bool value = false;
};

template <class A1, class A2, class A3>
class __promote_imp<A1, A2, A3, true> {
private:
    using __type1 = typename __promote_imp<A1>::type;
    using __type2 = typename __promote_imp<A2>::type;
    using __type3 = typename __promote_imp<A3>::type;

public:
    using type = decltype(__type1() + __type2() + __type3());
    static const bool value = true;
};

template <class A1, class A2>
class __promote_imp<A1, A2, void, true> {
private:
    using __type1 = typename __promote_imp<A1>::type;
    using __type2 = typename __promote_imp<A2>::type;

public:
    using type = decltype(__type1() + __type2());
    static const bool value = true;
};

template <class A1>
class __promote_imp<A1, void, void, true> {
public:
    using type = typename __numeric_type<A1>::type;
    static const bool value = true;
};

template <class A1, class A2 = void, class A3 = void>
class __promote : public __promote_imp<A1, A2, A3> {};

template <class A1, class A2 = void, class A3 = void>
using __promote_t = typename __promote<A1, A2, A3>::type;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_PROMOTE_H
