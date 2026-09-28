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
#ifndef ASC_STL_TEST_SUPPORT_FOUNDATION_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_FOUNDATION_SEMANTICS_H
#include <asc/std/__cstring/memcpy.h>
#include <asc/std/__cstring/memset.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/voidify.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__type_traits/add_const.h>
#include <asc/std/__type_traits/add_cv.h>
#include <asc/std/__type_traits/add_volatile.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/dependent_type.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/__type_traits/lazy.h>
#include <asc/std/__type_traits/nat.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__type_traits/remove_volatile.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/as_const.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/ratio>

namespace asc_stl_foundation_test {
template <class, class>
inline constexpr bool same_type = false;
template <class T>
inline constexpr bool same_type<T, T> = true;
struct tuple_probe {};
struct address_probe {
    CANN_ASC_STL_API address_probe* operator&() noexcept  // NOLINT(runtime/operator)
    {
        return nullptr;
    }
};
template <class T>
struct identity {
    using type = T;
};

static_assert(same_type<asc::std::add_const_t<int>, const int>);
static_assert(same_type<asc::std::add_cv_t<int>, const volatile int>);
static_assert(same_type<asc::std::add_volatile_t<int>, volatile int>);
static_assert(same_type<asc::std::conditional_t<true, int, long>, int>);
static_assert(same_type<asc::std::conditional_t<false, int, long>, long>);
static_assert(same_type<asc::std::enable_if_t<true, int>, int>);
static_assert(asc::std::integral_constant<int, 7>::value == 7);
static_assert(asc::std::true_type{} && !asc::std::false_type{});
static_assert(asc::std::is_constant_evaluated());
static_assert(same_type<typename asc::std::_Lazy<identity, int>::type, int>);
static_assert(!asc::std::__always_false_v<int>);
static_assert(same_type<asc::std::remove_const_t<const int>, int>);
static_assert(same_type<asc::std::remove_pointer_t<int* const>, int>);
static_assert(same_type<asc::std::remove_volatile_t<volatile int>, int>);
static_assert(same_type<asc::std::type_identity_t<int>, int>);
static_assert(same_type<asc::std::void_t<int, long>, void>);
static_assert(same_type<decltype(asc::std::declval<void>()), void>);
static_assert(asc::std::ratio_equal_v<asc::std::ratio<2, 4>, asc::std::ratio<1, 2>>);
static_assert(asc::std::ratio_add<asc::std::ratio<1, 2>, asc::std::ratio<1, 3>>::num == 5);
static_assert(asc::std::ratio_subtract<asc::std::ratio<1, 2>, asc::std::ratio<1, 3>>::num == 1);
static_assert(asc::std::ratio_multiply<asc::std::ratio<2, 3>, asc::std::ratio<3, 4>>::num == 1);
static_assert(asc::std::ratio_divide<asc::std::ratio<2, 3>, asc::std::ratio<4, 5>>::num == 5);
static_assert(asc::std::ratio_less_v<asc::std::milli, asc::std::centi>);
static_assert(asc::std::atto::den == 1000000000000000000LL);
static_assert(asc::std::exa::num == 1000000000000000000LL);

CANN_ASC_STL_API int evaluate() noexcept
{
    int value = 7;
    if (asc::std::addressof(asc::std::as_const(value)) != asc::std::addressof(value))
        return 1;
    address_probe probe;
    if (asc::std::addressof(probe) == nullptr)
        return 2;
    if (asc::std::__voidify(probe) != static_cast<void*>(asc::std::addressof(probe)))
        return 3;
    unsigned char source[6] = {11, 22, 33, 44, 55, 66};
    unsigned char target[8] = {0xA5, 0, 0, 0, 0, 0, 0, 0x5A};
    if (asc::std::memcpy(target + 1, source, 6) != target + 1)
        return 4;
    if (target[0] != 0xA5 || target[7] != 0x5A || target[3] != 33)
        return 5;
    if (asc::std::memset(target + 2, 0x7C, 3) != target + 2)
        return 6;
    if (target[1] != 11 || target[2] != 0x7C || target[4] != 0x7C || target[5] != 55)
        return 7;
    if (asc::std::is_constant_evaluated())
        return 8;
    return 0;
}
}  // namespace asc_stl_foundation_test

namespace asc::std {
template <>
struct tuple_element<0, asc_stl_foundation_test::tuple_probe> {
    using type = int;
};
}  // namespace asc::std
static_assert(
    asc_stl_foundation_test::same_type<asc::std::tuple_element_t<0, const asc_stl_foundation_test::tuple_probe>,
        const int>);
#endif
