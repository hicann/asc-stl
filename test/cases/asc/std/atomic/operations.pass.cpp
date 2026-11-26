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

#include <asc/std/atomic>

#include <cstdint>
#include <type_traits>

namespace {

namespace ast = asc::std;

#define CHECK_ATOMIC_ALIAS(Name, Type) static_assert(std::is_same_v<ast::Name, ast::atomic<Type>>)
CHECK_ATOMIC_ALIAS(atomic_bool, bool);
CHECK_ATOMIC_ALIAS(atomic_char, char);
CHECK_ATOMIC_ALIAS(atomic_schar, signed char);
CHECK_ATOMIC_ALIAS(atomic_uchar, unsigned char);
CHECK_ATOMIC_ALIAS(atomic_char16_t, char16_t);
CHECK_ATOMIC_ALIAS(atomic_char32_t, char32_t);
CHECK_ATOMIC_ALIAS(atomic_wchar_t, wchar_t);
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
CHECK_ATOMIC_ALIAS(atomic_char8_t, char8_t);
#endif
CHECK_ATOMIC_ALIAS(atomic_short, short);
CHECK_ATOMIC_ALIAS(atomic_ushort, unsigned short);
CHECK_ATOMIC_ALIAS(atomic_int, int);
CHECK_ATOMIC_ALIAS(atomic_uint, unsigned int);
CHECK_ATOMIC_ALIAS(atomic_long, long);
CHECK_ATOMIC_ALIAS(atomic_ulong, unsigned long);
CHECK_ATOMIC_ALIAS(atomic_llong, long long);
CHECK_ATOMIC_ALIAS(atomic_ullong, unsigned long long);
CHECK_ATOMIC_ALIAS(atomic_signed_lock_free, int);
CHECK_ATOMIC_ALIAS(atomic_unsigned_lock_free, unsigned int);
CHECK_ATOMIC_ALIAS(atomic_intmax_t, std::intmax_t);
CHECK_ATOMIC_ALIAS(atomic_uintmax_t, std::uintmax_t);
CHECK_ATOMIC_ALIAS(atomic_intptr_t, std::intptr_t);
CHECK_ATOMIC_ALIAS(atomic_uintptr_t, std::uintptr_t);
CHECK_ATOMIC_ALIAS(atomic_size_t, std::size_t);
CHECK_ATOMIC_ALIAS(atomic_ptrdiff_t, std::ptrdiff_t);

#define CHECK_ATOMIC_WIDTH(Width)                                               \
    CHECK_ATOMIC_ALIAS(atomic_int##Width##_t, std::int##Width##_t);             \
    CHECK_ATOMIC_ALIAS(atomic_uint##Width##_t, std::uint##Width##_t);           \
    CHECK_ATOMIC_ALIAS(atomic_int_fast##Width##_t, std::int_fast##Width##_t);   \
    CHECK_ATOMIC_ALIAS(atomic_uint_fast##Width##_t, std::uint_fast##Width##_t); \
    CHECK_ATOMIC_ALIAS(atomic_int_least##Width##_t, std::int_least##Width##_t); \
    CHECK_ATOMIC_ALIAS(atomic_uint_least##Width##_t, std::uint_least##Width##_t)
CHECK_ATOMIC_WIDTH(8);
CHECK_ATOMIC_WIDTH(16);
CHECK_ATOMIC_WIDTH(32);
CHECK_ATOMIC_WIDTH(64);
#undef CHECK_ATOMIC_WIDTH
#undef CHECK_ATOMIC_ALIAS

static_assert(CANN_ASC_STL_ATOMIC_CHAR8_T_LOCK_FREE == 2);
static_assert(std::is_enum_v<ast::memory_order>);
static_assert(ast::memory_order_consume != ast::memory_order_relaxed);
static_assert(ast::memory_order_consume != ast::memory_order_acquire);

template <class T>
bool check_compare_exchange()
{
    ast::atomic<T> x(T{7});
    T expected = T{6};
    if (x.compare_exchange_strong(expected, T{12}, ast::memory_order_seq_cst) || expected != T{7} || x.load() != T{7}) {
        return false;
    }
    if (!ast::atomic_compare_exchange_strong_explicit(
            &x, &expected, T{12}, ast::memory_order_acq_rel, ast::memory_order_acquire) ||
        x.load() != T{12}) {
        return false;
    }
    expected = T{3};
    if (ast::atomic_compare_exchange_weak(&x, &expected, T{19}) || expected != T{12}) {
        return false;
    }
    expected = T{12};
    for (int attempt = 0; attempt < 64; ++attempt) {
        if (x.compare_exchange_weak(expected, T{21}, ast::memory_order_acq_rel, ast::memory_order_relaxed)) {
            expected = T{4};
            return !ast::atomic_compare_exchange_weak_explicit(
                       &x, &expected, T{9}, ast::memory_order_acquire, ast::memory_order_relaxed) &&
                expected == T{21} && x.load() == T{21};
        }
        if (expected != T{12} || x.load() != T{12}) {
            return false;
        }
    }
    return false;
}

template <class T>
bool check_atomic_fetch_operations()
{
    using atomic_type = ast::atomic<T>;
    static_assert(std::is_same_v<typename atomic_type::value_type, T>);
    static_assert(sizeof(typename atomic_type::storage_type) >= sizeof(T));
    atomic_type x(T{0});
    if (atomic_type::is_always_lock_free && !x.is_lock_free()) {
        return false;
    }
    const T inputs[] = {T{0}, T{1}, T{31}, T{85}};
    for (T input : inputs) {
        ast::atomic_store_explicit(&x, input, ast::memory_order_release);
        if (x.exchange(T{15}) != input ||
            ast::atomic_exchange_explicit(&x, input, ast::memory_order_acq_rel) != T{15}) {
            return false;
        }

        T reference = input;
        if (x.fetch_sub(T{0}) != reference || ast::atomic_fetch_sub(&x, T{0}) != reference) {
            return false;
        }
        if (ast::atomic_fetch_add_explicit(&x, T{3}, ast::memory_order_relaxed) != reference) {
            return false;
        }
        reference = static_cast<T>(reference + T{3});
        if (x.fetch_and(T{63}) != reference) {
            return false;
        }
        reference = static_cast<T>(reference & T{63});
        if (ast::atomic_fetch_and(&x, T{31}) != reference) {
            return false;
        }
        reference = static_cast<T>(reference & T{31});
        if (ast::atomic_fetch_and_explicit(&x, T{23}, ast::memory_order_acquire) != reference) {
            return false;
        }
        reference = static_cast<T>(reference & T{23});
        if (x.fetch_or(T{8}) != reference) {
            return false;
        }
        reference = static_cast<T>(reference | T{8});
        if (ast::atomic_fetch_or(&x, T{2}) != reference) {
            return false;
        }
        reference = static_cast<T>(reference | T{2});
        if (ast::atomic_fetch_or_explicit(&x, T{1}, ast::memory_order_release) != reference) {
            return false;
        }
        reference = static_cast<T>(reference | T{1});
        if (x.fetch_xor(T{12}) != reference) {
            return false;
        }
        reference = static_cast<T>(reference ^ T{12});
        if (ast::atomic_fetch_xor(&x, T{14}) != reference) {
            return false;
        }
        reference = static_cast<T>(reference ^ T{14});
        if (ast::atomic_fetch_xor_explicit(&x, T{4}, ast::memory_order_acq_rel) != reference) {
            return false;
        }
        reference = static_cast<T>(reference ^ T{4});
        if (x.load(ast::memory_order_consume) != reference) {
            return false;
        }
    }
    return true;
}

bool check_flag_transitions()
{
    ast::atomic_flag flag = CANN_ASC_STL_ATOMIC_FLAG_INIT;
    for (int i = 0; i < 4; ++i) {
        if (ast::atomic_flag_test_explicit(&flag, ast::memory_order_acquire) ||
            ast::atomic_flag_test_and_set_explicit(&flag, ast::memory_order_acq_rel) ||
            !ast::atomic_flag_test_and_set_explicit(&flag, ast::memory_order_relaxed)) {
            return false;
        }
        ast::atomic_flag_clear_explicit(&flag, ast::memory_order_release);
    }
    return !flag.test(ast::memory_order_relaxed);
}
}  // namespace

int main()
{
    return check_compare_exchange<int>() && check_compare_exchange<unsigned long long>() &&
            check_atomic_fetch_operations<signed char>() && check_atomic_fetch_operations<unsigned short>() &&
            check_atomic_fetch_operations<int>() && check_atomic_fetch_operations<unsigned long long>() &&
            check_flag_transitions() ?
        0 :
        1;
}
