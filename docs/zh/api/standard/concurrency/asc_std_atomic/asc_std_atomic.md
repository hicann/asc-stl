# 头文件 asc/std/atomic

提供原子读写、交换、比较交换和标准内存序控制

## 使用方式

```cpp
#include <asc/std/atomic>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [CANN_ASC_STL_ATOMIC_BOOL_LOCK_FREE](cann_asc_stl_atomic_bool_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_CHAR16_T_LOCK_FREE](cann_asc_stl_atomic_char16_t_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_CHAR32_T_LOCK_FREE](cann_asc_stl_atomic_char32_t_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_CHAR8_T_LOCK_FREE](cann_asc_stl_atomic_char8_t_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_CHAR_LOCK_FREE](cann_asc_stl_atomic_char_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_FLAG_INIT](cann_asc_stl_atomic_flag_init.md) | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_INT_LOCK_FREE](cann_asc_stl_atomic_int_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_LLONG_LOCK_FREE](cann_asc_stl_atomic_llong_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_LONG_LOCK_FREE](cann_asc_stl_atomic_long_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_POINTER_LOCK_FREE](cann_asc_stl_atomic_pointer_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_SHORT_LOCK_FREE](cann_asc_stl_atomic_short_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_VAR_INIT](cann_asc_stl_atomic_var_init.md) | 宏 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [CANN_ASC_STL_ATOMIC_WCHAR_T_LOCK_FREE](cann_asc_stl_atomic_wchar_t_lock_free.md) | 宏 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic](atomic.md) | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::atomic](atomic_atomic.md) | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::compare_exchange_strong](atomic_compare_exchange_strong_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::compare_exchange_weak](atomic_compare_exchange_weak_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::exchange](atomic_exchange_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_add](atomic_fetch_add_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_and](atomic_fetch_and_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_or](atomic_fetch_or_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_sub](atomic_fetch_sub_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::fetch_xor](atomic_fetch_xor_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::is_always_lock_free](atomic_is_always_lock_free.md) | 变量 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::is_lock_free](atomic_is_lock_free_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::load](atomic_load_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::storage_type](atomic_storage_type.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::store](atomic_store_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic::value_type](atomic_value_type.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_bool](atomic_bool.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_char](atomic_char.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_char16_t](atomic_char16_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_char32_t](atomic_char32_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_char8_t](atomic_char8_t.md) | 类型别名 | C++20+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_compare_exchange_strong](atomic_compare_exchange_strong_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_compare_exchange_strong_explicit](atomic_compare_exchange_strong_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_compare_exchange_weak](atomic_compare_exchange_weak_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_compare_exchange_weak_explicit](atomic_compare_exchange_weak_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_exchange](atomic_exchange_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_exchange_explicit](atomic_exchange_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_add](atomic_fetch_add_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_add_explicit](atomic_fetch_add_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_and](atomic_fetch_and_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_and_explicit](atomic_fetch_and_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_or](atomic_fetch_or_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_or_explicit](atomic_fetch_or_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_sub](atomic_fetch_sub_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_sub_explicit](atomic_fetch_sub_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_xor](atomic_fetch_xor_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_fetch_xor_explicit](atomic_fetch_xor_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag](atomic_flag.md) | 类 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag::atomic_flag](atomic_flag_atomic_flag.md) | 构造函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag::clear](atomic_flag_clear_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag::test](atomic_flag_test_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag::test_and_set](atomic_flag_test_and_set_member_function.md) | 成员函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_clear](atomic_flag_clear_function.md) | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_clear_explicit](atomic_flag_clear_explicit.md) | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_test](atomic_flag_test_function.md) | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_test_and_set](atomic_flag_test_and_set_function.md) | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_test_and_set_explicit](atomic_flag_test_and_set_explicit.md) | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_flag_test_explicit](atomic_flag_test_explicit.md) | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_init](atomic_init.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int](atomic_int.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int16_t](atomic_int16_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int32_t](atomic_int32_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int64_t](atomic_int64_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int8_t](atomic_int8_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_fast16_t](atomic_int_fast16_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_fast32_t](atomic_int_fast32_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_fast64_t](atomic_int_fast64_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_fast8_t](atomic_int_fast8_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_least16_t](atomic_int_least16_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_least32_t](atomic_int_least32_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_least64_t](atomic_int_least64_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_int_least8_t](atomic_int_least8_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_intmax_t](atomic_intmax_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_intptr_t](atomic_intptr_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_is_lock_free](atomic_is_lock_free_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_llong](atomic_llong.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_load](atomic_load_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_load_explicit](atomic_load_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_long](atomic_long.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ptrdiff_t](atomic_ptrdiff_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ref](atomic_ref.md) | 类模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_schar](atomic_schar.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_short](atomic_short.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_signed_lock_free](atomic_signed_lock_free.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_size_t](atomic_size_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_store](atomic_store_function_template.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_store_explicit](atomic_store_explicit.md) | 函数模板 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_thread_fence](atomic_thread_fence.md) | 函数 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uchar](atomic_uchar.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint](atomic_uint.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint16_t](atomic_uint16_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint32_t](atomic_uint32_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint64_t](atomic_uint64_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint8_t](atomic_uint8_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_fast16_t](atomic_uint_fast16_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_fast32_t](atomic_uint_fast32_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_fast64_t](atomic_uint_fast64_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_fast8_t](atomic_uint_fast8_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_least16_t](atomic_uint_least16_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_least32_t](atomic_uint_least32_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_least64_t](atomic_uint_least64_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uint_least8_t](atomic_uint_least8_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uintmax_t](atomic_uintmax_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_uintptr_t](atomic_uintptr_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ullong](atomic_ullong.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ulong](atomic_ulong.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_unsigned_lock_free](atomic_unsigned_lock_free.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_ushort](atomic_ushort.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::atomic_wchar_t](atomic_wchar_t.md) | 类型别名 | C++17+ | Host、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::kill_dependency](kill_dependency.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order](memory_order.md) | 枚举 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_acq_rel](memory_order_acq_rel.md) | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_acquire](memory_order_acquire.md) | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_consume](memory_order_consume.md) | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_relaxed](memory_order_relaxed.md) | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_release](memory_order_release.md) | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::memory_order_seq_cst](memory_order_seq_cst.md) | 枚举值 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
