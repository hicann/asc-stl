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

#ifndef CANN_ASC_STL_ASC___ITERATOR_ACCESS_H
#define CANN_ASC_STL_ASC___ITERATOR_ACCESS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__iterator/cursor.h>

namespace asc {

template <class Iterator, class IndexIterator>
class permutation_iterator
    : public detail::iterator_detail::position_facade<permutation_iterator<Iterator, IndexIterator>,
          ::asc::std::iter_difference_t<IndexIterator>> {
    template <class, class>
    friend class permutation_iterator;
    static_assert(
        detail::iterator_detail::navigation<Iterator>::value >= 3 && detail::iterator_detail::readable<Iterator>::value,
        "permutation data must be random access and readable");
    static_assert(detail::iterator_detail::integer_v<::asc::std::iter_value_t<IndexIterator>>,
        "permutation indices must be non-bool standard integers");

public:
    using value_type = ::asc::std::iter_value_t<Iterator>;
    using reference = ::asc::std::iter_reference_t<Iterator>;
    using difference_type = ::asc::std::iter_difference_t<IndexIterator>;
    using pointer = detail::iterator_detail::arrow_type<reference>;
    using iterator_category = ::asc::std::input_iterator_tag;
    static constexpr int __iterator_rank = detail::iterator_detail::navigation<IndexIterator>::value;
    static constexpr bool __iterator_equality = detail::iterator_detail::equality<IndexIterator>::value;
    using iterator_concept = detail::iterator_detail::navigation_tag<__iterator_rank>;
    CANN_ASC_STL_API constexpr permutation_iterator() noexcept = default;
    CANN_ASC_STL_API constexpr permutation_iterator(Iterator data, IndexIterator index) noexcept(
        ::asc::std::is_nothrow_move_constructible_v<Iterator> &&
        ::asc::std::is_nothrow_move_constructible_v<IndexIterator>)
        : data_(::asc::std::in_place, ::asc::std::move(data)), index_(::asc::std::in_place, ::asc::std::move(index))
    {}
    template <class I, class J,
        ::asc::std::enable_if_t<
            ::asc::std::is_convertible_v<const I&, Iterator>&& ::asc::std::is_convertible_v<const J&,
                IndexIterator>&& ::asc::std::is_same_v<difference_type, ::asc::std::iter_difference_t<J>>,
            int> = 0>
    CANN_ASC_STL_API constexpr permutation_iterator(const permutation_iterator<I, J>& other) noexcept(
        ::asc::std::is_nothrow_constructible_v<Iterator, const I&> &&
        ::asc::std::is_nothrow_constructible_v<IndexIterator, const J&>)
        : data_(detail::iterator_detail::convert_box<Iterator>(other.data_)),
          index_(detail::iterator_detail::convert_box<IndexIterator>(other.index_))
    {}
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return data_.bound() && index_.bound();
    }
    CANN_ASC_STL_API constexpr Iterator base() const noexcept(::asc::std::is_nothrow_copy_constructible_v<Iterator>)
    {
        return data_.get();
    }
    CANN_ASC_STL_API constexpr IndexIterator index_base() const
        noexcept(::asc::std::is_nothrow_copy_constructible_v<IndexIterator>)
    {
        return index_.get();
    }
    CANN_ASC_STL_API constexpr Iterator __target() const noexcept(noexcept(
        data_.get() + detail::iterator_detail::index_offset<::asc::std::iter_difference_t<Iterator>>(*index_.get())))
    {
        detail::iterator_detail::require(__is_bound());
        return data_.get() +
            detail::iterator_detail::index_offset<::asc::std::iter_difference_t<Iterator>>(*index_.get());
    }
    CANN_ASC_STL_API constexpr reference operator*() const noexcept(noexcept(*__target()))
    {
        return *__target();
    }
    CANN_ASC_STL_API constexpr pointer operator->() const
        noexcept(noexcept(detail::iterator_detail::arrow<reference>(**this)))
    {
        return detail::iterator_detail::arrow<reference>(**this);
    }
    CANN_ASC_STL_API constexpr reference __at(difference_type n) const noexcept(noexcept(
        data_.get()[detail::iterator_detail::index_offset<::asc::std::iter_difference_t<Iterator>>(index_.get()[n])]))
    {
        detail::iterator_detail::require(__is_bound());
        return data_
            .get()[detail::iterator_detail::index_offset<::asc::std::iter_difference_t<Iterator>>(index_.get()[n])];
    }
    CANN_ASC_STL_API constexpr void __increment() noexcept(noexcept(++index_.get()))
    {
        detail::iterator_detail::require(__is_bound());
        ++index_.get();
    }
    CANN_ASC_STL_API constexpr void __decrement() noexcept(noexcept(--index_.get()))
    {
        --index_.get();
    }
    CANN_ASC_STL_API constexpr void __advance(difference_type n) noexcept(noexcept(index_.get() += n))
    {
        index_.get() += n;
    }
    CANN_ASC_STL_API constexpr void __retreat(difference_type n) noexcept(noexcept(index_.get() -= n))
    {
        index_.get() -= n;
    }
    CANN_ASC_STL_API constexpr bool __equal(const permutation_iterator& other) const
        noexcept(noexcept(static_cast<bool>(index_.get() == other.index_.get())))
    {
        return static_cast<bool>(index_.get() == other.index_.get());
    }
    CANN_ASC_STL_API constexpr bool __less(const permutation_iterator& other) const
        noexcept(noexcept(static_cast<bool>(index_.get() < other.index_.get())))
    {
        return static_cast<bool>(index_.get() < other.index_.get());
    }
    CANN_ASC_STL_API constexpr difference_type __distance(const permutation_iterator& other) const
        noexcept(noexcept(index_.get() - other.index_.get()))
    {
        return index_.get() - other.index_.get();
    }
    CANN_ASC_STL_API constexpr auto __postfix() noexcept(__iterator_rank >= 1 ?
            noexcept(detail::iterator_detail::old_position(*this)) :
            (noexcept(__target()) && noexcept(++index_.get()) && ::asc::std::is_nothrow_move_constructible_v<Iterator>))
    {
        if constexpr (__iterator_rank >= 1) {
            return detail::iterator_detail::old_position(*this);
        } else {
            auto target = __target();
            ++index_.get();
            return target;
        }
    }

private:
    detail::iterator_detail::state_box<Iterator> data_;
    detail::iterator_detail::state_box<IndexIterator> index_;
};

template <class Iterator>
class strided_iterator : public detail::iterator_detail::position_facade<strided_iterator<Iterator>,
                             ::asc::std::iter_difference_t<Iterator>> {
    template <class>
    friend class strided_iterator;
    static_assert(
        detail::iterator_detail::navigation<Iterator>::value >= 3 && detail::iterator_detail::readable<Iterator>::value,
        "strided_iterator requires a readable random-access base");

public:
    using value_type = ::asc::std::iter_value_t<Iterator>;
    using reference = ::asc::std::iter_reference_t<Iterator>;
    using difference_type = ::asc::std::iter_difference_t<Iterator>;
    using pointer = detail::iterator_detail::arrow_type<reference>;
    using iterator_category = ::asc::std::conditional_t<
        ::asc::std::is_lvalue_reference_v<reference>&& ::asc::std::is_base_of_v<::asc::std::random_access_iterator_tag,
            typename detail::iterator_detail::category<Iterator>::type>,
        ::asc::std::random_access_iterator_tag, ::asc::std::input_iterator_tag>;
    using iterator_concept = ::asc::std::random_access_iterator_tag;
    static constexpr int __iterator_rank = 3;
    static constexpr bool __iterator_equality = true;
    CANN_ASC_STL_API constexpr strided_iterator() noexcept = default;
    CANN_ASC_STL_API constexpr strided_iterator(Iterator first, difference_type extent, difference_type stride = 1,
        difference_type position = 0) noexcept(::asc::std::is_nothrow_move_constructible_v<Iterator>)
        : first_(::asc::std::in_place, ::asc::std::move(first)), extent_(extent), stride_(stride), position_(position)
    {
        detail::iterator_detail::require(extent >= 0 && stride != 0);
        using U = ::asc::std::make_unsigned_t<difference_type>;
        const U step = detail::iterator_detail::magnitude<U>(stride);
        count_ = extent == 0 ? 0 : static_cast<difference_type>(1 + (static_cast<U>(extent) - 1) / step);
        detail::iterator_detail::require(position >= 0 && position <= count_);
    }
    template <class I,
        ::asc::std::enable_if_t<::asc::std::is_convertible_v<const I&, Iterator>&& ::asc::std::is_same_v<
                                    difference_type, ::asc::std::iter_difference_t<I>>,
            int> = 0>
    CANN_ASC_STL_API constexpr strided_iterator(const strided_iterator<I>& other) noexcept(
        ::asc::std::is_nothrow_constructible_v<Iterator, const I&>)
        : first_(detail::iterator_detail::convert_box<Iterator>(other.first_)),
          extent_(other.extent_),
          stride_(other.stride_),
          position_(other.position_),
          count_(other.count_)
    {}
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return first_.bound();
    }
    CANN_ASC_STL_API constexpr Iterator base() const noexcept(::asc::std::is_nothrow_copy_constructible_v<Iterator>)
    {
        return first_.get();
    }
    CANN_ASC_STL_API constexpr difference_type extent() const noexcept
    {
        return extent_;
    }
    CANN_ASC_STL_API constexpr difference_type stride() const noexcept
    {
        return stride_;
    }
    CANN_ASC_STL_API constexpr difference_type count() const noexcept
    {
        return count_;
    }
    CANN_ASC_STL_API constexpr difference_type index() const noexcept
    {
        return position_;
    }
    CANN_ASC_STL_API constexpr Iterator __target(difference_type relative = 0) const
        noexcept(noexcept(first_.get() + relative))
    {
        const difference_type logical = detail::iterator_detail::add(position_, relative);
        detail::iterator_detail::require(__is_bound() && logical >= 0 && logical < count_);
        using U = ::asc::std::make_unsigned_t<difference_type>;
        const U product = static_cast<U>(logical) * detail::iterator_detail::magnitude<U>(stride_);
        const auto offset = static_cast<difference_type>(stride_ > 0 ? product : static_cast<U>(extent_ - 1) - product);
        return first_.get() + offset;
    }
    CANN_ASC_STL_API constexpr reference operator*() const noexcept(noexcept(*__target()))
    {
        return *__target();
    }
    CANN_ASC_STL_API constexpr reference __at(difference_type n) const noexcept(noexcept(*__target(n)))
    {
        return *__target(n);
    }
    CANN_ASC_STL_API constexpr pointer operator->() const
        noexcept(noexcept(detail::iterator_detail::arrow<reference>(**this)))
    {
        return detail::iterator_detail::arrow<reference>(**this);
    }
    CANN_ASC_STL_API constexpr void __advance(difference_type n) noexcept
    {
        detail::iterator_detail::require(__is_bound());
        const auto next = detail::iterator_detail::add(position_, n);
        detail::iterator_detail::require(next >= 0 && next <= count_);
        position_ = next;
    }
    CANN_ASC_STL_API constexpr void __retreat(difference_type n) noexcept
    {
        const auto next = detail::iterator_detail::subtract(position_, n);
        detail::iterator_detail::require(__is_bound() && next >= 0 && next <= count_);
        position_ = next;
    }
    CANN_ASC_STL_API constexpr void __increment() noexcept
    {
        __advance(1);
    }
    CANN_ASC_STL_API constexpr void __decrement() noexcept
    {
        __retreat(1);
    }
    CANN_ASC_STL_API constexpr strided_iterator __postfix() noexcept(
        noexcept(detail::iterator_detail::old_position(*this)))
    {
        return detail::iterator_detail::old_position(*this);
    }
    CANN_ASC_STL_API constexpr bool __equal(const strided_iterator& other) const noexcept
    {
        return position_ == other.position_;
    }
    CANN_ASC_STL_API constexpr bool __less(const strided_iterator& other) const noexcept
    {
        return position_ < other.position_;
    }
    CANN_ASC_STL_API constexpr difference_type __distance(const strided_iterator& other) const noexcept
    {
        return detail::iterator_detail::subtract(position_, other.position_);
    }

private:
    detail::iterator_detail::state_box<Iterator> first_;
    difference_type extent_ = 0;
    difference_type stride_ = 1;
    difference_type position_ = 0;
    difference_type count_ = 0;
};

namespace detail::iterator_detail {

template <class F, class I, class = void>
struct valid_read : ::asc::std::false_type {};
template <class F, class I>
struct valid_read<F, I, ::asc::std::void_t<::asc::std::invoke_result_t<const F&, ::asc::std::iter_reference_t<I>>>>
    : ::asc::std::bool_constant<readable<I>::value&& ::asc::std::is_copy_constructible_v<F>&& ::asc::std::
                                    is_nothrow_destructible_v<F>&& ::asc::std::is_object_v<::asc::std::remove_cvref_t<
                                        ::asc::std::invoke_result_t<const F&, ::asc::std::iter_reference_t<I>>>> &&
          !::asc::std::is_array_v<
              ::asc::std::remove_cvref_t<::asc::std::invoke_result_t<const F&, ::asc::std::iter_reference_t<I>>>>> {};

}  // namespace detail::iterator_detail

template <class Function, class Iterator>
class transform_iterator
    : public detail::iterator_detail::cursor_position<transform_iterator<Function, Iterator>, Iterator> {
    using base_type = detail::iterator_detail::cursor_position<transform_iterator, Iterator>;
    template <class, class>
    friend class transform_iterator;
    static_assert(detail::iterator_detail::valid_read<Function, Iterator>::value,
        "transform requires a stable readable operation");
    static_assert(::asc::std::is_same_v<::asc::std::iter_difference_t<Iterator>, typename base_type::difference_type>,
        "readable iterator difference must satisfy its signed difference protocol");

public:
    using reference = ::asc::std::invoke_result_t<const Function&, ::asc::std::iter_reference_t<Iterator>>;
    using value_type = ::asc::std::remove_cvref_t<reference>;
    using difference_type = ::asc::std::iter_difference_t<Iterator>;
    using pointer = detail::iterator_detail::arrow_type<reference>;
    using iterator_category = ::asc::std::input_iterator_tag;
    using iterator_concept = detail::iterator_detail::navigation_tag<base_type::__iterator_rank>;
    CANN_ASC_STL_API constexpr transform_iterator() noexcept = default;
    template <class F, ::asc::std::enable_if_t<::asc::std::is_constructible_v<Function, F>, int> = 0>
    CANN_ASC_STL_API constexpr transform_iterator(Iterator current, F&& function) noexcept(
        ::asc::std::is_nothrow_move_constructible_v<Iterator> && ::asc::std::is_nothrow_constructible_v<Function, F>)
        : base_type(::asc::std::in_place, ::asc::std::move(current)),
          function_(::asc::std::in_place, ::asc::std::forward<F>(function))
    {}
    template <class I,
        ::asc::std::enable_if_t<::asc::std::is_convertible_v<const I&, Iterator> &&
                detail::iterator_detail::valid_read<Function, Iterator>::value&& ::asc::std::is_same_v<difference_type,
                    ::asc::std::iter_difference_t<I>>,
            int> = 0>
    CANN_ASC_STL_API constexpr transform_iterator(const transform_iterator<Function, I>& other) noexcept(
        ::asc::std::is_nothrow_constructible_v<Iterator, const I&> &&
        ::asc::std::is_nothrow_copy_constructible_v<Function>)
        : base_type(other.current_), function_(other.function_)
    {}
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return this->current_.bound() && function_.bound();
    }
    CANN_ASC_STL_API constexpr reference operator*() const
        noexcept(::asc::std::is_nothrow_invocable_v<const Function&, ::asc::std::iter_reference_t<Iterator>> &&
            noexcept(*this->current_.get()))
    {
        detail::iterator_detail::require(__is_bound());
        return ::asc::std::invoke(function_.get(), *this->current_.get());
    }
    CANN_ASC_STL_API constexpr reference __at(difference_type n) const
        noexcept(noexcept(::asc::std::invoke(function_.get(), this->current_.get()[n])))
    {
        detail::iterator_detail::require(__is_bound());
        return ::asc::std::invoke(function_.get(), this->current_.get()[n]);
    }
    CANN_ASC_STL_API constexpr pointer operator->() const
        noexcept(noexcept(detail::iterator_detail::arrow<reference>(**this)))
    {
        return detail::iterator_detail::arrow<reference>(**this);
    }
    CANN_ASC_STL_API constexpr auto __postfix() noexcept(
        detail::iterator_detail::read_postfix_nothrow<transform_iterator>())
    {
        return detail::iterator_detail::read_postfix(*this);
    }

private:
    detail::iterator_detail::state_box<Function> function_;
};

template <class I, class J>
CANN_ASC_STL_API constexpr permutation_iterator<I, J> make_permutation_iterator(I data, J index) noexcept(
    ::asc::std::is_nothrow_move_constructible_v<I> && ::asc::std::is_nothrow_move_constructible_v<J>)
{
    return permutation_iterator<I, J>(::asc::std::move(data), ::asc::std::move(index));
}

template <class I>
CANN_ASC_STL_API constexpr strided_iterator<I> make_strided_iterator(I first, ::asc::std::iter_difference_t<I> extent,
    ::asc::std::iter_difference_t<I> stride = 1) noexcept(::asc::std::is_nothrow_move_constructible_v<I>)
{
    return strided_iterator<I>(::asc::std::move(first), extent, stride);
}

template <class I, class F,
    ::asc::std::enable_if_t<detail::iterator_detail::valid_read<::asc::std::decay_t<F>, I>::value &&
            detail::iterator_detail::stored_callable_v<F>,
        int> = 0>
CANN_ASC_STL_API constexpr transform_iterator<::asc::std::decay_t<F>, I> make_transform_iterator(
    I current, F&& function) noexcept(::asc::std::is_nothrow_move_constructible_v<I> &&
    ::asc::std::is_nothrow_constructible_v<::asc::std::decay_t<F>, F>)
{
    return transform_iterator<::asc::std::decay_t<F>, I>(::asc::std::move(current), ::asc::std::forward<F>(function));
}

template <class I, class J>
CANN_ASC_STL_API constexpr auto iter_move(const permutation_iterator<I, J>& it) noexcept(
    noexcept(::asc::std::iter_move(it.__target()))) -> decltype(::asc::std::iter_move(it.__target()))
{
    return ::asc::std::iter_move(it.__target());
}
template <class I>
CANN_ASC_STL_API constexpr auto iter_move(const strided_iterator<I>& it) noexcept(
    noexcept(::asc::std::iter_move(it.__target()))) -> decltype(::asc::std::iter_move(it.__target()))
{
    return ::asc::std::iter_move(it.__target());
}
template <class I, class J, class I2, class J2>
CANN_ASC_STL_API constexpr auto iter_swap(const permutation_iterator<I, J>& left,
    const permutation_iterator<I2, J2>& right) noexcept(noexcept(::asc::std::ranges::iter_swap(left.__target(),
    right.__target()))) -> decltype(::asc::std::ranges::iter_swap(left.__target(), right.__target()))
{
    return ::asc::std::ranges::iter_swap(left.__target(), right.__target());
}
template <class I, class I2>
CANN_ASC_STL_API constexpr auto iter_swap(const strided_iterator<I>& left, const strided_iterator<I2>& right) noexcept(
    noexcept(::asc::std::ranges::iter_swap(left.__target(),
        right.__target()))) -> decltype(::asc::std::ranges::iter_swap(left.__target(), right.__target()))
{
    return ::asc::std::ranges::iter_swap(left.__target(), right.__target());
}
template <class F, class I>
CANN_ASC_STL_API constexpr detail::iterator_detail::moved_reference<typename transform_iterator<F, I>::reference>
iter_move(const transform_iterator<F, I>& it) noexcept(noexcept(*it))
{
    if constexpr (::asc::std::is_lvalue_reference_v<typename transform_iterator<F, I>::reference>) {
        // NOLINTNEXTLINE(build/include_what_you_use)
        return ::asc::std::move(*it);
    } else {
        return *it;
    }
}
template <class F, class I, class I2,
    ::asc::std::enable_if_t<::asc::std::is_lvalue_reference_v<typename transform_iterator<F, I>::reference>&& ::asc::
                                std::is_lvalue_reference_v<typename transform_iterator<F, I2>::reference>,
        int> = 0>
CANN_ASC_STL_API constexpr auto iter_swap(const transform_iterator<F, I>& left,
    const transform_iterator<F, I2>& right) noexcept(noexcept(::asc::std::ranges::swap(*left,
    *right))) -> decltype(::asc::std::ranges::swap(*left, *right))
{
    return ::asc::std::ranges::swap(*left, *right);
}

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___ITERATOR_ACCESS_H
