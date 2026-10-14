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

#ifndef CANN_ASC_STL_ASC_STD___CHRONO_HH_MM_SS_H
#define CANN_ASC_STL_ASC_STD___CHRONO_HH_MM_SS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__chrono/duration.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/ratio>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace chrono {
template <class _Duration>
class hh_mm_ss {
private:
    static_assert(__is_asc_std_duration_v<_Duration>, "template parameter of hh_mm_ss must be a std::chrono::duration");
    using __common_type = common_type_t<_Duration, chrono::seconds>;

    // The fractional_width / precision initializers depend on these two
    // helpers, so they must stay plain constexpr with no API annotation.
    CANN_ASC_STL_NODISCARD static constexpr uint64_t __pow10(unsigned __exp)
    {
        uint64_t __ret = 1;
        for (unsigned __i = 0; __i < __exp; ++__i) {
            __ret *= 10U;
        }
        return __ret;
    }

    CANN_ASC_STL_NODISCARD static constexpr unsigned __width(uint64_t __n, uint64_t __d = 10, unsigned __w = 0)
    {
        unsigned __result = 0;
        while (__n >= 2 && __d != 0 && __w < 19) {
            __d = (__n != 0 ? __d % __n : 0) * 10;
            ++__w;
            ++__result;
        }
        return __result;
    }

public:
    static unsigned constexpr fractional_width =
        __width(__common_type::period::den) < 19 ? __width(__common_type::period::den) : 6u;
    using precision = duration<typename __common_type::rep, ratio<1, __pow10(fractional_width)>>;

    CANN_ASC_STL_API constexpr hh_mm_ss() noexcept : hh_mm_ss{_Duration::zero()}
    {}

    CANN_ASC_STL_API constexpr explicit hh_mm_ss(_Duration __dur) noexcept
        : __is_neg_(__dur < _Duration(0)),
          __hours_(asc::std::chrono::duration_cast<chrono::hours>(asc::std::chrono::abs(__dur))),
          __month_(asc::std::chrono::duration_cast<chrono::minutes>(asc::std::chrono::abs(__dur) - hours())),
          __seconds_(
              asc::std::chrono::duration_cast<chrono::seconds>(asc::std::chrono::abs(__dur) - hours() - minutes())),
          __fraction_(asc::std::chrono::duration_cast<precision>(
              asc::std::chrono::abs(__dur) - hours() - minutes() - seconds()))
    {}

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool is_negative() const noexcept
    {
        return __is_neg_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::hours hours() const noexcept
    {
        return __hours_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::minutes minutes() const noexcept
    {
        return __month_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr chrono::seconds seconds() const noexcept
    {
        return __seconds_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr precision subseconds() const noexcept
    {
        return __fraction_;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr precision to_duration() const noexcept
    {
        const auto __dur = __hours_ + __month_ + __seconds_ + __fraction_;
        return __is_neg_ ? -__dur : __dur;
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr explicit operator precision() const noexcept
    {
        return to_duration();
    }

private:
    bool __is_neg_;
    chrono::hours __hours_;
    chrono::minutes __month_;
    chrono::seconds __seconds_;
    precision __fraction_;
};

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool is_am(const hours& __hours_) noexcept
{
    return __hours_ >= hours{0} && __hours_ < hours{12};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool is_pm(const hours& __hours_) noexcept
{
    return __hours_ >= hours{12} && __hours_ < hours{24};
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr hours make12(const hours& __hours_) noexcept
{
    if (__hours_ == hours{0}) {
        return hours{12};
    } else if (__hours_ <= hours{12}) {
        return __hours_;
    } else {
        return __hours_ - hours{12};
    }
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr hours make24(const hours& __hours_, bool __is_pm) noexcept
{
    if (__is_pm) {
        return __hours_ == hours{12} ? __hours_ : __hours_ + hours{12};
    } else {
        return __hours_ == hours{12} ? hours{0} : __hours_;
    }
}
}  // namespace chrono

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CHRONO_HH_MM_SS_H
