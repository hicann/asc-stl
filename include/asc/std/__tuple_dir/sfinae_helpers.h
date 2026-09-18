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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_SFINAE_HELPERS_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_SFINAE_HELPERS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/tuple.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

enum class __smf_availability {
    __trivial,
    __available,
    __deleted,
};

template <class _Tp>
struct _TestSynthesizeAssignment {
    _Tp __dummy;
};

template <class _Tp>
inline constexpr bool __must_synthesize_assignment_v =
    (is_copy_assignable_v<_Tp> && !is_copy_assignable_v<_TestSynthesizeAssignment<_Tp>>) ||
    (is_move_assignable_v<_Tp> && !is_move_assignable_v<_TestSynthesizeAssignment<_Tp>>);

template <class _Impl, bool _AllCopyAssignable, bool _AllMoveAssignable>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __tuple_impl_sfinae_helper {};

template <class _Impl>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __tuple_impl_sfinae_helper<_Impl, false, true> {
    __tuple_impl_sfinae_helper() = default;
    __tuple_impl_sfinae_helper(const __tuple_impl_sfinae_helper&) = default;
    __tuple_impl_sfinae_helper(__tuple_impl_sfinae_helper&&) = default;
    __tuple_impl_sfinae_helper& operator=(const __tuple_impl_sfinae_helper&) = delete;
    __tuple_impl_sfinae_helper& operator=(__tuple_impl_sfinae_helper&&) = default;
};

template <class _Impl>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __tuple_impl_sfinae_helper<_Impl, true, false> {
    __tuple_impl_sfinae_helper() = default;
    __tuple_impl_sfinae_helper(const __tuple_impl_sfinae_helper&) = default;
    __tuple_impl_sfinae_helper(__tuple_impl_sfinae_helper&&) = default;
    __tuple_impl_sfinae_helper& operator=(const __tuple_impl_sfinae_helper&) = default;
    __tuple_impl_sfinae_helper& operator=(__tuple_impl_sfinae_helper&&) = delete;
};

template <class _Impl>
struct CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __tuple_impl_sfinae_helper<_Impl, false, false> {
    __tuple_impl_sfinae_helper() = default;
    __tuple_impl_sfinae_helper(const __tuple_impl_sfinae_helper&) = default;
    __tuple_impl_sfinae_helper(__tuple_impl_sfinae_helper&&) = default;
    __tuple_impl_sfinae_helper& operator=(const __tuple_impl_sfinae_helper&) = delete;
    __tuple_impl_sfinae_helper& operator=(__tuple_impl_sfinae_helper&&) = delete;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_SFINAE_HELPERS_H
