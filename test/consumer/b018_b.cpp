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

#include <asc/std/span>
#include <asc/std/array>

int asc_stl_b018_consumer_a();
int asc_stl_b018_consumer_b()
{
    asc::std::array<int, 2> values{{4, 5}};
    asc::std::span<int> view(values);
    return view.size() == 2 && view[0] + view[1] == 9 ? 0 : 1;
}
