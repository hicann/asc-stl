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

#include <asc/std/__memory/construct_at.h>
#include "support/b010_semantics.h"
#include "support/construct_at_cardinality_semantics.h"

int main()
{
    const int cardinality_result = asc_stl_construct_at_cardinality_test::evaluate();
    if (cardinality_result != 0)
        return cardinality_result;
    return asc_stl_b010_test::evaluate_runtime();
}
