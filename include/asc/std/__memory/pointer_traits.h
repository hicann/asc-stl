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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_POINTER_TRAITS_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_POINTER_TRAITS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

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

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp, class = void>
inline constexpr bool __has_element_type = false;

template <class _Tp>
inline constexpr bool __has_element_type<_Tp, void_t<typename _Tp::element_type>> = true;

template <class _Ptr, bool = __has_element_type<_Ptr>>
struct __pointer_traits_element_type;

template <class _Ptr>
struct __pointer_traits_element_type<_Ptr, true> {
    using type = typename _Ptr::element_type;
};

template <template <class, class...> class _Sp, class _Tp, class... _Args>
struct __pointer_traits_element_type<_Sp<_Tp, _Args...>, true> {
    using type = typename _Sp<_Tp, _Args...>::element_type;
};

template <template <class, class...> class _Sp, class _Tp, class... _Args>
struct __pointer_traits_element_type<_Sp<_Tp, _Args...>, false> {
    using type = _Tp;
};

template <class _Tp, class = void>
inline constexpr bool __has_difference_type = false;

template <class _Tp>
inline constexpr bool __has_difference_type<_Tp, void_t<typename _Tp::difference_type>> = true;

template <class _Ptr, bool = __has_difference_type<_Ptr>>
struct __pointer_traits_difference_type {
    using type = ptrdiff_t;
};

template <class _Ptr>
struct __pointer_traits_difference_type<_Ptr, true> {
    using type = typename _Ptr::difference_type;
};

template <class _Tp, class _Up, class = void>
inline constexpr bool __has_rebind = false;

template <class _Tp, class _Up>
inline constexpr bool __has_rebind<_Tp, _Up, void_t<typename _Tp::template rebind<_Up>>> = true;

template <class _Tp, class _Up, bool = __has_rebind<_Tp, _Up>>
struct __pointer_traits_rebind {
    using type = typename _Tp::template rebind<_Up>;
};

template <template <class, class...> class _Sp, class _Tp, class... _Args, class _Up>
struct __pointer_traits_rebind<_Sp<_Tp, _Args...>, _Up, true> {
    using type = typename _Sp<_Tp, _Args...>::template rebind<_Up>;
};

template <template <class, class...> class _Sp, class _Tp, class... _Args, class _Up>
struct __pointer_traits_rebind<_Sp<_Tp, _Args...>, _Up, false> {
    using type = _Sp<_Up, _Args...>;
};

template <class _Ptr, class = void>
struct __pointer_traits_impl {};

template <class _Ptr>
struct __pointer_traits_impl<_Ptr, void_t<typename __pointer_traits_element_type<_Ptr>::type>> {
    using pointer = _Ptr;
    using element_type = typename __pointer_traits_element_type<pointer>::type;
    using difference_type = typename __pointer_traits_difference_type<pointer>::type;

    template <class _Up>
    using rebind = typename __pointer_traits_rebind<pointer, _Up>::type;

private:
    struct __nat {};

public:
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 static pointer pointer_to(
        conditional_t<is_void_v<element_type>, __nat, element_type>& __r)
    {
        return pointer::pointer_to(__r);
    }
};

template <class _Ptr, class = void>
struct pointer_traits : __pointer_traits_impl<_Ptr> {};

template <class _Tp>
struct pointer_traits<_Tp*> {
    using pointer = _Tp*;
    using element_type = _Tp;
    using difference_type = ptrdiff_t;

    template <class _Up>
    using rebind = _Up*;

private:
    struct __nat {};

public:
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 static pointer pointer_to(
        conditional_t<is_void_v<element_type>, __nat, element_type>& __r) noexcept
    {
        return ::asc::std::addressof(__r);
    }
};

template <class _Pointer, class = void>
struct __to_address_helper;

template <class _Tp>
CANN_ASC_STL_API constexpr _Tp* __to_address(_Tp* __p) noexcept
{
    static_assert(!is_function_v<_Tp>, "_Tp is a function type");
    return __p;
}

template <class _Pointer, class = void>
inline constexpr bool __has_toaddress = false;

template <class _Pointer>
inline constexpr bool __has_toaddress<_Pointer,
    decltype((void)pointer_traits<_Pointer>::to_address(::asc::std::declval<const _Pointer&>()))> = true;

template <class _Pointer, class = void>
inline constexpr bool __has_const_operator_arrow = false;

template <class _Pointer>
inline constexpr bool
    __has_const_operator_arrow<_Pointer, decltype((void)::asc::std::declval<const _Pointer&>().operator->())> = true;

template <class _Pointer>
inline constexpr bool __is_fancy_pointer = __has_const_operator_arrow<_Pointer> || __has_toaddress<_Pointer>;

template <class _Pointer, class = enable_if_t<is_class_v<_Pointer>>, class = enable_if_t<__is_fancy_pointer<_Pointer>>>
CANN_ASC_STL_API constexpr decay_t<decltype(__to_address_helper<_Pointer>::__call(
    ::asc::std::declval<const _Pointer&>()))>
__to_address(const _Pointer& __p) noexcept
{
    return __to_address_helper<_Pointer>::__call(__p);
}

template <class _Pointer, class>
struct __to_address_helper {
    CANN_ASC_STL_API constexpr static decltype(::asc::std::__to_address(
        ::asc::std::declval<const _Pointer&>().operator->()))
    __call(const _Pointer& __p) noexcept
    {
        return ::asc::std::__to_address(__p.operator->());
    }
};

template <class _Pointer>
struct __to_address_helper<_Pointer,
    decltype((void)pointer_traits<_Pointer>::to_address(::asc::std::declval<const _Pointer&>()))> {
    CANN_ASC_STL_API constexpr static decltype(pointer_traits<_Pointer>::to_address(
        ::asc::std::declval<const _Pointer&>()))
    __call(const _Pointer& __p) noexcept
    {
        return pointer_traits<_Pointer>::to_address(__p);
    }
};

template <class _Tp>
CANN_ASC_STL_API constexpr auto to_address(_Tp* __p) noexcept
{
    return ::asc::std::__to_address(__p);
}

template <class _Pointer>
CANN_ASC_STL_API constexpr auto to_address(const _Pointer& __p) noexcept -> decltype(::asc::std::__to_address(__p))
{
    return ::asc::std::__to_address(__p);
}

template <class _Iter, class = void>
inline constexpr bool __can_to_address = false;

template <class _Iter>
inline constexpr bool __can_to_address<_Iter, void_t<decltype(::asc::std::to_address(::asc::std::declval<_Iter&>()))>> =
    true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_POINTER_TRAITS_H
