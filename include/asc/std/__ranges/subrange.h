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
#include <asc/std/__type_traits/enable_if.h>
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

// 非切片转换判定：指针到指针的数组限定转换（Derived(*)[] -> Base(*)[]）不得静默进入区间。
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class From, class To>
concept __uses_nonqualification_pointer_conversion =
    is_pointer_v<From> && is_pointer_v<To> && !convertible_to<remove_pointer_t<From> (*)[], remove_pointer_t<To> (*)[]>;

template <class From, class To>
concept __convertible_to_non_slicing =
    convertible_to<From, To> && !__uses_nonqualification_pointer_conversion<decay_t<From>, decay_t<To>>;

template <class Pair, class Iter, class Sent>
concept __pair_like_convertible_from = __pair_like<Pair> && !range<Pair> && constructible_from<Pair, Iter, Sent> &&
    __convertible_to_non_slicing<Iter, tuple_element_t<0, Pair>> && convertible_to<Sent, tuple_element_t<1, Pair>>;

// 部分编译器无法在 SFINAE 上下文内可靠使用成员常量 _StoreSize，拆出为独立约束（与源实现一致）。
template <class Iter, class It, bool StoreSize>
concept __subrange_from_iter_sent = !StoreSize && __convertible_to_non_slicing<It, Iter>;

template <class Iter, subrange_kind Kind, class It>
concept __subrange_from_iter_sent_size = Kind == subrange_kind::sized && __convertible_to_non_slicing<It, Iter>;

template <class Iter, class Sent, subrange_kind Kind, class Range, bool StoreSize>
concept __subrange_from_range =
    StoreSize && __different_from<Range, subrange<Iter, Sent, Kind>> && borrowed_range<Range> &&
    __convertible_to_non_slicing<iterator_t<Range>, Iter> && convertible_to<sentinel_t<Range>, Sent>;

template <class Iter, class Sent, subrange_kind Kind, class Range>
concept __subrange_from_range_size = Kind == subrange_kind::sized && borrowed_range<Range> &&
    __convertible_to_non_slicing<iterator_t<Range>, Iter> && convertible_to<sentinel_t<Range>, Sent>;

#else

namespace __subrange_detail {
// C++17/设备编译回退的内部探测（公开概念名按产品冻结合同缺席，仅提供 __ 前缀等价物）：
// 哨兵差值可换算到迭代器差型（等价 sized_sentinel_for 的可减部分）。
template <class Sent, class Iter, class = void>
inline constexpr bool __sized_sentinel = false;

template <class Sent, class Iter>
inline constexpr bool __sized_sentinel<Sent, Iter,
    void_t<decltype(::asc::std::declval<const Sent&>() - ::asc::std::declval<const Iter&>())>> =
    !disable_sized_sentinel_for<remove_cv_t<Sent>, remove_cv_t<Iter>> &&
    is_convertible_v<decltype(::asc::std::declval<const Sent&>() - ::asc::std::declval<const Iter&>()),
        iter_difference_t<Iter>>;

// ranges::size 定制点对 Range 可调用（等价 sized_range 的尺寸部分）。
template <class Range, class = void>
inline constexpr bool __sized_range = false;

template <class Range>
inline constexpr bool
    __sized_range<Range, void_t<decltype(::asc::std::ranges::__size_cpo{}(::asc::std::declval<Range&>()))>> = true;

// 弱迭代器/哨兵探测（仅用于推导指引消歧：避免 (range, size) 二参形式被 (iter, sent) 指引误吞）。
template <class Iter, class = void>
inline constexpr bool __weak_iterator = false;

template <class Iter>
inline constexpr bool
    __weak_iterator<Iter, void_t<decltype(*::asc::std::declval<Iter&>()), decltype(++::asc::std::declval<Iter&>())>> =
        true;

template <class Iter, class Sent, class = void>
inline constexpr bool __weak_sentinel = false;

template <class Iter, class Sent>
inline constexpr bool __weak_sentinel<Iter, Sent,
    void_t<decltype(::asc::std::declval<const Sent&>() == ::asc::std::declval<const Iter&>()),
        decltype(::asc::std::declval<const Iter&>() != ::asc::std::declval<const Sent&>()),
        decltype(::asc::std::declval<const Sent&>() != ::asc::std::declval<const Iter&>())>> = true;
}  // namespace __subrange_detail

// 是否需要在区间内显式存储尺寸：sized 且哨兵不可相减。
template <class Iter, class Sent, subrange_kind Kind>
inline constexpr bool __subrange_store_size =
    Kind == subrange_kind::sized && !__subrange_detail::__sized_sentinel<Sent, Iter>;

#endif

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator Iter, sentinel_for<Iter> Sent, subrange_kind Kind>
    requires(Kind == subrange_kind::sized || !sized_sentinel_for<Sent, Iter>)
class subrange : public view_interface<subrange<Iter, Sent, Kind>> {
public:
    using iterator = Iter;
    using sentinel = Sent;
    using size_type = make_unsigned_t<iter_difference_t<Iter>>;
    // 内部实现细节，公开仅为内部使用（适配器直通/存尺寸判定）。
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
    subrange()
        requires default_initializable<Iter>
    = default;

    template <class It>
        requires __subrange_from_iter_sent<Iter, It, _StoreSize>
    CANN_ASC_STL_API constexpr subrange(It first, Sent last)
        : view_interface<subrange<Iter, Sent, Kind>>(),
          __begin_(::asc::std::move(first)),
          __end_(::asc::std::move(last)),
          __size_(0)
    {}

    template <class It>
        requires __subrange_from_iter_sent_size<Iter, Kind, It>
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

    template <class Range>
        requires __subrange_from_range<Iter, Sent, Kind, Range, !_StoreSize>
    CANN_ASC_STL_API constexpr subrange(Range&& range)
        : subrange(::asc::std::ranges::__begin_cpo{}(range), ::asc::std::ranges::__end_cpo{}(range))
    {}

    template <class Range>
        requires __subrange_from_range<Iter, Sent, Kind, Range, _StoreSize>
    CANN_ASC_STL_API constexpr subrange(Range&& range)
        : subrange(
              range, static_cast<make_unsigned_t<iter_difference_t<Iter>>>(::asc::std::ranges::__size_cpo{}(range)))
    {}

    template <class Range>
        requires __subrange_from_range_size<Iter, Sent, Kind, Range>
    CANN_ASC_STL_API constexpr subrange(Range&& range, make_unsigned_t<iter_difference_t<Iter>> size)
        : subrange(::asc::std::ranges::__begin_cpo{}(range), ::asc::std::ranges::__end_cpo{}(range), size)
    {}

    // 右值 subrange 进入管道时旧版编译器常见 ICE，转换运算符仅在概念模式提供（与源实现一致）。
    template <class Pair>
        requires __different_from<Pair, subrange<Iter, Sent, Kind>> &&
        __pair_like_convertible_from<Pair, const Iter&, const Sent&>
    CANN_ASC_STL_API constexpr operator Pair() const
    {
        return Pair(__begin_, __end_);
    }

    template <class It = Iter>
        requires copyable<It>
    CANN_ASC_STL_API constexpr It begin() const
    {
        return __begin_;
    }

    template <class It = Iter>
        requires(!copyable<It>)
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

    template <subrange_kind Kind_ = Kind>
        requires(Kind_ == subrange_kind::sized)
    CANN_ASC_STL_API constexpr make_unsigned_t<iter_difference_t<Iter>> size() const
    {
        if constexpr (_StoreSize) {
            return __size_;
        } else {
            return static_cast<make_unsigned_t<iter_difference_t<Iter>>>(__end_ - __begin_);
        }
    }

    template <class It = Iter>
        requires forward_iterator<It>
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

    template <class It = Iter>
        requires bidirectional_iterator<It>
    CANN_ASC_STL_API constexpr subrange prev(__PTRDIFF_TYPE__ amount = 1) const
    {
        auto tmp = *this;
        tmp.advance(-amount);
        return tmp;
    }

    CANN_ASC_STL_API constexpr subrange& advance(__PTRDIFF_TYPE__ amount)
    {
        ::asc::std::advance(__begin_, amount);
        if constexpr (_StoreSize) {
            __size_ = static_cast<_Size>(static_cast<iter_difference_t<Iter>>(__size_) - amount);
        }
        return *this;
    }
};
#else
template <class Iter, class Sent, subrange_kind Kind>
class subrange : public view_interface<subrange<Iter, Sent, Kind>> {
public:
    using iterator = Iter;
    using sentinel = Sent;
    using size_type = make_unsigned_t<iter_difference_t<Iter>>;
    // 内部实现细节，公开仅为内部使用（适配器直通/存尺寸判定）。
    static constexpr bool _StoreSize = __subrange_store_size<Iter, Sent, Kind>;

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
    CANN_ASC_STL_API constexpr subrange() = default;

    // Enable 仅为保持约束表达式对成员模板参数的依赖性（类实例化时不提前求值）。
    template <class It = Iter, bool Enable = true,
        enable_if_t<Enable && !__subrange_store_size<Iter, Sent, Kind>, int> = 0>
    CANN_ASC_STL_API constexpr subrange(It first, Sent last)
        : view_interface<subrange<Iter, Sent, Kind>>(),
          __begin_(::asc::std::move(first)),
          __end_(::asc::std::move(last)),
          __size_(0)
    {}

    CANN_ASC_STL_API constexpr subrange(Iter first, Sent last, size_type size)
        : view_interface<subrange<Iter, Sent, Kind>>(),
          __begin_(::asc::std::move(first)),
          __end_(::asc::std::move(last)),
          __size_(size)
    {
        if constexpr (Kind == subrange_kind::sized && __subrange_detail::__sized_sentinel<Sent, Iter>) {
            CANN_ASC_STL_DETAIL_ASSERT(
                (__end_ - __begin_) == static_cast<iter_difference_t<Iter>>(size), "invalid subrange size hint");
        }
    }

    template <class Range,
        enable_if_t<is_lvalue_reference_v<Range&&> || enable_borrowed_range<remove_cvref_t<Range>>, int> = 0>
    CANN_ASC_STL_API constexpr subrange(Range&& range)
        : view_interface<subrange<Iter, Sent, Kind>>(),
          __begin_(::asc::std::ranges::__begin_cpo{}(range)),
          __end_(::asc::std::ranges::__end_cpo{}(range)),
          __size_(initial_size(range))
    {}

    template <class Range,
        enable_if_t<is_lvalue_reference_v<Range&&> || enable_borrowed_range<remove_cvref_t<Range>>, int> = 0>
    CANN_ASC_STL_API constexpr subrange(Range&& range, size_type size)
        : view_interface<subrange<Iter, Sent, Kind>>(),
          __begin_(::asc::std::ranges::__begin_cpo{}(range)),
          __end_(::asc::std::ranges::__end_cpo{}(range)),
          __size_(size)
    {}

    CANN_ASC_STL_API constexpr Iter begin()
    {
        return __begin_;
    }
    CANN_ASC_STL_API constexpr Iter begin() const
    {
        return __begin_;
    }
    CANN_ASC_STL_API constexpr Sent end() const
    {
        return __end_;
    }
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return __begin_ == __end_;
    }
    CANN_ASC_STL_API constexpr size_type size() const
    {
        if constexpr (Kind == subrange_kind::sized && _StoreSize) {
            return __size_;
        } else {
            return static_cast<size_type>(__end_ - __begin_);
        }
    }
    CANN_ASC_STL_API constexpr subrange& advance(__PTRDIFF_TYPE__ amount)
    {
        ::asc::std::advance(__begin_, amount);
        if constexpr (Kind == subrange_kind::sized && _StoreSize) {
            __size_ = static_cast<_Size>(static_cast<iter_difference_t<Iter>>(__size_) - amount);
        }
        return *this;
    }
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
    CANN_ASC_STL_API constexpr subrange prev(__PTRDIFF_TYPE__ amount = 1) const
    {
        return next(-amount);
    }

private:
    template <class Range>
    CANN_ASC_STL_API static constexpr _Size initial_size(Range& range)
    {
        if constexpr (__subrange_store_size<Iter, Sent, Kind>) {
            return static_cast<make_unsigned_t<iter_difference_t<Iter>>>(::asc::std::ranges::__size_cpo{}(range));
        } else {
            return 0;
        }
    }
};
#endif

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class Iter, class Sent>
    requires input_or_output_iterator<Iter> && sentinel_for<Sent, Iter>
subrange(Iter, Sent) -> subrange<Iter, Sent>;

template <class Iter, class Sent>
    requires input_or_output_iterator<Iter> && sentinel_for<Sent, Iter>
subrange(Iter, Sent, make_unsigned_t<iter_difference_t<Iter>>) -> subrange<Iter, Sent, subrange_kind::sized>;

template <class Range>
    requires borrowed_range<Range>
subrange(Range&&)
    -> subrange<iterator_t<Range>, sentinel_t<Range>,
        (sized_range<Range> || sized_sentinel_for<sentinel_t<Range>, iterator_t<Range>>) ? subrange_kind::sized :
                                                                                           subrange_kind::unsized>;

template <class Range>
    requires borrowed_range<Range>
subrange(Range&&,
    make_unsigned_t<range_difference_t<Range>>) -> subrange<iterator_t<Range>, sentinel_t<Range>, subrange_kind::sized>;
#else
template <class Iter, class Sent,
    enable_if_t<__subrange_detail::__weak_iterator<Iter> && __subrange_detail::__weak_sentinel<Iter, Sent>, int> = 0>
subrange(Iter, Sent) -> subrange<Iter, Sent>;

template <class Iter, class Sent,
    enable_if_t<__subrange_detail::__weak_iterator<Iter> && __subrange_detail::__weak_sentinel<Iter, Sent>, int> = 0>
subrange(Iter, Sent, make_unsigned_t<iter_difference_t<Iter>>) -> subrange<Iter, Sent, subrange_kind::sized>;

template <class Range>
subrange(Range&&) -> subrange<iterator_t<Range>, sentinel_t<Range>,
                      (__subrange_detail::__sized_range<Range&> ||
                          __subrange_detail::__sized_sentinel<sentinel_t<Range>, iterator_t<Range>>) ?
                          subrange_kind::sized :
                          subrange_kind::unsized>;

template <class Range>
subrange(Range&&,
    make_unsigned_t<range_difference_t<Range>>) -> subrange<iterator_t<Range>, sentinel_t<Range>, subrange_kind::sized>;
#endif

// 前向声明需要用到这些名字，这里用普通声明而非宏形式。
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <size_t Index, class Iter, class Sent, subrange_kind Kind>
    requires((Index == 0) && copyable<Iter>) || (Index == 1)
#else
template <size_t Index, class Iter, class Sent, subrange_kind Kind,
    enable_if_t<((Index == 0) && is_copy_constructible_v<Iter>) || (Index == 1), int> = 0>
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

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class R>
using borrowed_subrange_t = enable_if_t<range<R>, _If<borrowed_range<R>, subrange<iterator_t<R>>, dangling>>;
#else
template <class Range>
using borrowed_subrange_t = conditional_t<is_lvalue_reference_v<Range> || enable_borrowed_range<remove_cvref_t<Range>>,
    subrange<iterator_t<Range>>, dangling>;
#endif
}  // namespace asc::std::ranges

CANN_ASC_STL_BEGIN_NAMESPACE

using ::asc::std::ranges::get;

// 为 ranges::subrange 特化 tuple_size 与 tuple_element
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
