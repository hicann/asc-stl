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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_TYPEID_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_TYPEID_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__string/string_view.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/cstddef>

#if CANN_ASC_STL_DETAIL_HOSTED() && !defined(CANN_ASC_STL_DETAIL_NO_TYPEID)
#include <typeinfo>
#endif

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
using __typeid_only_supports_types = _Tp;

template <class _Tp>
struct __pretty_name_begin {
    struct __pretty_name_end;
};

[[nodiscard]] CANN_ASC_STL_API constexpr __string_view __find_pretty_name(__string_view __sv) noexcept
{
    ptrdiff_t __first = -1;
    ptrdiff_t __last = -1;
    for (ptrdiff_t __i = 0; __i < static_cast<ptrdiff_t>(__sv.size()); ++__i) {
        if (__sv[__i] == '<' && __first == -1) {
            __first = __i + 1;
        } else if (__sv[__i] == '>') {
            __last = __i;
        }
    }
    return __first == -1 || __last < __first ? __string_view(__sv.begin(), size_t(0)) : __sv.substr(__first, __last);
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr __string_view __pretty_nameof_helper() noexcept
{
    return __find_pretty_name(__string_view(CANN_ASC_STL_DETAIL_BUILTIN_PRETTY_FUNCTION()));
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr __string_view __pretty_nameof() noexcept
{
    return __pretty_nameof_helper<typename __pretty_name_begin<_Tp>::__pretty_name_end>();
}

// 回退实现保持纯类型/值机制: BiSheng 不允许在 aicore 函数中使用
// 源实现的变量模板或间接函数调用; 字符串视图句柄在不使用这两者的
// 前提下保持可观测的相等性/序/名称契约。
struct __type_info;
struct __type_info_ptr_;
struct __type_info_ref_;

struct __type_info {
    __type_info() = delete;
    __type_info(__type_info const&) = delete;
    __type_info& operator=(__type_info const&) = delete;

    CANN_ASC_STL_API explicit constexpr __type_info(__string_view __name) noexcept : __name_(__name)
    {}

    [[nodiscard]] CANN_ASC_STL_API constexpr char const* name() const noexcept
    {
        return __name_.begin();
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr __string_view __name_view() const noexcept
    {
        return __name_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr bool before(__type_info const& __other) const noexcept
    {
        return __name_ < __other.__name_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr __type_info_ptr_ operator&() const noexcept;  // NOLINT(runtime/operator)

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        __type_info const& __lhs, __type_info const& __rhs) noexcept
    {
        return __lhs.__name_ == __rhs.__name_;
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const __type_info& __lhs, const __type_info& __rhs) noexcept
    {
        return !(__lhs == __rhs);
    }

private:
    friend struct __type_info_ref_;
    CANN_ASC_STL_API constexpr __type_info(__type_info const& __other, int) noexcept : __name_(__other.__name_)
    {}

    __string_view __name_;
};

struct __type_info_ref_ : __type_info {
    CANN_ASC_STL_API explicit constexpr __type_info_ref_(__string_view __name) noexcept : __type_info(__name)
    {}

    CANN_ASC_STL_API constexpr __type_info_ref_(__type_info const& __other) noexcept : __type_info(__other, 0)
    {}

    CANN_ASC_STL_API constexpr __type_info_ref_(__type_info_ref_ const& __other) noexcept : __type_info(__other, 0)
    {}
};

struct __type_info_ptr_ {
    constexpr __type_info_ptr_() noexcept = default;

    CANN_ASC_STL_API explicit constexpr __type_info_ptr_(__string_view __name) noexcept : __name_(__name)
    {}

    [[nodiscard]] CANN_ASC_STL_API constexpr __type_info_ref_ operator*() const noexcept
    {
        return __type_info_ref_(__name_);
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        __type_info_ptr_ __lhs, __type_info_ptr_ __rhs) noexcept
    {
        return __lhs.__name_ == __rhs.__name_;
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const __type_info_ptr_ __lhs, const __type_info_ptr_ __rhs) noexcept
    {
        return !(__lhs == __rhs);
    }

private:
    __string_view __name_{nullptr, 0};
};

[[nodiscard]] CANN_ASC_STL_API constexpr __type_info_ptr_ __type_info::operator&()  // NOLINT(runtime/operator)
    const noexcept                                                                  // NOLINT(runtime/operator)
{
    return __type_info_ptr_(__name_);
}

#if CANN_ASC_STL_DETAIL_HOSTED() && !defined(CANN_ASC_STL_DETAIL_NO_TYPEID)

using type_info = ::std::type_info;
using __type_info_ptr = type_info const*;
using __type_info_ref = type_info const&;

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_HOST_API type_info const& __typeid() noexcept
{
    return typeid(__typeid_only_supports_types<_Tp>);
}

#else

using type_info = __type_info;
using __type_info_ptr = __type_info_ptr_;
using __type_info_ref = __type_info_ref_;

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr __type_info_ref_ __typeid() noexcept
{
    return __type_info_ref_(__pretty_nameof<remove_cv_t<_Tp> >());
}

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_TYPEID_H
