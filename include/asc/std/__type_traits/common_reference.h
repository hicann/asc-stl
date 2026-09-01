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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COMMON_REFERENCE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COMMON_REFERENCE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/copy_cv.h>
#include <asc/std/__type_traits/copy_cvref.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_scalar.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)
template <class _Tp>
_Tp __returns_exactly() noexcept;

template <class _Xp, class _Yp>
using __cond_res_if_right = decltype(false ? __returns_exactly<_Xp>() : __returns_exactly<_Yp>());

template <class _Tp, class _Up, class = void>
struct __cond_res_workaround {};

template <class _Tp, class _Up>
struct __cond_res_workaround<_Tp, _Up, void_t<__cond_res_if_right<_Tp, _Up>>> {
    using _RTp = remove_cvref_t<_Tp>;
    using type = conditional_t<is_same_v<_RTp, remove_cvref_t<_Up>> && (is_scalar_v<_RTp> || is_array_v<_RTp>) &&
            ((is_lvalue_reference_v<_Tp> && is_rvalue_reference_v<_Up>) ||
                (is_rvalue_reference_v<_Tp> && is_lvalue_reference_v<_Up>)),
        decay_t<__copy_cv_t<remove_reference_t<_Tp>, remove_reference_t<_Up>>>, __cond_res_if_right<_Tp, _Up>>;
};

template <class _Xp, class _Yp>
using __cond_res = typename __cond_res_workaround<_Xp, _Yp>::type;
#else
template <class _Xp, class _Yp>
using __cond_res = decltype(false ? ::asc::std::declval<_Xp (&)()>()() : ::asc::std::declval<_Yp (&)()>()());
#endif

template <class _Tp>
using __xref = __apply_cvref_fn<_Tp>;

template <class _Ap, class _Bp, class = void>
struct __common_ref;

template <class _Xp, class _Yp>
using __common_ref_t = typename __common_ref<_Xp, _Yp>::__type;

template <class _Xp, class _Yp>
using __cv_cond_res = __cond_res<__copy_cv_t<_Xp, _Yp>&, __copy_cv_t<_Yp, _Xp>&>;

template <class _Ap, class _Bp>
struct __common_ref<_Ap&, _Bp&, enable_if_t<is_reference_v<__cv_cond_res<_Ap, _Bp>>>> {
    using __type = __cv_cond_res<_Ap, _Bp>;
};

template <class _Xp, class _Yp>
using __common_ref_C = remove_reference_t<__common_ref_t<_Xp&, _Yp&>>&&;

template <class _Ap, class _Bp, class = void>
struct __common_ref_rr {};

template <class _Ap, class _Bp>
struct __common_ref_rr<_Ap&&, _Bp&&,
    enable_if_t<is_convertible_v<_Ap&&, __common_ref_C<_Ap, _Bp>> &&
        is_convertible_v<_Bp&&, __common_ref_C<_Ap, _Bp>>>> {
    using __type = __common_ref_C<_Ap, _Bp>;
};

template <class _Ap, class _Bp>
struct __common_ref<_Ap&&, _Bp&&> : __common_ref_rr<_Ap&&, _Bp&&> {};

template <class _Tp, class _Up>
using __common_ref_D = __common_ref_t<const _Tp&, _Up&>;

template <class _Ap, class _Bp, class = void>
struct __common_ref_lr {};

template <class _Ap, class _Bp>
struct __common_ref_lr<_Ap&&, _Bp&, enable_if_t<is_convertible_v<_Ap&&, __common_ref_D<_Ap, _Bp>>>> {
    using __type = __common_ref_D<_Ap, _Bp>;
};

template <class _Ap, class _Bp>
struct __common_ref<_Ap&&, _Bp&> : __common_ref_lr<_Ap&&, _Bp&> {};

template <class _Ap, class _Bp>
struct __common_ref<_Ap&, _Bp&&> : __common_ref_lr<_Bp&&, _Ap&> {};

template <class _Ap, class _Bp, class>
struct __common_ref {};

template <class...>
struct common_reference {};

template <class... _Types>
using common_reference_t = typename common_reference<_Types...>::type;

template <class, class, class = void>
inline constexpr bool __has_common_reference = false;

template <class _Tp, class _Up>
inline constexpr bool __has_common_reference<_Tp, _Up, void_t<common_reference_t<_Tp, _Up>>> = true;

template <>
struct common_reference<> {};

template <class _Tp>
struct common_reference<_Tp> {
    using type = _Tp;
};

template <class _Tp, class _Up, class = void>
struct __common_reference_sub_bullet3;

template <class _Tp, class _Up, class = void>
struct __common_reference_sub_bullet2 : __common_reference_sub_bullet3<_Tp, _Up> {};

template <class _Tp, class _Up, class = void>
struct __common_reference_sub_bullet1 : __common_reference_sub_bullet2<_Tp, _Up> {};

template <class _Tp, class _Up>
struct common_reference<_Tp, _Up> : __common_reference_sub_bullet1<_Tp, _Up> {};

template <class _Tp, class _Up>
struct __common_reference_sub_bullet1<_Tp, _Up,
    void_t<__common_ref_t<_Tp, _Up>, enable_if_t<is_reference_v<_Tp> && is_reference_v<_Up>>>> {
    using type = __common_ref_t<_Tp, _Up>;
};

template <class, class, template <class> class, template <class> class, class = void>
struct basic_common_reference {};

template <class _Tp, class _Up>
using __basic_common_reference_t = typename basic_common_reference<remove_cvref_t<_Tp>, remove_cvref_t<_Up>,
    __xref<_Tp>::template __call, __xref<_Up>::template __call>::type;

template <class _Tp, class _Up>
struct __common_reference_sub_bullet2<_Tp, _Up, void_t<__basic_common_reference_t<_Tp, _Up>>> {
    using type = __basic_common_reference_t<_Tp, _Up>;
};

template <class _Tp, class _Up>
struct __common_reference_sub_bullet3<_Tp, _Up, void_t<__cond_res<_Tp, _Up>>> {
    using type = __cond_res<_Tp, _Up>;
};

template <class _Tp, class _Up, class>
struct __common_reference_sub_bullet3 : common_type<_Tp, _Up> {};

template <class _Tp, class _Up, class _Vp, class _Enable, class... _Rest>
struct __common_reference_multi {};

template <class _Tp, class _Up, class _Vp, class... _Rest>
struct __common_reference_multi<_Tp, _Up, _Vp, void_t<common_reference_t<_Tp, _Up>>, _Rest...>
    : common_reference<common_reference_t<_Tp, _Up>, _Vp, _Rest...> {};

template <class _Tp, class _Up, class _Vp, class... _Rest>
struct common_reference<_Tp, _Up, _Vp, _Rest...> : __common_reference_multi<_Tp, _Up, _Vp, void, _Rest...> {};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COMMON_REFERENCE_H
