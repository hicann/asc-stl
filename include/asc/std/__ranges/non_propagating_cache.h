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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_NON_PROPAGATING_CACHE_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_NON_PROPAGATING_CACHE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/concepts.h>         // indirectly_readable
#include <asc/std/__iterator/iterator_traits.h>  // iter_reference_t
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/delegate_constructors.h>
#include <asc/std/__utility/forward.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

struct __forward_tag {};
struct __from_tag {};
// This helper class is needed to perform copy and move elision when constructing the contained type from an iterator.
template <class _Tp>
struct __npc_wrapper {
    template <class... _Args>
    CANN_ASC_STL_API constexpr explicit __npc_wrapper(__forward_tag, _Args&&... __args)
        : __t_(::asc::std::forward<_Args>(__args)...)
    {}

    template <class _Fn>
    CANN_ASC_STL_API constexpr explicit __npc_wrapper(__from_tag, const _Fn& __fun) : __t_(__fun())
    {}

    _Tp __t_;
};

template <class _Tp, class = void>
struct __npc_destruct_base {
    union {
        CANN_ASC_STL_NO_UNIQUE_ADDRESS __npc_wrapper<_Tp> __val_;
    };
    bool __engaged_ = false;

    CANN_ASC_STL_API constexpr __npc_destruct_base() noexcept
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __npc_destruct_base(__forward_tag, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __val_(__forward_tag{}, ::asc::std::forward<_Args>(__args)...), __engaged_(true)
    {}

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 ~__npc_destruct_base() noexcept
    {
        if (__engaged_) {
            __val_.~_Tp();
        }
    }

    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void __reset() noexcept
    {
        if (__engaged_) {
            __val_.~_Tp();
            __engaged_ = false;
        }
    }
};

template <class _Tp>
struct __npc_destruct_base<_Tp, enable_if_t<is_trivially_destructible_v<_Tp>>> {
    union {
        CANN_ASC_STL_NO_UNIQUE_ADDRESS __npc_wrapper<_Tp> __val_;
    };
    bool __engaged_ = false;

    CANN_ASC_STL_API constexpr __npc_destruct_base() noexcept
    {}

    template <class... _Args>
    CANN_ASC_STL_API constexpr __npc_destruct_base(__forward_tag, _Args&&... __args) noexcept(
        is_nothrow_constructible_v<_Tp, _Args...>)
        : __val_(__forward_tag{}, ::asc::std::forward<_Args>(__args)...), __engaged_(true)
    {}

    CANN_ASC_STL_API constexpr void __reset() noexcept
    {
        if (__engaged_) {
            __engaged_ = false;
        }
    }
};

// __non_propagating_cache is a helper type that allows storing an optional value in it,
// but which does not copy the source's value when it is copy constructed/assigned to,
// and which resets the source's value when it is moved-from.
//
// This type is used as an implementation detail of some views that need to cache the
// result of `begin()` in order to provide an amortized O(1) begin() method. Typically,
// we don't want to propagate the value of the cache upon copy because the cached iterator
// may refer to internal details of the source view.
template <class _Tp, enable_if_t<is_object_v<_Tp>, int> = 0>
class __non_propagating_cache : public __npc_destruct_base<_Tp> {
public:
    using __base = __npc_destruct_base<_Tp>;
    using __base::__base;
    CANN_ASC_STL_API constexpr __non_propagating_cache() noexcept(is_nothrow_default_constructible_v<__base>) = default;

    CANN_ASC_STL_API constexpr __non_propagating_cache(const __non_propagating_cache&) noexcept : __base()
    {}

    CANN_ASC_STL_API constexpr __non_propagating_cache(__non_propagating_cache&& __other) noexcept : __base()
    {
        __other.__reset();
    }

    CANN_ASC_STL_API constexpr __non_propagating_cache& operator=(const __non_propagating_cache& __other) noexcept
    {
        if (this != ::asc::std::addressof(__other)) {
            this->__reset();
        }
        return *this;
    }

    CANN_ASC_STL_API constexpr __non_propagating_cache& operator=(__non_propagating_cache&& __other) noexcept
    {
        this->__reset();
        __other.__reset();
        return *this;
    }

    CANN_ASC_STL_API constexpr _Tp& operator*() noexcept
    {
        return this->__val_.__t_;
    }
    CANN_ASC_STL_API constexpr _Tp const& operator*() const noexcept
    {
        return this->__val_.__t_;
    }

    CANN_ASC_STL_API constexpr bool __has_value() const noexcept
    {
        return this->__engaged_;
    }

    template <class... _Args>
    CANN_ASC_STL_API constexpr _Tp& __emplace(_Args&&... __args) noexcept(is_nothrow_constructible_v<_Tp, _Args...>)
    {
        ::asc::std::__construct_at(::asc::std::addressof(this->__val_), __forward_tag{},
            ::asc::std::forward<_Args>(__args)...);  // NOLINT(build/include_what_you_use)
        this->__engaged_ = true;
        return this->__val_.__t_;
    }

    template <class _Fn>
    CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 _Tp& __emplace_from(const _Fn& __fun) noexcept(
        is_nothrow_constructible_v<_Tp, invoke_result_t<_Fn>>)
    {
        ::asc::std::__construct_at(::asc::std::addressof(this->__val_), __from_tag{}, __fun);
        this->__engaged_ = true;
        return this->__val_.__t_;
    }
};

struct __empty_cache {};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES
#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_NON_PROPAGATING_CACHE_H
