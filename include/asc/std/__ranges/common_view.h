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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_COMMON_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_COMMON_VIEW_H

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
#include <asc/__detail/execution_space.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__iterator/common_iterator.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// Both language modes and execution spaces share the same view semantics.
// The shared constraints select native concepts or SFINAE as appropriate.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <view _View>
    requires(!common_range<_View> && copyable<iterator_t<_View>>)
#else
template <class _View>
#endif
class common_view : public view_interface<common_view<_View>> {
    static_assert(view<_View> && ((!common_range<_View> && copyable<iterator_t<_View>>)),
        "range view constraints are not satisfied");

private:
    _View __base_ = _View();

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr common_view()
        requires ::asc::std::default_initializable<_View>
    = default;
#else
    template <bool __asc_enabled = true,
        enable_if_t<__asc_enabled && (::asc::std::default_initializable<_View>), int> = 0>
    CANN_ASC_STL_API constexpr common_view()
    {}
#endif

    CANN_ASC_STL_API constexpr explicit common_view(_View __v) noexcept(is_nothrow_move_constructible_v<_View>)
        : __base_(::asc::std::move(__v))
    {}

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((::asc::std::copy_constructible<_View2>))
    CANN_ASC_STL_API constexpr _View base() const& noexcept(::asc::std::is_nothrow_copy_constructible_v<_View2>)
    {
        return __base_;
    }

    CANN_ASC_STL_API constexpr _View base() && noexcept(::asc::std::is_nothrow_move_constructible_v<_View>)
    {
        return ::asc::std::move(__base_);  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_API constexpr auto begin()
    {
        return common_iterator<iterator_t<_View>, sentinel_t<_View>>{::asc::std::ranges::__begin_cpo{}(__base_)};
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((range<const _View2>))
    CANN_ASC_STL_API constexpr auto begin() const
    {
        return common_iterator<iterator_t<const _View>, sentinel_t<const _View>>{
            ::asc::std::ranges::__begin_cpo{}(__base_)};
    }

    CANN_ASC_STL_API constexpr auto end()
    {
        return common_iterator<iterator_t<_View>, sentinel_t<_View>>{::asc::std::ranges::__end_cpo{}(__base_)};
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((range<const _View2>))
    CANN_ASC_STL_API constexpr auto end() const
    {
        return common_iterator<iterator_t<const _View>, sentinel_t<const _View>>{
            ::asc::std::ranges::__end_cpo{}(__base_)};
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<_View2>))
    CANN_ASC_STL_API constexpr auto size()
    {
        return ::asc::std::ranges::__size_cpo{}(__base_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<const _View2>))
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::ranges::__size_cpo{}(__base_);
    }
};

template <class _Range>
CANN_ASC_STL_HOST_DEVICE common_view(_Range&&) -> common_view<::asc::std::ranges::views::all_t<_Range>>;

template <class _View>
inline constexpr bool enable_borrowed_range<common_view<_View>> = enable_borrowed_range<_View>;

}  // namespace ranges

namespace ranges::views {

namespace __common {

struct __fn : __range_adaptor_closure<__fn> {
    // Ranges that are already common pass through directly (an all wrapper), without
    // an extra common_view.
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Range)
    CANN_ASC_STL_DETAIL_REQUIRES((common_range<_Range>))
    CANN_ASC_STL_API constexpr all_t<_Range> operator()(_Range&& __range) const
        noexcept(noexcept(::asc::std::ranges::views::all(::asc::std::forward<_Range>(__range))))
    {
        return ::asc::std::ranges::views::all(::asc::std::forward<_Range>(__range));
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _Range)
    CANN_ASC_STL_DETAIL_REQUIRES(((!common_range<_Range>)))
    CANN_ASC_STL_API constexpr common_view<all_t<_Range>> operator()(_Range&& __range) const
    {
        return common_view<all_t<_Range>>(::asc::std::ranges::views::all(
            ::asc::std::forward<_Range>(__range)));  // NOLINT(build/include_what_you_use)
    }
};

}  // namespace __common

inline constexpr __common::__fn common{};

}  // namespace ranges::views

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_COMMON_VIEW_H
