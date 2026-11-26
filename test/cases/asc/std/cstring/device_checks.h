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

#ifndef ASC_STL_TEST_CSTRING_DEVICE_CHECKS_H
#define ASC_STL_TEST_CSTRING_DEVICE_CHECKS_H

#include <asc/std/cstring>

namespace asc_stl_test_cstring {
CANN_ASC_STL_API int check(int seed = 7)
{
    char buf[16] = {};
    const char* const text = buf;
    char* copied = asc::std::strcpy(buf, "abca");  // NOLINT(runtime/printf)
    if (copied != buf || asc::std::strlen(buf) != 4 || asc::std::strchr(buf, 'a') != buf ||
        asc::std::strchr(text, 0) != text + 4 || asc::std::strrchr(buf, 'a') != buf + 3 ||
        asc::std::strrchr(text, 'x') != nullptr || asc::std::strncmp(buf, "abcz", 3) != 0 ||
        asc::std::strcmp(buf, "abc") <= 0)
        return 1;
    if (asc::std::strpbrk(buf, "xc") != buf + 2 || asc::std::strpbrk(text, "") != nullptr ||
        asc::std::strstr(buf, "bc") != buf + 1 || asc::std::strstr(text, "") != text ||
        asc::std::strspn(buf, "ab") != 2 || asc::std::strcspn(text, "bc") != 1)
        return 2;
    if (asc::std::strcat(buf, "") != buf || asc::std::strncat(buf, "xyz", 2) != buf ||  // NOLINT(runtime/printf)
        asc::std::strcmp(buf, "abcaxy") != 0)
        return 3;
    if (asc::std::strncpy(buf, "q", 4) != buf || buf[0] != 'q' || buf[1] || buf[2] || buf[3] || buf[4] != 'x')
        return 4;
    unsigned char bytes[] = {0, 4, static_cast<unsigned char>(seed + 121), 255, 128};
    const unsigned char* src = bytes;
    unsigned char copy[6] = {0, 0, 0, 0, 0, 99};
    if (asc::std::memcpy(copy, src, 5) != copy || asc::std::memcmp(copy, src, 5) != 0 || copy[5] != 99 ||
        asc::std::memchr(copy, 128, 5) != copy + 2 || asc::std::memchr(src, 255, 3) != nullptr)
        return 5;
    if (asc::std::memmove(copy + 1, copy, 4) != copy + 1 || copy[3] != 128 || copy[4] != 255 ||
        asc::std::memmove(copy, copy + 1, 4) != copy || asc::std::memcmp(copy, bytes, 4) != 0)
        return 6;
    if (asc::std::memset(copy, -1, 2) != copy || copy[0] != 255 || copy[1] != 255 || copy[2] != 128)
        return 7;
    return 0;
}
}  // namespace asc_stl_test_cstring

#endif  // ASC_STL_TEST_CSTRING_DEVICE_CHECKS_H
