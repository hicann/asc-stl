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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_DROP_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_DROP_VIEW_H

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
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__fwd/span.h>
#include <asc/std/__fwd/string_view.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/counted_adaptor.h>
#include <asc/std/__ranges/empty_view.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/iota_view.h>
#include <asc/std/__ranges/non_propagating_cache.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/repeat_view.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/subrange.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/forward_like.h>
#include <asc/std/__utility/move.h>

#ifndef CANN_ASC_STL_DETAIL_ASSERT
#ifndef ASC_ENABLE_ASSERTIONS
#ifdef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#define ASC_ENABLE_ASSERTIONS
#endif  // CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // !ASC_ENABLE_ASSERTIONS

#ifndef ASC_ENABLE_HOST_ASSERTIONS
#ifdef ASC_ENABLE_ASSERTIONS
#define ASC_ENABLE_HOST_ASSERTIONS
#endif  // ASC_ENABLE_ASSERTIONS
#endif  // !ASC_ENABLE_HOST_ASSERTIONS

#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// ASC device side has no assertion mechanism
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#elif defined(ASC_ENABLE_HOST_ASSERTIONS)
#ifdef NDEBUG
// <assert.h> is not necessarily included under NDEBUG; declare the prototype manually
extern "C" {
void __assert_fail(const char* __assertion, const char* __file, unsigned int __line, const char* __function) noexcept
    __attribute__((__noreturn__));
}  // extern "C"
#else
#include <assert.h>
#endif  // NDEBUG
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    __builtin_expect(static_cast<bool>(expression), 1) ? (void)0 : __assert_fail(message, __FILE__, __LINE__, __func__)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#endif  // CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#endif  // !CANN_ASC_STL_DETAIL_ASSERT

namespace asc::std::ranges {
// Both language modes and execution spaces share this implementation.
// Native constraints and SFINAE provide the same conditional members.

template <class _View>
inline constexpr bool __drop_simple_view = __simple_view<_View>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <view _View>
#else
template <class _View>
#endif
class drop_view : public view_interface<drop_view<_View>> {
    static_assert(view<_View>, "range view constraints are not satisfied");

    // begin() result cache: caches whenever __next is not guaranteed O(1), so begin()
    // stays amortized O(1); for an input_range, begin() is not equality-preserving and
    // must not be cached (a single-pass range calls begin() only once anyway).
    static constexpr bool _UseCache = forward_range<_View> && !(random_access_range<_View> && sized_range<_View>);
    using _Cache = conditional_t<_UseCache, __non_propagating_cache<iterator_t<_View>>, __empty_cache>;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Cache __cached_begin_ = _Cache();
    _View __base_ = _View();
    range_difference_t<_View> __count_ = 0;

    // Advance at most count steps without passing the sentinel (an equivalent
    // portable implementation of the three-argument next).
    CANN_ASC_STL_API static constexpr iterator_t<_View> __next_at_most(
        iterator_t<_View> __iter, range_difference_t<_View> __count, sentinel_t<_View> __last)
    {
        for (; __count > 0 && __iter != __last; --__count) {
            ++__iter;
        }
        return __iter;
    }

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    drop_view()
        requires default_initializable<_View>
    = default;
#else
    template <bool __asc_enabled = true, enable_if_t<__asc_enabled && (default_initializable<_View>), int> = 0>
    CANN_ASC_STL_API constexpr drop_view()
    {}
#endif

    CANN_ASC_STL_API constexpr drop_view(_View __base, range_difference_t<_View> __count)  //
        noexcept(is_nothrow_move_constructible_v<_View>)
        : view_interface<drop_view<_View>>(), __base_(::asc::std::move(__base)), __count_(__count)
    {
        CANN_ASC_STL_DETAIL_ASSERT(__count_ >= 0, "count must be greater than or equal to zero.");
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((copy_constructible<_View2>))
    CANN_ASC_STL_API constexpr _View base() const& noexcept(is_nothrow_copy_constructible_v<_View2>)
    {
        return __base_;
    }

    CANN_ASC_STL_API constexpr _View base() && noexcept(is_nothrow_move_constructible_v<_View>)
    {
        return ::asc::std::move(__base_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES(
        ((!(__drop_simple_view<_View2> && random_access_range<const _View2> && sized_range<const _View2>))))
    CANN_ASC_STL_API constexpr auto begin()
    {
        if constexpr (random_access_range<_View2> && sized_range<_View2>) {
            const auto __dist = ::asc::std::min<range_difference_t<_View>>(
                static_cast<range_difference_t<_View>>(::asc::std::ranges::__size_cpo{}(__base_)), __count_);
            return ::asc::std::ranges::__begin_cpo{}(__base_) + __dist;
        } else if constexpr (_UseCache) {
            if (!__cached_begin_.__has_value()) {
                __cached_begin_.__emplace(__next_at_most(
                    ::asc::std::ranges::__begin_cpo{}(__base_), __count_, ::asc::std::ranges::__end_cpo{}(__base_)));
            }
            return *__cached_begin_;
        } else {
            return __next_at_most(
                ::asc::std::ranges::__begin_cpo{}(__base_), __count_, ::asc::std::ranges::__end_cpo{}(__base_));
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<const _View2> && sized_range<const _View2>))
    CANN_ASC_STL_API constexpr auto begin() const
    {
        const auto __dist = ::asc::std::min<range_difference_t<_View>>(
            static_cast<range_difference_t<_View>>(::asc::std::ranges::__size_cpo{}(__base_)), __count_);
        return ::asc::std::ranges::__begin_cpo{}(__base_) + __dist;
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES(((!__drop_simple_view<_View2>)))
    CANN_ASC_STL_API constexpr auto end()
    {
        return ::asc::std::ranges::__end_cpo{}(__base_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((range<const _View2>))
    CANN_ASC_STL_API constexpr auto end() const
    {
        return ::asc::std::ranges::__end_cpo{}(__base_);
    }

    template <class _Self = drop_view>
    CANN_ASC_STL_API static constexpr auto __size(_Self& __self)
    {
        const auto __s = ::asc::std::ranges::__size_cpo{}(__self.__base_);
        const auto __c = static_cast<decltype(__s)>(__self.__count_);
        return __s < __c ? 0 : __s - __c;
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<_View2>))
    CANN_ASC_STL_API constexpr auto size()
    {
        return __size(*this);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<const _View2>))
    CANN_ASC_STL_API constexpr auto size() const
    {
        return __size(*this);
    }
};

template <class _Range>
CANN_ASC_STL_HOST_DEVICE drop_view(
    _Range&&, range_difference_t<_Range>) -> drop_view<::asc::std::ranges::views::all_t<_Range>>;

template <class _Tp>
inline constexpr bool enable_borrowed_range<drop_view<_Tp>> = enable_borrowed_range<_Tp>;

namespace views {

// Adaptor dispatch internals (passthrough and specialization detection for
// span/basic_string_view/iota_view/subrange/repeat_view).
namespace __drop_detail {

template <class _Iter, ::asc::std::ranges::subrange_kind _Kind>
struct __stores_size_impl
    : ::asc::std::bool_constant<_Kind == ::asc::std::ranges::subrange_kind::sized && !forward_iterator<_Iter>> {};

template <class _Iter, ::asc::std::ranges::subrange_kind _Kind>
inline constexpr bool __stores_size = __stores_size_impl<_Iter, _Kind>::value;

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

template <class _Np, class _Bound>
inline constexpr bool __is_passthrough_specialization<iota_view<_Np, _Bound>> = true;

template <class _Iter, class _Sent, ::asc::std::ranges::subrange_kind _Kind>
inline constexpr bool __is_passthrough_specialization<::asc::std::ranges::subrange<_Iter, _Sent, _Kind>> =
    !__stores_size<_Iter, _Kind>;

template <class _Tp>
inline constexpr bool __is_subrange_with_stored_size = false;

template <class _Iter, class _Sent, ::asc::std::ranges::subrange_kind _Kind>
inline constexpr bool __is_subrange_with_stored_size<::asc::std::ranges::subrange<_Iter, _Sent, _Kind>> =
    __stores_size<_Iter, _Kind>;

template <class _Tp>
struct __passthrough_type;

template <class _Tp, size_t _Extent>
struct __passthrough_type<span<_Tp, _Extent>> {
    using type = span<_Tp>;
};

template <class _CharT, class _Traits>
struct __passthrough_type<basic_string_view<_CharT, _Traits>> {
    using type = basic_string_view<_CharT, _Traits>;
};

template <class _Np, class _Bound>
struct __passthrough_type<iota_view<_Np, _Bound>> {
    using type = iota_view<_Np, _Bound>;
};

template <class _Iter, class _Sent, ::asc::std::ranges::subrange_kind _Kind>
struct __passthrough_type<::asc::std::ranges::subrange<_Iter, _Sent, _Kind>> {
    using type = ::asc::std::ranges::subrange<_Iter, _Sent, _Kind>;
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

    // span / basic_string_view / iota_view / subrange (without stored size) passthrough:
    // rebuild a range of the same type.
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>, class _Dist = range_difference_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<_Np, range_difference_t<_Range>> && (!__is_empty_view<_RawRange>) &&
        random_access_range<_RawRange> && sized_range<_RawRange> && __is_passthrough_specialization<_RawRange>))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __rng, _Np&& __n) const -> __passthrough_type_t<_RawRange>
    {
        // Deliberately do not forward __rng, to avoid a double move.
        const auto distance = static_cast<_Dist>(::asc::std::ranges::size(__rng));
        const auto count = ::asc::std::min<_Dist>(distance, ::asc::std::forward<_Np>(__n));
        auto first = ::asc::std::ranges::__begin_cpo{}(__rng) + count;
        if constexpr (__is_asc_std_basic_string_view_v<_RawRange>) {
            return __passthrough_type_t<_RawRange>(first, static_cast<typename _RawRange::size_type>(distance - count));
        } else {
            return __passthrough_type_t<_RawRange>(first, ::asc::std::ranges::__end_cpo{}(__rng));
        }
    }

    // subrange (with stored size) specialization: rebuild and state the remaining size
    // explicitly.
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>, class _Dist = range_difference_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<_Np, range_difference_t<_Range>> && (!__is_empty_view<_RawRange>) &&
        random_access_range<_RawRange> && sized_range<_RawRange> && __is_subrange_with_stored_size<_RawRange>))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __rng, _Np&& __n) const -> _RawRange
    {
        auto __dist = static_cast<_Dist>(::asc::std::ranges::size(__rng));
        auto __clamped = ::asc::std::min<_Dist>(__dist, ::asc::std::forward<_Np>(__n));
        return _RawRange(::asc::std::ranges::__begin_cpo{}(__rng) + __clamped, ::asc::std::ranges::__end_cpo{}(__rng),
            static_cast<::asc::std::make_unsigned_t<_Dist>>(__dist - __clamped));
    }

    // repeat_view satisfying sized_range: the repeated value is unchanged, the count
    // is reduced.
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>, class _Dist = range_difference_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<_Np, range_difference_t<_Range>> &&
        __is_repeat_specialization<_RawRange> && sized_range<_RawRange>))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&& __n) const -> _RawRange
    {
        auto __dist = static_cast<_Dist>(::asc::std::ranges::size(__range));
        auto __value = *__range.begin();
        return ::asc::std::ranges::views::repeat(::asc::std::forward_like<_Range>(__value),
            __dist -
                ::asc::std::min<_Dist>(__dist, ::asc::std::forward<_Np>(__n)));  // NOLINT(build/include_what_you_use)
    }

    // repeat_view in the remaining case: drop does not change an unbounded repetition
    // sequence.
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES((convertible_to<_Np, range_difference_t<_Range>> &&
        __is_repeat_specialization<_RawRange> && (!sized_range<_RawRange>)))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&&) const -> _RawRange
    {
        return static_cast<::asc::std::decay_t<decltype((::asc::std::forward<_Range>(__range)))>>(
            ::asc::std::forward<_Range>(__range));
    }

    // General case: wrap in a drop_view.
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES(((!__is_empty_view<_RawRange>) && (!__is_repeat_specialization<_RawRange>) &&
        (!(random_access_range<_RawRange> && sized_range<_RawRange> &&
            (__is_passthrough_specialization<_RawRange> || __is_subrange_with_stored_size<_RawRange>)))))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&& __n) const
    {
        auto view = ::asc::std::ranges::views::all(::asc::std::forward<_Range>(__range));
        // NOLINTNEXTLINE(build/include_what_you_use)
        return ::asc::std::ranges::drop_view<decltype(view)>(::asc::std::move(view), ::asc::std::forward<_Np>(__n));
    }
};

}  // namespace __drop_detail

struct __drop_fn : __counted_adaptor<__drop_fn, __drop_detail::__fn> {};
inline constexpr __drop_fn drop{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_DROP_VIEW_H
