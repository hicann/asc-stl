/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_EXCEPTION_EXCEPTION_MACROS_H
#define CANN_ASC_STL_STD_DETAIL_EXCEPTION_EXCEPTION_MACROS_H

#include <asc/std/detail/__config>

#include <asc/std/__exception/terminate.h>
#include <asc/std/__asc/exceptions.h>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <cstdio>
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

struct __asc_catch_any_lvalue {
    template <class _Tp>
    CANN_ASC_STL_API operator _Tp&() const noexcept;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

// The following macros are used to conditionally compile exception handling code. They
// are used in the same way as `try` and `catch`, but they allow for different behavior
// based on whether exceptions are enabled or not, and whether the code is being compiled
// for device or not.
//
// Usage: CANN_ASC_STL_DETAIL_ACCL_TRY / CANN_ASC_STL_DETAIL_ACCL_CATCH (variable) / CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL
// compose like try / catch (...).
//
// Notes:
//   - the catch clause must always bind to a named variable

// Expand to keywords only for host code when exceptions are enabled.
#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && CANN_ASC_STL_DETAIL_HOST_COMPILATION() && CANN_ASC_STL_DETAIL_HOSTED()
#define CANN_ASC_STL_DETAIL_ACCL_TRY try
#define CANN_ASC_STL_DETAIL_ACCL_CATCH catch
#define CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL catch (...)
#define CANN_ASC_STL_DETAIL_ACCL_CATCH_FALLTHROUGH

#define CANN_ASC_STL_DETAIL_ACCL_THROW(_TYPE, ...) \
    do {                                           \
        throw _TYPE(__VA_ARGS__);                  \
    } while (0)
#define CANN_ASC_STL_DETAIL_ACCL_RETHROW throw
#else  // ^^^ use exceptions ^^^ / vvv no exceptions vvv
#define CANN_ASC_STL_DETAIL_ACCL_TRY if constexpr (true) {
#define CANN_ASC_STL_DETAIL_ACCL_CATCH(...)                    \
    }                                                          \
    else if constexpr (false) /* NOLINT(readability/braces) */ \
    {                         /* NOLINT(whitespace/braces) */  \
        for (__VA_ARGS__ = ::asc::std::__asc_catch_any_lvalue{}; false;)
#define CANN_ASC_STL_DETAIL_ACCL_CATCH_ALL \
    }                                      \
    else  // NOLINT(readability/braces)
#define CANN_ASC_STL_DETAIL_ACCL_CATCH_FALLTHROUGH \
    }                                              \
    else /* NOLINT(readability/braces) */          \
    {    /* NOLINT(whitespace/braces) */           \
    }

#if CANN_ASC_STL_DETAIL_HOST_COMPILATION() && CANN_ASC_STL_DETAIL_HOSTED()
#define CANN_ASC_STL_DETAIL_ACCL_THROW(_TYPE, ...)                                                               \
    do {                                                                                                         \
        ::fprintf(stderr, "%s:%u: An instance of class %s would be thrown.\n  what():  %s\nAborted\n", __FILE__, \
            __LINE__, #_TYPE, (_TYPE(__VA_ARGS__)).what());                                                      \
        ::fflush(stderr);                                                                                        \
        ::asc::std::terminate();                                                                                 \
    } while (0)
#else  // ^^^ hosted Host ^^^ / vvv freestanding or Device vvv
#define CANN_ASC_STL_DETAIL_ACCL_THROW(_TYPE, ...)                                             \
    do {                                                                                       \
        CANN_ASC_STL_DETAIL_ASSERT(false, "An instance of class " #_TYPE " would be thrown."); \
        ::asc::std::terminate();                                                               \
    } while (0)
#endif  // freestanding or Device
#define CANN_ASC_STL_DETAIL_ACCL_RETHROW ::asc::std::terminate()
#endif  // ^^^ no exceptions ^^^

#endif  // CANN_ASC_STL_STD_DETAIL_EXCEPTION_EXCEPTION_MACROS_H
