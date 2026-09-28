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

#ifndef ASC_STL_B027_RUNTIME_SEMANTICS_H
#define ASC_STL_B027_RUNTIME_SEMANTICS_H

#include "../../../../../support/b027_semantics.h"

namespace asc_stl_b027_runtime {
template <class OutputPointer>
CANN_ASC_STL_API void evaluate(OutputPointer result)
{
    result[0] = static_cast<unsigned int>(asc_stl_b027_test::evaluate_core());
}
}  // namespace asc_stl_b027_runtime

#endif  // ASC_STL_B027_RUNTIME_SEMANTICS_H
