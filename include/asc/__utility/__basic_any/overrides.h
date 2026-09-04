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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_OVERRIDES_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_OVERRIDES_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/std/__tuple_dir/ignore.h>
#include <asc/std/__type_traits/is_const.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Interface, class _Tp = __remove_ireference_t<_Interface>>
using __overrides_for_t = typename _Interface::template overrides<_Tp>;

//!
//! __overrides_for
//!
template <class _InterfaceOrModel, class... _VirtualFnsOrOverrides>
struct __overrides_list {
    static_assert(!::asc::std::is_const_v<_InterfaceOrModel>, "expected a class type");
    using __vtable = __basic_vtable<_InterfaceOrModel, _VirtualFnsOrOverrides::value...>;
    using __vptr_t = __vtable const*;
};

template <class... _Interfaces>
struct __overrides_list<__iset_<_Interfaces...>> {
    using __vtable = __basic_vtable<__iset_<_Interfaces...>>;
    using __vptr_t = __iset_vptr<_Interfaces...>;
};

template <>
struct __overrides_list<__iunknown> {
    using __vtable = ::asc::std::__ignore_t;  // no vtable, rtti is added explicitly in __vtable_tuple
    using __vptr_t = __rtti const*;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_OVERRIDES_H
