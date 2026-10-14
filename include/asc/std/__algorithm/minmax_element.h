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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MINMAX_ELEMENT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MINMAX_ELEMENT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/comp.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __minmax_element_detail {

// Minimal inline traversal probes: first probe
// iterator_traits<Iter>::iterator_category, then the Iter::iterator_concept
// member; both are SFINAE-friendly.
template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_category_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool
    __has_iterator_category_convertible_to<Iter, Tag, void_t<typename iterator_traits<Iter>::iterator_category>> =
        is_convertible_v<typename iterator_traits<Iter>::iterator_category, Tag>;

template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_concept_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool __has_iterator_concept_convertible_to<Iter, Tag, void_t<typename Iter::iterator_concept>> =
    is_convertible_v<typename Iter::iterator_concept, Tag>;

template <class Iter>
inline constexpr bool __has_input_traversal = __has_iterator_category_convertible_to<Iter, input_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, input_iterator_tag>;

}  // namespace __minmax_element_detail

template <class _Comp, class _Proj>
class _MinmaxElementLessFunc {
    _Comp& __comp_;
    _Proj& __proj_;

public:
    CANN_ASC_STL_API constexpr _MinmaxElementLessFunc(_Comp& __comp, _Proj& __proj) : __comp_(__comp), __proj_(__proj)
    {}

    template <class _Iter>
    CANN_ASC_STL_API constexpr bool operator()(_Iter& __it1, _Iter& __it2)
    {
        return ::asc::std::invoke(__comp_, ::asc::std::invoke(__proj_, *__it1), ::asc::std::invoke(__proj_, *__it2));
    }
};

template <class _Iter, class _Sent, class _Proj, class _Comp>
CANN_ASC_STL_API constexpr pair<_Iter, _Iter> __minmax_element_impl(
    _Iter __first, _Sent __last, _Comp& __comp, _Proj& __proj)
{
    auto __less = _MinmaxElementLessFunc<_Comp, _Proj>(__comp, __proj);

    pair<_Iter, _Iter> __result(__first, __first);
    if (__first == __last || ++__first == __last) {
        return __result;
    }

    if (__less(__first, __result.first)) {
        __result.first = __first;
    } else {
        __result.second = __first;
    }

    while (++__first != __last) {
        _Iter __i = __first;
        if (++__first == __last) {
            if (__less(__i, __result.first)) {
                __result.first = __i;
            } else if (!__less(__i, __result.second)) {
                __result.second = __i;
            }
            break;
        }

        if (__less(__first, __i)) {
            if (__less(__first, __result.first)) {
                __result.first = __first;
            }
            if (!__less(__i, __result.second)) {
                __result.second = __i;
            }
        } else {
            if (__less(__i, __result.first)) {
                __result.first = __i;
            }
            if (!__less(__first, __result.second)) {
                __result.second = __first;
            }
        }
    }

    return __result;
}

template <class _ForwardIterator, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_ForwardIterator, _ForwardIterator> minmax_element(
    _ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
{
    static_assert(__minmax_element_detail::__has_input_traversal<_ForwardIterator>,
        "::asc::std::minmax_element requires a ForwardIterator");
    static_assert(
        __is_callable<_Compare, decltype(*__first), decltype(*__first)>::value, "The comparator has to be callable");
    auto __proj = identity();
    return ::asc::std::__minmax_element_impl(__first, __last, __comp, __proj);
}

template <class _ForwardIterator>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<_ForwardIterator, _ForwardIterator>  // NOLINT(build/include_what_you_use)
minmax_element(                                                                    // NOLINT(build/include_what_you_use)
    _ForwardIterator __first, _ForwardIterator __last)
{
    return ::asc::std::minmax_element(__first, __last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MINMAX_ELEMENT_H
