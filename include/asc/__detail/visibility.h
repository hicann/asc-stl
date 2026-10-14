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

#ifndef CANN_ASC_STL_DETAIL_VISIBILITY_H
#define CANN_ASC_STL_DETAIL_VISIBILITY_H

// Visibility policy: every library-internal symbol carries VISIBILITY_HIDDEN
// (via the CANN_ASC_STL_*_API macros) so nothing leaks from an embedding TU;
// the single deliberate VISIBILITY_DEFAULT user is the public piecewise
// construct tag. The _WIN32 arm is kept distinct from the fallback arm on
// purpose: Windows (including MinGW, which defines both _WIN32 and __GNUC__)
// must not receive ELF visibility attributes, and having the arm explicit
// with the same empty body documents that decision instead of relying on
// falling through the GNUC check above.
#if defined(_WIN32)
// Windows (including MinGW): no ELF visibility attributes.
#define CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN
#define CANN_ASC_STL_DETAIL_VISIBILITY_DEFAULT
#elif defined(__GNUC__) || defined(__clang__)
#define CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN __attribute__((visibility("hidden")))
#define CANN_ASC_STL_DETAIL_VISIBILITY_DEFAULT __attribute__((visibility("default")))
#else
#define CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN
#define CANN_ASC_STL_DETAIL_VISIBILITY_DEFAULT
#endif

#endif  // CANN_ASC_STL_DETAIL_VISIBILITY_H
