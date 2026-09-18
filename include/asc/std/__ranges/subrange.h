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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_SUBRANGE_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_SUBRANGE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/different_from.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__fwd/subrange.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__tuple_dir/tuple_like.h>
#include <asc/std/__tuple_dir/tuple_size.h>
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

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _From, class _To>
concept __uses_nonqualification_pointer_conversion = is_pointer_v<_From> && is_pointer_v<_To> &&
    !convertible_to<remove_pointer_t<_From> (*)[], remove_pointer_t<_To> (*)[]>;

template <class _From, class _To>
concept __convertible_to_non_slicing =
    convertible_to<_From, _To> && !__uses_nonqualification_pointer_conversion<decay_t<_From>, decay_t<_To>>;

template <class _Pair, class _Iter, class _Sent>
concept __pair_like_convertible_from =
    __pair_like_v<_Pair> && !range<_Pair> && constructible_from<_Pair, _Iter, _Sent> &&
    __convertible_to_non_slicing<_Iter, tuple_element_t<0, _Pair>> && convertible_to<_Sent, tuple_element_t<1, _Pair>>;

// We have issues with MSVC and _StoreSize being unable to be properly determined in SFINAE, so we need to pull that out
template <class _Iter, class _It, bool _StoreSize>
concept __subrange_from_iter_sent = !_StoreSize && __convertible_to_non_slicing<_It, _Iter>;

template <class _Iter, subrange_kind _Kind, class _It>
concept __subrange_from_iter_sent_size = _Kind == subrange_kind::sized && __convertible_to_non_slicing<_It, _Iter>;

template <class _Iter, class _Sent, subrange_kind _Kind, class _Range, bool _StoreSize>
concept __subrange_from_range =
    _StoreSize && __different_from<_Range, subrange<_Iter, _Sent, _Kind>> && borrowed_range<_Range> &&
    __convertible_to_non_slicing<iterator_t<_Range>, _Iter> && convertible_to<sentinel_t<_Range>, _Sent>;

template <class _Iter, class _Sent, subrange_kind _Kind, class _Range>
concept __subrange_from_range_size = _Kind == subrange_kind::sized && borrowed_range<_Range> &&
    __convertible_to_non_slicing<iterator_t<_Range>, _Iter> && convertible_to<sentinel_t<_Range>, _Sent>;

#else   // ^^^ concepts ^^^ / vvv !concepts vvv

template <class _From, class _To>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__uses_nonqualification_pointer_conversion_,
    requires()(requires(is_pointer_v<_From>), requires(is_pointer_v<_To>),
        requires(!convertible_to<remove_pointer_t<_From> (*)[], remove_pointer_t<_To> (*)[]>)));

template <class _From, class _To>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __uses_nonqualification_pointer_conversion =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__uses_nonqualification_pointer_conversion_, _From, _To);

template <class _From, class _To>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__convertible_to_non_slicing_,
    requires()(requires(convertible_to<_From, _To>),
        requires(!__uses_nonqualification_pointer_conversion<decay_t<_From>, decay_t<_To>>)));

template <class _From, class _To>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __convertible_to_non_slicing =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__convertible_to_non_slicing_, _From, _To);

template <class _Pair, class _Iter, class _Sent>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__pair_like_convertible_from_,
    requires()(requires(__pair_like_v<_Pair>), requires(!range<_Pair>),
        requires(constructible_from<_Pair, _Iter, _Sent>),
        requires(__convertible_to_non_slicing<_Iter, tuple_element_t<0, _Pair>>),
        requires(convertible_to<_Sent, tuple_element_t<1, _Pair>>)));

template <class _Pair, class _Iter, class _Sent>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __pair_like_convertible_from =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__pair_like_convertible_from_, _Pair, _Iter, _Sent);

// We have issues with MSVC and _StoreSize being unable to be properly determined in SFINAE, so we need to pull that out
template <class _Iter, class _It, class _StoreSize>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__subrange_from_iter_sent_,
    requires()(requires(!_StoreSize::value), requires(__convertible_to_non_slicing<_It, _Iter>)));

template <class _Iter, class _It, bool _StoreSize>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __subrange_from_iter_sent =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__subrange_from_iter_sent_, _Iter, _It, integral_constant<bool, _StoreSize>);

template <class _Iter, class _Kind, class _It>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__subrange_from_iter_sent_size_,
    requires()(requires(_Kind::value == subrange_kind::sized), requires(__convertible_to_non_slicing<_It, _Iter>)));

template <class _Iter, subrange_kind _Kind, class _It>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __subrange_from_iter_sent_size = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(
    __subrange_from_iter_sent_size_, _Iter, integral_constant<subrange_kind, _Kind>, _It);

template <class _Iter, class _Sent, class _Kind, class _Range, class _StoreSize>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__subrange_from_range_,
    requires()(requires(_StoreSize::value), requires(__different_from<_Range, subrange<_Iter, _Sent, _Kind::value>>),
        requires(borrowed_range<_Range>), requires(__convertible_to_non_slicing<iterator_t<_Range>, _Iter>),
        requires(convertible_to<sentinel_t<_Range>, _Sent>)));

template <class _Iter, class _Sent, subrange_kind _Kind, class _Range, bool _StoreSize>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __subrange_from_range = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__subrange_from_range_,
    _Iter, _Sent, integral_constant<subrange_kind, _Kind>, _Range, integral_constant<bool, _StoreSize>);

template <class _Iter, class _Sent, class _Kind, class _Range>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__subrange_from_range_size_,
    requires()(requires((_Kind::value == subrange_kind::sized)), requires(borrowed_range<_Range>),
        requires(__convertible_to_non_slicing<iterator_t<_Range>, _Iter>),
        requires(convertible_to<sentinel_t<_Range>, _Sent>)));

template <class _Iter, class _Sent, subrange_kind _Kind, class _Range>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __subrange_from_range_size = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(
    __subrange_from_range_size_, _Iter, _Sent, integral_constant<subrange_kind, _Kind>, _Range);
#endif  // !concepts

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator _Iter, sentinel_for<_Iter> _Sent, subrange_kind _Kind>
    requires(_Kind == subrange_kind::sized || !sized_sentinel_for<_Sent, _Iter>)
class subrange : public view_interface<subrange<_Iter, _Sent, _Kind>> {
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
template <class _Iter, class _Sent, subrange_kind _Kind, enable_if_t<input_or_output_iterator<_Iter>, int>,
    enable_if_t<sentinel_for<_Sent, _Iter>, int>,
    enable_if_t<(_Kind == subrange_kind::sized || !sized_sentinel_for<_Sent, _Iter>), int>>
class subrange : public view_interface<subrange<_Iter, _Sent, _Kind>> {
#endif  // !concepts
public:
    // Note: this is an internal implementation detail that is public only for internal usage.
    static constexpr bool _StoreSize = (_Kind == subrange_kind::sized && !sized_sentinel_for<_Sent, _Iter>);

private:
    struct _Empty {
        template <class _Tp>
        CANN_ASC_STL_API constexpr _Empty(_Tp) noexcept
        {}
    };

    using _Size = conditional_t<_StoreSize, make_unsigned_t<iter_difference_t<_Iter>>, _Empty>;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Iter __begin_ = _Iter();
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Sent __end_ = _Sent();
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Size __size_ = 0;

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI subrange()
        requires default_initializable<_Iter>
    = default;
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
    template <class _It = _Iter, enable_if_t<default_initializable<_It>, int> = 0>
    CANN_ASC_STL_API constexpr subrange() noexcept(is_nothrow_default_constructible_v<_It>)
        : view_interface<subrange<_Iter, _Sent, _Kind>>()
    {}
#endif  // !concepts

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _It)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__subrange_from_iter_sent<_Iter, _It, _StoreSize>)
    CANN_ASC_STL_API constexpr subrange(_It __iter, _Sent __sent)
        : view_interface<subrange<_Iter, _Sent, _Kind>>(),
          __begin_(::asc::std::move(__iter)),
          __end_(::asc::std::move(__sent))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _It)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__subrange_from_iter_sent_size<_Iter, _Kind, _It>)
    CANN_ASC_STL_API constexpr subrange(_It __iter, _Sent __sent, make_unsigned_t<iter_difference_t<_Iter>> __n)
        : view_interface<subrange<_Iter, _Sent, _Kind>>(),
          __begin_(::asc::std::move(__iter)),
          __end_(::asc::std::move(__sent)),
          __size_(__n)
    {
        if constexpr (sized_sentinel_for<_Sent, _Iter>) {
            CANN_ASC_STL_DETAIL_ASSERT((__end_ - __begin_) == static_cast<iter_difference_t<_Iter>>(__n),
                "::asc::std::ranges::subrange was passed an invalid size hint");
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__subrange_from_range<_Iter, _Sent, _Kind, _Range, !_StoreSize>)
    CANN_ASC_STL_API constexpr subrange(_Range&& __range)
        : subrange(::asc::std::ranges::__begin_cpo{}(__range), ::asc::std::ranges::__end_cpo{}(__range))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__subrange_from_range<_Iter, _Sent, _Kind, _Range, _StoreSize>)
    CANN_ASC_STL_API constexpr subrange(_Range&& __range) : subrange(__range, ::asc::std::ranges::__size_cpo{}(__range))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__subrange_from_range_size<_Iter, _Sent, _Kind, _Range>)
    CANN_ASC_STL_API constexpr subrange(_Range&& __range, make_unsigned_t<iter_difference_t<_Iter>> __n)
        : subrange(::asc::std::ranges::__begin_cpo{}(__range), ::asc::std::ranges::__end_cpo{}(__range), __n)
    {}

    // This often ICEs all of clang and old gcc when it encounteres a rvalue subrange in a pipe
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Pair)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        __different_from<_Pair, subrange<_Iter, _Sent, _Kind>> CANN_ASC_STL_DETAIL_ACCL_AND
            __pair_like_convertible_from<_Pair, const _Iter&, const _Sent&>)
    CANN_ASC_STL_API constexpr operator _Pair() const
    {
        return _Pair(__begin_, __end_);
    }
#endif  // concepts

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _It = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(copyable<_It>)
    [[nodiscard]] CANN_ASC_STL_API constexpr _It begin() const
    {
        return __begin_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _It = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!copyable<_It>))
    [[nodiscard]] CANN_ASC_STL_API constexpr _It begin()
    {
        return ::asc::std::move(__begin_);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr _Sent end() const
    {
        return __end_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr bool empty() const
    {
        return __begin_ == __end_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(subrange_kind _Kind_ = _Kind)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((_Kind_ == subrange_kind::sized))
    [[nodiscard]] CANN_ASC_STL_API constexpr make_unsigned_t<iter_difference_t<_Iter>> size() const
    {
        if constexpr (_StoreSize) {
            return __size_;
        } else {
            return ::asc::std::__to_unsigned_like(__end_ - __begin_);
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _It = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(forward_iterator<_It>)
    [[nodiscard]] CANN_ASC_STL_API constexpr subrange next(iter_difference_t<_Iter> __n = 1) const&
    {
        auto __tmp = *this;
        __tmp.advance(__n);
        return __tmp;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr subrange next(iter_difference_t<_Iter> __n = 1) &&
    {
        advance(__n);
        return ::asc::std::move(*this);  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _It = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(bidirectional_iterator<_It>)
    [[nodiscard]] CANN_ASC_STL_API constexpr subrange prev(iter_difference_t<_Iter> __n = 1) const
    {
        auto __tmp = *this;
        __tmp.advance(-__n);
        return __tmp;
    }

    CANN_ASC_STL_API constexpr subrange& advance(iter_difference_t<_Iter> __n)
    {
        if constexpr (bidirectional_iterator<_Iter>) {
            if (__n < 0) {
                ::asc::std::ranges::__advance_cpo{}(__begin_, __n);
                if constexpr (_StoreSize) {
                    __size_ += ::asc::std::__to_unsigned_like(-__n);
                }
                return *this;
            }
        }
        [[maybe_unused]] const auto __d = __n - ::asc::std::ranges::__advance_cpo{}(__begin_, __n, __end_);
        if constexpr (_StoreSize) {
            __size_ -= ::asc::std::__to_unsigned_like(__d);
        }
        return *this;
    }
};

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter, class _Sent)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
    input_or_output_iterator<_Iter> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sent, _Iter>)
subrange(_Iter, _Sent) -> subrange<_Iter, _Sent>;

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter, class _Sent)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
    input_or_output_iterator<_Iter> CANN_ASC_STL_DETAIL_ACCL_AND sentinel_for<_Sent, _Iter>)
subrange(_Iter, _Sent, make_unsigned_t<iter_difference_t<_Iter>>) -> subrange<_Iter, _Sent, subrange_kind::sized>;

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(borrowed_range<_Range>)
subrange(_Range&&)
    -> subrange<iterator_t<_Range>, sentinel_t<_Range>,
        (sized_range<_Range> || sized_sentinel_for<sentinel_t<_Range>, iterator_t<_Range>>) ? subrange_kind::sized :
                                                                                              subrange_kind::unsized>;

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Range)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(borrowed_range<_Range>)
subrange(_Range&&, make_unsigned_t<range_difference_t<_Range>>)
    -> subrange<iterator_t<_Range>, sentinel_t<_Range>, subrange_kind::sized>;

// Plain declarations rather than the macro form, because they must be forward declared.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <size_t _Index, class _Iter, class _Sent, subrange_kind _Kind>
    requires((_Index == 0) && copyable<_Iter>) || (_Index == 1)
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
template <size_t _Index, class _Iter, class _Sent, subrange_kind _Kind,
    enable_if_t<((_Index == 0) && copyable<_Iter>) || (_Index == 1), int>>
#endif  // !concepts
CANN_ASC_STL_API constexpr auto get(const subrange<_Iter, _Sent, _Kind>& __subrange)
{
    if constexpr (_Index == 0) {
        return __subrange.begin();
    } else {
        return __subrange.end();
    }
}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <size_t _Index, class _Iter, class _Sent, subrange_kind _Kind>
    requires(_Index < 2)
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
template <size_t _Index, class _Iter, class _Sent, subrange_kind _Kind, enable_if_t<_Index < 2, int>>
#endif  // !concepts
CANN_ASC_STL_API constexpr auto get(subrange<_Iter, _Sent, _Kind>&& __subrange)
{
    if constexpr (_Index == 0) {
        return __subrange.begin();
    } else {
        return __subrange.end();
    }
}

template <class _Ip, class _Sp, subrange_kind _Kp>
inline constexpr bool enable_borrowed_range<subrange<_Ip, _Sp, _Kp>> = true;

template <class _Rp>
using borrowed_subrange_t = enable_if_t<range<_Rp>, _If<borrowed_range<_Rp>, subrange<iterator_t<_Rp>>, dangling>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

// [range.subrange.general]
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

using ::asc::std::ranges::get;

// specialize tuple_size and tuple_element for ranges::subrange
template <class _Ip, class _Sp, ::asc::std::ranges::subrange_kind _Kp>
struct tuple_size<::asc::std::ranges::subrange<_Ip, _Sp, _Kp>> : integral_constant<size_t, 2> {};

template <class _Ip, class _Sp, ::asc::std::ranges::subrange_kind _Kp>
struct tuple_element<0, ::asc::std::ranges::subrange<_Ip, _Sp, _Kp>> {
    using type = _Ip;
};

template <class _Ip, class _Sp, ::asc::std::ranges::subrange_kind _Kp>
struct tuple_element<1, ::asc::std::ranges::subrange<_Ip, _Sp, _Kp>> {
    using type = _Sp;
};

template <class _Ip, class _Sp, ::asc::std::ranges::subrange_kind _Kp>
struct tuple_element<0, const ::asc::std::ranges::subrange<_Ip, _Sp, _Kp>> {
    using type = _Ip;
};

template <class _Ip, class _Sp, ::asc::std::ranges::subrange_kind _Kp>
struct tuple_element<1, const ::asc::std::ranges::subrange<_Ip, _Sp, _Kp>> {
    using type = _Sp;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_SUBRANGE_H
