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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_SINGLE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_SINGLE_VIEW_H

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
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/range_adaptor.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
namespace asc::std::ranges {
template <class T>
class single_view : public view_interface<single_view<T>> {
public:
    CANN_ASC_STL_API constexpr single_view() = default;
    CANN_ASC_STL_API constexpr explicit single_view(const T& value) noexcept(is_nothrow_copy_constructible_v<T>)
        : value_(value)
    {}
    CANN_ASC_STL_API constexpr explicit single_view(T&& value) noexcept(is_nothrow_move_constructible_v<T>)
        : value_(::asc::std::move(value))
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit single_view(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<T, Args...>)
        : value_(::asc::std::forward<Args>(args)...)
    {}
    CANN_ASC_STL_API constexpr T* begin() noexcept
    {
        return &value_;
    }
    CANN_ASC_STL_API constexpr const T* begin() const noexcept
    {
        return &value_;
    }
    CANN_ASC_STL_API constexpr T* end() noexcept
    {
        return &value_ + 1;
    }
    CANN_ASC_STL_API constexpr const T* end() const noexcept
    {
        return &value_ + 1;
    }
    CANN_ASC_STL_API constexpr T* data() noexcept
    {
        return &value_;
    }
    CANN_ASC_STL_API constexpr const T* data() const noexcept
    {
        return &value_;
    }
    CANN_ASC_STL_API static constexpr __SIZE_TYPE__ size() noexcept
    {
        return 1;
    }

private:
    T value_{};
};
namespace views {
struct __single_fn {
    template <class T>
    CANN_ASC_STL_API constexpr single_view<decay_t<T>> operator()(T&& value) const
    {
        return single_view<decay_t<T>>(::asc::std::forward<T>(value));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __single_fn single{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_SINGLE_VIEW_H
