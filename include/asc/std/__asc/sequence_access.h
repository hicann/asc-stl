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

#ifndef CANN_ASC_STL_STD_DETAIL_SEQUENCE_ACCESS_H
#define CANN_ASC_STL_STD_DETAIL_SEQUENCE_ACCESS_H

#include <asc/std/__asc/system_header.h>
#include <asc/std/__asc/visibility.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// {cr,r,}{begin,end} of ASC-STL containers are hidden friends to avoid
// ADL ambiguities. The macros below synthesize those friends with the ASC API
// annotation.
//
// Bisheng diagnoses a member access in a conditional noexcept expression while
// the containing class is still incomplete. ASC-STL containers require these
// accessors to be noexcept, so CCE uses that contract directly; host compilers
// evaluate the conditional noexcept expression.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(_EXPR) noexcept
#else
#define CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(_EXPR) noexcept(noexcept(_EXPR))
#endif

#define CANN_ASC_STL_DETAIL_SYNTHESIZE_SEQUENCE_ACCESS(_ClassName, _ConstIter)            \
    [[nodiscard]] CANN_ASC_STL_API friend iterator begin(_ClassName& __sequence)          \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.begin())                  \
    {                                                                                     \
        return __sequence.begin();                                                        \
    }                                                                                     \
    [[nodiscard]] CANN_ASC_STL_API friend _ConstIter begin(const _ClassName& __sequence)  \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.begin())                  \
    {                                                                                     \
        return __sequence.begin();                                                        \
    }                                                                                     \
    [[nodiscard]] CANN_ASC_STL_API friend iterator end(_ClassName& __sequence)            \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.end())                    \
    {                                                                                     \
        return __sequence.end();                                                          \
    }                                                                                     \
    [[nodiscard]] CANN_ASC_STL_API friend _ConstIter end(const _ClassName& __sequence)    \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.end())                    \
    {                                                                                     \
        return __sequence.end();                                                          \
    }                                                                                     \
    [[nodiscard]] CANN_ASC_STL_API friend _ConstIter cbegin(const _ClassName& __sequence) \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.begin())                  \
    {                                                                                     \
        return __sequence.begin();                                                        \
    }                                                                                     \
    [[nodiscard]] CANN_ASC_STL_API friend _ConstIter cend(const _ClassName& __sequence)   \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.end())                    \
    {                                                                                     \
        return __sequence.end();                                                          \
    }

#define CANN_ASC_STL_DETAIL_SYNTHESIZE_SEQUENCE_REVERSE_ACCESS(_ClassName, _ConstRevIter)     \
    [[nodiscard]] CANN_ASC_STL_API friend reverse_iterator rbegin(_ClassName& __sequence)     \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.rbegin())                     \
    {                                                                                         \
        return __sequence.rbegin();                                                           \
    }                                                                                         \
    [[nodiscard]] CANN_ASC_STL_API friend _ConstRevIter rbegin(const _ClassName& __sequence)  \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.rbegin())                     \
    {                                                                                         \
        return __sequence.rbegin();                                                           \
    }                                                                                         \
    [[nodiscard]] CANN_ASC_STL_API friend reverse_iterator rend(_ClassName& __sequence)       \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.rend())                       \
    {                                                                                         \
        return __sequence.rend();                                                             \
    }                                                                                         \
    [[nodiscard]] CANN_ASC_STL_API friend _ConstRevIter rend(const _ClassName& __sequence)    \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.rend())                       \
    {                                                                                         \
        return __sequence.rend();                                                             \
    }                                                                                         \
    [[nodiscard]] CANN_ASC_STL_API friend _ConstRevIter crbegin(const _ClassName& __sequence) \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.rbegin())                     \
    {                                                                                         \
        return __sequence.rbegin();                                                           \
    }                                                                                         \
    [[nodiscard]] CANN_ASC_STL_API friend _ConstRevIter crend(const _ClassName& __sequence)   \
        CANN_ASC_STL_DETAIL_SEQUENCE_ACCESS_NOEXCEPT(__sequence.rend())                       \
    {                                                                                         \
        return __sequence.rend();                                                             \
    }

#endif  // CANN_ASC_STL_STD_DETAIL_SEQUENCE_ACCESS_H
