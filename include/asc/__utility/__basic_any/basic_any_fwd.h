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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_BASIC_ANY_FWD_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_BASIC_ANY_FWD_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/cstddef>
#include <asc/std/cstdint>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Interface>
struct __ireference;

template <class _Interface>
struct __basic_any;
template <class _Interface>
struct __basic_any<__ireference<_Interface>>;
template <class _Interface>
struct __basic_any<_Interface*>;
template <class _Interface>
struct __basic_any<_Interface&>;

template <auto _Value>
using __constant = ::asc::std::integral_constant<decltype(_Value), _Value>;

template <class _InterfaceOrModel, class... _VirtualFnsOrOverrides>
struct __overrides_list;
template <class _InterfaceOrModel, auto... _VirtualFnsOrOverrides>
using __overrides_for = __overrides_list<_InterfaceOrModel, __constant<_VirtualFnsOrOverrides>...>;

template <class _Interface, auto... _Mbrs>
struct __basic_vtable;

struct __rtti_base;
struct __rtti;
template <::asc::std::size_t _NbrBases>
struct __rtti_ex;
template <class...>
struct __extends;
template <template <class...> class, class = __extends<>, ::asc::std::size_t = 0, ::asc::std::size_t = 0>
struct __basic_interface;

template <class _Interface, class... _Super>
using __rebind_interface = typename _Interface::template __rebind<_Super...>;

struct __iunknown;
template <class...>
struct __iset_;
template <class...>
struct __iset_vptr;
template <class...>
struct __imovable;
template <class...>
struct __icopyable;
template <class...>
struct __iequality_comparable;

template <class... _Tp>
using __tag = ::asc::std::__type_list_ptr<_Tp...>;
template <auto...>
struct __ctag_;
template <auto... _Is>
using __ctag = __ctag_<_Is...>*;

constexpr ::asc::std::size_t __word = sizeof(void*);
constexpr ::asc::std::size_t __default_small_object_size = 3 * __word;
constexpr ::asc::std::size_t __default_small_object_align = alignof(::asc::std::max_align_t);

using __make_type_list = ::asc::std::__type_quote<::asc::std::__type_list>;

[[noreturn]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __throw_bad_any_cast();

enum class __vtable_kind : uint8_t {
    __normal,
    __rtti,
};

inline constexpr uint8_t __basic_any_version = 1;

// Use type dispatch instead of the source variable-template/decltype trick;
// BiSheng rejects device references to variable templates in signatures.
template <class _Interface>
struct __remove_ireference {
    using type = _Interface;
};
template <class _Interface>
using __remove_ireference_t = typename __remove_ireference<_Interface>::type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_BASIC_ANY_FWD_H
