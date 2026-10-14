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

#ifndef CANN_ASC_STL_ASC___UTILITY_STATIC_FOR_H
#define CANN_ASC_STL_ASC___UTILITY_STATIC_FOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Compile-time iteration backend for the later public <asc/utility> facade.
// Every invocation is generated at compile time and receives its index as a
// lightweight integral_constant, so no kernel launch and no runtime loop
// scheduling is involved. A Device-side callable must carry the
// execution-space attributes of its calling domain: an ordinary AICore body
// cannot call a Host-only function object. Index-sequence generation uses the
// two compiler-provided spellings directly: CCE requires __make_integer_seq
// with angle brackets and GCC provides __integer_pack; neither is emulated.
namespace asc::detail {

template <class IndexType, IndexType Value>
struct static_for_index {
    using value_type = IndexType;
    static constexpr IndexType value = Value;
    CANN_ASC_STL_API constexpr operator IndexType() const noexcept
    {
        return Value;
    }
};

template <class IndexType, IndexType... Values>
struct static_for_sequence {};

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__make_integer_seq)

template <class IndexType, IndexType Size>
using static_for_make = __make_integer_seq<static_for_sequence, IndexType, Size>;

#elif CANN_ASC_STL_DETAIL_HAS_BUILTIN(__integer_pack)

template <class IndexType, IndexType Size>
using static_for_make = static_for_sequence<IndexType, __integer_pack(Size)...>;

#else

#error "ASC-STL static_for requires __make_integer_seq or __integer_pack support"

#endif

template <class Callable, class IndexType, IndexType... Values, class... Args>
CANN_ASC_STL_API constexpr void static_for_invoke(
    Callable&& callable, static_for_sequence<IndexType, Values...>, Args&&... args) noexcept((true && ... &&
    noexcept(static_cast<Callable&&>(callable)(static_for_index<IndexType, Values>{}, static_cast<Args&&>(args)...))))
{
    (static_cast<Callable&&>(callable)(static_for_index<IndexType, Values>{}, static_cast<Args&&>(args)...), ...);
}

template <class Callable, class IndexType, IndexType Offset, IndexType Step, IndexType... Values, class... Args>
CANN_ASC_STL_API constexpr void static_for_strided(
    Callable&& callable, static_for_sequence<IndexType, Values...>, Args&&... args) noexcept((true && ... &&
    noexcept(static_cast<Callable&&>(callable)(
        static_for_index<IndexType, Offset + Values * Step>{}, static_cast<Args&&>(args)...))))
{
    (static_cast<Callable&&>(callable)(
         static_for_index<IndexType, Offset + Values * Step>{}, static_cast<Args&&>(args)...),
        ...);
}

// Zero-based count form: [0, Size).
template <class IndexType, IndexType Size, class Callable, class... Args>
CANN_ASC_STL_API constexpr void static_for_count(Callable&& callable, Args&&... args) noexcept(
    noexcept(static_for_invoke(
        static_cast<Callable&&>(callable), static_for_make<IndexType, Size>{}, static_cast<Args&&>(args)...)))
{
    if constexpr (Size > 0) {
        static_for_invoke(
            static_cast<Callable&&>(callable), static_for_make<IndexType, Size>{}, static_cast<Args&&>(args)...);
    }
}

// Half-open range form: [Start, End) with an explicit nonzero step.
template <class IndexType, IndexType Start, IndexType End, IndexType Step, class Callable, class... Args>
CANN_ASC_STL_API constexpr void static_for_range(Callable&& callable, Args&&... args) noexcept(
    noexcept(static_for_strided<Callable, IndexType, Start, Step>(
        static_cast<Callable&&>(callable), static_for_make<IndexType, 0>{}, static_cast<Args&&>(args)...)))
{
    static_assert(Step != 0, "static_for step must be nonzero");
    if constexpr ((Step > 0 && Start < End) || (Step < 0 && Start > End)) {
        constexpr IndexType span = Step > 0 ? End - Start : Start - End;
        constexpr IndexType magnitude = Step > 0 ? Step : -Step;
        constexpr IndexType count = (span + magnitude - 1) / magnitude;
        static_for_strided<Callable, IndexType, Start, Step>(
            static_cast<Callable&&>(callable), static_for_make<IndexType, count>{}, static_cast<Args&&>(args)...);
    }
}

// Auto non-type-template-parameter convenience form with one shared index
// type; the facade spells the public overloads over this backend.
template <auto Start, auto End, auto Step, class Callable>
CANN_ASC_STL_API constexpr void static_for_auto(Callable&& callable)
{
    using IndexType = decltype(Start);
    static_for_range<IndexType, static_cast<IndexType>(Start), static_cast<IndexType>(End),
        static_cast<IndexType>(Step)>(static_cast<Callable&&>(callable));
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___UTILITY_STATIC_FOR_H
