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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_IN_OUT_RESULT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_IN_OUT_RESULT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
template <class Input, class Output>
struct in_out_result {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS Input in;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS Output out;

    CANN_ASC_STL_DETAIL_TEMPLATE(class OtherInput, class OtherOutput)
    CANN_ASC_STL_DETAIL_REQUIRES(convertible_to<Input const&, OtherInput>&& convertible_to<Output const&, OtherOutput>)
    CANN_ASC_STL_API constexpr operator in_out_result<OtherInput, OtherOutput>() const&
    {
        return {in, out};
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class OtherInput, class OtherOutput)
    CANN_ASC_STL_DETAIL_REQUIRES(convertible_to<Input, OtherInput>&& convertible_to<Output, OtherOutput>)
    CANN_ASC_STL_API constexpr operator in_out_result<OtherInput, OtherOutput>() &&
    {
        return {::asc::std::move(in), ::asc::std::move(out)};  // NOLINT(build/include_what_you_use)
    }
};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_IN_OUT_RESULT_H
