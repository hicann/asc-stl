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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_IOS_H
#define CANN_ASC_STL_STD_DETAIL_FWD_IOS_H

#include <asc/std/detail/__config>

#include <asc/std/__fwd/allocator.h>
#include <asc/std/__fwd/char_traits.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

class ios_base;

template <class _CharT, class _Traits = char_traits<_CharT>>
class basic_ios;

template <class _CharT, class _Traits = char_traits<_CharT>>
class basic_streambuf;
template <class _CharT, class _Traits = char_traits<_CharT>>
class basic_istream;
template <class _CharT, class _Traits = char_traits<_CharT>>
class basic_ostream;
template <class _CharT, class _Traits = char_traits<_CharT>>
class basic_iostream;

template <class _CharT, class _Traits = char_traits<_CharT>, class _Allocator = allocator<_CharT>>
class basic_stringbuf;
template <class _CharT, class _Traits = char_traits<_CharT>, class _Allocator = allocator<_CharT>>
class basic_istringstream;
template <class _CharT, class _Traits = char_traits<_CharT>, class _Allocator = allocator<_CharT>>
class basic_ostringstream;
template <class _CharT, class _Traits = char_traits<_CharT>,
    class _Allocator = allocator<_CharT>>  // NOLINT(build/include_what_you_use)
class basic_stringstream;

template <class _CharT, class _Traits = char_traits<_CharT>>
class basic_filebuf;
template <class _CharT, class _Traits = char_traits<_CharT>>
class basic_ifstream;
template <class _CharT, class _Traits = char_traits<_CharT>>
class basic_ofstream;
template <class _CharT, class _Traits = char_traits<_CharT>>
class basic_fstream;

template <class _CharT, class _Traits = char_traits<_CharT>>
class istreambuf_iterator;
template <class _CharT, class _Traits = char_traits<_CharT>>  // NOLINT(build/include_what_you_use)
class ostreambuf_iterator;

using ios = basic_ios<char>;
using wios = basic_ios<wchar_t>;

using streambuf = basic_streambuf<char>;
using istream = basic_istream<char>;
using ostream = basic_ostream<char>;
using iostream = basic_iostream<char>;

using stringbuf = basic_stringbuf<char>;
using istringstream = basic_istringstream<char>;
using ostringstream = basic_ostringstream<char>;
using stringstream = basic_stringstream<char>;

using filebuf = basic_filebuf<char>;
using ifstream = basic_ifstream<char>;
using ofstream = basic_ofstream<char>;
using fstream = basic_fstream<char>;

using wstreambuf = basic_streambuf<wchar_t>;
using wistream = basic_istream<wchar_t>;
using wostream = basic_ostream<wchar_t>;
using wiostream = basic_iostream<wchar_t>;

using wstringbuf = basic_stringbuf<wchar_t>;
using wistringstream = basic_istringstream<wchar_t>;
using wostringstream = basic_ostringstream<wchar_t>;
using wstringstream = basic_stringstream<wchar_t>;

using wfilebuf = basic_filebuf<wchar_t>;
using wifstream = basic_ifstream<wchar_t>;
using wofstream = basic_ofstream<wchar_t>;
using wfstream = basic_fstream<wchar_t>;

#if CANN_ASC_STL_DETAIL_HAS_WCHAR_T()
template <class _State>
class fpos;
using streampos = fpos<mbstate_t>;
using wstreampos = fpos<mbstate_t>;
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
using u8streampos = fpos<mbstate_t>;
#endif  // CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
using u16streampos = fpos<mbstate_t>;
using u32streampos = fpos<mbstate_t>;
#endif  // CANN_ASC_STL_DETAIL_HAS_WCHAR_T()

#if defined(_NEWLIB_VERSION)
// On newlib, off_t is 'long int'
using streamoff = long int;  // for char_traits in <string>
#else
using streamoff = long long;  // for char_traits in <string>
#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_IOS_H
