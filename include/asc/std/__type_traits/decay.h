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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DECAY_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DECAY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_referenceable.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_extent.h>
#include <asc/std/__type_traits/remove_reference.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__decay)

template <class Tp>
struct decay {
    using type = __decay(Tp);
};

template <class Tp>
using decay_t = __decay(Tp);

#else

// The frozen decay::type contract spells the referenceable dispatch
// __asc_is_referenceable; it routes to the shared is_referenceable trait.
template <class Tp>
using __asc_is_referenceable = __is_referenceable<Tp>;

template <class Up, bool>
struct __decay_impl {
    using type = remove_cv_t<Up>;
};

template <class Up>
struct __decay_impl<Up, true> {
    using type = conditional_t<is_array_v<Up>, remove_extent_t<Up>*,
        conditional_t<is_function_v<Up>, add_pointer_t<Up>, remove_cv_t<Up> > >;
};

template <class Tp>
struct decay {
private:
    using Up = remove_reference_t<Tp>;

public:
    using type = typename __decay_impl<Up, __asc_is_referenceable<Up>::value>::type;
};

template <class Tp>
using decay_t = typename decay<Tp>::type;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DECAY_H
