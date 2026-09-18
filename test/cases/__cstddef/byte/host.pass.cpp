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

#include <asc/std/__cstddef/byte.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq_int(const char* expr, unsigned int got, unsigned int expected)
{
    bool ok = (got == expected);
    std::cout << "[host][byte] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

constexpr asc::std::byte compile_time_byte = asc::std::byte{0x3c};
static_assert(asc::std::to_integer<unsigned>(compile_time_byte | asc::std::byte{0xc0}) == 0xfcu);
static_assert(asc::std::to_integer<unsigned>(compile_time_byte & asc::std::byte{0x0f}) == 0x0cu);
static_assert(asc::std::to_integer<unsigned>(compile_time_byte ^ asc::std::byte{0x3f}) == 0x03u);
static_assert(asc::std::to_integer<unsigned>(~asc::std::byte{0xf0}) == 0x0fu);
static_assert(asc::std::to_integer<unsigned>(compile_time_byte << 1) == 0x78u);
static_assert(asc::std::to_integer<unsigned>(compile_time_byte >> 2) == 0x0fu);

int main()
{
    using asc::std::byte;

    // Construction
    byte b0{0x00};
    byte b1{0x0F};
    byte b2{0xF0};
    byte b3{0xFF};

    // to_integer
    expect_eq_int("to_integer<int>(byte{0x0F})", static_cast<unsigned int>(asc::std::to_integer<int>(b1)), 0x0Fu);
    expect_eq_int("to_integer<int>(byte{0xF0})", static_cast<unsigned int>(asc::std::to_integer<int>(b2)), 0xF0u);
    expect_eq_int("to_integer<int>(byte{0xFF})", static_cast<unsigned int>(asc::std::to_integer<int>(b3)), 0xFFu);
    expect_eq_int("to_integer<unsigned char>(byte{0x00})",
        static_cast<unsigned int>(asc::std::to_integer<unsigned char>(b0)), 0x00u);

    // operator|
    expect_eq_int("byte{0x0F} | byte{0xF0}", static_cast<unsigned int>(asc::std::to_integer<int>(b1 | b2)), 0xFFu);
    expect_eq_int("byte{0x0F} | byte{0x0F}", static_cast<unsigned int>(asc::std::to_integer<int>(b1 | b1)), 0x0Fu);
    expect_eq_int("byte{0xFF} | byte{0x00}", static_cast<unsigned int>(asc::std::to_integer<int>(b3 | b0)), 0xFFu);

    // operator|=
    byte b_or = b1;
    b_or |= b2;
    expect_eq_int("byte{0x0F} |= byte{0xF0}", static_cast<unsigned int>(asc::std::to_integer<int>(b_or)), 0xFFu);

    // operator&
    expect_eq_int("byte{0xFF} & byte{0x0F}", static_cast<unsigned int>(asc::std::to_integer<int>(b3 & b1)), 0x0Fu);
    expect_eq_int("byte{0xFF} & byte{0xF0}", static_cast<unsigned int>(asc::std::to_integer<int>(b3 & b2)), 0xF0u);
    expect_eq_int("byte{0x0F} & byte{0xF0}", static_cast<unsigned int>(asc::std::to_integer<int>(b1 & b2)), 0x00u);

    // operator&=
    byte b_and = b3;
    b_and &= b1;
    expect_eq_int("byte{0xFF} &= byte{0x0F}", static_cast<unsigned int>(asc::std::to_integer<int>(b_and)), 0x0Fu);

    // operator^
    expect_eq_int("byte{0xFF} ^ byte{0x0F}", static_cast<unsigned int>(asc::std::to_integer<int>(b3 ^ b1)), 0xF0u);
    expect_eq_int("byte{0x0F} ^ byte{0xF0}", static_cast<unsigned int>(asc::std::to_integer<int>(b1 ^ b2)), 0xFFu);
    expect_eq_int("byte{0x0F} ^ byte{0x0F}", static_cast<unsigned int>(asc::std::to_integer<int>(b1 ^ b1)), 0x00u);

    // operator^=
    byte b_xor = b3;
    b_xor ^= b1;
    expect_eq_int("byte{0xFF} ^= byte{0x0F}", static_cast<unsigned int>(asc::std::to_integer<int>(b_xor)), 0xF0u);

    // operator~
    expect_eq_int("~byte{0x00}", static_cast<unsigned int>(asc::std::to_integer<int>(~b0)), 0xFFu);
    expect_eq_int("~byte{0xFF}", static_cast<unsigned int>(asc::std::to_integer<int>(~b3)), 0x00u);
    expect_eq_int("~byte{0x0F}", static_cast<unsigned int>(asc::std::to_integer<int>(~b1)), 0xF0u);
    expect_eq_int("~byte{0xF0}", static_cast<unsigned int>(asc::std::to_integer<int>(~b2)), 0x0Fu);

    // operator<<
    expect_eq_int("byte{0x01} << 3", static_cast<unsigned int>(asc::std::to_integer<int>(byte{0x01} << 3)), 0x08u);
    expect_eq_int("byte{0x01} << 7", static_cast<unsigned int>(asc::std::to_integer<int>(byte{0x01} << 7)), 0x80u);
    expect_eq_int("byte{0xFF} << 0", static_cast<unsigned int>(asc::std::to_integer<int>(byte{0xFF} << 0)), 0xFFu);

    // operator<<=
    byte b_shl = byte{0x01};
    b_shl <<= 4;
    expect_eq_int("byte{0x01} <<= 4", static_cast<unsigned int>(asc::std::to_integer<int>(b_shl)), 0x10u);

    // operator>>
    expect_eq_int("byte{0x80} >> 3", static_cast<unsigned int>(asc::std::to_integer<int>(byte{0x80} >> 3)), 0x10u);
    expect_eq_int("byte{0xFF} >> 4", static_cast<unsigned int>(asc::std::to_integer<int>(byte{0xFF} >> 4)), 0x0Fu);
    expect_eq_int("byte{0x80} >> 7", static_cast<unsigned int>(asc::std::to_integer<int>(byte{0x80} >> 7)), 0x01u);

    // operator>>=
    byte b_shr = byte{0x80};
    b_shr >>= 4;
    expect_eq_int("byte{0x80} >>= 4", static_cast<unsigned int>(asc::std::to_integer<int>(b_shr)), 0x08u);

    return g_failures == 0 ? 0 : 1;
}
