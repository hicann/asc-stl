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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_POINTER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_POINTER_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER) && \
    !defined(CANN_ASC_STL_DETAIL_ACCL_USE_REMOVE_POINTER_FALLBACK)
template <class _Tp>
struct remove_pointer {
    using type = CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER(_Tp);
};

template <class _Tp>
using remove_pointer_t = CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER(_Tp);

#else
template <class _Tp>
struct remove_pointer {
    using type = _Tp;
};
template <class _Tp>
struct remove_pointer<_Tp*> {
    using type = _Tp;
};
template <class _Tp>
struct remove_pointer<_Tp* const> {
    using type = _Tp;
};
template <class _Tp>
struct remove_pointer<_Tp* volatile> {
    using type = _Tp;
};
template <class _Tp>
struct remove_pointer<_Tp* const volatile> {
    using type = _Tp;
};

template <class _Tp>
using remove_pointer_t = typename remove_pointer<_Tp>::type;

#endif  // defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER) &&
        // !defined(CANN_ASC_STL_DETAIL_ACCL_USE_REMOVE_POINTER_FALLBACK)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_POINTER_H
