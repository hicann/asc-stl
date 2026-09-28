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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_REPEAT_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_REPEAT_VIEW_H

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
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__concepts/semiregular.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/unreachable_sentinel.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__ranges/iota_view.h>
#include <asc/std/__ranges/movable_box.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/piecewise_construct.h>
#include <asc/std/tuple>
namespace asc::std::ranges {
template <class T, class Bound = __PTRDIFF_TYPE__>
class repeat_view : public view_interface<repeat_view<T, Bound>> {
    class iterator {
    public:
        using value_type = T;
        using difference_type = __PTRDIFF_TYPE__;
        using reference = const T&;
        using pointer = const T*;
        CANN_ASC_STL_API constexpr iterator(const T* value, difference_type index) : value_(value), index_(index)
        {}
        CANN_ASC_STL_API constexpr const T& operator*() const
        {
            return *value_;
        }
        CANN_ASC_STL_API constexpr iterator& operator++()
        {
            ++index_;
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator& operator--()
        {
            --index_;
            return *this;
        }
        CANN_ASC_STL_API constexpr iterator& operator+=(difference_type value)
        {
            index_ += value;
            return *this;
        }
        CANN_ASC_STL_API constexpr const T& operator[](difference_type) const
        {
            return *value_;
        }
        friend CANN_ASC_STL_API constexpr iterator operator+(iterator value, difference_type amount)
        {
            value += amount;
            return value;
        }
        friend CANN_ASC_STL_API constexpr difference_type operator-(iterator left, iterator right)
        {
            return left.index_ - right.index_;
        }
        friend CANN_ASC_STL_API constexpr bool operator==(iterator left, iterator right)
        {
            return left.index_ == right.index_;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(iterator left, iterator right)
        {
            return !(left == right);
        }

    private:
        const T* value_;
        difference_type index_;
    };

public:
    CANN_ASC_STL_API constexpr repeat_view() = default;
    CANN_ASC_STL_API constexpr repeat_view(const T& value, Bound bound) : value_(value), bound_(bound)
    {}
    CANN_ASC_STL_API constexpr repeat_view(T&& value, Bound bound)
        : value_(::asc::std::move(value)), bound_(::asc::std::move(bound))
    {}
    template <class... TArgs, class... BoundArgs>
    CANN_ASC_STL_API constexpr repeat_view(piecewise_construct_t, tuple<TArgs...> value_args,
        tuple<BoundArgs...> bound_args)  // NOLINT(build/include_what_you_use)
        : value_(::asc::std::make_from_tuple<T>(::asc::std::move(value_args))),
          bound_(::asc::std::make_from_tuple<Bound>(::asc::std::move(bound_args)))
    {}
    CANN_ASC_STL_API constexpr iterator begin() const
    {
        return iterator(&value_, 0);
    }
    CANN_ASC_STL_API constexpr iterator end() const noexcept(is_nothrow_copy_constructible_v<Bound>)
    {
        return iterator(&value_, static_cast<__PTRDIFF_TYPE__>(bound_));
    }
    CANN_ASC_STL_API constexpr __SIZE_TYPE__ size() const
    {
        return static_cast<__SIZE_TYPE__>(bound_);
    }

private:
    T value_{};
    Bound bound_{};
};
namespace views {
struct __repeat_fn {
    template <class T, class Bound>
    CANN_ASC_STL_API constexpr repeat_view<remove_cvref_t<T>, Bound> operator()(T&& value, Bound bound) const
    {
        return {::asc::std::forward<T>(value), bound};  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __repeat_fn repeat{};
}  // namespace views
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_REPEAT_VIEW_H
