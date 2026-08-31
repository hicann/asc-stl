/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include <asc/std/__utility/constant_wrapper.h>

#if __cplusplus >= 202002L
static_assert(asc::std::__cw<4>.value == 4);
static_assert((asc::std::__cw<4> + asc::std::__cw<7>).value == 11);
static_assert((asc::std::__cw<7> - asc::std::__cw<4>).value == 3);
static_assert((asc::std::__cw<4> < asc::std::__cw<7>).value);
static_assert(static_cast<int>(asc::std::__cw<9>) == 9);
#endif

int main()
{
    return 0;
}
