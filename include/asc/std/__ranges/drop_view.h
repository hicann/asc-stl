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
#include <asc/std/__algorithm/min.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__fwd/span.h>
#include <asc/std/__fwd/string_view.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
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
#include <asc/std/__type_traits/enable_if.h>
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
// ASC 设备侧无断言机制
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#elif defined(ASC_ENABLE_HOST_ASSERTIONS)
#ifdef NDEBUG
// NDEBUG 下 <assert.h> 未必已包含，手工补声明
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
// 设备编译下 concept 约束求值不可用（纯 SIMT 后端），回退到弱约束版本，两分支公开接口一致。
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class _View>
concept __drop_simple_view = view<_View> && range<const _View> && same_as<iterator_t<_View>, iterator_t<const _View>> &&
    same_as<sentinel_t<_View>, sentinel_t<const _View>>;

template <view _View>
class drop_view : public view_interface<drop_view<_View>> {
    // begin() 结果缓存：__next 非保证 O(1) 时缓存以提供摊还 O(1) 的 begin()；
    // input_range 下 begin() 非相等保持，不可缓存（但单遍也只会调用一次 begin()）。
    static constexpr bool _UseCache = forward_range<_View> && !(random_access_range<_View> && sized_range<_View>);
    using _Cache = conditional_t<_UseCache, __non_propagating_cache<iterator_t<_View>>, __empty_cache>;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Cache __cached_begin_ = _Cache();
    _View __base_ = _View();
    range_difference_t<_View> __count_ = 0;

    // 前进至多 count 步且不越过哨兵（三参数 next 的等价可移植实现）。
    CANN_ASC_STL_API static constexpr iterator_t<_View> __next_at_most(
        iterator_t<_View> __iter, range_difference_t<_View> __count, sentinel_t<_View> __last)
    {
        for (; __count > 0 && __iter != __last; --__count) {
            ++__iter;
        }
        return __iter;
    }

public:
    drop_view()
        requires default_initializable<_View>
    = default;

    CANN_ASC_STL_API constexpr drop_view(_View __base, range_difference_t<_View> __count)  //
        noexcept(is_nothrow_move_constructible_v<_View>)
        : view_interface<drop_view<_View>>(), __base_(::asc::std::move(__base)), __count_(__count)
    {
        CANN_ASC_STL_DETAIL_ASSERT(__count_ >= 0, "count must be greater than or equal to zero.");
    }

    template <class _View2 = _View>
        requires copy_constructible<_View2>
    CANN_ASC_STL_API constexpr _View base() const& noexcept(is_nothrow_copy_constructible_v<_View2>)
    {
        return __base_;
    }

    CANN_ASC_STL_API constexpr _View base() && noexcept(is_nothrow_move_constructible_v<_View>)
    {
        return ::asc::std::move(__base_);
    }

    template <class _View2 = _View>
        requires(!(__drop_simple_view<_View2> && random_access_range<const _View2> && sized_range<const _View2>))
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

    template <class _View2 = _View>
        requires random_access_range<const _View2> && sized_range<const _View2>
    CANN_ASC_STL_API constexpr auto begin() const
    {
        const auto __dist = ::asc::std::min<range_difference_t<_View>>(
            static_cast<range_difference_t<_View>>(::asc::std::ranges::__size_cpo{}(__base_)), __count_);
        return ::asc::std::ranges::__begin_cpo{}(__base_) + __dist;
    }

    template <class _View2 = _View>
        requires(!__drop_simple_view<_View2>)
    CANN_ASC_STL_API constexpr auto end()
    {
        return ::asc::std::ranges::__end_cpo{}(__base_);
    }

    template <class _View2 = _View>
        requires range<const _View2>
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

    template <class _View2 = _View>
        requires sized_range<_View2>
    CANN_ASC_STL_API constexpr auto size()
    {
        return __size(*this);
    }

    template <class _View2 = _View>
        requires sized_range<const _View2>
    CANN_ASC_STL_API constexpr auto size() const
    {
        return __size(*this);
    }
};

#else

template <class View>
class drop_view : public view_interface<drop_view<View>> {
public:
    CANN_ASC_STL_API constexpr drop_view() = default;
    CANN_ASC_STL_API constexpr drop_view(View view, range_difference_t<View> count) noexcept(
        is_nothrow_move_constructible_v<View>)
        : view_(::asc::std::move(view)), count_(count)
    {}
    CANN_ASC_STL_API constexpr auto begin()
    {
        auto value = ranges::begin(view_);
        auto last = ranges::end(view_);
        for (auto n = count_; n > 0 && value != last; --n)
            ++value;
        return value;
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto begin() const
    {
        auto value = ranges::begin(view_);
        auto last = ranges::end(view_);
        for (auto n = count_; n > 0 && value != last; --n)
            ++value;
        return value;
    }
    CANN_ASC_STL_API constexpr auto end()
    {
        return ranges::end(view_);
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto end() const
    {
        return ranges::end(view_);
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto size()
    {
        const auto value = ranges::size(view_);
        return value < static_cast<decltype(value)>(count_) ? 0 : value - count_;
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto size() const
    {
        const auto value = ranges::size(view_);
        return value < static_cast<decltype(value)>(count_) ? 0 : value - count_;
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr View base() const& noexcept(is_nothrow_copy_constructible_v<View2>)
    {
        return view_;
    }
    CANN_ASC_STL_API constexpr View base() && noexcept(is_nothrow_move_constructible_v<View>)
    {
        return ::asc::std::move(view_);
    }

private:
    View view_{};
    range_difference_t<View> count_{};
};

#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class _Range>
drop_view(_Range&&, range_difference_t<_Range>) -> drop_view<::asc::std::ranges::views::all_t<_Range>>;

template <class _Tp>
inline constexpr bool enable_borrowed_range<drop_view<_Tp>> = enable_borrowed_range<_Tp>;

namespace views {

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// 适配器分发内部符号（span/basic_string_view/iota_view/subrange/repeat_view 的直通与特化判定）。
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
    // empty_view 直通：结果即为原（空）范围。
    template <class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>>
        requires convertible_to<_Np, range_difference_t<_Range>> && __is_empty_view<_RawRange>
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&&) const -> _RawRange
    {
        return static_cast<::asc::std::decay_t<decltype((::asc::std::forward<_Range>(__range)))>>(
            ::asc::std::forward<_Range>(__range));
    }

    // span / basic_string_view / iota_view / subrange（不存尺寸）直通：重建同类型区间。
    template <class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>,
        class _Dist = range_difference_t<_Range>>
        requires convertible_to<_Np, range_difference_t<_Range>> &&
                     (!__is_empty_view<_RawRange>) && random_access_range<_RawRange> && sized_range<_RawRange> &&
                     __is_passthrough_specialization<_RawRange>
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __rng, _Np&& __n) const -> __passthrough_type_t<_RawRange>
    {
        // 故意不转发 __rng，防双移动。
        return __passthrough_type_t<_RawRange>(::asc::std::ranges::__begin_cpo{}(__rng) +
                ::asc::std::min<_Dist>(
                    static_cast<_Dist>(::asc::std::ranges::size(__rng)), ::asc::std::forward<_Np>(__n)),
            ::asc::std::ranges::__end_cpo{}(__rng));
    }

    // subrange（存尺寸）特化：重建并显式给出剩余尺寸。
    template <class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>,
        class _Dist = range_difference_t<_Range>>
        requires convertible_to<_Np, range_difference_t<_Range>> &&
                     (!__is_empty_view<_RawRange>) && random_access_range<_RawRange> && sized_range<_RawRange> &&
                     __is_subrange_with_stored_size<_RawRange>
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __rng, _Np&& __n) const -> _RawRange
    {
        auto __dist = static_cast<_Dist>(::asc::std::ranges::size(__rng));
        auto __clamped = ::asc::std::min<_Dist>(__dist, ::asc::std::forward<_Np>(__n));
        return _RawRange(::asc::std::ranges::__begin_cpo{}(__rng) + __clamped, ::asc::std::ranges::__end_cpo{}(__rng),
            static_cast<::asc::std::make_unsigned_t<_Dist>>(__dist - __clamped));
    }

    // repeat_view 且满足 sized_range：重复值不变、次数扣减。
    template <class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>,
        class _Dist = range_difference_t<_Range>>
        requires convertible_to<_Np, range_difference_t<_Range>> && __is_repeat_specialization<_RawRange> &&
                     sized_range<_RawRange>
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&& __n) const -> _RawRange
    {
        auto __dist = static_cast<_Dist>(::asc::std::ranges::size(__range));
        auto __value = *__range.begin();
        return ::asc::std::ranges::views::repeat(::asc::std::forward_like<_Range>(__value),
            __dist -
                ::asc::std::min<_Dist>(__dist, ::asc::std::forward<_Np>(__n)));  // NOLINT(build/include_what_you_use)
    }

    // repeat_view 其余情形：drop 不改变无界重复序列。
    template <class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>>
        requires convertible_to<_Np, range_difference_t<_Range>> && __is_repeat_specialization<_RawRange> &&
                     (!sized_range<_RawRange>)
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&&) const -> _RawRange
    {
        return static_cast<::asc::std::decay_t<decltype((::asc::std::forward<_Range>(__range)))>>(
            ::asc::std::forward<_Range>(__range));
    }

    // 其余一般情形：包一层 drop_view。
    template <class _Range, class _Np, class _RawRange = remove_cvref_t<_Range>>
        requires(!__is_empty_view<_RawRange>) && (!__is_repeat_specialization<_RawRange>) &&
        (!(random_access_range<_RawRange> && sized_range<_RawRange> &&
            (__is_passthrough_specialization<_RawRange> || __is_subrange_with_stored_size<_RawRange>)))
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Np&& __n) const
    {
        auto view = ::asc::std::ranges::views::all(::asc::std::forward<_Range>(__range));
        return ::asc::std::ranges::drop_view<decltype(view)>(::asc::std::move(view), ::asc::std::forward<_Np>(__n));
    }
};

}  // namespace __drop_detail
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class Difference>
class __drop_closure : public range_adaptor_closure<__drop_closure<Difference>> {
public:
    CANN_ASC_STL_API constexpr explicit __drop_closure(Difference count) : count_(count)
    {}
    template <class Range>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range) const
    {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return __drop_detail::__fn{}(::asc::std::forward<Range>(range), count_);
#else
        auto view = views::all(::asc::std::forward<Range>(range));
        return drop_view<decltype(view)>(::asc::std::move(view), count_);
#endif
    }

private:
    Difference count_;
};

struct __drop_fn {
    template <class Range, class Difference>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range, Difference count) const
    {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return __drop_detail::__fn{}(::asc::std::forward<Range>(range), ::asc::std::forward<Difference>(count));
#else
        auto view = views::all(::asc::std::forward<Range>(range));
        return drop_view<decltype(view)>(::asc::std::move(view), count);  // NOLINT(build/include_what_you_use)
#endif
    }
    template <class Difference>
    CANN_ASC_STL_API constexpr __drop_closure<Difference> operator()(Difference count) const
    {
        return __drop_closure<Difference>(count);
    }
};
inline constexpr __drop_fn drop{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_DROP_VIEW_H
