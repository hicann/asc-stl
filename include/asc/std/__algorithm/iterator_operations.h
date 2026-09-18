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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_ITERATOR_OPERATIONS_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_ITERATOR_OPERATIONS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__iterator/prev.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _AlgPolicy>
struct _IterOps;

struct _RangeAlgPolicy {};

template <>
struct _IterOps<_RangeAlgPolicy> {
    template <class _Iter>
    using __value_type = iter_value_t<_Iter>;

    template <class _Iter>
    using __difference_type = iter_difference_t<_Iter>;

    static constexpr auto advance = ::asc::std::ranges::__advance_cpo{};
    static constexpr auto distance = ::asc::std::ranges::__distance_cpo{};
    static constexpr auto __iter_move = ::asc::std::ranges::__iter_move_cpo{};
    static constexpr auto iter_swap = ::asc::std::ranges::__iter_swap_cpo{};
    static constexpr auto next = ::asc::std::ranges::__next_cpo{};
    static constexpr auto prev = ::asc::std::ranges::__prev_cpo{};
    static constexpr auto __advance_to = ::asc::std::ranges::__advance_cpo{};
};

struct _ClassicAlgPolicy {};

template <>
struct _IterOps<_ClassicAlgPolicy> {
    template <class _Iter>
    using __value_type = typename iterator_traits<_Iter>::value_type;

    template <class _Iter>
    using __difference_type = typename iterator_traits<_Iter>::difference_type;

    // advance
    template <class _Iter, class _Distance>
    CANN_ASC_STL_API constexpr static void advance(_Iter& __iter, _Distance __count)
    {
        ::asc::std::advance(__iter, __count);
    }

    // distance
    template <class _Iter>
    CANN_ASC_STL_API constexpr static typename iterator_traits<_Iter>::difference_type distance(
        _Iter __first, _Iter __last)
    {
        return ::asc::std::distance(__first, __last);
    }

    template <class _Iter>
    using __deref_t = decltype(*::asc::std::declval<_Iter&>());

    template <class _Iter>
    using __move_t = decltype(::asc::std::move(*::asc::std::declval<_Iter&>()));

    template <class _Iter>
    CANN_ASC_STL_API constexpr static void __validate_iter_reference()
    {
        static_assert(is_same_v<__deref_t<_Iter>, typename iterator_traits<remove_cvref_t<_Iter>>::reference>,
            "It looks like your iterator's `iterator_traits<It>::reference` does not match the return type of "
            "dereferencing the iterator, i.e., calling `*it`. This is undefined behavior according to "
            "[input.iterators] "
            "and can lead to dangling reference issues at runtime, so we are flagging this.");
    }

    // iter_move
    template <class _Iter, enable_if_t<is_reference_v<__deref_t<_Iter>>, int> = 0>
    CANN_ASC_STL_API constexpr static
        // If the result of dereferencing `_Iter` is a reference type, deduce the result of calling `::asc::std::move`
        // on it. Note that the C++03 mode doesn't support `decltype(auto)` as the return type.
        __move_t<_Iter>
        __iter_move(_Iter&& __i)
    {
        __validate_iter_reference<_Iter>();
        return ::asc::std::move(*::asc::std::forward<_Iter>(__i));
    }

    template <class _Iter, enable_if_t<!is_reference_v<__deref_t<_Iter>>, int> = 0>
    CANN_ASC_STL_API constexpr static
        // If the result of dereferencing `_Iter` is a value type, deduce the return value of this function to also be a
        // value -- otherwise, after `operator*` returns a temporary, this function would return a dangling reference to
        // that temporary. Note that the C++03 mode doesn't support `auto` as the return type.
        __deref_t<_Iter>
        __iter_move(_Iter&& __i)
    {
        __validate_iter_reference<_Iter>();
        return *::asc::std::forward<_Iter>(__i);
    }

    // iter_swap
// Device TU: the requires-concept chain of the __iter_swap CPO fails to instantiate
// under CCE (measured on 9.0: "no matching function for call to object", while host
// g++ accepts the same code — the CPO's unqualified iter_swap ADL branch and concept
// combination do not resolve on the device pass), so fall back to a three-step move
// swap (a classic iterator's *it yields a reference and the CPO also ultimately
// dereference-swaps, so semantics match). The host side keeps the CPO path.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class _Iter1, class _Iter2>
    CANN_ASC_STL_API constexpr static void iter_swap(_Iter1&& __a, _Iter2&& __b)
    {
        _Iter1 __a_fwd = ::asc::std::forward<_Iter1>(__a);
        _Iter2 __b_fwd = ::asc::std::forward<_Iter2>(__b);
        auto __tmp = ::asc::std::move(*__a_fwd);
        *__a_fwd = ::asc::std::move(*__b_fwd);
        *__b_fwd = ::asc::std::move(__tmp);
    }
#else
    template <class _Iter1, class _Iter2>
    CANN_ASC_STL_API constexpr static void iter_swap(_Iter1&& __a, _Iter2&& __b)
    {
        ::asc::std::ranges::__iter_swap_cpo{}(::asc::std::forward<_Iter1>(__a), ::asc::std::forward<_Iter2>(__b));
    }
#endif

    // next
    template <class _Iterator>
    CANN_ASC_STL_API static constexpr _Iterator next(_Iterator, _Iterator __last)
    {
        return __last;
    }

    template <class _Iter>
    CANN_ASC_STL_API static constexpr remove_cvref_t<_Iter> next(
        _Iter&& __it, __difference_type<remove_cvref_t<_Iter>> __n = 1)
    {
        return ::asc::std::next(::asc::std::forward<_Iter>(__it), __n);
    }

    // prev
    template <class _Iter>
    CANN_ASC_STL_API static constexpr remove_cvref_t<_Iter> prev(
        _Iter&& __iter, __difference_type<remove_cvref_t<_Iter>> __n = 1)
    {
        return ::asc::std::prev(::asc::std::forward<_Iter>(__iter), __n);  // NOLINT(build/include_what_you_use)
    }

    template <class _Iter>
    CANN_ASC_STL_API static constexpr void __advance_to(_Iter& __first, _Iter __last)
    {
        __first = __last;
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_ITERATOR_OPERATIONS_H
