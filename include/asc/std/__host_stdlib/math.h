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

#ifndef CANN_ASC_STL_STD_DETAIL_HOST_STDLIB_MATH_H
#define CANN_ASC_STL_STD_DETAIL_HOST_STDLIB_MATH_H

#include <asc/std/detail/__config>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <math.h>

// Standard C++ library comes with it's own <math.h> C++ compatible header. However, if the include paths are jumbled,
// it might happen that the original C <math.h> is found first. This is a problem because C headers define many of the
// math functions as macros which would change our definitions. So, we check whether any of the functions are defined
// as a macro to distinguish the C++ copatibility header from the C header.
#if defined(fabs) || defined(fmod) || defined(remainder) || defined(remquo) || defined(fma) || defined(fmax) ||     \
    defined(fmin) || defined(fdim) || defined(exp) || defined(exp2) || defined(expm1) || defined(log) ||            \
    defined(log10) || defined(log2) || defined(log1p) || defined(pow) || defined(sqrt) || defined(cbrt) ||          \
    defined(hypot) || defined(sin) || defined(cos) || defined(tan) || defined(asin) || defined(acos) ||             \
    defined(atan) || defined(atan2) || defined(sinh) || defined(cosh) || defined(tanh) || defined(asinh) ||         \
    defined(acosh) || defined(atanh) || defined(erf) || defined(erfc) || defined(tgamma) || defined(lgamma) ||      \
    defined(ceil) || defined(floor) || defined(trunc) || defined(round) || defined(lround) || defined(llround) ||   \
    defined(nearbyint) || defined(rint) || defined(lrint) || defined(llrint) || defined(frexp) || defined(ldexp) || \
    defined(scalbn) || defined(scalbln) || defined(ilogb) || defined(logb) || defined(nextafter) ||                 \
    defined(nexttoward) || defined(copysign) || defined(fpclassify) || defined(isfinite) || defined(isinf) ||       \
    defined(isnan) || defined(isnormal) || defined(signbit) || defined(isgreater) || defined(isgreaterequal) ||     \
    defined(isless) || defined(islessequal) || defined(islessgreater) || defined(isunordered)
#error "ASC-STL requires the C++ compatibility <math.h> header, not the C <math.h> header."
#endif  // math functions defined as macros

#endif  // CANN_ASC_STL_DETAIL_HOSTED()

// The host <math.h> is included via the hosted branch of this header, and the
// validation above checks that the C++ compatible <math.h> (not the C
// <math.h> with function macros) was found.

#endif  // CANN_ASC_STL_STD_DETAIL_HOST_STDLIB_MATH_H
