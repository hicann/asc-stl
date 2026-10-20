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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_EMPTY_H
#define CANN_ASC_STL_ASC_STD___RANGES_EMPTY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// [range.prim.empty]

namespace __empty_detail {

// Three-level dispatch: member empty() -> ranges::size()==0 -> begin()==end().
// Concept constraints are expanded here as the conventional void_t detection
// structs + enable_if_t, matching access.h/size.h, so the C++17 and device paths
// work identically.
template <class T, class = void>
struct __has_member_empty : false_type {};
template <class T>
struct __has_member_empty<T, void_t<decltype(static_cast<bool>(::asc::std::declval<T>().empty()))>> : true_type {};

// Note: in the no-concepts branch, the size CPO's operator() is an unconstrained
// function with a deduced return type, so probing its callability on an arbitrary
// type would hard-error once the body is instantiated; this branch therefore
// rebuilds its internal dispatch equivalently (member size / ADL size / begin-end
// difference). The probe is SFINAE-safe throughout and matches the semantics of
// "__size_cpo{}(t) is callable".

template <class T, class = void>
struct __can_invoke_size : false_type {};
template <class T>
struct __can_invoke_size<T, void_t<decltype((void)::asc::std::ranges::__size_cpo{}(::asc::std::declval<T>()))>>
    : true_type {};

template <class T, class = void>
struct __can_compare_begin_end : false_type {};
template <class T>
struct __can_compare_begin_end<T,
    void_t<decltype(static_cast<bool>(::asc::std::ranges::__begin_cpo{}(::asc::std::declval<T>()) ==
        ::asc::std::ranges::__end_cpo{}(::asc::std::declval<T>())))>> : true_type {};

struct __fn {
    template <class T, enable_if_t<__has_member_empty<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr bool operator()(T&& value) const noexcept(noexcept(static_cast<bool>(value.empty())))
    {
        return static_cast<bool>(value.empty());
    }

    template <class T, enable_if_t<!__has_member_empty<T>::value && __can_invoke_size<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr bool operator()(T&& value) const
        noexcept(noexcept(::asc::std::ranges::__size_cpo{}(value)))
    {
        return ::asc::std::ranges::__size_cpo{}(value) == 0;
    }

    template <class T,
        enable_if_t<!__has_member_empty<T>::value && !__can_invoke_size<T&&>::value &&
                __can_compare_begin_end<T&&>::value,
            int> = 0>
    CANN_ASC_STL_API constexpr bool operator()(T&& value) const
        noexcept(noexcept(::asc::std::ranges::__begin_cpo{}(value) == ::asc::std::ranges::__end_cpo{}(value)))
    {
        return ::asc::std::ranges::__begin_cpo{}(value) == ::asc::std::ranges::__end_cpo{}(value);
    }
};

}  // namespace __empty_detail

inline constexpr __empty_detail::__fn empty{};

// Internal uses go through the __fn type rather than the CPO object directly
// (avoids the __tile__ access problem).
using __empty_cpo = __empty_detail::__fn;

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_EMPTY_H
