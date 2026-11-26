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

#include <asc/std/cstdint>
#include <cstddef>
#include <csignal>
#include <cwchar>
#include "integer_limits.h"

int main()
{
    static_assert(sizeof(asc::std::int8_t) == 1);
    static_assert(sizeof(asc::std::int16_t) == 2);
    static_assert(sizeof(asc::std::int32_t) == 4);
    static_assert(sizeof(asc::std::int64_t) == 8);
    static_assert(sizeof(asc::std::uint8_t) == 1);
    static_assert(sizeof(asc::std::uint16_t) == 2);
    static_assert(sizeof(asc::std::uint32_t) == 4);
    static_assert(sizeof(asc::std::uint64_t) == 8);
    static_assert(asc::std::int8_t(-1) < 0);
    static_assert(asc::std::uint8_t(-1) > 0);
    static_assert(PTRDIFF_MIN == asc::std::numeric_limits<std::ptrdiff_t>::min());
    static_assert(PTRDIFF_MAX == asc::std::numeric_limits<std::ptrdiff_t>::max());
    static_assert(SIZE_MAX == asc::std::numeric_limits<std::size_t>::max());
    static_assert(SIG_ATOMIC_MIN == asc::std::numeric_limits<std::sig_atomic_t>::min());
    static_assert(SIG_ATOMIC_MAX == asc::std::numeric_limits<std::sig_atomic_t>::max());
    static_assert(WINT_MIN == asc::std::numeric_limits<std::wint_t>::min());
    static_assert(WINT_MAX == asc::std::numeric_limits<std::wint_t>::max());
    static_assert(WCHAR_MIN == asc::std::numeric_limits<wchar_t>::min());
    static_assert(WCHAR_MAX == asc::std::numeric_limits<wchar_t>::max());
    return 0;
}
