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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COPY_CVREF_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COPY_CVREF_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/add_rvalue_reference.h>

CANN_ASC_STL_BEGIN_NAMESPACE

struct __apply_cvref_ {
    template <class _Tp>
    using __call = _Tp;
};

struct __apply_cvref_c {
    template <class _Tp>
    using __call = const _Tp;
};

struct __apply_cvref_v {
    template <class _Tp>
    using __call = volatile _Tp;
};

struct __apply_cvref_cv {
    template <class _Tp>
    using __call = const volatile _Tp;
};

struct __apply_cvref_lr {
    template <class _Tp>
    using __call = _Tp&;
};

struct __apply_cvref_clr {
    template <class _Tp>
    using __call = const _Tp&;
};

struct __apply_cvref_vlr {
    template <class _Tp>
    using __call = volatile _Tp&;
};

struct __apply_cvref_cvlr {
    template <class _Tp>
    using __call = const volatile _Tp&;
};

struct __apply_cvref_rr {
    template <class _Tp>
    using __call = _Tp&&;
};

struct __apply_cvref_crr {
    template <class _Tp>
    using __call = const _Tp&&;
};

struct __apply_cvref_vrr {
    template <class _Tp>
    using __call = volatile _Tp&&;
};

struct __apply_cvref_cvrr {
    template <class _Tp>
    using __call = const volatile _Tp&&;
};

// BiSheng rejects references to variable templates while instantiating an
// aicore function signature.  Keep the same dispatch contract, but express the
// mapping entirely through types so __copy_cvref_t is valid in device code.
template <class>
struct __apply_cvref_impl {
    using type = __apply_cvref_;
};
template <class _Tp>
struct __apply_cvref_impl<const _Tp> {
    using type = __apply_cvref_c;
};
template <class _Tp>
struct __apply_cvref_impl<volatile _Tp> {
    using type = __apply_cvref_v;
};
template <class _Tp>
struct __apply_cvref_impl<const volatile _Tp> {
    using type = __apply_cvref_cv;
};
template <class _Tp>
struct __apply_cvref_impl<_Tp&> {
    using type = __apply_cvref_lr;
};
template <class _Tp>
struct __apply_cvref_impl<const _Tp&> {
    using type = __apply_cvref_clr;
};
template <class _Tp>
struct __apply_cvref_impl<volatile _Tp&> {
    using type = __apply_cvref_vlr;
};
template <class _Tp>
struct __apply_cvref_impl<const volatile _Tp&> {
    using type = __apply_cvref_cvlr;
};
template <class _Tp>
struct __apply_cvref_impl<_Tp&&> {
    using type = __apply_cvref_rr;
};
template <class _Tp>
struct __apply_cvref_impl<const _Tp&&> {
    using type = __apply_cvref_crr;
};
template <class _Tp>
struct __apply_cvref_impl<volatile _Tp&&> {
    using type = __apply_cvref_vrr;
};
template <class _Tp>
struct __apply_cvref_impl<const volatile _Tp&&> {
    using type = __apply_cvref_cvrr;
};

template <class _Tp>
using __apply_cvref_fn = typename __apply_cvref_impl<_Tp>::type;

template <class _From, class _To>
using __copy_cvref_t = typename __apply_cvref_fn<_From>::template __call<_To>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COPY_CVREF_H
