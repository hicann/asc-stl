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

#ifndef CANN_ASC_STL_DETAIL_FUNCTIONAL_ADDRESS_STABILITY_H
#define CANN_ASC_STL_DETAIL_FUNCTIONAL_ADDRESS_STABILITY_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__functional/always_true_false.h>
#include <asc/__fwd/iterator.h>
#include <asc/std/__functional/not_fn.h>
#include <asc/std/__functional/operations.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__utility/move.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

//! Trait telling whether a function object type F does not rely on the memory addresses of its arguments. The nested
//! value is true when the addresses of the arguments do not matter and arguments can be provided from arbitrary copies
//! of the respective sources. This trait can be specialized for custom function objects types.
//! @see proclaim_copyable_arguments
template <typename F, typename SFINAE = void>
struct proclaims_copyable_arguments : ::asc::std::false_type {};

template <typename F, typename... Args>
inline constexpr bool proclaims_copyable_arguments_v = proclaims_copyable_arguments<F, Args...>::value;

// Wrapper for a callable to mark it as permitting copied arguments
template <typename F>
struct __callable_permitting_copied_arguments : F {
    using F::operator();
};

template <typename F>
struct proclaims_copyable_arguments<__callable_permitting_copied_arguments<F>> : ::asc::std::true_type {};

//! Creates a new function object from an existing one, which is marked as permitting its arguments to be copies of
//! whatever source they come from. This implies that the addresses of the arguments are irrelevant to the function
//! object. Some algorithms, like thrust::transform, can benefit from this information and choose a more efficient
//! implementation.
//! @see proclaims_copyable_arguments
template <typename F>
[[nodiscard]] CANN_ASC_STL_API constexpr auto proclaim_copyable_arguments(F&& f)
{
    if constexpr (proclaims_copyable_arguments<F>::value) {  // If F is already marked then we do not need to wrap it
        return f;
    } else {
        return __callable_permitting_copied_arguments<::asc::std::decay_t<F>>{
            ::asc::std::forward<F>(f)};  // NOLINT(build/include_what_you_use)
    }
}

// Specializations for ASC-STL function objects are provided here to avoid pulling this include into `<asc/std/...>`
// headers.

template <typename _Fn>
struct proclaims_copyable_arguments<::asc::std::__not_fn_t<_Fn>> : proclaims_copyable_arguments<_Fn> {};

template <typename _Fn>
struct proclaims_copyable_arguments<zip_function<_Fn>> : proclaims_copyable_arguments<_Fn> {};

template <typename _Tp>
struct __has_builtin_operators : ::asc::std::bool_constant<!::asc::std::is_class_v<_Tp> &&
                                     !::asc::std::is_enum_v<_Tp> && !::asc::std::is_void_v<_Tp>> {};

#define CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(functor)                               \
    /*we know what plus<T> etc. does if T is not a type that could have a weird operatorX() */  \
    template <typename _Tp>                                                                     \
    struct proclaims_copyable_arguments<functor<_Tp>> : ::asc::__has_builtin_operators<_Tp> {}; \
    /*we do not know what plus<void> etc. does, which depends on the types it is invoked on */  \
    template <>                                                                                 \
    struct proclaims_copyable_arguments<functor<void>> : ::asc::std::false_type {};

CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::plus)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::minus)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::multiplies)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::divides)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::modulus)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::negate)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::bit_and)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::bit_not)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::bit_or)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::bit_xor)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::equal_to)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::not_equal_to)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::less)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::less_equal)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::greater_equal)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::greater)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::logical_and)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::logical_not)
CANN_ASC_STL_DETAIL_ACCL_MARK_CAN_COPY_ARGUMENTS(::asc::std::logical_or)

#define CANN_ASC_STL_DETAIL_ACCL_MARK_RANGE_FUNCTOR_CAN_COPY_ARGUMENTS(functor)                                   \
    /*we do not know what equal_to etc. does, which depends on the types and their operator== it is invoked on */ \
    template <>                                                                                                   \
    struct proclaims_copyable_arguments<functor> : ::asc::std::false_type {};

CANN_ASC_STL_DETAIL_ACCL_MARK_RANGE_FUNCTOR_CAN_COPY_ARGUMENTS(::asc::std::ranges::equal_to)
CANN_ASC_STL_DETAIL_ACCL_MARK_RANGE_FUNCTOR_CAN_COPY_ARGUMENTS(::asc::std::ranges::not_equal_to)
CANN_ASC_STL_DETAIL_ACCL_MARK_RANGE_FUNCTOR_CAN_COPY_ARGUMENTS(::asc::std::ranges::less)
CANN_ASC_STL_DETAIL_ACCL_MARK_RANGE_FUNCTOR_CAN_COPY_ARGUMENTS(::asc::std::ranges::less_equal)
CANN_ASC_STL_DETAIL_ACCL_MARK_RANGE_FUNCTOR_CAN_COPY_ARGUMENTS(::asc::std::ranges::greater)
CANN_ASC_STL_DETAIL_ACCL_MARK_RANGE_FUNCTOR_CAN_COPY_ARGUMENTS(::asc::std::ranges::greater_equal)

#undef CANN_ASC_STL_DETAIL_ACCL_MARK_RANGE_FUNCTOR_CAN_COPY_ARGUMENTS

// always_true and always_false never inspect the addresses of their arguments
template <>
struct proclaims_copyable_arguments<::asc::always_true> : ::asc::std::true_type {};
template <>
struct proclaims_copyable_arguments<::asc::always_false> : ::asc::std::true_type {};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC
#endif  // CANN_ASC_STL_DETAIL_FUNCTIONAL_ADDRESS_STABILITY_H
