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

#ifndef CANN_ASC_STL_DETAIL_FEATURE_DETECTION_H
#define CANN_ASC_STL_DETAIL_FEATURE_DETECTION_H

#if defined(_MSVC_LANG)
#define CANN_ASC_STL_DETAIL_CPLUSPLUS _MSVC_LANG
#else
#define CANN_ASC_STL_DETAIL_CPLUSPLUS __cplusplus
#endif

#define CANN_ASC_STL_DETAIL_HAS_CXX17() (CANN_ASC_STL_DETAIL_CPLUSPLUS >= 201703L)
#define CANN_ASC_STL_DETAIL_HAS_CXX20() (CANN_ASC_STL_DETAIL_CPLUSPLUS >= 202002L)

#if defined(__cpp_concepts) && __cpp_concepts >= 201907L
#define CANN_ASC_STL_DETAIL_HAS_CONCEPTS() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_CONCEPTS() 0
#endif

#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
#define CANN_ASC_STL_DETAIL_HAS_CHAR8_T() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_CHAR8_T() 0
#endif

#endif  // CANN_ASC_STL_DETAIL_FEATURE_DETECTION_H
