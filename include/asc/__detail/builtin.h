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

#ifndef CANN_ASC_STL_DETAIL_BUILTIN_H
#define CANN_ASC_STL_DETAIL_BUILTIN_H

#if defined(__has_builtin)
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN(builtin) 0
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_trap) || defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_BUILTIN_UNREACHABLE() \
    do {                                          \
        __builtin_trap();                         \
        __builtin_unreachable();                  \
    } while (false)
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_UNREACHABLE() \
    do {                                          \
        for (;;) {                                \
        }                                         \
    } while (false)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_FILE) || defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_BUILTIN_FILE() __builtin_FILE()
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_FILE() __FILE__
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_FUNCTION) || defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_BUILTIN_FUNCTION() __builtin_FUNCTION()
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_FUNCTION() ""
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_LINE) || defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_BUILTIN_LINE() __builtin_LINE()
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_LINE() __LINE__
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_COLUMN)
#define CANN_ASC_STL_DETAIL_BUILTIN_COLUMN() __builtin_COLUMN()
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_COLUMN() 0
#endif

#endif  // CANN_ASC_STL_DETAIL_BUILTIN_H
