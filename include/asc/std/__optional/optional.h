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

#ifndef CANN_ASC_STL_ASC_STD___OPTIONAL_OPTIONAL_H
#define CANN_ASC_STL_ASC_STD___OPTIONAL_OPTIONAL_H

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
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__fwd/optional.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__optional/nullopt.h>
#include <asc/std/__optional/optional_base.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/in_place.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// 就地列表构造/emplace 重载经宿主 initializer_list 提供（设备侧不参与）。
#include <initializer_list>
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// 转换构造约束件：值形态与 optional<U> 形态各自的可构造/可隐转判别。
// optional<U> 四种值形态中任一路径能构造/转换出 T，即视为“T 与 optional 互转”，
// 此类组合从转换构造中排除，杜绝嵌套 optional 的意外包裹。
template <class T, class U>
struct __opt_check_constructible_from_opt
    : disjunction<is_constructible<T, optional<U>&>, is_constructible<T, const optional<U>&>,
          is_constructible<T, optional<U>&&>, is_constructible<T, const optional<U>&&>, is_convertible<optional<U>&, T>,
          is_convertible<const optional<U>&, T>, is_convertible<optional<U>&&, T>,
          is_convertible<const optional<U>&&, T>> {};

template <class T, class U>
inline constexpr bool __opt_is_implicitly_constructible = is_constructible_v<T, U> && is_convertible_v<U, T>;

template <class T, class U>
inline constexpr bool __opt_is_explicitly_constructible = is_constructible_v<T, U> && !is_convertible_v<U, T>;

template <class T, class U>
inline constexpr bool __opt_is_constructible_from_value =
    !is_same_v<remove_cvref_t<U>, in_place_t> && !is_same_v<remove_cvref_t<U>, optional<T>>;

template <class T, class U>
inline constexpr bool __opt_is_constructible_from_opt =
    !is_same_v<U, T> && !__opt_check_constructible_from_opt<T, U>::value;

template <class T>
class optional : private __optional_base<T> {
    static_assert(is_object_v<T>, "asc::std::optional requires a non-reference object type");
    static_assert(!is_reference_v<T>, "asc::std::optional<T&> is not in the frozen product boundary");
    using base = __optional_base<T>;

    template <class>
    friend class optional;

public:
    using value_type = T;
    CANN_ASC_STL_API constexpr optional() noexcept = default;
    CANN_ASC_STL_API constexpr optional(nullopt_t) noexcept
    {}

    CANN_ASC_STL_API constexpr optional(const optional& other)
    {
        if (other.engaged_) {
            this->construct(other.storage_.value_);
        }
    }
    CANN_ASC_STL_API constexpr optional(optional&& other) noexcept(is_nothrow_move_constructible_v<T>)
    {
        if (other.engaged_) {
            this->construct(::asc::std::move(other.storage_.value_));
        }
    }
    // 转换构造按可转换性分流：可隐转组合支持拷贝初始化，其余保持显式。
    template <class U,
        enable_if_t<__opt_is_constructible_from_opt<T, U> && __opt_is_implicitly_constructible<T, const U&>, int> = 0>
    CANN_ASC_STL_API constexpr optional(const optional<U>& other)
    {
        if (other.engaged_) {
            this->construct(other.storage_.value_);
        }
    }
    template <class U,
        enable_if_t<__opt_is_constructible_from_opt<T, U> && __opt_is_explicitly_constructible<T, const U&>, int> = 0>
    CANN_ASC_STL_API constexpr explicit optional(const optional<U>& other)
    {
        if (other.engaged_) {
            this->construct(other.storage_.value_);
        }
    }
    template <class U,
        enable_if_t<__opt_is_constructible_from_opt<T, U> && __opt_is_implicitly_constructible<T, U>, int> = 0>
    CANN_ASC_STL_API constexpr optional(optional<U>&& other)
    {
        if (other.engaged_) {
            this->construct(::asc::std::move(other.storage_.value_));
        }
    }
    template <class U,
        enable_if_t<__opt_is_constructible_from_opt<T, U> && __opt_is_explicitly_constructible<T, U>, int> = 0>
    CANN_ASC_STL_API constexpr explicit optional(optional<U>&& other)
    {
        if (other.engaged_) {
            this->construct(::asc::std::move(other.storage_.value_));
        }
    }
    template <class U = T,
        enable_if_t<__opt_is_constructible_from_value<T, U> && __opt_is_implicitly_constructible<T, U>, int> = 0>
    CANN_ASC_STL_API constexpr optional(U&& value) : base(in_place, ::asc::std::forward<U>(value))
    {}
    template <class U = T,
        enable_if_t<__opt_is_constructible_from_value<T, U> && __opt_is_explicitly_constructible<T, U>, int> = 0>
    CANN_ASC_STL_API constexpr explicit optional(U&& value) : base(in_place, ::asc::std::forward<U>(value))
    {}
    template <class... Args>
    CANN_ASC_STL_API constexpr explicit optional(in_place_t, Args&&... args)
        : base(in_place, ::asc::std::forward<Args>(args)...)
    {}
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class U, class... Args, enable_if_t<is_constructible_v<T, ::std::initializer_list<U>&, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr explicit optional(in_place_t, ::std::initializer_list<U> list, Args&&... args)
        : base(in_place, list, ::asc::std::forward<Args>(args)...)
    {}
#endif

    CANN_ASC_STL_API constexpr optional& operator=(nullopt_t) noexcept
    {
        reset();
        return *this;
    }
    CANN_ASC_STL_API constexpr optional& operator=(const optional& other)
    {
        assign(other);
        return *this;
    }
    CANN_ASC_STL_API constexpr optional& operator=(optional&& other) noexcept(
        is_nothrow_move_constructible_v<T> && is_nothrow_move_assignable_v<T>)
    {
        assign(::asc::std::move(other));
        return *this;
    }
    template <class U, enable_if_t<!__is_asc_std_optional_v<remove_cvref_t<U>>, int> = 0>
    CANN_ASC_STL_API constexpr optional& operator=(U&& value)
    {
        if (this->engaged_) {
            this->storage_.value_ = ::asc::std::forward<U>(value);
        } else {
            this->construct(::asc::std::forward<U>(value));
        }
        return *this;
    }
    template <class U>
    CANN_ASC_STL_API constexpr optional& operator=(const optional<U>& other)
    {
        assign(other);
        return *this;
    }
    template <class U>
    CANN_ASC_STL_API constexpr optional& operator=(optional<U>&& other)
    {
        assign(::asc::std::move(other));
        return *this;
    }

    template <class... Args>
    CANN_ASC_STL_API constexpr T& emplace(Args&&... args)
    {
        reset();
        return this->construct(::asc::std::forward<Args>(args)...);
    }
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class U, class... Args, enable_if_t<is_constructible_v<T, ::std::initializer_list<U>&, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr T& emplace(::std::initializer_list<U> list, Args&&... args)
    {
        reset();
        return this->construct(list, ::asc::std::forward<Args>(args)...);
    }
#endif
    CANN_ASC_STL_API constexpr void reset() noexcept
    {
        base::reset();
    }
    CANN_ASC_STL_API constexpr void swap(optional& other) noexcept(
        is_nothrow_move_constructible_v<T> && is_nothrow_swappable_v<T>)
    {
        if (this->engaged_ && other.engaged_) {
            ::asc::std::swap(this->storage_.value_, other.storage_.value_);
        } else if (this->engaged_) {
            other.construct(::asc::std::move(this->storage_.value_));
            reset();
        } else if (other.engaged_) {
            this->construct(::asc::std::move(other.storage_.value_));
            other.reset();
        }
    }

    CANN_ASC_STL_API constexpr T* operator->() noexcept
    {
        return ::asc::std::addressof(this->storage_.value_);
    }
    CANN_ASC_STL_API constexpr const T* operator->() const noexcept
    {
        return ::asc::std::addressof(this->storage_.value_);
    }
    CANN_ASC_STL_API constexpr T& operator*() & noexcept
    {
        return this->storage_.value_;
    }
    CANN_ASC_STL_API constexpr const T& operator*() const& noexcept
    {
        return this->storage_.value_;
    }
    CANN_ASC_STL_API constexpr T&& operator*() && noexcept
    {
        return ::asc::std::move(this->storage_.value_);
    }
    CANN_ASC_STL_API constexpr const T&& operator*() const&& noexcept
    {
        return ::asc::std::move(this->storage_.value_);
    }
    CANN_ASC_STL_API constexpr explicit operator bool() const noexcept
    {
        return this->engaged_;
    }
    CANN_ASC_STL_API constexpr bool has_value() const noexcept
    {
        return this->engaged_;
    }
    template <class U>
    CANN_ASC_STL_API constexpr T value_or(U&& default_value) const&
    {
        return this->engaged_ ? this->storage_.value_ : static_cast<T>(::asc::std::forward<U>(default_value));
    }
    template <class U>
    CANN_ASC_STL_API constexpr T value_or(U&& default_value) &&
    {
        return this->engaged_ ? ::asc::std::move(this->storage_.value_) :
                                static_cast<T>(::asc::std::forward<U>(default_value));
    }

private:
    template <class Other>
    CANN_ASC_STL_API constexpr void assign(Other&& other)
    {
        if (this->engaged_ && other.engaged_) {
            this->storage_.value_ =
                ::asc::std::forward<Other>(other).storage_.value_;  // NOLINT(build/include_what_you_use)
        } else if (other.engaged_) {
            this->construct(::asc::std::forward<Other>(other).storage_.value_);  // NOLINT(build/include_what_you_use)
        } else {
            reset();
        }
    }
};

// Restricted reference specialization: it borrows a
// same-type lvalue and never binds a temporary or a cross-type value, so no
// dangling path exists.  Rebinding assignment, monadic, value-result and
// interoperability surfaces stay outside the frozen boundary.
template <class T>
class optional<T&> {
public:
    using value_type = T;

    CANN_ASC_STL_API constexpr optional() noexcept = default;
    CANN_ASC_STL_API constexpr optional(nullopt_t) noexcept
    {}
    CANN_ASC_STL_API constexpr optional(const optional&) noexcept = default;
    CANN_ASC_STL_API constexpr optional(T& value) noexcept : pointer_(::asc::std::addressof(value))
    {}

    CANN_ASC_STL_API constexpr optional& operator=(nullopt_t) noexcept
    {
        pointer_ = nullptr;
        return *this;
    }
    CANN_ASC_STL_API constexpr optional& operator=(const optional&) noexcept = default;

    CANN_ASC_STL_API constexpr explicit operator bool() const noexcept
    {
        return pointer_ != nullptr;
    }
    CANN_ASC_STL_API constexpr bool has_value() const noexcept
    {
        return pointer_ != nullptr;
    }
    CANN_ASC_STL_API constexpr T& operator*() const noexcept
    {
        return *pointer_;
    }
    CANN_ASC_STL_API constexpr T* operator->() const noexcept
    {
        return pointer_;
    }

private:
    T* pointer_ = nullptr;
};

template <class T, class U>
CANN_ASC_STL_API constexpr bool operator==(const optional<T>& left, const optional<U>& right)
{
    return left ? (right && *left == *right) : !right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator!=(const optional<T>& left, const optional<U>& right)
{
    return !(left == right);
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator<(const optional<T>& left, const optional<U>& right)
{
    return right && (!left || *left < *right);
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator<=(const optional<T>& left, const optional<U>& right)
{
    return !left || (right && *left <= *right);
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator>(const optional<T>& left, const optional<U>& right)
{
    return right < left;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator>=(const optional<T>& left, const optional<U>& right)
{
    return right <= left;
}

template <class T>
CANN_ASC_STL_API constexpr bool operator==(const optional<T>& value, nullopt_t) noexcept
{
    return !value;
}
template <class T>
CANN_ASC_STL_API constexpr bool operator==(nullopt_t, const optional<T>& value) noexcept
{
    return !value;
}
template <class T>
CANN_ASC_STL_API constexpr bool operator!=(const optional<T>& value, nullopt_t) noexcept
{
    return static_cast<bool>(value);
}
template <class T>
CANN_ASC_STL_API constexpr bool operator!=(nullopt_t, const optional<T>& value) noexcept
{
    return static_cast<bool>(value);
}
template <class T>
CANN_ASC_STL_API constexpr bool operator<(const optional<T>&, nullopt_t) noexcept
{
    return false;
}
template <class T>
CANN_ASC_STL_API constexpr bool operator<(nullopt_t, const optional<T>& value) noexcept
{
    return static_cast<bool>(value);
}
template <class T>
CANN_ASC_STL_API constexpr bool operator<=(const optional<T>& value, nullopt_t) noexcept
{
    return !value;
}
template <class T>
CANN_ASC_STL_API constexpr bool operator<=(nullopt_t, const optional<T>&) noexcept
{
    return true;
}
template <class T>
CANN_ASC_STL_API constexpr bool operator>(const optional<T>& value, nullopt_t) noexcept
{
    return static_cast<bool>(value);
}
template <class T>
CANN_ASC_STL_API constexpr bool operator>(nullopt_t, const optional<T>&) noexcept
{
    return false;
}
template <class T>
CANN_ASC_STL_API constexpr bool operator>=(const optional<T>&, nullopt_t) noexcept
{
    return true;
}
template <class T>
CANN_ASC_STL_API constexpr bool operator>=(nullopt_t, const optional<T>& value) noexcept
{
    return !value;
}

template <class T, class U>
CANN_ASC_STL_API constexpr bool operator==(const optional<T>& left, const U& right)
{
    return left && *left == right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator==(const T& left, const optional<U>& right)
{
    return right && left == *right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator!=(const optional<T>& left, const U& right)
{
    return !left || *left != right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator!=(const T& left, const optional<U>& right)
{
    return !right || left != *right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator<(const optional<T>& left, const U& right)
{
    return !left || *left < right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator<(const T& left, const optional<U>& right)
{
    return right && left < *right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator<=(const optional<T>& left, const U& right)
{
    return !left || *left <= right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator<=(const T& left, const optional<U>& right)
{
    return right && left <= *right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator>(const optional<T>& left, const U& right)
{
    return left && *left > right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator>(const T& left, const optional<U>& right)
{
    return !right || left > *right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator>=(const optional<T>& left, const U& right)
{
    return left && *left >= right;
}
template <class T, class U>
CANN_ASC_STL_API constexpr bool operator>=(const T& left, const optional<U>& right)
{
    return !right || left >= *right;
}

// 自由函数 swap：ADL 与非限定 swap 调用点命中本重载并转发到成员 swap。
// 受限 optional<T&> 特化无交换成员，刻意不参与（引用重绑定在冻结核之外）。
template <class T>
CANN_ASC_STL_API constexpr enable_if_t<is_move_constructible_v<T> && is_swappable_v<T>, void> swap(
    optional<T>& left, optional<T>& right) noexcept(noexcept(left.swap(right)))
{
    left.swap(right);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___OPTIONAL_OPTIONAL_H
