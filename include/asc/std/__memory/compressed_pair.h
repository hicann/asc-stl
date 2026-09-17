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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_COMPRESSED_PAIR_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_COMPRESSED_PAIR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__tuple_dir/tuple_indices.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/dependent_type.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_final.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/piecewise_construct.h>
// Member swap reaches the scalar/ADL swap through using ::asc::std::swap;
// is_swappable.h only provides the detection declarations, so this header must
// include the definition itself (self-containment: the CCE compile gate does not
// instantiate swap, a missing definition only surfaces at kernel link time).
#include <asc/std/__utility/swap.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

//! @brief Tag type for default-initializing (instead of value-initializing) one or both members of a pair.
struct __default_init_tag {};
struct __value_init_tag {};

template <class _Tp, int _Idx, bool _CanBeEmptyBase = is_empty_v<_Tp> && !is_final_v<_Tp>>
struct __compressed_pair_elem {
    using _ParamT = _Tp;
    using reference = _Tp&;
    using const_reference = const _Tp&;

    CANN_ASC_STL_API constexpr explicit __compressed_pair_elem(__default_init_tag) noexcept(
        is_nothrow_default_constructible_v<_Tp>)
    {}
    CANN_ASC_STL_API constexpr explicit __compressed_pair_elem(__value_init_tag) noexcept(
        is_nothrow_default_constructible_v<_Tp>)
        : __value_()
    {}

    template <class _Up, enable_if_t<!is_same_v<__compressed_pair_elem, decay_t<_Up>>, int> = 0>
    CANN_ASC_STL_API constexpr explicit __compressed_pair_elem(_Up&& __u) noexcept(is_nothrow_constructible_v<_Tp, _Up>)
        : __value_(::asc::std::forward<_Up>(__u))
    {}

    template <class... _Args, size_t... _Indices>
    CANN_ASC_STL_API constexpr explicit __compressed_pair_elem(piecewise_construct_t, tuple<_Args...> __args,
        __tuple_indices<_Indices...>) noexcept(is_nothrow_constructible_v<_Tp, _Args...>)
        : __value_(::asc::std::forward<_Args>(::asc::std::get<_Indices>(__args))...)
    {}

    CANN_ASC_STL_API constexpr reference __get() noexcept
    {
        return __value_;
    }
    CANN_ASC_STL_API constexpr const_reference __get() const noexcept
    {
        return __value_;
    }

private:
    _Tp __value_;
};

template <class _Tp, int _Idx>
struct __compressed_pair_elem<_Tp, _Idx, true> : private _Tp {
    using _ParamT = _Tp;
    using reference = _Tp&;
    using const_reference = const _Tp&;
    using __value_type = _Tp;

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI explicit constexpr __compressed_pair_elem() = default;

    CANN_ASC_STL_API constexpr explicit __compressed_pair_elem(__default_init_tag) noexcept(
        is_nothrow_default_constructible_v<_Tp>)
    {}
    CANN_ASC_STL_API constexpr explicit __compressed_pair_elem(__value_init_tag) noexcept(
        is_nothrow_default_constructible_v<_Tp>)
        : __value_type()
    {}

    template <class _Up, enable_if_t<!is_same_v<__compressed_pair_elem, decay_t<_Up>>, int> = 0>
    CANN_ASC_STL_API constexpr explicit __compressed_pair_elem(_Up&& __u) noexcept(is_nothrow_constructible_v<_Tp, _Up>)
        : __value_type(::asc::std::forward<_Up>(__u))
    {}

    template <class... _Args, size_t... _Indices>
    CANN_ASC_STL_API constexpr __compressed_pair_elem(piecewise_construct_t, tuple<_Args...> __args,
        __tuple_indices<_Indices...>) noexcept(is_nothrow_constructible_v<_Tp, _Args...>)
        : __value_type(::asc::std::forward<_Args>(::asc::std::get<_Indices>(__args))...)
    {}

    CANN_ASC_STL_API constexpr reference __get() noexcept
    {
        return *this;
    }
    CANN_ASC_STL_API constexpr const_reference __get() const noexcept
    {
        return *this;
    }
};

template <class _T1, class _T2>
class __compressed_pair : private __compressed_pair_elem<_T1, 0>, private __compressed_pair_elem<_T2, 1> {
public:
    // NOTE: This static assert should never fire because __compressed_pair
    // is *almost never* used in a scenario where it's possible for T1 == T2.
    // (The exception is std::function where it is possible that the function
    //  object and the allocator have the same type).
    static_assert((!is_same_v<_T1, _T2>),
        "__compressed_pair cannot be instantiated when T1 and T2 are the same type; "
        "The current implementation is NOT ABI-compatible with the previous implementation for this "
        "configuration");

    using _Base1 = __compressed_pair_elem<_T1, 0>;
    using _Base2 = __compressed_pair_elem<_T2, 1>;

    template <bool _Dummy = true,
        class = enable_if_t<__dependent_type<is_default_constructible<_T1>, _Dummy>::value &&
            __dependent_type<is_default_constructible<_T2>, _Dummy>::value>>
    CANN_ASC_STL_API constexpr explicit __compressed_pair() noexcept(
        is_nothrow_default_constructible_v<_T1> && is_nothrow_default_constructible_v<_T2>)
        : _Base1(__value_init_tag()), _Base2(__value_init_tag())
    {}

    template <class _U1, class _U2>
    CANN_ASC_STL_API constexpr explicit __compressed_pair(_U1&& __t1, _U2&& __t2) noexcept(
        is_constructible_v<_T1, _U1> && is_constructible_v<_T2, _U2>)
        : _Base1(::asc::std::forward<_U1>(__t1)), _Base2(::asc::std::forward<_U2>(__t2))
    {}

    template <class... _Args1, class... _Args2>
    CANN_ASC_STL_API constexpr explicit __compressed_pair(piecewise_construct_t __pc, tuple<_Args1...> __first_args,
        tuple<_Args2...>                                                   // NOLINT(build/include_what_you_use)
            __second_args) noexcept(is_constructible_v<_T1, _Args1...> &&  // NOLINT(build/include_what_you_use)
        is_constructible_v<_T2, _Args2...>)
        : _Base1(__pc, ::asc::std::move(__first_args), typename __make_tuple_indices<sizeof...(_Args1)>::type()),
          _Base2(__pc, ::asc::std::move(__second_args), typename __make_tuple_indices<sizeof...(_Args2)>::type())
    {}

    CANN_ASC_STL_API constexpr typename _Base1::reference first() noexcept
    {
        return static_cast<_Base1&>(*this).__get();
    }

    CANN_ASC_STL_API constexpr typename _Base1::const_reference first() const noexcept
    {
        return static_cast<_Base1 const&>(*this).__get();
    }

    CANN_ASC_STL_API constexpr typename _Base2::reference second() noexcept
    {
        return static_cast<_Base2&>(*this).__get();
    }

    CANN_ASC_STL_API constexpr typename _Base2::const_reference second() const noexcept
    {
        return static_cast<_Base2 const&>(*this).__get();
    }

    CANN_ASC_STL_API constexpr static _Base1* __get_first_base(__compressed_pair* __pair) noexcept
    {
        return static_cast<_Base1*>(__pair);
    }
    CANN_ASC_STL_API constexpr static _Base2* __get_second_base(__compressed_pair* __pair) noexcept
    {
        return static_cast<_Base2*>(__pair);
    }

    CANN_ASC_STL_API constexpr void swap(__compressed_pair& __x) noexcept(
        is_nothrow_swappable_v<_T1> && is_nothrow_swappable_v<_T2>)
    {
        using ::asc::std::swap;
        swap(first(), __x.first());
        swap(second(), __x.second());  // NOLINT(build/include_what_you_use)
    }
};

template <class _T1, class _T2>
CANN_ASC_STL_API constexpr void swap(
    __compressed_pair<_T1, _T2>& __x, __compressed_pair<_T1, _T2>& __y) noexcept(  // NOLINT(build/include_what_you_use)
    is_nothrow_swappable_v<_T1> && is_nothrow_swappable_v<_T2>)
{
    __x.swap(__y);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_COMPRESSED_PAIR_H
