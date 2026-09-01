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

#define ASC_IGNORE_DEPRECATED_API

#include <asc/std/__type_traits/result_of.h>
#include <type_traits>

struct ResultCallable {
    long operator()(int, short) const;
};

#if __cplusplus <= 201703L || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_TYPE_TRAITS)
static_assert(std::is_same_v<typename asc::std::result_of<ResultCallable(int, short)>::type, long>);
static_assert(std::is_same_v<asc::std::result_of_t<ResultCallable(int, short)>, long>);
#endif

int main()
{
    return 0;
}
