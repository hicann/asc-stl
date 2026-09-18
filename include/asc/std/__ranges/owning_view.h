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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_OWNING_VIEW_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_OWNING_VIEW_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/data.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/move.h>
#include <asc/std/initializer_list>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <range _Rp>
    requires movable<_Rp> && (!__is_asc_std_initializer_list<remove_cvref_t<_Rp>>)
class owning_view : public view_interface<owning_view<_Rp>> {
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
template <class _Rp, enable_if_t<range<_Rp>, int> = 0, enable_if_t<movable<_Rp>, int> = 0,
    enable_if_t<!__is_asc_std_initializer_list<remove_cvref_t<_Rp>>, int> = 0>
class owning_view : public view_interface<owning_view<_Rp>> {
#endif  // !concepts
    _Rp __r_ = _Rp();

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI owning_view()
        requires default_initializable<_Rp>
    = default;
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range = _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(default_initializable<_Range>)
    CANN_ASC_STL_API constexpr owning_view() noexcept(is_nothrow_default_constructible_v<_Range>)
        : view_interface<owning_view<_Rp>>()
    {}
#endif  // !concepts

    CANN_ASC_STL_API constexpr owning_view(_Rp&& __r) noexcept(is_nothrow_move_constructible_v<_Rp>)
        : view_interface<owning_view<_Rp>>(), __r_(::asc::std::move(__r))
    {}

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI owning_view(owning_view&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI owning_view& operator=(owning_view&&) = default;

    [[nodiscard]] CANN_ASC_STL_API constexpr _Rp& base() & noexcept
    {
        return __r_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Rp& base() const& noexcept
    {
        return __r_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr _Rp&& base() && noexcept
    {
        return ::asc::std::move(__r_);
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Rp&& base() const&& noexcept
    {
        return ::asc::std::move(__r_);  // NOLINT(build/include_what_you_use)
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr iterator_t<_Rp> begin()
    {
        return ::asc::std::ranges::__begin_cpo{}(__r_);
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr sentinel_t<_Rp> end()
    {
        return ::asc::std::ranges::__end_cpo{}(__r_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range = _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(range<const _Range>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto begin() const
    {
        return ::asc::std::ranges::__begin_cpo{}(__r_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range = _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(range<const _Range>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto end() const
    {
        return ::asc::std::ranges::__end_cpo{}(__r_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range = _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(invocable<::asc::std::ranges::__empty::__fn, _Range&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool empty()
    {
        return ::asc::std::ranges::__empty_cpo{}(__r_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range = _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(invocable<::asc::std::ranges::__empty::__fn, const _Range&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool empty() const
    {
        return ::asc::std::ranges::__empty_cpo{}(__r_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range = _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(sized_range<_Range>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto size()
    {
        return ::asc::std::ranges::__size_cpo{}(__r_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range = _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(sized_range<const _Range>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::ranges::__size_cpo{}(__r_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range = _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(contiguous_range<_Range>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto data()
    {
        return ::asc::std::ranges::__data_cpo{}(__r_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range = _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(contiguous_range<const _Range>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto data() const
    {
        return ::asc::std::ranges::__data_cpo{}(__r_);
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(owning_view);

template <class _Rp>
inline constexpr bool enable_borrowed_range<owning_view<_Rp>> = enable_borrowed_range<_Rp>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_OWNING_VIEW_H
