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

#ifndef CANN_ASC_STL_ASC_STD___OPTIONAL_OPTIONAL_BASE_H
#define CANN_ASC_STL_ASC_STD___OPTIONAL_OPTIONAL_BASE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__tuple/sfinae_helpers.h>
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
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>

// asc/__detail/visibility.h provides no such macro, so define it here,
// keeping only the inline semantics for hiding from the ABI.
#ifndef CANN_ASC_STL_DETAIL_HIDE_FROM_ABI
#define CANN_ASC_STL_DETAIL_HIDE_FROM_ABI inline
#endif

// asc/__config provides no standard-version level macro, so key this on its
// feature detection helper instead.
#ifndef CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 constexpr
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20
#endif
#endif  // CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20

CANN_ASC_STL_BEGIN_NAMESPACE

struct __optional_construct_from_invoke_tag {};

template <class T, bool = is_trivially_destructible_v<T>>
struct __optional_destruct_base;

template <class T>
struct __optional_destruct_base<T, false> {
    using value_type = T;
    using __stored_type = remove_cv_t<value_type>;
    static_assert(is_object_v<value_type>, "instantiation of optional with a non-object type is undefined behavior");
    union __storage {
        unsigned char empty_;
        __stored_type value_;

        CANN_ASC_STL_API constexpr __storage() noexcept : empty_()
        {}
        template <class... Args>
        CANN_ASC_STL_API constexpr __storage(in_place_t, Args&&... args) noexcept(
            is_nothrow_constructible_v<value_type, Args...>)
            : value_(::asc::std::forward<Args>(args)...)
        {}
        template <class Fun, class... Args>
        CANN_ASC_STL_API constexpr __storage(__optional_construct_from_invoke_tag, Fun&& fun, Args&&... args)
            : value_(::asc::std::invoke(::asc::std::forward<Fun>(fun), ::asc::std::forward<Args>(args)...))
        {}
        CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__storage() noexcept
        {}
    };
    __storage storage_;
    bool engaged_;

    CANN_ASC_STL_API constexpr __optional_destruct_base() noexcept : storage_(), engaged_(false)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __optional_destruct_base(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<value_type, Args...>)
        : storage_(in_place_t{}, ::asc::std::forward<Args>(args)...), engaged_(true)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __optional_destruct_base(__optional_construct_from_invoke_tag, Fun&& fun, Args&&... args)
        : storage_(__optional_construct_from_invoke_tag{}, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...),
          engaged_(true)
    {}
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__optional_destruct_base()
    {
        if (engaged_) {
            storage_.value_.~__stored_type();
        }
    }

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void reset() noexcept
    {
        if (engaged_) {
            storage_.value_.~__stored_type();
            engaged_ = false;
        }
    }
};

template <class T>
struct __optional_destruct_base<T, true> {
    using value_type = T;
    using __stored_type = remove_cv_t<value_type>;
    static_assert(is_object_v<value_type>, "instantiation of optional with a non-object type is undefined behavior");
    union __storage {
        unsigned char empty_;
        __stored_type value_;

        CANN_ASC_STL_API constexpr __storage() noexcept : empty_()
        {}
        template <class... Args>
        CANN_ASC_STL_API constexpr __storage(in_place_t, Args&&... args) noexcept(
            is_nothrow_constructible_v<value_type, Args...>)
            : value_(::asc::std::forward<Args>(args)...)
        {}
        template <class Fun, class... Args>
        CANN_ASC_STL_API constexpr __storage(__optional_construct_from_invoke_tag, Fun&& fun, Args&&... args)
            : value_(::asc::std::invoke(::asc::std::forward<Fun>(fun), ::asc::std::forward<Args>(args)...))
        {}
    };
    __storage storage_;
    bool engaged_;

    CANN_ASC_STL_API constexpr __optional_destruct_base() noexcept : storage_(), engaged_(false)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr explicit __optional_destruct_base(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<value_type, Args...>)
        : storage_(in_place_t{}, ::asc::std::forward<Args>(args)...), engaged_(true)
    {}

    template <class Fun, class... Args>
    CANN_ASC_STL_API constexpr __optional_destruct_base(__optional_construct_from_invoke_tag, Fun&& fun, Args&&... args)
        : storage_(__optional_construct_from_invoke_tag{}, ::asc::std::forward<Fun>(fun),
              ::asc::std::forward<Args>(args)...),
          engaged_(true)
    {}

    CANN_ASC_STL_API constexpr void reset() noexcept
    {
        if (engaged_) {
            engaged_ = false;
        }
    }
};

template <class T>
struct __optional_storage_base : __optional_destruct_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_storage_base, __optional_destruct_base, T);

    using value_type = T;

    CANN_ASC_STL_API constexpr bool has_value() const noexcept
    {
        return this->engaged_;
    }

    CANN_ASC_STL_API constexpr value_type& __get() & noexcept
    {
        return this->storage_.value_;
    }
    CANN_ASC_STL_API constexpr const value_type& __get() const& noexcept
    {
        return this->storage_.value_;
    }
    CANN_ASC_STL_API constexpr value_type&& __get() && noexcept
    {
        return ::asc::std::move(this->storage_.value_);
    }
    CANN_ASC_STL_API constexpr const value_type&& __get() const&& noexcept
    {
        return ::asc::std::move(this->storage_.value_);
    }

    CANN_ASC_STL_API constexpr void __set_engaged(bool engaged) noexcept
    {
        this->engaged_ = engaged;
    }
    template <class... Args>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __construct(Args&&... args)
    {
        ::asc::std::__construct_at(::asc::std::addressof(this->storage_.value_), ::asc::std::forward<Args>(args)...);
        this->engaged_ = true;
    }

    template <class That>
    CANN_ASC_STL_API constexpr void __construct_from(That&& opt)
    {
        if (opt.has_value()) {
            __construct(::asc::std::forward<That>(opt).__get());
        }
    }
    template <class That>
    CANN_ASC_STL_API constexpr void __assign_from(That&& opt)
    {
        if (this->engaged_ == opt.has_value()) {
            if (this->engaged_) {
                this->storage_.value_ = ::asc::std::forward<That>(opt).__get();
            }
        } else {
            if (this->engaged_) {
                this->reset();
            } else {
                __construct(::asc::std::forward<That>(opt).__get());
            }
        }
    }
};

template <class T>
inline constexpr __smf_availability __optional_can_copy_construct =
    is_trivially_copy_constructible_v<T> ? __smf_availability::__trivial :
    is_copy_constructible_v<T>           ? __smf_availability::__available :
                                           __smf_availability::__deleted;

template <class T, __smf_availability = __optional_can_copy_construct<T>>
struct __optional_copy_base : __optional_storage_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_copy_base, __optional_storage_base, T);
};

template <class T>
struct __optional_copy_base<T, __smf_availability::__available> : __optional_storage_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_copy_base, __optional_storage_base, T);

    // This ctor shouldn't need to initialize the base explicitly, but g++ 9 considers it to be uninitialized
    // during constexpr evaluation if it isn't initialized explicitly. This can be replaced with the pattern
    // below, in __optional_move_base, once g++ 9 falls off our support matrix.
    CANN_ASC_STL_API constexpr __optional_copy_base(const __optional_copy_base& opt) noexcept(
        is_nothrow_copy_constructible_v<T>)
        : __base()
    {
        this->__construct_from(opt);
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base(__optional_copy_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base& operator=(const __optional_copy_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base& operator=(__optional_copy_base&&) = default;
};

template <class T>
struct __optional_copy_base<T, __smf_availability::__deleted> : __optional_storage_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_copy_base, __optional_storage_base, T);
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base(const __optional_copy_base&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base(__optional_copy_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base& operator=(const __optional_copy_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_base& operator=(__optional_copy_base&&) = default;
};

template <class T>
inline constexpr __smf_availability __optional_can_move_construct =
    is_trivially_move_constructible_v<T> ? __smf_availability::__trivial :
    is_move_constructible_v<T>           ? __smf_availability::__available :
                                           __smf_availability::__deleted;

template <class T, __smf_availability = __optional_can_move_construct<T>>
struct __optional_move_base : __optional_copy_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_move_base, __optional_copy_base, T);
};

template <class T>
struct __optional_move_base<T, __smf_availability::__available> : __optional_copy_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_move_base, __optional_copy_base, T);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base(const __optional_move_base&) = default;

    CANN_ASC_STL_API constexpr __optional_move_base(__optional_move_base&& opt) noexcept(
        is_nothrow_move_constructible_v<T>)
    {
        this->__construct_from(::asc::std::move(opt));
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base& operator=(const __optional_move_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base& operator=(__optional_move_base&&) = default;
};

template <class T>
struct __optional_move_base<T, __smf_availability::__deleted> : __optional_copy_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_move_base, __optional_copy_base, T);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base(const __optional_move_base&) = default;
    __optional_move_base(__optional_move_base&&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base& operator=(const __optional_move_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_base& operator=(__optional_move_base&&) = default;
};

template <class T>
inline constexpr __smf_availability __optional_can_copy_assign =
    is_trivially_destructible_v<T> && is_trivially_copy_constructible_v<T> && is_trivially_copy_assignable_v<T> ?
    __smf_availability::__trivial :
    is_destructible_v<T> && is_copy_constructible_v<T> && is_copy_assignable_v<T> ? __smf_availability::__available :
                                                                                    __smf_availability::__deleted;

template <class T, __smf_availability = __optional_can_copy_assign<T>>
struct __optional_copy_assign_base : __optional_move_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_copy_assign_base, __optional_move_base, T);
};

template <class T>
struct __optional_copy_assign_base<T, __smf_availability::__available> : __optional_move_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_copy_assign_base, __optional_move_base, T);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base(const __optional_copy_assign_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base(__optional_copy_assign_base&&) = default;

    CANN_ASC_STL_API constexpr __optional_copy_assign_base& operator=(const __optional_copy_assign_base& opt)
    {
        this->__assign_from(opt);
        return *this;
    }

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base& operator=(__optional_copy_assign_base&&) = default;
};

template <class T>
struct __optional_copy_assign_base<T, __smf_availability::__deleted> : __optional_move_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_copy_assign_base, __optional_move_base, T);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base(const __optional_copy_assign_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base(__optional_copy_assign_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base& operator=(
        const __optional_copy_assign_base&) = delete;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_copy_assign_base& operator=(__optional_copy_assign_base&&) = default;
};

template <class T>
inline constexpr __smf_availability __optional_can_move_assign =
    is_trivially_destructible_v<T> && is_trivially_move_constructible_v<T> && is_trivially_move_assignable_v<T> ?
    __smf_availability::__trivial :
    is_destructible_v<T> && is_move_constructible_v<T> && is_move_assignable_v<T> ? __smf_availability::__available :
                                                                                    __smf_availability::__deleted;

template <class T, __smf_availability = __optional_can_move_assign<T>>
struct __optional_move_assign_base : __optional_copy_assign_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_move_assign_base, __optional_copy_assign_base, T);
};

template <class T>
struct __optional_move_assign_base<T, __smf_availability::__available> : __optional_copy_assign_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_move_assign_base, __optional_copy_assign_base, T);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base(const __optional_move_assign_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base(__optional_move_assign_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base& operator=(
        const __optional_move_assign_base&) = default;

    CANN_ASC_STL_API constexpr __optional_move_assign_base& operator=(__optional_move_assign_base&& opt) noexcept(
        is_nothrow_move_assignable_v<T> && is_nothrow_move_constructible_v<T>)
    {
        this->__assign_from(::asc::std::move(opt));  // NOLINT(build/include_what_you_use)
        return *this;
    }
};

template <class T>
struct __optional_move_assign_base<T, __smf_availability::__deleted> : __optional_copy_assign_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_move_assign_base, __optional_copy_assign_base, T);

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base(const __optional_move_assign_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base(__optional_move_assign_base&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base& operator=(
        const __optional_move_assign_base&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __optional_move_assign_base& operator=(__optional_move_assign_base&&) = delete;
};

// Storage layer that keeps the historical member names (storage_ / engaged_ /
// construct / reset) consumed by optional<T> and its cross-type access paths.
template <class T>
struct __optional_base : __optional_move_assign_base<T> {
    CANN_ASC_STL_DETAIL_DELEGATE_CONSTRUCTORS(__optional_base, __optional_move_assign_base, T);

    template <class... Args>
    CANN_ASC_STL_API constexpr T& construct(Args&&... args)
    {
        ::asc::std::__construct_at(  // NOLINT(build/include_what_you_use)
            &this->storage_.value_,
            ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
        this->engaged_ = true;
        return this->storage_.value_;
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___OPTIONAL_OPTIONAL_BASE_H
