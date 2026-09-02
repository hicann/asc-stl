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
#ifndef ASC_STL_TEST_SUPPORT_FORCE_BUILTIN_FALLBACK_H
#define ASC_STL_TEST_SUPPORT_FORCE_BUILTIN_FALLBACK_H

#if defined(__clang__)
#pragma clang system_header
#elif defined(__GNUC__)
#pragma GCC system_header
#endif

// Force asc/__detail/builtin.h to report no compiler builtins. Keeping this
// compiler-macro override in a system test Header preserves the production
// configuration contract and keeps strict -Werror enabled for the test TU.
#if defined(__has_builtin)
#undef __has_builtin
#endif

#endif  // ASC_STL_TEST_SUPPORT_FORCE_BUILTIN_FALLBACK_H
