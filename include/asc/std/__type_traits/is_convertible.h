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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONVERTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONVERTIBLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONVERTIBLE_TO) && !defined(CANN_ASC_STL_DETAIL_USE_IS_CONVERTIBLE_FALLBACK)

template <class _From, class _To>
struct is_convertible : integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_IS_CONVERTIBLE_TO(_From, _To)> {};

template <class _From, class _To>
inline constexpr bool is_convertible_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_CONVERTIBLE_TO(_From, _To);

#else

namespace __is_convertible_imp {
template <class _Tp>
CANN_ASC_STL_API void __test_convert(_Tp);

template <class _From, class _To, class = void>
struct __is_convertible_test : false_type {};

template <class _From, class _To>
struct __is_convertible_test<_From, _To, decltype(__test_convert<_To>(declval<_From>()))> : true_type {};

template <class _Tp, bool = is_array_v<_Tp>, bool = is_function_v<_Tp>, bool = is_void_v<_Tp> >
struct __is_array_function_or_void : integral_constant<unsigned, 0> {};

template <class _Tp>
struct __is_array_function_or_void<_Tp, true, false, false> : integral_constant<unsigned, 1> {};

template <class _Tp>
struct __is_array_function_or_void<_Tp, false, true, false> : integral_constant<unsigned, 2> {};

template <class _Tp>
struct __is_array_function_or_void<_Tp, false, false, true> : integral_constant<unsigned, 3> {};
}  // namespace __is_convertible_imp

template <class _Tp, unsigned = __is_convertible_imp::__is_array_function_or_void<remove_reference_t<_Tp> >::value>
struct __is_convertible_check {
    static constexpr size_t __v = 0;
};

template <class _Tp>
struct __is_convertible_check<_Tp, 0> {
    static constexpr size_t __v = sizeof(_Tp);
};

template <class _From, class _To, unsigned = __is_convertible_imp::__is_array_function_or_void<_From>::value,
    unsigned = __is_convertible_imp::__is_array_function_or_void<_To>::value>
struct __is_convertible_fallback : __is_convertible_imp::__is_convertible_test<_From, _To> {};

template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 0, 1> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 1, 1> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 2, 1> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 3, 1> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 0, 2> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 1, 2> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 2, 2> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 3, 2> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 0, 3> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 1, 3> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 2, 3> : false_type {};
template <class _From, class _To>
struct __is_convertible_fallback<_From, _To, 3, 3> : true_type {};

template <class _From, class _To>
struct is_convertible : __is_convertible_fallback<_From, _To> {
    static constexpr size_t __complete_check1 = __is_convertible_check<_From>::__v;
    static constexpr size_t __complete_check2 = __is_convertible_check<_To>::__v;
};

template <class _From, class _To>
inline constexpr bool is_convertible_v = is_convertible<_From, _To>::value;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONVERTIBLE_H
