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

#ifndef ASC_STL_TEST_SUPPORT_DETECTED_H
#define ASC_STL_TEST_SUPPORT_DETECTED_H

#include <type_traits>

namespace asc_stl_test {
template <template <class> class Expression, class T, class = void>
inline constexpr bool detected = false;
template <template <class> class Expression, class T>
inline constexpr bool detected<Expression, T, std::void_t<Expression<T>>> = true;
}  // namespace asc_stl_test

#endif  // ASC_STL_TEST_SUPPORT_DETECTED_H
