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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_TRANSFORM_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_TRANSFORM_VIEW_H

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
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/maybe_const.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>

namespace asc::std::ranges {
// Both language modes and execution spaces share this implementation.
// Native constraints and SFINAE provide the same conditional members.

template <class _Fn, class _View, class = void>
inline constexpr bool __regular_invocable_with_range_ref = false;
template <class _Fn, class _View>
inline constexpr bool __regular_invocable_with_range_ref<_Fn, _View, void_t<range_reference_t<_View>>> =
    regular_invocable<_Fn, range_reference_t<_View>>;

template <class _View, class _Fn, class = void>
inline constexpr bool __transform_view_constraints = false;
template <class _View, class _Fn>
inline constexpr bool __transform_view_constraints<_View, _Fn,
    void_t<range_reference_t<_View>, invoke_result_t<_Fn&, range_reference_t<_View>>>> =
    view<_View> && is_object_v<_Fn> && regular_invocable<_Fn&, range_reference_t<_View>> &&
    __can_reference<invoke_result_t<_Fn&, range_reference_t<_View>>>;

template <class, class, class = void>
struct __transform_view_iterator_category_base {
    // A non-forward underlying iterator has no computable category, so present as
    // an input iterator (this library's traits extraction requires the category
    // member to exist).
    using iterator_category = input_iterator_tag;
};

template <class _View, class _Fn>
struct __transform_view_iterator_category_base<_View, _Fn, enable_if_t<forward_range<_View>>> {
    using _Cat = typename iterator_traits<iterator_t<_View>>::iterator_category;

    using iterator_category = conditional_t<is_reference_v<invoke_result_t<_Fn&, range_reference_t<_View>>>,
        conditional_t<derived_from<_Cat, contiguous_iterator_tag>, random_access_iterator_tag, _Cat>,
        input_iterator_tag>;
};

template <class _Fn, class _View, class = void>
inline constexpr bool __nothrow_subscript = false;

template <class _Fn, class _View>
inline constexpr bool __nothrow_subscript<_Fn, _View, enable_if_t<random_access_range<_View>>> =
    noexcept(::asc::std::invoke(::asc::std::declval<_Fn&>(), ::asc::std::declval<range_reference_t<_View>>()));

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <input_range _View, move_constructible _Fn>
    requires __transform_view_constraints<_View, _Fn>
#else
template <class _View, class _Fn>
#endif
class transform_view : public view_interface<transform_view<_View, _Fn>> {
    static_assert(input_range<_View> && move_constructible<_Fn> && (__transform_view_constraints<_View, _Fn>),
        "range view constraints are not satisfied");

    CANN_ASC_STL_NO_UNIQUE_ADDRESS _View __base_ = _View();
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __movable_box<_Fn> __func_;

public:
    template <bool>
    class __sentinel;

    template <bool _Const>
    class __iterator : public __transform_view_iterator_category_base<_View, _Fn> {
        using _Parent = __maybe_const<_Const, transform_view>;
        using _Base = __maybe_const<_Const, _View>;

        _Parent* __parent_ = nullptr;

        template <bool>
        friend class __iterator;

        template <bool>
        friend class __sentinel;

    public:
        iterator_t<_Base> __current_ = iterator_t<_Base>();

        using iterator_concept = conditional_t<random_access_range<_Base>, random_access_iterator_tag,
            conditional_t<bidirectional_range<_Base>, bidirectional_iterator_tag,
                conditional_t<forward_range<_Base>, forward_iterator_tag, input_iterator_tag>>>;
        using value_type = remove_cvref_t<invoke_result_t<__maybe_const<_Const, _Fn>&, range_reference_t<_Base>>>;
        using difference_type = range_difference_t<_Base>;
        using pointer = void;
        using reference = invoke_result_t<__maybe_const<_Const, _Fn>&, range_reference_t<_Base>>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        __iterator()
            requires default_initializable<iterator_t<_Base>>
        = default;
#else
        template <bool __asc_enabled = true,
            enable_if_t<__asc_enabled && (default_initializable<iterator_t<_Base>>), int> = 0>
        CANN_ASC_STL_API constexpr __iterator()
        {}
#endif

        CANN_ASC_STL_API constexpr __iterator(_Parent& __parent, iterator_t<_Base> __current)
            : __parent_(::asc::std::addressof(__parent)), __current_(::asc::std::move(__current))
        {}

        // Note: __i is always an __iterator<false>, but naming the type directly is
        // ill-formed when _Const is false ([class.copy.ctor]/5), hence the
        // _OtherConst indirection.
        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = _Const)
        CANN_ASC_STL_DETAIL_REQUIRES(((_OtherConst && convertible_to<iterator_t<_View>, iterator_t<_Base>>)))
        CANN_ASC_STL_API constexpr __iterator(__iterator<!_OtherConst> __i)
            : __parent_(__i.__parent_), __current_(::asc::std::move(__i.__current_))
        {}

        CANN_ASC_STL_API constexpr const iterator_t<_Base>& base() const& noexcept
        {
            return __current_;
        }

        CANN_ASC_STL_API constexpr iterator_t<_Base> base() &&
        {
            return ::asc::std::move(__current_);
        }

        CANN_ASC_STL_API constexpr decltype(auto) operator*() const
            noexcept(noexcept(::asc::std::invoke(*__parent_->__func_, *__current_)))
        {
            return ::asc::std::invoke(*__parent_->__func_, *__current_);
        }

        CANN_ASC_STL_API constexpr __iterator& operator++()
        {
            ++__current_;
            return *this;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES(((!forward_range<_Base2>)))
        CANN_ASC_STL_API constexpr void operator++(int)
        {
            ++__current_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((forward_range<_Base2>))
        CANN_ASC_STL_API constexpr __iterator operator++(int)
        {
            auto __tmp = *this;
            ++*this;
            return __tmp;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((bidirectional_range<_Base2>))
        CANN_ASC_STL_API constexpr __iterator& operator--()
        {
            --__current_;
            return *this;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((bidirectional_range<_Base2>))
        CANN_ASC_STL_API constexpr __iterator operator--(int)
        {
            auto __tmp = *this;
            --*this;
            return __tmp;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API constexpr __iterator& operator+=(difference_type __n)
        {
            __current_ += __n;
            return *this;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API constexpr __iterator& operator-=(difference_type __n)
        {
            __current_ -= __n;
            return *this;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API constexpr decltype(auto) operator[](difference_type __n) const
            noexcept(__nothrow_subscript<_Fn, _Base2>)
        {
            return ::asc::std::invoke(*__parent_->__func_, __current_[__n]);
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((equality_comparable<iterator_t<_Base2>>))
        CANN_ASC_STL_API friend constexpr bool operator==(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ == __y.__current_;
        }
        // operator!= is kept on both sides for C++17 compatibility; under C++20 the
        // explicit candidates agree with the rewritten semantics.
        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((equality_comparable<iterator_t<_Base2>>))
        CANN_ASC_STL_API friend constexpr bool operator!=(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ != __y.__current_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API friend constexpr bool operator<(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ < __y.__current_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API friend constexpr bool operator>(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ > __y.__current_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API friend constexpr bool operator<=(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ <= __y.__current_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API friend constexpr bool operator>=(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ >= __y.__current_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API friend constexpr __iterator operator+(__iterator __i, difference_type __n)
        {
            return __iterator{*__i.__parent_, __i.__current_ + __n};
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API friend constexpr __iterator operator+(difference_type __n, __iterator __i)
        {
            return __iterator{*__i.__parent_, __i.__current_ + __n};
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((random_access_range<_Base2>))
        CANN_ASC_STL_API friend constexpr __iterator operator-(__iterator __i, difference_type __n)
        {
            return __iterator{*__i.__parent_, __i.__current_ - __n};
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _Base2 = _Base)
        CANN_ASC_STL_DETAIL_REQUIRES((sized_sentinel_for<iterator_t<_Base2>, iterator_t<_Base2>>))
        CANN_ASC_STL_API friend constexpr difference_type operator-(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ - __y.__current_;
        }
    };

    template <bool _Const>
    class __sentinel {
        using _Parent = __maybe_const<_Const, transform_view>;
        using _Base = __maybe_const<_Const, _View>;

        sentinel_t<_Base> __end_ = sentinel_t<_Base>();

        template <bool>
        friend class __iterator;

        template <bool>
        friend class __sentinel;

    public:
        constexpr __sentinel() = default;

        CANN_ASC_STL_API constexpr explicit __sentinel(sentinel_t<_Base> __end) : __end_(__end)
        {}

        // Note: __i is always a __sentinel<false>, but naming the type directly is
        // ill-formed when _Const is false ([class.copy.ctor]/5), hence the
        // _OtherConst indirection.
        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst = _Const)
        CANN_ASC_STL_DETAIL_REQUIRES(((_OtherConst && convertible_to<sentinel_t<_View>, sentinel_t<_Base>>)))
        CANN_ASC_STL_API constexpr __sentinel(__sentinel<!_OtherConst> __i) : __end_(::asc::std::move(__i.__end_))
        {}

        CANN_ASC_STL_API constexpr sentinel_t<_Base> base() const
        {
            return __end_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst)
        CANN_ASC_STL_DETAIL_REQUIRES((sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr bool operator==(const __iterator<_OtherConst>& __x, const __sentinel& __y)
        {
            return __x.__current_ == __y.__end_;
        }
        // Both reversed ==/!= overloads are kept for C++17 compatibility; under
        // C++20 the explicit candidates agree with the rewritten operators.
        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst)
        CANN_ASC_STL_DETAIL_REQUIRES((sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr bool operator==(const __sentinel& __x, const __iterator<_OtherConst>& __y)
        {
            return __x.__end_ == __y.__current_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst)
        CANN_ASC_STL_DETAIL_REQUIRES((sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr bool operator!=(const __iterator<_OtherConst>& __x, const __sentinel& __y)
        {
            return __x.__current_ != __y.__end_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst)
        CANN_ASC_STL_DETAIL_REQUIRES((sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr bool operator!=(const __sentinel& __x, const __iterator<_OtherConst>& __y)
        {
            return __x.__end_ != __y.__current_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst)
        CANN_ASC_STL_DETAIL_REQUIRES(
            (sized_sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr range_difference_t<__maybe_const<_OtherConst, _View>> operator-(
            const __iterator<_OtherConst>& __x, const __sentinel& __y)
        {
            return __x.__current_ - __y.__end_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(bool _OtherConst)
        CANN_ASC_STL_DETAIL_REQUIRES(
            (sized_sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>))
        CANN_ASC_STL_API friend constexpr range_difference_t<__maybe_const<_OtherConst, _View>> operator-(
            const __sentinel& __x, const __iterator<_OtherConst>& __y)
        {
            return __x.__end_ - __y.__current_;
        }
    };

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    transform_view()
        requires default_initializable<_View> && default_initializable<_Fn>
    = default;
#else
    template <bool __asc_enabled = true,
        enable_if_t<__asc_enabled && (default_initializable<_View> && default_initializable<_Fn>), int> = 0>
    CANN_ASC_STL_API constexpr transform_view()
    {}
#endif

    CANN_ASC_STL_API constexpr transform_view(_View __base, _Fn __func)
        : view_interface<transform_view<_View, _Fn>>(),
          __base_(::asc::std::move(__base)),
          __func_(in_place_t{}, ::asc::std::move(__func))
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

    CANN_ASC_STL_API constexpr __iterator<false> begin()
    {
        return __iterator<false>{*this, ::asc::std::ranges::__begin_cpo{}(__base_)};
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((range<const _View2> && __regular_invocable_with_range_ref<const _Fn&, const _View2>))
    CANN_ASC_STL_API constexpr __iterator<true> begin() const
    {
        return __iterator<true>(*this, ::asc::std::ranges::__begin_cpo{}(__base_));
    }

    CANN_ASC_STL_API constexpr auto end()
    {
        if constexpr (common_range<_View>) {
            return __iterator<false>(*this, ::asc::std::ranges::__end_cpo{}(__base_));
        } else {
            return __sentinel<false>(::asc::std::ranges::__end_cpo{}(__base_));
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((range<const _View2> && __regular_invocable_with_range_ref<const _Fn&, const _View2>))
    CANN_ASC_STL_API constexpr auto end() const
    {
        if constexpr (common_range<const _View>) {
            return __iterator<true>(*this, ::asc::std::ranges::__end_cpo{}(__base_));
        } else {
            return __sentinel<true>(::asc::std::ranges::__end_cpo{}(__base_));
        }
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<_View2>))
    CANN_ASC_STL_API constexpr auto size()
    {
        return ::asc::std::ranges::__size_cpo{}(__base_);
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((sized_range<const _View2>))
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::ranges::__size_cpo{}(__base_);
    }
};

template <class _Range, class _Fn>
CANN_ASC_STL_HOST_DEVICE transform_view(_Range&&, _Fn) -> transform_view<::asc::std::ranges::views::all_t<_Range>, _Fn>;

namespace views {

template <class Function>
class __transform_closure : public range_adaptor_closure<__transform_closure<Function>> {
public:
    CANN_ASC_STL_API constexpr explicit __transform_closure(Function value) : function_(::asc::std::move(value))
    {}
    CANN_ASC_STL_DETAIL_TEMPLATE(class Range, class View = all_t<Range>)
    CANN_ASC_STL_DETAIL_REQUIRES(input_range<View>&& move_constructible<Function>&&
            __transform_view_constraints<View, Function>&& convertible_to<const Function&, Function>)
    CANN_ASC_STL_API constexpr auto operator()(Range&& range) const -> transform_view<View, Function>
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return transform_view<decltype(view), Function>(::asc::std::move(view), function_);
    }

private:
    Function function_;
};

struct __transform_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class Range, class Function, class View = all_t<Range>)
    CANN_ASC_STL_DETAIL_REQUIRES(
        input_range<View>&& move_constructible<Function>&& __transform_view_constraints<View, Function>)
    CANN_ASC_STL_API constexpr auto operator()(Range&& range, Function function) const -> transform_view<View, Function>
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return transform_view<decltype(view), Function>(::asc::std::move(view), ::asc::std::move(function));
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class Function)
    CANN_ASC_STL_DETAIL_REQUIRES(is_object_v<Function>&& move_constructible<Function>)
    CANN_ASC_STL_API constexpr auto operator()(Function function) const
    {
        return __transform_closure<Function>(::asc::std::move(function));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __transform_fn transform{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_TRANSFORM_VIEW_H
