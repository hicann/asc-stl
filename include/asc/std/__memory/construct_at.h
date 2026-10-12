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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_CONSTRUCT_AT_H
#define CANN_ASC_STL_ASC_STD___MEMORY_CONSTRUCT_AT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__iterator/access.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/voidify.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/__type_traits/is_trivially_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

// 断言宏：基座无集中定义（方言层持有），按 __mdspan/empty_base.h 的同形内联，
// #ifndef 守卫以免与未来集中定义冲突。
#ifndef CANN_ASC_STL_DETAIL_ASSERT
// 设备侧无断言机制恒为 no-op；宿主侧仅在显式开启 ASC_ENABLE_HOST_ASSERTIONS 时检查。
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

#ifndef CANN_ASC_STL_DETAIL_PLACEMENT_NEW_DECLARED
#define CANN_ASC_STL_DETAIL_PLACEMENT_NEW_DECLARED
#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
CANN_ASC_STL_DEVICE_API void* operator new(__SIZE_TYPE__, void* address) noexcept
{
    return address;
}
#else
void* operator new(__SIZE_TYPE__, void* address) noexcept;
#endif
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __detail {
// 仅用于未求值上下文的探测件（合入自迁移源语义；基座无对应独立头，就地内联）。
template <class T>
T&& __construct_at_declval(int);
template <class T>
T __construct_at_declval(long);
template <class T>
decltype(__detail::__construct_at_declval<T>(0)) __construct_at_declval_expr() noexcept;
template <class T>
void __construct_at_accepts_implicit_conversion(T) noexcept;

// 非窄化隐式可转换探测：花括号初始化拒绝窄化，与隐式转换要求共同构成守卫。
template <class Dest, class Source, class = void>
struct __is_non_narrowing_convertible {
    static constexpr bool value = false;
};
template <class Dest, class Source>
struct __is_non_narrowing_convertible<Dest, Source,
    void_t<decltype(__detail::__construct_at_accepts_implicit_conversion<Dest>(
               __detail::__construct_at_declval_expr<Source>())),
        decltype(Dest{__detail::__construct_at_declval_expr<Source>()})>> {
    static constexpr bool value = true;
};

// 赋值优化路径守卫：算术类型间窄化会在赋值初始化处直接编译失败，必须先行排除。
template <class T, class... Args>
using __check_narrowing = conditional_t<sizeof...(Args) == 1, __is_non_narrowing_convertible<T, Args...>, true_type>;

template <class T, class... Args>
inline constexpr bool __can_optimize_construct_at = is_trivially_constructible_v<T, Args...> &&
    is_trivially_move_assignable_v<T> && __check_narrowing<T, Args...>::value;
}  // namespace __detail

template <class T, class... Args>
CANN_ASC_STL_API constexpr T* construct_at(T* location, Args&&... args)
{
    CANN_ASC_STL_DETAIL_ASSERT(location != nullptr, "null pointer given to construct_at");
    // 平凡且非窄化类型走赋值快径（规避 placement new 的冗余空指针检查）；
    // 常量求值期仍走 placement new（赋值到未开始生命期的存储不可常量求值）。
    if constexpr (__detail::__can_optimize_construct_at<T, Args...>) {
        if (!__default_is_constant_evaluated()) {
            *location = T{::asc::std::forward<Args>(args)...};
            return location;
        }
    }
    return ::new (::asc::std::__voidify(*location)) T(::asc::std::forward<Args>(args)...);
}

template <class T, class... Args>
CANN_ASC_STL_API constexpr T* __construct_at(T* location, Args&&... args)
{
    return ::asc::std::construct_at(location, ::asc::std::forward<Args>(args)...);
}

template <class T>
CANN_ASC_STL_API constexpr void __destroy_at([[maybe_unused]] T* location)
{
    CANN_ASC_STL_DETAIL_ASSERT(location != nullptr, "null pointer given to __destroy_at");
    if constexpr (is_array_v<T>) {
        for (auto& value : *location) {
            ::asc::std::__destroy_at(::asc::std::addressof(value));
        }
    } else if constexpr (!is_trivially_destructible_v<T>) {
        location->~T();
    }
}

template <class ForwardIter>
CANN_ASC_STL_API constexpr ForwardIter __destroy(ForwardIter first, ForwardIter last)
{
    for (; first != last; ++first) {
        ::asc::std::__destroy_at(::asc::std::addressof(*first));
    }
    return first;
}

template <class BidirectionalIter>
CANN_ASC_STL_API constexpr BidirectionalIter __reverse_destroy(BidirectionalIter first, BidirectionalIter last)
{
    while (last != first) {
        --last;
        ::asc::std::__destroy_at(::asc::std::addressof(*last));
    }
    return last;
}

template <class T>
CANN_ASC_STL_API constexpr void destroy_at([[maybe_unused]] T* location)
{
    CANN_ASC_STL_DETAIL_ASSERT(location != nullptr, "null pointer given to destroy_at");
    ::asc::std::__destroy_at(location);
}

template <class ForwardIter>
CANN_ASC_STL_API constexpr void destroy(ForwardIter first, ForwardIter last)
{
    (void)::asc::std::__destroy(::asc::std::move(first),  // NOLINT(build/include_what_you_use)
        ::asc::std::move(last));                          // NOLINT(build/include_what_you_use)
}

template <class ForwardIter, class Size>
CANN_ASC_STL_API constexpr ForwardIter destroy_n(ForwardIter first, Size count)
{
    for (; count > 0; --count, ++first) {
        ::asc::std::__destroy_at(::asc::std::addressof(*first));
    }
    return first;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_CONSTRUCT_AT_H
