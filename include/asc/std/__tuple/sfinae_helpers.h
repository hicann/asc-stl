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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_SFINAE_HELPERS_H
#define CANN_ASC_STL_ASC_STD___TUPLE_SFINAE_HELPERS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

enum class __smf_availability { __trivial, __available, __deleted };
template <class T>
struct __test_synthesize_assignment {
    T value;
};
template <class T>
inline constexpr bool __must_synthesize_assignment_v =
    (is_copy_assignable_v<T> && !is_copy_assignable_v<__test_synthesize_assignment<T>>) ||
    (is_move_assignable_v<T> && !is_move_assignable_v<__test_synthesize_assignment<T>>);
template <class Impl, bool Copy, bool Move>
struct __tuple_impl_sfinae_helper {};
template <class Impl>
struct __tuple_impl_sfinae_helper<Impl, false, true> {
    __tuple_impl_sfinae_helper() = default;
    __tuple_impl_sfinae_helper(const __tuple_impl_sfinae_helper&) = default;
    __tuple_impl_sfinae_helper(__tuple_impl_sfinae_helper&&) = default;
    __tuple_impl_sfinae_helper& operator=(const __tuple_impl_sfinae_helper&) = delete;
    __tuple_impl_sfinae_helper& operator=(__tuple_impl_sfinae_helper&&) = default;
};
template <class Impl>
struct __tuple_impl_sfinae_helper<Impl, true, false> {
    __tuple_impl_sfinae_helper() = default;
    __tuple_impl_sfinae_helper(const __tuple_impl_sfinae_helper&) = default;
    __tuple_impl_sfinae_helper(__tuple_impl_sfinae_helper&&) = default;
    __tuple_impl_sfinae_helper& operator=(const __tuple_impl_sfinae_helper&) = default;
    __tuple_impl_sfinae_helper& operator=(__tuple_impl_sfinae_helper&&) = delete;
};
template <class Impl>
struct __tuple_impl_sfinae_helper<Impl, false, false> {
    __tuple_impl_sfinae_helper() = default;
    __tuple_impl_sfinae_helper(const __tuple_impl_sfinae_helper&) = default;
    __tuple_impl_sfinae_helper(__tuple_impl_sfinae_helper&&) = default;
    __tuple_impl_sfinae_helper& operator=(const __tuple_impl_sfinae_helper&) = delete;
    __tuple_impl_sfinae_helper& operator=(__tuple_impl_sfinae_helper&&) = delete;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_SFINAE_HELPERS_H
