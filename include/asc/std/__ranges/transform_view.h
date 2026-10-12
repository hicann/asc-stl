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
// 设备编译下 concept 约束求值不可用（纯 SIMT 后端），回退到弱约束版本，两分支公开接口一致。
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class _Fn, class _View>
concept __regular_invocable_with_range_ref = regular_invocable<_Fn, range_reference_t<_View>>;

template <class _View, class _Fn>
concept __transform_view_constraints =
    view<_View> && is_object_v<_Fn> && regular_invocable<_Fn&, range_reference_t<_View>> &&
    __can_reference<invoke_result_t<_Fn&, range_reference_t<_View>>>;

template <class, class, class = void>
struct __transform_view_iterator_category_base {
    // 非 forward 底层无类别可算，按 input 迭代器呈现（本库 traits 抽取要求类别成员存在）。
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

template <input_range _View, move_constructible _Fn>
    requires __transform_view_constraints<_View, _Fn>
class transform_view : public view_interface<transform_view<_View, _Fn>> {
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

        __iterator()
            requires default_initializable<iterator_t<_Base>>
        = default;

        CANN_ASC_STL_API constexpr __iterator(_Parent& __parent, iterator_t<_Base> __current)
            : __parent_(::asc::std::addressof(__parent)), __current_(::asc::std::move(__current))
        {}

        // 注：__i 恒为 __iterator<false>，但在 _Const 为 false 时直接写
        // __iterator<false> 非法（class.copy.ctor#5），故经 _OtherConst 中转。
        template <bool _OtherConst = _Const>
            requires(_OtherConst && convertible_to<iterator_t<_View>, iterator_t<_Base>>)
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

        template <class _Base2 = _Base>
            requires(!forward_range<_Base2>)
        CANN_ASC_STL_API constexpr void operator++(int)
        {
            ++__current_;
        }

        template <class _Base2 = _Base>
            requires forward_range<_Base2>
        CANN_ASC_STL_API constexpr __iterator operator++(int)
        {
            auto __tmp = *this;
            ++*this;
            return __tmp;
        }

        template <class _Base2 = _Base>
            requires bidirectional_range<_Base2>
        CANN_ASC_STL_API constexpr __iterator& operator--()
        {
            --__current_;
            return *this;
        }

        template <class _Base2 = _Base>
            requires bidirectional_range<_Base2>
        CANN_ASC_STL_API constexpr __iterator operator--(int)
        {
            auto __tmp = *this;
            --*this;
            return __tmp;
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API constexpr __iterator& operator+=(difference_type __n)
        {
            __current_ += __n;
            return *this;
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API constexpr __iterator& operator-=(difference_type __n)
        {
            __current_ -= __n;
            return *this;
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API constexpr decltype(auto) operator[](difference_type __n) const
            noexcept(__nothrow_subscript<_Fn, _Base2>)
        {
            return ::asc::std::invoke(*__parent_->__func_, __current_[__n]);
        }

        template <class _Base2 = _Base>
            requires equality_comparable<iterator_t<_Base2>>
        CANN_ASC_STL_API friend constexpr bool operator==(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ == __y.__current_;
        }
        // C++17 源头的 operator!= 双侧保留：C++20 下显式候选与改写语义一致。
        template <class _Base2 = _Base>
            requires equality_comparable<iterator_t<_Base2>>
        CANN_ASC_STL_API friend constexpr bool operator!=(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ != __y.__current_;
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API friend constexpr bool operator<(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ < __y.__current_;
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API friend constexpr bool operator>(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ > __y.__current_;
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API friend constexpr bool operator<=(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ <= __y.__current_;
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API friend constexpr bool operator>=(const __iterator& __x, const __iterator& __y)
        {
            return __x.__current_ >= __y.__current_;
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API friend constexpr __iterator operator+(__iterator __i, difference_type __n)
        {
            return __iterator{*__i.__parent_, __i.__current_ + __n};
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API friend constexpr __iterator operator+(difference_type __n, __iterator __i)
        {
            return __iterator{*__i.__parent_, __i.__current_ + __n};
        }

        template <class _Base2 = _Base>
            requires random_access_range<_Base2>
        CANN_ASC_STL_API friend constexpr __iterator operator-(__iterator __i, difference_type __n)
        {
            return __iterator{*__i.__parent_, __i.__current_ - __n};
        }

        template <class _Base2 = _Base>
            requires sized_sentinel_for<iterator_t<_Base2>, iterator_t<_Base2>>
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

        // 注：__i 恒为 __sentinel<false>，但在 _Const 为 false 时直接写
        // __sentinel<false> 非法（class.copy.ctor#5），故经 _OtherConst 中转。
        template <bool _OtherConst = _Const>
            requires(_OtherConst && convertible_to<sentinel_t<_View>, sentinel_t<_Base>>)
        CANN_ASC_STL_API constexpr __sentinel(__sentinel<!_OtherConst> __i) : __end_(::asc::std::move(__i.__end_))
        {}

        CANN_ASC_STL_API constexpr sentinel_t<_Base> base() const
        {
            return __end_;
        }

        template <bool _OtherConst>
            requires sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>
        CANN_ASC_STL_API friend constexpr bool operator==(const __iterator<_OtherConst>& __x, const __sentinel& __y)
        {
            return __x.__current_ == __y.__end_;
        }
        // C++17 源头的反序 ==/!= 双侧保留：C++20 下显式候选与改写语义一致。
        template <bool _OtherConst>
            requires sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>
        CANN_ASC_STL_API friend constexpr bool operator==(const __sentinel& __x, const __iterator<_OtherConst>& __y)
        {
            return __x.__end_ == __y.__current_;
        }

        template <bool _OtherConst>
            requires sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>
        CANN_ASC_STL_API friend constexpr bool operator!=(const __iterator<_OtherConst>& __x, const __sentinel& __y)
        {
            return __x.__current_ != __y.__end_;
        }

        template <bool _OtherConst>
            requires sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>
        CANN_ASC_STL_API friend constexpr bool operator!=(const __sentinel& __x, const __iterator<_OtherConst>& __y)
        {
            return __x.__end_ != __y.__current_;
        }

        template <bool _OtherConst>
            requires sized_sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>
        CANN_ASC_STL_API friend constexpr range_difference_t<__maybe_const<_OtherConst, _View>> operator-(
            const __iterator<_OtherConst>& __x, const __sentinel& __y)
        {
            return __x.__current_ - __y.__end_;
        }

        template <bool _OtherConst>
            requires sized_sentinel_for<sentinel_t<_Base>, iterator_t<__maybe_const<_OtherConst, _View>>>
        CANN_ASC_STL_API friend constexpr range_difference_t<__maybe_const<_OtherConst, _View>> operator-(
            const __sentinel& __x, const __iterator<_OtherConst>& __y)
        {
            return __x.__end_ - __y.__current_;
        }
    };

    transform_view()
        requires default_initializable<_View> && default_initializable<_Fn>
    = default;

    CANN_ASC_STL_API constexpr transform_view(_View __base, _Fn __func)
        : view_interface<transform_view<_View, _Fn>>(),
          __base_(::asc::std::move(__base)),
          __func_(in_place_t{}, ::asc::std::move(__func))
    {}

    template <class _View2 = _View>
        requires copy_constructible<_View2>
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
    template <class _View2 = _View>
        requires range<const _View2> && __regular_invocable_with_range_ref<const _Fn&, const _View2>
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

    template <class _View2 = _View>
        requires range<const _View2> && __regular_invocable_with_range_ref<const _Fn&, const _View2>
    CANN_ASC_STL_API constexpr auto end() const
    {
        if constexpr (common_range<const _View>) {
            return __iterator<true>(*this, ::asc::std::ranges::__end_cpo{}(__base_));
        } else {
            return __sentinel<true>(::asc::std::ranges::__end_cpo{}(__base_));
        }
    }

    template <class _View2 = _View>
        requires sized_range<_View2>
    CANN_ASC_STL_API constexpr auto size()
    {
        return ::asc::std::ranges::__size_cpo{}(__base_);
    }
    template <class _View2 = _View>
        requires sized_range<const _View2>
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::ranges::__size_cpo{}(__base_);
    }
};

#else

template <class View, class Function>
class transform_view : public view_interface<transform_view<View, Function>> {
    using base_iterator = iterator_t<View>;
    using base_sentinel = sentinel_t<View>;
    class iterator {
    public:
        using difference_type = iter_difference_t<base_iterator>;
        using value_type =
            remove_cvref_t<decltype(::asc::std::declval<const Function&>()(*::asc::std::declval<base_iterator&>()))>;
        using pointer = void;
        using reference = decltype(::asc::std::declval<const Function&>()(*::asc::std::declval<base_iterator&>()));
        using iterator_category = input_iterator_tag;

        CANN_ASC_STL_API constexpr iterator(base_iterator current, const Function* function)
            : current_(current), function_(function)
        {}
        CANN_ASC_STL_API constexpr decltype(auto) operator*() const
        {
            return (*function_)(*current_);
        }
        CANN_ASC_STL_API constexpr iterator& operator++()
        {
            ++current_;
            return *this;
        }
        CANN_ASC_STL_API constexpr void operator++(int)
        {
            ++*this;
        }
        CANN_ASC_STL_API constexpr const base_iterator& base() const noexcept
        {
            return current_;
        }
        friend CANN_ASC_STL_API constexpr bool operator==(const iterator& left, const iterator& right)
        {
            return left.current_ == right.current_;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(const iterator& left, const iterator& right)
        {
            return !(left == right);
        }

    private:
        base_iterator current_;
        const Function* function_;
    };
    class sentinel {
    public:
        CANN_ASC_STL_API constexpr explicit sentinel(base_sentinel last) : last_(last)
        {}
        friend CANN_ASC_STL_API constexpr bool operator==(const iterator& value, const sentinel& last)
        {
            return value.base() == last.last_;
        }
        friend CANN_ASC_STL_API constexpr bool operator==(const sentinel& last, const iterator& value)
        {
            return value == last;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(const iterator& value, const sentinel& last)
        {
            return !(value == last);
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(const sentinel& last, const iterator& value)
        {
            return !(last == value);
        }

    private:
        base_sentinel last_;
    };

public:
    CANN_ASC_STL_API constexpr transform_view() = default;
    CANN_ASC_STL_API constexpr transform_view(View view, Function function)
        : view_(::asc::std::move(view)), function_(::asc::std::move(function))
    {}
    CANN_ASC_STL_API constexpr iterator begin()
    {
        return {ranges::begin(view_), &function_};
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr iterator begin() const
    {
        return {ranges::begin(view_), &function_};
    }
    CANN_ASC_STL_API constexpr sentinel end()
    {
        return sentinel(ranges::end(view_));
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr sentinel end() const
    {
        return sentinel(ranges::end(view_));
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto size()
    {
        return ranges::size(view_);
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ranges::size(view_);
    }
    template <class View2 = View>
    CANN_ASC_STL_API constexpr View base() const&
    {
        return view_;
    }
    CANN_ASC_STL_API constexpr View base() &&
    {
        return ::asc::std::move(view_);
    }

private:
    View view_{};
    Function function_{};
};

#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class _Range, class _Fn>
transform_view(_Range&&, _Fn) -> transform_view<::asc::std::ranges::views::all_t<_Range>, _Fn>;

namespace views {

template <class Function>
class __transform_closure : public range_adaptor_closure<__transform_closure<Function>> {
public:
    CANN_ASC_STL_API constexpr explicit __transform_closure(Function value) : function_(::asc::std::move(value))
    {}
    template <class Range>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return transform_view<decltype(view), Function>(::asc::std::move(view), function_);
    }

private:
    Function function_;
};

struct __transform_fn {
    template <class Range, class Function>
    CANN_ASC_STL_API constexpr auto operator()(Range&& range, Function function) const
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return transform_view<decltype(view), Function>(::asc::std::move(view), ::asc::std::move(function));
    }
    template <class Function>
    CANN_ASC_STL_API constexpr auto operator()(Function function) const
    {
        return __transform_closure<Function>(::asc::std::move(function));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __transform_fn transform{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_TRANSFORM_VIEW_H
