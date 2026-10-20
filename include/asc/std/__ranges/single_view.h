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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_SINGLE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_SINGLE_VIEW_H

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
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// The shared movable box supports move-only and non-default-constructible
// elements without requiring their assignment operators.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <move_constructible _Tp>
    requires is_object_v<_Tp>
#else
template <class _Tp>
#endif
class single_view : public view_interface<single_view<_Tp>> {
    static_assert(move_constructible<_Tp> && (is_object_v<_Tp>), "range view constraints are not satisfied");

    CANN_ASC_STL_NO_UNIQUE_ADDRESS __movable_box<_Tp> __value_;

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr single_view()
        requires default_initializable<_Tp>
    = default;
#else
    template <bool __asc_enabled = true, enable_if_t<__asc_enabled && (default_initializable<_Tp>), int> = 0>
    CANN_ASC_STL_API constexpr single_view()
    {}
#endif

    CANN_ASC_STL_DETAIL_TEMPLATE(class _Tp2 = _Tp)
    CANN_ASC_STL_DETAIL_REQUIRES(((!is_same_v<remove_cvref_t<_Tp2>, single_view> && copy_constructible<_Tp2>)))
    CANN_ASC_STL_API constexpr explicit single_view(const _Tp2& __t) noexcept(is_nothrow_copy_constructible_v<_Tp2>)
        : view_interface<single_view<_Tp>>(), __value_(in_place_t{}, __t)
    {}

    CANN_ASC_STL_API constexpr explicit single_view(_Tp&& __t) noexcept(is_nothrow_move_constructible_v<_Tp>)
        : view_interface<single_view<_Tp>>(), __value_(in_place_t{}, ::asc::std::move(__t))
    {}

    CANN_ASC_STL_DETAIL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_REQUIRES((constructible_from<_Tp, _Args...>))
    CANN_ASC_STL_API constexpr explicit single_view(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : view_interface<single_view<_Tp>>(), __value_{in_place_t{}, ::asc::std::forward<_Args>(__args)...}
    {}

    CANN_ASC_STL_API constexpr _Tp* begin() noexcept
    {
        return data();
    }

    CANN_ASC_STL_API constexpr const _Tp* begin() const noexcept
    {
        return data();
    }

    CANN_ASC_STL_API constexpr _Tp* end() noexcept
    {
        return data() + 1;
    }

    CANN_ASC_STL_API constexpr const _Tp* end() const noexcept
    {
        return data() + 1;
    }

    CANN_ASC_STL_API static constexpr size_t size() noexcept
    {
        return 1;
    }

    CANN_ASC_STL_API constexpr _Tp* data() noexcept
    {
        return __value_.operator->();
    }

    CANN_ASC_STL_API constexpr const _Tp* data() const noexcept
    {
        return __value_.operator->();
    }
};

template <class _Tp>
CANN_ASC_STL_HOST_DEVICE single_view(_Tp) -> single_view<_Tp>;

namespace views {

namespace __single_view_detail {

template <class T, bool = is_object_v<decay_t<T>> && move_constructible<decay_t<T>>>
struct __can_single_view : false_type {};
template <class T>
struct __can_single_view<T, true> : is_constructible<single_view<decay_t<T>>, T> {};

struct __fn : ::asc::std::ranges::__range_adaptor_closure<__fn> {
    template <class T, enable_if_t<__can_single_view<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(single_view<decay_t<T>>(::asc::std::forward<T>(value)))) -> single_view<decay_t<T>>
    {
        return single_view<decay_t<T>>(::asc::std::forward<T>(value));  // NOLINT(build/include_what_you_use)
    }
};

}  // namespace __single_view_detail

inline constexpr __single_view_detail::__fn single{};

}  // namespace views

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_SINGLE_VIEW_H
