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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BIND_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BIND_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/reference_wrapper.h>
#include <asc/std/__functional/weak_result_type.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/reference_wrapper.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/cstddef>
#include <asc/std/tuple>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct is_bind_expression
    : conditional_t<is_same<T, remove_cvref_t<T>>::value, false_type, is_bind_expression<remove_cvref_t<T>>> {};

template <class T>
inline constexpr int is_bind_expression_v = is_bind_expression<T>::value;

template <class T>
struct is_placeholder : conditional_t<is_same<T, remove_cvref_t<T>>::value, integral_constant<int, 0>,
                            is_placeholder<remove_cvref_t<T>>> {};

template <class T>
inline constexpr int is_placeholder_v = is_placeholder<T>::value;

namespace placeholders {

template <int N>
struct __ph {};

inline constexpr __ph<1> _1{};    // NOLINT(build/include_what_you_use)
inline constexpr __ph<2> _2{};    // NOLINT(build/include_what_you_use)
inline constexpr __ph<3> _3{};    // NOLINT(build/include_what_you_use)
inline constexpr __ph<4> _4{};    // NOLINT(build/include_what_you_use)
inline constexpr __ph<5> _5{};    // NOLINT(build/include_what_you_use)
inline constexpr __ph<6> _6{};    // NOLINT(build/include_what_you_use)
inline constexpr __ph<7> _7{};    // NOLINT(build/include_what_you_use)
inline constexpr __ph<8> _8{};    // NOLINT(build/include_what_you_use)
inline constexpr __ph<9> _9{};    // NOLINT(build/include_what_you_use)
inline constexpr __ph<10> _10{};  // NOLINT(build/include_what_you_use)

}  // namespace placeholders

template <int N>
struct is_placeholder<placeholders::__ph<N>> : public integral_constant<int, N> {};

namespace detail {

template <class T>
struct is_reference_wrapper : false_type {};
template <class T>
struct is_reference_wrapper<reference_wrapper<T>> : true_type {};

}  // namespace detail

template <class T, class U>
CANN_ASC_STL_API T& __mu(reference_wrapper<T> wrapper, U&)
{
    return wrapper.get();
}

template <class Ti, class... Uj, size_t... Indx>
CANN_ASC_STL_API invoke_result_t<Ti&, Uj...> __mu_expand(Ti& ti, tuple<Uj...>& uj, __tuple_indices<Indx...>)
{
    return ti(::asc::std::forward<Uj>(::asc::std::get<Indx>(uj))...);
}

template <class Ti, class... Uj>
CANN_ASC_STL_API enable_if_t<is_bind_expression<Ti>::value, invoke_result_t<Ti&, Uj...>> __mu(Ti& ti, tuple<Uj...>& uj)
{
    using Indices = __make_tuple_indices_t<sizeof...(Uj)>;
    return ::asc::std::__mu_expand(ti, uj, Indices());
}

template <bool IsPh, class Ti, class Uj>
struct __mu_return2 {};

template <class Ti, class Uj>
struct __mu_return2<true, Ti, Uj> {
    using type = tuple_element_t<is_placeholder<Ti>::value - 1, Uj>;
};

template <class Ti, class Uj>
CANN_ASC_STL_API
    enable_if_t<0 < is_placeholder<Ti>::value, typename __mu_return2<0 < is_placeholder<Ti>::value, Ti, Uj>::type>
    __mu(Ti&, Uj& uj)
{
    const int index = is_placeholder<Ti>::value - 1;
    return ::asc::std::forward<tuple_element_t<index, Uj>>(::asc::std::get<index>(uj));
}

template <class Ti, class Uj>
CANN_ASC_STL_API enable_if_t<!is_bind_expression<Ti>::value && is_placeholder<Ti>::value == 0 &&
        !detail::is_reference_wrapper<remove_cv_t<Ti>>::value,
    Ti&>
__mu(Ti& ti, Uj&)
{
    return ti;
}

template <class Ti, bool IsReferenceWrapper, bool IsBindEx, bool IsPh, class TupleUj>
struct __mu_return_impl;

template <class Ti, class... Uj>
struct __mu_return_impl<Ti, false, true, false, tuple<Uj...>> {
    using type = invoke_result_t<Ti&, Uj...>;
};

template <class Ti, class TupleUj>
struct __mu_return_impl<Ti, false, false, true, TupleUj> {
    using type = tuple_element_t<is_placeholder<Ti>::value - 1, TupleUj>&&;
};

template <class Ti, class TupleUj>
struct __mu_return_impl<Ti, true, false, false, TupleUj> {
    using type = typename Ti::type&;
};

template <class Ti, class TupleUj>
struct __mu_return_impl<Ti, false, false, false, TupleUj> {
    using type = Ti&;
};

template <class Ti, class TupleUj>
struct __mu_return
    : public __mu_return_impl<Ti, detail::is_reference_wrapper<remove_cv_t<Ti>>::value, is_bind_expression<Ti>::value,
          0 < is_placeholder<Ti>::value && is_placeholder<Ti>::value <= tuple_size<TupleUj>::value, TupleUj> {};

template <class Fp, class BoundArgs, class TupleUj>
struct __is_valid_bind_return {
    static const bool value = false;
};

template <class Fp, class... BoundArgs, class TupleUj>
struct __is_valid_bind_return<Fp, tuple<BoundArgs...>, TupleUj> {
    static const bool value = is_invocable_v<Fp, typename __mu_return<BoundArgs, TupleUj>::type...>;
};

template <class Fp, class... BoundArgs, class TupleUj>
struct __is_valid_bind_return<Fp, const tuple<BoundArgs...>, TupleUj> {
    static const bool value = is_invocable_v<Fp, typename __mu_return<const BoundArgs, TupleUj>::type...>;
};

template <class Fp, class BoundArgs, class TupleUj, bool = __is_valid_bind_return<Fp, BoundArgs, TupleUj>::value>
struct __bind_return;

template <class Fp, class... BoundArgs, class TupleUj>
struct __bind_return<Fp, tuple<BoundArgs...>, TupleUj, true> {
    using type = invoke_result_t<Fp&, typename __mu_return<BoundArgs, TupleUj>::type...>;
};

template <class Fp, class... BoundArgs, class TupleUj>
struct __bind_return<Fp, const tuple<BoundArgs...>, TupleUj, true> {
    using type = invoke_result_t<Fp&, typename __mu_return<const BoundArgs, TupleUj>::type...>;
};

template <class Fp, class BoundArgs, class TupleUj>
using __bind_return_t = typename __bind_return<Fp, BoundArgs, TupleUj>::type;

template <class Fp, class BoundArgs, size_t... Indx, class Args>
CANN_ASC_STL_API __bind_return_t<Fp, BoundArgs, Args> __apply_functor(
    Fp& f, BoundArgs& bound_args, __tuple_indices<Indx...>, Args&& args)
{
    return ::asc::std::__invoke(f, ::asc::std::__mu(::asc::std::get<Indx>(bound_args), args)...);
}

template <class Fp, class... BoundArgs>
class __bind : public __weak_result_type<decay_t<Fp>> {
protected:
    using Fd = decay_t<Fp>;
    using Td = tuple<decay_t<BoundArgs>...>;

private:
    Fd f_;
    Td bound_args_;

    using Indices = __make_tuple_indices_t<sizeof...(BoundArgs)>;

public:
    template <class Gp, class... BA,
        class = enable_if_t<is_constructible<Fd, Gp>::value && !is_same<remove_reference_t<Gp>, __bind>::value>>
    CANN_ASC_STL_API explicit constexpr __bind(Gp&& f, BA&&... bound_args)
        : f_(::asc::std::forward<Gp>(f)), bound_args_(::asc::std::forward<BA>(bound_args)...)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr __bind_return_t<Fd, Td, tuple<Args&&...>> operator()(Args&&... args)
    {
        return ::asc::std::__apply_functor(
            f_, bound_args_, Indices(), tuple<Args&&...>(::asc::std::forward<Args>(args)...));
    }

    template <class... Args>
    CANN_ASC_STL_API constexpr __bind_return_t<const Fd, const Td, tuple<Args&&...>> operator()(Args&&... args) const
    {
        return ::asc::std::__apply_functor(
            f_, bound_args_, Indices(), tuple<Args&&...>(::asc::std::forward<Args>(args)...));
    }
};

template <class Fp, class... BoundArgs>
struct is_bind_expression<__bind<Fp, BoundArgs...>> : public true_type {};

template <class Rp, class Fp, class... BoundArgs>
class __bind_r : public __bind<Fp, BoundArgs...> {
    using base = __bind<Fp, BoundArgs...>;
    using Fd = typename base::Fd;
    using Td = typename base::Td;

public:
    using result_type = Rp;

    template <class Gp, class... BA,
        class = enable_if_t<is_constructible<Fd, Gp>::value && !is_same<remove_reference_t<Gp>, __bind_r>::value>>
    CANN_ASC_STL_API explicit constexpr __bind_r(Gp&& f, BA&&... bound_args)
        : base(::asc::std::forward<Gp>(f), ::asc::std::forward<BA>(bound_args)...)
    {}

    template <class... Args>
    CANN_ASC_STL_API constexpr enable_if_t<
        is_convertible<__bind_return_t<Fd, Td, tuple<Args&&...>>, result_type>::value || is_void<Rp>::value,
        result_type>
    operator()(Args&&... args)
    {
        return ::asc::std::invoke_r<Rp>(static_cast<base&>(*this), ::asc::std::forward<Args>(args)...);
    }

    template <class... Args>
    CANN_ASC_STL_API constexpr enable_if_t<
        is_convertible<__bind_return_t<const Fd, const Td, tuple<Args&&...>>,  // NOLINT(build/include_what_you_use)
            result_type>::value ||
            is_void<Rp>::value,
        result_type>
    operator()(Args&&... args) const
    {
        return ::asc::std::invoke_r<Rp>(static_cast<base const&>(*this), ::asc::std::forward<Args>(args)...);
    }
};

template <class Rp, class Fp, class... BoundArgs>
struct is_bind_expression<__bind_r<Rp, Fp, BoundArgs...>> : public true_type {};

template <class Fp, class... BoundArgs>
CANN_ASC_STL_API constexpr __bind<Fp, BoundArgs...> bind(Fp&& f, BoundArgs&&... bound_args)
{
    using type = __bind<Fp, BoundArgs...>;
    return type(::asc::std::forward<Fp>(f),
        ::asc::std::forward<BoundArgs>(bound_args)...);  // NOLINT(build/include_what_you_use)
}

template <class Rp, class Fp, class... BoundArgs>
CANN_ASC_STL_API constexpr __bind_r<Rp, Fp, BoundArgs...> bind(Fp&& f, BoundArgs&&... bound_args)
{
    using type = __bind_r<Rp, Fp, BoundArgs...>;
    return type(::asc::std::forward<Fp>(f),
        ::asc::std::forward<BoundArgs>(bound_args)...);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_BIND_H
