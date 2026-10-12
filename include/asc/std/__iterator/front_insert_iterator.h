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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_FRONT_INSERT_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_FRONT_INSERT_ITERATOR_H

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
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/move.h>
#include <asc/std/cstddef>

// Migrated from dev __asc/dialect.h: base asc/__config has no standard-version
// number macro, so key it on CANN_ASC_STL_DETAIL_CPLUSPLUS instead.
#ifndef CANN_ASC_STL_DETAIL_STD_VER
#if CANN_ASC_STL_DETAIL_CPLUSPLUS <= 199711L
#define CANN_ASC_STL_DETAIL_STD_VER 2003
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201103L
#define CANN_ASC_STL_DETAIL_STD_VER 2011
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201402L
#define CANN_ASC_STL_DETAIL_STD_VER 2014
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201703L
#define CANN_ASC_STL_DETAIL_STD_VER 2017
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202002L
#define CANN_ASC_STL_DETAIL_STD_VER 2020
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202302L
#define CANN_ASC_STL_DETAIL_STD_VER 2023
#else
#define CANN_ASC_STL_DETAIL_STD_VER 2024
#endif
#endif  // CANN_ASC_STL_DETAIL_STD_VER

CANN_ASC_STL_BEGIN_NAMESPACE

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

    CANN_ASC_STL_API constexpr front_insert_iterator& operator*() noexcept
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
CANN_ASC_STL_DETAIL_CTAD_SUPPORTED_FOR_TYPE(front_insert_iterator);

template <class _Container>
CANN_ASC_STL_API constexpr front_insert_iterator<_Container> front_inserter(_Container& __x) noexcept
{
    return front_insert_iterator<_Container>(__x);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_FRONT_INSERT_ITERATOR_H
