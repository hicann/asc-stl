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

#ifndef CANN_ASC_STL_ASC___ITERATOR_OUTPUT_H
#define CANN_ASC_STL_ASC___ITERATOR_OUTPUT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__iterator/access.h>
#include <asc/__iterator/cursor.h>

namespace asc::detail::iterator_detail {

struct disabled_assignment {};

template <class I, class F, class U, class = void>
struct can_write : ::asc::std::false_type {};
template <class I, class F, class U>
struct can_write<I, F, U,
    ::asc::std::void_t<decltype(*::asc::std::declval<I&>() = ::asc::std::invoke(
                                    ::asc::std::declval<F&>(), ::asc::std::declval<U>()))>> : ::asc::std::true_type {};

template <class I, class In, class Out>
CANN_ASC_STL_API constexpr bool io_copy_nothrow() noexcept
{
    using R = ::asc::std::invoke_result_t<const In&, ::asc::std::iter_reference_t<I>>;
    if constexpr (can_write<I, Out, R>::value) {
        return noexcept(*::asc::std::declval<I&>() = ::asc::std::invoke(::asc::std::declval<Out&>(),
                            ::asc::std::invoke(::asc::std::declval<const In&>(), *::asc::std::declval<I&>())));
    } else {
        return true;
    }
}

template <class I, class F>
class output_proxy {
public:
    CANN_ASC_STL_API constexpr output_proxy(I position, const F& function) noexcept(
        ::asc::std::is_nothrow_move_constructible_v<I> && ::asc::std::is_nothrow_copy_constructible_v<F>)
        : position_(::asc::std::move(position)), function_(function)
    {}
    CANN_ASC_STL_API constexpr output_proxy(const output_proxy&) = default;
    CANN_ASC_STL_API constexpr output_proxy(output_proxy&&) = default;
    template <class U, ::asc::std::enable_if_t<can_write<I, F, U>::value, int> = 0>
    CANN_ASC_STL_API constexpr const output_proxy& operator=(U&& value) const
        noexcept(noexcept(*position_ = ::asc::std::invoke(function_, ::asc::std::forward<U>(value))))
    {
        *position_ = ::asc::std::invoke(function_, ::asc::std::forward<U>(value));
        return *this;
    }
    CANN_ASC_STL_API constexpr output_proxy operator*() && noexcept(
        ::asc::std::is_nothrow_move_constructible_v<output_proxy>)
    {
        return ::asc::std::move(*this);
    }

private:
    mutable I position_;
    mutable F function_;
};

template <class I>
class output_target {
public:
    CANN_ASC_STL_API constexpr explicit output_target(I position) noexcept(
        ::asc::std::is_nothrow_move_constructible_v<I>)
        : position_(::asc::std::move(position))
    {}
    CANN_ASC_STL_API constexpr output_target(const output_target&) = default;
    CANN_ASC_STL_API constexpr output_target(output_target&&) = default;
    template <class U, class = decltype(*::asc::std::declval<I&>() = ::asc::std::declval<U>())>
    CANN_ASC_STL_API constexpr const output_target& operator=(U&& value) const
        noexcept(noexcept(*position_ = ::asc::std::forward<U>(value)))
    {
        *position_ = ::asc::std::forward<U>(value);
        return *this;
    }

private:
    mutable I position_;
};

template <class F, class Index>
class tabulate_proxy {
public:
    CANN_ASC_STL_API constexpr tabulate_proxy(const F& function, Index index) noexcept(
        ::asc::std::is_nothrow_copy_constructible_v<F>)
        : function_(function), index_(index)
    {}
    CANN_ASC_STL_API constexpr tabulate_proxy(const tabulate_proxy&) = default;
    CANN_ASC_STL_API constexpr tabulate_proxy(tabulate_proxy&&) = default;
    template <class U, ::asc::std::enable_if_t<::asc::std::is_invocable_v<F&, Index, U>, int> = 0>
    CANN_ASC_STL_API constexpr const tabulate_proxy& operator=(U&& value) const
        noexcept(noexcept(static_cast<void>(::asc::std::invoke(function_, index_, ::asc::std::forward<U>(value)))))
    {
        (void)::asc::std::invoke(function_, index_, ::asc::std::forward<U>(value));
        return *this;
    }

private:
    mutable F function_;
    Index index_;
};

template <class I, class In, class Out>
class io_proxy {
public:
    using read_type = ::asc::std::invoke_result_t<const In&, ::asc::std::iter_reference_t<I>>;
    using value_type = ::asc::std::remove_cvref_t<read_type>;
    CANN_ASC_STL_API constexpr io_proxy(I current, const In& input, const Out& output) noexcept(
        ::asc::std::is_nothrow_move_constructible_v<I> && ::asc::std::is_nothrow_copy_constructible_v<In> &&
        ::asc::std::is_nothrow_copy_constructible_v<Out>)
        : current_(::asc::std::move(current)), input_(input), output_(output)
    {}
    CANN_ASC_STL_API constexpr io_proxy(const io_proxy&) = default;
    CANN_ASC_STL_API constexpr io_proxy(io_proxy&&) = default;
    CANN_ASC_STL_API constexpr read_type read() const noexcept(noexcept(::asc::std::invoke(input_, *current_)))
    {
        return ::asc::std::invoke(input_, *current_);
    }
    CANN_ASC_STL_API constexpr operator read_type() const noexcept(noexcept(read()))
    {
        return read();
    }

    using copy_source =
        ::asc::std::conditional_t<can_write<I, Out, read_type>::value, const io_proxy&, disabled_assignment>;
    CANN_ASC_STL_API constexpr const io_proxy& operator=(copy_source other) const
        noexcept(io_copy_nothrow<I, In, Out>())
    {
        if constexpr (can_write<I, Out, read_type>::value) {
            __assign(other.read());
        }
        return *this;
    }
    template <class U,
        ::asc::std::enable_if_t<
            !::asc::std::is_same_v<::asc::std::remove_cvref_t<U>, io_proxy> && can_write<I, Out, U>::value, int> = 0>
    CANN_ASC_STL_API constexpr const io_proxy& operator=(U&& value) const
        noexcept(noexcept(__assign(::asc::std::forward<U>(value))))
    {
        __assign(::asc::std::forward<U>(value));
        return *this;
    }

private:
    template <class U>
    CANN_ASC_STL_API constexpr void __assign(U&& value) const
        noexcept(noexcept(*current_ = ::asc::std::invoke(output_, ::asc::std::forward<U>(value))))
    {
        *current_ = ::asc::std::invoke(output_, ::asc::std::forward<U>(value));
    }
    mutable I current_;
    In input_;
    mutable Out output_;
};

template <class I, class In, class Out>
CANN_ASC_STL_API constexpr moved_reference<typename io_proxy<I, In, Out>::read_type> proxy_move(
    const io_proxy<I, In, Out>& value) noexcept(noexcept(value.read()))
{
    if constexpr (::asc::std::is_lvalue_reference_v<typename io_proxy<I, In, Out>::read_type>) {
        return ::asc::std::move(value.read());
    } else {
        return value.read();
    }
}

template <class I, class In, class Out, class V = typename io_proxy<I, In, Out>::value_type,
    class M = moved_reference<typename io_proxy<I, In, Out>::read_type>,
    ::asc::std::enable_if_t<
        ::asc::std::is_constructible_v<V, M> && can_write<I, Out, M>::value && can_write<I, Out, V&&>::value, int> = 0>
CANN_ASC_STL_API constexpr void swap(const io_proxy<I, In, Out>& left, const io_proxy<I, In, Out>& right) noexcept(
    noexcept(V(proxy_move(left))) && noexcept(left = proxy_move(right)) && noexcept(right = ::asc::std::declval<V&&>()))
{
    V saved(proxy_move(left));
    left = proxy_move(right);
    right = ::asc::std::move(saved);
}

}  // namespace asc::detail::iterator_detail

namespace asc {

template <class Function, class Iterator>
class transform_output_iterator
    : public detail::iterator_detail::cursor_position<transform_output_iterator<Function, Iterator>, Iterator> {
    using base_type = detail::iterator_detail::cursor_position<transform_output_iterator, Iterator>;
    template <class, class>
    friend class transform_output_iterator;
    static_assert(::asc::std::is_copy_constructible_v<Function> && ::asc::std::is_move_constructible_v<Function> &&
        ::asc::std::is_nothrow_destructible_v<Function>);

public:
    using value_type = void;
    using reference = detail::iterator_detail::output_proxy<Iterator, Function>;
    using difference_type = detail::iterator_detail::difference_t<Iterator>;
    using pointer = void;
    using iterator_category = ::asc::std::output_iterator_tag;
    using iterator_concept = ::asc::std::output_iterator_tag;
    CANN_ASC_STL_API constexpr transform_output_iterator() noexcept = default;
    template <class F, ::asc::std::enable_if_t<::asc::std::is_constructible_v<Function, F>, int> = 0>
    CANN_ASC_STL_API constexpr transform_output_iterator(Iterator current, F&& function) noexcept(
        ::asc::std::is_nothrow_move_constructible_v<Iterator> && ::asc::std::is_nothrow_constructible_v<Function, F>)
        : base_type(::asc::std::move(current)), function_(::asc::std::in_place, ::asc::std::forward<F>(function))
    {}
    template <class I,
        ::asc::std::enable_if_t<::asc::std::is_convertible_v<const I&, Iterator>&& ::asc::std::is_same_v<
                                    difference_type, ::asc::std::iter_difference_t<I>>,
            int> = 0>
    CANN_ASC_STL_API constexpr transform_output_iterator(const transform_output_iterator<Function, I>& other) noexcept(
        ::asc::std::is_nothrow_constructible_v<Iterator, const I&> &&
        ::asc::std::is_nothrow_copy_constructible_v<Function>)
        : base_type(other.current_), function_(other.function_)
    {}
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return this->current_.bound() && function_.bound();
    }
    CANN_ASC_STL_API constexpr reference operator*() const noexcept(
        ::asc::std::is_nothrow_copy_constructible_v<Iterator> &&
        ::asc::std::is_nothrow_move_constructible_v<Iterator> && ::asc::std::is_nothrow_copy_constructible_v<Function>)
    {
        detail::iterator_detail::require(__is_bound());
        return reference(this->current_.get(), function_.get());
    }
    CANN_ASC_STL_API constexpr reference __at(difference_type n) const
        noexcept(noexcept(reference(this->current_.get() + n, function_.get())))
    {
        return reference(this->current_.get() + n, function_.get());
    }
    CANN_ASC_STL_API constexpr auto __postfix() noexcept(base_type::__iterator_rank >= 1 ?
            noexcept(detail::iterator_detail::old_position(*this)) :
            noexcept(detail::iterator_detail::output_proxy<decltype(this->current_.get()++), Function>(
                this->current_.get()++, function_.get())))
    {
        if constexpr (base_type::__iterator_rank >= 1) {
            return detail::iterator_detail::old_position(*this);
        } else {
            detail::iterator_detail::require(__is_bound());
            return detail::iterator_detail::output_proxy<decltype(this->current_.get()++), Function>(
                this->current_.get()++, function_.get());
        }
    }

private:
    detail::iterator_detail::state_box<Function> function_;
};

template <class Function, class Index = ::asc::std::ptrdiff_t, class Difference = ::asc::std::ptrdiff_t>
class tabulate_output_iterator
    : public detail::iterator_detail::logical_position<tabulate_output_iterator<Function, Index, Difference>,
          Difference> {
    using base_type = detail::iterator_detail::logical_position<tabulate_output_iterator, Difference>;
    static_assert(detail::iterator_detail::integer_v<Index> && ::asc::std::is_copy_constructible_v<Function> &&
        ::asc::std::is_move_constructible_v<Function> && ::asc::std::is_nothrow_destructible_v<Function>);

public:
    using value_type = void;
    using reference = detail::iterator_detail::tabulate_proxy<Function, Index>;
    using difference_type = Difference;
    using pointer = void;
    using iterator_category = ::asc::std::output_iterator_tag;
    using iterator_concept = ::asc::std::output_iterator_tag;
    CANN_ASC_STL_API constexpr tabulate_output_iterator() noexcept = default;
    template <class F, ::asc::std::enable_if_t<::asc::std::is_constructible_v<Function, F>, int> = 0>
    CANN_ASC_STL_API constexpr explicit tabulate_output_iterator(F&& function, Index first = 0,
        Difference position = 0) noexcept(::asc::std::is_nothrow_constructible_v<Function, F>)
        : base_type(true, position), function_(::asc::std::in_place, ::asc::std::forward<F>(function)), first_(first)
    {}
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return function_.bound();
    }
    CANN_ASC_STL_API constexpr reference operator*() const
        noexcept(::asc::std::is_nothrow_copy_constructible_v<Function>)
    {
        return __at(0);
    }
    CANN_ASC_STL_API constexpr reference __at(Difference n) const
        noexcept(::asc::std::is_nothrow_copy_constructible_v<Function>)
    {
        detail::iterator_detail::require(__is_bound());
        return reference(function_.get(),
            detail::iterator_detail::offset_value(first_, detail::iterator_detail::add(this->position_, n)));
    }

private:
    detail::iterator_detail::state_box<Function> function_;
    Index first_{};
};

template <class InputFunction, class OutputFunction, class Iterator>
class transform_input_output_iterator
    : public detail::iterator_detail::cursor_position<
          transform_input_output_iterator<InputFunction, OutputFunction, Iterator>, Iterator> {
    using base_type = detail::iterator_detail::cursor_position<transform_input_output_iterator, Iterator>;
    template <class, class, class>
    friend class transform_input_output_iterator;
    static_assert(detail::iterator_detail::valid_read<InputFunction, Iterator>::value &&
            base_type::__iterator_rank >= 1 && ::asc::std::is_copy_constructible_v<OutputFunction> &&
            ::asc::std::is_nothrow_destructible_v<OutputFunction>,
        "read/write transformation requires a readable forward base and copyable functions");

public:
    using reference = detail::iterator_detail::io_proxy<Iterator, InputFunction, OutputFunction>;
    using value_type = typename reference::value_type;
    using difference_type = ::asc::std::iter_difference_t<Iterator>;
    using pointer = void;
    using iterator_category = ::asc::std::input_iterator_tag;
    using iterator_concept = detail::iterator_detail::navigation_tag<base_type::__iterator_rank>;
    CANN_ASC_STL_API constexpr transform_input_output_iterator() noexcept = default;
    template <class In, class Out,
        ::asc::std::enable_if_t<
            ::asc::std::is_constructible_v<InputFunction, In>&& ::asc::std::is_constructible_v<OutputFunction, Out>,
            int> = 0>
    CANN_ASC_STL_API constexpr transform_input_output_iterator(Iterator current, In&& input, Out&& output) noexcept(
        ::asc::std::is_nothrow_move_constructible_v<Iterator> &&
        ::asc::std::is_nothrow_constructible_v<InputFunction, In> &&
        ::asc::std::is_nothrow_constructible_v<OutputFunction, Out>)
        : base_type(::asc::std::move(current)),
          input_(::asc::std::in_place, ::asc::std::forward<In>(input)),
          output_(::asc::std::in_place, ::asc::std::forward<Out>(output))
    {}
    template <class I,
        ::asc::std::enable_if_t<::asc::std::is_convertible_v<const I&, Iterator>&& ::asc::std::is_same_v<
                                    difference_type, ::asc::std::iter_difference_t<I>>,
            int> = 0>
    CANN_ASC_STL_API constexpr transform_input_output_iterator(
        const transform_input_output_iterator<InputFunction, OutputFunction, I>&
            other) noexcept(::asc::std::is_nothrow_constructible_v<Iterator, const I&> &&
        ::asc::std::is_nothrow_copy_constructible_v<InputFunction> &&
        ::asc::std::is_nothrow_copy_constructible_v<OutputFunction>)
        : base_type(other.current_), input_(other.input_), output_(other.output_)
    {}
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return this->current_.bound() && input_.bound() && output_.bound();
    }
    CANN_ASC_STL_API constexpr reference operator*() const
        noexcept(noexcept(reference(this->current_.get(), input_.get(), output_.get())))
    {
        detail::iterator_detail::require(__is_bound());
        return reference(this->current_.get(), input_.get(), output_.get());
    }
    CANN_ASC_STL_API constexpr reference __at(difference_type n) const
        noexcept(noexcept(reference(this->current_.get() + n, input_.get(), output_.get())))
    {
        return reference(this->current_.get() + n, input_.get(), output_.get());
    }
    CANN_ASC_STL_API constexpr auto __read() const
        noexcept(noexcept(::asc::std::invoke(input_.get(), *this->current_.get()))) -> typename reference::read_type
    {
        return ::asc::std::invoke(input_.get(), *this->current_.get());
    }
    CANN_ASC_STL_API constexpr transform_input_output_iterator __postfix() noexcept(
        noexcept(detail::iterator_detail::old_position(*this)))
    {
        return detail::iterator_detail::old_position(*this);
    }

private:
    detail::iterator_detail::state_box<InputFunction> input_;
    detail::iterator_detail::state_box<OutputFunction> output_;
};

template <class I, class F, ::asc::std::enable_if_t<detail::iterator_detail::stored_callable_v<F>, int> = 0>
CANN_ASC_STL_API constexpr transform_output_iterator<::asc::std::decay_t<F>, I> make_transform_output_iterator(
    I current, F&& function) noexcept(::asc::std::is_nothrow_move_constructible_v<I> &&
    ::asc::std::is_nothrow_constructible_v<::asc::std::decay_t<F>, F>)
{
    return transform_output_iterator<::asc::std::decay_t<F>, I>(
        ::asc::std::move(current), ::asc::std::forward<F>(function));
}

template <class D = ::asc::std::ptrdiff_t, class F, class Index = D,
    ::asc::std::enable_if_t<detail::iterator_detail::integer_v<Index> && detail::iterator_detail::stored_callable_v<F>,
        int> = 0>
CANN_ASC_STL_API constexpr tabulate_output_iterator<::asc::std::decay_t<F>, Index, D> make_tabulate_output_iterator(
    F&& function, Index first = 0,
    D position = 0) noexcept(::asc::std::is_nothrow_constructible_v<::asc::std::decay_t<F>, F>)
{
    return tabulate_output_iterator<::asc::std::decay_t<F>, Index, D>(
        ::asc::std::forward<F>(function), first, position);
}

template <class I, class In, class Out,
    ::asc::std::enable_if_t<detail::iterator_detail::valid_read<::asc::std::decay_t<In>, I>::value &&
            (detail::iterator_detail::navigation<I>::value >= 1) && detail::iterator_detail::stored_callable_v<In> &&
            detail::iterator_detail::stored_callable_v<Out>,
        int> = 0>
CANN_ASC_STL_API constexpr transform_input_output_iterator<::asc::std::decay_t<In>, ::asc::std::decay_t<Out>, I>
make_transform_input_output_iterator(I current, In&& input, Out&& output) noexcept(
    ::asc::std::is_nothrow_move_constructible_v<I> &&
    ::asc::std::is_nothrow_constructible_v<::asc::std::decay_t<In>, In> &&
    ::asc::std::is_nothrow_constructible_v<::asc::std::decay_t<Out>, Out>)
{
    return transform_input_output_iterator<::asc::std::decay_t<In>, ::asc::std::decay_t<Out>, I>(
        ::asc::std::move(current), ::asc::std::forward<In>(input), ::asc::std::forward<Out>(output));
}

template <class In, class Out, class I>
CANN_ASC_STL_API constexpr detail::iterator_detail::moved_reference<
    typename transform_input_output_iterator<In, Out, I>::reference::read_type>
iter_move(const transform_input_output_iterator<In, Out, I>& it) noexcept(noexcept(it.__read()))
{
    if constexpr (::asc::std::is_lvalue_reference_v<
                      typename transform_input_output_iterator<In, Out, I>::reference::read_type>) {
        // NOLINTNEXTLINE(build/include_what_you_use)
        return ::asc::std::move(it.__read());
    } else {
        return it.__read();
    }
}
template <class In, class Out, class I>
CANN_ASC_STL_API constexpr auto iter_swap(const transform_input_output_iterator<In, Out, I>& left,
    const transform_input_output_iterator<In, Out, I>& right) noexcept(noexcept(detail::iterator_detail::swap(*left,
    *right))) -> decltype(detail::iterator_detail::swap(*left, *right))
{
    return detail::iterator_detail::swap(*left, *right);
}

}  // namespace asc

namespace asc::std {

template <class I, class In, class Out, template <class> class TQual, template <class> class UQual>
struct basic_common_reference<::asc::detail::iterator_detail::io_proxy<I, In, Out>,
    typename ::asc::detail::iterator_detail::io_proxy<I, In, Out>::value_type, TQual, UQual> {
    using proxy = ::asc::detail::iterator_detail::io_proxy<I, In, Out>;
    using type = common_reference_t<typename proxy::read_type&&, UQual<typename proxy::value_type>>;
};
template <class I, class In, class Out, template <class> class TQual, template <class> class UQual>
struct basic_common_reference<typename ::asc::detail::iterator_detail::io_proxy<I, In, Out>::value_type,
    ::asc::detail::iterator_detail::io_proxy<I, In, Out>, TQual, UQual> {
    using proxy = ::asc::detail::iterator_detail::io_proxy<I, In, Out>;
    using type = common_reference_t<TQual<typename proxy::value_type>, typename proxy::read_type&&>;
};

}  // namespace asc::std

#endif  // CANN_ASC_STL_ASC___ITERATOR_OUTPUT_H
