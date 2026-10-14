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

#ifndef CANN_ASC_STL_ASC___ITERATOR_ADAPTORS_H
#define CANN_ASC_STL_ASC___ITERATOR_ADAPTORS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {

// Index-bound adaptor state.  Status: the lazy iterator adaptors of the
// public <asc/iterator> facade each carry their own state members and do not
// share this base; it stays delivered because the semantics suite
// (test/support/b024_semantics.h) pins it, and it remains the designated
// shared base (the dev-side zip_common.h pattern) should the facade adaptors
// ever be consolidated onto one implementation.  Removing the file or
// rewiring the facade onto it is a product decision.  An adaptor borrows its
// source position and exposes only the offset arithmetic, so no lazy view
// owns the underlying range.
template <class Source>
struct iterator_adaptor_state {
    Source source;
    __PTRDIFF_TYPE__ offset;

    CANN_ASC_STL_API constexpr iterator_adaptor_state() noexcept : source(), offset(0)
    {}
    CANN_ASC_STL_API constexpr explicit iterator_adaptor_state(Source source_position) noexcept
        : source(source_position), offset(0)
    {}
    CANN_ASC_STL_API constexpr iterator_adaptor_state(Source source_position, __PTRDIFF_TYPE__ start_offset) noexcept
        : source(source_position), offset(start_offset)
    {}

    CANN_ASC_STL_API constexpr Source advanced(__PTRDIFF_TYPE__ delta) const noexcept
    {
        return source + (offset + delta);
    }
};

// Sentinel distance helper for adaptors paired with a counted bound.
CANN_ASC_STL_API constexpr __PTRDIFF_TYPE__ adaptor_remaining(
    __PTRDIFF_TYPE__ position, __PTRDIFF_TYPE__ bound) noexcept
{
    return position < bound ? bound - position : 0;
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___ITERATOR_ADAPTORS_H
