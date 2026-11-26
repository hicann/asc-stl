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

#include <asc/std/ratio>

#include <cstdint>
#include <ratio>
#include <type_traits>

namespace {

namespace ast = asc::std;

#define CHECK_SI_RATIO(Name) static_assert(ast::Name::num == std::Name::num && ast::Name::den == std::Name::den)
CHECK_SI_RATIO(atto);
CHECK_SI_RATIO(femto);
CHECK_SI_RATIO(pico);
CHECK_SI_RATIO(nano);
CHECK_SI_RATIO(micro);
CHECK_SI_RATIO(milli);
CHECK_SI_RATIO(centi);
CHECK_SI_RATIO(deci);
CHECK_SI_RATIO(deca);
CHECK_SI_RATIO(hecto);
CHECK_SI_RATIO(kilo);
CHECK_SI_RATIO(mega);
CHECK_SI_RATIO(giga);
CHECK_SI_RATIO(tera);
CHECK_SI_RATIO(peta);
CHECK_SI_RATIO(exa);
#undef CHECK_SI_RATIO

template <std::intmax_t A, std::intmax_t B, std::intmax_t C, std::intmax_t D>
constexpr bool check_ratios()
{
    using lhs = ast::ratio<A, B>;
    using rhs = ast::ratio<C, D>;
    using left = std::ratio<A, B>;
    using right = std::ratio<C, D>;
    static_assert(std::is_same_v<typename lhs::type, ast::ratio<left::num, left::den>>);
    return lhs::num == left::num && lhs::den == left::den &&
        ast::ratio_equal<lhs, rhs>::value == std::ratio_equal<left, right>::value &&
        ast::ratio_not_equal<lhs, rhs>::value == std::ratio_not_equal<left, right>::value &&
        ast::ratio_not_equal_v<lhs, rhs> == std::ratio_not_equal_v<left, right> &&
        ast::ratio_less<lhs, rhs>::value == std::ratio_less<left, right>::value &&
        ast::ratio_less_equal<lhs, rhs>::value == std::ratio_less_equal<left, right>::value &&
        ast::ratio_less_equal_v<lhs, rhs> == std::ratio_less_equal_v<left, right> &&
        ast::ratio_greater<lhs, rhs>::value == std::ratio_greater<left, right>::value &&
        ast::ratio_greater_v<lhs, rhs> == std::ratio_greater_v<left, right> &&
        ast::ratio_greater_equal<lhs, rhs>::value == std::ratio_greater_equal<left, right>::value &&
        ast::ratio_greater_equal_v<lhs, rhs> == std::ratio_greater_equal_v<left, right>;
}

static_assert(check_ratios<6, -8, -9, 12>());
static_assert(check_ratios<-6, 8, -1, 7>());
static_assert(check_ratios<-3, -7, -1, 2>());
static_assert(check_ratios<0, -13, 0, 7>());
static_assert(check_ratios<1, 13, 1, 11>());
static_assert(
    check_ratios<9223372036854775781LL, 9223372036854775783LL, 9223372036854775783LL, 9223372036854775781LL>());
}  // namespace

int main()
{
    return 0;
}
