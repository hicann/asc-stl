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
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

// Class-level contract (C++20 [range.owning.view]): a movable range; the backing
// array of an initializer_list does not outlive the view, so owning one is
// forbidden on every standard path (the constraint stays SFINAE-friendly so the
// CTAD probing in views::all can fail gracefully).
template <class Range>
    requires range<Range> && movable<Range> && (!__is_asc_std_initializer_list<remove_cvref_t<Range>>)
class owning_view : public view_interface<owning_view<Range>> {
public:
    CANN_ASC_STL_API constexpr owning_view()
        requires default_initializable<Range>
    = default;
    CANN_ASC_STL_API constexpr owning_view(Range&& range) noexcept(is_nothrow_move_constructible_v<Range>)
        : range_(::asc::std::move(range))
    {}
    CANN_ASC_STL_API constexpr auto begin()
    {
        return __begin_cpo{}(range_);
    }
    template <class Range2 = Range>
        requires range<const Range2>
    CANN_ASC_STL_API constexpr auto begin() const
    {
        return __begin_cpo{}(range_);
    }
    CANN_ASC_STL_API constexpr auto end()
    {
        return __end_cpo{}(range_);
    }
    template <class Range2 = Range>
        requires range<const Range2>
    CANN_ASC_STL_API constexpr auto end() const
    {
        return __end_cpo{}(range_);
    }
    template <class Range2 = Range>
        requires sized_range<Range2>
    CANN_ASC_STL_API constexpr auto size()
    {
        return __size_cpo{}(range_);
    }

    template <class Range2 = Range>
        requires sized_range<const Range2>
    CANN_ASC_STL_API constexpr auto size() const
    {
        return __size_cpo{}(range_);
    }

    template <class Range2 = Range>
        requires invocable<__empty_cpo, Range2&>
    CANN_ASC_STL_API constexpr bool empty()
    {
        return __empty_cpo{}(range_);
    }

    template <class Range2 = Range>
        requires invocable<__empty_cpo, const Range2&>
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return __empty_cpo{}(range_);
    }

    template <class Range2 = Range>
        requires contiguous_range<Range2>
    CANN_ASC_STL_API constexpr auto data()
    {
        return __data_cpo{}(range_);
    }

    template <class Range2 = Range>
        requires contiguous_range<const Range2>
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

#else

// Non-concepts path (C++17 and device compilation): keeps the conventional
// lazily-instantiated template-member shape.
template <class Range>
class owning_view : public view_interface<owning_view<Range>> {
    // initializer_list elements dangle almost immediately, so owning one is
    // forbidden on this path too.
    static_assert(!__is_asc_std_initializer_list<remove_cvref_t<Range>>,
        "owning_view must not own an initializer_list; wrap it in another view first");

public:
    CANN_ASC_STL_API constexpr owning_view() = default;
    CANN_ASC_STL_API constexpr owning_view(Range&& range) noexcept(is_nothrow_move_constructible_v<Range>)
        : range_(::asc::std::move(range))
    {}
    CANN_ASC_STL_API constexpr auto begin()
    {
        return __begin_cpo{}(range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr auto begin() const
    {
        return __begin_cpo{}(range_);
    }
    CANN_ASC_STL_API constexpr auto end()
    {
        return __end_cpo{}(range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr auto end() const
    {
        return __end_cpo{}(range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr auto size()
    {
        return __size_cpo{}(range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr auto size() const
    {
        return __size_cpo{}(range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr bool empty()
    {
        return __empty_cpo{}(range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return __empty_cpo{}(range_);
    }
    template <class Range2 = Range>
    CANN_ASC_STL_API constexpr auto data()
    {
        return __data_cpo{}(range_);
    }
    template <class Range2 = Range>
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

#endif

CANN_ASC_STL_DETAIL_CTAD_SUPPORTED_FOR_TYPE(owning_view);
template <class R>
inline constexpr bool enable_borrowed_range<owning_view<R>> = enable_borrowed_range<R>;
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_OWNING_VIEW_H
