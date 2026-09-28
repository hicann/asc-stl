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

#include <asc/std/__cctype/classification.h>

#include <cassert>
#include <cstdio>

namespace {

// Exhaustive narrow-classification domain: EOF plus all 256 unsigned char
// inputs against the fixed C locale tables.
int expected_class(int value, int kind)
{
    const bool is_upper = value >= 'A' && value <= 'Z';
    const bool is_lower = value >= 'a' && value <= 'z';
    const bool is_digit = value >= '0' && value <= '9';
    const bool is_space = value == ' ' || (value >= 0x09 && value <= 0x0D);
    const bool is_print = value >= 0x20 && value <= 0x7E;
    const bool is_graph = value >= 0x21 && value <= 0x7E;
    const bool is_cntrl = (value >= 0 && value < 0x20) || value == 0x7F;
    const bool is_alpha = is_upper || is_lower;
    const bool is_alnum = is_alpha || is_digit;
    const bool is_xdigit = is_digit || (value >= 'A' && value <= 'F') || (value >= 'a' && value <= 'f');
    const bool is_blank = value == ' ' || value == 0x09;
    const bool is_punct = is_graph && !is_alnum;
    switch (kind) {
        case 0:
            return is_upper;
        case 1:
            return is_lower;
        case 2:
            return is_alpha;
        case 3:
            return is_digit;
        case 4:
            return is_xdigit;
        case 5:
            return is_alnum;
        case 6:
            return is_blank;
        case 7:
            return is_space;
        case 8:
            return is_cntrl;
        case 9:
            return is_print;
        case 10:
            return is_graph;
        default:
            return is_punct;
    }
}

}  // namespace

int main()
{
    int inputs[257]{};
    inputs[0] = -1;
    for (int value = 0; value < 256; ++value) {
        inputs[value + 1] = value;
    }

    for (int index = 0; index < 257; ++index) {
        const int value = inputs[index];
        for (int kind = 0; kind < 12; ++kind) {
            const int expected = expected_class(value, kind);
            const int actual = kind == 0 ? asc::std::isupper(value) :
                kind == 1                ? asc::std::islower(value) :
                kind == 2                ? asc::std::isalpha(value) :
                kind == 3                ? asc::std::isdigit(value) :
                kind == 4                ? asc::std::isxdigit(value) :
                kind == 5                ? asc::std::isalnum(value) :
                kind == 6                ? asc::std::isblank(value) :
                kind == 7                ? asc::std::isspace(value) :
                kind == 8                ? asc::std::iscntrl(value) :
                kind == 9                ? asc::std::isprint(value) :
                kind == 10               ? asc::std::isgraph(value) :
                                           asc::std::ispunct(value);
            const bool ok = (actual != 0) == (expected != 0);
            if (!ok) {
                std::printf(
                    "classification mismatch value=%d kind=%d actual=%d expected=%d\n", value, kind, actual, expected);
                return 1;
            }
        }
        if (value >= 'A' && value <= 'Z') {
            if (asc::std::tolower(value) != value + ('a' - 'A')) {
                return 1;
            }
        } else if (asc::std::tolower(value) != value) {
            return 1;
        }
        if (value >= 'a' && value <= 'z') {
            if (asc::std::toupper(value) != value - ('a' - 'A')) {
                return 1;
            }
        } else if (asc::std::toupper(value) != value) {
            return 1;
        }
    }
    return 0;
}
