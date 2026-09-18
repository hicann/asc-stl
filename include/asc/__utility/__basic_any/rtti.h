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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_RTTI_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_RTTI_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/__utility/__basic_any/interfaces.h>
#include <asc/__utility/__basic_any/virtual_ptrs.h>
#include <asc/__utility/immovable.h>
#include <asc/std/__asc/unreachable.h>
#include <asc/std/__exception/terminate.h>
#include <asc/std/__utility/typeid.h>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <typeinfo>  // IWYU pragma: keep (for std::bad_cast)
#endif               // HOSTED gate
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//!
//! __iunknown: Logically, the root of all interfaces.
//!
struct __iunknown : __basic_interface<::asc::std::__type_always<__iunknown>::__call> {};

#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS()
//!
//! __bad_any_cast
//!
struct __bad_any_cast : ::std::bad_cast {
    __bad_any_cast() noexcept = default;
    __bad_any_cast(__bad_any_cast const&) noexcept = default;
    ~__bad_any_cast() noexcept override = default;
    auto operator=(__bad_any_cast const&) noexcept -> __bad_any_cast& = default;

    auto what() const noexcept -> char const* override
    {
        return "cannot cast value to target type";
    }
};

[[noreturn]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __throw_bad_any_cast()
{
    throw __bad_any_cast();
}
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() vvv
[[noreturn]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __throw_bad_any_cast()
{
    ::asc::std::terminate();
}
#endif  // HOSTED gate
struct __rtti_base : __immovable {
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr __rtti_base(
        __vtable_kind __kind, uint16_t __nbr_interfaces, ::asc::std::__type_info_ref __self) noexcept
        : __kind_(__kind), __nbr_interfaces_(__nbr_interfaces), __typeid_(&__self)
    {}

    uint8_t __version_ = __basic_any_version;
    __vtable_kind __kind_ = __vtable_kind::__normal;
    uint16_t __nbr_interfaces_ = 0;
    uint32_t const __cookie_ = 0xDEADBEEF;
    ::asc::std::__type_info_ptr __typeid_{};
};

// The reference asserts the host ::std::type_info pointer layout; the ASC device typeid
// is a string-handle representation, so this ABI assertion holds only on the hosted+typeid
// path.
#if CANN_ASC_STL_DETAIL_HOSTED() && !defined(CANN_ASC_STL_DETAIL_NO_TYPEID)
static_assert(sizeof(__rtti_base) == sizeof(uint64_t) + sizeof(void*));
#endif

// Used to map an interface typeid to a pointer to the vtable for that interface.
struct __base_info {
    using __cast_fn_t = auto(__rtti const*) noexcept -> __base_vptr;

    ::asc::std::__type_info_ptr __typeid_;
    union {
        __cast_fn_t* __cast_fn_;  // used when __basic_any_version >= 1,
        __base_vptr __vptr_v0_;   // used when __basic_any_version == 0
    };

    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __get_vptr(
        __rtti const* __rtti_ptr, uint8_t __version) const noexcept -> __base_vptr
    {
        return __version >= 1 ? __cast_fn_(__rtti_ptr) : __vptr_v0_;
    }

    template <class _VTable, class _Interface>
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API static auto __cast_fn_impl(
        __rtti const* __rtti_ptr) noexcept -> __base_vptr
    {
        return {static_cast<__vptr_for<_Interface>>(static_cast<_VTable const*>(__rtti_ptr))};
    }
};

inline constexpr size_t __half_size_t_bits = sizeof(size_t) * CHAR_BIT / 2;

// The metadata for the type-erased object. All vtables have an rtti sub-object,
// which contains a sub-object of this type.
struct __object_metadata {
    size_t __size_ : __half_size_t_bits;
    size_t __align_ : __half_size_t_bits;
    ::asc::std::__type_info_ptr __object_typeid_;
    ::asc::std::__type_info_ptr __pointer_typeid_;
    ::asc::std::__type_info_ptr __const_pointer_typeid_;
};

template <class _Tp>
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT __object_metadata __object_metadata_v = {sizeof(_Tp), alignof(_Tp),
    &::asc::std::__typeid<_Tp>(), &::asc::std::__typeid<_Tp*>(), &::asc::std::__typeid<_Tp const*>()};

template <class _Tp>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __dtor_fn(void* __pv, bool __small) noexcept
{
    __small ? static_cast<_Tp*>(__pv)->~_Tp()  //
              :
              delete *static_cast<_Tp**>(__pv);
}

// All vtables have an rtti sub-object. This object has several responsibilities:
// * It contains the destructor for the type-erased object.
// * It contains the metadata for the type-erased object.
// * It contains a map from the base interfaces typeids to their vtables for use
//   in dynamic_cast-like functionality.
struct __rtti : __rtti_base {
    template <class _Tp, class _Super, class... _Interfaces>
    CANN_ASC_STL_DETAIL_NODEBUG_API constexpr __rtti(
        __tag<_Tp, _Super>, __tag<_Interfaces...>, __base_info const* __base_vptr_map) noexcept
        : __rtti_base{__vtable_kind::__rtti, sizeof...(_Interfaces), ::asc::std::__typeid<__rtti>()},
          __dtor_(&__dtor_fn<_Tp>),
          __object_info_(&__object_metadata_v<_Tp>),
          __interface_typeid_{&::asc::std::__typeid<_Super>()},
          __base_vptr_map_{__base_vptr_map}
    {}

    template <class... _Interfaces>
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __query_interface(
        __iset_<_Interfaces...>) const noexcept -> __vptr_for<__iset_<_Interfaces...>>
    {
        // Verify that every sub-interface in the requested set exists in the vtable.
        // TODO: Can it be done in a more efficient way?
        if ((__query_interface(_Interfaces{}) && ...)) {
            return static_cast<__vptr_for<__iset_<_Interfaces...>>>(this);
        }
        return nullptr;
    }

    // Sequentially search the base_vptr_map for the requested interface by
    // comparing typeids. If the requested interface is found, return a pointer to
    // its vtable; otherwise, return nullptr.
    template <class _Interface>
    [[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __query_interface(
        _Interface) const noexcept -> __vptr_for<_Interface>
    {
        // On sane implementations, comparing type_info objects first compares their
        // addresses and, if that fails, it does a string comparison. What we want is
        // to check _all_ the addresses first, and only if they all fail, resort to
        // string comparisons. So do two passes over the __base_vptr_map.
        constexpr ::asc::std::__type_info_ref __id = ::asc::std::__typeid<_Interface>();

        for (size_t __i = 0; __i < __nbr_interfaces_; ++__i) {
            if (&__id == __base_vptr_map_[__i].__typeid_) {
                return static_cast<__vptr_for<_Interface>>(__base_vptr_map_[__i].__get_vptr(this, __version_));
            }
        }

        for (size_t __i = 0; __i < __nbr_interfaces_; ++__i) {
            if (__id == *__base_vptr_map_[__i].__typeid_) {
                return static_cast<__vptr_for<_Interface>>(__base_vptr_map_[__i].__get_vptr(this, __version_));
            }
        }

        return nullptr;
    }

    void (*__dtor_)(void*, bool) noexcept = nullptr;
    __object_metadata const* __object_info_ = nullptr;
    ::asc::std::__type_info_ptr __interface_typeid_{};
    __base_info const* __base_vptr_map_ = nullptr;
};

template <size_t _NbrInterfaces>
struct __rtti_ex : __rtti {
    template <class _Tp, class _Super, class... _Interfaces, class _VTable>
    CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr __rtti_ex(
        __tag<_Tp, _Super> __type, __tag<_Interfaces...> __ibases, _VTable const*) noexcept
        : __rtti{__type, __ibases, __base_vptr_array},
          __base_vptr_array{
              {{&::asc::std::__typeid<_Interfaces>()}, {&__base_info::__cast_fn_impl<_VTable, _Interfaces>}}...}
    {}

    __base_info __base_vptr_array[_NbrInterfaces];
};

//!
//! __try_vptr_cast
//!
//! This function ignores const qualification on the source and destination
//! interfaces.
//!
template <class _SrcInterface, class _DstInterface>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __try_vptr_cast(
    __vptr_for<_SrcInterface> __src_vptr) noexcept -> __vptr_for<_DstInterface>
{
    static_assert(
        ::asc::std::is_class_v<_SrcInterface> && ::asc::std::is_class_v<_DstInterface>, "expected class types");
    if (__src_vptr == nullptr) {
        return nullptr;
    } else if constexpr (::asc::std::is_same_v<_SrcInterface const, _DstInterface const>) {
        return __src_vptr;
    } else if constexpr (__extension_of<_SrcInterface, _DstInterface>) {
        //! Fast up-casts:
        return __src_vptr->__query_interface(_DstInterface());
    } else {
        //! Slow down-casts and cross-casts:
        __rtti const* __rtti_ptr = __src_vptr->__query_interface(__iunknown());
        return __rtti_ptr->__query_interface(_DstInterface());
    }
}

template <class _SrcInterface, class _DstInterface>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API auto __vptr_cast(__vptr_for<_SrcInterface> __src_vptr)  //
    noexcept(::asc::std::is_same_v<_SrcInterface, _DstInterface>)                                         //
    -> __vptr_for<_DstInterface>
{
    if constexpr (::asc::std::is_same_v<_SrcInterface, _DstInterface>) {
        return __src_vptr;
    } else {
        auto __dst_vptr = __try_vptr_cast<_SrcInterface, _DstInterface>(__src_vptr);
        if (!__dst_vptr && __src_vptr) {
            __throw_bad_any_cast();
        }
        return __dst_vptr;
    }
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_RTTI_H
