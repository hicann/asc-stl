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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_ITERATOR_OPERATIONS_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_ITERATOR_OPERATIONS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/iter_swap.h>
#include <asc/std/__algorithm/ranges_iterator_concept.h>
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

CANN_ASC_STL_BEGIN_NAMESPACE

// Classic iterator operation set (policy layer for the algorithm family):
// algorithm templates take this struct as their _AlgPolicy parameter and
// dispatch iterator operations through its static members instead of hard-coding
// prefixed asc::std:: algorithms, allowing later per-policy extensions. Provides
// the full classic operation set: value/difference type aliases,
// advance/distance/next/prev/__advance_to, iter_move's reference/value dual
// dispatch (with reference-consistency diagnostics) and iter_swap's
// host/device dual path.
struct __classic_algorithm_iterator_operations {
    template <class _Iter>
    using __value_type = typename iterator_traits<_Iter>::value_type;

    template <class _Iter>
    using __difference_type = typename iterator_traits<_Iter>::difference_type;

    // advance
    template <class _Iter, class _Distance>
    CANN_ASC_STL_API static constexpr void advance(_Iter& __iter, _Distance __count)
    {
        ::asc::std::advance(__iter, __count);
    }

    // distance
    template <class _Iter>
    CANN_ASC_STL_API static constexpr typename iterator_traits<_Iter>::difference_type distance(
        _Iter __first, _Iter __last)
    {
        return ::asc::std::distance(__first, __last);  // NOLINT(build/include_what_you_use)
    }

    template <class _Iter>
    using __deref_t = decltype(*::asc::std::declval<_Iter&>());

    template <class _Iter>
    using __move_t = decltype(::asc::std::move(*::asc::std::declval<_Iter&>()));  // NOLINT(build/include_what_you_use)

    template <class _Iter>
    CANN_ASC_STL_API static constexpr void __validate_iter_reference()
    {
        static_assert(is_same_v<__deref_t<_Iter>, typename iterator_traits<remove_cvref_t<_Iter>>::reference>,
            "It looks like your iterator's `iterator_traits<It>::reference` does not match the return type of "
            "dereferencing the iterator, i.e., calling `*it`. This is undefined behavior according to "
            "[input.iterators] and can lead to dangling reference issues at runtime, so we are flagging this.");
    }

    // iter_move: return with move semantics when dereferencing yields a
    // reference; return by value (proxy iterators) otherwise to avoid returning
    // a dangling reference; both branches validate that
    // iterator_traits::reference agrees with *it.
    template <class Iterator, enable_if_t<is_reference_v<__deref_t<Iterator>>, int> = 0>
    CANN_ASC_STL_API static constexpr __move_t<Iterator> iter_move(Iterator&& iterator) noexcept(
        noexcept(::asc::std::move(*::asc::std::forward<Iterator>(iterator))))
    {
        __validate_iter_reference<Iterator>();
        return ::asc::std::move(                        // NOLINT(build/include_what_you_use)
            *::asc::std::forward<Iterator>(iterator));  // NOLINT(build/include_what_you_use)
    }

    template <class Iterator, enable_if_t<!is_reference_v<__deref_t<Iterator>>, int> = 0>
    CANN_ASC_STL_API static constexpr __deref_t<Iterator> iter_move(Iterator&& iterator) noexcept(
        noexcept(*::asc::std::forward<Iterator>(iterator)))
    {
        __validate_iter_reference<Iterator>();
        return *::asc::std::forward<Iterator>(iterator);
    }

    // iter_swap: the host uses the ranges customization point (prefer ADL
    // iter_swap, fall back to swap(*a, *b)); under CCE device compilation the
    // ADL branch of the ranges CPO fails to instantiate (observed error: no
    // matching function for call to object), so it falls back to classic
    // iter_swap (i.e. swap(*a, *b)).
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class Iterator1, class Iterator2>
    CANN_ASC_STL_API static constexpr void iter_swap(Iterator1 left, Iterator2 right) noexcept(
        noexcept(::asc::std::iter_swap(left, right)))
    {
        ::asc::std::iter_swap(left, right);
    }
#else
    template <class Iterator1, class Iterator2>
    CANN_ASC_STL_API static constexpr void iter_swap(Iterator1 left, Iterator2 right) noexcept(
        noexcept(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left, right)))
    {
        ::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left, right);
    }
#endif

    // next: with a known bound, take the end iterator directly; otherwise
    // advance n steps via asc::std::next
    template <class _Iterator>
    CANN_ASC_STL_API static constexpr _Iterator next(_Iterator, _Iterator __last)
    {
        return __last;
    }

    template <class _Iter>
    CANN_ASC_STL_API static constexpr remove_cvref_t<_Iter> next(
        _Iter&& __iter, __difference_type<remove_cvref_t<_Iter>> __count = 1)
    {
        return ::asc::std::next(::asc::std::forward<_Iter>(__iter), __count);  // NOLINT(build/include_what_you_use)
    }

    // prev
    template <class _Iter>
    CANN_ASC_STL_API static constexpr remove_cvref_t<_Iter> prev(
        _Iter&& __iter, __difference_type<remove_cvref_t<_Iter>> __count = 1)
    {
        return ::asc::std::prev(::asc::std::forward<_Iter>(__iter), __count);  // NOLINT(build/include_what_you_use)
    }

    // __advance_to: advance directly to a known end point
    template <class _Iter>
    CANN_ASC_STL_API static constexpr void __advance_to(_Iter& __first, _Iter __last)
    {
        __first = __last;
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_ITERATOR_OPERATIONS_H
