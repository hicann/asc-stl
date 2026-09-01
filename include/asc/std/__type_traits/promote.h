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

CANN_ASC_STL_BEGIN_NAMESPACE

struct __numeric_test {
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
};

template <class...>
using __numeric_void_t = void;

template <class T, class = void>
struct __numeric_type {
    static const bool value = false;
};

template <class T>
struct __numeric_type<T, __numeric_void_t<decltype(__numeric_test::__test(asc::std::declval<T>()))>> {
    using type = decltype(__numeric_test::__test(asc::std::declval<T>()));
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
