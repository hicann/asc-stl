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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_IMMOVABLE_H
#define CANN_ASC_STL_DETAIL_UTILITY_IMMOVABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

// BUG (gcc#98995): copy elision fails when initializing a [[no_unique_address]] field
// from a function returning an object of class type by value.
// See: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=98995
#if CANN_ASC_STL_DETAIL_COMPILER(GCC)
// By declaring the move constructor but not defining it, any TU that ODR-uses the move
// constructor will cause a linker error.
#define CANN_ASC_STL_DETAIL_ACCL_IMMOVABLE(_XP) CANN_ASC_STL_API _XP(_XP&&) noexcept
#else  // ^^^ CANN_ASC_STL_DETAIL_COMPILER(GCC) ^^^ / vvv !CANN_ASC_STL_DETAIL_COMPILER(GCC) vvv
#define CANN_ASC_STL_DETAIL_ACCL_IMMOVABLE(_XP) _XP(_XP&&) = delete
#endif  // !CANN_ASC_STL_DETAIL_COMPILER(GCC)

// Classes can inherit from this type to become immovable.
struct __immovable {
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __immovable() = default;
    CANN_ASC_STL_DETAIL_ACCL_IMMOVABLE(__immovable);
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_IMMOVABLE_H
