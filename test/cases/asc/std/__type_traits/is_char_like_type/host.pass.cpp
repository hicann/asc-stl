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

#include <asc/std/__type_traits/is_char_like_type.h>

#include <cassert>

int main()
{
    static_assert(asc::std::__asc_is_char_like_type_v<char>);
    static_assert(asc::std::__asc_is_char_like_type_v<wchar_t>);
    static_assert(asc::std::__asc_is_char_like_type_v<char16_t>);
    static_assert(asc::std::__asc_is_char_like_type_v<unsigned char>);
    static_assert(asc::std::__asc_is_char_like_type_v<int>);
    static_assert(!asc::std::__asc_is_char_like_type_v<char&>);
    static_assert(asc::std::__asc_is_char_like_type_v<char[4]>);
    struct StandardTrivial {
        char value;
    };
    static_assert(asc::std::__asc_is_char_like_type_v<StandardTrivial>);
    struct VirtualBase {
        virtual ~VirtualBase()
        {}
    };
    static_assert(!asc::std::__asc_is_char_like_type_v<VirtualBase>);
    return 0;
}
