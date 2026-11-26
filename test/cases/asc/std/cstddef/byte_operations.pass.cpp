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

#include <asc/std/cstddef>

namespace {
namespace ast = asc::std;

bool check_bytes()
{
    constexpr unsigned max_byte = 255;
    const unsigned masks[] = {0, 1, 85, 128, 170, 255};
    for (unsigned bits = 0; bits <= max_byte; ++bits) {
        const auto value = static_cast<ast::byte>(bits);
        if (ast::to_integer<unsigned>(~value) != (bits ^ max_byte)) {
            return false;
        }
        for (auto mask : masks) {
            const auto pattern = static_cast<ast::byte>(mask);
            auto and_value = value;
            auto or_value = value;
            auto xor_value = value;
            and_value &= pattern;
            or_value |= pattern;
            xor_value ^= pattern;
            if (ast::to_integer<unsigned>(and_value) != (bits & mask) || and_value != (value & pattern) ||
                ast::to_integer<unsigned>(or_value) != (bits | mask) || or_value != (value | pattern) ||
                ast::to_integer<unsigned>(xor_value) != (bits ^ mask) || xor_value != (value ^ pattern)) {
                return false;
            }
        }
        for (int shift = 0; shift < 8; ++shift) {
            auto left = value;
            auto right = value;
            left <<= shift;
            right >>= shift;
            if (ast::to_integer<unsigned>(left) != ((bits << shift) & max_byte) || left != (value << shift) ||
                ast::to_integer<unsigned>(right) != (bits >> shift) || right != (value >> shift)) {
                return false;
            }
        }
    }
    return true;
}
}  // namespace

int main()
{
    return check_bytes() ? 0 : 1;
}
