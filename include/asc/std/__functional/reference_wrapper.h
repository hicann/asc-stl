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

#ifndef CANN_ASC_STL_ASC_STD___FUNCTIONAL_REFERENCE_WRAPPER_H
#define CANN_ASC_STL_ASC_STD___FUNCTIONAL_REFERENCE_WRAPPER_H

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
#include <asc/std/__functional/weak_result_type.h>
#include <asc/std/__fwd/reference_wrapper.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
class reference_wrapper : public __weak_result_type<T> {
public:
    using type = T;

    template <class U, class = enable_if_t<!__is_same(remove_cvref_t<U>, reference_wrapper)>>
    CANN_ASC_STL_API constexpr reference_wrapper(U&& value) noexcept(
        noexcept(reference_wrapper::__accept(::asc::std::forward<U>(value))))
        : pointer_(::asc::std::addressof(__accept(::asc::std::forward<U>(value))))
    {}

    CANN_ASC_STL_API constexpr operator T&() const noexcept
    {
        return *pointer_;
    }

    CANN_ASC_STL_API constexpr T& get() const noexcept
    {
        return *pointer_;
    }

    template <class... Args>
    CANN_ASC_STL_API constexpr invoke_result_t<T&, Args...> operator()(Args&&... args) const
        noexcept(is_nothrow_invocable_v<T&, Args...>)
    {
        return ::asc::std::invoke(get(),          // NOLINT(build/include_what_you_use)
            ::asc::std::forward<Args>(args)...);  // NOLINT(build/include_what_you_use)
    }

private:
    static CANN_ASC_STL_API constexpr T& __accept(T& value) noexcept
    {
        return value;
    }
    static void __accept(T&&) = delete;

    T* pointer_;
};

template <class T>
CANN_ASC_STL_API constexpr reference_wrapper<T> ref(T& value) noexcept
{
    return reference_wrapper<T>(value);
}
template <class T>
void ref(const T&&) = delete;
template <class T>
CANN_ASC_STL_API constexpr reference_wrapper<T> ref(reference_wrapper<T> value) noexcept
{
    return value;
}

template <class T>
CANN_ASC_STL_API constexpr reference_wrapper<const T> cref(const T& value) noexcept
{
    return reference_wrapper<const T>(value);
}
template <class T>
void cref(const T&&) = delete;
template <class T>
CANN_ASC_STL_API constexpr reference_wrapper<const T> cref(reference_wrapper<T> value) noexcept
{
    return reference_wrapper<const T>(value.get());
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FUNCTIONAL_REFERENCE_WRAPPER_H
