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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_CONCEPT_MACROS_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_CONCEPT_MACROS_H

#include <asc/std/detail/__config>

////////////////////////////////////////////////////////////////////////////////
// CANN_ASC_STL_DETAIL_ACCL_TEMPLATE
// Usage:
//   CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(typename A, typename _Bp)
//     CANN_ASC_STL_DETAIL_ACCL_REQUIRES( Concept1<A> CANN_ASC_STL_DETAIL_ACCL_AND Concept2<_Bp>)
//   void foo(A a, _Bp b)
//   {}

// Barebones enable if implementation to use outside of asc::std
template <bool>
struct __asc_select {};

template <>
struct __asc_select<true> {
    template <class _Tp>
    using type = _Tp;
};

template <bool _Bp, class _Tp = void>
using __asc_enable_if_t = typename __asc_select<_Bp>::template type<_Tp>;

template <class _Tp, bool _Bp>
using __asc_requires_t = typename __asc_select<_Bp>::template type<_Tp>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
#define CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(...) template <__VA_ARGS__>
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES(...) requires __VA_ARGS__
#define CANN_ASC_STL_DETAIL_ACCL_AND &&
#define CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES_IMPL_(...) requires __VA_ARGS__
#define CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES(...) ->__VA_ARGS__ CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES_IMPL_
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT concept
#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
#define CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(...) template <__VA_ARGS__
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES(...) \
    , bool __asc_true_ = true, __asc_enable_if_t < __VA_ARGS__ && __asc_true_, int > = 0 >
#define CANN_ASC_STL_DETAIL_ACCL_AND &&__asc_true_, int > = 0, __asc_enable_if_t <
#define CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES(...) \
    ->__asc_requires_t < __VA_ARGS__ CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES_IMPL_
#define CANN_ASC_STL_DETAIL_ACCL_TRAILING_REQUIRES_IMPL_(...) , __VA_ARGS__ >
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT inline constexpr bool
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

// The following concepts emulation macros need variable template support

template <class...>
struct __asc_tag;

template <class>
CANN_ASC_STL_API constexpr bool __asc_is_true()
{
    return true;
}

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)
template <bool _Bp>
CANN_ASC_STL_API __asc_enable_if_t<_Bp> __asc_requires()
{}
#else   // ^^^ CANN_ASC_STL_DETAIL_COMPILER(MSVC) ^^^ / vvv !CANN_ASC_STL_DETAIL_COMPILER(MSVC) vvv
template <bool _Bp, __asc_enable_if_t<_Bp, int> = 0>
inline constexpr int __asc_requires = 0;
#endif  // !CANN_ASC_STL_DETAIL_COMPILER(MSVC)

template <class _Tp, class... _Args>
extern _Tp __asc_make_dependent;

template <class _Impl, class... _Args>
using __asc_requires_expr_impl = decltype(__asc_make_dependent<_Impl, _Args...>);

template <typename _Tp>
CANN_ASC_STL_API constexpr void __asc_unused(_Tp&&) noexcept
{}

// So that we can refer to the ::asc::std namespace below
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

// Bisheng CCE is Clang-based but is intentionally classified as CCE rather
// than as Host Clang by compiler.h.  Apply the same unqualified-namespace
// unqualified-namespace workaround for CCE as well, otherwise constrained
// expressions using the _Same_as form can acquire an unsupported qualified
// name in their mangling.
#if CANN_ASC_STL_DETAIL_COMPILER(CCE) || CANN_ASC_STL_DETAIL_COMPILER(CLANG, <, 19)
namespace __asc_unqualified_asc_std = ::asc::std;
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_VSTD __asc_unqualified_asc_std
#else
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_VSTD ::asc::std
#endif

// GCC < 14 can't mangle noexcept expressions. See
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70790.
#if CANN_ASC_STL_DETAIL_COMPILER(GCC, <, 14)
#define CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING() 0
#else
#define CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING() 1
#endif

// We use this macro to ignore the result of required expressions. It is needed because
// gcc < 10 complains about ignored [[nodiscard]] expressions when emulating concepts.
#if CANN_ASC_STL_DETAIL_COMPILER(GCC, <, 10)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_IGNORE_RESULT_(...) static_cast<void>(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_IGNORE_RESULT_(...) __VA_ARGS__
#endif

// The "0" or "1" suffixes indicate whether _REQ is parenthesized or not.
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_0(_REQ) \
    CANN_ASC_STL_DETAIL_PP_SWITCH(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT, _REQ)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_1(_REQ) CANN_ASC_STL_DETAIL_ACCL_CONCEPT_IGNORE_RESULT_ _REQ

// Permissible requirements are of the form (where ... indicates that the pattern can
// contain commas):
//
// - EXPR
// - (EXPR...)
// - noexcept(EXPR...)
// - requires(BOOL-EXPR...)
// - typename(TYPE...)
// - _Same_as(TYPE...) EXPR...
// - _Satisfies(CONCEPT...) EXPR...
//
// The last 4 are handled below:
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_SWITCH_requires CANN_ASC_STL_DETAIL_PP_CASE(REQUIRES)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_SWITCH_noexcept CANN_ASC_STL_DETAIL_PP_CASE(NOEXCEPT)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_SWITCH_typename CANN_ASC_STL_DETAIL_PP_CASE(TYPENAME)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_SWITCH__Same_as CANN_ASC_STL_DETAIL_PP_CASE(SAME_AS)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_SWITCH__Satisfies CANN_ASC_STL_DETAIL_PP_CASE(SATISFIES)

// Converts "requires(ARGS...)" to "ARGS..."
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_REQUIRES_(...) \
    CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_REQUIRES_, __VA_ARGS__)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_REQUIRES_requires(...) __VA_ARGS__

// Converts "noexcept(ARGS...)" to "ARGS..."
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_NOEXCEPT_(...) \
    CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_NOEXCEPT_, __VA_ARGS__)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_NOEXCEPT_noexcept(...) __VA_ARGS__

// Converts "typename(TYPE...)" to "TYPE..."
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_TYPENAME_(_REQ) \
    CANN_ASC_STL_DETAIL_PP_CAT2(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_TYPENAME_, _REQ)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_TYPENAME_typename(...) __VA_ARGS__

// Converts "[typename]opt TYPE..." to "typename TYPE..."
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_TRY_ADD_TYPENAME_(...) \
    CANN_ASC_STL_DETAIL_PP_SWITCH2(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_TRY_ADD_TYPENAME, __VA_ARGS__)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_TRY_ADD_TYPENAME_SWITCH_typename CANN_ASC_STL_DETAIL_PP_CASE(TYPENAME)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_TRY_ADD_TYPENAME_CASE_DEFAULT(...) typename __VA_ARGS__
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_TRY_ADD_TYPENAME_CASE_TYPENAME(...) __VA_ARGS__

// Converts "_Same_as(TYPE) EXPR..." to "EXPR..."
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SAME_AS_(...) \
    CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SAME_AS_, __VA_ARGS__)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SAME_AS__Same_as(...)

// Converts "_Same_as(TYPE) EXPR..." to "TYPE" (The ridiculous concatenation of _ASC with
// _PP_EXPAND(__VA_ARGS__) forms CANN_ASC_STL_DETAIL_PP_EXPAND and is the only way to get MSVC's broken preprocessor to
// do macro expansion here.)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_TYPE_FROM_SAME_AS_(...) \
    CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL,                  \
        CANN_ASC_STL_DETAIL_PP_EVAL(CANN_ASC_STL_DETAIL_PP_FIRST,    \
            CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_TYPE_FROM_SAME_AS_, __VA_ARGS__)))
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_TYPE_FROM_SAME_AS__Same_as(...) _PP_EXPAND(__VA_ARGS__),

// Converts "_Satisfies(TYPE) EXPR..." to "EXPR..."
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SATISFIES_(...) \
    CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SATISFIES_, __VA_ARGS__)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SATISFIES__Satisfies(...)

// Converts "_Satisfies(TYPE) EXPR..." to "TYPE" (The ridiculous concatenation of _ASC
// with _PP_EXPAND(__VA_ARGS__) forms CANN_ASC_STL_DETAIL_PP_EXPAND and is the only way to get MSVC's broken
// preprocessor to do macro expansion here.)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_CONCEPT_FROM_SATISFIES_(...) \
    CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL,                       \
        CANN_ASC_STL_DETAIL_PP_EVAL(CANN_ASC_STL_DETAIL_PP_FIRST,         \
            CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_CONCEPT_FROM_SATISFIES_, __VA_ARGS__)))
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_CONCEPT_FROM_SATISFIES__Satisfies(...) _PP_EXPAND(__VA_ARGS__),

// Here are the implementations of the internal macros, first for when concepts
// are available, and then for when they're not.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

// "CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(NAME, ARGS...)(REQS...)" expands into
// "concept NAME = requires(ARGS...) { CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_(REQS)... }"
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(_NAME, ...) \
    concept _NAME = CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_REQUIREMENTS_##__VA_ARGS__
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_REQUIREMENTS_requires(...) \
    requires(__VA_ARGS__) CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_REQUIREMENTS_
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_REQUIREMENTS_(...) \
    {CANN_ASC_STL_DETAIL_PP_FOR_EACH(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_, __VA_ARGS__)}

// Converts "EXPR" to "CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_0(EXPR)", and
// "(EXPR)" to "CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_1((EXPR))"
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_(_REQ)                                                          \
    CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_, CANN_ASC_STL_DETAIL_PP_IS_PAREN(_REQ)) \
    (_REQ);

// The following macros handle the various special forms of requirements:
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_DEFAULT(_REQ) _REQ
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_REQUIRES(_REQ) \
    requires CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_REQUIRES_(_REQ)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_NOEXCEPT(_REQ) \
    CANN_ASC_STL_DETAIL_PP_EXPAND({ CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_NOEXCEPT_(_REQ) } noexcept)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_TYPENAME(_REQ) \
    CANN_ASC_STL_DETAIL_ACCL_CONCEPT_TRY_ADD_TYPENAME_(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_TYPENAME_(_REQ))
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_SAME_AS(_REQ) \
    {                                                                   \
        CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SAME_AS_(_REQ)             \
    } -> CANN_ASC_STL_DETAIL_ACCL_CONCEPT_VSTD::same_as<CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_TYPE_FROM_SAME_AS_(_REQ)>
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_SATISFIES(_REQ) \
    {                                                                     \
        CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SATISFIES_(_REQ)             \
    } -> CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_CONCEPT_FROM_SATISFIES_(_REQ)

#define CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(_NAME, ...) _NAME<__VA_ARGS__>

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

// "CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(Foo, ARGS...)(REQS...)" expands into:
//
// CANN_ASC_STL_API inline auto Foo_ASC_CONCEPT_FRAGMENT_impl_(ARGS...)
//   -> __asc_enable_if_t<
//        ::__asc_is_true<decltype(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_(REQS)..., void())>()>
// {}
//
// template <class... As>
// CANN_ASC_STL_API inline auto Foo_ASC_CONCEPT_FRAGMENT_(::__asc_tag<As...>*,
//                                                  decltype(&Foo_ASC_CONCEPT_FRAGMENT_impl_<As...>))
//   -> char(&)[1];
//
// template <class... As>
// CANN_ASC_STL_API inline auto Foo_ASC_CONCEPT_FRAGMENT_(...)
//   -> char(&)[2]
//
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(_NAME, ...)                                                       \
    CANN_ASC_STL_API auto _NAME##CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_impl_                                    \
            CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_REQUIREMENTS_##__VA_ARGS__ >                                  \
    {}                                                                                                              \
    template <class... _As, class = decltype(&_NAME##CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_impl_<_As...>)>      \
    CANN_ASC_STL_API auto _NAME##CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_(::__asc_tag<_As...>*, int)->char(&)[1]; \
    template <class... _As>                                                                                         \
    CANN_ASC_STL_API auto _NAME##CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_(::__asc_tag<_As...>*, long)->char(&)[2]
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_REQUIREMENTS_requires(...) \
    (__VA_ARGS__)->__asc_enable_if_t < CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_REQUIREMENTS_IMPL_
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_REQUIREMENTS_IMPL_(...) \
    ::__asc_is_true<decltype(CANN_ASC_STL_DETAIL_PP_FOR_EACH(             \
        CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_, __VA_ARGS__) void())>()

// Called with each individual requirement in the list of requirements
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_(_REQ) \
    void(),                                                 \
        CANN_ASC_STL_DETAIL_PP_CAT(                         \
            CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_, CANN_ASC_STL_DETAIL_PP_IS_PAREN(_REQ))(_REQ),

// The following macros handle the various special forms of requirements:
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_DEFAULT(_REQ) \
    CANN_ASC_STL_DETAIL_ACCL_CONCEPT_IGNORE_RESULT_(_REQ)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_REQUIRES(_REQ) \
    ::__asc_requires<CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_REQUIRES_(_REQ)>
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_NOEXCEPT(_REQ) \
    CANN_ASC_STL_DETAIL_ACCL_CONCEPT_NOEXCEPT_REQUIREMENT_(_REQ)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_TYPENAME(_REQ) \
    static_cast<::__asc_tag<CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_TYPENAME_(_REQ)>*>(nullptr)
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_SAME_AS(_REQ) \
    ::__asc_requires<::asc::std::same_as<CANN_ASC_STL_DETAIL_ACCL_CONCEPT_SAME_AS_REQUIREMENT_(_REQ)>>
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_CASE_SATISFIES(_REQ)                   \
    ::__asc_requires < CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_CONCEPT_FROM_SATISFIES_(_REQ) < \
        decltype(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SATISFIES_(_REQ)) >>

// Converts "_Same_as(TYPE) EXPR..." to "TYPE, decltype(EXPR...)"
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_SAME_AS_REQUIREMENT_(_REQ) \
    CANN_ASC_STL_DETAIL_ACCL_CONCEPT_GET_TYPE_FROM_SAME_AS_(_REQ),  \
        decltype(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_SAME_AS_(_REQ))

#if CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING()
// Converts "noexcept(EXPR)" to "::__asc_requires<noexcept(EXPR)>"
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_NOEXCEPT_REQUIREMENT_(_REQ) ::__asc_requires<_REQ>
#else
// If the compiler cannot mangle noexcept expressions, just check that the expression is
// well-formed. This converts "noexcept(EXPR)" to "static_cast<void>(EXPR)"
#define CANN_ASC_STL_DETAIL_ACCL_CONCEPT_NOEXCEPT_REQUIREMENT_(_REQ) \
    CANN_ASC_STL_DETAIL_ACCL_CONCEPT_IGNORE_RESULT_(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_EAT_NOEXCEPT_(_REQ))
#endif

// "CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(Foo, Args...)" expands to
// "(1 == sizeof(Foo_ASC_CONCEPT_FRAGMENT_(static_cast<::__asc_tag<Args...>*>(nullptr), nullptr)))"
#define CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(_NAME, ...) \
    (1 == sizeof(_NAME##CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT_(static_cast<::__asc_tag<__VA_ARGS__>*>(nullptr), 0)))

#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

////////////////////////////////////////////////////////////////////////////////
// CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR
// Usage:
//   template <typename T>
//   CANN_ASC_STL_DETAIL_ACCL_CONCEPT equality_comparable =
//     CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((T), T const& lhs, T const& rhs) (
//       lhs == rhs,
//       lhs != rhs
//     );
//
// Can only be used as the last requirement in a concept definition.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR(_TY, ...) \
    requires(__VA_ARGS__) CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_IMPL_
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_IMPL_(...) \
    {CANN_ASC_STL_DETAIL_PP_FOR_EACH(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_, __VA_ARGS__)}

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR(_TY, ...) \
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_IMPL(_TY, CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_ID(_TY), __VA_ARGS__)
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_IMPL(_TY, _ID, ...)                                               \
    ::__asc_requires_expr_impl<struct CANN_ASC_STL_DETAIL_PP_CAT(__asc_requires_expr_detail_, _ID)               \
            CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_REFS _TY>::                                            \
        __asc_is_satisfied(                                                                                      \
            static_cast<::__asc_tag<void CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_REFS _TY>*>(nullptr), 0); \
    struct CANN_ASC_STL_DETAIL_PP_CAT(__asc_requires_expr_detail_, _ID) {                                        \
        using __asc_self_t = CANN_ASC_STL_DETAIL_PP_CAT(__asc_requires_expr_detail_, _ID);                       \
        template <class CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_DEFNS _TY>                                 \
        CANN_ASC_STL_API static auto __asc_well_formed(__VA_ARGS__)                                              \
            CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_REQUIREMENTS_

// Expands "T1, T2, variadic T3" to ", class T1, class T2, class... T3"
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_DEFNS(...) \
    CANN_ASC_STL_DETAIL_PP_FOR_EACH(CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_DEFN, __VA_ARGS__)

// Expands "TY" to ", class TY" and "variadic TY" to ", class... TY"
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_DEFN(_TY) \
    , CANN_ASC_STL_DETAIL_PP_SWITCH2(CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_DEFN, _TY)
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_DEFN_SWITCH_variadic CANN_ASC_STL_DETAIL_PP_CASE(VARIADIC)
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_DEFN_CASE_DEFAULT(_TY) class _TY
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_DEFN_CASE_VARIADIC(_TY) \
    class... CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_EAT_VARIADIC_, _TY)

// Expands "T1, T2, variadic T3" to ", T1, T2, T3..."
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_REFS(...) \
    CANN_ASC_STL_DETAIL_PP_FOR_EACH(CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_REF, __VA_ARGS__)

// Expands "TY" to ", TY" and "variadic TY" to ", TY..."
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_REF(_TY) \
    , CANN_ASC_STL_DETAIL_PP_SWITCH2(CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_REF, _TY)
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_REF_SWITCH_variadic CANN_ASC_STL_DETAIL_PP_CASE(VARIADIC)
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_REF_CASE_DEFAULT(_TY) _TY
#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_TPARAM_REF_CASE_VARIADIC(_TY) \
    CANN_ASC_STL_DETAIL_PP_CAT(CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_EAT_VARIADIC_, _TY)...

#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_ID(...) CANN_ASC_STL_DETAIL_COUNTER()

#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_EAT_VARIADIC_variadic

#define CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR_REQUIREMENTS_(...)                                                  \
    ->decltype(CANN_ASC_STL_DETAIL_PP_FOR_EACH(CANN_ASC_STL_DETAIL_ACCL_CONCEPT_REQUIREMENT_, __VA_ARGS__) void()) \
    {}                                                                                                             \
    template <class... _Args, class = decltype(&__asc_self_t::__asc_well_formed<_Args...>)>                        \
    CANN_ASC_STL_API static constexpr bool __asc_is_satisfied(::__asc_tag<_Args...>*, int)                         \
    {                                                                                                              \
        return true;                                                                                               \
    }                                                                                                              \
    CANN_ASC_STL_API static constexpr bool __asc_is_satisfied(void*, long)                                         \
    {                                                                                                              \
        return false;                                                                                              \
    }                                                                                                              \
    }
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_CONCEPT_MACROS_H
