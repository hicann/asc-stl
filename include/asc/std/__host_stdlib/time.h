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

#ifndef CANN_ASC_STL_STD_DETAIL_HOST_STDLIB_TIME_H
#define CANN_ASC_STL_STD_DETAIL_HOST_STDLIB_TIME_H

#include <asc/std/detail/__config>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <time.h>

// Standard C++ library comes with it's own <time.h> C++ compatible header. However, if the include paths are jumbled,
// it might happen that the original C <time.h> is found first. This is a problem because C headers define many of the
// time functions as macros which would change our definitions. So, we check whether any of the functions are defined
// as a macro to distinguish the C++ copatibility header from the C header.
#if defined(clock) || defined(difftime) || defined(mktime) || defined(time) || defined(asctime) || defined(ctime) || \
    defined(gmtime) || defined(localtime) || defined(strftime)
#error "ASC-STL requires the C++ compatibility <time.h> header, not the C <time.h> header."
#endif  // math functions defined as macros

#endif  // CANN_ASC_STL_DETAIL_HOSTED()

// The host <time.h> is included via the hosted branch of this header, and the
// validation above checks that the C++ compatible <time.h> (not the C
// <time.h> with function macros) was found.

#endif  // CANN_ASC_STL_STD_DETAIL_HOST_STDLIB_TIME_H
