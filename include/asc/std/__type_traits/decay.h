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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DECAY_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DECAY_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/add_pointer.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_function.h>
#include <asc/std/__type_traits/is_referenceable.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_extent.h>
#include <asc/std/__type_traits/remove_reference.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Up, bool>
struct __decay_impl {
    using type = remove_cv_t<_Up>;
};

template <class _Up>
struct __decay_impl<_Up, true> {
    using type = conditional_t<is_array_v<_Up>, remove_extent_t<_Up>*,
        conditional_t<is_function_v<_Up>, add_pointer_t<_Up>, remove_cv_t<_Up>>>;
};

template <class _Tp>
struct decay {
private:
    using _Up = remove_reference_t<_Tp>;

public:
    using type = typename __decay_impl<_Up, __asc_is_referenceable<_Up>::value>::type;
};

template <class _Tp>
using decay_t = typename decay<_Tp>::type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DECAY_H
