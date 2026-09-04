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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_ISTREAM_ITERATOR_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_ISTREAM_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/char_traits.h>
#include <asc/std/__fwd/ios.h>
#include <asc/std/__host_stdlib/istream>
#include <asc/std/__iterator/default_sentinel.h>
#include <asc/std/__iterator/iterator.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
template <class _Tp, class _CharT = char, class _Traits = char_traits<_CharT>,  // NOLINT(build/include_what_you_use)
    class _Distance = ptrdiff_t>                                                // NOLINT(build/include_what_you_use)
class istream_iterator {
public:
    using iterator_category = input_iterator_tag;
    using value_type = _Tp;
    using difference_type = _Distance;
    using pointer = const _Tp*;
    using reference = const _Tp&;
    using char_type = _CharT;
    using traits_type = _Traits;
#if CANN_ASC_STL_DETAIL_HOSTED()
    using istream_type = ::std::basic_istream<_CharT, _Traits>;
#else
    using istream_type = basic_istream<_CharT, _Traits>;
#endif

private:
    istream_type* __in_stream_;
    _Tp __value_;

public:
    CANN_ASC_STL_API constexpr istream_iterator() : __in_stream_(nullptr), __value_()
    {}

    CANN_ASC_STL_API constexpr istream_iterator(default_sentinel_t) : istream_iterator()
    {}

    CANN_ASC_STL_API istream_iterator(istream_type& __s) : __in_stream_(::asc::std::addressof(__s))
    {
        if (!(*__in_stream_ >> __value_)) {
            __in_stream_ = nullptr;
        }
    }

    [[nodiscard]] CANN_ASC_STL_API const _Tp& operator*() const noexcept
    {
        return __value_;
    }

    [[nodiscard]] CANN_ASC_STL_API const _Tp* operator->() const noexcept
    {
        return ::asc::std::addressof((operator*()));
    }

    CANN_ASC_STL_API istream_iterator& operator++()
    {
        if (!(*__in_stream_ >> __value_)) {
            __in_stream_ = nullptr;
        }
        return *this;
    }

    CANN_ASC_STL_API istream_iterator operator++(int)
    {
        istream_iterator __t(*this);
        ++(*this);
        return __t;
    }

    template <class _Up, class _CharU, class _TraitsU, class _DistanceU>
    CANN_ASC_STL_API friend bool operator==(const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __x,
        const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __y);

    [[nodiscard]] CANN_ASC_STL_API friend bool operator==(const istream_iterator& __i, default_sentinel_t)
    {
        return __i.__in_stream_ == nullptr;
    }

#if CANN_ASC_STL_DETAIL_STD_VER < 2020

    [[nodiscard]] CANN_ASC_STL_API friend bool operator==(default_sentinel_t, const istream_iterator& __i)
    {
        return __i.__in_stream_ == nullptr;
    }

    [[nodiscard]] CANN_ASC_STL_API friend bool operator!=(const istream_iterator& __i, default_sentinel_t)
    {
        return __i.__in_stream_ != nullptr;
    }

    [[nodiscard]] CANN_ASC_STL_API friend bool operator!=(default_sentinel_t, const istream_iterator& __i)
    {
        return __i.__in_stream_ != nullptr;
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020
};
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

template <class _Tp, class _CharT, class _Traits, class _Distance>
[[nodiscard]] CANN_ASC_STL_API bool operator==(const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __x,
    const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __y)
{
    return __x.__in_stream_ == __y.__in_stream_;
}

template <class _Tp, class _CharT, class _Traits, class _Distance>
[[nodiscard]] CANN_ASC_STL_API bool operator!=(const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __x,
    const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __y)
{
    return !(__x == __y);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_ISTREAM_ITERATOR_H
