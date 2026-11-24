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

#ifndef CANN_ASC_STL_ASC___ITERATOR_ZIP_FUNCTION_H
#define CANN_ASC_STL_ASC___ITERATOR_ZIP_FUNCTION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__iterator/zip_iterator.h>

namespace asc {

template <class Function>
class zip_function {
    Function function_;
    template <class Self, class Tuple, ::asc::std::size_t... N>
    CANN_ASC_STL_API static constexpr auto call(Self&& self, Tuple&& tuple, ::asc::std::index_sequence<N...>) noexcept(
        noexcept(::asc::std::invoke(::asc::std::forward<Self>(self).function_,
            detail::iterator_detail::tuple_get<N>(::asc::std::forward<Tuple>(tuple))...)))
        -> decltype(::asc::std::invoke(::asc::std::forward<Self>(self).function_,
            detail::iterator_detail::tuple_get<N>(::asc::std::forward<Tuple>(tuple))...))
    {
        return ::asc::std::invoke(::asc::std::forward<Self>(self).function_,
            detail::iterator_detail::tuple_get<N>(::asc::std::forward<Tuple>(tuple))...);
    }

public:
    CANN_ASC_STL_API constexpr zip_function() = default;
    template <class F,
        ::asc::std::enable_if_t<!::asc::std::is_same_v<::asc::std::remove_cvref_t<F>, zip_function> &&
                ::asc::std::is_constructible_v<Function, F>,
            int> = 0>
    CANN_ASC_STL_API constexpr explicit zip_function(F&& function) noexcept(
        ::asc::std::is_nothrow_constructible_v<Function, F>)
        : function_(::asc::std::forward<F>(function))
    {}
    template <class Tuple, ::asc::std::enable_if_t<detail::iterator_detail::tuple_shape<Tuple>::valid, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Tuple&& tuple) & noexcept(
        noexcept(call(*this, ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{})))
        -> decltype(call(*this, ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{}))
    {
        return call(*this, ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{});
    }
    template <class Tuple, ::asc::std::enable_if_t<detail::iterator_detail::tuple_shape<Tuple>::valid, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Tuple&& tuple) const& noexcept(
        noexcept(call(*this, ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{})))
        -> decltype(call(*this, ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{}))
    {
        return call(*this, ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{});
    }
    template <class Tuple, ::asc::std::enable_if_t<detail::iterator_detail::tuple_shape<Tuple>::valid, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Tuple&& tuple) && noexcept(
        noexcept(call(::asc::std::move(*this), ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{})))
        -> decltype(call(::asc::std::move(*this), ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{}))
    {
        return call(::asc::std::move(*this), ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{});
    }
    template <class Tuple, ::asc::std::enable_if_t<detail::iterator_detail::tuple_shape<Tuple>::valid, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(Tuple&& tuple) const&& noexcept(
        noexcept(call(::asc::std::move(*this), ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{})))
        -> decltype(call(::asc::std::move(*this), ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{}))
    {
        return call(::asc::std::move(*this), ::asc::std::forward<Tuple>(tuple),
            ::asc::std::make_index_sequence<detail::iterator_detail::tuple_shape<Tuple>::size>{});
    }
};

template <class F, ::asc::std::enable_if_t<::asc::std::is_constructible_v<::asc::std::decay_t<F>, F>, int> = 0>
CANN_ASC_STL_API constexpr zip_function<::asc::std::decay_t<F>> make_zip_function(F&& function) noexcept(
    ::asc::std::is_nothrow_constructible_v<::asc::std::decay_t<F>, F>)
{
    return zip_function<::asc::std::decay_t<F>>(::asc::std::forward<F>(function));
}
template <class Function, class... Iterators>
using zip_transform_iterator = transform_iterator<zip_function<Function>, zip_iterator<Iterators...>>;

template <class F, class... I,
    ::asc::std::enable_if_t<(detail::iterator_detail::readable<I>::value && ...) &&
            detail::iterator_detail::valid_read<zip_function<::asc::std::decay_t<F>>, zip_iterator<I...>>::value,
        int> = 0>
CANN_ASC_STL_API constexpr zip_transform_iterator<::asc::std::decay_t<F>, I...> make_zip_transform_iterator(
    F&& function,
    I... current) noexcept(noexcept(make_transform_iterator(make_zip_iterator(::asc::std::move(current)...),
    make_zip_function(::asc::std::forward<F>(function)))))
{
    return make_transform_iterator(
        // NOLINTNEXTLINE(build/include_what_you_use)
        make_zip_iterator(::asc::std::move(current)...), make_zip_function(::asc::std::forward<F>(function)));
}
}  // namespace asc

#endif  // CANN_ASC_STL_ASC___ITERATOR_ZIP_FUNCTION_H
