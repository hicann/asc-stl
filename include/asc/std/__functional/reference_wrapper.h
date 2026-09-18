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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_REFERENCE_WRAPPER_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_REFERENCE_WRAPPER_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/weak_result_type.h>
#include <asc/std/__fwd/reference_wrapper.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
class reference_wrapper : public __weak_result_type<_Tp> {
public:
    // types
    using type = _Tp;

private:
    type* __f_{};

    static CANN_ASC_STL_API void __fun(_Tp&) noexcept;
    static void __fun(_Tp&&) = delete;  // NOLINT(modernize-use-equals-delete)

public:
    template <class _Up,
        class =
            enable_if_t<!__is_same_uncvref<_Up, reference_wrapper>::value, decltype(__fun(::asc::std::declval<_Up>()))>>
    CANN_ASC_STL_API constexpr reference_wrapper(_Up&& __u) noexcept(noexcept(__fun(::asc::std::declval<_Up>())))
    {
        type& __f = static_cast<_Up&&>(__u);
        __f_ = ::asc::std::addressof(__f);
    }

    // access
    CANN_ASC_STL_API constexpr operator type&() const noexcept
    {
        return *__f_;
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr type& get() const noexcept
    {
        return *__f_;
    }

    // invoke
    template <class... _ArgTypes>
    CANN_ASC_STL_API constexpr invoke_result_t<type&, _ArgTypes...> operator()(_ArgTypes&&... __args) const
        noexcept(is_nothrow_invocable_v<_Tp&, _ArgTypes...>)
    {
        return ::asc::std::invoke(
            get(), ::asc::std::forward<_ArgTypes>(__args)...);  // NOLINT(build/include_what_you_use)
    }
};

template <class _Tp>
reference_wrapper(_Tp&) -> reference_wrapper<_Tp>;

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr reference_wrapper<_Tp> ref(_Tp& __t) noexcept
{
    return reference_wrapper<_Tp>(__t);
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr reference_wrapper<_Tp> ref(reference_wrapper<_Tp> __t) noexcept
{
    return __t;
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr reference_wrapper<const _Tp> cref(const _Tp& __t) noexcept
{
    return reference_wrapper<const _Tp>(__t);
}

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr reference_wrapper<const _Tp> cref(reference_wrapper<_Tp> __t) noexcept
{
    return __t;
}

template <class _Tp>
void ref(const _Tp&&) = delete;
template <class _Tp>
void cref(const _Tp&&) = delete;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_REFERENCE_WRAPPER_H
