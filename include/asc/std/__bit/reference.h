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

#ifndef CANN_ASC_STL_ASC_STD___BIT_REFERENCE_H
#define CANN_ASC_STL_ASC_STD___BIT_REFERENCE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/copy_n.h>
#include <asc/std/__algorithm/fill_n.h>
#include <asc/std/__algorithm/min.h>
#include <asc/std/__bit/countr.h>
#include <asc/std/__bit/popcount.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__utility/swap.h>

// The base <asc/__config> provides no standard-version number macro and no
// MSVC diagnostic suppression, so minimal equivalents are defined here.
#ifndef CANN_ASC_STL_DETAIL_STD_VER
#if CANN_ASC_STL_DETAIL_CPLUSPLUS <= 199711L
#define CANN_ASC_STL_DETAIL_STD_VER 2003
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201103L
#define CANN_ASC_STL_DETAIL_STD_VER 2011
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201402L
#define CANN_ASC_STL_DETAIL_STD_VER 2014
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 201703L
#define CANN_ASC_STL_DETAIL_STD_VER 2017
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202002L
#define CANN_ASC_STL_DETAIL_STD_VER 2020
#elif CANN_ASC_STL_DETAIL_CPLUSPLUS <= 202302L
#define CANN_ASC_STL_DETAIL_STD_VER 2023
#else
#define CANN_ASC_STL_DETAIL_STD_VER 2024
#endif
#endif  // CANN_ASC_STL_DETAIL_STD_VER

#ifndef CANN_ASC_STL_DETAIL_DIAG_PUSH
#define CANN_ASC_STL_DETAIL_DIAG_PUSH CANN_ASC_STL_DETAIL_DIAGNOSTIC_PUSH()
#define CANN_ASC_STL_DETAIL_DIAG_POP CANN_ASC_STL_DETAIL_DIAGNOSTIC_POP()
#if defined(_MSC_VER)
#define CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(x) __pragma(warning(disable : x))
#else
#define CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(x)
#endif
#endif  // CANN_ASC_STL_DETAIL_DIAG_PUSH

// Gate for the GCC pre-9 constexpr workaround: genuine GCC only (never CCE,
// pure-SIMT or clang, which may also define __GNUC__).
#ifndef CANN_ASC_STL_DETAIL_BIT_REF_GCC_PRE9
#if defined(__GNUC__) && !defined(__clang__) && !defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__) && \
    __GNUC__ < 9
#define CANN_ASC_STL_DETAIL_BIT_REF_GCC_PRE9 1
#else
#define CANN_ASC_STL_DETAIL_BIT_REF_GCC_PRE9 0
#endif
#endif  // CANN_ASC_STL_DETAIL_BIT_REF_GCC_PRE9

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Cp>
class __bit_const_reference;

template <class _Cp, bool _IsConst>
class __bit_iterator;

template <class _Cp>
class __bit_reference {
    using __storage_type = typename _Cp::__storage_type;
    using __storage_pointer = typename _Cp::__storage_pointer;

    __storage_pointer __seg_;
    __storage_type __mask_;

    friend typename _Cp::__self;

    friend class __bit_const_reference<_Cp>;
    friend class __bit_iterator<_Cp, false>;

public:
    using __container = typename _Cp::__self;

    CANN_ASC_STL_API constexpr __bit_reference(const __bit_reference&) = default;

    CANN_ASC_STL_API constexpr operator bool() const noexcept
    {
        return static_cast<bool>(*__seg_ & __mask_);
    }
    CANN_ASC_STL_API constexpr bool operator~() const noexcept
    {
        return !static_cast<bool>(*this);
    }

    CANN_ASC_STL_API constexpr __bit_reference& operator=(bool x) noexcept
    {
        if (x) {
            *__seg_ |= __mask_;
        } else {
            *__seg_ &= ~__mask_;
        }
        return *this;
    }

#if CANN_ASC_STL_DETAIL_STD_VER >= 2023
    CANN_ASC_STL_API constexpr const __bit_reference& operator=(bool x) const noexcept
    {
        if (x) {
            *__seg_ |= __mask_;
        } else {
            *__seg_ &= ~__mask_;
        }
        return *this;
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER >= 2023

    CANN_ASC_STL_API constexpr __bit_reference& operator=(const __bit_reference& x) noexcept
    {
        return operator=(static_cast<bool>(x));
    }

    CANN_ASC_STL_API constexpr void flip() noexcept
    {
        *__seg_ ^= __mask_;
    }
    CANN_ASC_STL_API constexpr __bit_iterator<_Cp, false> operator&() const noexcept  // NOLINT(runtime/operator)
    {
        return __bit_iterator<_Cp, false>(__seg_, static_cast<unsigned>(countr_zero(__mask_)));
    }

    CANN_ASC_STL_API friend constexpr void swap(__bit_reference<_Cp> x, __bit_reference<_Cp> y) noexcept
    {
        bool t = x;
        x = y;
        y = t;
    }

    template <class _Dp>
    CANN_ASC_STL_API friend constexpr void swap(__bit_reference<_Cp> x, __bit_reference<_Dp> y) noexcept
    {
        bool t = x;
        x = y;
        y = t;
    }

    CANN_ASC_STL_API friend constexpr void swap(__bit_reference<_Cp> x, bool& y) noexcept
    {
        bool t = x;
        x = y;
        y = t;
    }

    CANN_ASC_STL_API friend constexpr void swap(bool& x, __bit_reference<_Cp> y) noexcept
    {
        bool t = x;
        x = y;
        y = t;
    }

private:
    CANN_ASC_STL_API constexpr explicit __bit_reference(__storage_pointer s, __storage_type m) noexcept
        : __seg_(s), __mask_(m)
    {}
};

template <class _Cp>
class __bit_const_reference {
    using __storage_type = typename _Cp::__storage_type;
    using __storage_pointer = typename _Cp::__const_storage_pointer;

    __storage_pointer __seg_;
    __storage_type __mask_;

    friend typename _Cp::__self;
    friend class __bit_iterator<_Cp, true>;

public:
    using __container = typename _Cp::__self;

    CANN_ASC_STL_API __bit_const_reference(const __bit_const_reference&) = default;

    CANN_ASC_STL_API constexpr __bit_const_reference(const __bit_reference<_Cp>& x) noexcept
        : __seg_(x.__seg_), __mask_(x.__mask_)
    {}

    CANN_ASC_STL_API constexpr operator bool() const noexcept
    {
        return static_cast<bool>(*__seg_ & __mask_);
    }

    CANN_ASC_STL_API constexpr __bit_iterator<_Cp, true> operator&() const noexcept  // NOLINT(runtime/operator)
    {
        return __bit_iterator<_Cp, true>(__seg_, static_cast<unsigned>(countr_zero(__mask_)));
    }

private:
    CANN_ASC_STL_API constexpr explicit __bit_const_reference(__storage_pointer s, __storage_type m) noexcept
        : __seg_(s), __mask_(m)
    {}

    __bit_const_reference& operator=(const __bit_const_reference&) = delete;
};

// fill_n

template <bool _FillVal, class _Cp>
CANN_ASC_STL_API constexpr void __fill_n_impl(__bit_iterator<_Cp, false> first, typename _Cp::size_type n)
{
    using _It = __bit_iterator<_Cp, false>;
    using __storage_type = typename _It::__storage_type;
    using difference_type = typename _Cp::difference_type;

    const int bits_per_word = _It::__bits_per_word;
    // do first partial word
    if (first.__ctz_ != 0) {
        __storage_type clz_f = static_cast<__storage_type>(bits_per_word - first.__ctz_);
        __storage_type dn =  // NOLINT(build/include_what_you_use)
            min<__storage_type>(clz_f, static_cast<__storage_type>(n));
        __storage_type m = (~__storage_type(0) << first.__ctz_) & (~__storage_type(0) >> (clz_f - dn));
        if (_FillVal) {
            *first.__seg_ |= m;
        } else {
            *first.__seg_ &= ~m;
        }
        n -= dn;
        ++first.__seg_;
    }
    // do middle whole words
    __storage_type nw = n / bits_per_word;
    fill_n(first.__seg_, static_cast<difference_type>(nw), _FillVal ? ~static_cast<__storage_type>(0) : 0);
    n -= static_cast<difference_type>(nw * bits_per_word);
    // do last partial word
    if (n > 0) {
        first.__seg_ += static_cast<difference_type>(nw);
        __storage_type m = ~__storage_type(0) >> (bits_per_word - n);
        if (_FillVal) {
            *first.__seg_ |= m;
        } else {
            *first.__seg_ &= ~m;
        }
    }
}

template <class _Cp>
CANN_ASC_STL_API constexpr void fill_n(__bit_iterator<_Cp, false> first, typename _Cp::size_type n, bool value)
{
    if (n > 0) {
        if (value) {
            __fill_n_impl<true>(first, n);
        } else {
            __fill_n_impl<false>(first, n);
        }
    }
}

// fill

template <class _Cp>
CANN_ASC_STL_API constexpr void fill(__bit_iterator<_Cp, false> first, __bit_iterator<_Cp, false> last, bool value)
{
    fill_n(first, static_cast<typename _Cp::size_type>(last - first), value);
}

// copy

template <class _Cp, bool _IsConst>
CANN_ASC_STL_API constexpr __bit_iterator<_Cp, false> __copy_aligned(
    __bit_iterator<_Cp, _IsConst> first, __bit_iterator<_Cp, _IsConst> last, __bit_iterator<_Cp, false> result)
{
    using _In = __bit_iterator<_Cp, _IsConst>;
    using difference_type = typename _In::difference_type;
    using __storage_type = typename _In::__storage_type;

    const int bits_per_word = _In::__bits_per_word;
    difference_type n = last - first;
    if (n > 0) {
        // do first word
        if (first.__ctz_ != 0) {
            unsigned clz_f = bits_per_word - first.__ctz_;
            difference_type dn =  // NOLINT(build/include_what_you_use)
                min(static_cast<difference_type>(clz_f), n);
            n -= dn;
            __storage_type m = (~__storage_type(0) << first.__ctz_) & (~__storage_type(0) >> (clz_f - dn));
            __storage_type b = *first.__seg_ & m;
            *result.__seg_ &= ~m;
            *result.__seg_ |= b;
            result.__seg_ += (dn + result.__ctz_) / bits_per_word;
            result.__ctz_ = static_cast<unsigned>((dn + result.__ctz_) % bits_per_word);
            ++first.__seg_;
            // first.__ctz_ = 0;
        }
        // first.__ctz_ == 0;
        // do middle words
        __storage_type nw = n / bits_per_word;
        copy_n(first.__seg_, static_cast<typename _In::difference_type>(nw), result.__seg_);
        result.__seg_ += static_cast<difference_type>(nw);
        n -= static_cast<difference_type>(nw * bits_per_word);
        // do last word
        if (n > 0) {
            first.__seg_ += static_cast<difference_type>(nw);
            __storage_type m = ~__storage_type(0) >> (bits_per_word - n);
            __storage_type b = *first.__seg_ & m;
            *result.__seg_ &= ~m;
            *result.__seg_ |= b;
            result.__ctz_ = static_cast<unsigned>(n);
        }
    }
    return result;
}

template <class _Cp, bool _IsConst>
CANN_ASC_STL_API constexpr __bit_iterator<_Cp, false> __copy_unaligned(
    __bit_iterator<_Cp, _IsConst> first, __bit_iterator<_Cp, _IsConst> last, __bit_iterator<_Cp, false> result)
{
    using _In = __bit_iterator<_Cp, _IsConst>;
    using difference_type = typename _In::difference_type;
    using __storage_type = typename _In::__storage_type;

    const int bits_per_word = _In::__bits_per_word;
    difference_type n = last - first;
    if (n > 0) {
        // do first word
        if (first.__ctz_ != 0) {
            unsigned clz_f = bits_per_word - first.__ctz_;
            difference_type dn = min(static_cast<difference_type>(clz_f), n);
            n -= dn;
            __storage_type m = (~__storage_type(0) << first.__ctz_) & (~__storage_type(0) >> (clz_f - dn));
            __storage_type b = *first.__seg_ & m;
            unsigned clz_r = bits_per_word - result.__ctz_;
            __storage_type ddn =
                static_cast<__storage_type>(min<difference_type>(dn, static_cast<difference_type>(clz_r)));
            m = (~__storage_type(0) << result.__ctz_) & (~__storage_type(0) >> (clz_r - ddn));
            *result.__seg_ &= ~m;
            if (result.__ctz_ > first.__ctz_) {
                *result.__seg_ |= b << (result.__ctz_ - first.__ctz_);
            } else {
                *result.__seg_ |= b >> (first.__ctz_ - result.__ctz_);
            }
            result.__seg_ += (ddn + result.__ctz_) / bits_per_word;
            result.__ctz_ = static_cast<unsigned>((ddn + result.__ctz_) % bits_per_word);
            dn -= ddn;
            if (dn > 0) {
                m = ~__storage_type(0) >> (bits_per_word - dn);
                *result.__seg_ &= ~m;
                *result.__seg_ |= b >> (first.__ctz_ + ddn);
                result.__ctz_ = static_cast<unsigned>(dn);
            }
            ++first.__seg_;
            // first.__ctz_ = 0;
        }
        // first.__ctz_ == 0;
        // do middle words
        unsigned clz_r = bits_per_word - result.__ctz_;
        __storage_type m = ~__storage_type(0) << result.__ctz_;
        for (; n >= bits_per_word; n -= bits_per_word, ++first.__seg_) {
            __storage_type b = *first.__seg_;
            *result.__seg_ &= ~m;
            *result.__seg_ |= b << result.__ctz_;
            ++result.__seg_;
            *result.__seg_ &= m;
            *result.__seg_ |= b >> clz_r;
        }
        // do last word
        if (n > 0) {
            m = ~__storage_type(0) >> (bits_per_word - n);
            __storage_type b = *first.__seg_ & m;
            __storage_type dn = static_cast<__storage_type>(min(n, static_cast<difference_type>(clz_r)));
            m = (~__storage_type(0) << result.__ctz_) & (~__storage_type(0) >> (clz_r - dn));
            *result.__seg_ &= ~m;
            *result.__seg_ |= b << result.__ctz_;
            result.__seg_ += (dn + result.__ctz_) / bits_per_word;
            result.__ctz_ = static_cast<unsigned>((dn + result.__ctz_) % bits_per_word);
            n -= dn;
            if (n > 0) {
                m = ~__storage_type(0) >> (bits_per_word - n);
                *result.__seg_ &= ~m;
                *result.__seg_ |= b >> dn;
                result.__ctz_ = static_cast<unsigned>(n);
            }
        }
    }
    return result;
}

template <class _Cp, bool _IsConst>
CANN_ASC_STL_API constexpr __bit_iterator<_Cp, false> copy(
    __bit_iterator<_Cp, _IsConst> first, __bit_iterator<_Cp, _IsConst> last, __bit_iterator<_Cp, false> result)
{
    if (first.__ctz_ == result.__ctz_) {
        return __copy_aligned(first, last, result);
    }
    return __copy_unaligned(first, last, result);
}

// copy_backward

template <class _Cp, bool _IsConst>
CANN_ASC_STL_API constexpr __bit_iterator<_Cp, false> __copy_backward_aligned(
    __bit_iterator<_Cp, _IsConst> first, __bit_iterator<_Cp, _IsConst> last, __bit_iterator<_Cp, false> result)
{
    using _In = __bit_iterator<_Cp, _IsConst>;
    using difference_type = typename _In::difference_type;
    using __storage_type = typename _In::__storage_type;

    const int bits_per_word = _In::__bits_per_word;
    difference_type n = last - first;
    if (n > 0) {
        // do first word
        if (last.__ctz_ != 0) {
            difference_type dn = min(static_cast<difference_type>(last.__ctz_), n);
            n -= dn;
            unsigned clz_f = bits_per_word - last.__ctz_;
            __storage_type m = (~__storage_type(0) << (last.__ctz_ - dn)) & (~__storage_type(0) >> clz_f);
            __storage_type b = *last.__seg_ & m;
            *result.__seg_ &= ~m;
            *result.__seg_ |= b;
            result.__ctz_ = static_cast<unsigned>(((-dn & (bits_per_word - 1)) + result.__ctz_) % bits_per_word);
            // last.__ctz_ = 0
        }
        // last.__ctz_ == 0 || n == 0
        // result.__ctz_ == 0 || n == 0
        // do middle words
        __storage_type nw = n / bits_per_word;
        result.__seg_ -= static_cast<difference_type>(nw);
        last.__seg_ -= static_cast<difference_type>(nw);
        copy_n(last.__seg_, static_cast<typename _In::difference_type>(nw), result.__seg_);
        n -= static_cast<difference_type>(nw * bits_per_word);
        // do last word
        if (n > 0) {
            __storage_type m = ~__storage_type(0) << (bits_per_word - n);
#if CANN_ASC_STL_DETAIL_BIT_REF_GCC_PRE9
            // workaround for GCC pre-9 being really bad at tracking one-past-the-end pointers at constexpr
            // can't check for is-constant-evaluated, because GCC pre-9 also lacks _that_.
            if (last.__seg_ == first.__seg_ + 1) {
                last.__seg_ = first.__seg_;
            } else {
                --last.__seg_;
            }
#else   // GCC < 9
            --last.__seg_;
#endif  // !GCC || GCC >= 9
            __storage_type b = *last.__seg_ & m;
#if CANN_ASC_STL_DETAIL_BIT_REF_GCC_PRE9
            // workaround for GCC pre-9 being really bad at tracking one-past-the-end pointers at constexpr
            // can't check for is-constant-evaluated, because GCC pre-9 also lacks _that_.
            if (result.__seg_ == first.__seg_ + 1) {
                result.__seg_ = first.__seg_;
            } else {
                --result.__seg_;
            }
#else   // GCC < 9
            --result.__seg_;
#endif  // !GCC || GCC >= 9
            *result.__seg_ &= ~m;
            *result.__seg_ |= b;
            result.__ctz_ = static_cast<unsigned>(-n & (bits_per_word - 1));
        }
    }
    return result;
}

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4146)  // unary minus applied to unsigned type

template <class _Cp, bool _IsConst>
CANN_ASC_STL_API constexpr __bit_iterator<_Cp, false> __copy_backward_unaligned(
    __bit_iterator<_Cp, _IsConst> first, __bit_iterator<_Cp, _IsConst> last, __bit_iterator<_Cp, false> result)
{
    using _In = __bit_iterator<_Cp, _IsConst>;
    using difference_type = typename _In::difference_type;
    using __storage_type = typename _In::__storage_type;

    const int bits_per_word = _In::__bits_per_word;
    difference_type n = last - first;
    if (n > 0) {
        // do first word
        if (last.__ctz_ != 0) {
            difference_type dn = min(static_cast<difference_type>(last.__ctz_), n);
            n -= dn;
            unsigned clz_l = bits_per_word - last.__ctz_;
            __storage_type m = (~__storage_type(0) << (last.__ctz_ - dn)) & (~__storage_type(0) >> clz_l);
            __storage_type b = *last.__seg_ & m;
            unsigned clz_r = bits_per_word - result.__ctz_;
            __storage_type ddn = static_cast<__storage_type>(min(dn, static_cast<difference_type>(result.__ctz_)));
            if (ddn > 0) {
                m = (~__storage_type(0) << (result.__ctz_ - ddn)) & (~__storage_type(0) >> clz_r);
                *result.__seg_ &= ~m;
                if (result.__ctz_ > last.__ctz_) {
                    *result.__seg_ |= b << (result.__ctz_ - last.__ctz_);
                } else {
                    *result.__seg_ |= b >> (last.__ctz_ - result.__ctz_);
                }
                result.__ctz_ = static_cast<unsigned>(((-ddn & (bits_per_word - 1)) + result.__ctz_) % bits_per_word);
                dn -= ddn;
            }
            if (dn > 0) {
                // result.__ctz_ == 0
#if CANN_ASC_STL_DETAIL_BIT_REF_GCC_PRE9
                // workaround for GCC pre-9 being really bad at tracking one-past-the-end pointers at constexpr
                // can't check for is-constant-evaluated, because GCC pre-9 also lacks _that_.
                if (result.__seg_ == first.__seg_ + 1) {
                    result.__seg_ = first.__seg_;
                } else {
                    --result.__seg_;
                }
#else   // GCC < 9
                --result.__seg_;
#endif  // !GCC || GCC >= 9
                CANN_ASC_STL_DETAIL_DIAG_PUSH
                CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4146)  // unary minus applied to unsigned type
                result.__ctz_ = static_cast<unsigned>(-dn & (bits_per_word - 1));
                CANN_ASC_STL_DETAIL_DIAG_POP
                m = ~__storage_type(0) << result.__ctz_;
                *result.__seg_ &= ~m;
                last.__ctz_ -= static_cast<unsigned>(dn + ddn);
                *result.__seg_ |= b << (result.__ctz_ - last.__ctz_);
            }
            // last.__ctz_ = 0
        }
        // last.__ctz_ == 0 || n == 0
        // result.__ctz_ != 0 || n == 0
        // do middle words
        unsigned clz_r = bits_per_word - result.__ctz_;
        __storage_type m = ~__storage_type(0) >> clz_r;
        for (; n >= bits_per_word; n -= bits_per_word) {
            __storage_type b = *--last.__seg_;
            *result.__seg_ &= ~m;
            *result.__seg_ |= b >> clz_r;
            *--result.__seg_ &= m;
            *result.__seg_ |= b << result.__ctz_;
        }
        // do last word
        if (n > 0) {
            m = ~__storage_type(0) << (bits_per_word - n);
            __storage_type b = *--last.__seg_ & m;
            clz_r = bits_per_word - result.__ctz_;
            __storage_type dn = static_cast<__storage_type>(min(n, static_cast<difference_type>(result.__ctz_)));
            m = (~__storage_type(0) << (result.__ctz_ - dn)) & (~__storage_type(0) >> clz_r);
            *result.__seg_ &= ~m;
            *result.__seg_ |= b >> (bits_per_word - result.__ctz_);
            result.__ctz_ = static_cast<unsigned>(((-dn & (bits_per_word - 1)) + result.__ctz_) % bits_per_word);
            n -= dn;
            if (n > 0) {
                // result.__ctz_ == 0
                --result.__seg_;
                result.__ctz_ = static_cast<unsigned>(-n & (bits_per_word - 1));
                m = ~__storage_type(0) << result.__ctz_;
                *result.__seg_ &= ~m;
                *result.__seg_ |= b << (result.__ctz_ - (bits_per_word - n - dn));
            }
        }
    }
    return result;
}

CANN_ASC_STL_DETAIL_DIAG_POP

template <class _Cp, bool _IsConst>
CANN_ASC_STL_API constexpr __bit_iterator<_Cp, false> copy_backward(
    __bit_iterator<_Cp, _IsConst> first, __bit_iterator<_Cp, _IsConst> last, __bit_iterator<_Cp, false> result)
{
    if (last.__ctz_ == result.__ctz_) {
        return __copy_backward_aligned(first, last, result);
    }
    return __copy_backward_unaligned(first, last, result);
}

// move

template <class _Cp, bool _IsConst>
CANN_ASC_STL_API __bit_iterator<_Cp, false> move(
    __bit_iterator<_Cp, _IsConst> first, __bit_iterator<_Cp, _IsConst> last, __bit_iterator<_Cp, false> result)
{
    return copy(first, last, result);
}

// move_backward

template <class _Cp, bool _IsConst>
CANN_ASC_STL_API __bit_iterator<_Cp, false> move_backward(
    __bit_iterator<_Cp, _IsConst> first, __bit_iterator<_Cp, _IsConst> last, __bit_iterator<_Cp, false> result)
{
    return copy_backward(first, last, result);
}

// swap_ranges

template <class _Cl, class _Cr>
CANN_ASC_STL_API __bit_iterator<_Cr, false> __swap_ranges_aligned(
    __bit_iterator<_Cl, false> first, __bit_iterator<_Cl, false> last, __bit_iterator<_Cr, false> result)
{
    using _I1 = __bit_iterator<_Cl, false>;
    using difference_type = typename _I1::difference_type;
    using __storage_type = typename _I1::__storage_type;

    const int bits_per_word = _I1::__bits_per_word;
    difference_type n = last - first;
    if (n > 0) {
        // do first word
        if (first.__ctz_ != 0) {
            unsigned clz_f = bits_per_word - first.__ctz_;
            difference_type dn = min(static_cast<difference_type>(clz_f), n);
            n -= dn;
            __storage_type m = (~__storage_type(0) << first.__ctz_) & (~__storage_type(0) >> (clz_f - dn));
            __storage_type b1 = *first.__seg_ & m;
            *first.__seg_ &= ~m;
            __storage_type b2 = *result.__seg_ & m;
            *result.__seg_ &= ~m;
            *result.__seg_ |= b1;
            *first.__seg_ |= b2;
            result.__seg_ += (dn + result.__ctz_) / bits_per_word;
            result.__ctz_ = static_cast<unsigned>((dn + result.__ctz_) % bits_per_word);
            ++first.__seg_;
            // first.__ctz_ = 0;
        }
        // first.__ctz_ == 0;
        // do middle words
        for (; n >= bits_per_word; n -= bits_per_word, ++first.__seg_, ++result.__seg_) {
            swap(*first.__seg_, *result.__seg_);  // NOLINT(build/include_what_you_use)
        }
        // do last word
        if (n > 0) {
            __storage_type m = ~__storage_type(0) >> (bits_per_word - n);
            __storage_type b1 = *first.__seg_ & m;
            *first.__seg_ &= ~m;
            __storage_type b2 = *result.__seg_ & m;
            *result.__seg_ &= ~m;
            *result.__seg_ |= b1;
            *first.__seg_ |= b2;
            result.__ctz_ = static_cast<unsigned>(n);
        }
    }
    return result;
}

template <class _Cl, class _Cr>
CANN_ASC_STL_API __bit_iterator<_Cr, false> __swap_ranges_unaligned(
    __bit_iterator<_Cl, false> first, __bit_iterator<_Cl, false> last, __bit_iterator<_Cr, false> result)
{
    using _I1 = __bit_iterator<_Cl, false>;
    using difference_type = typename _I1::difference_type;
    using __storage_type = typename _I1::__storage_type;

    const int bits_per_word = _I1::__bits_per_word;
    difference_type n = last - first;
    if (n > 0) {
        // do first word
        if (first.__ctz_ != 0) {
            unsigned clz_f = bits_per_word - first.__ctz_;
            difference_type dn = min(static_cast<difference_type>(clz_f), n);
            n -= dn;
            __storage_type m = (~__storage_type(0) << first.__ctz_) & (~__storage_type(0) >> (clz_f - dn));
            __storage_type b1 = *first.__seg_ & m;
            *first.__seg_ &= ~m;
            unsigned clz_r = bits_per_word - result.__ctz_;
            __storage_type ddn =
                static_cast<__storage_type>(min<difference_type>(dn, static_cast<difference_type>(clz_r)));
            m = (~__storage_type(0) << result.__ctz_) & (~__storage_type(0) >> (clz_r - ddn));
            __storage_type b2 = *result.__seg_ & m;
            *result.__seg_ &= ~m;
            if (result.__ctz_ > first.__ctz_) {
                unsigned s = result.__ctz_ - first.__ctz_;
                *result.__seg_ |= b1 << s;
                *first.__seg_ |= b2 >> s;
            } else {
                unsigned s = first.__ctz_ - result.__ctz_;
                *result.__seg_ |= b1 >> s;
                *first.__seg_ |= b2 << s;
            }
            result.__seg_ += (ddn + result.__ctz_) / bits_per_word;
            result.__ctz_ = static_cast<unsigned>((ddn + result.__ctz_) % bits_per_word);
            dn -= ddn;
            if (dn > 0) {
                m = ~__storage_type(0) >> (bits_per_word - dn);
                b2 = *result.__seg_ & m;
                *result.__seg_ &= ~m;
                unsigned s = first.__ctz_ + ddn;
                *result.__seg_ |= b1 >> s;
                *first.__seg_ |= b2 << s;
                result.__ctz_ = static_cast<unsigned>(dn);
            }
            ++first.__seg_;
            // first.__ctz_ = 0;
        }
        // first.__ctz_ == 0;
        // do middle words
        __storage_type m = ~__storage_type(0) << result.__ctz_;
        unsigned clz_r = bits_per_word - result.__ctz_;
        for (; n >= bits_per_word; n -= bits_per_word, ++first.__seg_) {
            __storage_type b1 = *first.__seg_;
            __storage_type b2 = *result.__seg_ & m;
            *result.__seg_ &= ~m;
            *result.__seg_ |= b1 << result.__ctz_;
            *first.__seg_ = b2 >> result.__ctz_;
            ++result.__seg_;
            b2 = *result.__seg_ & ~m;
            *result.__seg_ &= m;
            *result.__seg_ |= b1 >> clz_r;
            *first.__seg_ |= b2 << clz_r;
        }
        // do last word
        if (n > 0) {
            m = ~__storage_type(0) >> (bits_per_word - n);
            __storage_type b1 = *first.__seg_ & m;
            *first.__seg_ &= ~m;
            __storage_type dn =
                static_cast<__storage_type>(min<difference_type>(n, static_cast<difference_type>(clz_r)));
            m = (~__storage_type(0) << result.__ctz_) & (~__storage_type(0) >> (clz_r - dn));
            __storage_type b2 = *result.__seg_ & m;
            *result.__seg_ &= ~m;
            *result.__seg_ |= b1 << result.__ctz_;
            *first.__seg_ |= b2 >> result.__ctz_;
            result.__seg_ += (dn + result.__ctz_) / bits_per_word;
            result.__ctz_ = static_cast<unsigned>((dn + result.__ctz_) % bits_per_word);
            n -= dn;
            if (n > 0) {
                m = ~__storage_type(0) >> (bits_per_word - n);
                b2 = *result.__seg_ & m;
                *result.__seg_ &= ~m;
                *result.__seg_ |= b1 >> dn;
                *first.__seg_ |= b2 << dn;
                result.__ctz_ = static_cast<unsigned>(n);
            }
        }
    }
    return result;
}

template <class _Cl, class _Cr>
CANN_ASC_STL_API __bit_iterator<_Cr, false> swap_ranges(
    __bit_iterator<_Cl, false> first1, __bit_iterator<_Cl, false> last1, __bit_iterator<_Cr, false> first2)
{
    if (first1.__ctz_ == first2.__ctz_) {
        return __swap_ranges_aligned(first1, last1, first2);
    }
    return __swap_ranges_unaligned(first1, last1, first2);
}

// rotate

template <class _Cp>
struct __bit_array {
    using difference_type = typename _Cp::difference_type;
    using __storage_type = typename _Cp::__storage_type;
    using __storage_pointer = typename _Cp::__storage_pointer;
    using iterator = typename _Cp::iterator;

    static const unsigned __bits_per_word = _Cp::__bits_per_word;
    static const unsigned _Np = 4;

    difference_type __size_;
    __storage_type __word_[_Np];

    CANN_ASC_STL_API constexpr static difference_type capacity()
    {
        return static_cast<difference_type>(_Np * __bits_per_word);
    }
    CANN_ASC_STL_API constexpr explicit __bit_array(difference_type s) : __size_(s), __word_()
    {}
    CANN_ASC_STL_API constexpr iterator begin()
    {
        return iterator(pointer_traits<__storage_pointer>::pointer_to(__word_[0]), 0);
    }
    CANN_ASC_STL_API constexpr iterator end()
    {
        return iterator(pointer_traits<__storage_pointer>::pointer_to(__word_[0]) + __size_ / __bits_per_word,
            static_cast<unsigned>(__size_ % __bits_per_word));
    }
};

template <class _Cp>
CANN_ASC_STL_API constexpr __bit_iterator<_Cp, false> rotate(
    __bit_iterator<_Cp, false> first, __bit_iterator<_Cp, false> middle, __bit_iterator<_Cp, false> last)
{
    using _I1 = __bit_iterator<_Cp, false>;
    using difference_type = typename _I1::difference_type;

    difference_type d1 = middle - first;
    difference_type d2 = last - middle;
    _I1 r = first + d2;
    while (d1 != 0 && d2 != 0) {
        if (d1 <= d2) {
            if (d1 <= __bit_array<_Cp>::capacity()) {
                __bit_array<_Cp> b(d1);
                copy(first, middle, b.begin());
                copy(b.begin(), b.end(), copy(middle, last, first));
                break;
            } else {
                __bit_iterator<_Cp, false> mp = swap_ranges(first, middle, middle);
                first = middle;
                middle = mp;
                d2 -= d1;
            }
        } else {
            if (d2 <= __bit_array<_Cp>::capacity()) {
                __bit_array<_Cp> b(d2);
                copy(middle, last, b.begin());
                copy_backward(b.begin(), b.end(), copy_backward(first, middle, last));
                break;
            } else {
                __bit_iterator<_Cp, false> mp = first + d2;
                swap_ranges(first, mp, middle);
                first = mp;
                d1 -= d2;
            }
        }
    }
    return r;
}

// equal

template <class _Cp, bool _IC1, bool _IC2>
CANN_ASC_STL_API constexpr bool __equal_unaligned(
    __bit_iterator<_Cp, _IC1> first1, __bit_iterator<_Cp, _IC1> last1, __bit_iterator<_Cp, _IC2> first2)
{
    using _It = __bit_iterator<_Cp, _IC1>;
    using difference_type = typename _It::difference_type;
    using __storage_type = typename _It::__storage_type;

    const int bits_per_word = _It::__bits_per_word;
    difference_type n = last1 - first1;
    if (n > 0) {
        // do first word
        if (first1.__ctz_ != 0) {
            unsigned clz_f = bits_per_word - first1.__ctz_;
            // NOLINTNEXTLINE(build/include_what_you_use)
            difference_type dn = min(static_cast<difference_type>(clz_f), n);
            n -= dn;
            __storage_type m = (~__storage_type(0) << first1.__ctz_) & (~__storage_type(0) >> (clz_f - dn));
            __storage_type b = *first1.__seg_ & m;
            unsigned clz_r = bits_per_word - first2.__ctz_;
            __storage_type ddn =
                static_cast<__storage_type>(min<difference_type>(dn, static_cast<difference_type>(clz_r)));
            m = (~__storage_type(0) << first2.__ctz_) & (~__storage_type(0) >> (clz_r - ddn));
            if (first2.__ctz_ > first1.__ctz_) {
                if ((*first2.__seg_ & m) != (b << (first2.__ctz_ - first1.__ctz_))) {
                    return false;
                }
            } else {
                if ((*first2.__seg_ & m) != (b >> (first1.__ctz_ - first2.__ctz_))) {
                    return false;
                }
            }
            first2.__seg_ += (ddn + first2.__ctz_) / bits_per_word;
            first2.__ctz_ = static_cast<unsigned>((ddn + first2.__ctz_) % bits_per_word);
            dn -= ddn;
            if (dn > 0) {
                m = ~__storage_type(0) >> (bits_per_word - dn);
                if ((*first2.__seg_ & m) != (b >> (first1.__ctz_ + ddn))) {
                    return false;
                }
                first2.__ctz_ = static_cast<unsigned>(dn);
            }
            ++first1.__seg_;
            // first1.__ctz_ = 0;
        }
        // first1.__ctz_ == 0;
        // do middle words
        unsigned clz_r = bits_per_word - first2.__ctz_;
        __storage_type m = ~__storage_type(0) << first2.__ctz_;
        bool result = true;
        for (; n >= bits_per_word; n -= bits_per_word, ++first1.__seg_) {
            __storage_type b = *first1.__seg_;
            if ((*first2.__seg_ & m) != (b << first2.__ctz_)) {
                result = false;
                break;
            }
            ++first2.__seg_;
            if ((*first2.__seg_ & ~m) != (b >> clz_r)) {
                result = false;
                break;
            }
        }
        if (!result) {
            return false;
        }

        // do last word
        if (n > 0) {
            m = ~__storage_type(0) >> (bits_per_word - n);
            __storage_type b = *first1.__seg_ & m;
            __storage_type dn = static_cast<__storage_type>(min(n, static_cast<difference_type>(clz_r)));
            m = (~__storage_type(0) << first2.__ctz_) & (~__storage_type(0) >> (clz_r - dn));
            if ((*first2.__seg_ & m) != (b << first2.__ctz_)) {
                return false;
            }
            first2.__seg_ += (dn + first2.__ctz_) / bits_per_word;
            first2.__ctz_ = static_cast<unsigned>((dn + first2.__ctz_) % bits_per_word);
            n -= dn;
            if (n > 0) {
                m = ~__storage_type(0) >> (bits_per_word - n);
                if ((*first2.__seg_ & m) != (b >> dn)) {
                    return false;
                }
            }
        }
    }
    return true;
}

template <class _Cp, bool _IC1, bool _IC2>
CANN_ASC_STL_API constexpr bool __equal_aligned(
    __bit_iterator<_Cp, _IC1> first1, __bit_iterator<_Cp, _IC1> last1, __bit_iterator<_Cp, _IC2> first2)
{
    using _It = __bit_iterator<_Cp, _IC1>;
    using difference_type = typename _It::difference_type;
    using __storage_type = typename _It::__storage_type;

    const int bits_per_word = _It::__bits_per_word;
    difference_type n = last1 - first1;
    if (n > 0) {
        // do first word
        if (first1.__ctz_ != 0) {
            unsigned clz_f = bits_per_word - first1.__ctz_;
            // NOLINTNEXTLINE(build/include_what_you_use)
            difference_type dn = min(static_cast<difference_type>(clz_f), n);
            n -= dn;
            __storage_type m = (~__storage_type(0) << first1.__ctz_) & (~__storage_type(0) >> (clz_f - dn));
            if ((*first2.__seg_ & m) != (*first1.__seg_ & m)) {
                return false;
            }
            ++first2.__seg_;
            ++first1.__seg_;
            // first1.__ctz_ = 0;
            // first2.__ctz_ = 0;
        }
        // first1.__ctz_ == 0;
        // first2.__ctz_ == 0;
        // do middle words
        bool result = true;
        for (; n >= bits_per_word; n -= bits_per_word, ++first1.__seg_, ++first2.__seg_) {
            if (*first2.__seg_ != *first1.__seg_) {
                result = false;
                break;
            }
        }
        if (!result) {
            return false;
        }

        // do last word
        if (n > 0) {
            __storage_type m = ~__storage_type(0) >> (bits_per_word - n);
            if ((*first2.__seg_ & m) != (*first1.__seg_ & m)) {
                return false;
            }
        }
    }
    return true;
}

template <class _Cp, bool _IC1, bool _IC2>
CANN_ASC_STL_API constexpr bool equal(
    __bit_iterator<_Cp, _IC1> first1, __bit_iterator<_Cp, _IC1> last1, __bit_iterator<_Cp, _IC2> first2)
{
    if (first1.__ctz_ == first2.__ctz_) {
        return __equal_aligned(first1, last1, first2);
    }
    return __equal_unaligned(first1, last1, first2);
}

template <class _Cp, bool _IsConst>
class __bit_iterator {
public:
    using difference_type = typename _Cp::difference_type;
    using value_type = bool;
    using pointer = __bit_iterator;
    using reference = conditional_t<_IsConst, __bit_const_reference<_Cp>, __bit_reference<_Cp>>;
    using iterator_category = random_access_iterator_tag;

private:
    using __storage_type = typename _Cp::__storage_type;
    using __storage_pointer =
        conditional_t<_IsConst, typename _Cp::__const_storage_pointer, typename _Cp::__storage_pointer>;

    static const unsigned __bits_per_word = _Cp::__bits_per_word;

    __storage_pointer __seg_;
    unsigned __ctz_;

public:
    CANN_ASC_STL_API constexpr __bit_iterator() noexcept : __seg_(nullptr), __ctz_(0)
    {}

    constexpr __bit_iterator(const __bit_iterator<_Cp, _IsConst>& it) = default;

    template <bool _OtherIsConst, class = enable_if_t<_IsConst == true && _OtherIsConst == false>>
    CANN_ASC_STL_API constexpr __bit_iterator(const __bit_iterator<_Cp, _OtherIsConst>& it) noexcept
        : __seg_(it.__seg_), __ctz_(it.__ctz_)
    {}

    CANN_ASC_STL_API constexpr reference operator*() const noexcept
    {
        return reference(__seg_, __storage_type(1) << __ctz_);
    }

    CANN_ASC_STL_API constexpr __bit_iterator& operator++()
    {
        if (__ctz_ != __bits_per_word - 1) {
            ++__ctz_;
        } else {
            __ctz_ = 0;
            ++__seg_;
        }
        return *this;
    }

    CANN_ASC_STL_API constexpr __bit_iterator operator++(int)
    {
        __bit_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    CANN_ASC_STL_API constexpr __bit_iterator& operator--()
    {
        if (__ctz_ != 0) {
            --__ctz_;
        } else {
            __ctz_ = __bits_per_word - 1;
            --__seg_;
        }
        return *this;
    }

    CANN_ASC_STL_API constexpr __bit_iterator operator--(int)
    {
        __bit_iterator tmp = *this;
        --(*this);
        return tmp;
    }

    CANN_ASC_STL_API constexpr __bit_iterator& operator+=(difference_type n)
    {
        if (n >= 0) {
            __seg_ += (n + __ctz_) / __bits_per_word;
        } else {
            __seg_ += static_cast<difference_type>(n - static_cast<difference_type>(__bits_per_word) + __ctz_ + 1) /
                static_cast<difference_type>(__bits_per_word);
        }
        n &= (__bits_per_word - 1);
        __ctz_ = static_cast<unsigned>((n + __ctz_) % __bits_per_word);
        return *this;
    }

    CANN_ASC_STL_API constexpr __bit_iterator& operator-=(difference_type n)
    {
        return *this += -n;
    }

    CANN_ASC_STL_API constexpr __bit_iterator operator+(difference_type n) const
    {
        __bit_iterator t(*this);
        t += n;
        return t;
    }

    CANN_ASC_STL_API constexpr __bit_iterator operator-(difference_type n) const
    {
        __bit_iterator t(*this);
        t -= n;
        return t;
    }

    CANN_ASC_STL_API constexpr friend __bit_iterator operator+(difference_type n, const __bit_iterator& it)
    {
        return it + n;
    }

    CANN_ASC_STL_API constexpr friend difference_type operator-(const __bit_iterator& x, const __bit_iterator& y)
    {
#if CANN_ASC_STL_DETAIL_BIT_REF_GCC_PRE9 && __GNUC__ >= 8
        // workaround for GCC 8 being really bad at tracking one-past-the-end pointers at constexpr
        if (y.__seg_ && y.__seg_ != x.__seg_) {
            return (x.__seg_ == y.__seg_ + 1 ? 1 : x.__seg_ - y.__seg_) * __bits_per_word + x.__ctz_ - y.__ctz_;
        }
#endif  // GCC [8, 9)
        return (x.__seg_ - y.__seg_) * __bits_per_word + x.__ctz_ - y.__ctz_;
    }

    CANN_ASC_STL_API constexpr reference operator[](difference_type n) const
    {
        return *(*this + n);
    }

    CANN_ASC_STL_API constexpr friend bool operator==(const __bit_iterator& x, const __bit_iterator& y)
    {
        return x.__seg_ == y.__seg_ && x.__ctz_ == y.__ctz_;
    }

    CANN_ASC_STL_API constexpr friend bool operator!=(const __bit_iterator& x, const __bit_iterator& y)
    {
        return !(x == y);
    }

    CANN_ASC_STL_API constexpr friend bool operator<(const __bit_iterator& x, const __bit_iterator& y)
    {
        return x.__seg_ < y.__seg_ || (x.__seg_ == y.__seg_ && x.__ctz_ < y.__ctz_);
    }

    CANN_ASC_STL_API constexpr friend bool operator>(const __bit_iterator& x, const __bit_iterator& y)
    {
        return y < x;
    }

    CANN_ASC_STL_API constexpr friend bool operator<=(const __bit_iterator& x, const __bit_iterator& y)
    {
        return !(y < x);
    }

    CANN_ASC_STL_API constexpr friend bool operator>=(const __bit_iterator& x, const __bit_iterator& y)
    {
        return !(x < y);
    }

private:
    CANN_ASC_STL_API constexpr explicit __bit_iterator(__storage_pointer s, unsigned ctz) noexcept
        : __seg_(s), __ctz_(ctz)
    {}

    friend typename _Cp::__self;

    friend class __bit_reference<_Cp>;
    friend class __bit_const_reference<_Cp>;
    friend class __bit_iterator<_Cp, true>;
    template <class _Dp>
    friend struct __bit_array;
    template <bool _FillVal, class _Dp>
    CANN_ASC_STL_API constexpr friend void __fill_n_impl(__bit_iterator<_Dp, false> first, typename _Dp::size_type n);

    template <class _Dp, bool _IC>
    CANN_ASC_STL_API constexpr friend __bit_iterator<_Dp, false> __copy_aligned(
        __bit_iterator<_Dp, _IC> first, __bit_iterator<_Dp, _IC> last, __bit_iterator<_Dp, false> result);
    template <class _Dp, bool _IC>
    CANN_ASC_STL_API constexpr friend __bit_iterator<_Dp, false> __copy_unaligned(
        __bit_iterator<_Dp, _IC> first, __bit_iterator<_Dp, _IC> last, __bit_iterator<_Dp, false> result);
    template <class _Dp, bool _IC>
    CANN_ASC_STL_API constexpr friend __bit_iterator<_Dp, false> copy(
        __bit_iterator<_Dp, _IC> first, __bit_iterator<_Dp, _IC> last, __bit_iterator<_Dp, false> result);
    template <class _Dp, bool _IC>
    CANN_ASC_STL_API constexpr friend __bit_iterator<_Dp, false> __copy_backward_aligned(
        __bit_iterator<_Dp, _IC> first, __bit_iterator<_Dp, _IC> last, __bit_iterator<_Dp, false> result);
    template <class _Dp, bool _IC>
    CANN_ASC_STL_API constexpr friend __bit_iterator<_Dp, false> __copy_backward_unaligned(
        __bit_iterator<_Dp, _IC> first, __bit_iterator<_Dp, _IC> last, __bit_iterator<_Dp, false> result);
    template <class _Dp, bool _IC>
    CANN_ASC_STL_API constexpr friend __bit_iterator<_Dp, false> copy_backward(
        __bit_iterator<_Dp, _IC> first, __bit_iterator<_Dp, _IC> last, __bit_iterator<_Dp, false> result);
    template <class _Cl2, class _Cr2>
    CANN_ASC_STL_API friend __bit_iterator<_Cr2, false> __swap_ranges_aligned(
        __bit_iterator<_Cl2, false>, __bit_iterator<_Cl2, false>, __bit_iterator<_Cr2, false>);
    template <class _Cl2, class _Cr2>
    CANN_ASC_STL_API friend __bit_iterator<_Cr2, false> __swap_ranges_unaligned(
        __bit_iterator<_Cl2, false>, __bit_iterator<_Cl2, false>, __bit_iterator<_Cr2, false>);
    template <class _Cl2, class _Cr2>
    CANN_ASC_STL_API friend __bit_iterator<_Cr2, false> swap_ranges(
        __bit_iterator<_Cl2, false>, __bit_iterator<_Cl2, false>, __bit_iterator<_Cr2, false>);
    template <class _Dp>
    CANN_ASC_STL_API constexpr friend __bit_iterator<_Dp, false> rotate(
        __bit_iterator<_Dp, false>, __bit_iterator<_Dp, false>, __bit_iterator<_Dp, false>);
    template <class _Dp, bool _IC1, bool _IC2>
    CANN_ASC_STL_API constexpr friend bool __equal_aligned(
        __bit_iterator<_Dp, _IC1>, __bit_iterator<_Dp, _IC1>, __bit_iterator<_Dp, _IC2>);
    template <class _Dp, bool _IC1, bool _IC2>
    CANN_ASC_STL_API constexpr friend bool __equal_unaligned(
        __bit_iterator<_Dp, _IC1>, __bit_iterator<_Dp, _IC1>, __bit_iterator<_Dp, _IC2>);
    template <class _Dp, bool _IC1, bool _IC2>
    CANN_ASC_STL_API constexpr friend bool equal(
        __bit_iterator<_Dp, _IC1>, __bit_iterator<_Dp, _IC1>, __bit_iterator<_Dp, _IC2>);
    template <bool _ToFind, class _Dp, bool _IC>
    CANN_ASC_STL_API constexpr friend __bit_iterator<_Dp, _IC> __find_bool(
        __bit_iterator<_Dp, _IC>, typename _Dp::size_type);
    template <bool _ToCount, class _Dp, bool _IC>
    CANN_ASC_STL_API constexpr friend typename __bit_iterator<_Dp, _IC>::difference_type __count_bool(
        __bit_iterator<_Dp, _IC>, typename _Dp::size_type);
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_REFERENCE_H
