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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_BASIC_ANY_BASE_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_BASIC_ANY_BASE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/__utility/__basic_any/storage.h>
#include <asc/__utility/__basic_any/tagged_ptr.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/cstddef>  // for byte
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Interface>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __is_basic_any_test(__basic_any<_Interface>&&) -> __basic_any<_Interface>&&;
template <class _Interface>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __is_basic_any_test(__basic_any<_Interface>&) -> __basic_any<_Interface>&;
template <class _Interface>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __is_basic_any_test(
    __basic_any<_Interface> const&) -> __basic_any<_Interface> const&;

#if CANN_ASC_STL_DETAIL_COMPILER(CLANG, <, 12) || CANN_ASC_STL_DETAIL_COMPILER(GCC, <, 11)
// Older versions of clang and gcc need help disambiguating between
// __basic_any<__ireference<I>> and __basic_any<I&>.
template <class _Interface>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __is_basic_any_test(__basic_any<_Interface&>&&) -> __basic_any<_Interface&>&&;
template <class _Interface>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __is_basic_any_test(__basic_any<_Interface&>&) -> __basic_any<_Interface&>&;
template <class _Interface>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __is_basic_any_test(
    __basic_any<_Interface&> const&) -> __basic_any<_Interface&> const&;
#endif

// clang-format off
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __is_basic_any =
  CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Tp), _Tp& __value)
  (
    (::asc::__is_basic_any_test(__value))
  );  // NOLINT(whitespace/parens)
// clang-format on

// We need a base class to correctly implement movability and copyability.
template <class _Interface, int = __extension_of<_Interface, __imovable<>> + __extension_of<_Interface, __icopyable<>>>
struct __basic_any_base;

template <class _Interface>
struct __basic_any_base<_Interface, 2> : __interface_of<_Interface>  // copyable interfaces
{
    __basic_any_base() = default;

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any_base(__basic_any_base&& __other) noexcept
    {
        static_cast<__basic_any<_Interface>*>(this)->__convert_from(static_cast<__basic_any<_Interface>&&>(__other));
    }

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __basic_any_base(__basic_any_base const& __other)
    {
        static_cast<__basic_any<_Interface>*>(this)->__convert_from(
            static_cast<__basic_any<_Interface> const&>(__other));
    }

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(__basic_any_base&& __other) noexcept -> __basic_any_base&
    {
        static_cast<__basic_any<_Interface>*>(this)->__assign_from(static_cast<__basic_any<_Interface>&&>(__other));
        return *this;
    }

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto operator=(__basic_any_base const& __other) -> __basic_any_base&
    {
        static_cast<__basic_any<_Interface>*>(this)->__assign_from(
            static_cast<__basic_any<_Interface> const&>(__other));
        return *this;
    }

private:
    template <class>
    friend struct __basic_any;
    friend struct __basic_any_access;

    static constexpr size_t __size_ = __buffer_size(_Interface::size);
    static constexpr size_t __align_ = __buffer_align(_Interface::align);

    __tagged_ptr<__vptr_for<_Interface>> __vptr_{};
    alignas(__align_)::asc::std::byte __buffer_[__size_];
};

template <class _Interface>
struct __basic_any_base<_Interface, 1> : __basic_any_base<_Interface, 2>  // move-only interfaces
{
    __basic_any_base() = default;
    __basic_any_base(__basic_any_base&&) noexcept = default;
    __basic_any_base(__basic_any_base const&) = delete;
    auto operator=(__basic_any_base&&) noexcept -> __basic_any_base& = default;
    auto operator=(__basic_any_base const&) -> __basic_any_base& = delete;
};

template <class _Interface>
struct __basic_any_base<_Interface, 0> : __basic_any_base<_Interface, 2>  // immovable interfaces
{
    __basic_any_base() = default;
    __basic_any_base(__basic_any_base&&) noexcept = delete;
    __basic_any_base(__basic_any_base const&) = delete;
    auto operator=(__basic_any_base&&) noexcept -> __basic_any_base& = delete;
    auto operator=(__basic_any_base const&) -> __basic_any_base& = delete;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_BASIC_ANY_BASE_H
