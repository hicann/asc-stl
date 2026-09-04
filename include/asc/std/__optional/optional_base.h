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

#ifndef CANN_ASC_STL_STD_DETAIL_OPTIONAL_OPTIONAL_BASE_H
#define CANN_ASC_STL_STD_DETAIL_OPTIONAL_OPTIONAL_BASE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__tuple_dir/sfinae_helpers.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_destructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_copy_assignable.h>
#include <asc/std/__type_traits/is_nothrow_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#define CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__class, __baseclass, ...) \
    using __base = __baseclass<__VA_ARGS__>;                                          \
    using __base::__base;                                                             \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr __class() noexcept(                   \
        ::asc::std::is_nothrow_default_constructible_v<__base>) = default;

struct __optional_construct_from_invoke_tag {};

template <class _Tp, bool = is_trivially_destructible_v<_Tp>>
struct __optional_destruct_base;

template <class _Tp>
struct __optional_destruct_base<_Tp, false> {
    using value_type = _Tp;
    static_assert(is_object_v<value_type>, "instantiation of optional with a non-object type is undefined behavior");
    union __storage {
        char __null_state_;
        remove_cv_t<value_type> __val_;

        CANN_ASC_STL_API constexpr __storage() noexcept : __null_state_()
        {}
        template <class... _Args>
        CANN_ASC_STL_API constexpr __storage(in_place_t, _Args&&... __args) noexcept(
            is_nothrow_constructible_v<value_type, _Args...>)
            : __val_(::asc::std::forward<_Args>(__args)...)
        {}
        template <class _Fp, class... _Args>
        CANN_ASC_STL_API constexpr __storage(__optional_construct_from_invoke_tag, _Fp&& __f, _Args&&... __args)
            : __val_(::asc::std::invoke(::asc::std::forward<_Fp>(__f), ::asc::std::forward<_Args>(__args)...))
        {}
        CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__storage() noexcept
        {}
    };
    __storage __storage_;
    bool __engaged_;
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__optional_destruct_base()
    {
        if (__engaged_) {
            __storage_.__val_.~value_type();
        }
    }

    CANN_ASC_STL_API constexpr __optional_destruct_base() noexcept : __storage_(), __engaged_(false)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr explicit __optional_destruct_base(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<value_type, _Args...>)
        : __storage_(in_place_t{}, ::asc::std::forward<_Args>(__args)...), __engaged_(true)
    {}

    template <class _Fp, class... _Args>
    CANN_ASC_STL_API constexpr __optional_destruct_base(
        __optional_construct_from_invoke_tag, _Fp&& __f, _Args&&... __args)
        : __storage_(__optional_construct_from_invoke_tag{}, ::asc::std::forward<_Fp>(__f),
              ::asc::std::forward<_Args>(__args)...),
          __engaged_(true)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void reset() noexcept
    {
        if (__engaged_) {
            __storage_.__val_.~value_type();
            __engaged_ = false;
        }
    }
};

template <class _Tp>
struct __optional_destruct_base<_Tp, true> {
    using value_type = _Tp;
    static_assert(is_object_v<value_type>, "instantiation of optional with a non-object type is undefined behavior");
    union __storage {
        char __null_state_;
        remove_cv_t<value_type> __val_;

        CANN_ASC_STL_API constexpr __storage() noexcept : __null_state_()
        {}
        template <class... _Args>
        CANN_ASC_STL_API constexpr __storage(in_place_t, _Args&&... __args) noexcept(
            is_nothrow_constructible_v<value_type, _Args...>)
            : __val_(::asc::std::forward<_Args>(__args)...)
        {}
        template <class _Fp, class... _Args>
        CANN_ASC_STL_API constexpr __storage(__optional_construct_from_invoke_tag, _Fp&& __f, _Args&&... __args)
            : __val_(::asc::std::invoke(::asc::std::forward<_Fp>(__f), ::asc::std::forward<_Args>(__args)...))
        {}
    };
    __storage __storage_;
    bool __engaged_;

    CANN_ASC_STL_API constexpr __optional_destruct_base() noexcept : __storage_(), __engaged_(false)
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr explicit __optional_destruct_base(in_place_t, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<value_type, _Args...>)
        : __storage_(in_place_t{}, ::asc::std::forward<_Args>(__args)...), __engaged_(true)
    {}

    template <class _Fp, class... _Args>
    CANN_ASC_STL_API constexpr __optional_destruct_base(
        __optional_construct_from_invoke_tag, _Fp&& __f, _Args&&... __args)
        : __storage_(__optional_construct_from_invoke_tag{}, ::asc::std::forward<_Fp>(__f),
              ::asc::std::forward<_Args>(__args)...),
          __engaged_(true)
    {}

    CANN_ASC_STL_API constexpr void reset() noexcept
    {
        if (__engaged_) {
            __engaged_ = false;
        }
    }
};

template <class _Tp>
struct __optional_storage_base : __optional_destruct_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_storage_base, __optional_destruct_base, _Tp);

    using value_type = _Tp;

    [[nodiscard]] CANN_ASC_STL_API constexpr bool has_value() const noexcept
    {
        return this->__engaged_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr value_type& __get() & noexcept
    {
        return this->__storage_.__val_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const value_type& __get() const& noexcept
    {
        return this->__storage_.__val_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr value_type&& __get() && noexcept
    {
        return ::asc::std::move(this->__storage_.__val_);
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr const value_type&& __get() const&& noexcept
    {
        return ::asc::std::move(this->__storage_.__val_);
    }

    CANN_ASC_STL_API constexpr void __set_engaged(bool __engaged) noexcept
    {
        this->__engaged_ = __engaged;
    }
    template <class... _Args>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __construct(_Args&&... __args)
    {
        CANN_ASC_STL_DETAIL_ASSERT(!has_value(), "__construct called for engaged __optional_storage");
        ::asc::std::__construct_at(
            ::asc::std::addressof(this->__storage_.__val_), ::asc::std::forward<_Args>(__args)...);
        this->__engaged_ = true;
    }

    template <class _That>
    CANN_ASC_STL_API constexpr void __construct_from(_That&& __opt)
    {
        if (__opt.has_value()) {
            __construct(::asc::std::forward<_That>(__opt).__get());
        }
    }
    template <class _That>
    CANN_ASC_STL_API constexpr void __assign_from(_That&& __opt)
    {
        if (this->__engaged_ == __opt.has_value()) {
            if (this->__engaged_) {
                this->__storage_.__val_ = ::asc::std::forward<_That>(__opt).__get();
            }
        } else {
            if (this->__engaged_) {
                this->reset();
            } else {
                __construct(::asc::std::forward<_That>(__opt).__get());
            }
        }
    }
};

template <class _Tp>
inline constexpr __smf_availability __optional_can_copy_construct =
    is_trivially_copy_constructible_v<_Tp> ? __smf_availability::__trivial :
    is_copy_constructible_v<_Tp>           ? __smf_availability::__available :
                                             __smf_availability::__deleted;

template <class _Tp, __smf_availability = __optional_can_copy_construct<_Tp>>
struct __optional_copy_base : __optional_storage_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_copy_base, __optional_storage_base, _Tp);
};

template <class _Tp>
struct __optional_copy_base<_Tp, __smf_availability::__available> : __optional_storage_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_copy_base, __optional_storage_base, _Tp);

    // This ctor shouldn't need to initialize the base explicitly, but g++ 9 considers it to be uninitialized
    // during constexpr evaluation if it isn't initialized explicitly. This can be replaced with the pattern
    // below, in __optional_move_base, once g++ 9 falls off our support matrix.
    CANN_ASC_STL_API constexpr __optional_copy_base(const __optional_copy_base& __opt) noexcept(
        is_nothrow_copy_constructible_v<_Tp>)
        : __base()
    {
        this->__construct_from(__opt);
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base(__optional_copy_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base& operator=(const __optional_copy_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base& operator=(__optional_copy_base&&) = default;
};

template <class _Tp>
struct __optional_copy_base<_Tp, __smf_availability::__deleted> : __optional_storage_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_copy_base, __optional_storage_base, _Tp);
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base(const __optional_copy_base&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base(__optional_copy_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base& operator=(const __optional_copy_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base& operator=(__optional_copy_base&&) = default;
};

template <class _Tp>
inline constexpr __smf_availability __optional_can_move_construct =
    is_trivially_move_constructible_v<_Tp> ? __smf_availability::__trivial :
    is_move_constructible_v<_Tp>           ? __smf_availability::__available :
                                             __smf_availability::__deleted;

template <class _Tp, __smf_availability = __optional_can_move_construct<_Tp>>
struct __optional_move_base : __optional_copy_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_move_base, __optional_copy_base, _Tp);
};

template <class _Tp>
struct __optional_move_base<_Tp, __smf_availability::__available> : __optional_copy_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_move_base, __optional_copy_base, _Tp);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base(const __optional_move_base&) = default;

    CANN_ASC_STL_API constexpr __optional_move_base(__optional_move_base&& __opt) noexcept(
        is_nothrow_move_constructible_v<_Tp>)
    {
        this->__construct_from(::asc::std::move(__opt));
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base& operator=(const __optional_move_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base& operator=(__optional_move_base&&) = default;
};

template <class _Tp>
struct __optional_move_base<_Tp, __smf_availability::__deleted> : __optional_copy_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_move_base, __optional_copy_base, _Tp);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base(const __optional_move_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base(__optional_move_base&&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base& operator=(const __optional_move_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base& operator=(__optional_move_base&&) = default;
};

template <class _Tp>
inline constexpr __smf_availability __optional_can_copy_assign =
    is_trivially_destructible_v<_Tp> && is_trivially_copy_constructible_v<_Tp> && is_trivially_copy_assignable_v<_Tp> ?
    __smf_availability::__trivial :
    is_destructible_v<_Tp> && is_copy_constructible_v<_Tp> && is_copy_assignable_v<_Tp> ?
    __smf_availability::__available :
    __smf_availability::__deleted;

template <class _Tp, __smf_availability = __optional_can_copy_assign<_Tp>>
struct __optional_copy_assign_base : __optional_move_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_copy_assign_base, __optional_move_base, _Tp);
};

template <class _Tp>
struct __optional_copy_assign_base<_Tp, __smf_availability::__available> : __optional_move_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_copy_assign_base, __optional_move_base, _Tp);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base(const __optional_copy_assign_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base(__optional_copy_assign_base&&) = default;

    CANN_ASC_STL_API constexpr __optional_copy_assign_base& operator=(const __optional_copy_assign_base& __opt)
    {
        this->__assign_from(__opt);
        return *this;
    }

    __optional_copy_assign_base& operator=(__optional_copy_assign_base&&) = default;
};

template <class _Tp>
struct __optional_copy_assign_base<_Tp, __smf_availability::__deleted> : __optional_move_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_copy_assign_base, __optional_move_base, _Tp);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base(const __optional_copy_assign_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base(__optional_copy_assign_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base& operator=(
        const __optional_copy_assign_base&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base& operator=(__optional_copy_assign_base&&) = default;
};

template <class _Tp>
inline constexpr __smf_availability __optional_can_move_assign =
    is_trivially_destructible_v<_Tp> && is_trivially_move_constructible_v<_Tp> && is_trivially_move_assignable_v<_Tp> ?
    __smf_availability::__trivial :
    is_destructible_v<_Tp> && is_move_constructible_v<_Tp> && is_move_assignable_v<_Tp> ?
    __smf_availability::__available :
    __smf_availability::__deleted;

template <class _Tp, __smf_availability = __optional_can_move_assign<_Tp>>
struct __optional_move_assign_base : __optional_copy_assign_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_move_assign_base, __optional_copy_assign_base, _Tp);
};

template <class _Tp>
struct __optional_move_assign_base<_Tp, __smf_availability::__available> : __optional_copy_assign_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_move_assign_base, __optional_copy_assign_base, _Tp);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base(const __optional_move_assign_base& __opt) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base(__optional_move_assign_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base& operator=(
        const __optional_move_assign_base&) = default;

    CANN_ASC_STL_API constexpr __optional_move_assign_base& operator=(__optional_move_assign_base&& __opt) noexcept(
        is_nothrow_move_assignable_v<_Tp> && is_nothrow_move_constructible_v<_Tp>)
    {
        this->__assign_from(::asc::std::move(__opt));  // NOLINT(build/include_what_you_use)
        return *this;
    }
};

template <class _Tp>
struct __optional_move_assign_base<_Tp, __smf_availability::__deleted> : __optional_copy_assign_base<_Tp> {
    CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS(__optional_move_assign_base, __optional_copy_assign_base, _Tp);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base(const __optional_move_assign_base& __opt) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base(__optional_move_assign_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base& operator=(
        const __optional_move_assign_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base& operator=(__optional_move_assign_base&&) = delete;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#undef CANN_ASC_STL_DETAIL_OPTIONAL_DELEGATE_CONSTRUCTORS

#endif  // CANN_ASC_STL_STD_DETAIL_OPTIONAL_OPTIONAL_BASE_H
