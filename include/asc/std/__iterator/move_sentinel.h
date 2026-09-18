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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_MOVE_SENTINEL_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_MOVE_SENTINEL_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/semiregular.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <semiregular _Sent>
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Sent, enable_if_t<semiregular<_Sent>, int> = 0>
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^
class move_sentinel {
public:
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr move_sentinel() = default;

    CANN_ASC_STL_API constexpr explicit move_sentinel(_Sent __s)
        : __last_(::asc::std::move(__s))  // NOLINT(build/include_what_you_use)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(convertible_to<const _S2&, _Sent>)
    CANN_ASC_STL_API constexpr move_sentinel(const move_sentinel<_S2>& __s) : __last_(__s.base())
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _S2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(assignable_from<const _S2&, _Sent>)
    CANN_ASC_STL_API constexpr move_sentinel& operator=(const move_sentinel<_S2>& __s)
    {
        __last_ = __s.base();
        return *this;
    }

    CANN_ASC_STL_API constexpr _Sent base() const
    {
        return __last_;
    }

private:
    _Sent __last_ = _Sent();
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_MOVE_SENTINEL_H
