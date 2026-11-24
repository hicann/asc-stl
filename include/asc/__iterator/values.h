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

#ifndef CANN_ASC_STL_ASC___ITERATOR_VALUES_H
#define CANN_ASC_STL_ASC___ITERATOR_VALUES_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__iterator/support.h>

namespace asc {

template <class T, class Difference = ::asc::std::ptrdiff_t>
class constant_iterator
    : public detail::iterator_detail::logical_position<constant_iterator<T, Difference>, Difference> {
    using base_type = detail::iterator_detail::logical_position<constant_iterator, Difference>;
    static_assert(::asc::std::is_object_v<T> && !::asc::std::is_array_v<T> &&
            ::asc::std::is_same_v<T, ::asc::std::remove_cv_t<T>> && ::asc::std::is_copy_constructible_v<T> &&
            ::asc::std::is_move_constructible_v<T> && ::asc::std::is_nothrow_destructible_v<T>,
        "constant_iterator must own a copyable object");

public:
    using value_type = T;
    using reference = T;
    using difference_type = Difference;
    using pointer = detail::iterator_detail::arrow_value<T>;
    using iterator_category = ::asc::std::input_iterator_tag;
    using iterator_concept = ::asc::std::random_access_iterator_tag;

    CANN_ASC_STL_API constexpr constant_iterator() noexcept = default;
    template <class U,
        ::asc::std::enable_if_t<!::asc::std::is_same_v<::asc::std::remove_cvref_t<U>, constant_iterator> &&
                ::asc::std::is_constructible_v<T, U>,
            int> = 0>
    CANN_ASC_STL_API constexpr explicit constant_iterator(U&& value, Difference position = 0) noexcept(
        ::asc::std::is_nothrow_constructible_v<T, U>)
        : base_type(true, position), value_(::asc::std::in_place, ::asc::std::forward<U>(value))
    {}
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return value_.bound();
    }
    CANN_ASC_STL_API constexpr T operator*() const noexcept(::asc::std::is_nothrow_copy_constructible_v<T>)
    {
        detail::iterator_detail::require(__is_bound());
        return value_.get();
    }
    CANN_ASC_STL_API constexpr T __at(Difference n) const noexcept(::asc::std::is_nothrow_copy_constructible_v<T>)
    {
        (void)detail::iterator_detail::add(this->position_, n);
        return **this;
    }
    CANN_ASC_STL_API constexpr pointer operator->() const
        noexcept(::asc::std::is_nothrow_copy_constructible_v<T> && ::asc::std::is_nothrow_move_constructible_v<T>)
    {
        return pointer(**this);
    }
    CANN_ASC_STL_API friend constexpr T iter_move(const constant_iterator& it) noexcept(noexcept(*it))
    {
        return *it;
    }

private:
    detail::iterator_detail::state_box<T> value_;
};

template <class Start, class Difference = ::asc::std::ptrdiff_t>
class counting_iterator
    : public detail::iterator_detail::logical_position<counting_iterator<Start, Difference>, Difference> {
    using base_type = detail::iterator_detail::logical_position<counting_iterator, Difference>;
    static_assert(detail::iterator_detail::integer_v<Start>, "counting_iterator requires a non-bool standard integer");

public:
    using value_type = Start;
    using reference = Start;
    using difference_type = Difference;
    using pointer = void;
    using iterator_category = ::asc::std::input_iterator_tag;
    using iterator_concept = ::asc::std::random_access_iterator_tag;
    CANN_ASC_STL_API constexpr counting_iterator() noexcept = default;
    CANN_ASC_STL_API constexpr explicit counting_iterator(Start first, Difference position = 0) noexcept
        : base_type(true, position), first_(first)
    {}
    CANN_ASC_STL_API constexpr Start operator*() const noexcept
    {
        return __at(0);
    }
    CANN_ASC_STL_API constexpr Start __at(Difference n) const noexcept
    {
        detail::iterator_detail::require(this->__is_bound());
        return detail::iterator_detail::offset_value(first_, detail::iterator_detail::add(this->position_, n));
    }
    CANN_ASC_STL_API friend constexpr Start iter_move(const counting_iterator& it) noexcept
    {
        return *it;
    }

private:
    Start first_{};
};

template <class Index, class Bijection, class Difference = ::asc::std::ptrdiff_t>
class shuffle_iterator
    : public detail::iterator_detail::logical_position<shuffle_iterator<Index, Bijection, Difference>, Difference> {
    using base_type = detail::iterator_detail::logical_position<shuffle_iterator, Difference>;
    static_assert(detail::iterator_detail::integer_v<Index>);
    static_assert(::asc::std::is_copy_constructible_v<Bijection> && ::asc::std::is_move_constructible_v<Bijection> &&
        ::asc::std::is_nothrow_destructible_v<Bijection>);
    static_assert(
        ::asc::std::is_same_v<Index, ::asc::std::remove_cvref_t<::asc::std::invoke_result_t<const Bijection&, Index>>>,
        "index mapping must return the specified index type");

public:
    using value_type = Index;
    using reference = Index;
    using difference_type = Difference;
    using pointer = void;
    using iterator_category = ::asc::std::input_iterator_tag;
    using iterator_concept = ::asc::std::random_access_iterator_tag;
    CANN_ASC_STL_API constexpr shuffle_iterator() noexcept = default;
    template <class F, ::asc::std::enable_if_t<::asc::std::is_constructible_v<Bijection, F>, int> = 0>
    CANN_ASC_STL_API constexpr explicit shuffle_iterator(F&& function, Index first = 0,
        Difference position = 0) noexcept(::asc::std::is_nothrow_constructible_v<Bijection, F>)
        : base_type(true, position), function_(::asc::std::in_place, ::asc::std::forward<F>(function)), first_(first)
    {}
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return function_.bound();
    }
    CANN_ASC_STL_API constexpr Index operator*() const noexcept(noexcept(__at(0)))
    {
        return __at(0);
    }
    CANN_ASC_STL_API constexpr Index __at(Difference n) const
        noexcept(::asc::std::is_nothrow_invocable_v<const Bijection&, Index>)
    {
        detail::iterator_detail::require(__is_bound());
        return ::asc::std::invoke(function_.get(),
            detail::iterator_detail::offset_value(first_, detail::iterator_detail::add(this->position_, n)));
    }
    CANN_ASC_STL_API friend constexpr Index iter_move(const shuffle_iterator& it) noexcept(noexcept(*it))
    {
        return *it;
    }

private:
    detail::iterator_detail::state_box<Bijection> function_;
    Index first_{};
};

namespace detail::iterator_detail {

struct discard_proxy {
    template <class U>
    CANN_ASC_STL_API constexpr const discard_proxy& operator=(U&&) const noexcept
    {
        return *this;
    }
};

}  // namespace detail::iterator_detail

class discard_iterator : public detail::iterator_detail::logical_position<discard_iterator, ::asc::std::ptrdiff_t> {
    using base_type = detail::iterator_detail::logical_position<discard_iterator, ::asc::std::ptrdiff_t>;

public:
    using value_type = void;
    using reference = detail::iterator_detail::discard_proxy;
    using difference_type = ::asc::std::ptrdiff_t;
    using pointer = void;
    using iterator_category = ::asc::std::output_iterator_tag;
    using iterator_concept = ::asc::std::output_iterator_tag;
    CANN_ASC_STL_API constexpr discard_iterator() noexcept : base_type(true, 0)
    {}
    CANN_ASC_STL_API constexpr explicit discard_iterator(difference_type position) noexcept : base_type(true, position)
    {}
    CANN_ASC_STL_API constexpr reference operator*() const noexcept
    {
        return {};
    }
    CANN_ASC_STL_API constexpr reference __at(difference_type n) const noexcept
    {
        (void)detail::iterator_detail::add(this->position_, n);
        return {};
    }
};

template <class D = ::asc::std::ptrdiff_t, class T,
    ::asc::std::enable_if_t<::asc::std::is_copy_constructible_v<
                                ::asc::std::decay_t<T>>&& ::asc::std::is_constructible_v<::asc::std::decay_t<T>, T>,
        int> = 0>
CANN_ASC_STL_API constexpr constant_iterator<::asc::std::decay_t<T>, D> make_constant_iterator(
    T&& value, D position = 0) noexcept(::asc::std::is_nothrow_constructible_v<::asc::std::decay_t<T>, T>)
{
    return constant_iterator<::asc::std::decay_t<T>, D>(::asc::std::forward<T>(value), position);
}

template <class D = ::asc::std::ptrdiff_t, class Start,
    ::asc::std::enable_if_t<detail::iterator_detail::integer_v<Start>, int> = 0>
CANN_ASC_STL_API constexpr counting_iterator<Start, D> make_counting_iterator(Start first, D position = 0) noexcept
{
    return counting_iterator<Start, D>(first, position);
}

template <class D = ::asc::std::ptrdiff_t, class F, class Index = ::asc::std::size_t,
    ::asc::std::enable_if_t<detail::iterator_detail::integer_v<Index>&& ::asc::std::is_copy_constructible_v<::asc::std::
                                    decay_t<F>>&& ::asc::std::is_invocable_v<const ::asc::std::decay_t<F>&, Index>,
        int> = 0>
CANN_ASC_STL_API constexpr shuffle_iterator<Index, ::asc::std::decay_t<F>, D> make_shuffle_iterator(F&& function,
    Index first = 0, D position = 0) noexcept(::asc::std::is_nothrow_constructible_v<::asc::std::decay_t<F>, F>)
{
    // NOLINTNEXTLINE(build/include_what_you_use)
    return shuffle_iterator<Index, ::asc::std::decay_t<F>, D>(::asc::std::forward<F>(function), first, position);
}

CANN_ASC_STL_API constexpr discard_iterator make_discard_iterator(::asc::std::ptrdiff_t position = 0) noexcept
{
    return discard_iterator(position);
}

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___ITERATOR_VALUES_H
