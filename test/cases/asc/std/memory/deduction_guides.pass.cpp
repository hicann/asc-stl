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

#include <asc/std/memory>
#include <asc/std/type_traits>
namespace s = asc::std;
// The library marks allocation_result as supporting CTAD but declares no deducible two-field guide.
template <class Pointer, class = void>
struct from_fields : s::false_type {};
template <class Pointer>
struct from_fields<Pointer, s::void_t<decltype(s::allocation_result{s::declval<Pointer>(), 2u})>> : s::true_type {};
static_assert(!from_fields<int*>::value);
int main()
{
    int values[]{4, 1};
    const s::allocation_result<int*, unsigned> owner{values, 2};
    s::allocation_result copied(owner);
    static_assert(s::is_same_v<decltype(copied), s::allocation_result<int*, unsigned>>);
    return copied.ptr == values && copied.count == 2 && copied.ptr[1] == 1 ? 0 : 1;
}
