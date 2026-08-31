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

#include <asc/std/__config>

#if !defined(CANN_ASC_STL_DETAIL_COMPILER_GCC) && !defined(CANN_ASC_STL_DETAIL_COMPILER_CLANG) && \
    !defined(CANN_ASC_STL_DETAIL_COMPILER_MSVC) && !defined(CANN_ASC_STL_DETAIL_COMPILER_CCE)
#error "asc/std/__config failed to detect the host compiler"
#endif

int main()
{
    return 0;
}
