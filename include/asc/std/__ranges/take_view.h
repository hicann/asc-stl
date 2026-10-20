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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_TAKE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_TAKE_VIEW_H

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
#include <asc/std/__algorithm/min.h>
#include <asc/std/__algorithm/ranges_min.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__fwd/span.h>
#include <asc/std/__fwd/string_view.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/counted_iterator.h>
#include <asc/std/__iterator/default_sentinel.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/counted_adaptor.h>
#include <asc/std/__ranges/empty_view.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/iota_view.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/repeat_view.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/subrange.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/maybe_const.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/forward_like.h>
#include <asc/std/__utility/move.h>

namespace asc::std::ranges {
// Both language modes and execution spaces share this implementation.
// Native constraints and SFINAE provide the same conditional members.

template <class _View>
inline constexpr bool __take_simple_view = __simple_view<_View>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <view _View>
#else
template <class _View>
#endif
class take_view : public view_interface<take_view<_View>> {
    static_assert(view<_View>, "range view constraints are not satisfied");

    CANN_ASC_STL_NO_UNIQUE_ADDRESS _View __base_ = _View();
    range_difference_t<_View> __count_ = 0;

public:
    template <bool _Const>
    class __sentinel {
        using _Base = __maybe_const<_Const, _View>;
        template <bool _OtherConst>
        using _Iter = counted_iterator<iterator_t<__maybe_const<_OtherConst, _View>>>;
        CANN_ASC_STL_NO_UNIQUE_ADDRESS sentinel_t<_Base> __end_ = sentinel_t<_Base>();

        template <bool>
        friend class __sentinel;

    public:
        constexpr __sentinel() = default;

        CANN_ASC_STL_API constexpr explicit __sentinel(sentinel_t<_Base> __end) : __end_(::asc::std::move(__end))
        {}

        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = _Const)
        CANN_ASC_STL_DETAIL_REQUIRES(((_OtherConst && convertible_to<sentinel_t<_View>, sentinel_t<_Base>>)))
        CANN_ASC_STL_API constexpr __sentinel(__sentinel<!_OtherConst> __s) : __end_(::asc::std::move(__s.__end_))
        {}

        CANN_ASC_STL_API constexpr sentinel_t<_Base> base() const
        {
            return __end_;
        }

        CANN_ASC_STL_API friend constexpr bool operator==(const _Iter<_Const>& __lhs, const __sentinel& __rhs)
        {
            return __lhs.count() == 0 || __lhs.base() == __rhs.__end_;
        }
        // Both reversed ==/!= overloads are kept for C++17 compatibility; under
        // C++20 the explicit candidates agree with the rewritten operators.
        CANN_ASC_STL_API friend constexpr bool operator==(const __sentinel& __lhs, const _Iter<_Const>& __rhs)
        {
            return __rhs.count() == 0 || __rhs.base() == __lhs.__end_;
        }
        CANN_ASC_STL_API friend constexpr bool operator!=(const _Iter<_Const>& __lhs, const __sentinel& __rhs)
        {
            return !(__lhs == __rhs);
        }
        CANN_ASC_STL_API friend constexpr bool operator!=(const __sentinel& __lhs, const _Iter<_Const>& __rhs)
        {
            return !(__lhs == __rhs);
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = !_Const)
        CANN_ASC_STL_DETAIL_REQUIRES((sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr bool operator==(const _Iter<_OtherConst>& __lhs, const __sentinel& __rhs)
        {
            return __lhs.count() == 0 || __lhs.base() == __rhs.__end_;
        }
        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = !_Const)
        CANN_ASC_STL_DETAIL_REQUIRES((sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr bool operator==(const __sentinel& __lhs, const _Iter<_OtherConst>& __rhs)
        {
            return __rhs.count() == 0 || __rhs.base() == __lhs.__end_;
        }
        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = !_Const)
        CANN_ASC_STL_DETAIL_REQUIRES((sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr bool operator!=(const _Iter<_OtherConst>& __lhs, const __sentinel& __rhs)
        {
            return !(__lhs == __rhs);
        }
        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = !_Const)
        CANN_ASC_STL_DETAIL_REQUIRES((sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr bool operator!=(const __sentinel& __lhs, const _Iter<_OtherConst>& __rhs)
        {
            return !(__lhs == __rhs);
        }
    };

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    take_view()
        requires default_initializable<_View>
    = default;
#else
    template <bool __asc_enabled = true, enable_if_t<__asc_enabled && (default_initializable<_View>), int> = 0>
    CANN_ASC_STL_API constexpr take_view()
    {}
#endif

    CANN_ASC_STL_API constexpr take_view(_View __base, range_difference_t<_View> __count)
        : __base_(::asc::std::move(__base)), __count_(__count)
    {}

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((copy_constructible<_View2>))
    CANN_ASC_STL_API constexpr _View base() const&
    {
        return __base_;
    }

    CANN_ASC_STL_API constexpr _View base() &&
    {
        return ::asc::std::move(__base_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES(((!__take_simple_view<_View2>)))
    CANN_ASC_STL_API constexpr auto begin()
    {
        if constexpr (sized_range<_View>) {
            if constexpr (random_access_range<_View>) {
                return ::asc::std::ranges::__begin_cpo{}(__base_);
            } else {
                using _DifferenceT = range_difference_t<_View>;
                auto __size = size();
                return counted_iterator(::asc::std::ranges::__begin_cpo{}(__base_), static_cast<_DifferenceT>(__size));
            }
        } else {
            return counted_iterator(::asc::std::ranges::__begin_cpo{}(__base_), __count_);
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((range<const _View2>))
    CANN_ASC_STL_API constexpr auto begin() const
    {
        if constexpr (sized_range<const _View>) {
            if constexpr (random_access_range<const _View>) {
                return ::asc::std::ranges::__begin_cpo{}(__base_);
            } else {
                using _DifferenceT = range_difference_t<const _View>;
                auto __size = size();
                return counted_iterator(::asc::std::ranges::__begin_cpo{}(__base_), static_cast<_DifferenceT>(__size));
            }
        } else {
            return counted_iterator(::asc::std::ranges::__begin_cpo{}(__base_), __count_);
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES(((!__take_simple_view<_View2>)))
    CANN_ASC_STL_API constexpr auto end()
    {
        if constexpr (sized_range<_View>) {
            if constexpr (random_access_range<_View>) {
                return ::asc::std::ranges::__begin_cpo{}(__base_) + size();
            } else {
                return default_sentinel;
            }
        } else {
            return __sentinel<false>{::asc::std::ranges::__end_cpo{}(__base_)};
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((range<const _View2>))
    CANN_ASC_STL_API constexpr auto end() const
    {
        if constexpr (sized_range<const _View>) {
            if constexpr (random_access_range<const _View>) {
                return ::asc::std::ranges::__begin_cpo{}(__base_) + size();
            } else {
                return default_sentinel;
            }
        } else {
            return __sentinel<true>{::asc::std::ranges::__end_cpo{}(__base_)};
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<_View2>))
    CANN_ASC_STL_API constexpr auto size()
    {
        const auto __n = ::asc::std::ranges::__size_cpo{}(__base_);
        return (::asc::std::ranges::min)(__n, static_cast<decltype(__n)>(__count_));
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<const _View2>))
    CANN_ASC_STL_API constexpr auto size() const
    {
        auto __n = ::asc::std::ranges::__size_cpo{}(__base_);
        return (::asc::std::ranges::min)(__n, static_cast<decltype(__n)>(__count_));
    }
};

template <class _Range>
CANN_ASC_STL_HOST_DEVICE take_view(
    _Range&&, range_difference_t<_Range>) -> take_view<::asc::std::ranges::views::all_t<_Range>>;

template <class _Tp>
inline constexpr bool enable_borrowed_range<take_view<_Tp>> = enable_borrowed_range<_Tp>;

namespace views {

// Adaptor dispatch internals (passthrough and specialization detection for
// span/basic_string_view/subrange/iota_view/repeat_view).
namespace __take_detail {

template <class _Tp>
inline constexpr bool __is_empty_view = false;

template <class _Tp>
inline constexpr bool __is_empty_view<empty_view<_Tp>> = true;

template <class _Tp>
inline constexpr bool __is_passthrough_specialization = false;

template <class _Tp, size_t _Extent>
inline constexpr bool __is_passthrough_specialization<span<_Tp, _Extent>> = true;

template <class _CharT, class _Traits>
inline constexpr bool __is_passthrough_specialization<basic_string_view<_CharT, _Traits>> = true;

template <class _Iter, class _Sent, ::asc::std::ranges::subrange_kind _Kind>
inline constexpr bool __is_passthrough_specialization<::asc::std::ranges::subrange<_Iter, _Sent, _Kind>> = true;

template <class _Tp, class = void>
inline constexpr bool __is_iota_specialization = false;

template <class _Np, class _Bound>
inline constexpr bool __is_iota_specialization<iota_view<_Np, _Bound>, void> = true;

template <class _Tp, class = void>
struct __passthrough_type;

template <class _Tp, size_t _Extent>
struct __passthrough_type<span<_Tp, _Extent>, void> {
    using type = span<_Tp>;
};

template <class _CharT, class _Traits>
struct __passthrough_type<basic_string_view<_CharT, _Traits>, void> {
    using type = basic_string_view<_CharT, _Traits>;
};

template <class _Iter, class _Sent, ::asc::std::ranges::subrange_kind _Kind>
struct __passthrough_type<::asc::std::ranges::subrange<_Iter, _Sent, _Kind>,
    void_t<typename ::asc::std::ranges::subrange<_Iter>>> {
    using type = ::asc::std::ranges::subrange<_Iter>;
};

template <class _Tp>
using __passthrough_type_t = typename __passthrough_type<_Tp>::type;

template <class _Tp, class = void>
inline constexpr bool __is_repeat_specialization = false;

template <class _Tp, class _Bound>
inline constexpr bool __is_repeat_specialization<repeat_view<_Tp, _Bound>, void> = true;

struct __fn {
    // empty_view passthrough: the result is the original (empty) range.
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<_Np, range_difference_t<_Range>> && __is_empty_view<_RawRange>))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&&) const -> _RawRange
    {
        return static_cast<::asc::std::decay_t<decltype((::asc::std::forward<_Range>(__range)))>>(
            ::asc::std::forward<_Range>(__range));
    }

    // span / basic_string_view / subrange passthrough: rebuild a range of the same
    // type.
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>, class _Dist = range_difference_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<_Np, range_difference_t<_Range>> && (!__is_empty_view<_RawRange>) &&
        random_access_range<_RawRange> && sized_range<_RawRange> && __is_passthrough_specialization<_RawRange>))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __rng, _Np&& __n) const -> __passthrough_type_t<_RawRange>
    {
        const auto count =
            ::asc::std::min<_Dist>(static_cast<_Dist>(::asc::std::ranges::size(__rng)), ::asc::std::forward<_Np>(__n));
        auto first = ::asc::std::ranges::__begin_cpo{}(__rng);
        if constexpr (__is_asc_std_basic_string_view_v<_RawRange>) {
            // ASC string_view exposes (pointer, count), not (first, last).
            return __passthrough_type_t<_RawRange>(first, static_cast<typename _RawRange::size_type>(count));
        } else {
            return __passthrough_type_t<_RawRange>(first, first + count);
        }
    }

    // repeat_view satisfying sized_range: the repeated value is unchanged,
    // truncated to min(count, n).
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>, class _Dist = range_difference_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<_Np, range_difference_t<_Range>> &&
        __is_repeat_specialization<_RawRange> && sized_range<_RawRange>))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&& __n) const -> _RawRange
    {
        auto __dist = static_cast<_Dist>(::asc::std::ranges::size(__range));
        auto __value = *__range.begin();
        return ::asc::std::ranges::views::repeat(::asc::std::forward_like<_Range>(__value),
            ::asc::std::min<_Dist>(__dist, ::asc::std::forward<_Np>(__n)));  // NOLINT(build/include_what_you_use)
    }

    // repeat_view in the remaining case: n becomes the new repetition count.
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>, class _Dist = range_difference_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<_Np, range_difference_t<_Range>> &&
        __is_repeat_specialization<_RawRange> && (!sized_range<_RawRange>)))
    CANN_ASC_STL_API constexpr auto operator()(
        _Range&& __range, _Np&& __n) const -> repeat_view<range_value_t<_RawRange>, _Dist>
    {
        auto __value = *__range.begin();
        return ::asc::std::ranges::views::repeat(
            ::asc::std::forward_like<_Range>(__value), static_cast<_Dist>(::asc::std::forward<_Np>(__n)));
    }

    // iota_view specialization: the new sentinel is the first value plus
    // min(distance, n).
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>, class _Dist = range_difference_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<_Np, range_difference_t<_Range>> && (!__is_empty_view<_RawRange>) &&
        random_access_range<_RawRange> && sized_range<_RawRange> && __is_iota_specialization<_RawRange>))
    CANN_ASC_STL_API constexpr auto operator()(
        _Range&& __rng, _Np&& __n) const -> iota_view<range_value_t<_RawRange>, _Dist>
    {
        return ::asc::std::ranges::iota_view(*::asc::std::ranges::__begin_cpo{}(__rng),
            *::asc::std::ranges::__begin_cpo{}(__rng) +
                ::asc::std::min<_Dist>(
                    static_cast<_Dist>(::asc::std::ranges::size(__rng)), ::asc::std::forward<_Np>(__n)));
    }

    // General case: wrap in a take_view.
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES(((!__is_empty_view<_RawRange>) && (!__is_repeat_specialization<_RawRange>) &&
        (!(random_access_range<_RawRange> && sized_range<_RawRange> &&
            (__is_passthrough_specialization<_RawRange> || __is_iota_specialization<_RawRange>)))))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&& __n) const
    {
        auto view = ::asc::std::ranges::views::all(::asc::std::forward<_Range>(__range));
        // NOLINTNEXTLINE(build/include_what_you_use)
        return ::asc::std::ranges::take_view<decltype(view)>(::asc::std::move(view), ::asc::std::forward<_Np>(__n));
    }
};

}  // namespace __take_detail

struct __take_fn : __counted_adaptor<__take_fn, __take_detail::__fn> {};
inline constexpr __take_fn take{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_TAKE_VIEW_H
