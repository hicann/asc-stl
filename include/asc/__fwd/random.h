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

#ifndef CANN_ASC_STL_DETAIL_FWD_RANDOM_H
#define CANN_ASC_STL_DETAIL_FWD_RANDOM_H

#include <asc/std/detail/__config>

#include <asc/std/cstdint>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

class __feistel_bijection;

template <class _IndexType = asc::std::uint64_t, class _Bijection = __feistel_bijection>
class random_bijection;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_FWD_RANDOM_H
