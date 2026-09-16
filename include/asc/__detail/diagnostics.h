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

#ifndef CANN_ASC_STL_DETAIL_DIAGNOSTICS_H
#define CANN_ASC_STL_DETAIL_DIAGNOSTICS_H

#define CANN_ASC_STL_DETAIL_PRAGMA_IMPL(value) _Pragma(#value)
#define CANN_ASC_STL_DETAIL_PRAGMA(value) CANN_ASC_STL_DETAIL_PRAGMA_IMPL(value)

#if defined(__clang__)
#define CANN_ASC_STL_DETAIL_DIAGNOSTIC_PUSH() CANN_ASC_STL_DETAIL_PRAGMA(clang diagnostic push)
#define CANN_ASC_STL_DETAIL_DIAGNOSTIC_POP() CANN_ASC_STL_DETAIL_PRAGMA(clang diagnostic pop)
#define CANN_ASC_STL_DETAIL_DIAGNOSTIC_IGNORE(option) CANN_ASC_STL_DETAIL_PRAGMA(clang diagnostic ignored option)
#elif defined(__GNUC__)
#define CANN_ASC_STL_DETAIL_DIAGNOSTIC_PUSH() CANN_ASC_STL_DETAIL_PRAGMA(GCC diagnostic push)
#define CANN_ASC_STL_DETAIL_DIAGNOSTIC_POP() CANN_ASC_STL_DETAIL_PRAGMA(GCC diagnostic pop)
#define CANN_ASC_STL_DETAIL_DIAGNOSTIC_IGNORE(option) CANN_ASC_STL_DETAIL_PRAGMA(GCC diagnostic ignored option)
#else
#define CANN_ASC_STL_DETAIL_DIAGNOSTIC_PUSH()
#define CANN_ASC_STL_DETAIL_DIAGNOSTIC_POP()
#define CANN_ASC_STL_DETAIL_DIAGNOSTIC_IGNORE(option)
#endif

#endif  // CANN_ASC_STL_DETAIL_DIAGNOSTICS_H
