/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_ERASE_IF_CONTAINER_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_ERASE_IF_CONTAINER_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Container, class _Predicate>
CANN_ASC_STL_API typename _Container::size_type __asc_erase_if_container(_Container& __c, _Predicate& __pred)
{
    typename _Container::size_type __old_size = __c.size();

    for (typename _Container::iterator __iter = __c.begin(); __iter != __c.end();) {
        if (__pred(*__iter)) {
            __iter = __c.erase(__iter);
        } else {
            ++__iter;
        }
    }

    return __old_size - __c.size();
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_ERASE_IF_CONTAINER_H
