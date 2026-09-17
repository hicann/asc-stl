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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_LEAF_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_LEAF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER
#include <asc/std/__tuple_dir/make_tuple_types.h>
#include <asc/std/__tuple_dir/sfinae_helpers.h>
#include <asc/std/__tuple_dir/tuple_constraints.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__tuple_dir/tuple_indices.h>
#include <asc/std/__tuple_dir/tuple_types.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_final.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

struct __tuple_leaf_default_constructor_tag {};

enum class __tuple_leaf_specialization {
    __default,
    __synthesize_assignment,
    __empty_non_final,
};

// 2026-09-16 根因修复（tuple 债二）：__tuple_impl 的递归实现以 __tuple_impl<> 作空尾终止基。
// 空类型叶（__empty_non_final）私有继承元素以做 EBO——当元素本身是元组（tuple<tuple<空>...>、
// bind_back 的 tuple<fn, tuple<closure>> 等）时，内层元组的 __tuple_impl<> 会经由
// 「叶 → 元素 → 内层 impl」链成为外层 impl 的第二个子对象，使 __base_t 转换产生歧义基类。
// __tuple_impl 以本标记为基，选择器对「已派生标记的元素」退回成员存储，切断第二条子对象路径；
// 代价仅是「元组作元素」这一种情形不再 EBO（std 对此同样无布局保证）。
struct __tuple_impl_base {};

template <class _Tp>
CANN_ASC_STL_API constexpr __tuple_leaf_specialization __tuple_leaf_choose()
{
    return is_empty_v<_Tp> && !is_final_v<_Tp> && !is_base_of_v<__tuple_impl_base, remove_cv_t<_Tp>> ?
        __tuple_leaf_specialization::__empty_non_final :
        __must_synthesize_assignment_v<_Tp> ? __tuple_leaf_specialization::__synthesize_assignment :
                                              __tuple_leaf_specialization::__default;
}

template <size_t _Ip, class _Hp, __tuple_leaf_specialization = __tuple_leaf_choose<_Hp>()>
class __tuple_leaf;

template <size_t _Ip, class _Hp, __tuple_leaf_specialization _Ep>
CANN_ASC_STL_API void swap(__tuple_leaf<_Ip, _Hp, _Ep>& __x, __tuple_leaf<_Ip, _Hp, _Ep>& __y) noexcept(
    __is_nothrow_swappable<_Hp>::value)
{
    swap(__x.__get(), __y.__get());
}

template <class _Tp, class _Up, class _Current, bool = !is_same_v<remove_cvref_t<_Tp>, _Current>>
inline constexpr bool __tuple_leaf_can_forward = false;
template <class _Tp, class _Up, class _Current>
inline constexpr bool __tuple_leaf_can_forward<_Tp, _Up, _Current, true> = is_constructible_v<_Up, _Tp>;

// Default specialization: non-empty, non-reference types.
template <size_t _Ip, class _Hp>
class __tuple_leaf<_Ip, _Hp, __tuple_leaf_specialization::__default> {
    _Hp __value_;

public:
    CANN_ASC_STL_API constexpr __tuple_leaf() noexcept(is_nothrow_default_constructible_v<_Hp>) : __value_()
    {}

    CANN_ASC_STL_API constexpr __tuple_leaf(__tuple_leaf_default_constructor_tag) noexcept(
        is_nothrow_default_constructible_v<_Hp>)
        : __value_()
    {}

    template <class _Alloc>
    CANN_ASC_STL_API __tuple_leaf(integral_constant<int, 0>, const _Alloc&) : __value_()
    {}

    CANN_ASC_STL_API constexpr __tuple_leaf(const __tuple_leaf& __x) noexcept(is_nothrow_copy_constructible_v<_Hp>)
        : __value_(__x.__value_)
    {}

    CANN_ASC_STL_API constexpr __tuple_leaf(__tuple_leaf&& __x) noexcept(is_nothrow_move_constructible_v<_Hp>)
        : __value_(::asc::std::move(__x.__value_))
    {}

    template <class _Tp,
        enable_if_t<__tuple_leaf_can_forward<_Tp, _Hp, __tuple_leaf> && is_convertible_v<_Tp, _Hp>, int> = 0>
    CANN_ASC_STL_API constexpr __tuple_leaf(_Tp&& __t) : __value_(::asc::std::forward<_Tp>(__t))
    {}
    template <class _Tp,
        enable_if_t<__tuple_leaf_can_forward<_Tp, _Hp, __tuple_leaf> && !is_convertible_v<_Tp, _Hp>, int> = 0>
    CANN_ASC_STL_API constexpr explicit __tuple_leaf(_Tp&& __t) : __value_(::asc::std::forward<_Tp>(__t))
    {}

    CANN_ASC_STL_API __tuple_leaf& operator=(const __tuple_leaf& __x)
    {
        __value_ = __x.__value_;
        return *this;
    }

    CANN_ASC_STL_API __tuple_leaf& operator=(__tuple_leaf&& __x) noexcept(is_nothrow_assignable_v<_Hp&, _Hp&&>)
    {
        __value_ = ::asc::std::move(__x.__value_);
        return *this;
    }

    template <class _Up>
    CANN_ASC_STL_API __tuple_leaf& operator=(_Up&& __x)
    {
        __value_ = ::asc::std::forward<_Up>(__x);
        return *this;
    }

    CANN_ASC_STL_API void swap(__tuple_leaf& __y) noexcept(__is_nothrow_swappable<_Hp>::value)
    {
        ::asc::std::swap(__value_, __y.__value_);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr _Hp& __get() & noexcept
    {
        return __value_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Hp& __get() const& noexcept
    {
        return __value_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr _Hp&& __get() && noexcept
    {
        return ::asc::std::move(__value_);
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Hp&& __get() const&& noexcept
    {
        return ::asc::std::move(__value_);
    }
};

// Synthesize assignment for reference and const types.
// 2026-09 根因修复：原实现继承 __default 特化并声明 move assignment，导致
// 隐式 copy ctor 被 deleted（C++ 规则：声明 move assignment 删除隐式 copy ctor）。
// tuple<int&&> 等引用元组在整个 __tuple_cat 链上一旦被按值传递即编译失败或产生
// 悬垂。改为独立类（照 CCCL 做法）：自行存储 _Hp __value_，提供完整的拷贝/移动
// 构造/赋值，语义与 __default 一致但附加 synthesize assignment。
template <size_t _Ip, class _Hp>
class __tuple_leaf<_Ip, _Hp, __tuple_leaf_specialization::__synthesize_assignment> {
    _Hp __value_;

public:
    CANN_ASC_STL_API constexpr __tuple_leaf() noexcept(is_nothrow_default_constructible_v<_Hp>) : __value_()
    {}

    template <class _Up, enable_if_t<is_constructible_v<_Hp, _Up&&>, int> = 0>
    CANN_ASC_STL_API constexpr explicit __tuple_leaf(_Up&& __u) : __value_(::asc::std::forward<_Up>(__u))
    {}

    CANN_ASC_STL_API constexpr __tuple_leaf(const __tuple_leaf& __x) : __value_(static_cast<_Hp>(__x.__value_))
    {}

    CANN_ASC_STL_API constexpr __tuple_leaf(__tuple_leaf&& __x)
        : __value_(static_cast<_Hp>(::asc::std::move(__x.__value_)))
    {}

    CANN_ASC_STL_API __tuple_leaf& operator=(const __tuple_leaf& __x)
    {
        this->__get() = __x.__get();
        return *this;
    }

    CANN_ASC_STL_API __tuple_leaf& operator=(__tuple_leaf&& __x)
    {
        this->__get() = ::asc::std::move(__x.__get());
        return *this;
    }

    CANN_ASC_STL_API constexpr _Hp& __get() noexcept
    {
        return __value_;
    }

    CANN_ASC_STL_API constexpr const _Hp& __get() const noexcept
    {
        return __value_;
    }
};

// Empty non-final types: inherit for EBO.
template <size_t _Ip, class _Hp>
class __tuple_leaf<_Ip, _Hp, __tuple_leaf_specialization::__empty_non_final> : private _Hp {
public:
    CANN_ASC_STL_API constexpr __tuple_leaf() noexcept(is_nothrow_default_constructible_v<_Hp>) : _Hp()
    {}

    CANN_ASC_STL_API constexpr __tuple_leaf(__tuple_leaf_default_constructor_tag) noexcept(
        is_nothrow_default_constructible_v<_Hp>)
        : _Hp()
    {}

    CANN_ASC_STL_API constexpr __tuple_leaf(const _Hp& __x) : _Hp(__x)
    {}

    CANN_ASC_STL_API constexpr __tuple_leaf(_Hp&& __x) : _Hp(::asc::std::move(__x))
    {}

    // 约束模板赋值（对齐源侧）：非模板移动赋值会删除隐式拷贝构造，
    // 导致含空类元素（如 range adaptor closure）的元组不可复制。
    template <class _Tp, enable_if_t<is_assignable_v<_Hp&, const _Tp&>, int> = 0>
    CANN_ASC_STL_API __tuple_leaf& operator=(const _Tp& __x) noexcept(is_nothrow_assignable_v<_Hp&, const _Tp&>)
    {
        _Hp::operator=(__x);
        return *this;
    }

    template <class _Tp, enable_if_t<is_assignable_v<_Hp&, _Tp>, int> = 0>
    CANN_ASC_STL_API __tuple_leaf& operator=(_Tp&& __x) noexcept(is_nothrow_assignable_v<_Hp&, _Tp>)
    {
        _Hp::operator=(::asc::std::move(__x));
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr _Hp& __get() & noexcept
    {
        return *this;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Hp& __get() const& noexcept
    {
        return *this;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr _Hp&& __get() && noexcept
    {
        return ::asc::std::move(*this);
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const _Hp&& __get() const&& noexcept
    {
        return ::asc::std::move(*this);  // NOLINT(build/include_what_you_use)
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_LEAF_H
