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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_REVERSE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_REVERSE_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/non_propagating_cache.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__ranges/subrange.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <view _View>
    requires bidirectional_range<_View>
#else
template <class _View>
#endif
class reverse_view : public view_interface<reverse_view<_View>> {
private:
    // Minimal inline equivalent of the iterator-sentinel form of next: advance to
    // the sentinel and return it (stays constexpr and usable on the device side).
    template <class _Iterator, class _Sentinel>
    static CANN_ASC_STL_API constexpr _Iterator __advance_to_sentinel(_Iterator __iterator, _Sentinel __last)
    {
        while (__iterator != __last) {
            ++__iterator;
        }
        return __iterator;
    }

    // We cache begin() whenever advancing to the end is not guaranteed O(1) to provide an
    // amortized O(1) begin() method.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    static constexpr bool _UseCache = !random_access_range<_View> && !common_range<_View>;
    using _Cache =
        conditional_t<_UseCache, __non_propagating_cache<reverse_iterator<iterator_t<_View>>>, __empty_cache>;
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Cache __cached_begin_ = _Cache();
#endif
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _View __base_ = _View();

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr reverse_view()
        requires ::asc::std::default_initializable<_View>
    = default;
#else
    CANN_ASC_STL_API constexpr reverse_view() = default;
#endif

    CANN_ASC_STL_API constexpr explicit reverse_view(_View __view) : __base_(::asc::std::move(__view))
    {}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class _View2 = _View>
        requires ::asc::std::copy_constructible<_View2>
    CANN_ASC_STL_API constexpr _View base() const& noexcept(::asc::std::is_nothrow_copy_constructible_v<_View>)
    {
        return __base_;
    }

    CANN_ASC_STL_API constexpr _View base() && noexcept(::asc::std::is_nothrow_move_constructible_v<_View>)
    {
        return ::asc::std::move(__base_);
    }

    template <class _View2 = _View>
        requires(!common_range<_View2>)
    CANN_ASC_STL_API constexpr reverse_iterator<iterator_t<_View2>> begin()
    {
        if constexpr (_UseCache) {
            if (__cached_begin_.__has_value()) {
                return *__cached_begin_;
            }
        }

        auto __tmp = ::asc::std::make_reverse_iterator(__advance_to_sentinel(
            ::asc::std::ranges::__begin_cpo{}(__base_), ::asc::std::ranges::__end_cpo{}(__base_)));
        if constexpr (_UseCache) {
            __cached_begin_.__emplace(__tmp);
        }
        return __tmp;
    }

    template <class _View2 = _View>
        requires common_range<_View2>
    CANN_ASC_STL_API constexpr reverse_iterator<iterator_t<_View2>> begin()
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__end_cpo{}(__base_));
    }

    template <class _View2 = _View>
        requires common_range<const _View2>
    CANN_ASC_STL_API constexpr auto begin() const
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__end_cpo{}(__base_));
    }

    CANN_ASC_STL_API constexpr reverse_iterator<iterator_t<_View>> end()
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__begin_cpo{}(__base_));
    }

    template <class _View2 = _View>
        requires common_range<const _View2>
    CANN_ASC_STL_API constexpr auto end() const
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__begin_cpo{}(__base_));
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
#else
    // C++17 and device-side shape: constraints are not evaluable (no concept
    // fallback), so the members are unconstrained and begin() keeps only the
    // common-range form.
    CANN_ASC_STL_API constexpr _View base() const& noexcept(::asc::std::is_nothrow_copy_constructible_v<_View>)
    {
        return __base_;
    }

    CANN_ASC_STL_API constexpr _View base() && noexcept(::asc::std::is_nothrow_move_constructible_v<_View>)
    {
        return ::asc::std::move(__base_);
    }

    CANN_ASC_STL_API constexpr auto begin()
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__end_cpo{}(__base_));
    }

    CANN_ASC_STL_API constexpr auto begin() const
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__end_cpo{}(__base_));
    }

    CANN_ASC_STL_API constexpr auto end()
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__begin_cpo{}(__base_));
    }

    CANN_ASC_STL_API constexpr auto end() const
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__begin_cpo{}(__base_));
    }

    CANN_ASC_STL_API constexpr auto size()
    {
        return ::asc::std::ranges::__size_cpo{}(__base_);
    }

    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::ranges::__size_cpo{}(__base_);
    }
#endif
};

template <class _Range>
reverse_view(_Range&&) -> reverse_view<::asc::std::ranges::views::all_t<_Range>>;

template <class _Tp>
inline constexpr bool enable_borrowed_range<reverse_view<_Tp>> = enable_borrowed_range<_Tp>;

}  // namespace ranges

namespace ranges::views {

namespace __reverse {

template <class _Tp>
inline constexpr bool __is_reverse_view = false;

template <class _Tp>
inline constexpr bool __is_reverse_view<reverse_view<_Tp>> = true;

template <class _Tp>
inline constexpr bool __is_sized_reverse_subrange = false;

template <class _Iter>
inline constexpr bool __is_sized_reverse_subrange<::asc::std::ranges::subrange<reverse_iterator<_Iter>,
    reverse_iterator<_Iter>, ::asc::std::ranges::subrange_kind::sized>> = true;

template <class _Tp>
inline constexpr bool __is_unsized_reverse_subrange = false;

template <class _Iter, ::asc::std::ranges::subrange_kind _Kind>
inline constexpr bool __is_unsized_reverse_subrange<
    ::asc::std::ranges::subrange<reverse_iterator<_Iter>, reverse_iterator<_Iter>, _Kind>> =
    _Kind == ::asc::std::ranges::subrange_kind::unsized;

template <class _Tp>
struct __unwrapped_reverse_subrange {
    using type = void;  // avoid SFINAE-ing out the overload below -- let the concept requirements do it for better
                        // diagnostics
};

template <class _Iter, ::asc::std::ranges::subrange_kind _Kind>
struct __unwrapped_reverse_subrange<
    ::asc::std::ranges::subrange<reverse_iterator<_Iter>, reverse_iterator<_Iter>, _Kind>> {
    using type = ::asc::std::ranges::subrange<_Iter, _Iter, _Kind>;
};

template <class _Tp>
using __unwrapped_reverse_subrange_t = typename __unwrapped_reverse_subrange<_Tp>::type;

struct __fn : __range_adaptor_closure<__fn> {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class _Range>
        requires __is_reverse_view<remove_cvref_t<_Range>>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Range&& __range) const noexcept(
        noexcept(::asc::std::forward<_Range>(__range).base())) -> decltype(::asc::std::forward<_Range>(__range).base())
    {
        return ::asc::std::forward<_Range>(__range).base();
    }

    template <class _Range, class _UnwrappedSubrange = __unwrapped_reverse_subrange_t<remove_cvref_t<_Range>>>
        requires __is_sized_reverse_subrange<remove_cvref_t<_Range>>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Range&& __range) const noexcept(noexcept(
        _UnwrappedSubrange(__range.end().base(), __range.begin().base(), __range.size()))) -> _UnwrappedSubrange
    {
        return _UnwrappedSubrange(__range.end().base(), __range.begin().base(), __range.size());
    }

    template <class _Range, class _UnwrappedSubrange = __unwrapped_reverse_subrange_t<remove_cvref_t<_Range>>>
        requires __is_unsized_reverse_subrange<remove_cvref_t<_Range>>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Range&& __range) const
        noexcept(noexcept(_UnwrappedSubrange(__range.end().base(), __range.begin().base()))) -> _UnwrappedSubrange
    {
        return _UnwrappedSubrange(__range.end().base(), __range.begin().base());
    }

    template <class _Range>
        requires(!__is_reverse_view<remove_cvref_t<_Range>>) &&
                    (!__is_sized_reverse_subrange<remove_cvref_t<_Range>>) &&
                    (!__is_unsized_reverse_subrange<remove_cvref_t<_Range>>)
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range) const
        noexcept(noexcept(reverse_view{::asc::std::forward<_Range>(__range)})) -> reverse_view<all_t<_Range>>
    {
        return reverse_view{::asc::std::forward<_Range>(__range)};
    }
#else
    template <class _Range, enable_if_t<__is_reverse_view<remove_cvref_t<_Range>>, int> = 0>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Range&& __range) const noexcept(
        noexcept(::asc::std::forward<_Range>(__range).base())) -> decltype(::asc::std::forward<_Range>(__range).base())
    {
        return ::asc::std::forward<_Range>(__range).base();
    }

    template <class _Range, class _UnwrappedSubrange = __unwrapped_reverse_subrange_t<remove_cvref_t<_Range>>,
        enable_if_t<__is_sized_reverse_subrange<remove_cvref_t<_Range>>, int> = 0>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Range&& __range) const noexcept(noexcept(
        _UnwrappedSubrange(__range.end().base(), __range.begin().base(), __range.size()))) -> _UnwrappedSubrange
    {
        return _UnwrappedSubrange(__range.end().base(), __range.begin().base(), __range.size());
    }

    template <class _Range, class _UnwrappedSubrange = __unwrapped_reverse_subrange_t<remove_cvref_t<_Range>>,
        enable_if_t<__is_unsized_reverse_subrange<remove_cvref_t<_Range>>, int> = 0>
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Range&& __range) const
        noexcept(noexcept(_UnwrappedSubrange(__range.end().base(), __range.begin().base()))) -> _UnwrappedSubrange
    {
        return _UnwrappedSubrange(__range.end().base(), __range.begin().base());
    }

    template <class _Range,
        enable_if_t<!__is_reverse_view<remove_cvref_t<_Range>> &&
                !__is_sized_reverse_subrange<remove_cvref_t<_Range>> &&
                !__is_unsized_reverse_subrange<remove_cvref_t<_Range>>,
            int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(_Range&& __range) const
        noexcept(noexcept(reverse_view{::asc::std::forward<_Range>(__range)})) -> reverse_view<all_t<_Range>>
    {
        return reverse_view{::asc::std::forward<_Range>(__range)};  // NOLINT(build/include_what_you_use)
    }
#endif
};

}  // namespace __reverse

inline constexpr __reverse::__fn reverse{};

}  // namespace ranges::views

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_REVERSE_VIEW_H
