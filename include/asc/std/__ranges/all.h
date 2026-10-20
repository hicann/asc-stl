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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_ALL_H
#define CANN_ASC_STL_ASC_STD___RANGES_ALL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/owning_view.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/ref_view.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
namespace asc::std::ranges::views {
template <class T, class = void>
inline constexpr bool __to_ref_view = false;
template <class T>
inline constexpr bool __to_ref_view<T,
    void_t<enable_if_t<!::asc::std::ranges::view<decay_t<T>> && ::asc::std::ranges::range<remove_reference_t<T>>>,
        decltype(::asc::std::ranges::ref_view{::asc::std::declval<T>()})>> = true;

template <class T, class = void>
inline constexpr bool __to_owning_view = false;
template <class T>
inline constexpr bool __to_owning_view<T,
    void_t<enable_if_t<!::asc::std::ranges::view<decay_t<T>> && !__to_ref_view<T> &&
               ::asc::std::ranges::range<decay_t<T>> && ::asc::std::movable<decay_t<T>> &&
               !::asc::std::ranges::__is_asc_std_initializer_list<decay_t<T>>>,
        decltype(::asc::std::ranges::owning_view{::asc::std::declval<T>()})>> = true;

struct __all_fn : __range_adaptor_closure<__all_fn> {
    CANN_ASC_STL_DETAIL_TEMPLATE(class T)
    CANN_ASC_STL_DETAIL_REQUIRES((::asc::std::ranges::view<decay_t<T>>))
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(
        noexcept(static_cast<decay_t<decltype((::asc::std::forward<T>(value)))>>(::asc::std::forward<T>(value))))
        -> decltype(static_cast<decay_t<decltype((::asc::std::forward<T>(value)))>>(::asc::std::forward<T>(value)))
    {
        // For lvalue arguments the view must be returned by value, not passed
        // through as a reference — otherwise all_t<view&> degenerates to view&
        // and the view constraints of downstream closures all fail.
        return static_cast<decay_t<decltype((::asc::std::forward<T>(value)))>>(::asc::std::forward<T>(value));
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class T)
    CANN_ASC_STL_DETAIL_REQUIRES((__to_ref_view<T>))
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(::asc::std::ranges::ref_view{::asc::std::forward<T>(value)}))
    {
        return ::asc::std::ranges::ref_view{::asc::std::forward<T>(value)};
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class T)
    CANN_ASC_STL_DETAIL_REQUIRES((__to_owning_view<T>))
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(::asc::std::ranges::owning_view{::asc::std::forward<T>(value)}))
    {
        return ::asc::std::ranges::owning_view{::asc::std::forward<T>(value)};  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __all_fn all{};
CANN_ASC_STL_DETAIL_TEMPLATE(class Range)
CANN_ASC_STL_DETAIL_REQUIRES(::asc::std::ranges::viewable_range<Range>)
using all_t = decltype(all(::asc::std::declval<Range>()));
}  // namespace asc::std::ranges::views

#endif  // CANN_ASC_STL_ASC_STD___RANGES_ALL_H
