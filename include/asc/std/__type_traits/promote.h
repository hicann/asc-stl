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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_PROMOTE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_PROMOTE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
struct __numeric_type {
    // This fallback is used only in unevaluated overload resolution. CCE rejects
    // variadic AI Core functions, so it deliberately has no Device annotation.
    static void __test(...);
#if CANN_ASC_STL_DETAIL_HAS_FP16()
    CANN_ASC_STL_API static float __test(half);
#endif  // CANN_ASC_STL_DETAIL_HAS_FP16()
#if CANN_ASC_STL_DETAIL_HAS_BF16()
    CANN_ASC_STL_API static float __test(bfloat16_t);
#endif  // CANN_ASC_STL_DETAIL_HAS_BF16()
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

    using type = decltype(__test(declval<_Tp>()));
    static const bool value = !is_same_v<type, void>;
};

template <>
struct __numeric_type<void> {
    static const bool value = true;
};

template <class _A1, class _A2, class _A3>
struct __is_mixed_extended_floating_point {
    static constexpr bool value = false;
};

#if CANN_ASC_STL_DETAIL_HAS_FP16() && CANN_ASC_STL_DETAIL_HAS_BF16()
template <class _A1>
struct __is_mixed_extended_floating_point<_A1, half, bfloat16_t> {
    static constexpr bool value = true;
};

template <class _A1>
struct __is_mixed_extended_floating_point<_A1, bfloat16_t, half> {
    static constexpr bool value = true;
};

template <class _A1>
struct __is_mixed_extended_floating_point<half, _A1, bfloat16_t> {
    static constexpr bool value = true;
};

template <class _A1>
struct __is_mixed_extended_floating_point<bfloat16_t, _A1, half> {
    static constexpr bool value = true;
};

template <class _A1>
struct __is_mixed_extended_floating_point<half, bfloat16_t, _A1> {
    static constexpr bool value = true;
};

template <class _A1>
struct __is_mixed_extended_floating_point<bfloat16_t, half, _A1> {
    static constexpr bool value = true;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_FP16() && CANN_ASC_STL_DETAIL_HAS_BF16()

template <class _A1, class _A2 = void, class _A3 = void,
    bool = __numeric_type<_A1>::value && __numeric_type<_A2>::value && __numeric_type<_A3>::value &&
        !__is_mixed_extended_floating_point<_A1, _A2, _A3>::value>
class __promote_imp {
public:
    static const bool value = false;
};

template <class _A1, class _A2, class _A3>
class __promote_imp<_A1, _A2, _A3, true> {
private:
    using __type1 = typename __promote_imp<_A1>::type;
    using __type2 = typename __promote_imp<_A2>::type;
    using __type3 = typename __promote_imp<_A3>::type;

public:
    using type = decltype(__type1() + __type2() + __type3());
    static const bool value = true;
};

template <class _A1, class _A2>
class __promote_imp<_A1, _A2, void, true> {
private:
    using __type1 = typename __promote_imp<_A1>::type;
    using __type2 = typename __promote_imp<_A2>::type;

public:
    using type = decltype(__type1() + __type2());
    static const bool value = true;
};

template <class _A1>
class __promote_imp<_A1, void, void, true> {
public:
    using type = typename __numeric_type<_A1>::type;
    static const bool value = true;
};

template <class _A1, class _A2 = void, class _A3 = void>
class __promote : public __promote_imp<_A1, _A2, _A3> {};

template <class _A1, class _A2 = void, class _A3 = void>
using __promote_t = typename __promote<_A1, _A2, _A3>::type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_PROMOTE_H
