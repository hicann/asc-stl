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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_DROP_WHILE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_DROP_WHILE_VIEW_H

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
#include <asc/__detail/execution_space.h>
#include <asc/std/__algorithm/ranges_find_if_not.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__functional/reference_wrapper.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/non_propagating_cache.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_object.h>
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

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// Both language modes and execution spaces share the same view semantics.
// The shared constraints select native concepts or SFINAE as appropriate.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <view _View, class _Pred>
    requires input_range<_View> && ::asc::std::is_object_v<_Pred> &&
    ::asc::std::indirect_unary_predicate<const _Pred, iterator_t<_View>>
#else
template <class _View, class _Pred>
#endif
class drop_while_view : public view_interface<drop_while_view<_View, _Pred>> {
    static_assert(view<_View> &&
            (input_range<_View> && ::asc::std::is_object_v<_Pred> &&
                ::asc::std::indirect_unary_predicate<const _Pred, iterator_t<_View>>),
        "range view constraints are not satisfied");

private:
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _View __base_ = _View();

    CANN_ASC_STL_NO_UNIQUE_ADDRESS __movable_box<_Pred> __pred_{};

    // For a forward_range, cache the first iterator that fails the predicate, giving
    // an amortized O(1) begin(); for an input_range, begin() is not equality-preserving
    // and must not be cached (a single pass calls begin() only once anyway).
    static constexpr bool _use_cache = forward_range<_View>;
    using _cache_type =
        ::asc::std::conditional_t<_use_cache, __non_propagating_cache<iterator_t<_View>>, __empty_cache>;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _cache_type __cached_begin_{};

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr drop_while_view()
        requires ::asc::std::default_initializable<_View> && ::asc::std::default_initializable<_Pred>
    = default;
#else
    template <bool __asc_enabled = true,
        enable_if_t<__asc_enabled &&
                (::asc::std::default_initializable<_View> && ::asc::std::default_initializable<_Pred>),
            int> = 0>
    CANN_ASC_STL_API constexpr drop_while_view()
    {}
#endif

    CANN_ASC_STL_API constexpr drop_while_view(_View __base, _Pred __pred)
        : view_interface<drop_while_view<_View, _Pred>>(),
          __base_(::asc::std::move(__base)),
          __pred_(in_place_t{}, ::asc::std::move(__pred))
    {}

    CANN_ASC_STL_DETAIL_TEMPLATE(class _View2 = _View)
    CANN_ASC_STL_DETAIL_REQUIRES((::asc::std::copy_constructible<_View2>))
    CANN_ASC_STL_API constexpr _View base() const& noexcept(::asc::std::is_nothrow_copy_constructible_v<_View2>)
    {
        return __base_;
    }

    CANN_ASC_STL_API constexpr _View base() && noexcept(::asc::std::is_nothrow_move_constructible_v<_View>)
    {
        return ::asc::std::move(__base_);
    }

    CANN_ASC_STL_API constexpr const _Pred& pred() const
    {
        return *__pred_;
    }

    CANN_ASC_STL_API constexpr auto begin()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __pred_.__has_value(), "drop_while_view needs to have a valid predicate before calling begin()");

        if constexpr (_use_cache) {
            if (!__cached_begin_.__has_value()) {
                __cached_begin_.__emplace(::asc::std::ranges::find_if_not(__base_, ::asc::std::cref(*__pred_)));
            }
            return *__cached_begin_;
        } else {
            return ::asc::std::ranges::find_if_not(__base_, ::asc::std::cref(*__pred_));
        }
    }

    CANN_ASC_STL_API constexpr auto end()
    {
        return ::asc::std::ranges::__end_cpo{}(__base_);
    }
};

template <class _Range, class _Pred>
CANN_ASC_STL_HOST_DEVICE drop_while_view(
    _Range&&, _Pred) -> drop_while_view<::asc::std::ranges::views::all_t<_Range>, _Pred>;

template <class _Tp, class _Pred>
inline constexpr bool enable_borrowed_range<drop_while_view<_Tp, _Pred>> = enable_borrowed_range<_Tp>;

}  // namespace ranges

namespace ranges::views {

namespace __drop_while {

struct __fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class _Range, class _Pred, class _View = all_t<_Range>)
    CANN_ASC_STL_DETAIL_REQUIRES(
        input_range<_View>&& is_object_v<decay_t<_Pred>>&& indirect_unary_predicate<const decay_t<_Pred>,
            iterator_t<_View>>&& constructible_from<decay_t<_Pred>, _Pred>)
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range, _Pred&& __pred) const
        noexcept(noexcept(drop_while_view{::asc::std::forward<_Range>(__range), ::asc::std::forward<_Pred>(__pred)}))
            -> decltype(drop_while_view{::asc::std::forward<_Range>(__range), ::asc::std::forward<_Pred>(__pred)})
    {
        return drop_while_view{::asc::std::forward<_Range>(__range), ::asc::std::forward<_Pred>(__pred)};
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

}  // namespace __drop_while

inline constexpr __drop_while::__fn drop_while{};

}  // namespace ranges::views

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_DROP_WHILE_VIEW_H
