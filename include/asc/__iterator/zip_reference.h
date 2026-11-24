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

#ifndef CANN_ASC_STL_ASC___ITERATOR_ZIP_REFERENCE_H
#define CANN_ASC_STL_ASC___ITERATOR_ZIP_REFERENCE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__iterator/output.h>

namespace asc::detail::iterator_detail {

using ::asc::std::get;

template <::asc::std::size_t N, class Tuple>
CANN_ASC_STL_API constexpr auto tuple_get(Tuple&& value) noexcept(
    noexcept(get<N>(::asc::std::forward<Tuple>(value)))) -> decltype(get<N>(::asc::std::forward<Tuple>(value)))
{
    return get<N>(::asc::std::forward<Tuple>(value));
}

template <class Tuple, class = void>
struct tuple_shape {
    static constexpr bool valid = false;
    static constexpr ::asc::std::size_t size = 0;
};
template <class Tuple>
struct tuple_shape<Tuple,
    ::asc::std::void_t<decltype(::asc::std::tuple_size<::asc::std::remove_cvref_t<Tuple>>::value)>> {
    static constexpr bool valid = true;
    static constexpr ::asc::std::size_t size = ::asc::std::tuple_size<::asc::std::remove_cvref_t<Tuple>>::value;
};

template <class Dest, class Source, class Sequence, class = void>
struct tuple_constructible : ::asc::std::false_type {};
template <class... R, class Source, ::asc::std::size_t... N>
struct tuple_constructible<::asc::std::tuple<R...>, Source, ::asc::std::index_sequence<N...>,
    ::asc::std::void_t<::asc::std::enable_if_t<tuple_shape<Source>::valid && tuple_shape<Source>::size == sizeof...(R)>,
        decltype(tuple_get<N>(::asc::std::declval<Source>()))...>>
    : ::asc::std::bool_constant<tuple_shape<Source>::valid && tuple_shape<Source>::size == sizeof...(R) &&
          (::asc::std::is_constructible_v<R, decltype(tuple_get<N>(::asc::std::declval<Source>()))> && ...)> {};

template <class Dest, class Source, class Sequence, class = void>
struct tuple_assignable : ::asc::std::false_type {};
template <class... R, class Source, ::asc::std::size_t... N>
struct tuple_assignable<::asc::std::tuple<R...>, Source, ::asc::std::index_sequence<N...>,
    ::asc::std::void_t<::asc::std::enable_if_t<tuple_shape<Source>::valid && tuple_shape<Source>::size == sizeof...(R)>,
        decltype(tuple_get<N>(::asc::std::declval<Source>()))...>>
    : ::asc::std::bool_constant<tuple_shape<Source>::valid && tuple_shape<Source>::size == sizeof...(R) &&
          (::asc::std::is_assignable_v<const R&, decltype(tuple_get<N>(::asc::std::declval<Source>()))> && ...)> {};

struct zip_init {};

template <class... R>
class zip_reference {
    using tuple_type = ::asc::std::tuple<R...>;
    using sequence = ::asc::std::index_sequence_for<R...>;
    tuple_type values_;

    template <class Tuple, ::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr zip_reference(Tuple&& value, ::asc::std::index_sequence<N...>) noexcept(
        (::asc::std::is_nothrow_constructible_v<R, decltype(tuple_get<N>(::asc::std::forward<Tuple>(value)))> && ...) &&
        (noexcept(tuple_get<N>(::asc::std::forward<Tuple>(value))) && ...))
        : values_(tuple_get<N>(::asc::std::forward<Tuple>(value))...)
    {}
    template <class Tuple, ::asc::std::size_t... N>
    CANN_ASC_STL_API constexpr void assign(Tuple&& value, ::asc::std::index_sequence<N...>) const
        noexcept((noexcept(::asc::std::get<N>(values_) = tuple_get<N>(::asc::std::forward<Tuple>(value))) && ...))
    {
        ((void)(::asc::std::get<N>(values_) = tuple_get<N>(::asc::std::forward<Tuple>(value))), ...);
    }
    template <class Target, class Self, ::asc::std::size_t... N>
    CANN_ASC_STL_API static constexpr Target convert(Self&& self, ::asc::std::index_sequence<N...>) noexcept(
        noexcept(Target(::asc::std::forward<Self>(self).template get<N>()...)))
    {
        return Target(::asc::std::forward<Self>(self).template get<N>()...);
    }

public:
    CANN_ASC_STL_API constexpr explicit zip_reference(zip_init, R... values) noexcept(
        (::asc::std::is_nothrow_constructible_v<R, R> && ...))
        : values_(::asc::std::forward<R>(values)...)
    {}
    CANN_ASC_STL_API constexpr zip_reference(const zip_reference&) = default;
    CANN_ASC_STL_API constexpr zip_reference(zip_reference&&) = default;
    template <class Tuple,
        ::asc::std::enable_if_t<!::asc::std::is_same_v<::asc::std::remove_cvref_t<Tuple>, zip_reference> &&
                tuple_constructible<tuple_type, Tuple, sequence>::value,
            int> = 0>
    CANN_ASC_STL_API constexpr zip_reference(Tuple&& value) noexcept(
        noexcept(zip_reference(::asc::std::forward<Tuple>(value), sequence{})))
        : zip_reference(::asc::std::forward<Tuple>(value), sequence{})
    {}

    template <::asc::std::size_t N>
    CANN_ASC_STL_API constexpr decltype(auto) get() & noexcept
    {
        return ::asc::std::get<N>(values_);
    }
    template <::asc::std::size_t N>
    CANN_ASC_STL_API constexpr decltype(auto) get() const& noexcept
    {
        return ::asc::std::get<N>(values_);
    }
    template <::asc::std::size_t N>
    CANN_ASC_STL_API constexpr decltype(auto) get() && noexcept
    {
        return static_cast<::asc::std::tuple_element_t<N, tuple_type>&&>(::asc::std::get<N>(values_));
    }
    template <::asc::std::size_t N>
    CANN_ASC_STL_API constexpr decltype(auto) get() const&& noexcept
    {
        return static_cast<::asc::std::add_const_t<::asc::std::tuple_element_t<N, tuple_type>>&&>(
            ::asc::std::get<N>(values_));
    }

    using copy_source = ::asc::std::conditional_t<(::asc::std::is_assignable_v<const R&, const R&> && ...),
        const zip_reference&, disabled_assignment>;
    CANN_ASC_STL_API constexpr const zip_reference& operator=(copy_source other) const
        noexcept((::asc::std::is_nothrow_assignable_v<const R&, const R&> && ...))
    {
        if constexpr ((::asc::std::is_assignable_v<const R&, const R&> && ...)) {
            assign(other, sequence{});
        }
        return *this;
    }
    template <class Tuple, ::asc::std::enable_if_t<tuple_assignable<tuple_type, Tuple, sequence>::value, int> = 0>
    CANN_ASC_STL_API constexpr const zip_reference& operator=(Tuple&& value) const
        noexcept(noexcept(assign(::asc::std::forward<Tuple>(value), sequence{})))
    {
        assign(::asc::std::forward<Tuple>(value), sequence{});
        return *this;
    }

    template <class... V,
        ::asc::std::enable_if_t<sizeof...(V) == sizeof...(R) && (::asc::std::is_constructible_v<V, const R&> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr operator ::asc::std::tuple<V...>() const& noexcept(
        (::asc::std::is_nothrow_constructible_v<V, const R&> && ...))
    {
        return convert<::asc::std::tuple<V...>>(*this, sequence{});
    }
    template <class... V,
        ::asc::std::enable_if_t<sizeof...(V) == sizeof...(R) && (::asc::std::is_constructible_v<V, R&&> && ...), int> =
            0>
    CANN_ASC_STL_API constexpr operator ::asc::std::tuple<V...>() && noexcept(
        (::asc::std::is_nothrow_constructible_v<V, R&&> && ...))
    {
        return convert<::asc::std::tuple<V...>>(::asc::std::move(*this), sequence{});
    }
};

template <::asc::std::size_t N, class... R>
CANN_ASC_STL_API constexpr decltype(auto) get(zip_reference<R...>& value) noexcept
{
    return value.template get<N>();
}
template <::asc::std::size_t N, class... R>
CANN_ASC_STL_API constexpr decltype(auto) get(const zip_reference<R...>& value) noexcept
{
    return value.template get<N>();
}
template <::asc::std::size_t N, class... R>
CANN_ASC_STL_API constexpr decltype(auto) get(zip_reference<R...>&& value) noexcept
{
    return ::asc::std::move(value).template get<N>();
}
template <::asc::std::size_t N, class... R>
CANN_ASC_STL_API constexpr decltype(auto) get(const zip_reference<R...>&& value) noexcept
{
    return ::asc::std::move(value).template get<N>();
}

template <class Left, class Right, class Sequence, class = void>
struct zip_common {};
template <class Left, class Right, ::asc::std::size_t... N>
struct zip_common<Left, Right, ::asc::std::index_sequence<N...>,
    ::asc::std::void_t<::asc::std::common_reference_t<decltype(tuple_get<N>(::asc::std::declval<Left>())),
        decltype(tuple_get<N>(::asc::std::declval<Right>()))>...>> {
    using type = zip_reference<::asc::std::common_reference_t<decltype(tuple_get<N>(::asc::std::declval<Left>())),
        decltype(tuple_get<N>(::asc::std::declval<Right>()))>...>;
};

template <class Left, class Right, class Sequence, class = void>
struct zip_swappable : ::asc::std::false_type {};
template <class Left, class Right, ::asc::std::size_t... N>
struct zip_swappable<Left, Right, ::asc::std::index_sequence<N...>,
    ::asc::std::void_t<decltype(::asc::std::ranges::swap(tuple_get<N>(::asc::std::declval<Left>()),
        tuple_get<N>(::asc::std::declval<Right>())))...>> : ::asc::std::true_type {};
template <class Left, class Right, ::asc::std::size_t... N>
CANN_ASC_STL_API constexpr void swap_zip(Left&& left, Right&& right, ::asc::std::index_sequence<N...>) noexcept(
    (noexcept(::asc::std::ranges::swap(tuple_get<N>(left), tuple_get<N>(right))) && ...))
{
    (::asc::std::ranges::swap(tuple_get<N>(left), tuple_get<N>(right)), ...);
}
template <class... R, class... S,
    ::asc::std::enable_if_t<sizeof...(R) == sizeof...(S) &&
            zip_swappable<const zip_reference<R...>&, const zip_reference<S...>&,
                ::asc::std::index_sequence_for<R...>>::value,
        int> = 0>
// NOLINTNEXTLINE(build/include_what_you_use)
CANN_ASC_STL_API constexpr void swap(const zip_reference<R...>& left, const zip_reference<S...>& right) noexcept(
    noexcept(swap_zip(left, right, ::asc::std::index_sequence_for<R...>{})))
{
    swap_zip(left, right, ::asc::std::index_sequence_for<R...>{});
}

}  // namespace asc::detail::iterator_detail

namespace asc::std {

template <class... R>
struct tuple_size<::asc::detail::iterator_detail::zip_reference<R...>> : integral_constant<size_t, sizeof...(R)> {};
template <size_t N, class... R>
struct tuple_element<N, ::asc::detail::iterator_detail::zip_reference<R...>> : tuple_element<N, tuple<R...>> {};
template <class... R, class... V, template <class> class TQual, template <class> class UQual>
struct basic_common_reference<::asc::detail::iterator_detail::zip_reference<R...>, tuple<V...>, TQual, UQual>
    : ::asc::detail::iterator_detail::zip_common<TQual<::asc::detail::iterator_detail::zip_reference<R...>>,
          UQual<tuple<V...>>, index_sequence_for<R...>> {};
template <class... R, class... V, template <class> class TQual, template <class> class UQual>
struct basic_common_reference<tuple<V...>, ::asc::detail::iterator_detail::zip_reference<R...>, TQual, UQual>
    // NOLINTNEXTLINE(build/include_what_you_use)
    : ::asc::detail::iterator_detail::zip_common<TQual<tuple<V...>>,
          UQual<::asc::detail::iterator_detail::zip_reference<R...>>, index_sequence_for<R...>> {};
template <class... R, class... S, template <class> class TQual, template <class> class UQual>
struct basic_common_reference<::asc::detail::iterator_detail::zip_reference<R...>,
    ::asc::detail::iterator_detail::zip_reference<S...>, TQual, UQual>
    : ::asc::detail::iterator_detail::zip_common<TQual<::asc::detail::iterator_detail::zip_reference<R...>>,
          UQual<::asc::detail::iterator_detail::zip_reference<S...>>, index_sequence_for<R...>> {};

}  // namespace asc::std

namespace std {

template <class... R>
struct tuple_size<::asc::detail::iterator_detail::zip_reference<R...>>
    : ::asc::std::integral_constant<::asc::std::size_t, sizeof...(R)> {};
template <::asc::std::size_t N, class... R>
struct tuple_element<N, ::asc::detail::iterator_detail::zip_reference<R...>>
    : ::asc::std::tuple_element<N, ::asc::std::tuple<R...>> {};

}  // namespace std

#endif  // CANN_ASC_STL_ASC___ITERATOR_ZIP_REFERENCE_H
