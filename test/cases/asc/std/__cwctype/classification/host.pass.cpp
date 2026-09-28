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

#include <asc/std/__cwctype/classification.h>
#include <asc/std/__cwctype/descriptors.h>

#include <cassert>
#include <cstdio>

namespace {

// All twelve wide-classification descriptors plus every direct wide
// classification over the 0..255 domain and WEOF.
bool expected_wide(asc::std::wint_t value, int kind)
{
    const bool is_upper = value >= L'A' && value <= L'Z';
    const bool is_lower = value >= L'a' && value <= L'z';
    const bool is_digit = value >= L'0' && value <= L'9';
    const bool is_alpha = is_upper || is_lower;
    const bool is_alnum = is_alpha || is_digit;
    const bool is_print = value >= 0x20 && value <= 0x7E;
    const bool is_graph = value >= 0x21 && value <= 0x7E;
    const bool is_cntrl = value < 0x20 || value == 0x7F;
    const bool is_punct = is_graph && !is_alnum;
    const bool is_blank = value == L' ' || value == L'\t';
    const bool is_space = value == L' ' || (value >= L'\t' && value <= L'\r');
    const bool is_xdigit = is_digit || (value >= L'A' && value <= L'F') || (value >= L'a' && value <= L'f');
    switch (kind) {
        case 0:
            return is_alnum;
        case 1:
            return is_alpha;
        case 2:
            return is_blank;
        case 3:
            return is_cntrl;
        case 4:
            return is_digit;
        case 5:
            return is_graph;
        case 6:
            return is_lower;
        case 7:
            return is_print;
        case 8:
            return is_punct;
        case 9:
            return is_space;
        case 10:
            return is_upper;
        default:
            return is_xdigit;
    }
}

}  // namespace

int main()
{
    const char* names[12] = {
        "alnum", "alpha", "blank", "cntrl", "digit", "graph", "lower", "print", "punct", "space", "upper", "xdigit"};
    for (int index = 0; index < 12; ++index) {
        const asc::std::wctype_t descriptor = asc::std::wctype(names[index]);
        assert(descriptor != 0);
        for (asc::std::wint_t value = 0; value < 256; ++value) {
            const int actual = asc::std::iswctype(value, descriptor);
            const bool expected = expected_wide(value, index);
            if ((actual != 0) != expected) {
                std::printf("wide mismatch name=%s value=%u\n", names[index], static_cast<unsigned>(value));
                return 1;
            }
        }
        const asc::std::wint_t weof = static_cast<asc::std::wint_t>(-1);
        assert(asc::std::iswctype(weof, descriptor) == 0);
    }

    // Unknown properties resolve to the none descriptor.
    assert(asc::std::wctype("nope") == asc::std::wctype_t(0));

    // Direct classification: the fourteen functions over the same domain.
    for (asc::std::wint_t value = 0; value < 256; ++value) {
        assert((asc::std::iswalpha(value) != 0) == expected_wide(value, 1));
        assert((asc::std::iswupper(value) != 0) == expected_wide(value, 10));
        assert((asc::std::iswlower(value) != 0) == expected_wide(value, 6));
        assert((asc::std::iswdigit(value) != 0) == expected_wide(value, 4));
        assert((asc::std::iswxdigit(value) != 0) == expected_wide(value, 11));
        assert((asc::std::iswalnum(value) != 0) == expected_wide(value, 0));
        assert((asc::std::iswblank(value) != 0) == expected_wide(value, 2));
        assert((asc::std::iswspace(value) != 0) == expected_wide(value, 9));
        assert((asc::std::iswcntrl(value) != 0) == expected_wide(value, 3));
        assert((asc::std::iswprint(value) != 0) == expected_wide(value, 7));
        assert((asc::std::iswgraph(value) != 0) == expected_wide(value, 5));
        assert((asc::std::iswpunct(value) != 0) == expected_wide(value, 8));
    }
    const asc::std::wint_t weof = static_cast<asc::std::wint_t>(-1);
    assert(asc::std::iswalpha(weof) == 0);
    assert(asc::std::iswprint(weof) == 0);
    assert(asc::std::iswcntrl(weof) == 0);

    // Case conversion and descriptor-driven conversion.
    assert(asc::std::towlower(L'Q') == L'q');
    assert(asc::std::towupper(L'q') == L'Q');
    assert(asc::std::towlower(L'1') == L'1');
    assert(asc::std::towupper(weof) == weof);
    assert(asc::std::wctrans("tolower") != asc::std::wctrans_t(0));
    assert(asc::std::wctrans("toupper") != asc::std::wctrans_t(0));
    assert(asc::std::wctrans("nope") == asc::std::wctrans_t(0));
    assert(asc::std::towctrans(L'Q', asc::std::wctrans("tolower")) == L'q');
    assert(asc::std::towctrans(L'q', asc::std::wctrans("toupper")) == L'Q');
    return 0;
}
