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

#ifndef CANN_ASC_STL_STD_DETAIL_NEW_LAUNDER_H
#define CANN_ASC_STL_STD_DETAIL_NEW_LAUNDER_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cv.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp* launder(_Tp* __p) noexcept
{
    static_assert(!is_function_v<_Tp>, "can't launder functions");
    static_assert(!is_same_v<void, remove_cv_t<_Tp>>, "can't launder cv-void");
#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_launder) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 7) || \
    CANN_ASC_STL_DETAIL_COMPILER(MSVC)
    return __builtin_launder(__p);
#else
    return __p;
#endif
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_NEW_LAUNDER_H
