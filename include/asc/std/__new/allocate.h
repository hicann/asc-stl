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

#ifndef CANN_ASC_STL_STD_DETAIL_NEW_ALLOCATE_H
#define CANN_ASC_STL_STD_DETAIL_NEW_ALLOCATE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/cstddef>

// 2026-09-02 三层设计（与 __barrier/barrier.h、__cmath/gamma.h 同款）：
// (1) 宿主：委托宿主 operator new/delete（含对齐/尺寸分派，与源侧同构）；
// (2) SIMT 设备：CCE 编译器在 SIMT 模式下自带设备 operator new/delete
//     覆盖（__clang_dpp_runtime_wrapper.h：operator new → ::malloc →
//     dpp_alloc，950 SIMT TU 实测前端可用）。dpp_alloc/dpp_dealloc 的运行
//     时实现库不随 CANN 发行（可经 -cce-dpp-malloc-path 或用户自链实现
//     提供——本头的 SIMT 分支即面向该插拔运行时）。设备覆盖仅有无对齐、
//     无尺寸的基础形态：over-aligned 路径编译期拒绝（设备无 align_val_t
//     契约），sized delete 回退到无尺寸 delete。
// (3) mixed/向量核设备：真机对齐判定 mismatch（1638/16384，2026-08-09 台
//     账），不提供定义——调用得到明确链接诊断。
// 分支次序：SIMT TU 同时含 host+device，HOSTED() 在其中也为真，必须先判
// SIMT 设备上下文。
#if CANN_ASC_STL_DETAIL_HAS_DEVICE_HEAP()
// 自包含取版本号：SIMT 工程的编译命令不一定 -include devkit version 头
#if defined(__has_include)
#if __has_include(<version/asc_devkit_version.h>)
#include <version/asc_devkit_version.h>
#elif __has_include(<ascendc/asc_devkit_version.h>)
#include <ascendc/asc_devkit_version.h>
#endif
#endif
#if defined(ASC_DEVKIT_VERSION_NUM) && ASC_DEVKIT_VERSION_NUM >= 90200000
#define CANN_ASC_STL_DETAIL_NEW_ALLOCATE_SIMT 1
#endif
#elif CANN_ASC_STL_DETAIL_HOSTED()
#define CANN_ASC_STL_DETAIL_NEW_ALLOCATE_HOST 1
#include <asc/std/__host_stdlib/new>
#endif

#if CANN_ASC_STL_DETAIL_NEW_ALLOCATE_HOST

#if __cpp_sized_deallocation < 201309L
#define CANN_ASC_STL_DETAIL_HAS_SIZED_DEALLOCATION() 0
#else
#define CANN_ASC_STL_DETAIL_HAS_SIZED_DEALLOCATION() 1
#endif

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_HOST_API constexpr bool __is_overaligned_for_new(size_t __align) noexcept
{
#ifdef __STDCPP_DEFAULT_NEW_ALIGNMENT__
    return __align > __STDCPP_DEFAULT_NEW_ALIGNMENT__;
#else
    return __align > alignof(max_align_t);
#endif
}

template <class... _Args>
CANN_ASC_STL_HOST_API void* __asc_operator_new(_Args... __args)
{
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_OPERATOR_NEW)
    return CANN_ASC_STL_DETAIL_BUILTIN_OPERATOR_NEW(__args...);
#else
    return ::operator new(__args...);
#endif
}

template <class... _Args>
CANN_ASC_STL_HOST_API void __asc_operator_delete(_Args... __args)
{
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_OPERATOR_DELETE)
    CANN_ASC_STL_DETAIL_BUILTIN_OPERATOR_DELETE(__args...);
#else
    ::operator delete(__args...);
#endif
}

#if CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION()
using ::std::align_val_t;
#endif

CANN_ASC_STL_HOST_API void* __asc_allocate(size_t __size, [[maybe_unused]] size_t __align)
{
#if CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION()
    if (asc::std::__is_overaligned_for_new(__align)) {
        return asc::std::__asc_operator_new(__size, static_cast<align_val_t>(__align));
    }
#endif
    return asc::std::__asc_operator_new(__size);
}

template <class... _Args>
CANN_ASC_STL_HOST_API void __do_deallocate_handle_size(void* __ptr, [[maybe_unused]] size_t __size, _Args... __args)
{
#if CANN_ASC_STL_DETAIL_HAS_SIZED_DEALLOCATION()
    asc::std::__asc_operator_delete(__ptr, __size, __args...);
#else
    asc::std::__asc_operator_delete(__ptr, __args...);
#endif
}

CANN_ASC_STL_HOST_API void __asc_deallocate(void* __ptr, size_t __size, [[maybe_unused]] size_t __align)
{
#if CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION()
    if (asc::std::__is_overaligned_for_new(__align)) {
        return asc::std::__do_deallocate_handle_size(__ptr, __size, static_cast<align_val_t>(__align));
    }
#endif
    return asc::std::__do_deallocate_handle_size(__ptr, __size);
}

CANN_ASC_STL_HOST_API void __asc_deallocate_unsized(void* __ptr, [[maybe_unused]] size_t __align)
{
#if CANN_ASC_STL_DETAIL_ACCL_HAS_ALIGNED_ALLOCATION()
    if (asc::std::__is_overaligned_for_new(__align)) {
        return asc::std::__asc_operator_delete(__ptr, static_cast<align_val_t>(__align));
    }
#endif
    return asc::std::__asc_operator_delete(__ptr);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#undef CANN_ASC_STL_DETAIL_HAS_SIZED_DEALLOCATION

#elif CANN_ASC_STL_DETAIL_NEW_ALLOCATE_SIMT

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

//! @brief 设备 operator new/delete：CCE SIMT 模式自带覆盖（lower 到
//! dpp_alloc/dpp_dealloc）。需用户侧提供 dpp 运行时实现（CANN 不随附，
//! 见文件头注释）。设备覆盖无 align_val_t/sized 形态：
//! over-aligned 请求按分配失败契约返回 nullptr；sized delete 回退无尺寸
//! 形态。注意设备编译遍的 max_align_t 对齐为 8（宿主 x86-64 为 16，
//! 2026-09-02 950 真机实测），故对齐 >8 的请求在设备侧即属 over-aligned。
CANN_ASC_STL_API void* __asc_operator_new(size_t __size)
{
    return ::operator new(__size);
}

CANN_ASC_STL_API void __asc_operator_delete(void* __ptr)
{
    ::operator delete(__ptr);
}

CANN_ASC_STL_API constexpr bool __is_overaligned_for_new(size_t __align) noexcept
{
#ifdef __STDCPP_DEFAULT_NEW_ALIGNMENT__
    return __align > __STDCPP_DEFAULT_NEW_ALIGNMENT__;
#else
    return __align > alignof(max_align_t);
#endif
}

CANN_ASC_STL_API void* __asc_allocate(size_t __size, size_t __align)
{
    if (__is_overaligned_for_new(__align)) {
        // 设备 new 覆盖无 align_val_t 契约（dpp_alloc 不接受对齐参数）。
        // 对齐是运行时值无法编译期拒绝；按分配失败契约返回 nullptr，
        // 不静默降对齐（对齐契约破坏是 UB）。
        return nullptr;
    }
    return ::asc::std::__asc_operator_new(__size);
}

CANN_ASC_STL_API void __asc_deallocate(void* __ptr, size_t __size, size_t __align)
{
    static_cast<void>(__size);  // 设备 delete 覆盖无 sized 形态，尺寸仅由运行时记账
    static_cast<void>(__align);
    ::asc::std::__asc_operator_delete(__ptr);
}

CANN_ASC_STL_API void __asc_deallocate_unsized(void* __ptr, size_t __align)
{
    static_cast<void>(__align);
    ::asc::std::__asc_operator_delete(__ptr);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#else
// mixed/向量核设备：不提供定义（调用得到明确链接诊断而非静默错误值）。
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_NEW_ALLOCATE_H
