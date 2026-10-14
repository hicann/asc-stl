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

#ifndef CANN_ASC_STL_ASC___MDSPAN_ACCESSORS_H
#define CANN_ASC_STL_ASC___MDSPAN_ACCESSORS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
#define CANN_ASC_STL_DETAIL_MDSPAN_GM __gm__
#define CANN_ASC_STL_DETAIL_MDSPAN_UB __ubuf__
#else
#define CANN_ASC_STL_DETAIL_MDSPAN_GM
#define CANN_ASC_STL_DETAIL_MDSPAN_UB
#endif

namespace asc {

namespace detail {
// Local pointer vocabulary: this root stays free of trait-header
// dependencies, so the accessor checks spell their own primitives.
template <class T>
struct mdspan_is_pointer {
    static constexpr bool value = false;
};
template <class T>
struct mdspan_is_pointer<T*> {
    static constexpr bool value = true;
};

template <class T>
struct mdspan_remove_pointer {
    using type = T;
};
template <class T>
struct mdspan_remove_pointer<T*> {
    using type = T;
};
}  // namespace detail

template <class Accessor>
class host_accessor : public Accessor {
public:
    using offset_policy = host_accessor<typename Accessor::offset_policy>;
    using element_type = typename Accessor::element_type;
    using reference = typename Accessor::reference;
    using data_handle_type = typename Accessor::data_handle_type;

    // Host-domain accessor: unlike gm/ub it is never valid in pure SIMT code,
    // and access fails fast there instead of silently dereferencing a host
    // pointer.  A Host-side runtime pointer-space validation (the dev-side
    // __detectably_invalid probe over AscendCL pointer attributes) would move
    // "host_accessor holding a device pointer" to debug time, but it needs a
    // pointer-space runtime binding this tree does not deliver and would
    // forfeit the constexpr access contract, so only the compile-time half is
    // enforced here.
    CANN_ASC_STL_HOST_API constexpr host_accessor() noexcept = default;
    CANN_ASC_STL_HOST_API constexpr explicit host_accessor(Accessor accessor) noexcept : Accessor(accessor)
    {}
    CANN_ASC_STL_HOST_API constexpr reference access(data_handle_type pointer, __SIZE_TYPE__ index) const noexcept
    {
        return Accessor::access(pointer, index);
    }
    CANN_ASC_STL_HOST_API constexpr data_handle_type offset(
        data_handle_type pointer, __SIZE_TYPE__ index) const noexcept
    {
        return Accessor::offset(pointer, index);
    }
};

template <class Accessor>
class gm_accessor {
public:
    using offset_policy = gm_accessor<typename Accessor::offset_policy>;
    using element_type = typename Accessor::element_type;
    using reference = CANN_ASC_STL_DETAIL_MDSPAN_GM element_type&;
    using data_handle_type = CANN_ASC_STL_DETAIL_MDSPAN_GM element_type*;

    CANN_ASC_STL_API constexpr gm_accessor() noexcept = default;
    CANN_ASC_STL_API constexpr explicit gm_accessor(Accessor) noexcept
    {}
    CANN_ASC_STL_API constexpr reference access(data_handle_type pointer, __SIZE_TYPE__ index) const noexcept
    {
        return pointer[index];
    }
    CANN_ASC_STL_API constexpr data_handle_type offset(data_handle_type pointer, __SIZE_TYPE__ index) const noexcept
    {
        return pointer + index;
    }
};

#if !CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class Accessor>
class ub_accessor {
public:
    using offset_policy = ub_accessor<typename Accessor::offset_policy>;
    using element_type = typename Accessor::element_type;
    using reference = CANN_ASC_STL_DETAIL_MDSPAN_UB element_type&;
    using data_handle_type = CANN_ASC_STL_DETAIL_MDSPAN_UB element_type*;

    CANN_ASC_STL_API constexpr ub_accessor() noexcept = default;
    CANN_ASC_STL_API constexpr explicit ub_accessor(Accessor) noexcept
    {}
    CANN_ASC_STL_API constexpr reference access(data_handle_type pointer, __SIZE_TYPE__ index) const noexcept
    {
        return pointer[index];
    }
    CANN_ASC_STL_API constexpr data_handle_type offset(data_handle_type pointer, __SIZE_TYPE__ index) const noexcept
    {
        return pointer + index;
    }
};
#endif

template <class Accessor>
class restrict_accessor : public Accessor {
    static_assert(detail::mdspan_is_pointer<typename Accessor::data_handle_type>::value,
        "restrict_accessor requires a pointer based accessor");

public:
    using offset_policy = restrict_accessor<typename Accessor::offset_policy>;
    using element_type = typename Accessor::element_type;
    using reference = typename Accessor::reference;
    // The reason this accessor exists: advertise the no-alias guarantee to
    // the compiler (CCE and g++ both honour __restrict on the handle) instead
    // of transparently re-exporting the base handle type.  cv-qualification
    // of the base pointee is preserved through remove_pointer.
    using data_handle_type =
        typename detail::mdspan_remove_pointer<typename Accessor::data_handle_type>::type* __restrict;

    CANN_ASC_STL_API constexpr restrict_accessor() noexcept = default;
    CANN_ASC_STL_API constexpr explicit restrict_accessor(Accessor accessor) noexcept : Accessor(accessor)
    {}
};

template <class T>
inline constexpr bool is_host_accessor_v = false;
template <class A>
inline constexpr bool is_host_accessor_v<host_accessor<A>> = true;
template <class T>
inline constexpr bool is_gm_accessor_v = false;
template <class A>
inline constexpr bool is_gm_accessor_v<gm_accessor<A>> = true;
template <class T>
inline constexpr bool is_ub_accessor_v = false;
#if !CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
template <class A>
inline constexpr bool is_ub_accessor_v<ub_accessor<A>> = true;
#endif
template <class T>
inline constexpr bool is_restrict_accessor_v = false;
template <class A>
inline constexpr bool is_restrict_accessor_v<restrict_accessor<A>> = true;

}  // namespace asc

// The address-space spellings are an implementation detail of the accessor
// declarations above and must not leak into including translation units.
#undef CANN_ASC_STL_DETAIL_MDSPAN_GM
#undef CANN_ASC_STL_DETAIL_MDSPAN_UB

#endif  // CANN_ASC_STL_ASC___MDSPAN_ACCESSORS_H
