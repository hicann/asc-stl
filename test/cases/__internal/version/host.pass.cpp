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

#include <asc/std/__internal/version.h>

static_assert(CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION == 4);
static_assert(CANN_ASC_STL_DETAIL_ACCL_ABI_VERSION_LATEST == 4);
static_assert(CANN_ASC_STL_DETAIL_ACCL_API_VERSION == CANN_ASC_STL_ACCL_VERSION);
static_assert(CANN_ASC_STL_DETAIL_ACCL_API_VERSION_MAJOR == CANN_ASC_STL_ACCL_MAJOR_VERSION);

int main()
{
    return 0;
}
