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

#ifndef ASC_STL_B028_RUNTIME_SEMANTICS_H
#define ASC_STL_B028_RUNTIME_SEMANTICS_H

#include "../../../../../support/b028_semantics.h"

namespace asc_stl_b028_runtime {
template <class ResultPointer>
CANN_ASC_STL_API void evaluate_foundation(ResultPointer result)
{
    result[0] = static_cast<unsigned int>(asc_stl_b028_test::evaluate_foundation());
}

template <class ResultPointer, class StoragePointer>
CANN_ASC_STL_HOST_SIMT_API void evaluate(ResultPointer result, StoragePointer storage)
{
    result[0] = static_cast<unsigned int>(asc_stl_b028_test::evaluate_device(storage, 8192));
}
}  // namespace asc_stl_b028_runtime

#endif  // ASC_STL_B028_RUNTIME_SEMANTICS_H
