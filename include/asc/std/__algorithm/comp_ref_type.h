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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_COMP_REF_TYPE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_COMP_REF_TYPE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__utility/declval.h>

// dev 版 <asc/std/__asc/assert.h> 断言链的最小等价内联（规则册条款5，#ifndef 守卫防重）：
// debug 构建（_DEBUG/DEBUG）启用 ENABLE_DEBUG_MODE，进而启用宿主断言；设备侧无断言机制，恒为 no-op。
#ifndef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#if defined(_DEBUG) || defined(DEBUG)
#define CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // defined(_DEBUG) || defined(DEBUG)
#endif  // !CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE

#ifndef ASC_ENABLE_ASSERTIONS
#ifdef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#define ASC_ENABLE_ASSERTIONS
#endif  // CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // !ASC_ENABLE_ASSERTIONS

#ifndef ASC_ENABLE_HOST_ASSERTIONS
#ifdef ASC_ENABLE_ASSERTIONS
#define ASC_ENABLE_HOST_ASSERTIONS
#endif  // ASC_ENABLE_ASSERTIONS
#endif  // !ASC_ENABLE_HOST_ASSERTIONS

#ifndef CANN_ASC_STL_DETAIL_ASSERT
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// ASC 设备侧无断言机制
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#elif defined(ASC_ENABLE_HOST_ASSERTIONS)
#ifdef NDEBUG
// NDEBUG 下 <assert.h> 未必已包含，按 dev 版做法手工补声明
extern "C" {
void __assert_fail(const char* __assertion, const char* __file, unsigned int __line, const char* __function) noexcept
    __attribute__((__noreturn__));
}  // extern "C"
#else
#include <assert.h>
#endif  // NDEBUG
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    __builtin_expect(static_cast<bool>(expression), 1) ? (void)0 : __assert_fail(message, __FILE__, __LINE__, __func__)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#endif  // ASC_ENABLE_HOST_ASSERTIONS
#endif  // !CANN_ASC_STL_DETAIL_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Compare>
struct __debug_less {
    _Compare& __comp_;
    CANN_ASC_STL_API constexpr __debug_less(_Compare& __c) : __comp_(__c)
    {}

    template <class _Tp, class _Up>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool operator()(const _Tp& __x, const _Up& __y)
    {
        bool __r = __comp_(__x, __y);
        if (__r) {
            __do_compare_assert(0, __y, __x);
        }
        return __r;
    }

    template <class _Tp, class _Up>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool operator()(_Tp& __x, _Up& __y)
    {
        bool __r = __comp_(__x, __y);
        if (__r) {
            __do_compare_assert(0, __y, __x);
        }
        return __r;
    }

    template <class _LHS, class _RHS>
    CANN_ASC_STL_API constexpr decltype((void)declval<_Compare&>()(declval<_LHS&>(), declval<_RHS&>()))
    __do_compare_assert(int, [[maybe_unused]] _LHS& __l, [[maybe_unused]] _RHS& __r)
    {
        CANN_ASC_STL_DETAIL_ASSERT(!__comp_(__l, __r), "Comparator does not induce a strict weak ordering");
    }

    template <class _LHS, class _RHS>
    CANN_ASC_STL_API constexpr void __do_compare_assert(long, _LHS&, _RHS&)
    {}
};

// Pass the comparator by lvalue reference. Or in debug mode, using a
// debugging wrapper that stores a reference.
#ifdef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
template <class _Comp>
using __comp_ref_type = __debug_less<_Comp>;
#else   // ^^^ CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE ^^^ / vvv !CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE vvv
template <class _Comp>
using __comp_ref_type = _Comp&;
#endif  // !CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_COMP_REF_TYPE_H
