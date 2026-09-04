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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_OSTREAM_ITERATOR_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_OSTREAM_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/char_traits.h>
#include <asc/std/__fwd/ios.h>
#include <asc/std/__host_stdlib/ostream>
#include <asc/std/__iterator/iterator.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
template <class _Tp, class _CharT = char, class _Traits = char_traits<_CharT>>  // NOLINT(build/include_what_you_use)
class ostream_iterator {
public:
    using iterator_category = output_iterator_tag;
    using value_type = void;
#if CANN_ASC_STL_DETAIL_STD_VER > 2017
    using difference_type = ptrdiff_t;
#else
    using difference_type = void;
#endif
    using pointer = void;
    using reference = void;
    using char_type = _CharT;
    using traits_type = _Traits;
#if CANN_ASC_STL_DETAIL_HOSTED()
    using ostream_type = ::std::basic_ostream<_CharT, _Traits>;
#else
    using ostream_type = basic_ostream<_CharT, _Traits>;
#endif

private:
    ostream_type* __out_stream_;
    const char_type* __delim_;

public:
    CANN_ASC_STL_API ostream_iterator(ostream_type& __s) noexcept
        : __out_stream_(::asc::std::addressof(__s)), __delim_(nullptr)
    {}
    CANN_ASC_STL_API ostream_iterator(ostream_type& __s, const _CharT* __delimiter) noexcept
        : __out_stream_(::asc::std::addressof(__s)), __delim_(__delimiter)
    {}
    CANN_ASC_STL_API ostream_iterator& operator=(const _Tp& __value)
    {
        *__out_stream_ << __value;
        if (__delim_) {
            *__out_stream_ << __delim_;
        }
        return *this;
    }

    [[nodiscard]] CANN_ASC_STL_API ostream_iterator& operator*() noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API ostream_iterator& operator++() noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API ostream_iterator& operator++(int) noexcept
    {
        return *this;
    }
};
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_OSTREAM_ITERATOR_H
