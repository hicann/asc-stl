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

#include <cmath>
#include <complex>
#include <cstdio>
#include <type_traits>
#include <utility>

#include "device_checks.h"

using float_complex = asc::std::complex<float>;
static_assert(asc::std::tuple_size<float_complex>::value == 2);
static_assert(std::is_same_v<asc::std::tuple_element<0, float_complex>::type, float> &&
    std::is_same_v<asc::std::tuple_element<1, float_complex>::type, float>);
bool close(asc::std::complex<float> a, std::complex<double> b)
{
    // Values are bounded and away from poles. Allow rounding in the float elementary functions.
    const auto within = [](float actual, double ref) {
        return std::abs(actual - ref) <= 0.000004 * (1 + std::abs(ref));
    };
    return within(a.real(), b.real()) && within(a.imag(), b.imag());
}

#define CHECK_COMPLEX(name)                                   \
    do {                                                      \
        if (!close(asc::std::name(a), std::name(b))) {        \
            std::fprintf(stderr, "%s(%g,%g)\n", #name, x, y); \
            return false;                                     \
        }                                                     \
    } while (false)

bool check_point(float x, float y)
{
    const asc::std::complex<float> a(x, y);
    const std::complex<double> b(x, y);
    CHECK_COMPLEX(sin);
    CHECK_COMPLEX(cos);
    CHECK_COMPLEX(tan);
    CHECK_COMPLEX(asin);
    CHECK_COMPLEX(acos);
    CHECK_COMPLEX(atan);
    CHECK_COMPLEX(sinh);
    CHECK_COMPLEX(cosh);
    CHECK_COMPLEX(tanh);
    CHECK_COMPLEX(asinh);
    CHECK_COMPLEX(acosh);
    CHECK_COMPLEX(atanh);
    CHECK_COMPLEX(exp);
    CHECK_COMPLEX(log);
    CHECK_COMPLEX(log10);
    CHECK_COMPLEX(sqrt);
    if (!close(asc::std::pow(a, 2.0F), b * b) || !close(asc::std::pow(2.0F, a), std::pow(2.0, b)))
        return false;
    return close(
        asc::std::pow(a, asc::std::complex<float>(0.5F, -0.25F)), std::pow(b, std::complex<double>(0.5, -0.25)));
}

int main()
{
    if (const int error = asc_stl_test_complex::check())
        return error;
    if (asc::std::real(2) != 2.0 || asc::std::imag(-1) != 0.0)
        return 13;
    const float values[] = {-1.5F, -0.75F, -0.125F, 0.125F, 0.75F, 1.5F};
    for (float x : values) {
        for (float y : values) {
            if (!check_point(x, y))
                return 10;
        }
    }
    using z = asc::std::complex<float>;
    const z original(-2, 7);
    z copied(original);
    z moved(std::move(copied));
    z copy_assigned, move_assigned;
    copy_assigned = original;
    move_assigned = std::move(copy_assigned);
    if (moved != original || move_assigned != original)
        return 15;
    z value(2, -1);
    const z other(1, 2);
    value.template operator+= <float>(other);
    value.template operator-= <float>(other);
    asc::std::operator*= <float, float>(value, other);
    asc::std::operator/= <float, float>(value, other);
    if (value != z(2, -1) || asc::std::operator* <float>(value, 2.0F) != z(4, -2) ||
        asc::std::operator* <float>(2.0F, value) != z(4, -2) ||
        !close(asc::std::pow<float, float>(z(2), z(3)), {8, 0}) || asc::std::arg(-2.0L) != std::arg(-2.0L) ||
        asc::std::arg(-2) != std::arg(-2))
        return 14;
    using asc::std::literals::complex_literals::operator""if;
    const std::complex<double> reference(-1.25, 0.5);
    asc::std::complex<float> converted(reference);
    if (!close(converted, reference))
        return 11;
    converted = std::complex<double>(4, 5);
    const auto back = static_cast<std::complex<float>>(converted);
    return back == std::complex<float>(4, 5) && 3if == asc::std::complex<float>(0, 3) &&
            0.25if == asc::std::complex<float>(0, 0.25F) ?
        0 :
        12;
}
