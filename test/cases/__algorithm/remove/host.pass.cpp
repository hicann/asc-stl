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

#include <asc/std/__algorithm/remove.h>

constexpr bool test_remove()
{
    int values[] = {1, 2, 3, 2, 4};
    int* end = asc::std::remove(values, values + 5, 2);
    return end == values + 3 && values[0] == 1 && values[1] == 3 && values[2] == 4;
}

static_assert(test_remove());

int main()
{
    return test_remove() ? 0 : 1;
}
