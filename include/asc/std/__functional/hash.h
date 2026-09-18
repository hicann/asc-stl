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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_HASH_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_HASH_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// No special library mode applies here: the main body always compiles. Sanitizer
// annotations and default-type-visibility hints have no ASC counterpart and are not
// carried over.
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/unary_function.h>
#include <asc/std/__fwd/hash.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/underlying_type.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/climits>
#include <asc/std/cstdint>
#include <asc/std/cstring>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Size>
CANN_ASC_STL_API _Size __loadword(const void* __p)
{
    _Size __r;
    ::asc::std::memcpy(&__r, __p, sizeof(__r));
    return __r;
}

// We use murmur2 when size_t is 32 bits, and cityhash64 when size_t
// is 64 bits.  This is because cityhash64 uses 64bit x 64bit
// multiplication, which can be very slow on 32-bit systems.
template <class _Size, size_t = sizeof(_Size) * CHAR_BIT>
struct __murmur2_or_cityhash;

template <class _Size>
struct __murmur2_or_cityhash<_Size, 32> {
    CANN_ASC_STL_API _Size operator()(const void* __key, _Size __len);
};

// murmur2
template <class _Size>
CANN_ASC_STL_API _Size __murmur2_or_cityhash<_Size, 32>::operator()(const void* __key, _Size __len)
{
    const _Size __m = 0x5bd1e995;
    const _Size __r = 24;
    _Size __h = __len;
    const unsigned char* __data = static_cast<const unsigned char*>(__key);
    for (; __len >= 4; __data += 4, __len -= 4) {
        _Size __k = __loadword<_Size>(__data);
        __k *= __m;
        __k ^= __k >> __r;
        __k *= __m;
        __h *= __m;
        __h ^= __k;
    }
    switch (__len) {
        case 3:
            __h ^= static_cast<_Size>(__data[2] << 16);
            [[fallthrough]];
        case 2:
            __h ^= static_cast<_Size>(__data[1] << 8);
            [[fallthrough]];
        case 1:
            __h ^= __data[0];
            __h *= __m;
    }
    __h ^= __h >> 13;
    __h *= __m;
    __h ^= __h >> 15;
    return __h;
}

template <class _Size>
struct __murmur2_or_cityhash<_Size, 64> {
    CANN_ASC_STL_API _Size operator()(const void* __key, _Size __len);

private:
    // Some primes between 2^63 and 2^64.
    static const _Size __k0 = 0xc3a5c85c97cb3127ULL;
    static const _Size __k1 = 0xb492b66fbe98f273ULL;
    static const _Size __k2 = 0x9ae16a3b2f90404fULL;
    static const _Size __k3 = 0xc949d7c7509e6557ULL;

    static CANN_ASC_STL_API _Size __rotate(_Size __val, int __shift)
    {
        return __shift == 0 ? __val : ((__val >> __shift) | (__val << (64 - __shift)));
    }

    static CANN_ASC_STL_API _Size __rotate_by_at_least_1(_Size __val, int __shift)
    {
        return (__val >> __shift) | (__val << (64 - __shift));
    }

    static CANN_ASC_STL_API _Size __shift_mix(_Size __val)
    {
        return __val ^ (__val >> 47);
    }

    static CANN_ASC_STL_API _Size __hash_len_16(_Size __u, _Size __v)
    {
        const _Size __mul = 0x9ddfea08eb382d69ULL;
        _Size __a = (__u ^ __v) * __mul;
        __a ^= (__a >> 47);
        _Size __b = (__v ^ __a) * __mul;
        __b ^= (__b >> 47);
        __b *= __mul;
        return __b;
    }

    static CANN_ASC_STL_API _Size __hash_len_0_to_16(const char* __s, _Size __len)
    {
        if (__len > 8) {
            const _Size __a = __loadword<_Size>(__s);
            const _Size __b = __loadword<_Size>(__s + __len - 8);
            return __hash_len_16(__a, __rotate_by_at_least_1(__b + __len, __len)) ^ __b;
        }
        if (__len >= 4) {
            const uint32_t __a = __loadword<uint32_t>(__s);
            const uint32_t __b = __loadword<uint32_t>(__s + __len - 4);
            return __hash_len_16(__len + (static_cast<_Size>(__a) << 3), __b);
        }
        if (__len > 0) {
            const unsigned char __a = static_cast<unsigned char>(__s[0]);
            const unsigned char __b = static_cast<unsigned char>(__s[__len >> 1]);
            const unsigned char __c = static_cast<unsigned char>(__s[__len - 1]);
            const uint32_t __y = static_cast<uint32_t>(__a) + (static_cast<uint32_t>(__b) << 8);
            const uint32_t __z = __len + (static_cast<uint32_t>(__c) << 2);
            return __shift_mix(__y * __k2 ^ __z * __k3) * __k2;
        }
        return __k2;
    }

    static CANN_ASC_STL_API _Size __hash_len_17_to_32(const char* __s, _Size __len)
    {
        const _Size __a = __loadword<_Size>(__s) * __k1;
        const _Size __b = __loadword<_Size>(__s + 8);
        const _Size __c = __loadword<_Size>(__s + __len - 8) * __k2;
        const _Size __d = __loadword<_Size>(__s + __len - 16) * __k0;
        return __hash_len_16(
            __rotate(__a - __b, 43) + __rotate(__c, 30) + __d, __a + __rotate(__b ^ __k3, 20) - __c + __len);
    }

    // Return a 16-byte hash for 48 bytes.  Quick and dirty.
    // Callers do best to use "random-looking" values for a and b.
    static CANN_ASC_STL_API pair<_Size, _Size> __weak_hash_len_32_with_seeds(
        _Size __w, _Size __x, _Size __y, _Size __z, _Size __a, _Size __b)
    {
        __a += __w;
        __b = __rotate(__b + __a + __z, 21);
        const _Size __c = __a;
        __a += __x;
        __a += __y;
        __b += __rotate(__a, 44);
        return pair<_Size, _Size>(__a + __z, __b + __c);
    }

    // Return a 16-byte hash for s[0] ... s[31], a, and b.  Quick and dirty.
    static CANN_ASC_STL_API pair<_Size, _Size> __weak_hash_len_32_with_seeds(const char* __s, _Size __a, _Size __b)
    {
        return __weak_hash_len_32_with_seeds(__loadword<_Size>(__s), __loadword<_Size>(__s + 8),
            __loadword<_Size>(__s + 16), __loadword<_Size>(__s + 24), __a, __b);
    }

    // Return an 8-byte hash for 33 to 64 bytes.
    static CANN_ASC_STL_API _Size __hash_len_33_to_64(const char* __s, size_t __len)
    {
        _Size __z = __loadword<_Size>(__s + 24);
        _Size __a = __loadword<_Size>(__s) + (__len + __loadword<_Size>(__s + __len - 16)) * __k0;
        _Size __b = __rotate(__a + __z, 52);
        _Size __c = __rotate(__a, 37);
        __a += __loadword<_Size>(__s + 8);
        __c += __rotate(__a, 7);
        __a += __loadword<_Size>(__s + 16);
        _Size __vf = __a + __z;
        _Size __vs = __b + __rotate(__a, 31) + __c;
        __a = __loadword<_Size>(__s + 16) + __loadword<_Size>(__s + __len - 32);
        __z += __loadword<_Size>(__s + __len - 8);
        __b = __rotate(__a + __z, 52);
        __c = __rotate(__a, 37);
        __a += __loadword<_Size>(__s + __len - 24);
        __c += __rotate(__a, 7);
        __a += __loadword<_Size>(__s + __len - 16);
        _Size __wf = __a + __z;
        _Size __ws = __b + __rotate(__a, 31) + __c;
        _Size __r = __shift_mix((__vf + __ws) * __k2 + (__wf + __vs) * __k0);
        return __shift_mix(__r * __k0 + __vs) * __k2;
    }
};

// cityhash64
template <class _Size>
CANN_ASC_STL_API _Size __murmur2_or_cityhash<_Size, 64>::operator()(const void* __key, _Size __len)
{
    const char* __s = static_cast<const char*>(__key);
    if (__len <= 32) {
        if (__len <= 16) {
            return __hash_len_0_to_16(__s, __len);
        } else {
            return __hash_len_17_to_32(__s, __len);
        }
    } else if (__len <= 64) {
        return __hash_len_33_to_64(__s, __len);
    }

    // For strings over 64 bytes we hash the end first, and then as we
    // loop we keep 56 bytes of state: v, w, x, y, and z.
    _Size __x = __loadword<_Size>(__s + __len - 40);
    _Size __y = __loadword<_Size>(__s + __len - 16) + __loadword<_Size>(__s + __len - 56);
    _Size __z = __hash_len_16(__loadword<_Size>(__s + __len - 48) + __len, __loadword<_Size>(__s + __len - 24));
    pair<_Size, _Size> __v = __weak_hash_len_32_with_seeds(__s + __len - 64, __len, __z);
    pair<_Size, _Size> __w = __weak_hash_len_32_with_seeds(__s + __len - 32, __y + __k1, __x);
    __x = __x * __k1 + __loadword<_Size>(__s);

    // Decrease len to the nearest multiple of 64, and operate on 64-byte chunks.
    __len = (__len - 1) & ~static_cast<_Size>(63);
    do {
        __x = __rotate(__x + __y + __v.first + __loadword<_Size>(__s + 8), 37) * __k1;
        __y = __rotate(__y + __v.second + __loadword<_Size>(__s + 48), 42) * __k1;
        __x ^= __w.second;
        __y += __v.first + __loadword<_Size>(__s + 40);
        __z = __rotate(__z + __w.first, 33) * __k1;
        __v = __weak_hash_len_32_with_seeds(__s, __v.second * __k1, __x + __w.first);
        __w = __weak_hash_len_32_with_seeds(__s + 32, __z + __w.second, __y + __loadword<_Size>(__s + 16));
        ::asc::std::swap(__z, __x);  // NOLINT(build/include_what_you_use)
        __s += 64;
        __len -= 64;
    } while (__len != 0);
    return __hash_len_16(__hash_len_16(__v.first, __w.first) + __shift_mix(__y) * __k1 + __z,
        __hash_len_16(__v.second, __w.second) + __x);
}

template <class _Tp, size_t = sizeof(_Tp) / sizeof(size_t)>
struct __scalar_hash;

template <class _Tp>
struct __scalar_hash<_Tp, 0> : public __unary_function<_Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(_Tp __v) const noexcept
    {
        union {
            _Tp __t;
            size_t __a;
        } __u;
        __u.__a = 0;
        __u.__t = __v;
        return __u.__a;
    }
};

template <class _Tp>
struct __scalar_hash<_Tp, 1> : public __unary_function<_Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(_Tp __v) const noexcept
    {
        union {
            _Tp __t;
            size_t __a;
        } __u;
        __u.__t = __v;
        return __u.__a;
    }
};

template <class _Tp>
struct __scalar_hash<_Tp, 2> : public __unary_function<_Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(_Tp __v) const noexcept
    {
        union {
            _Tp __t;
            struct {
                size_t __a;
                size_t __b;
            } __s;
        } __u;
        __u.__t = __v;
        return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
    }
};

template <class _Tp>
struct __scalar_hash<_Tp, 3> : public __unary_function<_Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(_Tp __v) const noexcept
    {
        union {
            _Tp __t;
            struct {
                size_t __a;
                size_t __b;
                size_t __c;
            } __s;
        } __u;
        __u.__t = __v;
        return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
    }
};

template <class _Tp>
struct __scalar_hash<_Tp, 4> : public __unary_function<_Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(_Tp __v) const noexcept
    {
        union {
            _Tp __t;
            struct {
                size_t __a;
                size_t __b;
                size_t __c;
                size_t __d;
            } __s;
        } __u;
        __u.__t = __v;
        return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
    }
};

struct _PairT {
    size_t first;
    size_t second;
};

CANN_ASC_STL_API size_t __hash_combine(size_t __lhs, size_t __rhs) noexcept
{
    using _HashT = __scalar_hash<_PairT>;
    const _PairT __p = {__lhs, __rhs};
    return _HashT()(__p);
}

template <class _Tp>
struct hash<_Tp*> : public __unary_function<_Tp*, size_t> {
    CANN_ASC_STL_API size_t operator()(_Tp* __v) const noexcept
    {
        union {
            _Tp* __t;
            size_t __a;
        } __u;
        __u.__t = __v;
        return __murmur2_or_cityhash<size_t>()(&__u, sizeof(__u));
    }
};

template <>
struct hash<bool> : public __unary_function<bool, size_t> {
    CANN_ASC_STL_API size_t operator()(bool __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<char> : public __unary_function<char, size_t> {
    CANN_ASC_STL_API size_t operator()(char __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<signed char> : public __unary_function<signed char, size_t> {
    CANN_ASC_STL_API size_t operator()(signed char __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<unsigned char> : public __unary_function<unsigned char, size_t> {
    CANN_ASC_STL_API size_t operator()(unsigned char __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<char16_t> : public __unary_function<char16_t, size_t> {
    CANN_ASC_STL_API size_t operator()(char16_t __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<char32_t> : public __unary_function<char32_t, size_t> {
    CANN_ASC_STL_API size_t operator()(char32_t __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<wchar_t> : public __unary_function<wchar_t, size_t> {
    CANN_ASC_STL_API size_t operator()(wchar_t __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<short> : public __unary_function<short, size_t> {
    CANN_ASC_STL_API size_t operator()(short __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<unsigned short> : public __unary_function<unsigned short, size_t> {
    CANN_ASC_STL_API size_t operator()(unsigned short __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<int> : public __unary_function<int, size_t> {
    CANN_ASC_STL_API size_t operator()(int __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<unsigned int> : public __unary_function<unsigned int, size_t> {
    CANN_ASC_STL_API size_t operator()(unsigned int __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<long> : public __unary_function<long, size_t> {
    CANN_ASC_STL_API size_t operator()(long __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<unsigned long> : public __unary_function<unsigned long, size_t> {
    CANN_ASC_STL_API size_t operator()(unsigned long __v) const noexcept
    {
        return static_cast<size_t>(__v);
    }
};

template <>
struct hash<long long> : public __scalar_hash<long long> {};

template <>
struct hash<unsigned long long> : public __scalar_hash<unsigned long long> {};

#if CANN_ASC_STL_DETAIL_HAS_INT128()

template <>
struct hash<__int128_t> : public __scalar_hash<__int128_t> {};

template <>
struct hash<__uint128_t> : public __scalar_hash<__uint128_t> {};

#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()

template <>
struct hash<float> : public __scalar_hash<float> {
    CANN_ASC_STL_API size_t operator()(float __v) const noexcept
    {
        // -0.0 and 0.0 should return same hash
        if (__v == 0.0f) {
            return 0;
        }
        return __scalar_hash<float>::operator()(__v);
    }
};

template <>
struct hash<double> : public __scalar_hash<double> {
    CANN_ASC_STL_API size_t operator()(double __v) const noexcept
    {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        // The AI Core forbids double-precision arithmetic: the ±0.0 normalization test is
        // unavailable, so this falls back to a pure bit-pattern hash (union bit copy, no
        // floating-point arithmetic; the device side has no meaningful double payload).
        return __scalar_hash<double>::operator()(__v);
#else
        // -0.0 and 0.0 should return same hash
        if (__v == 0.0) {
            return 0;
        }
        return __scalar_hash<double>::operator()(__v);
#endif
    }
};

template <>
struct hash<long double> : public __scalar_hash<long double> {
    CANN_ASC_STL_API size_t operator()(long double __v) const noexcept
    {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return __scalar_hash<long double>::operator()(__v);
#else
        // -0.0 and 0.0 should return same hash
        if (__v == 0.0L) {
            return 0;
        }
#if CANN_ASC_STL_DETAIL_ARCH(X86_64) && CANN_ASC_STL_DETAIL_OS(LINUX)
        // Zero out padding bits
        union {
            long double __t;
            struct {
                size_t __a;
                size_t __b;
            } __s;
        } __u;
        __u.__s.__a = 0;
        __u.__s.__b = 0;
        __u.__t = __v;
        return __u.__s.__a ^ __u.__s.__b;
#else
        return __scalar_hash<long double>::operator()(__v);
#endif
#endif  // CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    }
};

template <class _Tp, bool = is_enum_v<_Tp>>
struct __enum_hash : public __unary_function<_Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(_Tp __v) const noexcept
    {
        using type = typename underlying_type<_Tp>::type;
        return hash<type>()(static_cast<type>(__v));
    }
};
template <class _Tp>
struct __enum_hash<_Tp, false> {
    __enum_hash() = delete;
    __enum_hash(__enum_hash const&) = delete;
    __enum_hash& operator=(__enum_hash const&) = delete;
};

template <class _Tp>
struct hash : public __enum_hash<_Tp> {};

template <>
struct hash<nullptr_t> : public __unary_function<nullptr_t, size_t> {
    CANN_ASC_STL_API size_t operator()(nullptr_t) const noexcept
    {
        return 662607004ull;
    }
};

template <class _Key, class _Hash>
using __check_hash_requirements = integral_constant<bool,
    is_copy_constructible_v<_Hash> && is_move_constructible_v<_Hash> && __is_invocable_r<size_t, _Hash, _Key const&>>;

template <class _Key, class _Hash = hash<_Key>>
using __has_enabled_hash =
    integral_constant<bool, __check_hash_requirements<_Key, _Hash>::value && is_default_constructible_v<_Hash>>;

template <class _Type, class>
using __enable_hash_helper_imp = _Type;

template <class _Type, class... _Keys>
using __enable_hash_helper =
    __enable_hash_helper_imp<_Type, enable_if_t<__fold_and_v<__has_enabled_hash<_Keys>::value...>>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_HASH_H
