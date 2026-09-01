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

#if CANN_ASC_STL_DETAIL_HOSTED()

#include <asc/std/__host_stdlib/new>

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

#endif  // CANN_ASC_STL_DETAIL_HOSTED()

#endif  // CANN_ASC_STL_STD_DETAIL_NEW_ALLOCATE_H
