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
#include "support/force_builtin_fallback.h"

#include <asc/std/__type_traits/is_constructible.h>  // NOLINT(build/include_order)

struct constructible_from_int {
    explicit constructible_from_int(int);
};

static_assert(asc::std::is_constructible_v<int>);
static_assert(asc::std::is_constructible_v<constructible_from_int, int>);
static_assert(!asc::std::is_constructible_v<constructible_from_int, void*>);
static_assert(!asc::std::is_constructible_v<void, int>);

int main()
{
    return 0;
}
