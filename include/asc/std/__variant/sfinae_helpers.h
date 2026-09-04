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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_SFINAE_HELPERS_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_SFINAE_HELPERS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__tuple_dir/sfinae_helpers.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <bool _CanCopy>
struct __variant_copy_base {};
template <>
struct __variant_copy_base<false> {
    __variant_copy_base() = default;
    __variant_copy_base(const __variant_copy_base&) = delete;
    __variant_copy_base(__variant_copy_base&&) = default;
    __variant_copy_base& operator=(const __variant_copy_base&) = default;
    __variant_copy_base& operator=(__variant_copy_base&&) = default;
};

template <bool _CanCopy, bool _CanMove>
struct __variant_move_base : __variant_copy_base<_CanCopy> {};
template <bool _CanCopy>
struct __variant_move_base<_CanCopy, false> : __variant_copy_base<_CanCopy> {
    __variant_move_base() = default;
    __variant_move_base(const __variant_move_base&) = default;
    __variant_move_base(__variant_move_base&&) = delete;
    __variant_move_base& operator=(const __variant_move_base&) = default;
    __variant_move_base& operator=(__variant_move_base&&) = default;
};

template <bool _CanCopy, bool _CanMove, bool _CanCopyAssign>
struct __variant_copy_assign_base : __variant_move_base<_CanCopy, _CanMove> {};
template <bool _CanCopy, bool _CanMove>
struct __variant_copy_assign_base<_CanCopy, _CanMove, false> : __variant_move_base<_CanCopy, _CanMove> {
    __variant_copy_assign_base() = default;
    __variant_copy_assign_base(const __variant_copy_assign_base&) = default;
    __variant_copy_assign_base(__variant_copy_assign_base&&) = default;
    __variant_copy_assign_base& operator=(const __variant_copy_assign_base&) = delete;
    __variant_copy_assign_base& operator=(__variant_copy_assign_base&&) = default;
};

template <bool _CanCopy, bool _CanMove, bool _CanCopyAssign, bool _CanMoveAssign>
struct __variant_move_assign_base : __variant_copy_assign_base<_CanCopy, _CanMove, _CanCopyAssign> {};
template <bool _CanCopy, bool _CanMove, bool _CanCopyAssign>
struct __variant_move_assign_base<_CanCopy, _CanMove, _CanCopyAssign, false>
    : __variant_copy_assign_base<_CanCopy, _CanMove, _CanCopyAssign> {
    __variant_move_assign_base() = default;
    __variant_move_assign_base(const __variant_move_assign_base&) = default;
    __variant_move_assign_base(__variant_move_assign_base&&) = default;
    __variant_move_assign_base& operator=(const __variant_move_assign_base&) = default;
    __variant_move_assign_base& operator=(__variant_move_assign_base&&) = delete;
};

template <bool _CanCopy, bool _CanMove, bool _CanCopyAssign, bool _CanMoveAssign>
using __variant_base = __variant_move_assign_base<_CanCopy, _CanMove, _CanCopyAssign, _CanMoveAssign>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_SFINAE_HELPERS_H
