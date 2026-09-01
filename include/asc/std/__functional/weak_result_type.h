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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_WEAK_RESULT_TYPE_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_WEAK_RESULT_TYPE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/binary_function.h>
#include <asc/std/__functional/unary_function.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp, class = void>
inline constexpr bool __has_member_result_type = false;

template <class _Tp>
inline constexpr bool __has_member_result_type<_Tp, void_t<typename _Tp::result_type>> = true;

template <class _Tp>
struct __derives_from_unary_function {
private:
    struct __two {
        char __lx;
        char __lxx;
    };

    // These declarations participate only in unevaluated overload resolution.
    // Giving the ellipsis overload a device-call attribute is invalid in BiSheng.
    static __two __test(...);
    template <class _Ap, class _Rp>
    static __unary_function<_Ap, _Rp> __test(const volatile __unary_function<_Ap, _Rp>*);

public:
    // NOLINTNEXTLINE(readability/casting)
    static const bool value = !is_same_v<decltype(__test((_Tp*)nullptr)), __two>;
    // NOLINTNEXTLINE(readability/casting)
    using type = decltype(__test((_Tp*)nullptr));
};

template <class _Tp>
struct __derives_from_binary_function {
private:
    struct __two {
        char __lx;
        char __lxx;
    };

    static __two __test(...);
    template <class _A1, class _A2, class _Rp>
    static __binary_function<_A1, _A2, _Rp> __test(const volatile __binary_function<_A1, _A2, _Rp>*);

public:
    // NOLINTNEXTLINE(readability/casting)
    static const bool value = !is_same_v<decltype(__test((_Tp*)nullptr)), __two>;
    // NOLINTNEXTLINE(readability/casting)
    using type = decltype(__test((_Tp*)nullptr));
};

template <class _Tp, bool = __derives_from_unary_function<_Tp>::value>
struct __maybe_derive_from_unary_function : public __derives_from_unary_function<_Tp>::type {};

template <class _Tp>
struct __maybe_derive_from_unary_function<_Tp, false> {};

template <class _Tp, bool = __derives_from_binary_function<_Tp>::value>
struct __maybe_derive_from_binary_function : public __derives_from_binary_function<_Tp>::type {};

template <class _Tp>
struct __maybe_derive_from_binary_function<_Tp, false> {};

template <class _Tp, bool = __has_member_result_type<_Tp>>
struct __weak_result_type_imp : public __maybe_derive_from_unary_function<_Tp>,
                                public __maybe_derive_from_binary_function<_Tp> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = typename _Tp::result_type;
#endif
};

template <class _Tp>
struct __weak_result_type_imp<_Tp, false> : public __maybe_derive_from_unary_function<_Tp>,
                                            public __maybe_derive_from_binary_function<_Tp> {};

template <class _Tp>
struct __weak_result_type : public __weak_result_type_imp<_Tp> {};

template <class _Rp>
struct __weak_result_type<_Rp()> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

template <class _Rp>
struct __weak_result_type<_Rp (&)()> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

template <class _Rp>
struct __weak_result_type<_Rp (*)()> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

template <class _Rp, class _A1>
struct __weak_result_type<_Rp(_A1)> : public __unary_function<_A1, _Rp> {};

template <class _Rp, class _A1>
struct __weak_result_type<_Rp (&)(_A1)> : public __unary_function<_A1, _Rp> {};

template <class _Rp, class _A1>
struct __weak_result_type<_Rp (*)(_A1)> : public __unary_function<_A1, _Rp> {};

template <class _Rp, class _Cp>
struct __weak_result_type<_Rp (_Cp::*)()> : public __unary_function<_Cp*, _Rp> {};

template <class _Rp, class _Cp>
struct __weak_result_type<_Rp (_Cp::*)() const> : public __unary_function<const _Cp*, _Rp> {};

template <class _Rp, class _Cp>
struct __weak_result_type<_Rp (_Cp::*)() volatile> : public __unary_function<volatile _Cp*, _Rp> {};

template <class _Rp, class _Cp>
struct __weak_result_type<_Rp (_Cp::*)() const volatile> : public __unary_function<const volatile _Cp*, _Rp> {};

template <class _Rp, class _A1, class _A2>
struct __weak_result_type<_Rp(_A1, _A2)> : public __binary_function<_A1, _A2, _Rp> {};

template <class _Rp, class _A1, class _A2>
struct __weak_result_type<_Rp (*)(_A1, _A2)> : public __binary_function<_A1, _A2, _Rp> {};

template <class _Rp, class _A1, class _A2>
struct __weak_result_type<_Rp (&)(_A1, _A2)> : public __binary_function<_A1, _A2, _Rp> {};

template <class _Rp, class _Cp, class _A1>
struct __weak_result_type<_Rp (_Cp::*)(_A1)> : public __binary_function<_Cp*, _A1, _Rp> {};

template <class _Rp, class _Cp, class _A1>
struct __weak_result_type<_Rp (_Cp::*)(_A1) const> : public __binary_function<const _Cp*, _A1, _Rp> {};

template <class _Rp, class _Cp, class _A1>
struct __weak_result_type<_Rp (_Cp::*)(_A1) volatile> : public __binary_function<volatile _Cp*, _A1, _Rp> {};

template <class _Rp, class _Cp, class _A1>
struct __weak_result_type<_Rp (_Cp::*)(_A1) const volatile> : public __binary_function<const volatile _Cp*, _A1, _Rp> {
};

template <class _Rp, class _A1, class _A2, class _A3, class... _A4>
struct __weak_result_type<_Rp(_A1, _A2, _A3, _A4...)> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

template <class _Rp, class _A1, class _A2, class _A3, class... _A4>
struct __weak_result_type<_Rp (&)(_A1, _A2, _A3, _A4...)> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

template <class _Rp, class _A1, class _A2, class _A3, class... _A4>
struct __weak_result_type<_Rp (*)(_A1, _A2, _A3, _A4...)> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

template <class _Rp, class _Cp, class _A1, class _A2, class... _A3>
struct __weak_result_type<_Rp (_Cp::*)(_A1, _A2, _A3...)> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

template <class _Rp, class _Cp, class _A1, class _A2, class... _A3>
struct __weak_result_type<_Rp (_Cp::*)(_A1, _A2, _A3...) const> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

template <class _Rp, class _Cp, class _A1, class _A2, class... _A3>
struct __weak_result_type<_Rp (_Cp::*)(_A1, _A2, _A3...) volatile> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

template <class _Rp, class _Cp, class _A1, class _A2, class... _A3>
struct __weak_result_type<_Rp (_Cp::*)(_A1, _A2, _A3...) const volatile> {
#if CANN_ASC_STL_DETAIL_STD_VER <= 2017 || defined(CANN_ASC_STL_DETAIL_ENABLE_CXX20_REMOVED_BINDER_TYPEDEFS)
    using result_type ASC_DEPRECATED = _Rp;
#endif
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_WEAK_RESULT_TYPE_H
