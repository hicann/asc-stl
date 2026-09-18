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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_DEFAULT_SEARCHER_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_DEFAULT_SEARCHER_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// No special library mode applies here: the main body is always compiled.
#include <asc/std/__algorithm/search.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// default searcher
template <class _ForwardIterator, class _BinaryPredicate = equal_to<>>  // NOLINT(build/include_what_you_use)
class default_searcher {
public:
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 default_searcher(
        _ForwardIterator __f, _ForwardIterator __l, _BinaryPredicate __p = _BinaryPredicate())
        : __first_(__f), __last_(__l), __pred_(__p)
    {}

    template <typename _ForwardIterator2>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
        pair<_ForwardIterator2, _ForwardIterator2>  // NOLINT(build/include_what_you_use)
        operator()(                                 // NOLINT(build/include_what_you_use)
            _ForwardIterator2 __f, _ForwardIterator2 __l) const
    {
        return ::asc::std::__search(__f, __l, __first_, __last_, __pred_,
            __iterator_traits_category_or_concept_t<_ForwardIterator>(),
            __iterator_traits_category_or_concept_t<_ForwardIterator2>());
    }

private:
    _ForwardIterator __first_;
    _ForwardIterator __last_;
    _BinaryPredicate __pred_;
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(default_searcher);

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_DEFAULT_SEARCHER_H
