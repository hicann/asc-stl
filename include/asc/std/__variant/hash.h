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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_HASH_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_HASH_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/hash.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/cstdint>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class... _Types>
struct hash<__enable_hash_helper<variant<_Types...>, remove_const_t<_Types>...>> {
    using argument_type = variant<_Types...>;
    using result_type = size_t;

    template <size_t _CurrentIndex>
    [[nodiscard]] CANN_ASC_STL_API constexpr static size_t __hash(
        integral_constant<size_t, _CurrentIndex>, const size_t __index_, const argument_type& __v) noexcept
    {
        if (__index_ == _CurrentIndex) {
            using __value_type = remove_const_t<__type_index_c<_CurrentIndex, _Types...>>;
            return hash<__value_type>{}(__variant_detail::__access::__variant::__get_alt<_CurrentIndex>(__v).__value);
        }
        // Defect fix relative to the reference: the recursive branch lacked a return; a non-void
        // fallthrough is undefined behavior (some device compilers accepted it silently).
        return __hash(integral_constant<size_t, _CurrentIndex - 1>{}, __index_, __v);
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr static size_t __hash(
        integral_constant<size_t, 0>, const size_t __index_, const argument_type& __v) noexcept
    {
        if (__index_ == 0) {
            using __value_type = remove_const_t<__type_index_c<0, _Types...>>;
            return hash<__value_type>{}(__variant_detail::__access::__variant::__get_alt<0>(__v).__value);
        }
        // We already checked that every variant has a value, so we should never reach this line
        CANN_ASC_STL_DETAIL_UNREACHABLE();
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr result_type operator()(const argument_type& __v) const
    {
        size_t __res = __v.valueless_by_exception() ?
            299792458  // Random value chosen by the universe upon creation
            :
            __hash(integral_constant<size_t, sizeof...(_Types) - 1>{}, __v.index(), __v);
        return ::asc::std::__hash_combine(__res, hash<size_t>{}(__v.index()));
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_HASH_H
