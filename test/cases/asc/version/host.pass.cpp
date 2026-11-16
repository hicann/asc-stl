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
#include <asc/version>

#if CANN_ASC_STL < 20261023
#error "This test requires the 20261023 release or newer"
#endif
#if CANN_ASC_STL_HAS_PIPELINE || CANN_ASC_STL_HAS_NUMERIC_TYPES || CANN_ASC_STL_HAS_CACHE
#error "The baseline extension APIs have not yet completed delivery and acceptance"
#endif
static_assert(CANN_ASC_STL == 20261023);
static_assert(CANN_ASC_STL_LIB_type_identity == 201806L);
static_assert(20261231 < 20270101);
static_assert(20260131 < 20260201);

int main()
{
    return 0;
}
