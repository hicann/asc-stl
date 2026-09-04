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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_ENABLE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_ENABLE_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/void_t.h>

namespace asc::std::ranges {

struct view_base {};

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class Derived>
    requires is_class_v<Derived> && same_as<Derived, remove_cv_t<Derived>>
class view_interface {
private:
    CANN_ASC_STL_API constexpr Derived& __derived() noexcept
    {
        return static_cast<Derived&>(*this);
    }
    CANN_ASC_STL_API constexpr const Derived& __derived() const noexcept
    {
        return static_cast<const Derived&>(*this);
    }

public:
    CANN_ASC_STL_API constexpr bool empty()
    {
        return __derived().begin() == __derived().end();
    }
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return __derived().begin() == __derived().end();
    }
    CANN_ASC_STL_API constexpr auto data()
    {
        return __derived().begin();
    }
    CANN_ASC_STL_API constexpr auto data() const
    {
        return __derived().begin();
    }
    CANN_ASC_STL_API constexpr auto size()
    {
        return __derived().end() - __derived().begin();
    }
    CANN_ASC_STL_API constexpr auto size() const
    {
        return __derived().end() - __derived().begin();
    }
    CANN_ASC_STL_API constexpr decltype(auto) front()
    {
        return *__derived().begin();
    }
    CANN_ASC_STL_API constexpr decltype(auto) front() const
    {
        return *__derived().begin();
    }
    CANN_ASC_STL_API constexpr decltype(auto) back()
    {
        return *(__derived().end() - 1);
    }
    CANN_ASC_STL_API constexpr decltype(auto) back() const
    {
        return *(__derived().end() - 1);
    }
    template <class Difference>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](Difference index)
    {
        return __derived().begin()[index];
    }
    template <class Difference>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](Difference index) const
    {
        return __derived().begin()[index];
    }
};
#else
template <class Derived, enable_if_t<is_class_v<Derived> && is_same_v<Derived, remove_cv_t<Derived>>, int> = 0>
class view_interface {
private:
    CANN_ASC_STL_API constexpr Derived& __derived() noexcept
    {
        return static_cast<Derived&>(*this);
    }
    CANN_ASC_STL_API constexpr const Derived& __derived() const noexcept
    {
        return static_cast<const Derived&>(*this);
    }

public:
    CANN_ASC_STL_API constexpr bool empty()
    {
        return __derived().begin() == __derived().end();
    }
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return __derived().begin() == __derived().end();
    }
    CANN_ASC_STL_API constexpr auto data()
    {
        return __derived().begin();
    }
    CANN_ASC_STL_API constexpr auto data() const
    {
        return __derived().begin();
    }
    CANN_ASC_STL_API constexpr auto size()
    {
        return __derived().end() - __derived().begin();
    }
    CANN_ASC_STL_API constexpr auto size() const
    {
        return __derived().end() - __derived().begin();
    }
    CANN_ASC_STL_API constexpr decltype(auto) front()
    {
        return *__derived().begin();
    }
    CANN_ASC_STL_API constexpr decltype(auto) front() const
    {
        return *__derived().begin();
    }
    CANN_ASC_STL_API constexpr decltype(auto) back()
    {
        return *(__derived().end() - 1);
    }
    CANN_ASC_STL_API constexpr decltype(auto) back() const
    {
        return *(__derived().end() - 1);
    }
    template <class Difference>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](Difference index)
    {
        return __derived().begin()[index];
    }
    template <class Difference>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](Difference index) const
    {
        return __derived().begin()[index];
    }
};
#endif

template <class Op, class Yp>
CANN_ASC_STL_API auto __is_derived_from_view_interface(const Op*, const view_interface<Yp>*) -> void;

template <class T, class = void>
inline constexpr bool enable_view = is_base_of_v<view_base, T>;

template <class T>
inline constexpr bool enable_view<T,
    void_t<decltype(__is_derived_from_view_interface(static_cast<T*>(nullptr), static_cast<T*>(nullptr)))>> = true;

}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_ENABLE_VIEW_H
