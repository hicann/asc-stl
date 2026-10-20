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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_COMMON_ITERATOR_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_COMMON_ITERATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__fwd/common_iterator.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iter_swap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__iterator/variant_like.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __common_iterator_detail {

// SFINAE-friendly probes shared by every compilation mode.
template <class Iter, class = void>
inline constexpr bool __ci_has_const_arrow_op = false;

template <class Iter>
inline constexpr bool __ci_has_const_arrow_op<Iter, void_t<decltype(::asc::std::declval<const Iter&>().operator->())>> =
    true;

template <class Iter>
inline constexpr bool __ci_has_const_arrow = is_pointer_v<Iter> || __ci_has_const_arrow_op<Iter>;

template <class Iter, class = void>
struct __ci_readable_value_ref : false_type {};

template <class Iter>
struct __ci_readable_value_ref<Iter, void_t<::asc::std::iter_value_t<Iter>, ::asc::std::iter_reference_t<Iter>>>
    : true_type {};

template <class Iter, class = void>
inline constexpr bool __ci_input_probe = false;

template <class Iter>
inline constexpr bool __ci_input_probe<Iter, void_t<typename iterator_traits<Iter>::iterator_category>> =
    is_convertible_v<typename iterator_traits<Iter>::iterator_category, input_iterator_tag>;

template <class Iter, class = void>
inline constexpr bool __ci_input_concept_probe = false;

template <class Iter>
inline constexpr bool __ci_input_concept_probe<Iter, void_t<typename Iter::iterator_concept>> =
    is_convertible_v<typename Iter::iterator_concept, input_iterator_tag>;

template <class Iter, class = void>
inline constexpr bool __ci_fwd_probe = false;

template <class Iter>
inline constexpr bool __ci_fwd_probe<Iter, void_t<typename iterator_traits<Iter>::iterator_category>> =
    is_convertible_v<typename iterator_traits<Iter>::iterator_category, forward_iterator_tag>;

template <class Iter, class = void>
inline constexpr bool __ci_fwd_concept_probe = false;

template <class Iter>
inline constexpr bool __ci_fwd_concept_probe<Iter, void_t<typename Iter::iterator_concept>> =
    is_convertible_v<typename Iter::iterator_concept, forward_iterator_tag>;

template <class Iter>
inline constexpr bool __ci_has_fwd_category = __ci_fwd_probe<Iter> || __ci_fwd_concept_probe<Iter>;

// `A - B` is valid and convertible to `D`; the SFINAE analogue of the
// subtractability implied by sized_sentinel_for.
template <class A, class B, class D, class = void>
inline constexpr bool __ci_diff_convertible = false;

template <class A, class B, class D>
inline constexpr bool __ci_diff_convertible<A, B, D,
    void_t<decltype(::asc::std::declval<const A&>() - ::asc::std::declval<const B&>())>> =
    is_convertible_v<decltype(::asc::std::declval<const A&>() - ::asc::std::declval<const B&>()), D>;

// The pointer member of iterator_traits<common_iterator>: mirrors the
// three-way operator-> (const arrow / address-of-reference / value proxy).
template <class CommonIter, class Iter>
struct __ci_pointer_of {
private:
    static CANN_ASC_STL_API constexpr auto __select()
    {
        if constexpr (__ci_has_const_arrow<Iter>) {
            return static_cast<Iter*>(nullptr);
        } else if constexpr (__ci_readable_value_ref<Iter>::value) {
            using Ref = ::asc::std::iter_reference_t<Iter>;
            using Val = ::asc::std::iter_value_t<Iter>;
            if constexpr (is_reference_v<Ref>) {
                return static_cast<remove_reference_t<Ref>**>(nullptr);
            } else if constexpr (is_constructible_v<Val, Ref>) {
                return static_cast<const typename CommonIter::__proxy**>(nullptr);
            } else {
                return static_cast<void*>(nullptr);
            }
        } else {
            return static_cast<void*>(nullptr);
        }
    }

public:
    using type = remove_pointer_t<decltype(__select())>;
};

}  // namespace __common_iterator_detail

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class Iter>
concept __postfix_can_reference = requires(Iter& it) { requires __can_reference<decltype(*it++)>; };

template <class Iter>
concept __use_postfix_proxy = !__postfix_can_reference<Iter> && indirectly_readable<Iter> &&
    constructible_from<iter_value_t<Iter>, iter_reference_t<Iter>> && is_move_constructible_v<iter_value_t<Iter>>;

template <class Iter>
concept __ci_forward_iterator = forward_iterator<Iter>;

template <class Iter>
concept __ci_is_input_iterator = input_iterator<Iter>;

template <class A, class B>
concept __ci_eq_comparable = equality_comparable_with<A, B>;

#else  // !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())

template <class Iter, class = void>
inline constexpr bool __postfix_can_reference = false;

template <class Iter>
inline constexpr bool __postfix_can_reference<Iter, void_t<decltype(*::asc::std::declval<Iter&>()++)>> =
    !is_void_v<decltype(*::asc::std::declval<Iter&>()++)>;

template <class Iter, class = void>
struct __ci_use_postfix_proxy_impl : false_type {};

template <class Iter>
struct __ci_use_postfix_proxy_impl<Iter,
    enable_if_t<!__postfix_can_reference<Iter> && indirectly_readable<Iter> &&
        is_constructible_v<iter_value_t<Iter>, iter_reference_t<Iter>> && is_move_constructible_v<iter_value_t<Iter>>>>
    : true_type {};

template <class Iter>
inline constexpr bool __use_postfix_proxy = __ci_use_postfix_proxy_impl<Iter>::value;

template <class Iter>
inline constexpr bool __ci_forward_iterator = forward_iterator<Iter>;

template <class Iter>
inline constexpr bool __ci_is_input_iterator = input_iterator<Iter>;

template <class A, class B>
inline constexpr bool __ci_eq_comparable = equality_comparable_with<A, B>;

#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator Iter, sentinel_for<Iter> Sent>
    requires(!same_as<Iter, Sent> && copyable<Iter>)
#else
template <class Iter, class Sent, class Enable>
#endif
class common_iterator {
public:
    // These should be private but older compilers complain about implicitly
    // naming private types in decltype or auto expressions.
    struct __proxy {
        iter_value_t<Iter> value_;

        CANN_ASC_STL_API constexpr const iter_value_t<Iter>* operator->() const noexcept
        {
            return ::asc::std::addressof(value_);
        }
    };

    struct __postfix_proxy {
        iter_value_t<Iter> value_;

        CANN_ASC_STL_API constexpr const iter_value_t<Iter>& operator*() const noexcept
        {
            return value_;
        }
    };

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    CANN_ASC_STL_API constexpr common_iterator() noexcept(is_nothrow_default_constructible_v<Iter>)
        requires default_initializable<Iter>
    = default;
#else
    template <class I2 = Iter, enable_if_t<default_initializable<I2>, int> = 0>
    CANN_ASC_STL_API constexpr common_iterator() noexcept(is_nothrow_default_constructible_v<Iter>)
    {}
#endif

    CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator(const common_iterator&) = default;
    CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator& operator=(const common_iterator&) = default;
    CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator(common_iterator&&) = default;
    CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator& operator=(common_iterator&&) = default;

    CANN_ASC_STL_API constexpr common_iterator(Iter value) noexcept(is_nothrow_move_constructible_v<Iter>)
        : hold_(__construct_first{}, ::asc::std::move(value))
    {}
    CANN_ASC_STL_API constexpr common_iterator(Sent value) noexcept(is_nothrow_move_constructible_v<Sent>)
        : hold_(__construct_second{}, ::asc::std::move(value))  // NOLINT(build/include_what_you_use)
    {}
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class I2, class S2>
        requires(convertible_to<const I2&, Iter> && convertible_to<const S2&, Sent>)
    CANN_ASC_STL_API constexpr common_iterator(const common_iterator<I2, S2>& other) noexcept(
        is_nothrow_constructible_v<Iter, const I2&> && is_nothrow_constructible_v<Sent, const S2&>)
        : hold_(other.__get_hold())
    {}
#else
    template <class I2, class S2,
        enable_if_t<convertible_to<const I2&, Iter> && convertible_to<const S2&, Sent>, int> = 0>
    CANN_ASC_STL_API constexpr common_iterator(const common_iterator<I2, S2>& other) noexcept(
        is_nothrow_constructible_v<Iter, const I2&> && is_nothrow_constructible_v<Sent, const S2&>)
        : hold_(other.__get_hold())
    {}
#endif
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class I2, class S2>
        requires(convertible_to<const I2&, Iter> && convertible_to<const S2&, Sent> &&
            assignable_from<Iter&, const I2&> && assignable_from<Sent&, const S2&>)
    CANN_ASC_STL_API constexpr common_iterator& operator=(const common_iterator<I2, S2>& other)
    {
        hold_ = other.__get_hold();
        return *this;
    }
#else
    template <class I2, class S2,
        enable_if_t<convertible_to<const I2&, Iter> && convertible_to<const S2&, Sent> &&
                assignable_from<Iter&, const I2&> && assignable_from<Sent&, const S2&>,
            int> = 0>
    CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator& operator=(
        const common_iterator<I2, S2>& other)
    {
        hold_ = other.__get_hold();
        return *this;
    }
#endif

    CANN_ASC_STL_API constexpr decltype(auto) operator*()
    {
        return *hold_.__first_;
    }
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class I2 = Iter>
        requires requires { *::asc::std::declval<const I2&>(); }
    CANN_ASC_STL_API constexpr decltype(auto) operator*() const
    {
        return *hold_.__first_;
    }
#else
    template <class I2 = Iter, class = decltype(*::asc::std::declval<const I2&>())>
    CANN_ASC_STL_API constexpr decltype(auto) operator*() const
    {
        return *hold_.__first_;
    }
#endif
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class I2 = Iter>
        requires(indirectly_readable<const I2> &&
            (__common_iterator_detail::__ci_has_const_arrow<I2> || is_reference_v<iter_reference_t<I2>> ||
                constructible_from<iter_value_t<I2>, iter_reference_t<I2>>))
    CANN_ASC_STL_API constexpr decltype(auto) operator->() const
#else
    template <class I2 = Iter,
        enable_if_t<indirectly_readable<const I2> &&
                (__common_iterator_detail::__ci_has_const_arrow<I2> || is_reference_v<iter_reference_t<I2>> ||
                    constructible_from<iter_value_t<I2>, iter_reference_t<I2>>),
            int> = 0>
    CANN_ASC_STL_API constexpr decltype(auto) operator->() const
#endif
    {
        if constexpr (__common_iterator_detail::__ci_has_const_arrow<I2>) {
            return static_cast<const I2&>(hold_.__first_);
        } else if constexpr (is_reference_v<iter_reference_t<I2>>) {
            auto&& tmp = *hold_.__first_;
            return ::asc::std::addressof(tmp);
        } else {
            return __proxy{*hold_.__first_};
        }
    }
    CANN_ASC_STL_API constexpr common_iterator& operator++()
    {
        ++hold_.__first_;
        return *this;
    }
    CANN_ASC_STL_API constexpr decltype(auto) operator++(int)
    {
        if constexpr (__ci_forward_iterator<Iter>) {
            common_iterator tmp(*this);
            ++*this;
            return tmp;
        } else if constexpr (__use_postfix_proxy<Iter>) {
            auto p = __postfix_proxy{**this};
            ++*this;
            return p;
        } else {
            return hold_.__first_++;
        }
    }

    CANN_ASC_STL_API constexpr const __variant_like<Iter, Sent>& __get_hold() const noexcept
    {
        return hold_;
    }
    CANN_ASC_STL_API constexpr __variant_like<Iter, Sent>& __get_hold() noexcept
    {
        return hold_;
    }

private:
    __variant_like<Iter, Sent> hold_;
};

template <class I1, class S1, class I2, class S2>
CANN_ASC_STL_API constexpr bool operator==(const common_iterator<I1, S1>& left, const common_iterator<I2, S2>& right)
{
    const auto& lhs = left.__get_hold();
    const auto& rhs = right.__get_hold();
    if constexpr (__ci_eq_comparable<I1, I2>) {
        if (lhs.__holds_second() && rhs.__holds_second()) {
            return true;
        }
        if (lhs.__holds_first() && rhs.__holds_first()) {
            return lhs.__first_ == rhs.__first_;
        }
        if (lhs.__holds_first()) {
            return lhs.__first_ == rhs.__second_;
        }
        return lhs.__second_ == rhs.__first_;
    } else {
        if (lhs.__contains_ == rhs.__contains_) {
            return true;
        }
        if (lhs.__holds_first()) {
            return lhs.__first_ == rhs.__second_;
        }
        return lhs.__second_ == rhs.__first_;
    }
}
template <class I1, class S1, class I2, class S2>
CANN_ASC_STL_API constexpr bool operator!=(const common_iterator<I1, S1>& left, const common_iterator<I2, S2>& right)
{
    return !(left == right);
}

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class I1, class S1, class I2, class S2>
    requires(sized_sentinel_for<I2, I1> && sized_sentinel_for<S2, I1> && sized_sentinel_for<S1, I2>)
CANN_ASC_STL_API constexpr iter_difference_t<I2> operator-(
    const common_iterator<I1, S1>& left, const common_iterator<I2, S2>& right)
{
    const auto& lhs = left.__get_hold();
    const auto& rhs = right.__get_hold();
    if (lhs.__holds_second() && rhs.__holds_second()) {
        return 0;
    }
    if (lhs.__holds_first() && rhs.__holds_first()) {
        return lhs.__first_ - rhs.__first_;
    }
    if (lhs.__holds_first()) {
        return lhs.__first_ - rhs.__second_;
    }
    return lhs.__second_ - rhs.__first_;
}
#else
template <class I1, class S1, class I2, class S2,
    enable_if_t<sized_sentinel_for<I2, I1> && sized_sentinel_for<S2, I1> && sized_sentinel_for<S1, I2>, int> = 0>
CANN_ASC_STL_API constexpr auto operator-(
    const common_iterator<I1, S1>& left, const common_iterator<I2, S2>& right) -> ::asc::std::iter_difference_t<I2>
{
    const auto& lhs = left.__get_hold();
    const auto& rhs = right.__get_hold();
    if (lhs.__holds_second() && rhs.__holds_second()) {
        return 0;
    }
    if (lhs.__holds_first() && rhs.__holds_first()) {
        return lhs.__first_ - rhs.__first_;
    }
    if (lhs.__holds_first()) {
        return lhs.__first_ - rhs.__second_;
    }
    return lhs.__second_ - rhs.__first_;
}
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

// Note: a hidden-friend iter_move cannot be declared here:
// asc::std::iter_move is a customization-point object (a namespace-scope
// variable), and a same-named friend function in an asc::std class is
// ill-formed ("redeclared as a different kind of entity"). The equivalent
// behavior is provided by the customization point itself: iter_move(ci)
// dispatches to move(*ci), which yields the moved element.
// iter_swap keeps full underlying-element semantics through the
// namespace-scope overload below (overloading the function template is
// legal, unlike the iter_move variable case).

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class Iter, class Sent, class I2, class S2>
    requires indirectly_swappable<I2, Iter>
CANN_ASC_STL_API constexpr void
iter_swap(const common_iterator<Iter, Sent>& left, const common_iterator<I2, S2>& right) noexcept(
    noexcept(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(
        ::asc::std::declval<const Iter&>(), ::asc::std::declval<const I2&>())))
{
    return ::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.__get_hold().__first_, right.__get_hold().__first_);
}
#else
template <class Iter, class Sent, class I2, class S2, enable_if_t<indirectly_swappable<I2, Iter>, int> = 0>
CANN_ASC_STL_API constexpr void
iter_swap(const common_iterator<Iter, Sent>& left, const common_iterator<I2, S2>& right) noexcept(
    noexcept(::asc::std::ranges::__iter_swap::__iter_swap_fn{}(
        ::asc::std::declval<const Iter&>(), ::asc::std::declval<const I2&>())))
{
    return ::asc::std::ranges::__iter_swap::__iter_swap_fn{}(left.__get_hold().__first_, right.__get_hold().__first_);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class Iter, class Sent>
struct incrementable_traits<common_iterator<Iter, Sent>> {
    using difference_type = iter_difference_t<Iter>;
};

template <class Iter, class Sent>
struct iterator_traits<common_iterator<Iter, Sent>, enable_if_t<__ci_is_input_iterator<Iter>>> {
    using iterator_concept = conditional_t<__ci_forward_iterator<Iter>, forward_iterator_tag, input_iterator_tag>;
    using iterator_category =
        conditional_t<__common_iterator_detail::__ci_has_fwd_category<Iter>, forward_iterator_tag, input_iterator_tag>;
    using pointer = typename __common_iterator_detail::__ci_pointer_of<common_iterator<Iter, Sent>, Iter>::type;
    using value_type = iter_value_t<Iter>;
    using difference_type = iter_difference_t<Iter>;
    using reference = iter_reference_t<Iter>;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_COMMON_ITERATOR_H
