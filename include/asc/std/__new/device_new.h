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

#ifndef CANN_ASC_STL_STD_DETAIL_NEW_DEVICE_NEW_H
#define CANN_ASC_STL_STD_DETAIL_NEW_DEVICE_NEW_H

#include <asc/std/detail/__config>

// BiSheng device compilation does not expose the standard non-allocating
// placement-new declarations. ASC-STL uses these overloads to construct an
// object in caller-owned local storage; they never allocate device memory.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
CANN_ASC_STL_DEVICE inline void* operator new(decltype(sizeof(0)), void* __ptr) noexcept
{
    return __ptr;
}

CANN_ASC_STL_DEVICE inline void* operator new[](decltype(sizeof(0)), void* __ptr) noexcept
{
    return __ptr;
}

CANN_ASC_STL_DEVICE inline void operator delete(void*, void*) noexcept
{}
CANN_ASC_STL_DEVICE inline void operator delete[](void*, void*) noexcept
{}
#else
#include <asc/std/__host_stdlib/new>
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_NEW_DEVICE_NEW_H
