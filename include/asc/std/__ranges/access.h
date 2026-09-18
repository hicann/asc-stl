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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_ACCESS_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_ACCESS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/declval.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __can_borrow =
    is_lvalue_reference_v<_Tp> || enable_borrowed_range<remove_cvref_t<_Tp>>;

// [range.access.begin]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__begin)
template <class _Tp>
void begin(_Tp&) = delete;
template <class _Tp>
void begin(const _Tp&) = delete;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Tp>
concept __member_begin = __can_borrow<_Tp> && __workaround_52970<_Tp> && requires(_Tp&& __t) {
    { static_cast<::asc::std::decay_t<decltype((__t.begin()))>>(__t.begin()) } -> input_or_output_iterator;
};

template <class _Tp>
concept __unqualified_begin =
    !__member_begin<_Tp> && __can_borrow<_Tp> && __class_or_enum<remove_cvref_t<_Tp>> && requires(_Tp&& __t) {
        { static_cast<::asc::std::decay_t<decltype((begin(__t)))>>(begin(__t)) } -> input_or_output_iterator;
    };
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__member_begin_,
    requires(_Tp&& __t)(requires(__can_borrow<_Tp>), requires(__workaround_52970<_Tp>),
        requires(input_or_output_iterator<decltype(static_cast<::asc::std::decay_t<decltype((__t.begin()))>>(
                __t.begin()))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __member_begin = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__member_begin_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__unqualified_begin_,
    requires(_Tp&& __t)(requires(!__member_begin<_Tp>), requires(__can_borrow<_Tp>),
        requires(__class_or_enum<remove_cvref_t<_Tp>>),
        requires(
            input_or_output_iterator<decltype(static_cast<::asc::std::decay_t<decltype((begin(__t)))>>(begin(__t)))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __unqualified_begin = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__unqualified_begin_, _Tp);
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

struct __fn {
    // This has been made valid as a defect report for C++17 onwards, however gcc below 11.0 does not implement it
#if (!CANN_ASC_STL_DETAIL_COMPILER(GCC) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 11))
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((sizeof(_Tp) >= 0))  // Disallow incomplete element types.
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp (&__t)[]) const noexcept
    {
        return __t + 0;
    }
#endif  // (!CANN_ASC_STL_DETAIL_COMPILER(GCC) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 11))

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, size_t _Np)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((sizeof(_Tp) >= 0))  // Disallow incomplete element types.
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp (&__t)[_Np]) const noexcept
    {
        return __t + 0;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__member_begin<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(static_cast<::asc::std::decay_t<decltype((__t.begin()))>>(__t.begin())))
    {
        return static_cast<::asc::std::decay_t<decltype((__t.begin()))>>(__t.begin());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__unqualified_begin<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(static_cast<::asc::std::decay_t<decltype((begin(__t)))>>(begin(__t))))
    {
        return static_cast<::asc::std::decay_t<decltype((begin(__t)))>>(begin(__t));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__member_begin<_Tp>)CANN_ASC_STL_DETAIL_ACCL_AND(!__unqualified_begin<_Tp>))
    void operator()(_Tp&&) const = delete;

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC, <, 19, 23)
    template <class _Tp>
    void operator()(_Tp (&&)[]) const = delete;

    template <class _Tp, size_t _Np>
    void operator()(_Tp (&&)[_Np]) const = delete;
#endif  // CANN_ASC_STL_DETAIL_COMPILER(MSVC, <, 19, 23)
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto begin = __begin::__fn{};

// Avoid using the public CPO internally so lookup stays constrained to this implementation.
using __begin_cpo = __begin::__fn;
}  // namespace __cpo

// [range.range]

template <class _Tp>
using iterator_t = decltype(::asc::std::ranges::__begin_cpo{}(::asc::std::declval<_Tp&>()));

// [range.access.end]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__end)
template <class _Tp>
void end(_Tp&) = delete;
template <class _Tp>
void end(const _Tp&) = delete;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Tp>
concept __member_end = __can_borrow<_Tp> && __workaround_52970<_Tp> && requires(_Tp&& __t) {
    typename iterator_t<_Tp>;
    { static_cast<::asc::std::decay_t<decltype((__t.end()))>>(__t.end()) } -> sentinel_for<iterator_t<_Tp>>;
};

template <class _Tp>
concept __unqualified_end =
    !__member_end<_Tp> && __can_borrow<_Tp> && __class_or_enum<remove_cvref_t<_Tp>> && requires(_Tp&& __t) {
        typename iterator_t<_Tp>;
        { static_cast<::asc::std::decay_t<decltype((end(__t)))>>(end(__t)) } -> sentinel_for<iterator_t<_Tp>>;
    };
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__member_end_,
    requires(_Tp&& __t)(requires(__can_borrow<_Tp>), requires(__workaround_52970<_Tp>), typename(iterator_t<_Tp>),
        requires(sentinel_for<decltype(static_cast<::asc::std::decay_t<decltype((__t.end()))>>(__t.end())),
            iterator_t<_Tp>>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __member_end = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__member_end_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__unqualified_end_,
    requires(_Tp&& __t)(requires(!__member_end<_Tp>), requires(__can_borrow<_Tp>),
        requires(__class_or_enum<remove_cvref_t<_Tp>>), typename(iterator_t<_Tp>),
        requires(sentinel_for<decltype(static_cast<::asc::std::decay_t<decltype((end(__t)))>>(end(__t))),
            iterator_t<_Tp>>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __unqualified_end = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__unqualified_end_, _Tp);
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, size_t _Np)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((sizeof(_Tp) >= 0))  // Disallow incomplete element types.
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp (&__t)[_Np]) const noexcept
    {
        return __t + _Np;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__member_end<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(static_cast<::asc::std::decay_t<decltype((__t.end()))>>(__t.end())))
    {
        return static_cast<::asc::std::decay_t<decltype((__t.end()))>>(__t.end());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__unqualified_end<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(static_cast<::asc::std::decay_t<decltype((end(__t)))>>(end(__t))))
    {
        return static_cast<::asc::std::decay_t<decltype((end(__t)))>>(end(__t));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__member_end<_Tp>)CANN_ASC_STL_DETAIL_ACCL_AND(!__unqualified_end<_Tp>))
    void operator()(_Tp&&) const = delete;

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC, <, 19, 23)
    template <class _Tp>
    void operator()(_Tp (&&)[]) const = delete;

    template <class _Tp, size_t _Np>
    void operator()(_Tp (&&)[_Np]) const = delete;
#endif  // CANN_ASC_STL_DETAIL_COMPILER(MSVC, <, 19, 23)
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto end = __end::__fn{};

// Avoid using the public CPO internally so lookup stays constrained to this implementation.
using __end_cpo = __end::__fn;
}  // namespace __cpo

// [range.access.cbegin]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__cbegin)
struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_lvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__begin_cpo{}(static_cast<const remove_reference_t<_Tp>&>(
            __t)))) -> decltype(::asc::std::ranges::__begin_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t)))
    {
        return ::asc::std::ranges::__begin_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_rvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__begin_cpo{}(static_cast<const _Tp&&>(
            __t)))) -> decltype(::asc::std::ranges::__begin_cpo{}(static_cast<const _Tp&&>(__t)))
    {
        return ::asc::std::ranges::__begin_cpo{}(static_cast<const _Tp&&>(__t));
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto cbegin = __cbegin::__fn{};

// Avoid using the public CPO internally so lookup stays constrained to this implementation.
using __cbegin_cpo = __cbegin::__fn;
}  // namespace __cpo

// [range.access.cend]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__cend)
struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_lvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__end_cpo{}(static_cast<const remove_reference_t<_Tp>&>(
            __t)))) -> decltype(::asc::std::ranges::__end_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t)))
    {
        return ::asc::std::ranges::__end_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_rvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__end_cpo{}(
            static_cast<const _Tp&&>(__t)))) -> decltype(::asc::std::ranges::__end_cpo{}(static_cast<const _Tp&&>(__t)))
    {
        return ::asc::std::ranges::__end_cpo{}(static_cast<const _Tp&&>(__t));
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto cend = __cend::__fn{};

// Avoid using the public CPO internally so lookup stays constrained to this implementation.
using __cend_cpo = __cend::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES
#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_ACCESS_H
