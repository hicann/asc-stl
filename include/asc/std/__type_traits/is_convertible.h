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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONVERTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONVERTIBLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_convertible_to)

template <class T1, class T2>
struct is_convertible : integral_constant<bool, __is_convertible_to(T1, T2)> {};

template <class T1, class T2>
inline constexpr bool is_convertible_v = __is_convertible_to(T1, T2);

#else

namespace __is_convertible_imp {
template <class Tp>
CANN_ASC_STL_API void __test_convert(Tp);

template <class From, class To, class = void>
struct __is_convertible_test : public false_type {};

template <class From, class To>
struct __is_convertible_test<From, To,
    decltype(asc::std::__is_convertible_imp::__test_convert<To>(asc::std::declval<From>()))> : public true_type {};

template <class Tp, bool IsArray = is_array_v<Tp>, bool IsFunction = is_function_v<Tp>, bool IsVoid = is_void_v<Tp> >
struct __is_array_function_or_void {
    enum { value = 0 };
};
template <class Tp>
struct __is_array_function_or_void<Tp, true, false, false> {
    enum { value = 1 };
};
template <class Tp>
struct __is_array_function_or_void<Tp, false, true, false> {
    enum { value = 2 };
};
template <class Tp>
struct __is_array_function_or_void<Tp, false, false, true> {
    enum { value = 3 };
};
}  // namespace __is_convertible_imp

template <class Tp, unsigned = __is_convertible_imp::__is_array_function_or_void<remove_reference_t<Tp> >::value>
struct __is_convertible_check {
    static const size_t __v = 0;
};

template <class Tp>
struct __is_convertible_check<Tp, 0> {
    static const size_t __v = sizeof(Tp);
};

template <class T1, class T2,
    unsigned T1IsArrayFunctionOrVoid = __is_convertible_imp::__is_array_function_or_void<T1>::value,
    unsigned T2IsArrayFunctionOrVoid = __is_convertible_imp::__is_array_function_or_void<T2>::value>
struct __is_convertible_fallback
    : public integral_constant<bool, __is_convertible_imp::__is_convertible_test<T1, T2>::value> {};

template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 0, 1> : public false_type {};
template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 1, 1> : public false_type {};
template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 2, 1> : public false_type {};
template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 3, 1> : public false_type {};

template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 0, 2> : public false_type {};
template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 1, 2> : public false_type {};
template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 2, 2> : public false_type {};
template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 3, 2> : public false_type {};

template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 0, 3> : public false_type {};
template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 1, 3> : public false_type {};
template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 2, 3> : public false_type {};
template <class T1, class T2>
struct __is_convertible_fallback<T1, T2, 3, 3> : public true_type {};

template <class T1, class T2>
struct is_convertible : public __is_convertible_fallback<T1, T2> {
    static const size_t __complete_check1 = __is_convertible_check<T1>::__v;
    static const size_t __complete_check2 = __is_convertible_check<T2>::__v;
};

template <class From, class To>
inline constexpr bool is_convertible_v = is_convertible<From, To>::value;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONVERTIBLE_H
