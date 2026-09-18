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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_SIZE_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_SIZE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__type_traits/is_unbounded_array.h>
#include <asc/std/__type_traits/make_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

template <class>
inline constexpr bool disable_sized_range = false;

// [range.prim.size]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__size)
template <class _Tp>
void size(_Tp&) = delete;
template <class _Tp>
void size(const _Tp&) = delete;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __size_enabled = !disable_sized_range<remove_cvref_t<_Tp>>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Tp>
concept __member_size = __size_enabled<_Tp> && __workaround_52970<_Tp> && requires(_Tp&& __t) {
    { static_cast<::asc::std::decay_t<decltype((__t.size()))>>(__t.size()) } -> __integer_like;
};

template <class _Tp>
concept __unqualified_size =
    __size_enabled<_Tp> && !__member_size<_Tp> && __class_or_enum<remove_cvref_t<_Tp>> && requires(_Tp&& __t) {
        { static_cast<::asc::std::decay_t<decltype((size(__t)))>>(size(__t)) } -> __integer_like;
    };

template <class _Tp>
concept __difference =
    !__member_size<_Tp> && !__unqualified_size<_Tp> && __class_or_enum<remove_cvref_t<_Tp>> && requires(_Tp&& __t) {
        { ::asc::std::ranges::__begin_cpo{}(__t) } -> forward_iterator;
        {
            ::asc::std::ranges::__end_cpo{}(__t)
        } -> sized_sentinel_for<decltype(::asc::std::ranges::__begin_cpo{}(::asc::std::declval<_Tp>()))>;
    };
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__member_size_,
    requires(_Tp&& __t)(requires(__size_enabled<_Tp>), requires(__workaround_52970<_Tp>),
        requires(__integer_like<decltype(static_cast<::asc::std::decay_t<decltype((__t.size()))>>(__t.size()))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __member_size = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__member_size_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__unqualified_size_,
    requires(_Tp&& __t)(requires(__size_enabled<_Tp>), requires(!__member_size<_Tp>),
        requires(__class_or_enum<remove_cvref_t<_Tp>>),
        requires(__integer_like<decltype(static_cast<::asc::std::decay_t<decltype((size(__t)))>>(size(__t)))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __unqualified_size = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__unqualified_size_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__difference_,
    requires(_Tp&& __t)(requires(!__member_size<_Tp>), requires(!__unqualified_size<_Tp>),
        requires(__class_or_enum<remove_cvref_t<_Tp>>),
        requires(forward_iterator<decltype(::asc::std::ranges::__begin_cpo{}(__t))>),
        requires(sized_sentinel_for<decltype(::asc::std::ranges::__end_cpo{}(__t)),
            decltype(::asc::std::ranges::__begin_cpo{}(::asc::std::declval<_Tp>()))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __difference = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__difference_, _Tp);
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

struct __fn {
    // `[range.prim.size]`: the array case (for rvalues).
    template <class _Tp, size_t _Sz>
    [[nodiscard]] CANN_ASC_STL_API constexpr size_t operator()(_Tp (&&)[_Sz]) const noexcept
    {
        return _Sz;
    }

    // `[range.prim.size]`: the array case (for lvalues).
    template <class _Tp, size_t _Sz>
    [[nodiscard]] CANN_ASC_STL_API constexpr size_t operator()(_Tp (&)[_Sz]) const noexcept
    {
        return _Sz;
    }

    // `[range.prim.size]`: `auto(t.size())` is a valid expression.
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__member_size<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(static_cast<::asc::std::decay_t<decltype((__t.size()))>>(__t.size())))
    {
        return static_cast<::asc::std::decay_t<decltype((__t.size()))>>(__t.size());
    }

    // `[range.prim.size]`: `auto(size(t))` is a valid expression.
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__unqualified_size<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(static_cast<::asc::std::decay_t<decltype((size(__t)))>>(size(__t))))
    {
        return static_cast<::asc::std::decay_t<decltype((size(__t)))>>(size(__t));
    }

    // [range.prim.size]: the `to-unsigned-like` case.
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__difference<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const noexcept(noexcept(
        ::asc::std::__to_unsigned_like(::asc::std::ranges::__end_cpo{}(__t) - ::asc::std::ranges::__begin_cpo{}(__t))))
        -> decltype(::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__t) - ::asc::std::ranges::__begin_cpo{}(__t)))
    {
        return ::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__t) - ::asc::std::ranges::__begin_cpo{}(__t));
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto size = __size::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __size_cpo = __size::__fn;
}  // namespace __cpo

// [range.prim.ssize]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__ssize)
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Tp>
concept __can_ssize = requires(_Tp&& __t) { ::asc::std::ranges::__size_cpo{}(__t); };
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__can_ssize_,
    requires(_Tp&& __t)(requires(!is_unbounded_array_v<_Tp>), ((void)::asc::std::ranges::__size_cpo{}(__t))));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __can_ssize = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__can_ssize_, _Tp);
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_ssize<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__size_cpo{}(__t)))
    {
        using _Signed = make_signed_t<decltype(::asc::std::ranges::__size_cpo{}(__t))>;
        using _Result = conditional_t<(sizeof(ptrdiff_t) > sizeof(_Signed)), ptrdiff_t, _Signed>;
        return static_cast<_Result>(::asc::std::ranges::__size_cpo{}(__t));
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto ssize = __ssize::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __ssize_cpo = __ssize::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_SIZE_H
