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

#ifndef LIBASCENDCXX_INCLUDE_ASC_STD___ALGORITHM_CLAMP_H_
#define LIBASCENDCXX_INCLUDE_ASC_STD___ALGORITHM_CLAMP_H_

#include <asc/std/detail/__config>

_ACCL_STD_BEGIN

template <typename _Tp>
_ASC_API constexpr const _Tp& clamp(const _Tp& __value, const _Tp& __low, const _Tp& __high)
{
    return (__value < __low) ? __low : (__high < __value) ? __high : __value;
}

template <typename _Tp, typename _Compare>
_ASC_API constexpr const _Tp& clamp(const _Tp& __value, const _Tp& __low, const _Tp& __high, _Compare __compare)
{
    return __compare(__value, __low) ? __low : __compare(__high, __value) ? __high : __value;
}

_ACCL_STD_END

#endif  // LIBASCENDCXX_INCLUDE_ASC_STD___ALGORITHM_CLAMP_H_
