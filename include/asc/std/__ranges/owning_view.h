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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_OWNING_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_OWNING_VIEW_H

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
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/data.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {

// Class-level contract (C++20 [range.owning.view]): a movable range; the backing
// array of an initializer_list does not outlive the view, so owning one is
// forbidden on every standard path (the constraint stays SFINAE-friendly so the
// CTAD probing in views::all can fail gracefully).
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class Range>
    requires range<Range> && movable<Range> && (!__is_asc_std_initializer_list<remove_cvref_t<Range>>)
#else
template <class Range>
#endif
class owning_view : public view_interface<owning_view<Range>> {
    static_assert((range<Range> && movable<Range> && (!__is_asc_std_initializer_list<remove_cvref_t<Range>>)),
        "range view constraints are not satisfied");

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr owning_view()
        requires default_initializable<Range>
    = default;
#else
    template <bool __asc_enabled = true, enable_if_t<__asc_enabled && (default_initializable<Range>), int> = 0>
    CANN_ASC_STL_API constexpr owning_view()
    {}
#endif
    CANN_ASC_STL_API constexpr owning_view(Range&& range) noexcept(is_nothrow_move_constructible_v<Range>)
        : range_(::asc::std::move(range))
    {}
    CANN_ASC_STL_API constexpr auto begin()
    {
        return __begin_cpo{}(range_);
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class Range2 = Range)
    CANN_ASC_STL_DETAIL_REQUIRES((range<const Range2>))
    CANN_ASC_STL_API constexpr auto begin() const
    {
        return __begin_cpo{}(range_);
    }
    CANN_ASC_STL_API constexpr auto end()
    {
        return __end_cpo{}(range_);
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class Range2 = Range)
    CANN_ASC_STL_DETAIL_REQUIRES((range<const Range2>))
    CANN_ASC_STL_API constexpr auto end() const
    {
        return __end_cpo{}(range_);
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class Range2 = Range)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<Range2>))
    CANN_ASC_STL_API constexpr auto size()
    {
        return __size_cpo{}(range_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range2 = Range)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<const Range2>))
    CANN_ASC_STL_API constexpr auto size() const
    {
        return __size_cpo{}(range_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range2 = Range)
    CANN_ASC_STL_DETAIL_REQUIRES((invocable<__empty_cpo, Range2&>))
    CANN_ASC_STL_API constexpr bool empty()
    {
        return __empty_cpo{}(range_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range2 = Range)
    CANN_ASC_STL_DETAIL_REQUIRES((invocable<__empty_cpo, const Range2&>))
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return __empty_cpo{}(range_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range2 = Range)
    CANN_ASC_STL_DETAIL_REQUIRES((contiguous_range<Range2>))
    CANN_ASC_STL_API constexpr auto data()
    {
        return __data_cpo{}(range_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range2 = Range)
    CANN_ASC_STL_DETAIL_REQUIRES((contiguous_range<const Range2>))
    CANN_ASC_STL_API constexpr auto data() const
    {
        return __data_cpo{}(range_);
    }

    CANN_ASC_STL_API constexpr Range& base() & noexcept
    {
        return range_;
    }
    CANN_ASC_STL_API constexpr const Range& base() const& noexcept
    {
        return range_;
    }
    CANN_ASC_STL_API constexpr Range&& base() && noexcept
    {
        return ::asc::std::move(range_);  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API constexpr const Range&& base() const&& noexcept
    {
        return ::asc::std::move(range_);  // NOLINT(build/include_what_you_use)
    }

private:
    Range range_{};
};

CANN_ASC_STL_DETAIL_CTAD_SUPPORTED_FOR_TYPE(owning_view);
CANN_ASC_STL_DETAIL_TEMPLATE(class Range)
CANN_ASC_STL_DETAIL_REQUIRES(range<Range>&& movable<Range> && !__is_asc_std_initializer_list<remove_cvref_t<Range>>)
CANN_ASC_STL_HOST_DEVICE owning_view(Range&&) -> owning_view<Range>;
template <class R>
inline constexpr bool enable_borrowed_range<owning_view<R>> = enable_borrowed_range<R>;
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_OWNING_VIEW_H
