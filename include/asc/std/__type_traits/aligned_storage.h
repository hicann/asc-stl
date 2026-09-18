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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_ALIGNED_STORAGE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_ALIGNED_STORAGE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/nat.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
struct __align_type {
    static const size_t value = alignof(_Tp);
    using type = _Tp;
};

struct __struct_double {
    long double __lx;
};
struct __struct_double4 {
    double __lx[4];
};

using __all_types = __type_list<__align_type<unsigned char>, __align_type<unsigned short>, __align_type<unsigned int>,
    __align_type<unsigned long>, __align_type<unsigned long long>, __align_type<double>, __align_type<long double>,
    __align_type<__struct_double>, __align_type<__struct_double4>, __align_type<int*>>;

template <size_t _Align>
struct CANN_ASC_STL_DETAIL_ACCL_ALIGNAS(_Align) __fallback_overaligned {
    static const size_t value = _Align;
    using type = __fallback_overaligned;
};

template <size_t _Align>
struct __has_align {
    template <class _Ty>
    using __call = bool_constant<_Align == _Ty::value>;
};

template <class _TL, size_t _Align>
struct __find_pod
    : public __type_front<__type_find_if<__type_push_back<_TL, __fallback_overaligned<_Align>>, __has_align<_Align>>> {
};

CANN_ASC_STL_API constexpr size_t __select_align_fn_2_(size_t __len, size_t __min, size_t __max)
{
    return __len < __max ? __min : __max;
}

CANN_ASC_STL_API constexpr size_t __select_align_fn_(size_t __len, size_t __a1, size_t __a2)
{
    return __select_align_fn_2_(__len, __a2 < __a1 ? __a2 : __a1, __a1 < __a2 ? __a2 : __a1);
}

template <size_t _Len>
struct __select_align_fn {
    template <class _State, class _Ty>
    using __call = integral_constant<size_t, __select_align_fn_(_Len, _State::value, _Ty::value)>;
};

template <class _TL, size_t _Len>
struct __find_max_align : public __type_fold_left<_TL, integral_constant<size_t, 0>, __select_align_fn<_Len>> {};

template <size_t _Len, size_t _Align = __find_max_align<__all_types, _Len>::value>
struct aligned_storage {
    using _Aligner = typename __find_pod<__all_types, _Align>::type;
    union type {
        _Aligner __align;
        unsigned char __data[(_Len + _Align - 1) / _Align * _Align];
    };
};

template <size_t _Len, size_t _Align = __find_max_align<__all_types, _Len>::value>
using aligned_storage_t = typename aligned_storage<_Len, _Align>::type;

#define _CREATE_ALIGNED_STORAGE_SPECIALIZATION(n)         \
    template <size_t _Len>                                \
    struct aligned_storage<_Len, n> {                     \
        struct CANN_ASC_STL_DETAIL_ACCL_ALIGNAS(n) type { \
            unsigned char __lx[(_Len + n - 1) / n * n];   \
        };                                                \
    }

_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x1);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x2);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x4);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x8);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x10);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x20);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x40);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x80);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x100);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x200);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x400);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x800);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x1000);
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x2000);
// PE/COFF does not support alignment beyond 8192 (=0x2000)
#if !defined(_WIN32)
_CREATE_ALIGNED_STORAGE_SPECIALIZATION(0x4000);
#endif  // !defined(_WIN32)

#undef _CREATE_ALIGNED_STORAGE_SPECIALIZATION

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_ALIGNED_STORAGE_H
