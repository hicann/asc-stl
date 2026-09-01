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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_RESULT_OF_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_RESULT_OF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_TYPE_TRAITS)
template <class _Callable>
class result_of;

template <class _Fp, class... _Args>
class ASC_DEPRECATED result_of<_Fp(_Args...)> : public invoke_result<_Fp, _Args...> {};

template <class _Tp>
using result_of_t ASC_DEPRECATED = typename result_of<_Tp>::type;
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_TYPE_TRAITS)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_RESULT_OF_H
