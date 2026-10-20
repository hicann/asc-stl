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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_FILTER_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_FILTER_VIEW_H

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
#include <asc/std/__algorithm/ranges_find_if.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/reference_wrapper.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/non_propagating_cache.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_comparable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
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

template <class _View, bool = forward_range<_View>>
struct __filter_iterator_category {
    // A non-forward underlying iterator has no computable category, so present as an
    // input iterator (this library's traits extraction requires the category member
    // to exist).
    using iterator_category = input_iterator_tag;
};

template <class _View>
struct __filter_iterator_category<_View, true> {
    using category = typename iterator_traits<iterator_t<_View>>::iterator_category;
    using iterator_category =
        conditional_t<derived_from<category, bidirectional_iterator_tag>, bidirectional_iterator_tag,
            conditional_t<derived_from<category, forward_iterator_tag>, forward_iterator_tag,
                /* else */ category>>;
};

template <class _Iter, class = void>
inline constexpr bool __filter_member_has_arrow = false;
template <class _Iter>
inline constexpr bool __filter_member_has_arrow<_Iter, void_t<decltype(::asc::std::declval<_Iter&>().operator->())>> =
    true;
template <class _Iter>
inline constexpr bool __filter_iterator_has_arrow =
    input_iterator<_Iter> && (is_pointer_v<_Iter> || __filter_member_has_arrow<_Iter>);

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <input_range _View, indirect_unary_predicate<iterator_t<_View>> _Pred>
    requires view<_View> && is_object_v<_Pred>
#else
template <class _View, class _Pred>
#endif
class filter_view : public view_interface<filter_view<_View, _Pred>> {
    static_assert(
        input_range<_View> && indirect_unary_predicate<_Pred, iterator_t<_View>> && (view<_View> && is_object_v<_Pred>),
        "range view constraints are not satisfied");

    _View __base_;
    __movable_box<_Pred> __pred_;

    // begin() result cache: provides an amortized O(1) begin() when the underlying
    // range is at least a forward_range.
    static constexpr bool __use_cache = forward_range<_View>;
    using _cache_type = conditional_t<__use_cache, __non_propagating_cache<iterator_t<_View>>, __empty_cache>;
    _cache_type __cached_begin_;

public:
    class __iterator : public __filter_iterator_category<_View> {
    public:
        iterator_t<_View> __current_;
        filter_view* __parent_ = nullptr;

        using iterator_concept = conditional_t<bidirectional_range<_View>, bidirectional_iterator_tag,
            conditional_t<forward_range<_View>, forward_iterator_tag,
                /* else */ input_iterator_tag>>;

        using value_type = range_value_t<_View>;
        using difference_type = range_difference_t<_View>;
        using pointer = void;
        using reference = range_reference_t<_View>;

        CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
        CANN_ASC_STL_DETAIL_REQUIRES((default_initializable<iterator_t<_View2>>))
        CANN_ASC_STL_API constexpr __iterator() noexcept(is_nothrow_default_constructible_v<iterator_t<_View2>>)
            : __current_()
        {}

        CANN_ASC_STL_API constexpr __iterator(filter_view& __parent, iterator_t<_View> __current) noexcept(
            is_nothrow_move_constructible_v<iterator_t<_View>>)
            : __current_{::asc::std::move(__current)}, __parent_{::asc::std::addressof(__parent)}
        {}

        CANN_ASC_STL_API constexpr const iterator_t<_View>& base() const& noexcept
        {
            return __current_;
        }

        CANN_ASC_STL_API constexpr iterator_t<_View> base() && noexcept(
            is_nothrow_move_constructible_v<iterator_t<_View>>)
        {
            return ::asc::std::move(__current_);
        }

        CANN_ASC_STL_API constexpr range_reference_t<_View> operator*() const
            noexcept(is_nothrow_constructible_v<range_reference_t<_View>, decltype(*__current_)>)
        {
            return *__current_;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
        CANN_ASC_STL_DETAIL_REQUIRES((__filter_iterator_has_arrow<iterator_t<_View2>> && copyable<iterator_t<_View2>>))
        CANN_ASC_STL_API constexpr iterator_t<_View> operator->() const
            noexcept(is_nothrow_copy_constructible_v<iterator_t<_View2>>)
        {
            return __current_;
        }

        CANN_ASC_STL_API constexpr __iterator& operator++()
        {
            __current_ = ::asc::std::ranges::find_if(::asc::std::move(++__current_),
                ::asc::std::ranges::__end_cpo{}(__parent_->__base_), ::asc::std::ref(*__parent_->__pred_));
            return *this;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
        CANN_ASC_STL_DETAIL_REQUIRES(((!forward_range<_View2>)))
        CANN_ASC_STL_API constexpr void operator++(int)
        {
            ++*this;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
        CANN_ASC_STL_DETAIL_REQUIRES((forward_range<_View2>))
        CANN_ASC_STL_API constexpr __iterator operator++(int)
        {
            auto __tmp = *this;
            ++*this;
            return __tmp;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
        CANN_ASC_STL_DETAIL_REQUIRES((bidirectional_range<_View2>))
        CANN_ASC_STL_API constexpr __iterator& operator--()
        {
            do {
                --__current_;
            } while (!::asc::std::invoke(*__parent_->__pred_, *__current_));
            return *this;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
        CANN_ASC_STL_DETAIL_REQUIRES((bidirectional_range<_View2>))
        CANN_ASC_STL_API constexpr __iterator operator--(int)
        {
            auto __tmp = *this;
            --*this;
            return __tmp;
        }

        CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
        CANN_ASC_STL_DETAIL_REQUIRES((equality_comparable<iterator_t<_View2>>))
        CANN_ASC_STL_API friend constexpr bool operator==(const __iterator& __x, const __iterator& __y) noexcept(
            __is_cpp17_nothrow_equality_comparable_v<iterator_t<_View>, iterator_t<_View>>)
        {
            return __x.__current_ == __y.__current_;
        }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
        CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
        CANN_ASC_STL_DETAIL_REQUIRES(equality_comparable<iterator_t<_View2>>)
        CANN_ASC_STL_API friend constexpr bool operator!=(const __iterator& __x, const __iterator& __y)
        {
            return !(__x == __y);
        }
#endif

#if defined(__cpp_impl_three_way_comparison) && __cpp_impl_three_way_comparison >= 201907L
        CANN_ASC_STL_API friend constexpr auto operator<=>(const __iterator& __x, const __iterator& __y) noexcept(
            noexcept(__x.__current_ <=> __y.__current_))
        {
            return __x.__current_ <=> __y.__current_;
        }
#endif

        CANN_ASC_STL_API friend constexpr range_rvalue_reference_t<_View> iter_move(const __iterator& __it) noexcept(
            noexcept(::asc::std::iter_move(__it.__current_)))
        {
            return ::asc::std::iter_move(__it.__current_);
        }

        // iter_swap dispatches through the namespace-level CPO default path (which
        // swaps the underlying iterators); a hidden-friend form would clash with the
        // CPO variable name (as with reverse_iterator).
    };

    class __sentinel {
    public:
        sentinel_t<_View> __end_{};

        constexpr __sentinel() = default;

        CANN_ASC_STL_API constexpr explicit __sentinel(filter_view& __parent)
            : __end_{::asc::std::ranges::__end_cpo{}(__parent.__base_)}
        {}

        CANN_ASC_STL_API constexpr sentinel_t<_View> base() const
            noexcept(is_nothrow_copy_constructible_v<sentinel_t<_View>>)
        {
            return __end_;
        }

        CANN_ASC_STL_API friend constexpr bool operator==(const __iterator& __x, const __sentinel& __y) noexcept(
            __is_cpp17_nothrow_equality_comparable_v<iterator_t<_View>, sentinel_t<_View>>)
        {
            return __x.__current_ == __y.__end_;
        }

#if !CANN_ASC_STL_DETAIL_HAS_CXX20()
        CANN_ASC_STL_API friend constexpr bool operator==(const __sentinel& __x, const __iterator& __y)
        {
            return __y == __x;
        }
        CANN_ASC_STL_API friend constexpr bool operator!=(const __iterator& __x, const __sentinel& __y)
        {
            return !(__x == __y);
        }
        CANN_ASC_STL_API friend constexpr bool operator!=(const __sentinel& __x, const __iterator& __y)
        {
            return !(__y == __x);
        }
#endif
    };

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View, class _Pred2 = _Pred)
    CANN_ASC_STL_DETAIL_REQUIRES((default_initializable<_View2> && default_initializable<_Pred2>))
    CANN_ASC_STL_API constexpr filter_view() noexcept(
        is_nothrow_default_constructible_v<_View2> && is_nothrow_default_constructible_v<_Pred2>)
        : view_interface<filter_view<_View, _Pred>>{}, __base_(), __pred_(), __cached_begin_()
    {}

    CANN_ASC_STL_API constexpr explicit filter_view(_View __base, _Pred __pred) noexcept(
        is_nothrow_move_constructible_v<_View> &&
        is_nothrow_constructible_v<__movable_box<_Pred>, in_place_t, add_rvalue_reference_t<_Pred>>)
        : __base_{::asc::std::move(__base)}, __pred_{in_place_t{}, ::asc::std::move(__pred)}
    {}

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

    CANN_ASC_STL_API constexpr const _Pred& pred() const noexcept
    {
        return *__pred_;
    }

    CANN_ASC_STL_API constexpr __iterator begin()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __pred_.__has_value(), "filter_view needs to have a valid predicate before calling begin()");

        if constexpr (__use_cache) {
            if (!__cached_begin_.__has_value()) {
                __cached_begin_.__emplace(::asc::std::ranges::find_if(__base_, ::asc::std::ref(*__pred_)));
            }
            return {*this, *__cached_begin_};
        } else {
            return {*this, ::asc::std::ranges::find_if(__base_, ::asc::std::ref(*__pred_))};
        }
    }

    CANN_ASC_STL_API constexpr auto end()
    {
        if constexpr (common_range<_View>) {
            return __iterator{*this, ::asc::std::ranges::__end_cpo{}(__base_)};
        } else {
            return __sentinel{*this};
        }
    }
};

template <class _Range, class _Pred>
CANN_ASC_STL_HOST_DEVICE filter_view(_Range&&, _Pred) -> filter_view<ranges::views::all_t<_Range>, _Pred>;

namespace views {

template <class Predicate>
class __filter_closure : public range_adaptor_closure<__filter_closure<Predicate>> {
public:
    CANN_ASC_STL_API constexpr explicit __filter_closure(Predicate value) : predicate_(::asc::std::move(value))
    {}
    CANN_ASC_STL_DETAIL_TEMPLATE(class Range, class View = all_t<Range>)
    CANN_ASC_STL_DETAIL_REQUIRES(input_range<View>&& view<View>&& is_object_v<Predicate>&&
            indirect_unary_predicate<Predicate, iterator_t<View>>&& constructible_from<Predicate, const Predicate&>)
    CANN_ASC_STL_API constexpr auto operator()(Range&& range) const -> filter_view<View, Predicate>
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return filter_view<decltype(view), Predicate>(::asc::std::move(view), predicate_);
    }

private:
    Predicate predicate_;
};

struct __filter_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class Range, class Predicate, class View = all_t<Range>)
    CANN_ASC_STL_DETAIL_REQUIRES(
        input_range<View>&& view<View>&& is_object_v<Predicate>&& indirect_unary_predicate<Predicate, iterator_t<View>>)
    CANN_ASC_STL_API constexpr auto operator()(Range&& range, Predicate predicate) const -> filter_view<View, Predicate>
    {
        auto view = views::all(::asc::std::forward<Range>(range));
        return filter_view<decltype(view), Predicate>(::asc::std::move(view), ::asc::std::move(predicate));
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class Predicate)
    CANN_ASC_STL_DETAIL_REQUIRES(is_object_v<Predicate>&& move_constructible<Predicate>)
    CANN_ASC_STL_API constexpr auto operator()(Predicate predicate) const
    {
        return __filter_closure<Predicate>(::asc::std::move(predicate));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __filter_fn filter{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_FILTER_VIEW_H
