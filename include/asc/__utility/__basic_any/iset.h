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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_ISET_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_ISET_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__type_traits/is_specialization_of.h>
#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/rtti.h>
#include <asc/__utility/__basic_any/tagged_ptr.h>
#include <asc/__utility/__basic_any/virtual_tables.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__type_traits/type_set.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! __iset_
//!
template <class... _Interfaces>
struct __iset__ {
    template <class...>
    struct __interface_ : __basic_interface<__interface_, __extends<_Interfaces...>> {};
};

template <class... _Interfaces>
struct __iset_ : __iset__<_Interfaces...>::template __interface_<> {};

// flatten any nested sets
template <class _Interface>
using __iset_flatten =
    ::asc::std::__as_type_list<::asc::std::conditional_t<__is_specialization_of_v<_Interface, __iset_>, _Interface,
        ::asc::std::__type_list<_Interface>>>;

// flatten all sets into one, remove duplicates, and sort the elements.
// TODO: sort!
// template <class... _Interfaces>
// using __iset = ::asc::std::__type_call<
//   ::asc::std::__type_unique<::asc::std::__type_sort<::asc::std::__type_concat<__iset_flatten<_Interfaces>...>>>,
//   ::asc::std::__type_quote<__iset_>>;
// GCC 7 had a problem with the original implementation, so we use a workaround.
#if 0  // GCC<10 workaround not applicable
template <class _Lhs, class _Rhs>
struct __iset_cat;

template <class... _Lhs, class... _Rhs>
struct __iset_cat<::asc::std::__type_list<_Lhs...>, ::asc::std::__type_list<_Rhs...>>
{
  using type = ::asc::std::__type_list<_Lhs..., _Rhs...>;
};

template <class... _Interfaces>
struct __iset_flatten_all;

template <>
struct __iset_flatten_all<>
{
  using type = ::asc::std::__type_list<>;
};

template <class... _Nested, class... _Rest>
struct __iset_flatten_all<__iset_<_Nested...>, _Rest...>
{
  using type = typename __iset_cat<typename __iset_flatten_all<_Nested...>::type,
                                   typename __iset_flatten_all<_Rest...>::type>::type;
};

template <class _Interface, class... _Rest>
struct __iset_flatten_all<_Interface, _Rest...>
{
  using type =
    typename __iset_cat<::asc::std::__type_list<_Interface>, typename __iset_flatten_all<_Rest...>::type>::type;
};

template <class... _Interfaces>
using __iset = ::asc::std::__type_call<::asc::std::__type_unique<typename __iset_flatten_all<_Interfaces...>::type>,
                                        ::asc::std::__type_quote<__iset_>>;
#else  // ^^^ CANN_ASC_STL_DETAIL_COMPILER(GCC, <, 10) ^^^ / vvv CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 10) vvv
template <class... _Interfaces>
using __iset =
    ::asc::std::__type_call<::asc::std::__type_unique<::asc::std::__type_concat<__iset_flatten<_Interfaces>...>>,
        ::asc::std::__type_quote<__iset_>>;
#endif  // CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 10)

//!
//! Virtual table pointers
//!
template <class... _Interfaces>
struct __iset_vptr : __base_vptr {
    using __iset_vtable = __vtable_for<__iset_<_Interfaces...>>;

    __iset_vptr() = default;

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr __iset_vptr(__iset_vtable const* __vptr) noexcept
        : __base_vptr(__vptr)
    {}

    CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr __iset_vptr(__base_vptr __vptr) noexcept : __base_vptr(__vptr)
    {}

    // Permit narrowing conversions from a super-set __vptr. Warning: we can't
    // simply constrain this because then the ctor from __base_vptr would be
    // selected instead, giving the wrong result.
    template <class... _Others>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API __iset_vptr(__iset_vptr<_Others...> __vptr) noexcept
        : __base_vptr(__vptr->__query_interface(__iunknown()))
    {
        static_assert(::asc::std::__type_set_contains_v<::asc::std::__make_type_set<_Others...>, _Interfaces...>);
        CANN_ASC_STL_DETAIL_ASSERT(__vptr_->__kind_ == __vtable_kind::__rtti && __vptr_->__cookie_ == 0xDEADBEEF,
            "query_interface returned a bad pointer to the __iunknown vtable");
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API constexpr auto operator->() const noexcept -> __iset_vptr const*
    {
        return this;
    }

    template <class _Interface>
    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API constexpr auto __query_interface(
        _Interface) const noexcept -> __vptr_for<_Interface>
    {
        if (__vptr_->__kind_ == __vtable_kind::__normal) {
            return static_cast<__iset_vtable const*>(__vptr_)->__query_interface(_Interface{});
        } else {
            return static_cast<__rtti const*>(__vptr_)->__query_interface(_Interface{});
        }
    }
};

template <class... _Interfaces>
struct __tagged_ptr<__iset_vptr<_Interfaces...>> {
    CANN_ASC_STL_DETAIL_NODEBUG_API auto __set(__iset_vptr<_Interfaces...> __vptr, bool __flag) noexcept -> void
    {
        __ptr_ = reinterpret_cast<uintptr_t>(__vptr.__vptr_) | uintptr_t(__flag);
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __get() const noexcept -> __iset_vptr<_Interfaces...>
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        return __iset_vptr<_Interfaces...>{reinterpret_cast<__rtti_base const*>(__ptr_ & ~uintptr_t(1))};
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __flag() const noexcept -> bool
    {
        return static_cast<bool>(__ptr_ & uintptr_t(1));
    }

    uintptr_t __ptr_ = 0;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_ISET_H
