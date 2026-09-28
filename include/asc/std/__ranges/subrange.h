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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_SUBRANGE_H
#define CANN_ASC_STL_ASC_STD___RANGES_SUBRANGE_H

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
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/different_from.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/subrange.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator Iter, sentinel_for<Iter> Sent, subrange_kind Kind>
    requires(Kind == subrange_kind::sized || !sized_sentinel_for<Sent, Iter>)
#else
template <class Iter, class Sent, subrange_kind Kind>
#endif
class subrange : public view_interface<subrange<Iter, Sent, Kind>> {
public:
    using iterator = Iter;
    using sentinel = Sent;
    using size_type = make_unsigned_t<iter_difference_t<Iter>>;
    CANN_ASC_STL_API constexpr subrange() = default;
    CANN_ASC_STL_API constexpr subrange(Iter first, Sent last)
        : first_(first), last_(last), size_(initial_size(first, last))
    {}
    CANN_ASC_STL_API constexpr subrange(Iter first, Sent last, size_type size) : first_(first), last_(last), size_(size)
    {}
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    template <borrowed_range Range>
#else
    template <class Range,
        enable_if_t<is_lvalue_reference_v<Range&&> || enable_borrowed_range<remove_cvref_t<Range>>, int> = 0>
#endif
    CANN_ASC_STL_API constexpr subrange(Range&& range)
        : first_(ranges::begin(range)), last_(ranges::end(range)), size_(initial_size(range))
    {}
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    template <borrowed_range Range>
#else
    template <class Range,
        enable_if_t<is_lvalue_reference_v<Range&&> || enable_borrowed_range<remove_cvref_t<Range>>, int> = 0>
#endif
    CANN_ASC_STL_API constexpr subrange(Range&& range, size_type size)
        : first_(ranges::begin(range)), last_(ranges::end(range)), size_(size)
    {}
    CANN_ASC_STL_API constexpr Iter begin()
    {
        return first_;
    }
    CANN_ASC_STL_API constexpr Iter begin() const
    {
        return first_;
    }
    CANN_ASC_STL_API constexpr Sent end() const
    {
        return last_;
    }
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return first_ == last_;
    }
    CANN_ASC_STL_API constexpr size_type size() const
    {
        return Kind == subrange_kind::sized ? size_ : static_cast<size_type>(last_ - first_);
    }
    CANN_ASC_STL_API constexpr subrange& advance(__PTRDIFF_TYPE__ amount)
    {
        ::asc::std::advance(first_, amount);
        if constexpr (Kind == subrange_kind::sized) {
            size_ = static_cast<size_type>(static_cast<iter_difference_t<Iter>>(size_) - amount);
        }
        return *this;
    }
    CANN_ASC_STL_API constexpr subrange next(__PTRDIFF_TYPE__ amount = 1) const&
    {
        auto copy = *this;
        copy.advance(amount);
        return copy;
    }
    CANN_ASC_STL_API constexpr subrange next(__PTRDIFF_TYPE__ amount = 1) &&
    {
        advance(amount);
        return ::asc::std::move(*this);  // NOLINT(build/include_what_you_use)
    }
    CANN_ASC_STL_API constexpr subrange prev(__PTRDIFF_TYPE__ amount = 1) const
    {
        return next(-amount);
    }

private:
    CANN_ASC_STL_API static constexpr size_type initial_size(Iter first, Sent last)
    {
        if constexpr (Kind == subrange_kind::sized) {
            return static_cast<size_type>(last - first);
        }
        return 0;
    }
    template <class Range>
    CANN_ASC_STL_API static constexpr size_type initial_size(Range& range)
    {
        if constexpr (Kind == subrange_kind::sized) {
            return static_cast<size_type>(ranges::size(range));
        }
        return 0;
    }
    Iter first_{};
    Sent last_{};
    size_type size_{};
};
template <class I, class S, subrange_kind K>
inline constexpr bool enable_borrowed_range<subrange<I, S, K>> = true;
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class Range>
using borrowed_subrange_t = conditional_t<borrowed_range<Range>, subrange<iterator_t<Range>>, dangling>;
#else
template <class Range>
using borrowed_subrange_t = conditional_t<is_lvalue_reference_v<Range> || enable_borrowed_range<remove_cvref_t<Range>>,
    subrange<iterator_t<Range>>, dangling>;
#endif
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_SUBRANGE_H
