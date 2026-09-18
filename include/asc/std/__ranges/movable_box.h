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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_MOVABLE_BOX_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_MOVABLE_BOX_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__tuple_dir/sfinae_helpers.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__utility/move.h>
#include <asc/std/optional>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

//! @brief Requirement for the boxed type: movable and a pure object.
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __movable_box_object = move_constructible<_Tp> && is_object_v<_Tp>;

//! @brief True when the box can drop the empty state entirely: the stored
//! type can always be re-created by assignment, so the optional layer
//! would only add size without adding behavior.
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEVAL bool __doesnt_need_empty_state() noexcept
{
    if constexpr (copy_constructible<_Tp>) {
        return copyable<_Tp> || (is_nothrow_move_constructible_v<_Tp> && is_nothrow_copy_constructible_v<_Tp>);
    } else {
        return movable<_Tp> || is_nothrow_move_constructible_v<_Tp>;
    }
}

//! @brief True when the holder may collapse into the surrounding object
//! through [[no_unique_address]] because the type is fully copyable.
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEVAL bool __can_use_no_unique_address() noexcept
{
    if constexpr (copy_constructible<_Tp>) {
        return copyable<_Tp>;
    } else {
        return movable<_Tp>;
    }
}

// ---------------------------------------------------------------------
// optional-backed flavor: the type needs an empty state
// ---------------------------------------------------------------------

template <class _Tp, bool = default_initializable<_Tp>>
struct __mb_optional_destruct_base {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS optional<_Tp> __val_;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_optional_destruct_base(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __val_(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}
};

template <class _Tp>
struct __mb_optional_destruct_base<_Tp, true> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS optional<_Tp> __val_;

    CANN_ASC_STL_API constexpr __mb_optional_destruct_base() noexcept(is_nothrow_default_constructible_v<_Tp>)
        : __val_(in_place_t{})
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_optional_destruct_base(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __val_(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}
};

template <class _Tp, bool = copy_constructible<_Tp>>
struct __mb_optional_copy_assign : __mb_optional_destruct_base<_Tp> {
    using __base = __mb_optional_destruct_base<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_optional_copy_assign(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_API constexpr __mb_optional_copy_assign(const __mb_optional_copy_assign&) = delete;
    CANN_ASC_STL_API constexpr __mb_optional_copy_assign(__mb_optional_copy_assign&&) = default;

    CANN_ASC_STL_API constexpr __mb_optional_copy_assign& operator=(const __mb_optional_copy_assign&) = delete;
    CANN_ASC_STL_API constexpr __mb_optional_copy_assign& operator=(__mb_optional_copy_assign&&) = default;
};

template <class _Tp>
struct __mb_optional_copy_assign<_Tp, true> : __mb_optional_destruct_base<_Tp> {
    using __base = __mb_optional_destruct_base<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_optional_copy_assign(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_API constexpr __mb_optional_copy_assign(const __mb_optional_copy_assign&) = default;
    CANN_ASC_STL_API constexpr __mb_optional_copy_assign(__mb_optional_copy_assign&&) = default;

    CANN_ASC_STL_API constexpr __mb_optional_copy_assign& operator=(const __mb_optional_copy_assign& __other) noexcept(
        is_nothrow_copy_constructible_v<_Tp>)
    {
        if (this != ::asc::std::addressof(__other)) {
            if (__other.__val_.has_value()) {
                this->__val_.emplace(*__other.__val_);
            } else {
                this->__val_.reset();
            }
        }
        return *this;
    };
    CANN_ASC_STL_API constexpr __mb_optional_copy_assign& operator=(__mb_optional_copy_assign&&) = default;
};

template <class _Tp, bool = movable<_Tp>>
struct __mb_optional_move_assign : __mb_optional_copy_assign<_Tp> {
    using __base = __mb_optional_copy_assign<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_optional_move_assign(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}
};

template <class _Tp>
struct __mb_optional_move_assign<_Tp, false> : __mb_optional_copy_assign<_Tp> {
    using __base = __mb_optional_copy_assign<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_optional_move_assign(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_API constexpr __mb_optional_move_assign(const __mb_optional_move_assign&) = default;
    CANN_ASC_STL_API constexpr __mb_optional_move_assign(__mb_optional_move_assign&&) = default;
    CANN_ASC_STL_API constexpr __mb_optional_move_assign& operator=(const __mb_optional_move_assign&) = default;

    CANN_ASC_STL_API constexpr __mb_optional_move_assign& operator=(__mb_optional_move_assign&& __other) noexcept(
        is_nothrow_move_constructible_v<_Tp>)
    {
        if (this != ::asc::std::addressof(__other)) {
            if (__other.__val_.has_value()) {
                this->__val_.emplace(::asc::std::move(*__other.__val_));
            } else {
                this->__val_.reset();
            }
        }
        return *this;
    }
};

template <class _Tp>
struct __mb_optional_base : __mb_optional_move_assign<_Tp> {
    using __base = __mb_optional_move_assign<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_optional_base(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp const& operator*() const noexcept
    {
        return *this->__val_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp& operator*() noexcept
    {
        return *this->__val_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr const _Tp* operator->() const noexcept
    {
        return this->__val_.operator->();
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp* operator->() noexcept
    {
        return this->__val_.operator->();
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr bool __has_value() const noexcept
    {
        return this->__val_.has_value();
    }
};

// ---------------------------------------------------------------------
// holder flavor: the type needs no empty state
// ---------------------------------------------------------------------

template <class _Tp, bool = __can_use_no_unique_address<_Tp>()>
struct __mb_holder {
    _Tp __val_;

    template <class... _Args>
    CANN_ASC_STL_API constexpr explicit __mb_holder(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __val_(::asc::std::forward<_Args>(__args)...)
    {}
};

template <class _Tp>
struct __mb_holder<_Tp, true> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS _Tp __val_;

    template <class... _Args>
    CANN_ASC_STL_API constexpr explicit __mb_holder(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __val_(::asc::std::forward<_Args>(__args)...)
    {}
};

template <class _Tp, bool = default_initializable<_Tp>>
struct __mb_holder_base {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __mb_holder<_Tp> __holder_;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_holder_base(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __holder_(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}
};

template <class _Tp>
struct __mb_holder_base<_Tp, true> {
    CANN_ASC_STL_NO_UNIQUE_ADDRESS __mb_holder<_Tp> __holder_;

    CANN_ASC_STL_API constexpr __mb_holder_base() noexcept(is_nothrow_default_constructible_v<_Tp>)
        : __holder_(in_place_t{})
    {}

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_holder_base(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __holder_(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}
};

template <class _Tp, bool = copyable<_Tp>>
struct __mb_copy_assign : __mb_holder_base<_Tp> {
    using __base = __mb_holder_base<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_copy_assign(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}
};

template <class _Tp>
struct __mb_copy_assign<_Tp, false> : __mb_holder_base<_Tp> {
    using __base = __mb_holder_base<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_copy_assign(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_API constexpr __mb_copy_assign(const __mb_copy_assign&) = default;
    CANN_ASC_STL_API constexpr __mb_copy_assign(__mb_copy_assign&&) = default;

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __mb_copy_assign& operator=(
        const __mb_copy_assign& __other) noexcept
    {
        static_assert(is_nothrow_copy_constructible_v<_Tp>);
        static_assert(!__can_use_no_unique_address<_Tp>());
        if (this != ::asc::std::addressof(__other)) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__holder_.__val_));
            ::asc::std::__construct_at(::asc::std::addressof(this->__holder_.__val_), __other.__holder_.__val_);
        }
        return *this;
    };
    CANN_ASC_STL_API constexpr __mb_copy_assign& operator=(__mb_copy_assign&&) = default;
};

template <class _Tp, bool = movable<_Tp>>
struct __mb_move_assign : __mb_copy_assign<_Tp> {
    using __base = __mb_copy_assign<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_move_assign(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}
};

template <class _Tp>
struct __mb_move_assign<_Tp, false> : __mb_copy_assign<_Tp> {
    using __base = __mb_copy_assign<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_move_assign(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    CANN_ASC_STL_API constexpr __mb_move_assign(const __mb_move_assign&) = default;
    CANN_ASC_STL_API constexpr __mb_move_assign(__mb_move_assign&&) = default;
    CANN_ASC_STL_API constexpr __mb_move_assign& operator=(const __mb_move_assign&) = default;

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 __mb_move_assign& operator=(
        __mb_move_assign&& __other) noexcept(is_nothrow_move_constructible_v<_Tp>)
    {
        static_assert(is_nothrow_move_constructible_v<_Tp>);
        static_assert(!__can_use_no_unique_address<_Tp>());
        if (this != ::asc::std::addressof(__other)) {
            ::asc::std::__destroy_at(::asc::std::addressof(this->__holder_.__val_));
            ::asc::std::__construct_at(
                ::asc::std::addressof(this->__holder_.__val_), ::asc::std::move(__other.__holder_.__val_));
        }
        return *this;
    }
};

template <class _Tp>
struct __mb_base : __mb_move_assign<_Tp> {
    using __base = __mb_move_assign<_Tp>;
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __mb_base(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)
    {}

    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp const& operator*() const noexcept
    {
        return this->__holder_.__val_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp& operator*() noexcept
    {
        return this->__holder_.__val_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr const _Tp* operator->() const noexcept
    {
        return ::asc::std::addressof(this->__holder_.__val_);
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr _Tp* operator->() noexcept
    {
        return ::asc::std::addressof(this->__holder_.__val_);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr bool __has_value() const noexcept
    {
        return true;
    }
};

//! @brief Selects the storage flavor: types that can always re-create
//! their value collapse into the holder (no empty state, empty types
//! collapse to zero size); everything else is boxed in an optional.
template <class _Tp>
using __movable_box_base = _If<__doesnt_need_empty_state<_Tp>(), __mb_base<_Tp>, __mb_optional_base<_Tp>>;

template <class _Tp, bool = __movable_box_object<_Tp>>
struct __movable_box;

template <class _Tp>
struct __movable_box<_Tp, true> : __movable_box_base<_Tp> {
    using __base = __movable_box_base<_Tp>;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class... _Args)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
    CANN_ASC_STL_API constexpr explicit __movable_box(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __base(in_place_t{}, ::asc::std::forward<_Args>(__args)...)  // NOLINT(build/include_what_you_use)
    {}

    CANN_ASC_STL_API constexpr __movable_box() noexcept(is_nothrow_default_constructible_v<_Tp>) = default;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_MOVABLE_BOX_H
