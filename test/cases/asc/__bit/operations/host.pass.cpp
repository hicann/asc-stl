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
#include <asc/__bit/operations.h>

#include <cassert>

int main()
{
    static_assert(asc::detail::bit_reverse_impl<unsigned char>(0xB4) == 0x2D);
    static_assert(asc::detail::bit_reverse_impl<unsigned>(0x000000F0) == 0x0F000000u);
    static_assert(asc::detail::bit_reverse_impl<unsigned long long>(0x8000000000000000ULL) == 1ULL);
    static_assert(asc::detail::bit_reverse_impl<unsigned>(0) == 0u);
    static_assert(asc::detail::bit_reverse_impl<unsigned>(~0u) == ~0u);

    static_assert(asc::detail::bitmask_low_impl<unsigned>(0) == 0u);
    static_assert(asc::detail::bitmask_low_impl<unsigned>(3) == 7u);
    static_assert(asc::detail::bitmask_low_impl<unsigned>(31) == 0x7FFFFFFFu);
    static_assert(asc::detail::bitmask_low_impl<unsigned>(32) == 0xFFFFFFFFu);

    static_assert(asc::detail::bitfield_extract_impl<unsigned>(0xF0u, 4, 4) == 0xFu);
    static_assert(asc::detail::bitfield_extract_impl<unsigned>(0xF0u, 8, 4) == 0u);
    static_assert(asc::detail::bitfield_extract_impl<unsigned>(0xABCDEF01u, 12, 8) == 0xDEu);

    static_assert(asc::detail::bitfield_insert_impl<unsigned>(0xF0u, 0x5u, 4, 4) == 0x50u);
    static_assert(asc::detail::bitfield_insert_impl<unsigned>(0xFFFFFFFFu, 0x3u, 4, 4) == 0xFFFFFF3Fu);
    assert(asc::detail::bit_reverse_impl<unsigned>(0x12345678u) == 0x1E6A2C48u);
    return 0;
}
