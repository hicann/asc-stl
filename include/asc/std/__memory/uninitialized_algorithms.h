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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_UNINITIALIZED_ALGORITHMS_H
#define CANN_ASC_STL_ASC_STD___MEMORY_UNINITIALIZED_ALGORITHMS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/copy.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/move.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__algorithm/unwrap_range.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/allocator_traits.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__memory/voidify.h>
#include <asc/std/__type_traits/extent.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/is_trivially_copy_constructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/is_trivially_move_constructible.h>
#include <asc/std/__type_traits/is_unbounded_array.h>
#include <asc/std/__type_traits/negation.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_extent.h>
#include <asc/std/__utility/exception_guard.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __uninitialized_detail {
template <class Iterator>
class rollback_guard {
public:
    CANN_ASC_STL_API constexpr explicit rollback_guard(Iterator first) : first_(first), current_(first), active_(true)
    {}
    CANN_ASC_STL_API ~rollback_guard()
    {
        if (active_)
            ::asc::std::__destroy(first_, current_);
    }
    CANN_ASC_STL_API constexpr Iterator& current() noexcept
    {
        return current_;
    }
    CANN_ASC_STL_API constexpr void release() noexcept
    {
        active_ = false;
    }

private:
    Iterator first_;
    Iterator current_;
    bool active_;
};
template <class Iterator>
using value_type = typename iterator_traits<Iterator>::value_type;
}  // namespace __uninitialized_detail

template <class Input, class Forward>
CANN_ASC_STL_API Forward uninitialized_copy(Input first, Input last, Forward output)
{
    __uninitialized_detail::rollback_guard<Forward> guard(output);
    for (; first != last; ++first, ++guard.current())
        ::asc::std::__construct_at(::asc::std::addressof(*guard.current()), *first);
    Forward result = guard.current();
    guard.release();
    return result;
}
template <class Input, class Size, class Forward>
CANN_ASC_STL_API Forward uninitialized_copy_n(Input first, Size count, Forward output)
{
    __uninitialized_detail::rollback_guard<Forward> guard(output);
    for (; count > 0; --count, ++first, ++guard.current())
        ::asc::std::__construct_at(::asc::std::addressof(*guard.current()), *first);
    Forward result = guard.current();
    guard.release();
    return result;
}
template <class Forward, class T>
CANN_ASC_STL_API void uninitialized_fill(Forward first, Forward last, const T& value)
{
    __uninitialized_detail::rollback_guard<Forward> guard(first);
    for (; guard.current() != last; ++guard.current())
        ::asc::std::__construct_at(::asc::std::addressof(*guard.current()), value);
    guard.release();
}
template <class Forward, class Size, class T>
CANN_ASC_STL_API Forward uninitialized_fill_n(Forward first, Size count, const T& value)
{
    __uninitialized_detail::rollback_guard<Forward> guard(first);
    for (; count > 0; --count, ++guard.current())
        ::asc::std::__construct_at(::asc::std::addressof(*guard.current()), value);
    Forward result = guard.current();
    guard.release();
    return result;
}
template <class Forward>
CANN_ASC_STL_API void uninitialized_default_construct(Forward first, Forward last)
{
    __uninitialized_detail::rollback_guard<Forward> guard(first);
    for (; guard.current() != last; ++guard.current())
        ::new (::asc::std::__voidify(*guard.current())) __uninitialized_detail::value_type<Forward>;
    guard.release();
}
template <class Forward, class Size>
CANN_ASC_STL_API Forward uninitialized_default_construct_n(Forward first, Size count)
{
    __uninitialized_detail::rollback_guard<Forward> guard(first);
    for (; count > 0; --count, ++guard.current())
        ::new (::asc::std::__voidify(*guard.current())) __uninitialized_detail::value_type<Forward>;
    Forward result = guard.current();
    guard.release();
    return result;
}
template <class Forward>
CANN_ASC_STL_API void uninitialized_value_construct(Forward first, Forward last)
{
    __uninitialized_detail::rollback_guard<Forward> guard(first);
    for (; guard.current() != last; ++guard.current())
        ::asc::std::__construct_at(::asc::std::addressof(*guard.current()));
    guard.release();
}
template <class Forward, class Size>
CANN_ASC_STL_API Forward uninitialized_value_construct_n(Forward first, Size count)
{
    __uninitialized_detail::rollback_guard<Forward> guard(first);
    for (; count > 0; --count, ++guard.current())
        ::asc::std::__construct_at(::asc::std::addressof(*guard.current()));
    Forward result = guard.current();
    guard.release();
    return result;
}
template <class Input, class Forward>
CANN_ASC_STL_API Forward uninitialized_move(Input first, Input last, Forward output)
{
    __uninitialized_detail::rollback_guard<Forward> guard(output);
    for (; first != last; ++first, ++guard.current())
        ::asc::std::__construct_at(::asc::std::addressof(*guard.current()), ::asc::std::move(*first));
    Forward result = guard.current();
    guard.release();
    return result;
}
template <class Input, class Size, class Forward>
CANN_ASC_STL_API pair<Input, Forward> uninitialized_move_n(Input first, Size count, Forward output)
{
    __uninitialized_detail::rollback_guard<Forward> guard(output);
    for (; count > 0; --count, ++first, ++guard.current())
        // NOLINTNEXTLINE(build/include_what_you_use)
        ::asc::std::__construct_at(::asc::std::addressof(*guard.current()), ::asc::std::move(*first));
    Forward result = guard.current();
    guard.release();
    return {first, result};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_UNINITIALIZED_ALGORITHMS_H
