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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_EMPTY_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_EMPTY_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/is_object.h>
namespace asc::std::ranges {
template <class T>
class empty_view : public view_interface<empty_view<T>> {
public:
    CANN_ASC_STL_API static constexpr T* begin() noexcept
    {
        return nullptr;
    }
    CANN_ASC_STL_API static constexpr T* end() noexcept
    {
        return nullptr;
    }
    CANN_ASC_STL_API static constexpr T* data() noexcept
    {
        return nullptr;
    }
    CANN_ASC_STL_API static constexpr __SIZE_TYPE__ size() noexcept
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr bool empty() noexcept
    {
        return true;
    }
};
template <class T>
inline constexpr bool enable_borrowed_range<empty_view<T>> = true;
namespace views {
template <class T>
inline constexpr empty_view<T> empty{};
}
}  // namespace asc::std::ranges

#endif  // CANN_ASC_STL_ASC_STD___RANGES_EMPTY_VIEW_H
