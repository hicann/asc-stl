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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_REF_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_REF_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/data.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// 判定 _Tp 能否转换为 _Range 的左值（排除把右值绑定到左值引用的路径）。
template <class _Range>
struct __conversion_tester {
    CANN_ASC_STL_API static void __fun(_Range&);
    static void __fun(_Range&&) = delete;
};

template <class _Tp, class _Range, class = void>
struct __convertible_to_lvalue : false_type {};
template <class _Tp, class _Range>
struct __convertible_to_lvalue<_Tp, _Range,
    void_t<decltype(__conversion_tester<_Range>::__fun(::asc::std::declval<_Tp>()))>> : true_type {};

// 成员门控：empty()/size()/data() 仅在对应 CPO 可调用时提供，
// 以基座惯用的 void_t 探测结构 + enable_if_t 展开，C++17 与设备路径同样可用。
template <class T, class = void>
struct __ref_view_has_empty : false_type {};
template <class T>
struct __ref_view_has_empty<T, void_t<decltype((void)::asc::std::ranges::__empty_cpo{}(::asc::std::declval<T>()))>>
    : true_type {};

template <class T, class = void>
struct __ref_view_has_size : false_type {};
template <class T>
struct __ref_view_has_size<T, void_t<decltype((void)::asc::std::ranges::__size_cpo{}(::asc::std::declval<T&>()))>>
    : true_type {};

template <class T, class = void>
struct __ref_view_has_data : false_type {};
template <class T>
struct __ref_view_has_data<T, void_t<decltype((void)::asc::std::ranges::__data_cpo{}(::asc::std::declval<T&>()))>>
    : true_type {};

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <range _Range>
    requires is_object_v<_Range>
#else
template <class _Range>
#endif
class ref_view : public view_interface<ref_view<_Range>> {
    _Range* __range_;

public:
    template <class _Tp,
        enable_if_t<!is_same_v<remove_cvref_t<_Tp>, ref_view> && is_convertible_v<_Tp, _Range&> &&
                __convertible_to_lvalue<_Tp, _Range>::value,
            int> = 0>
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

    template <class _Range2 = _Range, enable_if_t<__ref_view_has_empty<const _Range2&>::value, int> = 0>
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return ::asc::std::ranges::__empty_cpo{}(*__range_);
    }

    template <class _Range2 = _Range, enable_if_t<__ref_view_has_size<_Range2>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::ranges::__size_cpo{}(*__range_);
    }

    template <class _Range2 = _Range, enable_if_t<__ref_view_has_data<_Range2>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto data() const
    {
        return ::asc::std::ranges::__data_cpo{}(*__range_);
    }
};

template <class _Range>
ref_view(_Range&) -> ref_view<_Range>;

template <class _Tp>
inline constexpr bool enable_borrowed_range<ref_view<_Tp>> = true;

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_REF_VIEW_H
