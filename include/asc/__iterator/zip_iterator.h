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

#ifndef CANN_ASC_STL_ASC___ITERATOR_ZIP_ITERATOR_H
#define CANN_ASC_STL_ASC___ITERATOR_ZIP_ITERATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__iterator/zip_reference.h>

namespace asc::detail::iterator_detail {

template <class I>
using zip_component = ::asc::std::conditional_t<readable<I>::value, ::asc::std::iter_reference_t<I>, output_target<I>>;
template <class I>
CANN_ASC_STL_API constexpr bool component_nothrow() noexcept
{
    if constexpr (readable<I>::value) {
        return noexcept(*::asc::std::declval<const I&>());
    } else {
        return ::asc::std::is_nothrow_copy_constructible_v<I> && ::asc::std::is_nothrow_move_constructible_v<I>;
    }
}
template <class I>
CANN_ASC_STL_API constexpr zip_component<I> read_component(const I& current) noexcept(component_nothrow<I>())
{
    if constexpr (readable<I>::value) {
        return *current;
    } else {
        return output_target<I>(current);
    }
}
template <bool Readable, class... I>
struct zip_value {
    using type = void;
};
template <class... I>
struct zip_value<true, I...> {
    using type = ::asc::std::tuple<::asc::std::iter_value_t<I>...>;
};
template <int... Ranks>
struct minimum_rank;
template <>
struct minimum_rank<> : ::asc::std::integral_constant<int, 3> {};
template <int First, int... Rest>
struct minimum_rank<First, Rest...>
    : ::asc::std::integral_constant<int,
          (First < minimum_rank<Rest...>::value ? First : minimum_rank<Rest...>::value)> {};
template <class... I>
using zip_rank = minimum_rank<navigation<I>::value...>;

template <class R>
struct postfix_write {
    R value;
    CANN_ASC_STL_API constexpr R operator*() && noexcept(::asc::std::is_nothrow_move_constructible_v<R>)
    {
        return ::asc::std::move(value);
    }
};

}  // namespace asc::detail::iterator_detail

namespace asc {

template <class... Iterators>
class zip_iterator : public detail::iterator_detail::position_facade<zip_iterator<Iterators...>,
                         ::asc::std::common_type_t<detail::iterator_detail::difference_t<Iterators>...>> {
    static_assert(sizeof...(Iterators) > 0, "zip_iterator requires at least one component");
    template <class...>
    friend class zip_iterator;
    using tuple_type = ::asc::std::tuple<Iterators...>;
    using sequence = ::asc::std::index_sequence_for<Iterators...>;
    detail::iterator_detail::state_box<tuple_type> current_;

public:
    static constexpr bool __iterator_readable = (detail::iterator_detail::readable<Iterators>::value && ...);
    static constexpr int __iterator_rank = detail::iterator_detail::zip_rank<Iterators...>::value;
    static constexpr bool __iterator_equality = (detail::iterator_detail::equality<Iterators>::value && ...);
    using value_type = typename detail::iterator_detail::zip_value<__iterator_readable, Iterators...>::type;
    using reference = detail::iterator_detail::zip_reference<detail::iterator_detail::zip_component<Iterators>...>;
    using difference_type = ::asc::std::common_type_t<detail::iterator_detail::difference_t<Iterators>...>;
    using pointer = void;
    using iterator_category =
        ::asc::std::conditional_t<__iterator_readable, ::asc::std::input_iterator_tag, ::asc::std::output_iterator_tag>;
    using iterator_concept = ::asc::std::conditional_t<__iterator_readable,
        detail::iterator_detail::navigation_tag<__iterator_rank>, ::asc::std::output_iterator_tag>;
    static_assert(detail::iterator_detail::integer_v<difference_type> && ::asc::std::is_signed_v<difference_type>);
    CANN_ASC_STL_API constexpr zip_iterator() noexcept = default;
    CANN_ASC_STL_API constexpr explicit zip_iterator(Iterators... current) noexcept(
        (::asc::std::is_nothrow_move_constructible_v<Iterators> && ...))
        : current_(::asc::std::in_place, tuple_type(::asc::std::move(current)...))
    {}
    template <class... J,
        ::asc::std::enable_if_t<sizeof...(J) == sizeof...(Iterators) &&
                (::asc::std::is_convertible_v<const J&, Iterators> && ...) &&
                ::asc::std::is_same_v<difference_type,
                    ::asc::std::common_type_t<detail::iterator_detail::difference_t<J>...>>,
            int> = 0>
    CANN_ASC_STL_API constexpr zip_iterator(const zip_iterator<J...>& other) noexcept(
        (::asc::std::is_nothrow_constructible_v<Iterators, const J&> && ...) &&
        (::asc::std::is_nothrow_move_constructible_v<Iterators> && ...))
        : current_(other.__is_bound() ? convert(other.current_.get(), sequence{}) :
                                        detail::iterator_detail::state_box<tuple_type>())
    {}
    CANN_ASC_STL_API constexpr bool __is_bound() const noexcept
    {
        return current_.bound();
    }
    CANN_ASC_STL_API constexpr tuple_type base() const noexcept(::asc::std::is_nothrow_copy_constructible_v<tuple_type>)
    {
        return current_.get();
    }
    CANN_ASC_STL_API constexpr reference operator*() const noexcept(noexcept(dereference(sequence{})))
    {
        detail::iterator_detail::require(__is_bound());
        return dereference(sequence{});
    }
    CANN_ASC_STL_API constexpr reference __at(difference_type n) const noexcept(noexcept(at(n, sequence{})))
    {
        return at(n, sequence{});
    }
    CANN_ASC_STL_API constexpr void __increment() noexcept((noexcept(++::asc::std::declval<Iterators&>()) && ...))
    {
        detail::iterator_detail::require(__is_bound());
        increment(sequence{});
    }
    CANN_ASC_STL_API constexpr void __decrement() noexcept((noexcept(--::asc::std::declval<Iterators&>()) && ...))
    {
        decrement(sequence{});
    }
    CANN_ASC_STL_API constexpr void __advance(difference_type n) noexcept(
        (noexcept(::asc::std::declval<Iterators&>() +=
             ::asc::std::declval<detail::iterator_detail::difference_t<Iterators>>()) &&
            ...))
    {
        advance(n, sequence{});
    }
    CANN_ASC_STL_API constexpr void __retreat(difference_type n) noexcept(
        (noexcept(::asc::std::declval<Iterators&>() -=
             ::asc::std::declval<detail::iterator_detail::difference_t<Iterators>>()) &&
            ...))
    {
        retreat(n, sequence{});
    }
    CANN_ASC_STL_API constexpr bool __equal(const zip_iterator& other) const noexcept(
        (noexcept(
             static_cast<bool>(::asc::std::declval<const Iterators&>() == ::asc::std::declval<const Iterators&>())) &&
            ...))
    {
        return equal(other, sequence{});
    }
    CANN_ASC_STL_API constexpr difference_type __distance(const zip_iterator& other) const
        noexcept((noexcept(::asc::std::declval<const Iterators&>() - ::asc::std::declval<const Iterators&>()) && ...))
    {
        const difference_type distance = ::asc::std::get<0>(current_.get()) - ::asc::std::get<0>(other.current_.get());
        detail::iterator_detail::require(distances_equal(other, distance, sequence{}));
        return distance;
    }
    CANN_ASC_STL_API constexpr bool __less(const zip_iterator& other) const noexcept(noexcept(__distance(other)))
    {
        return __distance(other) < 0;
    }
    CANN_ASC_STL_API constexpr auto __postfix() noexcept(
        (__iterator_readable || __iterator_rank >= 1) && detail::iterator_detail::read_postfix_nothrow<zip_iterator>())
    {
        if constexpr (__iterator_rank >= 1 || __iterator_readable) {
            return detail::iterator_detail::read_postfix(*this);
        } else {
            return output_postfix(sequence{});
        }
    }
    template <bool Read = __iterator_readable, ::asc::std::enable_if_t<Read, int> = 0>
    CANN_ASC_STL_API constexpr auto __move() const noexcept(noexcept(move_values(sequence{})))
    {
        return move_values(sequence{});
    }

private:
    template <class Tuple, ::asc::std::size_t... N>
    CANN_ASC_STL_API static constexpr detail::iterator_detail::state_box<tuple_type> convert(
        const Tuple& source, ::asc::std::index_sequence<N...>)
    {
        return detail::iterator_detail::state_box<tuple_type>(
            ::asc::std::in_place, tuple_type(::asc::std::get<N>(source)...));
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr reference dereference(::asc::std::index_sequence<N...>) const
        noexcept(noexcept(reference{detail::iterator_detail::zip_init{},
            detail::iterator_detail::read_component(::asc::std::get<N>(current_.get()))...}))
    {
        return reference{detail::iterator_detail::zip_init{},
            detail::iterator_detail::read_component(::asc::std::get<N>(current_.get()))...};
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr reference at(difference_type n, ::asc::std::index_sequence<N...>) const
        noexcept(noexcept(reference{detail::iterator_detail::zip_init{},
            detail::iterator_detail::read_component(::asc::std::get<N>(current_.get()) +
                detail::iterator_detail::offset_value(detail::iterator_detail::difference_t<Iterators>{0}, n))...}))
    {
        return reference{detail::iterator_detail::zip_init{},
            detail::iterator_detail::read_component(::asc::std::get<N>(current_.get()) +
                detail::iterator_detail::offset_value(detail::iterator_detail::difference_t<Iterators>{0}, n))...};
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr void increment(::asc::std::index_sequence<N...>)
    {
        ((void)++::asc::std::get<N>(current_.get()), ...);
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr void decrement(::asc::std::index_sequence<N...>)
    {
        ((void)--::asc::std::get<N>(current_.get()), ...);
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr void advance(difference_type n, ::asc::std::index_sequence<N...>)
    {
        ((void)(::asc::std::get<N>(current_.get()) +=
             detail::iterator_detail::offset_value(detail::iterator_detail::difference_t<Iterators>{0}, n)),
            ...);
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr void retreat(difference_type n, ::asc::std::index_sequence<N...>)
    {
        ((void)(::asc::std::get<N>(current_.get()) -=
             detail::iterator_detail::offset_value(detail::iterator_detail::difference_t<Iterators>{0}, n)),
            ...);
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr bool equal(const zip_iterator& other, ::asc::std::index_sequence<N...>) const
    {
        return (
            static_cast<bool>(::asc::std::get<N>(current_.get()) == ::asc::std::get<N>(other.current_.get())) && ...);
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr bool distances_equal(
        const zip_iterator& other, difference_type distance, ::asc::std::index_sequence<N...>) const
    {
        return ((::asc::std::get<N>(current_.get()) - ::asc::std::get<N>(other.current_.get()) == distance) && ...);
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr auto output_postfix(::asc::std::index_sequence<N...>)
    {
        using R = detail::iterator_detail::zip_reference<
            detail::iterator_detail::output_target<decltype(::asc::std::declval<Iterators&>()++)>...>;
        return detail::iterator_detail::postfix_write<R>{R{detail::iterator_detail::zip_init{},
            detail::iterator_detail::output_target<decltype(::asc::std::declval<Iterators&>()++)>(
                ::asc::std::get<N>(current_.get())++)...}};
    }
    template <::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr auto move_values(::asc::std::index_sequence<N...>) const
        noexcept(noexcept(detail::iterator_detail::zip_reference<::asc::std::iter_rvalue_reference_t<Iterators>...>{
            detail::iterator_detail::zip_init{}, ::asc::std::iter_move(::asc::std::get<N>(current_.get()))...}))
    {
        using R = detail::iterator_detail::zip_reference<::asc::std::iter_rvalue_reference_t<Iterators>...>;
        return R{detail::iterator_detail::zip_init{}, ::asc::std::iter_move(::asc::std::get<N>(current_.get()))...};
    }
};

template <class... I, ::asc::std::enable_if_t<(sizeof...(I) > 0), int> = 0>
CANN_ASC_STL_API constexpr zip_iterator<I...> make_zip_iterator(I... current) noexcept(
    (::asc::std::is_nothrow_move_constructible_v<I> && ...))
{
    // NOLINTNEXTLINE(build/include_what_you_use)
    return zip_iterator<I...>(::asc::std::move(current)...);
}
template <class... I, ::asc::std::enable_if_t<(detail::iterator_detail::readable<I>::value && ...), int> = 0>
CANN_ASC_STL_API constexpr auto iter_move(const zip_iterator<I...>& it) noexcept(
    noexcept(it.__move())) -> decltype(it.__move())
{
    return it.__move();
}

namespace detail::iterator_detail {
template <class... I, ::asc::std::size_t... N>
CANN_ASC_STL_API constexpr auto zip_iter_swap(const ::asc::std::tuple<I...>& left, const ::asc::std::tuple<I...>& right,
    ::asc::std::index_sequence<N...>) noexcept((noexcept(::asc::std::ranges::iter_swap(::asc::std::get<N>(left),
                                                    ::asc::std::get<N>(right))) &&
    ...)) -> ::asc::std::void_t<decltype(::asc::std::ranges::iter_swap(::asc::std::get<N>(left),
              ::asc::std::get<N>(right)))...>
{
    (::asc::std::ranges::iter_swap(::asc::std::get<N>(left), ::asc::std::get<N>(right)), ...);
}
}  // namespace detail::iterator_detail

template <class... I>
CANN_ASC_STL_API constexpr auto iter_swap(const zip_iterator<I...>& left, const zip_iterator<I...>& right) noexcept(
    noexcept(detail::iterator_detail::zip_iter_swap(left.base(), right.base(),
        ::asc::std::index_sequence_for<I...>{}))) -> decltype(detail::iterator_detail::zip_iter_swap(left.base(),
                                                      right.base(), ::asc::std::index_sequence_for<I...>{}))
{
    return detail::iterator_detail::zip_iter_swap(left.base(), right.base(), ::asc::std::index_sequence_for<I...>{});
}

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___ITERATOR_ZIP_ITERATOR_H
