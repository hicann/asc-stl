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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_SIZE_H
#define CANN_ASC_STL_ASC_STD___RANGES_SIZE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__concepts/arithmetic.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_unbounded_array.h>
#include <asc/std/__type_traits/make_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

template <class>
inline constexpr bool disable_sized_range = false;

// [range.prim.size]

namespace __size {

template <class _Tp>
void size(_Tp&) = delete;
template <class _Tp>
void size(const _Tp&) = delete;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class _Tp>
concept __size_enabled = !disable_sized_range<remove_cvref_t<_Tp>>;

template <class _Tp>
concept __integer_like = integral<_Tp> && !same_as<_Tp, bool>;

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

struct __fn {
    // `[range.prim.size]`: the array case (for rvalues).
    template <class _Tp, size_t _Sz>
    CANN_ASC_STL_API constexpr size_t operator()(_Tp (&&)[_Sz]) const noexcept
    {
        return _Sz;
    }

    // `[range.prim.size]`: the array case (for lvalues).
    template <class _Tp, size_t _Sz>
    CANN_ASC_STL_API constexpr size_t operator()(_Tp (&)[_Sz]) const noexcept
    {
        return _Sz;
    }

    // `[range.prim.size]`: `auto(t.size())` is a valid expression.
    template <class _Tp>
        requires __member_size<_Tp>
    CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(static_cast<::asc::std::decay_t<decltype((__t.size()))>>(__t.size())))
    {
        return static_cast<::asc::std::decay_t<decltype((__t.size()))>>(__t.size());
    }

    // `[range.prim.size]`: `auto(size(t))` is a valid expression.
    template <class _Tp>
        requires __unqualified_size<_Tp>
    CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(static_cast<::asc::std::decay_t<decltype((size(__t)))>>(size(__t))))
    {
        return static_cast<::asc::std::decay_t<decltype((size(__t)))>>(size(__t));
    }

    // [range.prim.size]: the `to-unsigned-like` case.
    template <class _Tp>
        requires __difference<_Tp>
    CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const noexcept(noexcept(
        ::asc::std::__to_unsigned_like(::asc::std::ranges::__end_cpo{}(__t) - ::asc::std::ranges::__begin_cpo{}(__t))))
        -> decltype(::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__t) - ::asc::std::ranges::__begin_cpo{}(__t)))
    {
        return ::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__t) - ::asc::std::ranges::__begin_cpo{}(__t));
    }
};
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
template <class _Tp>
CANN_ASC_STL_API constexpr auto __adl_size(_Tp&& __value) noexcept(
    noexcept(size(static_cast<_Tp&&>(__value)))) -> decltype(size(static_cast<_Tp&&>(__value)))
{
    return size(static_cast<_Tp&&>(__value));
}

template <class _Tp, class = void>
struct __has_member_size : false_type {};
template <class _Tp>
struct __has_member_size<_Tp, void_t<decltype(::asc::std::declval<_Tp>().size())>> : true_type {};
template <class _Tp, class = void>
struct __has_adl_size : false_type {};
template <class _Tp>
struct __has_adl_size<_Tp, void_t<decltype(__adl_size(::asc::std::declval<_Tp>()))>> : true_type {};

struct __member_tag {};
struct __adl_tag {};
struct __difference_tag {};

template <class _Tp>
using __tag = conditional_t<__has_member_size<_Tp>::value && !disable_sized_range<remove_cvref_t<_Tp>>, __member_tag,
    conditional_t<__has_adl_size<_Tp>::value && !disable_sized_range<remove_cvref_t<_Tp>>, __adl_tag,
        __difference_tag>>;

struct __fn {
private:
    template <class _Tp>
    CANN_ASC_STL_API static constexpr auto __call(_Tp&& __value, __member_tag) noexcept(
        noexcept(__value.size())) -> decltype(__value.size())
    {
        return __value.size();
    }
    template <class _Tp>
    CANN_ASC_STL_API static constexpr auto __call(_Tp&& __value, __adl_tag) noexcept(
        noexcept(__adl_size(static_cast<_Tp&&>(__value)))) -> decltype(__adl_size(static_cast<_Tp&&>(__value)))
    {
        return __adl_size(static_cast<_Tp&&>(__value));
    }
    template <class _Tp>
    CANN_ASC_STL_API static constexpr auto __call(_Tp&& __value, __difference_tag) noexcept(
        noexcept(ranges::end(__value) -
            ranges::begin(__value))) -> make_unsigned_t<decltype(ranges::end(__value) - ranges::begin(__value))>
    {
        using __result_type = make_unsigned_t<decltype(ranges::end(__value) - ranges::begin(__value))>;
        return static_cast<__result_type>(ranges::end(__value) - ranges::begin(__value));
    }

public:
    // `[range.prim.size]`: the array case (for rvalues).
    template <class _Tp, size_t _Sz>
    CANN_ASC_STL_API constexpr size_t operator()(_Tp (&&)[_Sz]) const noexcept
    {
        return _Sz;
    }

    // `[range.prim.size]`: the array case (for lvalues).
    template <class _Tp, size_t _Sz>
    CANN_ASC_STL_API constexpr size_t operator()(_Tp (&)[_Sz]) const noexcept
    {
        return _Sz;
    }

    template <class _Tp>
    CANN_ASC_STL_API constexpr auto operator()(_Tp&& __value) const
        noexcept(noexcept(__call(static_cast<_Tp&&>(__value), __tag<_Tp&&>{})))
    {
        return __call(static_cast<_Tp&&>(__value), __tag<_Tp&&>{});
    }
};
#endif  // !concepts

}  // namespace __size

inline constexpr __size::__fn size{};

// Avoid using the CPO object internally because of __tile__ access.
using __size_cpo = __size::__fn;

// [range.prim.ssize]

namespace __ssize {

struct __fn {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class _Tp>
        requires requires(_Tp&& __t) { ::asc::std::ranges::__size_cpo{}(__t); }
    CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__size_cpo{}(__t)))
    {
        using _Signed = make_signed_t<decltype(::asc::std::ranges::__size_cpo{}(__t))>;
        using _Result = conditional_t<(sizeof(ptrdiff_t) > sizeof(_Signed)), ptrdiff_t, _Signed>;
        return static_cast<_Result>(::asc::std::ranges::__size_cpo{}(__t));
    }
#else
    // Requires-expression equivalent: `ranges::size(__t)` must be a valid call. Unbounded arrays
    // are rejected because no array-bound overload exists for them.
    template <class _Tp>
    CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const noexcept(
        noexcept(::asc::std::ranges::__size_cpo{}(__t)))
        -> conditional_t<(sizeof(ptrdiff_t) > sizeof(make_signed_t<decltype(::asc::std::ranges::__size_cpo{}(__t))>)),
            ptrdiff_t, make_signed_t<decltype(::asc::std::ranges::__size_cpo{}(__t))>>
    {
        using _Signed = make_signed_t<decltype(::asc::std::ranges::__size_cpo{}(__t))>;
        using _Result = conditional_t<(sizeof(ptrdiff_t) > sizeof(_Signed)), ptrdiff_t, _Signed>;
        return static_cast<_Result>(::asc::std::ranges::__size_cpo{}(__t));
    }
#endif
};

}  // namespace __ssize

inline constexpr __ssize::__fn ssize{};

// Avoid using the CPO object internally because of __tile__ access.
using __ssize_cpo = __ssize::__fn;

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_SIZE_H
