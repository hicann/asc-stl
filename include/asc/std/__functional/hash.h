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

#ifndef CANN_ASC_STL_ASC_STD___FUNCTIONAL_HASH_H
#define CANN_ASC_STL_ASC_STD___FUNCTIONAL_HASH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__functional/invoke.h>
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
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/cstring>

CANN_ASC_STL_BEGIN_NAMESPACE

// No unary_function header is available here, so inline the minimal
// equivalent (an empty base class kept only to shape the specializations
// uniformly).
template <class Arg, class Result>
struct __unary_function {};

template <class Size>
CANN_ASC_STL_API Size __loadword(const void* p)
{
    Size r;
    ::asc::std::memcpy(&r, p, sizeof(r));
    return r;
}

// Use murmur2 when size_t is 32 bits and cityhash64 when it is 64 bits:
// cityhash64 relies on 64x64-bit multiplication, which is too slow on 32-bit
// systems.
template <class Size, size_t = sizeof(Size) * CHAR_BIT>
struct __murmur2_or_cityhash;

// murmur2
template <class Size>
struct __murmur2_or_cityhash<Size, 32> {
    CANN_ASC_STL_API Size operator()(const void* key, Size len);
};

template <class Size>
CANN_ASC_STL_API Size __murmur2_or_cityhash<Size, 32>::operator()(const void* key, Size len)
{
    const Size m = 0x5bd1e995;
    const Size r = 24;
    Size h = len;
    const unsigned char* data = static_cast<const unsigned char*>(key);
    for (; len >= 4; data += 4, len -= 4) {
        Size k = __loadword<Size>(data);
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
    }
    switch (len) {
        case 3:
            h ^= static_cast<Size>(data[2] << 16);
            [[fallthrough]];
        case 2:
            h ^= static_cast<Size>(data[1] << 8);
            [[fallthrough]];
        case 1:
            h ^= data[0];
            h *= m;
    }
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;
}

template <class Size>
struct __murmur2_or_cityhash<Size, 64> {
    CANN_ASC_STL_API Size operator()(const void* key, Size len);

private:
    // Some primes between 2^63 and 2^64.
    static const Size k0 = 0xc3a5c85c97cb3127ULL;
    static const Size k1 = 0xb492b66fbe98f273ULL;
    static const Size k2 = 0x9ae16a3b2f90404fULL;
    static const Size k3 = 0xc949d7c7509e6557ULL;

    static CANN_ASC_STL_API Size __rotate(Size val, int shift)
    {
        return shift == 0 ? val : ((val >> shift) | (val << (64 - shift)));
    }

    static CANN_ASC_STL_API Size __rotate_by_at_least_1(Size val, int shift)
    {
        return (val >> shift) | (val << (64 - shift));
    }

    static CANN_ASC_STL_API Size __shift_mix(Size val)
    {
        return val ^ (val >> 47);
    }

    static CANN_ASC_STL_API Size __hash_len_16(Size u, Size v)
    {
        const Size mul = 0x9ddfea08eb382d69ULL;
        Size a = (u ^ v) * mul;
        a ^= a >> 47;
        Size b = (v ^ a) * mul;
        b ^= b >> 47;
        b *= mul;
        return b;
    }

    static CANN_ASC_STL_API Size __hash_len_0_to_16(const char* s, Size len)
    {
        if (len > 8) {
            const Size a = __loadword<Size>(s);
            const Size b = __loadword<Size>(s + len - 8);
            return __hash_len_16(a, __rotate_by_at_least_1(b + len, len)) ^ b;
        }
        if (len >= 4) {
            const uint32_t a = __loadword<uint32_t>(s);
            const uint32_t b = __loadword<uint32_t>(s + len - 4);
            return __hash_len_16(len + (static_cast<Size>(a) << 3), b);
        }
        if (len > 0) {
            const unsigned char a = static_cast<unsigned char>(s[0]);
            const unsigned char b = static_cast<unsigned char>(s[len >> 1]);
            const unsigned char c = static_cast<unsigned char>(s[len - 1]);
            const uint32_t y = static_cast<uint32_t>(a) + (static_cast<uint32_t>(b) << 8);
            const uint32_t z = len + (static_cast<uint32_t>(c) << 2);
            return __shift_mix(y * k2 ^ z * k3) * k2;
        }
        return k2;
    }

    static CANN_ASC_STL_API Size __hash_len_17_to_32(const char* s, Size len)
    {
        const Size a = __loadword<Size>(s) * k1;
        const Size b = __loadword<Size>(s + 8);
        const Size c = __loadword<Size>(s + len - 8) * k2;
        const Size d = __loadword<Size>(s + len - 16) * k0;
        return __hash_len_16(__rotate(a - b, 43) + __rotate(c, 30) + d, a + __rotate(b ^ k3, 20) - c + len);
    }

    // Return a 16-byte hash for 48 bytes: quick and dirty; callers should
    // pass "random-looking" values for a and b.
    static CANN_ASC_STL_API pair<Size, Size> __weak_hash_len_32_with_seeds(
        Size w, Size x, Size y, Size z, Size a, Size b)
    {
        a += w;
        b = __rotate(b + a + z, 21);
        const Size c = a;
        a += x;
        a += y;
        b += __rotate(a, 44);
        return pair<Size, Size>(a + z, b + c);
    }

    // Return a 16-byte hash from s[0]...s[31], a, and b: quick and dirty.
    static CANN_ASC_STL_API pair<Size, Size> __weak_hash_len_32_with_seeds(const char* s, Size a, Size b)
    {
        return __weak_hash_len_32_with_seeds(
            __loadword<Size>(s), __loadword<Size>(s + 8), __loadword<Size>(s + 16), __loadword<Size>(s + 24), a, b);
    }

    // Return an 8-byte hash for 33 to 64 bytes.
    static CANN_ASC_STL_API Size __hash_len_33_to_64(const char* s, size_t len)
    {
        Size z = __loadword<Size>(s + 24);
        Size a = __loadword<Size>(s) + (len + __loadword<Size>(s + len - 16)) * k0;
        Size b = __rotate(a + z, 52);
        Size c = __rotate(a, 37);
        a += __loadword<Size>(s + 8);
        c += __rotate(a, 7);
        a += __loadword<Size>(s + 16);
        Size vf = a + z;
        Size vs = b + __rotate(a, 31) + c;
        a = __loadword<Size>(s + 16) + __loadword<Size>(s + len - 32);
        z += __loadword<Size>(s + len - 8);
        b = __rotate(a + z, 52);
        c = __rotate(a, 37);
        a += __loadword<Size>(s + len - 24);
        c += __rotate(a, 7);
        a += __loadword<Size>(s + len - 16);
        Size wf = a + z;
        Size ws = b + __rotate(a, 31) + c;
        Size r = __shift_mix((vf + ws) * k2 + (wf + vs) * k0);
        return __shift_mix(r * k0 + vs) * k2;
    }
};

// cityhash64
template <class Size>
CANN_ASC_STL_API Size __murmur2_or_cityhash<Size, 64>::operator()(const void* key, Size len)
{
    const char* s = static_cast<const char*>(key);
    if (len <= 32) {
        if (len <= 16) {
            return __hash_len_0_to_16(s, len);
        }
        return __hash_len_17_to_32(s, len);
    }
    if (len <= 64) {
        return __hash_len_33_to_64(s, len);
    }

    // For lengths over 64 bytes, hash the tail first, then keep 56 bytes of
    // state (v, w, x, y, z) across the loop.
    Size x = __loadword<Size>(s + len - 40);
    Size y = __loadword<Size>(s + len - 16) + __loadword<Size>(s + len - 56);
    Size z = __hash_len_16(__loadword<Size>(s + len - 48) + len, __loadword<Size>(s + len - 24));
    pair<Size, Size> v = __weak_hash_len_32_with_seeds(s + len - 64, len, z);
    pair<Size, Size> w = __weak_hash_len_32_with_seeds(s + len - 32, y + k1, x);
    x = x * k1 + __loadword<Size>(s);

    // Shrink len down to the nearest multiple of 64 and process the data in
    // 64-byte blocks.
    len = (len - 1) & ~static_cast<Size>(63);
    do {
        x = __rotate(x + y + v.first + __loadword<Size>(s + 8), 37) * k1;
        y = __rotate(y + v.second + __loadword<Size>(s + 48), 42) * k1;
        x ^= w.second;
        y += v.first + __loadword<Size>(s + 40);
        z = __rotate(z + w.first, 33) * k1;
        v = __weak_hash_len_32_with_seeds(s, v.second * k1, x + w.first);
        w = __weak_hash_len_32_with_seeds(s + 32, z + w.second, y + __loadword<Size>(s + 16));
        ::asc::std::swap(z, x);  // NOLINT(build/include_what_you_use)
        s += 64;
        len -= 64;
    } while (len != 0);
    return __hash_len_16(
        __hash_len_16(v.first, w.first) + __shift_mix(y) * k1 + z, __hash_len_16(v.second, w.second) + x);
}

template <class Tp, size_t = sizeof(Tp) / sizeof(size_t)>
struct __scalar_hash;

template <class Tp>
struct __scalar_hash<Tp, 0> : public __unary_function<Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(Tp v) const noexcept
    {
        union {
            Tp t;
            size_t a;
        } u;
        u.a = 0;
        u.t = v;
        return u.a;
    }
};

template <class Tp>
struct __scalar_hash<Tp, 1> : public __unary_function<Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(Tp v) const noexcept
    {
        union {
            Tp t;
            size_t a;
        } u;
        u.t = v;
        return u.a;
    }
};

template <class Tp>
struct __scalar_hash<Tp, 2> : public __unary_function<Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(Tp v) const noexcept
    {
        union {
            Tp t;
            struct {
                size_t a;
                size_t b;
            } s;
        } u;
        u.t = v;
        return __murmur2_or_cityhash<size_t>()(&u, sizeof(u));
    }
};

template <class Tp>
struct __scalar_hash<Tp, 3> : public __unary_function<Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(Tp v) const noexcept
    {
        union {
            Tp t;
            struct {
                size_t a;
                size_t b;
                size_t c;
            } s;
        } u;
        u.t = v;
        return __murmur2_or_cityhash<size_t>()(&u, sizeof(u));
    }
};

template <class Tp>
struct __scalar_hash<Tp, 4> : public __unary_function<Tp, size_t> {
    CANN_ASC_STL_API size_t operator()(Tp v) const noexcept
    {
        union {
            Tp t;
            struct {
                size_t a;
                size_t b;
                size_t c;
                size_t d;
            } s;
        } u;
        u.t = v;
        return __murmur2_or_cityhash<size_t>()(&u, sizeof(u));
    }
};

// Synthetic input pair for __hash_combine (internal symbol).
struct __hash_combine_pair {
    size_t first;
    size_t second;
};

CANN_ASC_STL_API size_t __hash_combine(size_t lhs, size_t rhs) noexcept
{
    using hash_t = __scalar_hash<__hash_combine_pair>;
    const __hash_combine_pair p = {lhs, rhs};
    return hash_t()(p);
}

template <class Tp>
struct hash<Tp*> : public __unary_function<Tp*, size_t> {
    CANN_ASC_STL_API size_t operator()(Tp* v) const noexcept
    {
        union {
            Tp* t;
            size_t a;
        } u;
        u.t = v;
        return __murmur2_or_cityhash<size_t>()(&u, sizeof(u));
    }
};

template <>
struct hash<bool> : public __unary_function<bool, size_t> {
    CANN_ASC_STL_API size_t operator()(bool v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<char> : public __unary_function<char, size_t> {
    CANN_ASC_STL_API size_t operator()(char v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<signed char> : public __unary_function<signed char, size_t> {
    CANN_ASC_STL_API size_t operator()(signed char v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<unsigned char> : public __unary_function<unsigned char, size_t> {
    CANN_ASC_STL_API size_t operator()(unsigned char v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<char16_t> : public __unary_function<char16_t, size_t> {
    CANN_ASC_STL_API size_t operator()(char16_t v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<char32_t> : public __unary_function<char32_t, size_t> {
    CANN_ASC_STL_API size_t operator()(char32_t v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<wchar_t> : public __unary_function<wchar_t, size_t> {
    CANN_ASC_STL_API size_t operator()(wchar_t v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<short> : public __unary_function<short, size_t> {
    CANN_ASC_STL_API size_t operator()(short v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<unsigned short> : public __unary_function<unsigned short, size_t> {
    CANN_ASC_STL_API size_t operator()(unsigned short v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<int> : public __unary_function<int, size_t> {
    CANN_ASC_STL_API size_t operator()(int v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<unsigned int> : public __unary_function<unsigned int, size_t> {
    CANN_ASC_STL_API size_t operator()(unsigned int v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<long> : public __unary_function<long, size_t> {
    CANN_ASC_STL_API size_t operator()(long v) const noexcept
    {
        return static_cast<size_t>(v);
    }
};

template <>
struct hash<unsigned long> : public __unary_function<unsigned long, size_t> {
    CANN_ASC_STL_API size_t operator()(unsigned long v) const noexcept
    {
        return static_cast<size_t>(v);
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
    CANN_ASC_STL_API size_t operator()(float v) const noexcept
    {
        // -0.0 and 0.0 must hash the same
        if (v == 0.0f) {
            return 0;
        }
        return __scalar_hash<float>::operator()(v);
    }
};

template <>
struct hash<double> : public __scalar_hash<double> {
    CANN_ASC_STL_API size_t operator()(double v) const noexcept
    {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        // Normalize either binary64 zero using integer operations on AI Core.
        if ((::asc::std::bit_cast<__UINT64_TYPE__>(v) << 1) == 0) {
            return 0;
        }
        return __scalar_hash<double>::operator()(v);
#else
        // -0.0 and 0.0 must hash the same
        if (v == 0.0) {
            return 0;
        }
        return __scalar_hash<double>::operator()(v);
#endif
    }
};

template <>
struct hash<long double> : public __scalar_hash<long double> {
    CANN_ASC_STL_API size_t operator()(long double v) const noexcept
    {
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && __SIZEOF_LONG_DOUBLE__ == 8 && __LDBL_MANT_DIG__ == 53
        return hash<double>{}(::asc::std::bit_cast<double>(v));
#elif CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        return __scalar_hash<long double>::operator()(v);
#else
        // -0.0 and 0.0 must hash the same
        if (v == 0.0L) {
            return 0;
        }
#if defined(__x86_64__) && defined(__linux__) && __LDBL_MANT_DIG__ == 64
        // The x86 extended representation has ten value bytes and six padding bytes.
        // Only copy the significand and the sign/exponent field.
        uint64_t significand;
        uint16_t sign_exponent;
        const auto* bytes = reinterpret_cast<const unsigned char*>(&v);
        __builtin_memcpy(&significand, bytes, sizeof(significand));
        __builtin_memcpy(&sign_exponent, bytes + sizeof(significand), sizeof(sign_exponent));
        return static_cast<size_t>(significand ^ sign_exponent);
#else
        return __scalar_hash<long double>::operator()(v);
#endif
#endif  // CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    }
};

// This byte-wise fallback for non-enum types is an ASC extension kept callable
// for existing users and internal consumers such as variant hash synthesis.
// It reads every object byte without consulting operator== or a key predicate.
// As a key hasher it requires determinate bytes and identical representations
// for equivalent keys; being trivially copyable alone does not establish this.
// For padding, equality-ignored fields, or non-trivial object state, supply an
// equality-aware value hasher instead of relying on this fallback. The hash
// enablement probes below check invocation, not these semantic requirements.
template <class T>
struct __byte_hash : public __unary_function<T, size_t> {
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API size_t operator()(const T& value) const noexcept
    {
        const auto* bytes = reinterpret_cast<const unsigned char*>(&value);
        size_t result = sizeof(size_t) == 8 ? static_cast<size_t>(1469598103934665603ULL) : 2166136261U;
        const size_t prime = sizeof(size_t) == 8 ? static_cast<size_t>(1099511628211ULL) : 16777619U;
        for (size_t index = 0; index < sizeof(T); ++index) {
            result = (result ^ bytes[index]) * prime;
        }
        return result;
    }
};

// Enum types forward to the specialization for the underlying integral type
// (primary template).
template <class T, bool = is_enum_v<T>>
struct __primary_hash;
template <class T>
struct __primary_hash<T, true> : public __unary_function<T, size_t> {
    CANN_ASC_STL_API size_t operator()(T v) const noexcept
    {
        using type = typename underlying_type<T>::type;
        return hash<type>()(static_cast<type>(v));
    }
};
template <class T>
struct __primary_hash<T, false> : public __byte_hash<T> {};

template <class T>
struct hash : public __primary_hash<T> {};

template <>
struct hash<nullptr_t> : public __unary_function<nullptr_t, size_t> {
    CANN_ASC_STL_API size_t operator()(nullptr_t) const noexcept
    {
        return 662607004ull;
    }
};

template <class Key, class Hash>
using __check_hash_requirements = integral_constant<bool,
    is_copy_constructible_v<Hash> && is_move_constructible_v<Hash> && __is_invocable_r_v<size_t, Hash, const Key&>>;

template <class Key, class Hash = hash<Key>>
using __has_enabled_hash =
    integral_constant<bool, __check_hash_requirements<Key, Hash>::value && is_default_constructible_v<Hash>>;

template <class Type, class>
using __enable_hash_helper_imp = Type;

template <class Type, class... Keys>
using __enable_hash_helper =
    __enable_hash_helper_imp<Type, enable_if_t<__fold_and_v<__has_enabled_hash<Keys>::value...>>>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FUNCTIONAL_HASH_H
