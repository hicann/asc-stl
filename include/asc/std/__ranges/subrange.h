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
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/different_from.h>
#include <asc/std/__cstddef/types.h>
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
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {

// Non-slicing conversion check: a pointer-to-pointer array qualification
// conversion (Derived(*)[] -> Base(*)[]) must not silently enter the range.

template <class T>
using __subrange_array_pointer = T (*)[];
template <class From, class To, class = void>
inline constexpr bool __uses_nonqualification_pointer_conversion = false;
template <class From, class To>
inline constexpr bool __uses_nonqualification_pointer_conversion<From, To,
    void_t<enable_if_t<is_pointer_v<From> && is_pointer_v<To>>, __subrange_array_pointer<remove_pointer_t<From>>,
        __subrange_array_pointer<remove_pointer_t<To>>>> =
    !convertible_to<__subrange_array_pointer<remove_pointer_t<From>>, __subrange_array_pointer<remove_pointer_t<To>>>;

template <class From, class To>
inline constexpr bool __convertible_to_non_slicing =
    convertible_to<From, To> && !__uses_nonqualification_pointer_conversion<decay_t<From>, decay_t<To>>;

template <class Pair, class Iter, class Sent, class = void>
inline constexpr bool __pair_like_convertible_from = false;
template <class Pair, class Iter, class Sent>
inline constexpr bool __pair_like_convertible_from<Pair, Iter, Sent,
    void_t<decltype(tuple_size<remove_cvref_t<Pair>>::value), enable_if_t<tuple_size<remove_cvref_t<Pair>>::value == 2>,
        tuple_element_t<0, Pair>, tuple_element_t<1, Pair>>> =
    __tuple_like_ext<remove_cvref_t<Pair>> && !range<Pair> && constructible_from<Pair, Iter, Sent> &&
    __convertible_to_non_slicing<Iter, tuple_element_t<0, Pair>> && convertible_to<Sent, tuple_element_t<1, Pair>>;

template <class Iter, class It, bool StoreSize>
inline constexpr bool __subrange_from_iter_sent = !StoreSize && __convertible_to_non_slicing<It, Iter>;
template <class Iter, subrange_kind Kind, class It>
inline constexpr bool __subrange_from_iter_sent_size =
    Kind == subrange_kind::sized && __convertible_to_non_slicing<It, Iter>;

template <class Iter, class Sent, subrange_kind Kind, class Range, bool StoreSize, class = void>
inline constexpr bool __subrange_from_range = false;
template <class Iter, class Sent, subrange_kind Kind, class Range, bool StoreSize>
inline constexpr bool
    __subrange_from_range<Iter, Sent, Kind, Range, StoreSize, void_t<iterator_t<Range>, sentinel_t<Range>>> =
        StoreSize && __different_from<Range, subrange<Iter, Sent, Kind>> && borrowed_range<Range> &&
    __convertible_to_non_slicing<iterator_t<Range>, Iter> && convertible_to<sentinel_t<Range>, Sent>;

template <class Iter, class Sent, subrange_kind Kind, class Range, class = void>
inline constexpr bool __subrange_from_range_size = false;
template <class Iter, class Sent, subrange_kind Kind, class Range>
inline constexpr bool
    __subrange_from_range_size<Iter, Sent, Kind, Range, void_t<iterator_t<Range>, sentinel_t<Range>>> =
        Kind == subrange_kind::sized && borrowed_range<Range> &&
    __convertible_to_non_slicing<iterator_t<Range>, Iter> && convertible_to<sentinel_t<Range>, Sent>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator Iter, sentinel_for<Iter> Sent, subrange_kind Kind>
    requires(Kind == subrange_kind::sized || !sized_sentinel_for<Sent, Iter>)
#else
template <class Iter, class Sent, subrange_kind Kind>
#endif
class subrange : public view_interface<subrange<Iter, Sent, Kind>> {
    static_assert(input_or_output_iterator<Iter> && sentinel_for<Sent, Iter> &&
            ((Kind == subrange_kind::sized || !sized_sentinel_for<Sent, Iter>)),
        "range view constraints are not satisfied");

public:
    using iterator = Iter;
    using sentinel = Sent;
    using size_type = make_unsigned_t<iter_difference_t<Iter>>;
    // Internal implementation detail, public only for internal use (adaptor
    // passthrough / stored-size detection).
    static constexpr bool _StoreSize = (Kind == subrange_kind::sized && !sized_sentinel_for<Sent, Iter>);

private:
    struct _Empty {
        template <class T>
        CANN_ASC_STL_API constexpr _Empty(T) noexcept
        {}
    };

    using _Size = conditional_t<_StoreSize, make_unsigned_t<iter_difference_t<Iter>>, _Empty>;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS Iter __begin_ = Iter();
    CANN_ASC_STL_NO_UNIQUE_ADDRESS Sent __end_ = Sent();
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Size __size_ = 0;

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    subrange()
        requires default_initializable<Iter>
    = default;
#else
    template <bool __asc_enabled = true, enable_if_t<__asc_enabled && (default_initializable<Iter>), int> = 0>
    CANN_ASC_STL_API constexpr subrange()
    {}
#endif

    CANN_ASC_STL_DETAIL_TEMPLATE(class It)
    CANN_ASC_STL_DETAIL_REQUIRES((__subrange_from_iter_sent<Iter, It, _StoreSize>))
    CANN_ASC_STL_API constexpr subrange(It first, Sent last)
        : view_interface<subrange<Iter, Sent, Kind>>(),
          __begin_(::asc::std::move(first)),
          __end_(::asc::std::move(last)),
          __size_(0)
    {}

    CANN_ASC_STL_DETAIL_TEMPLATE(class It)
    CANN_ASC_STL_DETAIL_REQUIRES((__subrange_from_iter_sent_size<Iter, Kind, It>))
    CANN_ASC_STL_API constexpr subrange(It first, Sent last, make_unsigned_t<iter_difference_t<Iter>> size)
        : view_interface<subrange<Iter, Sent, Kind>>(),
          __begin_(::asc::std::move(first)),
          __end_(::asc::std::move(last)),
          __size_(size)
    {
        if constexpr (sized_sentinel_for<Sent, Iter>) {
            CANN_ASC_STL_DETAIL_ASSERT(
                (__end_ - __begin_) == static_cast<iter_difference_t<Iter>>(size), "invalid subrange size hint");
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range)
    CANN_ASC_STL_DETAIL_REQUIRES((__subrange_from_range<Iter, Sent, Kind, Range, !_StoreSize>))
    CANN_ASC_STL_API constexpr subrange(Range&& range)
        : subrange(::asc::std::ranges::__begin_cpo{}(range), ::asc::std::ranges::__end_cpo{}(range))
    {}

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range)
    CANN_ASC_STL_DETAIL_REQUIRES((__subrange_from_range<Iter, Sent, Kind, Range, _StoreSize>))
    CANN_ASC_STL_API constexpr subrange(Range&& range)
        : subrange(
              range, static_cast<make_unsigned_t<iter_difference_t<Iter>>>(::asc::std::ranges::__size_cpo{}(range)))
    {}

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range)
    CANN_ASC_STL_DETAIL_REQUIRES((__subrange_from_range_size<Iter, Sent, Kind, Range>))
    CANN_ASC_STL_API constexpr subrange(Range&& range, make_unsigned_t<iter_difference_t<Iter>> size)
        : subrange(::asc::std::ranges::__begin_cpo{}(range), ::asc::std::ranges::__end_cpo{}(range), size)
    {}

    // Pair-like conversion preserves iterator and sentinel conversions and
    // rejects slicing and range types in both language modes.
    CANN_ASC_STL_DETAIL_TEMPLATE(class Pair)
    CANN_ASC_STL_DETAIL_REQUIRES((__different_from<Pair, subrange<Iter, Sent, Kind>> &&
        __pair_like_convertible_from<Pair, const Iter&, const Sent&>))
    CANN_ASC_STL_API constexpr operator Pair() const
    {
        return Pair(__begin_, __end_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class It = Iter)
    CANN_ASC_STL_DETAIL_REQUIRES((copyable<It>))
    CANN_ASC_STL_API constexpr It begin() const
    {
        return __begin_;
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class It = Iter)
    CANN_ASC_STL_DETAIL_REQUIRES(((!copyable<It>)))
    CANN_ASC_STL_API constexpr It begin()
    {
        return ::asc::std::move(__begin_);
    }

    CANN_ASC_STL_API constexpr Sent end() const
    {
        return __end_;
    }

    CANN_ASC_STL_API constexpr bool empty() const
    {
        return __begin_ == __end_;
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(subrange_kind Kind_ = Kind)
    CANN_ASC_STL_DETAIL_REQUIRES(((Kind_ == subrange_kind::sized)))
    CANN_ASC_STL_API constexpr make_unsigned_t<iter_difference_t<Iter>> size() const
    {
        if constexpr (_StoreSize) {
            return __size_;
        } else {
            return static_cast<make_unsigned_t<iter_difference_t<Iter>>>(__end_ - __begin_);
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class It = Iter)
    CANN_ASC_STL_DETAIL_REQUIRES((forward_iterator<It>))
    CANN_ASC_STL_API constexpr subrange next(__PTRDIFF_TYPE__ amount = 1) const&
    {
        auto tmp = *this;
        tmp.advance(amount);
        return tmp;
    }

    CANN_ASC_STL_API constexpr subrange next(__PTRDIFF_TYPE__ amount = 1) &&
    {
        advance(amount);
        return ::asc::std::move(*this);  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class It = Iter)
    CANN_ASC_STL_DETAIL_REQUIRES((bidirectional_iterator<It>))
    CANN_ASC_STL_API constexpr subrange prev(__PTRDIFF_TYPE__ amount = 1) const
    {
        auto tmp = *this;
        tmp.advance(-amount);
        return tmp;
    }

    CANN_ASC_STL_API constexpr subrange& advance(__PTRDIFF_TYPE__ amount)
    {
        if constexpr (bidirectional_iterator<Iter>) {
            if (amount < 0) {
                ::asc::std::ranges::advance(__begin_, static_cast<iter_difference_t<Iter>>(amount));
                if constexpr (_StoreSize) {
                    // Avoid negating the most negative signed difference.
                    __size_ += static_cast<_Size>(-(amount + 1)) + 1;
                }
                return *this;
            }
        }
        const auto remaining =
            ::asc::std::ranges::advance(__begin_, static_cast<iter_difference_t<Iter>>(amount), __end_);
        if constexpr (_StoreSize) {
            __size_ -= static_cast<_Size>(amount - remaining);
        }
        return *this;
    }
};

CANN_ASC_STL_DETAIL_TEMPLATE(class Iter, class Sent)
CANN_ASC_STL_DETAIL_REQUIRES((input_or_output_iterator<Iter> && sentinel_for<Sent, Iter>))
CANN_ASC_STL_HOST_DEVICE subrange(Iter, Sent) -> subrange<Iter, Sent>;

CANN_ASC_STL_DETAIL_TEMPLATE(class Iter, class Sent)
CANN_ASC_STL_DETAIL_REQUIRES((input_or_output_iterator<Iter> && sentinel_for<Sent, Iter>))
CANN_ASC_STL_HOST_DEVICE subrange(
    Iter, Sent, make_unsigned_t<iter_difference_t<Iter>>) -> subrange<Iter, Sent, subrange_kind::sized>;

CANN_ASC_STL_DETAIL_TEMPLATE(class Range)
CANN_ASC_STL_DETAIL_REQUIRES((borrowed_range<Range>))
CANN_ASC_STL_HOST_DEVICE subrange(Range&&)
    -> subrange<iterator_t<Range>, sentinel_t<Range>,
        (sized_range<Range> || sized_sentinel_for<sentinel_t<Range>, iterator_t<Range>>) ? subrange_kind::sized :
                                                                                           subrange_kind::unsized>;

CANN_ASC_STL_DETAIL_TEMPLATE(class Range)
CANN_ASC_STL_DETAIL_REQUIRES((borrowed_range<Range>))
CANN_ASC_STL_HOST_DEVICE subrange(Range&&,
    make_unsigned_t<range_difference_t<Range>>) -> subrange<iterator_t<Range>, sentinel_t<Range>, subrange_kind::sized>;

// Keep the explicit cv/ref overloads and the index/copyability conditions in
// both modes, including const subranges whose iterator cannot be copied.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <size_t Index, class Iter, class Sent, subrange_kind Kind>
    requires((Index == 0) && copyable<Iter>) || (Index == 1)
#else
template <size_t Index, class Iter, class Sent, subrange_kind Kind,
    enable_if_t<((Index == 0) && copyable<Iter>) || (Index == 1), int> = 0>
#endif
CANN_ASC_STL_API constexpr auto get(const subrange<Iter, Sent, Kind>& value)
{
    if constexpr (Index == 0) {
        return value.begin();
    } else {
        return value.end();
    }
}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <size_t Index, class Iter, class Sent, subrange_kind Kind>
    requires(Index < 2)
#else
template <size_t Index, class Iter, class Sent, subrange_kind Kind, enable_if_t<Index < 2, int> = 0>
#endif
CANN_ASC_STL_API constexpr auto get(subrange<Iter, Sent, Kind>&& value)
{
    if constexpr (Index == 0) {
        return ::asc::std::move(value).begin();  // NOLINT(build/include_what_you_use)
    } else {
        return ::asc::std::move(value).end();  // NOLINT(build/include_what_you_use)
    }
}

template <class I, class S, subrange_kind K>
inline constexpr bool enable_borrowed_range<subrange<I, S, K>> = true;

template <class R>
using borrowed_subrange_t = enable_if_t<range<R>, _If<borrowed_range<R>, subrange<iterator_t<R>>, dangling>>;
}  // namespace asc::std::ranges

CANN_ASC_STL_BEGIN_NAMESPACE

using ::asc::std::ranges::get;

// tuple_size and tuple_element specializations for ranges::subrange
template <class I, class S, ranges::subrange_kind K>
struct tuple_size<ranges::subrange<I, S, K>> : integral_constant<size_t, 2> {};

template <class I, class S, ranges::subrange_kind K>
struct tuple_element<0, ranges::subrange<I, S, K>> {
    using type = I;
};

template <class I, class S, ranges::subrange_kind K>
struct tuple_element<1, ranges::subrange<I, S, K>> {
    using type = S;
};

template <class I, class S, ranges::subrange_kind K>
struct tuple_element<0, const ranges::subrange<I, S, K>> {
    using type = I;
};

template <class I, class S, ranges::subrange_kind K>
struct tuple_element<1, const ranges::subrange<I, S, K>> {
    using type = S;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_SUBRANGE_H
