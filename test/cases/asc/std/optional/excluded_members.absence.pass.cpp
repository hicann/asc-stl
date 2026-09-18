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

#include <asc/std/optional>

struct identity_optional {
    asc::std::optional<int> operator()(int value) const
    {
        return asc::std::optional<int>(value);
    }
};

struct identity_value {
    constexpr int operator()(int value) const
    {
        return value;
    }
};

struct fallback_optional {
    asc::std::optional<int> operator()() const
    {
        return asc::std::optional<int>(1);
    }
};

template <class T>
concept lacks_value_lvalue = !requires(T& value) { value.value(); };
template <class T>
concept lacks_value_const_lvalue = !requires(const T& value) { value.value(); };
template <class T>
concept lacks_value_rvalue = !requires(T&& value) { static_cast<T&&>(value).value(); };
template <class T>
concept lacks_value_const_rvalue = !requires(const T&& value) { static_cast<const T&&>(value).value(); };

template <class T>
concept lacks_and_then_lvalue = !requires(T& value) { value.and_then(identity_optional{}); };
template <class T>
concept lacks_and_then_const_lvalue = !requires(const T& value) { value.and_then(identity_optional{}); };
template <class T>
concept lacks_and_then_rvalue = !requires(T&& value) { static_cast<T&&>(value).and_then(identity_optional{}); };
template <class T>
concept lacks_and_then_const_rvalue =
    !requires(const T&& value) { static_cast<const T&&>(value).and_then(identity_optional{}); };

template <class T>
concept lacks_transform_lvalue = !requires(T& value) { value.transform(identity_value{}); };
template <class T>
concept lacks_transform_const_lvalue = !requires(const T& value) { value.transform(identity_value{}); };
template <class T>
concept lacks_transform_rvalue = !requires(T&& value) { static_cast<T&&>(value).transform(identity_value{}); };
template <class T>
concept lacks_transform_const_rvalue =
    !requires(const T&& value) { static_cast<const T&&>(value).transform(identity_value{}); };

template <class T>
concept lacks_or_else_const_lvalue = !requires(const T& value) { value.or_else(fallback_optional{}); };
template <class T>
concept lacks_or_else_rvalue = !requires(T&& value) { static_cast<T&&>(value).or_else(fallback_optional{}); };

using tested_optional = asc::std::optional<int>;
static_assert(lacks_value_lvalue<tested_optional>);
static_assert(lacks_value_const_lvalue<tested_optional>);
static_assert(lacks_value_rvalue<tested_optional>);
static_assert(lacks_value_const_rvalue<tested_optional>);
static_assert(lacks_and_then_lvalue<tested_optional>);
static_assert(lacks_and_then_const_lvalue<tested_optional>);
static_assert(lacks_and_then_rvalue<tested_optional>);
static_assert(lacks_and_then_const_rvalue<tested_optional>);
static_assert(lacks_transform_lvalue<tested_optional>);
static_assert(lacks_transform_const_lvalue<tested_optional>);
static_assert(lacks_transform_rvalue<tested_optional>);
static_assert(lacks_transform_const_rvalue<tested_optional>);
static_assert(lacks_or_else_const_lvalue<tested_optional>);
static_assert(lacks_or_else_rvalue<tested_optional>);

int main()
{
    return 0;
}
