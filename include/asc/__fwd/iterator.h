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

#ifndef CANN_ASC_STL_DETAIL_FWD_ITERATOR_H
#define CANN_ASC_STL_DETAIL_FWD_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__fwd/random.h>
#include <asc/std/__concepts/arithmetic.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/cstdint>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Tp, class _Index = ::asc::std::ptrdiff_t>
class constant_iterator;

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEVAL auto __get_wider_signed() noexcept
{
    if constexpr (sizeof(_Tp) < sizeof(int)) {
        return ::asc::std::type_identity<int>{};
    } else if constexpr (sizeof(_Tp) < sizeof(long)) {
        return ::asc::std::type_identity<long>{};
    }
#if CANN_ASC_STL_DETAIL_HAS_INT128()
    else if constexpr (sizeof(_Tp) < sizeof(long long)) {
        return ::asc::std::type_identity<long long>{};
    } else  // if constexpr (sizeof(_Start) < sizeof(__int128_t))  // NOLINT(readability/braces)
    {
        return ::asc::std::type_identity<__int128_t>{};
    }
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_INT128() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_INT128() vvv
    else  // if constexpr (sizeof(_Start) < sizeof(long long))
    {
        return ::asc::std::type_identity<long long>{};
    }
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()
}

template <class _Start>
using _IotaDiffT =
    typename ::asc::std::conditional_t<(!::asc::std::integral<_Start> ||
                                           sizeof(::asc::std::iter_difference_t<_Start>) > sizeof(_Start)),
        ::asc::std::type_identity<::asc::std::iter_difference_t<_Start>>,
        decltype(::asc::__get_wider_signed<_Start>())>::type;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <::asc::std::weakly_incrementable _Start, ::asc::std::signed_integral _DiffT = _IotaDiffT<_Start>>
    requires ::asc::std::copyable<_Start>
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Start, class _DiffT = _IotaDiffT<_Start>,
    ::asc::std::enable_if_t<::asc::std::weakly_incrementable<_Start>, int> = 0,
    ::asc::std::enable_if_t<::asc::std::copyable<_Start>, int> = 0,
    ::asc::std::enable_if_t<::asc::std::signed_integral<_DiffT>, int> = 0>
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^
class counting_iterator;

class discard_iterator;

template <class _Iter, class _Index = _Iter>
class permutation_iterator;

template <class _IndexType = ::asc::std::size_t, class _Bijection = random_bijection<_IndexType>>
class shuffle_iterator;

template <class _Iter, class _Stride = ::asc::std::iter_difference_t<_Iter>>
class strided_iterator;

template <class _Fn, class _Index = ::asc::std::ptrdiff_t>
class tabulate_output_iterator;

template <class _InputFn, class _OutputFn, class _Iter>
class transform_input_output_iterator;

template <class _Fn, class _Iter>
class transform_iterator;

template <class _Fn, class _Iter>
class transform_output_iterator;

template <class... _Iterators>
class zip_iterator;

template <class>
inline constexpr bool __is_zip_iterator = false;

template <class... _Iterators>
inline constexpr bool __is_zip_iterator<zip_iterator<_Iterators...>> = true;

template <class _Fn>
class zip_function;

template <class>
inline constexpr bool __is_zip_function = false;

template <class _Fn>
inline constexpr bool __is_zip_function<zip_function<_Fn>> = true;

template <class _Fn, class... _Iterators>
class zip_transform_iterator;

template <class>
inline constexpr bool __is_zip_transform_iterator = false;

template <class _Fn, class... _Iterators>
inline constexpr bool __is_zip_transform_iterator<zip_transform_iterator<_Fn, _Iterators...>> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC
#endif  // CANN_ASC_STL_DETAIL_FWD_ITERATOR_H
