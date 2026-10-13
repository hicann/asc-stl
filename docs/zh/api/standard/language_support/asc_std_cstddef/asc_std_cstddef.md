# 头文件asc/std/cstddef

提供`size_t`、`ptrdiff_t`、`nullptr_t`和`byte`等基础类型

## 使用方式

```cpp
#include <asc/std/cstddef>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::byte](byte.md) | 枚举 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::max_align_t](max_align_t.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::nullptr_t](nullptr_t.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::operator&（byte重载）（函数）](operator_bit_and.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::operator&=](operator_bit_and_assign.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator<<`](operator_shift_left.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator<<=`](operator_shift_left_assign.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator>>`](operator_shift_right.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator>>=`](operator_shift_right_assign.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::operator^（byte重载）（函数）](operator_bit_xor.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::operator^=](operator_bit_xor_assign.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::operator\|（byte重载）（函数）](operator_bit_or.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::operator\|=](operator_bit_or_assign.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::operator~](operator_bit_not.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::ptrdiff_t](ptrdiff_t.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::size_t](size_t.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::to_integer](to_integer.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [offsetof](offsetof.md) | 宏 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
