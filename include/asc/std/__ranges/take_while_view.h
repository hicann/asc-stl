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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_TAKE_WHILE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_TAKE_WHILE_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/maybe_const.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// concepts.h does not provide __simple_view, so its definition is minimally
// inlined here under a private name (avoids clashing with other headers that
// define it).
template <class _View>
inline constexpr bool __take_while_simple_view = __simple_view<_View>;

template <class _View, class _Pred, class = void>
inline constexpr bool __take_while_const_is_range = false;
template <class _View, class _Pred>
inline constexpr bool __take_while_const_is_range<_View, _Pred, void_t<iterator_t<const _View>>> =
    range<const _View> && indirect_unary_predicate<const _Pred, iterator_t<const _View>>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <view _View, class _Pred>
    requires input_range<_View> && ::asc::std::is_object_v<_Pred> &&
    ::asc::std::indirect_unary_predicate<const _Pred, iterator_t<_View>>
#else
template <class _View, class _Pred>
#endif
class take_while_view : public view_interface<take_while_view<_View, _Pred>> {
    static_assert(view<_View> &&
            (input_range<_View> && ::asc::std::is_object_v<_Pred> &&
                ::asc::std::indirect_unary_predicate<const _Pred, iterator_t<_View>>),
        "range view constraints are not satisfied");

    CANN_ASC_STL_NO_UNIQUE_ADDRESS __movable_box<_Pred> __pred_;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _View __base_ = _View();

public:
    template <bool>
    class __sentinel;

    template <bool _Const>
    class __sentinel {
        using _Base = __maybe_const<_Const, _View>;
        template <bool _OtherConst>
        using _Base2 = __maybe_const<_OtherConst, _View>;

        sentinel_t<_Base> __end_ = sentinel_t<_Base>();
        const _Pred* __pred_ = nullptr;

        friend class __sentinel<!_Const>;

    public:
        CANN_ASC_STL_API constexpr __sentinel() = default;

        CANN_ASC_STL_API constexpr explicit __sentinel(sentinel_t<_Base> __end, const _Pred* __pred)
            : __end_(::asc::std::move(__end)), __pred_(__pred)
        {}

        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = _Const)
        CANN_ASC_STL_DETAIL_REQUIRES(
            (_OtherConst && convertible_to<sentinel_t<_View>, sentinel_t<_Base2<_OtherConst>>>))
        CANN_ASC_STL_API constexpr __sentinel(__sentinel<!_OtherConst> __s)
            : __end_(::asc::std::move(__s.__end_)), __pred_(__s.__pred_)
        {}

        [[nodiscard]] CANN_ASC_STL_API constexpr sentinel_t<_Base> base() const
        {
            return __end_;
        }

        [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
            const iterator_t<_Base>& __x, const __sentinel& __y)
        {
            return __x == __y.__end_ || !::asc::std::invoke(*__y.__pred_, *__x);
        }
        // The lazy sentinel's difference is computed by walking to the predicate
        // breakpoint (same value as an eager scan, O(n) complexity).
        CANN_ASC_STL_API friend constexpr auto operator-(const __sentinel& __y, const iterator_t<_Base>& __x)
        {
            auto __it = __x;
            ::asc::std::iter_difference_t<iterator_t<_Base>> __n = 0;
            while (!(__it == __y.__end_ || !::asc::std::invoke(*__y.__pred_, *__it))) {
                ++__it;
                ++__n;
            }
            return __n;
        }
        CANN_ASC_STL_API friend constexpr auto operator-(const iterator_t<_Base>& __x, const __sentinel& __y)
        {
            return -(__y - __x);
        }
        // Both reversed ==/!= overloads are kept for C++17 compatibility; under
        // C++20 the explicit candidates agree with the synthesized rewriting
        // semantics of == and !=.
        [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
            const __sentinel& __x, const iterator_t<_Base>& __y)
        {
            return __y == __x.__end_ || !::asc::std::invoke(*__x.__pred_, *__y);
        }
        [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
            const iterator_t<_Base>& __x, const __sentinel& __y)
        {
            return __x != __y.__end_ && ::asc::std::invoke(*__y.__pred_, *__x);
        }
        [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
            const __sentinel& __x, const iterator_t<_Base>& __y)
        {
            return __y != __x.__end_ && ::asc::std::invoke(*__x.__pred_, *__y);
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = !_Const)
        CANN_ASC_STL_DETAIL_REQUIRES(sentinel_for<sentinel_t<_Base>, iterator_t<_Base2<_OtherConst>>>)
        [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator==(
            const iterator_t<_Base2<_OtherConst>>& __x, const __sentinel& __y)
        {
            return __x == __y.__end_ || !::asc::std::invoke(*__y.__pred_, *__x);
        }
        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = !_Const)
        CANN_ASC_STL_DETAIL_REQUIRES(sentinel_for<sentinel_t<_Base>, iterator_t<_Base2<_OtherConst>>>)
        [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator==(
            const __sentinel& __x, const iterator_t<_Base2<_OtherConst>>& __y)
        {
            return __y == __x.__end_ || !::asc::std::invoke(*__x.__pred_, *__y);
        }
        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = !_Const)
        CANN_ASC_STL_DETAIL_REQUIRES(sentinel_for<sentinel_t<_Base>, iterator_t<_Base2<_OtherConst>>>)
        [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator!=(
            const iterator_t<_Base2<_OtherConst>>& __x, const __sentinel& __y)
        {
            return __x != __y.__end_ && ::asc::std::invoke(*__y.__pred_, *__x);
        }
        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = !_Const)
        CANN_ASC_STL_DETAIL_REQUIRES(sentinel_for<sentinel_t<_Base>, iterator_t<_Base2<_OtherConst>>>)
        [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator!=(
            const __sentinel& __x, const iterator_t<_Base2<_OtherConst>>& __y)
        {
            return __y != __x.__end_ && ::asc::std::invoke(*__x.__pred_, *__y);
        }
    };

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr take_while_view()
        requires ::asc::std::default_initializable<_View> && ::asc::std::default_initializable<_Pred>
    = default;
#else
    template <bool __asc_enabled = true,
        enable_if_t<__asc_enabled &&
                (::asc::std::default_initializable<_View> && ::asc::std::default_initializable<_Pred>),
            int> = 0>
    CANN_ASC_STL_API constexpr take_while_view()
    {}
#endif

    CANN_ASC_STL_API constexpr take_while_view(_View __base, _Pred __pred)
        : view_interface<take_while_view<_View, _Pred>>(),
          __pred_(in_place_t{}, ::asc::std::move(__pred)),
          __base_(::asc::std::move(__base))
    {}

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((::asc::std::copy_constructible<_View2>))
    CANN_ASC_STL_API constexpr _View base() const&
    {
        return __base_;
    }

    CANN_ASC_STL_API constexpr _View base() &&
    {
        return ::asc::std::move(__base_);
    }

    CANN_ASC_STL_API constexpr const _Pred& pred() const
    {
        return *__pred_;
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES(((!__take_while_simple_view<_View2>)))
    CANN_ASC_STL_API constexpr auto begin()
    {
        return ::asc::std::ranges::__begin_cpo{}(__base_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((__take_while_const_is_range<_View2, _Pred>))
    CANN_ASC_STL_API constexpr auto begin() const
    {
        return ::asc::std::ranges::__begin_cpo{}(__base_);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES(((!__take_while_simple_view<_View2>)))
    CANN_ASC_STL_API constexpr auto end()
    {
        return __sentinel<false>(::asc::std::ranges::__end_cpo{}(__base_), ::asc::std::addressof(*__pred_));
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((__take_while_const_is_range<_View2, _Pred>))
    CANN_ASC_STL_API constexpr auto end() const
    {
        return __sentinel<true>(::asc::std::ranges::__end_cpo{}(__base_), ::asc::std::addressof(*__pred_));
    }
};

template <class _Range, class _Pred>
CANN_ASC_STL_HOST_DEVICE take_while_view(
    _Range&&, _Pred) -> take_while_view<::asc::std::ranges::views::all_t<_Range>, _Pred>;

}  // namespace ranges

namespace ranges::views {

namespace __take_while {

struct __fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Range, class _Pred, class _View = all_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES(
        input_range<_View>&& is_object_v<decay_t<_Pred>>&& indirect_unary_predicate<const decay_t<_Pred>,
            iterator_t<_View>>&& constructible_from<decay_t<_Pred>, _Pred>)
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Pred&& __pred) const
        noexcept(noexcept(take_while_view(::asc::std::forward<_Range>(__range), ::asc::std::forward<_Pred>(__pred))))
            -> take_while_view<::asc::std::ranges::views::all_t<_Range>, ::asc::std::remove_cvref_t<_Pred>>
    {
        return take_while_view(::asc::std::forward<_Range>(__range), ::asc::std::forward<_Pred>(__pred));
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _Pred)
    CANN_ASC_STL_DETAIL_REQUIRES((::asc::std::constructible_from<::asc::std::decay_t<_Pred>, _Pred>))
    CANN_ASC_STL_API constexpr auto operator()(_Pred&& __pred) const
        noexcept(::asc::std::is_nothrow_constructible_v<::asc::std::decay_t<_Pred>, _Pred>)
    {
        return ::asc::std::ranges::__pipeable(
            ::asc::std::__bind_back(*this, ::asc::std::forward<_Pred>(__pred)));  // NOLINT(build/include_what_you_use)
    }
};

}  // namespace __take_while

inline constexpr __take_while::__fn take_while{};

}  // namespace ranges::views

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_TAKE_WHILE_VIEW_H
