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

#ifndef CANN_ASC_STL_ASC_STD___FUNCTIONAL_DEFAULT_SEARCHER_H
#define CANN_ASC_STL_ASC_STD___FUNCTIONAL_DEFAULT_SEARCHER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/search.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class ForwardIterator, class BinaryPredicate = equal_to<>>  // NOLINT(build/include_what_you_use)
class default_searcher {
public:
    CANN_ASC_STL_API constexpr default_searcher(
        ForwardIterator first, ForwardIterator last, BinaryPredicate predicate = BinaryPredicate())
        : first_(first), last_(last), predicate_(predicate)
    {}

    template <class ForwardIterator2>
    CANN_ASC_STL_API constexpr pair<ForwardIterator2, ForwardIterator2> operator()(
        ForwardIterator2 first, ForwardIterator2 last) const
    {
        const auto found = ::asc::std::search(first, last, first_, last_, predicate_);
        if (found == last) {
            return pair<ForwardIterator2, ForwardIterator2>(last, last);
        }
        auto match_end = found;
        auto pattern = first_;
        while (pattern != last_) {
            ++match_end;
            ++pattern;
        }
        return pair<ForwardIterator2, ForwardIterator2>(found, match_end);  // NOLINT(build/include_what_you_use)
    }

private:
    ForwardIterator first_;
    ForwardIterator last_;
    BinaryPredicate predicate_;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FUNCTIONAL_DEFAULT_SEARCHER_H
