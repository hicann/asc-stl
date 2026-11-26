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

#include <asc/std/cfloat>

#include <limits>

#define CHECK_FORMAT(prefix, T)                                                   \
    static_assert(prefix##_MANT_DIG == std::numeric_limits<T>::digits);           \
    static_assert(prefix##_DIG == std::numeric_limits<T>::digits10);              \
    static_assert(prefix##_MIN_EXP == std::numeric_limits<T>::min_exponent);      \
    static_assert(prefix##_MAX_EXP == std::numeric_limits<T>::max_exponent);      \
    static_assert(prefix##_MIN_10_EXP == std::numeric_limits<T>::min_exponent10); \
    static_assert(prefix##_MAX_10_EXP == std::numeric_limits<T>::max_exponent10); \
    static_assert(prefix##_MIN == std::numeric_limits<T>::min());                 \
    static_assert(prefix##_MAX == std::numeric_limits<T>::max());                 \
    static_assert(prefix##_EPSILON == std::numeric_limits<T>::epsilon());         \
    static_assert(prefix##_DECIMAL_DIG == std::numeric_limits<T>::max_digits10);  \
    static_assert(prefix##_TRUE_MIN == std::numeric_limits<T>::denorm_min());     \
    static_assert(prefix##_HAS_SUBNORM == std::numeric_limits<T>::has_denorm)

CHECK_FORMAT(FLT, float);
CHECK_FORMAT(DBL, double);
CHECK_FORMAT(LDBL, long double);
static_assert(FLT_RADIX == std::numeric_limits<float>::radix);

int main()
{
    static_assert(DECIMAL_DIG >= 10);
    static_assert(FLT_EVAL_METHOD >= -1);
    const int mode = FLT_ROUNDS;
    return mode < -1 || mode > 3;
}
