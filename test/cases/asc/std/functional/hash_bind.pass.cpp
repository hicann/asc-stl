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

#include <asc/std/functional>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <unordered_map>

template <class T>
bool lookup(T first, T other)
{
    std::unordered_map<T, int, asc::std::hash<T>> values;
    values.emplace(first, 4);
    values.emplace(other, 8);
    return values.at(first) == 4 && values.at(other) == (first == other ? 4 : 8);
}

template <class T>
bool bounds()
{
    return lookup<T>(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max());
}

template <class Placeholder>
bool binds_position(Placeholder ph, int expected)
{
    auto select = asc::std::bind([](int value) { return value; }, ph);
    return select(11, 22, 33, 44, 55, 66, 77, 88, 99, 110) == expected;
}

int main()
{
    int data[2]{};
    if (!bounds<bool>() || !bounds<char>() || !bounds<signed char>() || !bounds<unsigned char>() ||
        !bounds<wchar_t>() || !bounds<char16_t>() || !bounds<char32_t>() || !bounds<short>() ||
        !bounds<unsigned short>() || !bounds<int>() || !bounds<unsigned int>() || !bounds<long>() ||
        !bounds<unsigned long>() || !bounds<long long>() || !bounds<unsigned long long>() || !lookup(data, data + 1) ||
        !lookup<std::nullptr_t>(nullptr, nullptr))
        return 1;
    if (!lookup(0.0f, -0.0f) || !lookup(0.0, -0.0) || !lookup(0.0L, -0.0L) || !lookup(2.0L, -2.0L) ||
        !lookup(2.0, -2.0) || !lookup(2.0f, -2.0f))
        return 2;
#if CANN_ASC_STL_DETAIL_HAS_INT128()
    if (!lookup<__int128_t>(3, -7) || !lookup<__uint128_t>(0, ~__uint128_t{0}))
        return 3;
#endif
    namespace p = asc::std::placeholders;
    if (!binds_position(p::_1, 11) || !binds_position(p::_2, 22) || !binds_position(p::_3, 33) ||
        !binds_position(p::_4, 44) || !binds_position(p::_5, 55) || !binds_position(p::_6, 66) ||
        !binds_position(p::_7, 77) || !binds_position(p::_8, 88) || !binds_position(p::_9, 99) ||
        !binds_position(p::_10, 110))
        return 5;
    const auto inferred = asc::std::bind(asc::std::plus<int>{}, asc::std::placeholders::_2, 3);
    const auto binder = asc::std::bind<long>(asc::std::minus<int>{}, 17, asc::std::placeholders::_1);
    static_assert(std::is_same_v<decltype(binder(8)), long>);
    using placeholder = std::remove_cv_t<decltype(asc::std::placeholders::_2)>;
    static_assert(asc::std::is_placeholder<placeholder>::value == 2);
    static_assert(asc::std::is_bind_expression<std::remove_cv_t<decltype(inferred)>>::value &&
        asc::std::is_bind_expression<std::remove_cv_t<decltype(binder)>>::value);
    if (inferred(31, 9) != 12)
        return 4;
    auto r = asc::std::ref(data[0]);
    return binder(8) != 9 || &asc::std::ref(r).get() != data || &asc::std::cref(r).get() != data;
}
