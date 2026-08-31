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

#include <asc/std/__floating_point/properties.h>

using asc::std::__fp_format;

static_assert(asc::std::__fp_is_signed_v<__fp_format::__binary16>);
static_assert(!asc::std::__fp_is_signed_v<__fp_format::__fp8_e8m0>);
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__binary16> == 5);
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__binary32> == 8);
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__binary64> == 11);
static_assert(asc::std::__fp_exp_nbits_v<__fp_format::__bfloat16> == 8);
static_assert(asc::std::__fp_exp_min_v<__fp_format::__binary16> == -14);
static_assert(asc::std::__fp_exp_max_v<__fp_format::__binary16> == 15);
static_assert(asc::std::__fp_digits_v<__fp_format::__binary16> == 11);
static_assert(asc::std::__fp_digits_v<__fp_format::__binary32> == 24);
static_assert(asc::std::__fp_digits_v<__fp_format::__bfloat16> == 8);
static_assert(asc::std::__fp_has_denorm_v<__fp_format::__fp8_e4m3>);
static_assert(!asc::std::__fp_has_denorm_v<__fp_format::__fp8_e8m0>);
static_assert(!asc::std::__fp_has_inf_v<__fp_format::__fp8_e4m3>);
static_assert(asc::std::__fp_has_nan_v<__fp_format::__fp8_e4m3>);
static_assert(!asc::std::__fp_has_nans_v<__fp_format::__fp8_e4m3>);

int main()
{
    return 0;
}
