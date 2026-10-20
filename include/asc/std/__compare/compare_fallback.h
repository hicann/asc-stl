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

#ifndef CANN_ASC_STL_STD_DETAIL_COMPARE_COMPARE_FALLBACK_H
#define CANN_ASC_STL_STD_DETAIL_COMPARE_COMPARE_FALLBACK_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__compare/ordering.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace detail {

// Header-local vocabulary so the fallback comparison roots stay inside their
// planned two-edge closure. The unevaluated expression probe uses static_cast
// on a null pointer instead of an extern declval reference so no
// namespace-scope variable participates in a device-reachable signature.
template <bool Value>
struct fallback_bool {
    static constexpr bool value = Value;
};

template <class...>
using fallback_void = void;

template <class T>
struct fallback_remove_ref {
    using type = T;
};
template <class T>
struct fallback_remove_ref<T&> {
    using type = T;
};
template <class T>
struct fallback_remove_ref<T&&> {
    using type = T;
};
template <class T>
using fallback_remove_ref_t = typename fallback_remove_ref<T>::type;

template <class T, class U, class = void>
struct has_three_way : fallback_bool<false> {};

#if CANN_ASC_STL_DETAIL_HAS_THREE_WAY_COMPARISON()
// The probe strips references first: static_cast<T*> is ill-formed when T is
// a reference type.
template <class T, class U>
struct has_three_way<T, U,
    fallback_void<decltype(*static_cast<fallback_remove_ref_t<T>*>(nullptr) <=>
        *static_cast<fallback_remove_ref_t<U>*>(nullptr))>> : fallback_bool<true> {};
#endif

template <class T, class U>
struct fallback_is_same : fallback_bool<false> {};
template <class T>
struct fallback_is_same<T, T> : fallback_bool<true> {};

// Built-in three-way operands produce the compiler's own category type; the
// ASC vocabulary result is returned directly, every other category is
// translated through the standard ordered-against-zero idiom.
template <class Result>
CANN_ASC_STL_API constexpr strong_ordering translate_strong(const Result& result)
{
    if constexpr (fallback_is_same<Result, strong_ordering>::value) {
        return result;
    } else {
        if (result < 0) {
            return strong_ordering::less;
        }
        if (0 < result) {
            return strong_ordering::greater;
        }
        return strong_ordering::equal;
    }
}

template <class Result>
CANN_ASC_STL_API constexpr weak_ordering translate_weak(const Result& result)
{
    if constexpr (fallback_is_same<Result, weak_ordering>::value) {
        return result;
    } else {
        if (result < 0) {
            return weak_ordering::less;
        }
        if (0 < result) {
            return weak_ordering::greater;
        }
        return weak_ordering::equivalent;
    }
}

template <class Result>
CANN_ASC_STL_API constexpr partial_ordering translate_partial(const Result& result)
{
    if constexpr (fallback_is_same<Result, partial_ordering>::value) {
        return result;
    } else {
        if (result < 0) {
            return partial_ordering::less;
        }
        if (0 < result) {
            return partial_ordering::greater;
        }
        if (result == 0) {
            return partial_ordering::equivalent;
        }
        return partial_ordering::unordered;
    }
}

template <class T, class U>
CANN_ASC_STL_API constexpr strong_ordering strong_synthesize(T& left, U& right)
{
    if (left == right) {
        return strong_ordering::equal;
    }
    if (left < right) {
        return strong_ordering::less;
    }
    return strong_ordering::greater;
}

template <class T, class U>
CANN_ASC_STL_API constexpr weak_ordering weak_synthesize(T& left, U& right)
{
    if (left == right) {
        return weak_ordering::equivalent;
    }
    if (left < right) {
        return weak_ordering::less;
    }
    return weak_ordering::greater;
}

template <class T, class U>
CANN_ASC_STL_API constexpr partial_ordering partial_synthesize(T& left, U& right)
{
    if (left < right) {
        return partial_ordering::less;
    }
    if (right < left) {
        return partial_ordering::greater;
    }
    if (left == right) {
        return partial_ordering::equivalent;
    }
    return partial_ordering::unordered;
}

template <class T, class U>
CANN_ASC_STL_API constexpr strong_ordering strong_fallback(T&& left, U& right)
{
#if CANN_ASC_STL_DETAIL_HAS_THREE_WAY_COMPARISON()
    if constexpr (has_three_way<fallback_remove_ref_t<T>, fallback_remove_ref_t<U>>::value) {
        return translate_strong(static_cast<T&&>(left) <=> right);
    } else {
        return strong_synthesize(left, right);
    }
#else
    return strong_synthesize(left, right);
#endif
}

template <class T, class U>
CANN_ASC_STL_API constexpr weak_ordering weak_fallback(T&& left, U& right)
{
#if CANN_ASC_STL_DETAIL_HAS_THREE_WAY_COMPARISON()
    if constexpr (has_three_way<fallback_remove_ref_t<T>, fallback_remove_ref_t<U>>::value) {
        return translate_weak(static_cast<T&&>(left) <=> right);
    } else {
        return weak_synthesize(left, right);
    }
#else
    return weak_synthesize(left, right);
#endif
}

template <class T, class U>
CANN_ASC_STL_API constexpr partial_ordering partial_fallback(T&& left, U& right)
{
#if CANN_ASC_STL_DETAIL_HAS_THREE_WAY_COMPARISON()
    if constexpr (has_three_way<fallback_remove_ref_t<T>, fallback_remove_ref_t<U>>::value) {
        return translate_partial(static_cast<T&&>(left) <=> right);
    } else {
        return partial_synthesize(left, right);
    }
#else
    return partial_synthesize(left, right);
#endif
}

}  // namespace detail

struct compare_strong_order_fallback {
    template <class T, class U>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr strong_ordering operator()(T&& left, U&& right) const
    {
        return ::asc::std::detail::strong_fallback(static_cast<T&&>(left), right);
    }
};

struct compare_weak_order_fallback {
    template <class T, class U>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr weak_ordering operator()(T&& left, U&& right) const
    {
        return ::asc::std::detail::weak_fallback(static_cast<T&&>(left), right);
    }
};

struct compare_partial_order_fallback {
    template <class T, class U>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr partial_ordering operator()(T&& left, U&& right) const
    {
        return ::asc::std::detail::partial_fallback(static_cast<T&&>(left), right);
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_COMPARE_COMPARE_FALLBACK_H
