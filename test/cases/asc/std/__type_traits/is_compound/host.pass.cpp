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

#include <asc/std/__type_traits/is_compound.h>

#include <cassert>

enum Enum { A };
enum class Scoped { B };
struct Struct {};
class Class {};
union Union {};

int main()
{
    static_assert(!asc::std::is_compound_v<int>);
    static_assert(!asc::std::is_compound_v<float>);
    static_assert(!asc::std::is_compound_v<void>);
    static_assert(!asc::std::is_compound_v<bool>);
    static_assert(asc::std::is_compound_v<Enum>);
    static_assert(asc::std::is_compound_v<Scoped>);
    static_assert(asc::std::is_compound_v<Struct>);
    static_assert(asc::std::is_compound_v<Class>);
    static_assert(asc::std::is_compound_v<Union>);
    static_assert(asc::std::is_compound_v<int*>);
    static_assert(asc::std::is_compound_v<int&>);
    static_assert(asc::std::is_compound_v<int[4]>);

    static_assert(asc::std::is_compound<Struct>::value);
    static_assert(!asc::std::is_compound<int>::value);
    assert(asc::std::is_compound_v<Struct>);
    assert(!asc::std::is_compound_v<int>);
    return 0;
}
