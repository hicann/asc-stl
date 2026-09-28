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

#include <asc/std/__bit/endian.h>

#include <cassert>
#include <cstdint>

int main()
{
    // Exactly one of the two scalar orders is native and they stay distinct.
    static_assert(asc::std::endian::little != asc::std::endian::big);
    static_assert(
        asc::std::endian::native == asc::std::endian::little || asc::std::endian::native == asc::std::endian::big);

    // The platform byte order is little on every supported target.
    static_assert(asc::std::endian::native == asc::std::endian::little);

    constexpr std::uint32_t probe = 0x01020304u;
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&probe);
    assert(bytes[0] == 0x04u ? asc::std::endian::native == asc::std::endian::little :
                               asc::std::endian::native == asc::std::endian::big);
    return 0;
}
