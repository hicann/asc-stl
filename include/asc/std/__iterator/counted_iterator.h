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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_COUNTED_ITERATOR_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_COUNTED_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/common_with.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__exception/exception_macros.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/default_sentinel.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/exception_guard.h>
#include <asc/std/__utility/move.h>

// 源头 spaceship 门控的三方比较头分支
// 按已复核的条件依赖裁决移除（该头在本源检出不存在，spaceship 双侧禁用），
// 对应 operator<=> 重载一并不迁移，比较语义由上方的传统关系运算符承担。

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class, class = void>
struct __counted_iterator_concept {};

template <class _Iter>
struct __counted_iterator_concept<_Iter, void_t<typename _Iter::iterator_concept>> {
    using iterator_concept = typename _Iter::iterator_concept;
};

template <class, class = void>
struct __counted_iterator_category {};

template <class _Iter>
struct __counted_iterator_category<_Iter, void_t<typename _Iter::iterator_category>> {
    using iterator_category = typename _Iter::iterator_category;
};

template <class, class = void>
struct __counted_iterator_value_type {};

template <class _Iter>
struct __counted_iterator_value_type<_Iter, enable_if_t<indirectly_readable<_Iter>>> {
    using value_type = iter_value_t<_Iter>;
};

CANN_ASC_STL_DETAIL_ACCL_BEGIN_HIDDEN_FRIEND_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator _Iter>
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Iter, enable_if_t<input_or_output_iterator<_Iter>, int> = 0>
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
class counted_iterator : public __counted_iterator_concept<_Iter>,
                         public __counted_iterator_category<_Iter>,
                         public __counted_iterator_value_type<_Iter> {
public:
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Iter __current_ = _Iter();
    iter_difference_t<_Iter> __count_ = 0;

    using iterator_type = _Iter;
    using difference_type = iter_difference_t<_Iter>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    CANN_ASC_STL_API constexpr counted_iterator()
        requires default_initializable<_Iter>
    = default;
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(default_initializable<_I2>)
    CANN_ASC_STL_API constexpr counted_iterator() noexcept(is_nothrow_default_constructible_v<_I2>)
    {}
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

    CANN_ASC_STL_API constexpr counted_iterator(_Iter __iter, iter_difference_t<_Iter> __n) noexcept(
        is_nothrow_move_constructible_v<_Iter>)
        : __current_(::asc::std::move(__iter)), __count_(__n)
    {
        CANN_ASC_STL_DETAIL_ASSERT(__n >= 0, "__n must not be negative.");
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(convertible_to<const _I2&, _Iter>)
    CANN_ASC_STL_API constexpr counted_iterator(const counted_iterator<_I2>& __other) noexcept(
        is_nothrow_constructible_v<_Iter, const _I2&>)
        : __current_(__other.__current_), __count_(__other.__count_)
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(assignable_from<_Iter&, const _I2&>)
    CANN_ASC_STL_API constexpr counted_iterator& operator=(const counted_iterator<_I2>& __other) noexcept(
        is_nothrow_assignable_v<_Iter&, const _I2&>)
    {
        __current_ = __other.__current_;
        __count_ = __other.__count_;
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr const _Iter& base() const& noexcept
    {
        return __current_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr _Iter base() &&
    {
        return ::asc::std::move(__current_);  // NOLINT(build/include_what_you_use)
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr iter_difference_t<_Iter> count() const noexcept
    {
        return __count_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) operator*()
    {
        CANN_ASC_STL_DETAIL_ASSERT(__count_ > 0, "Iterator is equal to or past end.");
        return *__current_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__dereferenceable<const _I2>)
    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) operator*() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(__count_ > 0, "Iterator is equal to or past end.");
        return *__current_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(contiguous_iterator<_I2>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator->() const noexcept
    {
        return ::asc::std::to_address(__current_);
    }

    CANN_ASC_STL_API constexpr counted_iterator& operator++()
    {
        CANN_ASC_STL_DETAIL_ASSERT(__count_ > 0, "Iterator already at or past end.");
        ++__current_;
        --__count_;
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!forward_iterator<_I2>))
    CANN_ASC_STL_API decltype(auto) operator++(int)
    {
        CANN_ASC_STL_DETAIL_ASSERT(__count_ > 0, "Iterator already at or past end.");
        --__count_;
        // 源侧 NV_IF_ELSE_TARGET 的 host 异常回滚语义映射为条件异常宏：
        // 可抛异常的 host 路径回滚 __count_ 后重抛，设备/无异常路径直退。
        CANN_ASC_STL_DETAIL_ACCL_TRY
        {
            return __current_++;
        }
        CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL
        {
            ++__count_;
            CANN_ASC_STL_DETAIL_ACCL_RETHROW;
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(forward_iterator<_I2>)
    CANN_ASC_STL_API constexpr counted_iterator operator++(int)
    {
        CANN_ASC_STL_DETAIL_ASSERT(__count_ > 0, "Iterator already at or past end.");
        counted_iterator __tmp = *this;
        ++*this;
        return __tmp;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(bidirectional_iterator<_I2>)
    CANN_ASC_STL_API constexpr counted_iterator& operator--()
    {
        --__current_;
        ++__count_;
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(bidirectional_iterator<_I2>)
    CANN_ASC_STL_API constexpr counted_iterator operator--(int)
    {
        counted_iterator __tmp = *this;
        --*this;
        return __tmp;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_iterator<_I2>)
    [[nodiscard]] CANN_ASC_STL_API constexpr counted_iterator operator+(iter_difference_t<_I2> __n) const
    {
        return counted_iterator(__current_ + __n, __count_ - __n);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_iterator<_I2>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr counted_iterator operator+(
        iter_difference_t<_I2> __n, const counted_iterator& __x)
    {
        return __x + __n;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_iterator<_I2>)
    CANN_ASC_STL_API constexpr counted_iterator& operator+=(iter_difference_t<_I2> __n)
    {
        CANN_ASC_STL_DETAIL_ASSERT(__n <= __count_, "Cannot advance iterator past end.");
        __current_ += __n;
        __count_ -= __n;
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_iterator<_I2>)
    [[nodiscard]] CANN_ASC_STL_API constexpr counted_iterator operator-(iter_difference_t<_I2> __n) const
    {
        return counted_iterator(__current_ - __n, __count_ + __n);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(common_with<_I2, _Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_difference_t<_I2> operator-(
        const counted_iterator& __lhs, const counted_iterator<_I2>& __rhs)
    {
        return __rhs.__count_ - __lhs.__count_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_iterator<_I2>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_difference_t<_I2> operator-(
        const counted_iterator& __lhs, const counted_iterator& __rhs)
    {
        return __rhs.__count_ - __lhs.__count_;
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_difference_t<_Iter> operator-(
        const counted_iterator& __lhs, default_sentinel_t)
    {
        return -__lhs.__count_;
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_difference_t<_Iter> operator-(
        default_sentinel_t, const counted_iterator& __rhs)
    {
        return __rhs.__count_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_iterator<_I2>)
    CANN_ASC_STL_API constexpr counted_iterator& operator-=(iter_difference_t<_I2> __n)
    {
        CANN_ASC_STL_DETAIL_ASSERT(-__n <= __count_,
            "Attempt to subtract too large of a size: "
            "counted_iterator would be decremented before the "
            "first element of its range.");
        __current_ -= __n;
        __count_ += __n;
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_iterator<_I2>)
    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) operator[](iter_difference_t<_I2> __n) const
    {
        CANN_ASC_STL_DETAIL_ASSERT(__n < __count_, "Subscript argument must be less than size.");
        return __current_[__n];
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(common_with<_I2, _Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const counted_iterator& __lhs, const counted_iterator<_I2>& __rhs) noexcept
    {
        return __lhs.__count_ == __rhs.__count_;
    }

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const counted_iterator& __lhs, const counted_iterator& __rhs) noexcept
    {
        return __lhs.__count_ == __rhs.__count_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(common_with<_I2, _Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const counted_iterator& __lhs, const counted_iterator<_I2>& __rhs) noexcept
    {
        return __lhs.__count_ != __rhs.__count_;
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const counted_iterator& __lhs, default_sentinel_t) noexcept
    {
        return __lhs.__count_ == 0;
    }

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        default_sentinel_t, const counted_iterator& __lhs) noexcept
    {
        return __lhs.__count_ == 0;
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const counted_iterator& __lhs, default_sentinel_t) noexcept
    {
        return __lhs.__count_ != 0;
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        default_sentinel_t, const counted_iterator& __lhs) noexcept
    {
        return __lhs.__count_ != 0;
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(common_with<_I2, _Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator<(
        const counted_iterator& __lhs, const counted_iterator<_I2>& __rhs) noexcept
    {
        return __lhs.__count_ < __rhs.__count_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(common_with<_I2, _Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator<=(
        const counted_iterator& __lhs, const counted_iterator<_I2>& __rhs) noexcept
    {
        return __lhs.__count_ <= __rhs.__count_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(common_with<_I2, _Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator>(
        const counted_iterator& __lhs, const counted_iterator<_I2>& __rhs) noexcept
    {
        return __lhs.__count_ > __rhs.__count_;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(common_with<_I2, _Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator>=(
        const counted_iterator& __lhs, const counted_iterator<_I2>& __rhs) noexcept
    {
        return __lhs.__count_ >= __rhs.__count_;
    }

    template <class _I2>
    CANN_ASC_STL_API friend constexpr auto iter_swap(const counted_iterator& __x,
        const counted_iterator<_I2>& __y) noexcept(noexcept(::asc::std::ranges::__iter_swap_cpo{}(__x.__current_,
        __y.__current_))) CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES(void)(indirectly_swappable<_I2, _Iter>)
    {
        CANN_ASC_STL_DETAIL_ASSERT(__x.__count_ > 0 && __y.__count_ > 0, "Iterators must not be past end of range.");
        return ::asc::std::ranges::__iter_swap_cpo{}(__x.__current_, __y.__current_);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _I2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_iterator<_I2>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr decltype(auto) iter_move(const counted_iterator& __i) noexcept(
        noexcept(::asc::std::ranges::__iter_move_cpo{}(__i.base())))
    {
        CANN_ASC_STL_DETAIL_ASSERT(__i.count() > 0, "Iterator must not be past end of range.");
        return ::asc::std::ranges::__iter_move_cpo{}(__i.base());
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(counted_iterator);
CANN_ASC_STL_DETAIL_ACCL_END_HIDDEN_FRIEND_NAMESPACE(counted_iterator)

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_iterator _Iter>
    requires same_as<_ITER_TRAITS<_Iter>, iterator_traits<_Iter>>
struct iterator_traits<counted_iterator<_Iter>> : iterator_traits<_Iter> {
    using pointer = conditional_t<contiguous_iterator<_Iter>, add_pointer_t<iter_reference_t<_Iter>>, void>;
};
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Iter>
struct iterator_traits<counted_iterator<_Iter>,
    enable_if_t<input_iterator<_Iter> && same_as<_ITER_TRAITS<_Iter>, iterator_traits<_Iter>>>>
    : iterator_traits<_Iter> {
    using pointer = conditional_t<contiguous_iterator<_Iter>, add_pointer_t<iter_reference_t<_Iter>>, void>;
};

// In C++17 we end up in an infinite recursion trying to determine the return type of `to_address`
template <class _Iter>
struct pointer_traits<counted_iterator<_Iter>, enable_if_t<contiguous_iterator<_Iter>>> {
    using pointer = counted_iterator<_Iter>;
    using element_type = typename pointer_traits<_Iter>::element_type;
    using difference_type = typename pointer_traits<_Iter>::difference_type;

    CANN_ASC_STL_API static constexpr auto to_address(const pointer __iter) noexcept
    {
        return ::asc::std::to_address(__iter.base());
    }
};
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_COUNTED_ITERATOR_H
