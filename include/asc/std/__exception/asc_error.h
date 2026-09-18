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

#ifndef CANN_ASC_STL_STD_DETAIL_EXCEPTION_ASC_ERROR_H
#define CANN_ASC_STL_STD_DETAIL_EXCEPTION_ASC_ERROR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__exception/exception_macros.h>
#include <asc/std/__exception/msg_storage.h>
#include <asc/std/__host_stdlib/stdexcept>
#include <asc/std/source_location>

#if CANN_ASC_STL_DETAIL_HOSTED()
#if __has_include(<acl/acl_base_rt.h>)
#include <acl/acl_base_rt.h>
#define CANN_ASC_STL_DETAIL_HAS_ACL_ERROR_TYPE 1
#else
#define CANN_ASC_STL_DETAIL_HAS_ACL_ERROR_TYPE 0
#endif
#include <cstdio>
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

#if CANN_ASC_STL_DETAIL_HOSTED() && CANN_ASC_STL_DETAIL_HAS_ACL_ERROR_TYPE
using __asc_error_t = ::aclError;
#else
using __asc_error_t = int;
#endif

#if CANN_ASC_STL_DETAIL_HOSTED()
namespace __detail {
// 手写有界追加, 避免不安全格式化函数; 缓冲区初始化为全 0, 追加不写末位, 天然保终止符。
static char* __append_span(char* __cursor, char* __last, const char* __text) noexcept
{
    while (__cursor != __last && *__text != '\0') {
        *__cursor++ = *__text++;
    }
    return __cursor;
}

static char* __append_int(char* __cursor, char* __last, int __value) noexcept
{
    char __digits[12];
    unsigned int __magnitude =
        __value < 0 ? 0U - static_cast<unsigned int>(__value) : static_cast<unsigned int>(__value);
    int __count = 0;
    do {
        __digits[__count++] = static_cast<char>('0' + __magnitude % 10U);
        __magnitude /= 10U;
    } while (__magnitude != 0U);
    if (__value < 0 && __cursor != __last) {
        *__cursor++ = '-';
    }
    while (__count > 0 && __cursor != __last) {
        *__cursor++ = __digits[--__count];
    }
    return __cursor;
}

static char* __format_asc_error(::asc::__msg_storage& __msg_buffer, const int __status, const char* __msg,
    const char* __api = nullptr, ::asc::std::source_location __loc = ::asc::std::source_location::current()) noexcept
{
    char* const __first = __msg_buffer.__buffer;
    char* const __last = __first + sizeof(__msg_buffer.__buffer);
    char* __cursor = __append_span(__first, __last, __loc.file_name());
    __cursor = __append_span(__cursor, __last, ":");
    __cursor = __append_int(__cursor, __last, static_cast<int>(__loc.line()));
    if (__api != nullptr) {
        __cursor = __append_span(__cursor, __last, __api);
        __cursor = __append_span(__cursor, __last, " ");
    }
    __cursor = __append_span(__cursor, __last, "aclError(");
    __cursor = __append_int(__cursor, __last, __status);
    __cursor = __append_span(__cursor, __last, "): ");
    __append_span(__cursor, __last, __msg);
    return __first;
}
}  // namespace __detail

/**
 * @brief Exception thrown when an ASC error is encountered.
 */
class asc_error : public ::std::runtime_error {
public:
    asc_error(const __asc_error_t __status, const char* __msg, const char* __api = nullptr,
        ::asc::std::source_location __loc = ::asc::std::source_location::current(),
        __msg_storage __msg_buffer = {}) noexcept
        : ::std::runtime_error(::asc::__detail::__format_asc_error(__msg_buffer, __status, __msg, __api, __loc)),
          __status_(__status)
    {}

    [[nodiscard]] auto status() const noexcept -> __asc_error_t
    {
        return __status_;
    }

private:
    __asc_error_t __status_;
};
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#if CANN_ASC_STL_DETAIL_HOSTED()
#undef CANN_ASC_STL_DETAIL_HAS_ACL_ERROR_TYPE
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_EXCEPTION_ASC_ERROR_H
