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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_IOTA_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_IOTA_VIEW_H

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
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__concepts/semiregular.h>
#include <asc/std/__concepts/totally_ordered.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iota_iterator.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/unreachable_sentinel.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
template <class Value, class Bound = Value>
class iota_view : public view_interface<iota_view<Value, Bound>> {
public:
    using iterator = __iota_iterator<Value>;
    CANN_ASC_STL_API constexpr iota_view() noexcept : first_{}, bound_{}
    {}
    CANN_ASC_STL_API constexpr explicit iota_view(Value first) noexcept : first_(first), bound_{}
    {}
    CANN_ASC_STL_API constexpr iota_view(Value first, Bound bound) noexcept : first_(first), bound_(bound)
    {}
    CANN_ASC_STL_API constexpr iterator begin() const noexcept
    {
        return iterator(first_);
    }
    CANN_ASC_STL_API constexpr iterator end() const noexcept
    {
        return iterator(static_cast<Value>(bound_));
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ size() const noexcept
    {
        return static_cast<__SIZE_TYPE__>(bound_ - first_);
    }

private:
    Value first_;
    Bound bound_;
};
template <class V, class B>
inline constexpr bool enable_borrowed_range<iota_view<V, B>> = true;
namespace views {
struct __iota_fn {
    template <class Value, class Bound>
    CANN_ASC_STL_API constexpr iota_view<Value, Bound> operator()(Value value, Bound bound) const noexcept
    {
        return {value, bound};
    }
};
inline constexpr __iota_fn iota{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_IOTA_VIEW_H
