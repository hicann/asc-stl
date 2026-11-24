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

#include <asc/iterator>
struct unchanged {
    CANN_ASC_STL_API int operator()(int x) const noexcept
    {
        return x;
    }
};
CANN_ASC_STL_API void rejected()
{
    const int value = 3;
    auto output = asc::make_transform_output_iterator(&value, unchanged{});
    *output = 7;
}
