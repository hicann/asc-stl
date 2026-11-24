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

#ifndef CANN_ASC_STL_ASC___ITERATOR_CURSOR_H
#define CANN_ASC_STL_ASC___ITERATOR_CURSOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__iterator/support.h>

namespace asc::detail::iterator_detail {

template <class Derived, class I>
class cursor_position : public position_facade<Derived, difference_t<I>> {
public:
    using difference_type = difference_t<I>;
    static constexpr int __iterator_rank = navigation<I>::value;
    static constexpr bool __iterator_equality = equality<I>::value;
    CANN_ASC_STL_API constexpr I base() const noexcept(::asc::std::is_nothrow_copy_constructible_v<I>)
    {
        return current_.get();
    }
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return current_.bound();
    }
    CANN_ASC_STL_API constexpr void __increment() noexcept(noexcept(++current_.get()))
    {
        require(static_cast<const Derived&>(*this).__is_bound());
        ++current_.get();
    }
    CANN_ASC_STL_API constexpr void __decrement() noexcept(noexcept(--current_.get()))
    {
        --current_.get();
    }
    CANN_ASC_STL_API constexpr void __advance(difference_type n) noexcept(noexcept(current_.get() += n))
    {
        current_.get() += n;
    }
    CANN_ASC_STL_API constexpr void __retreat(difference_type n) noexcept(noexcept(current_.get() -= n))
    {
        current_.get() -= n;
    }
    CANN_ASC_STL_API constexpr bool __equal(const Derived& other) const
        noexcept(noexcept(static_cast<bool>(current_.get() == other.current_.get())))
    {
        return static_cast<bool>(current_.get() == other.current_.get());
    }
    CANN_ASC_STL_API constexpr bool __less(const Derived& other) const
        noexcept(noexcept(static_cast<bool>(current_.get() < other.current_.get())))
    {
        return static_cast<bool>(current_.get() < other.current_.get());
    }
    CANN_ASC_STL_API constexpr difference_type __distance(const Derived& other) const
        noexcept(noexcept(current_.get() - other.current_.get()))
    {
        return current_.get() - other.current_.get();
    }

protected:
    CANN_ASC_STL_API constexpr cursor_position() noexcept = default;
    CANN_ASC_STL_API constexpr explicit cursor_position(I current) noexcept(
        ::asc::std::is_nothrow_move_constructible_v<I>)
        : current_(::asc::std::in_place, ::asc::std::move(current))
    {}
    template <class J>
    CANN_ASC_STL_API constexpr explicit cursor_position(const state_box<J>& current) noexcept(
        ::asc::std::is_nothrow_constructible_v<I, const J&>)
        : current_(convert_box<I>(current))
    {}
    template <class J>
    CANN_ASC_STL_API constexpr cursor_position(::asc::std::in_place_t, J&& current) noexcept(
        ::asc::std::is_nothrow_constructible_v<I, J>)
        // ASC-STL provides the Device-capable utility declarations through support.h.
        // NOLINTNEXTLINE(build/include_what_you_use)
        : current_(::asc::std::in_place, ::asc::std::forward<J>(current))
    {}
    state_box<I> current_;
};

}  // namespace asc::detail::iterator_detail

#endif  // CANN_ASC_STL_ASC___ITERATOR_CURSOR_H
