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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_FRONT_INSERT_ITERATOR_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_FRONT_INSERT_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/iterator.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/move.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
template <class _Container>
class front_insert_iterator {
protected:
    _Container* container;

public:
    using iterator_category = output_iterator_tag;
    using value_type = void;
#if CANN_ASC_STL_DETAIL_STD_VER > 2017
    using difference_type = ptrdiff_t;
#else
    using difference_type = void;
#endif
    using pointer = void;
    using reference = void;
    using container_type = _Container;

    CANN_ASC_STL_API constexpr explicit front_insert_iterator(_Container& __x) noexcept
        : container(::asc::std::addressof(__x))
    {}

    CANN_ASC_STL_API constexpr front_insert_iterator& operator=(const typename _Container::value_type& __value)
    {
        container->push_front(__value);
        return *this;
    }

    CANN_ASC_STL_API constexpr front_insert_iterator& operator=(typename _Container::value_type&& __value)
    {
        container->push_front(::asc::std::move(__value));  // NOLINT(build/include_what_you_use)
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr front_insert_iterator& operator*() noexcept
    {
        return *this;
    }

    CANN_ASC_STL_API constexpr front_insert_iterator& operator++() noexcept
    {
        return *this;
    }

    CANN_ASC_STL_API constexpr front_insert_iterator operator++(int) noexcept
    {
        return *this;
    }
};
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(front_insert_iterator);

template <class _Container>
[[nodiscard]] CANN_ASC_STL_API constexpr front_insert_iterator<_Container> front_inserter(_Container& __x) noexcept
{
    return front_insert_iterator<_Container>(__x);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_FRONT_INSERT_ITERATOR_H
