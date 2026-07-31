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

#ifndef LIBASCENDCXX_INCLUDE_ASC_STD___TYPE_TRAITS_INTEGRAL_CONSTANT_H_
#define LIBASCENDCXX_INCLUDE_ASC_STD___TYPE_TRAITS_INTEGRAL_CONSTANT_H_

#include <asc/std/detail/__config>

_ACCL_STD_BEGIN

template <class _Tp, _Tp __v>
struct integral_constant {
    static constexpr _Tp value = __v;
    using value_type = _Tp;
    using type = integral_constant;

    _ASC_API constexpr operator value_type() const noexcept
    {
        return value;
    }
    _ASC_API constexpr value_type operator()() const noexcept
    {
        return value;
    }
};

template <bool __v>
using bool_constant = integral_constant<bool, __v>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

_ACCL_STD_END

#endif  // LIBASCENDCXX_INCLUDE_ASC_STD___TYPE_TRAITS_INTEGRAL_CONSTANT_H_
