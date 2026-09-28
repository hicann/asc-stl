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

#include <asc/std/__type_traits/alignment_of.h>

#include <cassert>

int main()
{
    static_assert(asc::std::alignment_of<char>::value == 1);
    static_assert(asc::std::alignment_of<int>::value == alignof(int));
    static_assert(asc::std::alignment_of<double>::value == alignof(double));
    static_assert(asc::std::alignment_of_v<char> == 1);
    static_assert(asc::std::alignment_of_v<long double> == alignof(long double));
    struct Overaligned {
        alignas(32) char payload[4];
    };
    static_assert(asc::std::alignment_of<Overaligned>::value == 32);
    return 0;
}
