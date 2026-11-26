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

#include <asc/std/functional>
#include <asc/std/type_traits>
#include <cassert>
#include "device_checks.h"

int main()
{
    int value = 7;
    const asc::std::reference_wrapper<int> reference(value);
    int& alias = reference;
    static_assert(asc::std::is_convertible_v<decltype(reference), int&>);
    assert(&alias == &value);
    alias = 11;
    assert(value == 11);
    return asc_stl_test_functional::check();
}
