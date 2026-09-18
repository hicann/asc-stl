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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_EMPTY_VIEW_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_EMPTY_VIEW_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__ranges/view_interface.h>
#include <asc/std/__type_traits/is_object.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_object_v<_Tp>)
class empty_view : public view_interface<empty_view<_Tp>> {
public:
    CANN_ASC_STL_API static constexpr _Tp* begin() noexcept
    {
        return nullptr;
    }
    CANN_ASC_STL_API static constexpr _Tp* end() noexcept
    {
        return nullptr;
    }
    CANN_ASC_STL_API static constexpr _Tp* data() noexcept
    {
        return nullptr;
    }
    CANN_ASC_STL_API static constexpr size_t size() noexcept
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr bool empty() noexcept
    {
        return true;
    }
};

template <class _Tp>
inline constexpr bool enable_borrowed_range<empty_view<_Tp>> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_VIEWS

template <class _Tp>
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT empty_view<_Tp> empty{};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_VIEWS

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_EMPTY_VIEW_H
