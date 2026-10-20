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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_COUNTED_ADAPTOR_H
#define CANN_ASC_STL_ASC_STD___RANGES_COUNTED_ADAPTOR_H

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
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__functional/bind_back.h>
#include <asc/std/__ranges/all.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>

namespace asc::std::ranges::views {

template <class Function, class Range, class Difference, class = void>
struct __counted_adaptor_result {};
template <class Function, class Range, class Difference>
struct __counted_adaptor_result<Function, Range, Difference,
    void_t<all_t<Range>, enable_if_t<convertible_to<Difference, range_difference_t<all_t<Range>>>>>> {
    using type = decltype(Function{}(::asc::std::declval<Range>(), ::asc::std::declval<Difference>()));
};

// take and drop share count validation and binding while dispatching to their
// own algorithms. Bind the derived CPO so closures retain its original type.
template <class Derived, class Function>
struct __counted_adaptor {
    CANN_ASC_STL_DETAIL_TEMPLATE(class Range, class Difference, class View = all_t<Range>)
    CANN_ASC_STL_DETAIL_REQUIRES(view<View>&& convertible_to<Difference, range_difference_t<View>>)
    CANN_ASC_STL_API constexpr auto operator()(Range&& range, Difference&& count) const ->
        typename __counted_adaptor_result<Function, Range, Difference>::type
    {
        return Function{}(::asc::std::forward<Range>(range), ::asc::std::forward<Difference>(count));
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Difference)
    CANN_ASC_STL_DETAIL_REQUIRES(
        constructible_from<decay_t<Difference>, Difference>&& move_constructible<decay_t<Difference>>)
    CANN_ASC_STL_API constexpr auto operator()(Difference&& count) const
    {
        return __pipeable(::asc::std::__bind_back(static_cast<const Derived&>(*this),
            ::asc::std::forward<Difference>(count)));  // NOLINT(build/include_what_you_use)
    }
};

}  // namespace asc::std::ranges::views

#endif  // CANN_ASC_STL_ASC_STD___RANGES_COUNTED_ADAPTOR_H
