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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_POINTER_TRAITS_H
#define CANN_ASC_STL_ASC_STD___MEMORY_POINTER_TRAITS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/conjunction.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class P, class = void>
struct __pointer_element;
template <class P>
struct __pointer_element<P, void_t<typename P::element_type>> {
    using type = typename P::element_type;
};
template <template <class, class...> class P, class T, class... Args>
struct __pointer_element<P<T, Args...>, void> {
    using type = T;
};
template <class P, class = void>
struct __pointer_difference {
    using type = ptrdiff_t;
};
template <class P>
struct __pointer_difference<P, void_t<typename P::difference_type>> {
    using type = typename P::difference_type;
};
template <class P, class U, class = void>
struct __pointer_rebind;
template <class P, class U>
struct __pointer_rebind<P, U, void_t<typename P::template rebind<U>>> {
    using type = typename P::template rebind<U>;
};
template <template <class, class...> class P, class T, class... Args, class U>
struct __pointer_rebind<P<T, Args...>, U, void> {
    using type = P<U, Args...>;
};
template <class P, class = void>
struct pointer_traits {};
template <class P>
struct pointer_traits<P, void_t<typename __pointer_element<P>::type>> {
    using pointer = P;
    using element_type = typename __pointer_element<P>::type;
    using difference_type = typename __pointer_difference<P>::type;
    template <class U>
    using rebind = typename __pointer_rebind<P, U>::type;

private:
    struct __nat {};

public:
    CANN_ASC_STL_API static pointer pointer_to(conditional_t<is_void_v<element_type>, __nat, element_type>& value)
    {
        return P::pointer_to(value);
    }
};
template <class T>
struct pointer_traits<T*> {
    using pointer = T*;
    using element_type = T;
    using difference_type = ptrdiff_t;
    template <class U>
    using rebind = U*;

private:
    struct __nat {};

public:
    CANN_ASC_STL_API static constexpr pointer pointer_to(
        conditional_t<is_void_v<element_type>, __nat, element_type>& value) noexcept
    {
        return ::asc::std::addressof(value);
    }
};
template <class T>
CANN_ASC_STL_API constexpr T* to_address(T* pointer) noexcept
{
    static_assert(!is_function_v<T>, "to_address does not accept function pointers");
    return pointer;
}
template <class P, class = void>
struct __to_address_helper {
    CANN_ASC_STL_API static constexpr auto call(
        const P& pointer) noexcept -> decltype(::asc::std::to_address(pointer.operator->()))
    {
        return ::asc::std::to_address(pointer.operator->());
    }
};
template <class P>
struct __to_address_helper<P, void_t<decltype(pointer_traits<P>::to_address(::asc::std::declval<const P&>()))>> {
    CANN_ASC_STL_API static constexpr auto call(
        const P& pointer) noexcept -> decltype(pointer_traits<P>::to_address(pointer))
    {
        return pointer_traits<P>::to_address(pointer);
    }
};
template <class P, enable_if_t<is_class_v<P>, int> = 0>
CANN_ASC_STL_API constexpr auto to_address(const P& pointer) noexcept -> decltype(__to_address_helper<P>::call(pointer))
{
    return __to_address_helper<P>::call(pointer);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_POINTER_TRAITS_H
