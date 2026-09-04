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

#ifndef CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_BASE_H
#define CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_BASE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/variant.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/__variant/variant_traits.h>
#include <asc/std/__utility/unreachable.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __variant_detail {
template <size_t _Index, class _Tp>
struct __alt {
    using __value_type = _Tp;
    template <class... _Args>
    CANN_ASC_STL_API explicit constexpr __alt(in_place_t, _Args&&... __args)
        : __value(::asc::std::forward<_Args>(__args)...)
    {}
    constexpr __alt(const __alt&) = default;
    constexpr __alt(__alt&&) = default;
    constexpr __alt& operator=(const __alt&) = default;
    constexpr __alt& operator=(__alt&&) = default;
    ~__alt() = default;

    __value_type __value;
};

template <_Trait _DestructibleTrait, size_t _Index, class... _Types>
union __union;

template <_Trait _DestructibleTrait, size_t _Index>
union __union<_DestructibleTrait, _Index> {};

#define CANN_ASC_STL_DETAIL_VARIANT_UNION_BODY(destructible_trait)                        \
                                                                                          \
private:                                                                                  \
    char __dummy;                                                                         \
    __alt<_Index, _Tp> __head_;                                                           \
    __union<destructible_trait, _Index + 1, _Types...> __tail_;                           \
                                                                                          \
    friend struct __access::__union;                                                      \
                                                                                          \
public:                                                                                   \
    CANN_ASC_STL_API explicit constexpr __union(__valueless_t) noexcept : __dummy{}       \
    {}                                                                                    \
                                                                                          \
    template <class... _Args>                                                             \
    CANN_ASC_STL_API explicit constexpr __union(in_place_index_t<0>, _Args&&... __args)   \
        : __head_(in_place_t{}, ::asc::std::forward<_Args>(__args)...)                    \
    {}                                                                                    \
                                                                                          \
    template <size_t _Ip, class... _Args>                                                 \
    CANN_ASC_STL_API explicit constexpr __union(in_place_index_t<_Ip>, _Args&&... __args) \
        : __tail_(in_place_index<_Ip - 1>, ::asc::std::forward<_Args>(__args)...)         \
    {}                                                                                    \
                                                                                          \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __union(const __union&) = default;                  \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __union(__union&&) = default;                       \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __union& operator=(const __union&) = default;       \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __union& operator=(__union&&) = default;

template <size_t _Index, class _Tp, class... _Types>
union __union<_Trait::_TriviallyAvailable, _Index, _Tp, _Types...> {
    CANN_ASC_STL_DETAIL_VARIANT_UNION_BODY(_Trait::_TriviallyAvailable)
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI ~__union() = default;
};

template <size_t _Index, class _Tp, class... _Types>
union __union<_Trait::_Available, _Index, _Tp, _Types...> {
    CANN_ASC_STL_DETAIL_VARIANT_UNION_BODY(_Trait::_Available)
    CANN_ASC_STL_API ~__union()
    {}
};

template <size_t _Index, class _Tp, class... _Types>
union __union<_Trait::_Unavailable, _Index, _Tp, _Types...> {
    CANN_ASC_STL_DETAIL_VARIANT_UNION_BODY(_Trait::_Unavailable)
    CANN_ASC_STL_API ~__union() = delete;
};

#undef CANN_ASC_STL_DETAIL_VARIANT_UNION_BODY

template <_Trait _DestructibleTrait, class... _Types>
class __base {
public:
    using __index_t = __variant_index_t<sizeof...(_Types)>;

    CANN_ASC_STL_API explicit constexpr __base(__valueless_t __tag) noexcept
        : __data_(__tag), __index_(__variant_npos<__index_t>)
    {}

    template <size_t _Ip, class... _Args>
    CANN_ASC_STL_API explicit constexpr __base(in_place_index_t<_Ip>, _Args&&... __args)
        : __data_(in_place_index<_Ip>, ::asc::std::forward<_Args>(__args)...), __index_(_Ip)
    {}

    [[nodiscard]] CANN_ASC_STL_API constexpr bool valueless_by_exception() const noexcept
    {
        return index() == variant_npos;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr size_t index() const noexcept
    {
        return __index_ == __variant_npos<__index_t> ? variant_npos : __index_;
    }

protected:
    [[nodiscard]] CANN_ASC_STL_API constexpr auto&& __as_base() &
    {
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr auto&& __as_base() &&
    {
        return ::asc::std::move(*this);
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr auto&& __as_base() const&
    {
        return *this;
    }

    CANN_ASC_STL_API constexpr auto&& __as_base() const&&
    {
        return ::asc::std::move(*this);
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr size_t __size() noexcept
    {
        return sizeof...(_Types);
    }

    __union<_DestructibleTrait, 0, _Types...> __data_;
    __index_t __index_;

    friend struct __access::__base;
};

template <class _Traits, _Trait = _Traits::__destructible_trait>
class __dtor;

#define CANN_ASC_STL_DETAIL_VARIANT_DESTRUCTOR_BODY(destructible_trait)           \
    using __base_type = __base<destructible_trait, _Types...>;                    \
    using __index_t = typename __base_type::__index_t;                            \
                                                                                  \
public:                                                                           \
    using __base_type::__base_type;                                               \
    using __base_type::operator=;                                                 \
                                                                                  \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __dtor(const __dtor&) = default;            \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __dtor(__dtor&&) = default;                 \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __dtor& operator=(const __dtor&) = default; \
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __dtor& operator=(__dtor&&) = default;

template <class... _Types>
class __dtor<__traits<_Types...>, _Trait::_TriviallyAvailable> : public __base<_Trait::_TriviallyAvailable, _Types...> {
    CANN_ASC_STL_DETAIL_VARIANT_DESTRUCTOR_BODY(_Trait::_TriviallyAvailable)
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI ~__dtor() = default;

protected:
    CANN_ASC_STL_API void __destroy() noexcept
    {
        this->__index_ = __variant_npos<__index_t>;
    }
};

template <class... _Types>
class __dtor<__traits<_Types...>, _Trait::_Available> : public __base<_Trait::_Available, _Types...> {
    struct __visitor {
        template <class _Alt>
        CANN_ASC_STL_API void operator()(_Alt& __alt) const noexcept
        {
            using __alt_type = remove_cvref_t<decltype(__alt)>;
            __alt.~__alt_type();
        }
    };

    CANN_ASC_STL_DETAIL_VARIANT_DESTRUCTOR_BODY(_Trait::_Available)

    CANN_ASC_STL_API ~__dtor() noexcept
    {
        __destroy();
    }

protected:
    CANN_ASC_STL_API void __destroy() noexcept
    {
        if (!this->valueless_by_exception()) {
            constexpr size_t __np = remove_cvref_t<__dtor>::__size();
            __destroy(integral_constant<size_t, __np - 1>{}, this->__index_);
        }
        this->__index_ = __variant_npos<__index_t>;
    }

private:
    template <size_t _CurrentIndex>
    CANN_ASC_STL_API void __destroy(integral_constant<size_t, _CurrentIndex>, const size_t __index_) noexcept
    {
        if (__index_ == _CurrentIndex) {
            using __alt_type = remove_cvref_t<decltype(__access::__base::__get_alt<_CurrentIndex>(this->__as_base()))>;
            __access::__base::__get_alt<_CurrentIndex>(this->__as_base()).~__alt_type();
            return;
        }
        __destroy(integral_constant<size_t, _CurrentIndex - 1>{}, __index_);
    }
    CANN_ASC_STL_API void __destroy(integral_constant<size_t, 0>, const size_t __index_) noexcept
    {
        if (__index_ == 0) {
            using __alt_type = remove_cvref_t<decltype(__access::__base::__get_alt<0>(this->__as_base()))>;
            __access::__base::__get_alt<0>(this->__as_base()).~__alt_type();
            return;
        }
        // We already checked that every variant has a value, so we should never reach this line
        ::asc::std::unreachable();
    }
};

template <class... _Types>
class __dtor<__traits<_Types...>, _Trait::_Unavailable> : public __base<_Trait::_Unavailable, _Types...> {
    CANN_ASC_STL_DETAIL_VARIANT_DESTRUCTOR_BODY(_Trait::_Unavailable)
    CANN_ASC_STL_API ~__dtor() = delete;

protected:
    CANN_ASC_STL_API void __destroy() noexcept = delete;
};

#undef CANN_ASC_STL_DETAIL_VARIANT_DESTRUCTOR_BODY

template <class _Traits>
class __ctor : public __dtor<_Traits> {
    using __base_type = __dtor<_Traits>;

    template <size_t _CurrentIndex, class _Rhs>
    CANN_ASC_STL_API static constexpr void __generic_construct_impl(
        integral_constant<size_t, _CurrentIndex>, const size_t __index_, __ctor& __lhs, _Rhs&& __rhs)
    {
        if (__index_ == _CurrentIndex) {
            ::asc::std::__construct_at(
                ::asc::std::addressof(__access::__base::__get_alt<_CurrentIndex>(__lhs.__as_base())), in_place_t{},
                __access::__base::__get_alt<_CurrentIndex>(::asc::std::forward<_Rhs>(__rhs).__as_base()).__value);
            return;
        }
        __generic_construct_impl(
            integral_constant<size_t, _CurrentIndex - 1>{}, __index_, __lhs, ::asc::std::forward<_Rhs>(__rhs));
    }

    template <class _Rhs>
    CANN_ASC_STL_API static constexpr void __generic_construct_impl(
        integral_constant<size_t, 0>, const size_t __index_, __ctor& __lhs, _Rhs&& __rhs)
    {
        if (__index_ == 0) {
            ::asc::std::__construct_at(::asc::std::addressof(__access::__base::__get_alt<0>(__lhs.__as_base())),
                in_place_t{}, __access::__base::__get_alt<0>(::asc::std::forward<_Rhs>(__rhs).__as_base()).__value);
            return;
        }
        // We already checked that every variant has a value, so we should never reach this line
        ::asc::std::unreachable();
    }

public:
    using __base_type::__base_type;
    using __base_type::operator=;

protected:
    template <size_t _Ip, class _Tp, class... _Args>
    CANN_ASC_STL_API static _Tp& __construct_alt(__alt<_Ip, _Tp>& __a, _Args&&... __args)
    {
        ::asc::std::__construct_at(::asc::std::addressof(__a), in_place_t{}, ::asc::std::forward<_Args>(__args)...);
        return __a.__value;
    }

    template <class _Rhs>
    CANN_ASC_STL_API static void __generic_construct(__ctor& __lhs, _Rhs&& __rhs)
    {
        __lhs.__destroy();
        if (!__rhs.valueless_by_exception()) {
            constexpr size_t __np = remove_cvref_t<__ctor>::__size();
            __generic_construct_impl(
                integral_constant<size_t, __np - 1>{}, __rhs.index(), __lhs, ::asc::std::forward<_Rhs>(__rhs));
            __lhs.__index_ = static_cast<decltype(__lhs.__index_)>(__rhs.index());
        }
    }
};

template <class _Traits, _Trait = _Traits::__move_constructible_trait>
class __move_constructor;

#define CANN_ASC_STL_DETAIL_VARIANT_MOVE_CONSTRUCTOR(move_constructible_trait, move_constructor)                   \
    template <class... _Types>                                                                                     \
    class __move_constructor<__traits<_Types...>, move_constructible_trait> : public __ctor<__traits<_Types...>> { \
        using __base_type = __ctor<__traits<_Types...>>;                                                           \
                                                                                                                   \
    public:                                                                                                        \
        using __base_type::__base_type;                                                                            \
        using __base_type::operator=;                                                                              \
                                                                                                                   \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __move_constructor(const __move_constructor&) = default;                 \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI ~__move_constructor() = default;                                         \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __move_constructor& operator=(const __move_constructor&) = default;      \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __move_constructor& operator=(__move_constructor&&) = default;           \
        move_constructor                                                                                           \
    }

CANN_ASC_STL_DETAIL_VARIANT_MOVE_CONSTRUCTOR(
    _Trait::_TriviallyAvailable,
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __move_constructor(__move_constructor&& __that) = default;);

CANN_ASC_STL_DETAIL_VARIANT_MOVE_CONSTRUCTOR(
    _Trait::_Available,
    CANN_ASC_STL_API __move_constructor(__move_constructor&& __that) noexcept(
        __fold_and_v<is_nothrow_move_constructible_v<_Types>...>)
    : __move_constructor(__valueless_t{}) { this->__generic_construct(*this, ::asc::std::move(__that)); });

CANN_ASC_STL_DETAIL_VARIANT_MOVE_CONSTRUCTOR(_Trait::_Unavailable, __move_constructor(__move_constructor&&) = delete;);

#undef CANN_ASC_STL_DETAIL_VARIANT_MOVE_CONSTRUCTOR

template <class _Traits, _Trait = _Traits::__copy_constructible_trait>
class __copy_constructor;

#define CANN_ASC_STL_DETAIL_VARIANT_COPY_CONSTRUCTOR(copy_constructible_trait, copy_constructor)              \
    template <class... _Types>                                                                                \
    class __copy_constructor<__traits<_Types...>, copy_constructible_trait>                                   \
        : public __move_constructor<__traits<_Types...>> {                                                    \
        using __base_type = __move_constructor<__traits<_Types...>>;                                          \
                                                                                                              \
    public:                                                                                                   \
        using __base_type::__base_type;                                                                       \
        using __base_type::operator=;                                                                         \
                                                                                                              \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __copy_constructor(__copy_constructor&&) = default;                 \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI ~__copy_constructor() = default;                                    \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __copy_constructor& operator=(const __copy_constructor&) = default; \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __copy_constructor& operator=(__copy_constructor&&) = default;      \
        copy_constructor                                                                                      \
    }

CANN_ASC_STL_DETAIL_VARIANT_COPY_CONSTRUCTOR(
    _Trait::_TriviallyAvailable,
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __copy_constructor(const __copy_constructor& __that) = default;);

CANN_ASC_STL_DETAIL_VARIANT_COPY_CONSTRUCTOR(
    _Trait::_Available, CANN_ASC_STL_API __copy_constructor(const __copy_constructor& __that)
    : __copy_constructor(__valueless_t{}) { this->__generic_construct(*this, __that); });

CANN_ASC_STL_DETAIL_VARIANT_COPY_CONSTRUCTOR(
    _Trait::_Unavailable, __copy_constructor(const __copy_constructor&) = delete;);

#undef CANN_ASC_STL_DETAIL_VARIANT_COPY_CONSTRUCTOR

template <class _Traits>
class __assignment : public __copy_constructor<_Traits> {
    using __base_type = __copy_constructor<_Traits>;

    template <size_t _CurrentIndex, class _Other>
    CANN_ASC_STL_API constexpr void __generic_assign(
        integral_constant<size_t, _CurrentIndex>, const size_t __index_, _Other&& __rhs)
    {
        if (__index_ == _CurrentIndex) {
            this->__assign_alt(__access::__base::__get_alt<_CurrentIndex>(this->__as_base()),
                __access::__base::__get_alt<_CurrentIndex>(::asc::std::forward<_Other>(__rhs).__as_base()).__value);
            return;
        }
        this->__generic_assign(
            integral_constant<size_t, _CurrentIndex - 1>{}, __index_, ::asc::std::forward<_Other>(__rhs));
    }

    template <class _Other>
    CANN_ASC_STL_API constexpr void __generic_assign(
        integral_constant<size_t, 0>, const size_t __index_, _Other&& __rhs)
    {
        if (__index_ == 0) {
            this->__assign_alt(__access::__base::__get_alt<0>(this->__as_base()),
                __access::__base::__get_alt<0>(::asc::std::forward<_Other>(__rhs).__as_base()).__value);
            return;
        }
        // We already checked that every variant has a value, so we should never reach this line
        ::asc::std::unreachable();
    }

public:
    using __base_type::__base_type;
    using __base_type::operator=;

    template <size_t _Ip, class... _Args>
    CANN_ASC_STL_API auto& __emplace(_Args&&... __args)
    {
        this->__destroy();
        auto& __res =
            this->__construct_alt(__access::__base::__get_alt<_Ip>(*this), ::asc::std::forward<_Args>(__args)...);
        this->__index_ = _Ip;
        return __res;
    }

protected:
    template <size_t _Ip, class _Tp, class _Arg,
        enable_if_t<is_nothrow_constructible_v<_Tp, _Arg> || !is_nothrow_move_constructible_v<_Tp>, int> = 0>
    CANN_ASC_STL_API void __assign_alt(__alt<_Ip, _Tp>& __a, _Arg&& __arg)
    {
        if (this->index() == _Ip) {
            __a.__value = ::asc::std::forward<_Arg>(__arg);
        } else {
            this->__emplace<_Ip>(::asc::std::forward<_Arg>(__arg));
        }
    }
    template <size_t _Ip, class _Tp, class _Arg,
        enable_if_t<!is_nothrow_constructible_v<_Tp, _Arg> && is_nothrow_move_constructible_v<_Tp>, int> = 0>
    CANN_ASC_STL_API void __assign_alt(__alt<_Ip, _Tp>& __a, _Arg&& __arg)
    {
        if (this->index() == _Ip) {
            __a.__value = ::asc::std::forward<_Arg>(__arg);
        } else {
            this->__emplace<_Ip>(_Tp(::asc::std::forward<_Arg>(__arg)));
        }
    }

    template <class _That>
    CANN_ASC_STL_API void __generic_assign(_That&& __that)
    {
        if (this->valueless_by_exception() && __that.valueless_by_exception()) {
            // do nothing.
        } else if (__that.valueless_by_exception()) {
            this->__destroy();
        } else {
            constexpr size_t __np = remove_cvref_t<__assignment>::__size();
            this->__generic_assign(
                integral_constant<size_t, __np - 1>{}, __that.index(), ::asc::std::forward<_That>(__that));
        }
    }
};

template <class _Traits, _Trait = _Traits::__move_assignable_trait>
class __move_assignment;

#define CANN_ASC_STL_DETAIL_VARIANT_MOVE_ASSIGNMENT(move_assignable_trait, move_assignment)                          \
    template <class... _Types>                                                                                       \
    class __move_assignment<__traits<_Types...>, move_assignable_trait> : public __assignment<__traits<_Types...>> { \
        using __base_type = __assignment<__traits<_Types...>>;                                                       \
                                                                                                                     \
    public:                                                                                                          \
        using __base_type::__base_type;                                                                              \
        using __base_type::operator=;                                                                                \
                                                                                                                     \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __move_assignment(const __move_assignment&) = default;                     \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __move_assignment(__move_assignment&&) = default;                          \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI ~__move_assignment() = default;                                            \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __move_assignment& operator=(const __move_assignment&) = default;          \
        move_assignment                                                                                              \
    }

CANN_ASC_STL_DETAIL_VARIANT_MOVE_ASSIGNMENT(
    _Trait::_TriviallyAvailable,
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __move_assignment& operator=(__move_assignment&& __that) = default;);

CANN_ASC_STL_DETAIL_VARIANT_MOVE_ASSIGNMENT(
    _Trait::_Available,
    CANN_ASC_STL_API __move_assignment& operator=(__move_assignment&& __that) noexcept(
        __fold_and_v<(is_nothrow_move_constructible_v<_Types> && is_nothrow_move_assignable_v<_Types>)...>) {
        this->__generic_assign(::asc::std::move(__that));
        return *this;
    });

CANN_ASC_STL_DETAIL_VARIANT_MOVE_ASSIGNMENT(
    _Trait::_Unavailable, __move_assignment& operator=(__move_assignment&&) = delete;);

#undef CANN_ASC_STL_DETAIL_VARIANT_MOVE_ASSIGNMENT

template <class _Traits, _Trait = _Traits::__copy_assignable_trait>
class __copy_assignment;

#define CANN_ASC_STL_DETAIL_VARIANT_COPY_ASSIGNMENT(copy_assignable_trait, copy_assignment)            \
    template <class... _Types>                                                                         \
    class __copy_assignment<__traits<_Types...>, copy_assignable_trait>                                \
        : public __move_assignment<__traits<_Types...>> {                                              \
        using __base_type = __move_assignment<__traits<_Types...>>;                                    \
                                                                                                       \
    public:                                                                                            \
        using __base_type::__base_type;                                                                \
        using __base_type::operator=;                                                                  \
                                                                                                       \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __copy_assignment(const __copy_assignment&) = default;       \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __copy_assignment(__copy_assignment&&) = default;            \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI ~__copy_assignment() = default;                              \
        CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __copy_assignment& operator=(__copy_assignment&&) = default; \
        copy_assignment                                                                                \
    }

CANN_ASC_STL_DETAIL_VARIANT_COPY_ASSIGNMENT(
    _Trait::_TriviallyAvailable,
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __copy_assignment& operator=(const __copy_assignment& __that) = default;);

CANN_ASC_STL_DETAIL_VARIANT_COPY_ASSIGNMENT(
    _Trait::_Available, CANN_ASC_STL_API __copy_assignment& operator=(const __copy_assignment& __that) {
        this->__generic_assign(__that);
        return *this;
    });

CANN_ASC_STL_DETAIL_VARIANT_COPY_ASSIGNMENT(
    _Trait::_Unavailable, __copy_assignment& operator=(const __copy_assignment&) = delete;);

#undef CANN_ASC_STL_DETAIL_VARIANT_COPY_ASSIGNMENT

template <class... _Types>
class __impl : public __copy_assignment<__traits<_Types...>> {
    using __base_type = __copy_assignment<__traits<_Types...>>;

    template <size_t _CurrentIndex>
    CANN_ASC_STL_API static constexpr void __swap_value(
        integral_constant<size_t, _CurrentIndex>, const size_t __index_, __impl& __lhs, __impl& __rhs)
    {
        if (__index_ == _CurrentIndex) {
            using ::asc::std::swap;
            swap(__access::__base::__get_alt<_CurrentIndex>(__lhs.__as_base()).__value,
                __access::__base::__get_alt<_CurrentIndex>(__rhs.__as_base()).__value);
            return;
        }
        __swap_value(integral_constant<size_t, _CurrentIndex - 1>{}, __index_, __lhs, __rhs);
    }

    CANN_ASC_STL_API static constexpr void __swap_value(
        integral_constant<size_t, 0>, const size_t __index_, __impl& __lhs, __impl& __rhs)
    {
        if (__index_ == 0) {
            using ::asc::std::swap;
            swap(__access::__base::__get_alt<0>(__lhs.__as_base()).__value,
                __access::__base::__get_alt<0>(__rhs.__as_base()).__value);
            return;
        }
        // We already checked that every variant has a value, so we should never reach this line
        ::asc::std::unreachable();
    }

public:
    using __base_type::__base_type;  // get in_place_index_t constructor & friends
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __impl(__impl const&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __impl(__impl&&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __impl& operator=(__impl const&) = default;
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI __impl& operator=(__impl&&) = default;

    template <size_t _Ip, class _Arg>
    CANN_ASC_STL_API void __assign(_Arg&& __arg)
    {
        this->__assign_alt(__access::__base::__get_alt<_Ip>(*this), ::asc::std::forward<_Arg>(__arg));
    }

    CANN_ASC_STL_API void __swap(__impl& __that)
    {
        if (this->valueless_by_exception() && __that.valueless_by_exception()) {
            // do nothing.
        } else if (this->index() == __that.index()) {
            constexpr size_t __np = remove_cvref_t<__impl>::__size();
            __swap_value(integral_constant<size_t, __np - 1>{}, this->index(), *this, __that);
        } else {
            __impl* __lhs = this;
            __impl* __rhs = ::asc::std::addressof(__that);
            if (__lhs->__move_nothrow() && !__rhs->__move_nothrow()) {
                ::asc::std::swap(__lhs, __rhs);
            } else {
                __impl __tmp(::asc::std::move(*__rhs));
                this->__generic_construct(*__rhs, ::asc::std::move(*__lhs));
                this->__generic_construct(*__lhs, ::asc::std::move(__tmp));  // NOLINT(build/include_what_you_use)
            }
        }
    }

private:
    [[nodiscard]] CANN_ASC_STL_API constexpr bool __move_nothrow() const
    {
        constexpr bool __results[] = {is_nothrow_move_constructible_v<_Types>...};
        return this->valueless_by_exception() || __results[this->index()];
    }
};
}  // namespace __variant_detail

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_VARIANT_VARIANT_BASE_H
