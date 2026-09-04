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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_ISTREAMBUF_ITERATOR_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_ISTREAMBUF_ITERATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/ios.h>
#include <asc/std/__host_stdlib/istream>
#include <asc/std/__iterator/default_sentinel.h>
#include <asc/std/__iterator/iterator.h>
#include <asc/std/__iterator/iterator_traits.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH
template <class _CharT, class _Traits>
class istreambuf_iterator {
public:
    using iterator_category = input_iterator_tag;
    using value_type = _CharT;
    using difference_type = typename _Traits::off_type;
    using pointer = _CharT*;
    using reference = _CharT;
    using char_type = _CharT;
    using traits_type = _Traits;
    using int_type = typename _Traits::int_type;
#if CANN_ASC_STL_DETAIL_HOSTED()
    using streambuf_type = ::std::basic_streambuf<_CharT, _Traits>;
    using istream_type = ::std::basic_istream<_CharT, _Traits>;
#else
    using streambuf_type = basic_streambuf<_CharT, _Traits>;
    using istream_type = basic_istream<_CharT, _Traits>;
#endif

private:
    mutable streambuf_type* __sbuf_;

    class __proxy {
        char_type __keep_;
        streambuf_type* __sbuf_;
        CANN_ASC_STL_API explicit __proxy(char_type __c, streambuf_type* __s) : __keep_(__c), __sbuf_(__s)
        {}
        friend class istreambuf_iterator;

    public:
        [[nodiscard]] CANN_ASC_STL_API char_type operator*() const
        {
            return __keep_;
        }
    };

    [[nodiscard]] CANN_ASC_STL_API bool __test_for_eof() const
    {
        if (__sbuf_ && traits_type::eq_int_type(__sbuf_->sgetc(), traits_type::eof())) {
            __sbuf_ = nullptr;
        }
        return __sbuf_ == nullptr;
    }

public:
    CANN_ASC_STL_API constexpr istreambuf_iterator() noexcept : __sbuf_(nullptr)
    {}

    CANN_ASC_STL_API constexpr istreambuf_iterator(default_sentinel_t) noexcept : istreambuf_iterator()
    {}

    CANN_ASC_STL_API istreambuf_iterator(istream_type& __s) noexcept : __sbuf_(__s.rdbuf())
    {}

    CANN_ASC_STL_API istreambuf_iterator(streambuf_type* __s) noexcept : __sbuf_(__s)
    {}

    CANN_ASC_STL_API istreambuf_iterator(const __proxy& __p) noexcept : __sbuf_(__p.__sbuf_)
    {}

    [[nodiscard]] CANN_ASC_STL_API char_type operator*() const
    {
        return static_cast<char_type>(__sbuf_->sgetc());
    }

    CANN_ASC_STL_API istreambuf_iterator& operator++()
    {
        __sbuf_->sbumpc();
        return *this;
    }

    CANN_ASC_STL_API __proxy operator++(int)
    {
        return __proxy(__sbuf_->sbumpc(), __sbuf_);
    }

    [[nodiscard]] CANN_ASC_STL_API bool equal(const istreambuf_iterator& __b) const
    {
        return __test_for_eof() == __b.__test_for_eof();
    }

    [[nodiscard]] CANN_ASC_STL_API friend bool operator==(const istreambuf_iterator& __i, default_sentinel_t)
    {
        return __i.__test_for_eof();
    }
#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    [[nodiscard]] CANN_ASC_STL_API friend bool operator==(default_sentinel_t, const istreambuf_iterator& __i)
    {
        return __i.__test_for_eof();
    }
    [[nodiscard]] CANN_ASC_STL_API friend bool operator!=(const istreambuf_iterator& __i, default_sentinel_t)
    {
        return !__i.__test_for_eof();
    }
    [[nodiscard]] CANN_ASC_STL_API friend bool operator!=(default_sentinel_t, const istreambuf_iterator& __i)
    {
        return !__i.__test_for_eof();
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020
};
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP

template <class _CharT, class _Traits>
[[nodiscard]] CANN_ASC_STL_API bool operator==(
    const istreambuf_iterator<_CharT, _Traits>& __a, const istreambuf_iterator<_CharT, _Traits>& __b)
{
    return __a.equal(__b);
}

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017
template <class _CharT, class _Traits>
[[nodiscard]] CANN_ASC_STL_API bool operator!=(
    const istreambuf_iterator<_CharT, _Traits>& __a, const istreambuf_iterator<_CharT, _Traits>& __b)
{
    return !__a.equal(__b);
}
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_ISTREAMBUF_ITERATOR_H
