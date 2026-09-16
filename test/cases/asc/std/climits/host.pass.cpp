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

#include <asc/std/climits>

int main()
{
    static_assert(CHAR_BIT == 8);
    static_assert(SCHAR_MIN < 0 && SCHAR_MAX > 0);
    static_assert(UCHAR_MAX > SCHAR_MAX);
    static_assert(USHRT_MAX > SHRT_MAX);
    static_assert(UINT_MAX > INT_MAX);
    static_assert(ULONG_MAX > LONG_MAX);
    static_assert(ULLONG_MAX > LLONG_MAX);
    return 0;
}
