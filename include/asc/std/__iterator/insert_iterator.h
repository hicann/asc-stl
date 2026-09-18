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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_INSERT_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_INSERT_ITERATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/iterator.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__utility/move.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Container>
using __insert_iterator_iter_t = typename Container::iterator;
template <class Container>
class insert_iterator {
public:
    using iterator_category = output_iterator_tag;
    using value_type = void;
    using difference_type = ptrdiff_t;
    using pointer = void;
    using reference = void;
    using container_type = Container;
    CANN_ASC_STL_API constexpr insert_iterator(Container& container, __insert_iterator_iter_t<Container> iterator)
        : container_(::asc::std::addressof(container)), iterator_(iterator)
    {}
    CANN_ASC_STL_API constexpr insert_iterator& operator=(const typename Container::value_type& value)
    {
        iterator_ = container_->insert(iterator_, value);
        ++iterator_;
        return *this;
    }
    CANN_ASC_STL_API constexpr insert_iterator& operator=(typename Container::value_type&& value)
    {
        iterator_ = container_->insert(iterator_, ::asc::std::move(value));  // NOLINT(build/include_what_you_use)
        ++iterator_;
        return *this;
    }
    CANN_ASC_STL_API constexpr insert_iterator& operator*() noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API constexpr insert_iterator& operator++() noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API constexpr insert_iterator& operator++(int) noexcept
    {
        return *this;
    }

protected:
    Container* container_;
    __insert_iterator_iter_t<Container> iterator_;
};
template <class Container>
CANN_ASC_STL_API constexpr insert_iterator<Container> inserter(
    Container& container, __insert_iterator_iter_t<Container> iterator)
{
    return insert_iterator<Container>(container, iterator);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_INSERT_ITERATOR_H
