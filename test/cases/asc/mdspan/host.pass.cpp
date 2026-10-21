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

#include "../../../support/w09_w10_semantics.h"
#include "../../../support/dlpack_review_regression.h"

int main()
{
    const int core = asc_stl_w09_w10_test::evaluate_extension_mdspan();
    if (core != 0)
        return core;
#if defined(CANN_ASC_STL_HAS_DLPACK)
    return asc_stl_dlpack_review::evaluate() ? asc_stl_w09_w10_test::evaluate_dlpack() : 91;
#else
    return 0;
#endif
}
