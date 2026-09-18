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

#ifndef CANN_ASC_STL_STD_DETAIL_EXCEPTION_MSG_STORAGE_H
#define CANN_ASC_STL_STD_DETAIL_EXCEPTION_MSG_STORAGE_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

struct __msg_storage {
    static constexpr ::asc::std::size_t __size = 512;
    char __buffer[__size]{0};
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_STD_DETAIL_EXCEPTION_MSG_STORAGE_H
