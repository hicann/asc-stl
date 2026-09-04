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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_MOVE_ITERATOR_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_MOVE_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// 源头 spaceship 门控的 __compare 条件 include 分支按已复核的条件依赖裁决
// 移除（__compare 家族在本源检出不存在、spaceship 双侧禁用），比较语义
// 由传统关系运算符（operator</>/<=/>=）承担。
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/move_sentinel.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_convertible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Iter, class = void>
struct __move_iter_category_base {};

template <class _Iter>
    requires requires { typename iterator_traits<_Iter>::iterator_category; }
struct __move_iter_category_base<_Iter> {
    using iterator_category =
        _If<derived_from<__iterator_traits_category_or_concept_t<_Iter>, random_access_iterator_tag>,
            random_access_iterator_tag, __iterator_traits_category_or_concept_t<_Iter>>;
};

template <class _Iter, class _Sent>
concept __move_iter_comparable = requires {
    { declval<const _Iter&>() == declval<_Sent>() } -> convertible_to<bool>;
};

template <class _Iter>
inline constexpr bool __noexcept_move_iter_iter_move =
    noexcept(::asc::std::ranges::__iter_move_cpo{}(::asc::std::declval<const _Iter&>()));
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Iter, class = void>
struct __move_iter_category_base {};

template <class _Iter>
struct __move_iter_category_base<_Iter, enable_if_t<__has_iter_category<iterator_traits<_Iter>>>> {
    using iterator_category =
        _If<derived_from<__iterator_traits_category_or_concept_t<_Iter>, random_access_iterator_tag>,
            random_access_iterator_tag, __iterator_traits_category_or_concept_t<_Iter>>;
};

template <class _Iter, class _Sent>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__move_iter_comparable_,
    requires()(requires(convertible_to<decltype(declval<const _Iter&>() == declval<_Sent>()), bool>)));

template <class _Iter, class _Sent>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __move_iter_comparable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__move_iter_comparable_, _Iter, _Sent);

template <class _Iter>
inline constexpr bool __noexcept_move_iter_iter_move =
    noexcept(::asc::std::ranges::__iter_move_cpo{}(::asc::std::declval<const _Iter&>()));
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_HIDDEN_FRIEND_NAMESPACE

template <class _Iter>
class move_iterator : public __move_iter_category_base<_Iter> {
private:
    template <class _It2>
    friend class move_iterator;

    _Iter __current_;

    CANN_ASC_STL_API static constexpr auto __mi_get_iter_concept()
    {
        if constexpr (random_access_iterator<_Iter>) {
            return random_access_iterator_tag{};
        } else if constexpr (bidirectional_iterator<_Iter>) {
            return bidirectional_iterator_tag{};
        } else if constexpr (forward_iterator<_Iter>) {
            return forward_iterator_tag{};
        } else {
            return input_iterator_tag{};
        }
    }

public:
    using iterator_type = _Iter;
    using iterator_concept = decltype(__mi_get_iter_concept());

    // iterator_category is inherited and not always present
    using value_type = iter_value_t<_Iter>;
    using difference_type = iter_difference_t<_Iter>;
    using pointer = _Iter;
    using reference = iter_rvalue_reference_t<_Iter>;

    CANN_ASC_STL_API constexpr explicit move_iterator(_Iter __i) noexcept(is_nothrow_move_constructible_v<_Iter>)
        : __current_(::asc::std::move(__i))
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _It2 = _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_default_constructible_v<_It2>)
    CANN_ASC_STL_API constexpr move_iterator() noexcept(is_nothrow_default_constructible_v<_It2>) : __current_()
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (!is_same_v<_Up, _Iter>)CANN_ASC_STL_DETAIL_ACCL_AND convertible_to<const _Up&, _Iter>)
    CANN_ASC_STL_API constexpr move_iterator(const move_iterator<_Up>& __u) noexcept(
        is_nothrow_convertible_v<const _Up&, _Iter>)
        : __current_(__u.base())
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        (!is_same_v<_Up, _Iter>)CANN_ASC_STL_DETAIL_ACCL_AND convertible_to<const _Up&, _Iter>
            CANN_ASC_STL_DETAIL_ACCL_AND assignable_from<_Iter&, const _Up&>)
    CANN_ASC_STL_API constexpr move_iterator& operator=(const move_iterator<_Up>& __u) noexcept(
        is_nothrow_assignable_v<_Iter&, const _Up&>)
    {
        __current_ = __u.base();
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr const _Iter& base() const& noexcept
    {
        return __current_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr _Iter base() &&
    {
        return ::asc::std::move(__current_);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr reference operator*() const
    {
        return ::asc::std::ranges::__iter_move_cpo{}(__current_);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr reference operator[](difference_type __n) const
    {
        return ::asc::std::ranges::__iter_move_cpo{}(__current_ + __n);
    }

    [[nodiscard]] CANN_ASC_STL_DETAIL_DEPRECATED_IN_CXX20 CANN_ASC_STL_API constexpr pointer operator->() const
    {
        return __current_;
    }

    CANN_ASC_STL_API constexpr move_iterator& operator++()
    {
        ++__current_;
        return *this;
    }

    CANN_ASC_STL_API constexpr auto operator++(int)
    {
        if constexpr (forward_iterator<_Iter>) {
            move_iterator __tmp{*this};
            ++__current_;
            return __tmp;
        } else {
            ++__current_;
        }
    }

    CANN_ASC_STL_API constexpr move_iterator& operator--()
    {
        --__current_;
        return *this;
    }

    CANN_ASC_STL_API constexpr move_iterator operator--(int)
    {
        move_iterator __tmp{*this};
        --__current_;
        return __tmp;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr move_iterator operator+(difference_type __n) const
    {
        return move_iterator{__current_ + __n};
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr move_iterator operator+(
        difference_type __n, const move_iterator& __x)
    {
        return move_iterator{__x.base() + __n};
    }

    CANN_ASC_STL_API constexpr move_iterator& operator+=(difference_type __n)
    {
        __current_ += __n;
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr move_iterator operator-(difference_type __n) const
    {
        return move_iterator{__current_ - __n};
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator-(
        const move_iterator& __x, const move_iterator<_Iter2>& __y) -> decltype(::asc::std::declval<const _Iter&>() -
                                                                        ::asc::std::declval<const _Iter2&>())
    {
        return __x.base() - __y.base();
    }

    CANN_ASC_STL_API constexpr move_iterator& operator-=(difference_type __n)
    {
        __current_ -= __n;
        return *this;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Sent)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        sentinel_for<_Sent, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND __move_iter_comparable<_Iter, _Sent>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const move_iterator& __x, const move_sentinel<_Sent>& __y)
    {
        return __x.base() == __y.base();
    }

#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Sent)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        sentinel_for<_Sent, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND __move_iter_comparable<_Iter, _Sent>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const move_sentinel<_Sent>& __y, const move_iterator& __x)
    {
        return __y.base() == __x.base();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Sent)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        sentinel_for<_Sent, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND __move_iter_comparable<_Iter, _Sent>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const move_iterator& __x, const move_sentinel<_Sent>& __y)
    {
        return __x.base() != __y.base();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Sent)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        sentinel_for<_Sent, _Iter> CANN_ASC_STL_DETAIL_ACCL_AND __move_iter_comparable<_Iter, _Sent>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const move_sentinel<_Sent>& __y, const move_iterator& __x)
    {
        return __y.base() != __x.base();
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator==(const move_iterator& __x,
        const move_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() ==
                                              ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() == __y.base();
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator!=(const move_iterator& __x,
        const move_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() !=
                                              ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() != __y.base();
    }

    // 源头 spaceship 分支按条件依赖裁决移除：比较语义由以下传统关系运算符承担。
    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator<(const move_iterator& __x,
        const move_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() <
                                              ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() < __y.base();
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator>(const move_iterator& __x,
        const move_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() >
                                              ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() > __y.base();
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator<=(const move_iterator& __x,
        const move_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() <=
                                              ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() <= __y.base();
    }

    template <class _Iter2>
    [[nodiscard]] CANN_ASC_STL_API friend constexpr auto operator>=(const move_iterator& __x,
        const move_iterator<_Iter2>& __y) -> decltype(static_cast<bool>(::asc::std::declval<const _Iter&>() >=
                                              ::asc::std::declval<const _Iter2&>()))
    {
        return __x.base() >= __y.base();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Sent)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(sized_sentinel_for<_Sent, _Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_difference_t<_Iter> operator-(
        const move_sentinel<_Sent>& __x, const move_iterator& __y)
    {
        return __x.base() - __y.base();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Sent)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(sized_sentinel_for<_Sent, _Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_difference_t<_Iter> operator-(
        const move_iterator& __x, const move_sentinel<_Sent>& __y)
    {
        return __x.base() - __y.base();
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr iter_rvalue_reference_t<_Iter> iter_move(
        const move_iterator& __i) noexcept(__noexcept_move_iter_iter_move<_Iter>)
    {
        return ::asc::std::ranges::__iter_move_cpo{}(__i.__current_);
    }

    template <class _Iter2>
    CANN_ASC_STL_API friend constexpr auto iter_swap(
        const move_iterator& __x, const move_iterator<_Iter2>& __y) noexcept(__noexcept_swappable<_Iter, _Iter2>)
        CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES(void)(indirectly_swappable<_Iter2, _Iter>)
    {
        return ::asc::std::ranges::__iter_swap_cpo{}(__x.__current_, __y.__current_);
    }
};
CANN_ASC_STL_DETAIL_ACCL_CTAD_SUPPORTED_FOR_TYPE(move_iterator);
CANN_ASC_STL_DETAIL_ACCL_END_HIDDEN_FRIEND_NAMESPACE(move_iterator)

// Some compilers have issues determining __is_fancy_pointer
#if CANN_ASC_STL_DETAIL_COMPILER(GCC) || CANN_ASC_STL_DETAIL_COMPILER(MSVC)
template <class _Iter>
inline constexpr bool __is_fancy_pointer<move_iterator<_Iter>> = __is_fancy_pointer<_Iter>;
#endif  // CANN_ASC_STL_DETAIL_COMPILER(GCC) || CANN_ASC_STL_DETAIL_COMPILER(MSVC)

template <class _Iter>
[[nodiscard]] CANN_ASC_STL_API constexpr move_iterator<_Iter> make_move_iterator(_Iter __i) noexcept(
    is_nothrow_move_constructible_v<_Iter>)
{
    return move_iterator<_Iter>{::asc::std::move(__i)};  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_MOVE_ITERATOR_H
