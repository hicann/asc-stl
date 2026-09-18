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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_REF_VIEW_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_REF_VIEW_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/different_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/data.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

template <class _Range>
struct __conversion_tester {
    CANN_ASC_STL_API static void __fun(_Range&);
    static void __fun(_Range&&) = delete;
};

template <class _Tp, class _Range>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __convertible_to_lvalue =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Tp, _Range))((__conversion_tester<_Range>::__fun(declval<_Tp>())));

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <range _Range>
    requires is_object_v<_Range>
class ref_view : public view_interface<ref_view<_Range>> {
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
template <class _Range, enable_if_t<range<_Range>, int> = 0, enable_if_t<is_object_v<_Range>, int> = 0>
class ref_view : public view_interface<ref_view<_Range>> {
#endif  // !concepts
    _Range* __range_;

public:
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __different_from<_Tp, ref_view> CANN_ASC_STL_DETAIL_ACCL_AND convertible_to<_Tp, _Range&>
            CANN_ASC_STL_DETAIL_ACCL_AND __convertible_to_lvalue<_Tp, _Range>)
    CANN_ASC_STL_API constexpr ref_view(_Tp&& __t)
        : view_interface<ref_view<_Range>>(),
          __range_(::asc::std::addressof(
              static_cast<_Range&>(::asc::std::forward<_Tp>(__t))))  // NOLINT(build/include_what_you_use)
    {}

    CANN_ASC_STL_API constexpr _Range& base() const
    {
        return *__range_;
    }

    CANN_ASC_STL_API constexpr iterator_t<_Range> begin() const
    {
        return ::asc::std::ranges::__begin_cpo{}(*__range_);
    }

    CANN_ASC_STL_API constexpr sentinel_t<_Range> end() const
    {
        return ::asc::std::ranges::__end_cpo{}(*__range_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range2 = _Range)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(invocable<::asc::std::ranges::__empty::__fn, const _Range2&>)
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return ::asc::std::ranges::__empty_cpo{}(*__range_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range2 = _Range)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(sized_range<_Range2>)
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::ranges::__size_cpo{}(*__range_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range2 = _Range)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(contiguous_range<_Range2>)
    CANN_ASC_STL_API constexpr auto data() const
    {
        return ::asc::std::ranges::__data_cpo{}(*__range_);
    }
};

template <class _Range>
ref_view(_Range&) -> ref_view<_Range>;

template <class _Tp>
inline constexpr bool enable_borrowed_range<ref_view<_Tp>> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_REF_VIEW_H
