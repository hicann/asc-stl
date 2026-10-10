# 头文件 asc/numeric

提供整数溢出检测、饱和计算和窄化类型转换检查

## 使用方式

```cpp
#include <asc/numeric>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::add_overflow](add_overflow.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::div_overflow](div_overflow.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::mul_overflow](mul_overflow.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::narrow](narrow.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::narrow_cast](narrow_cast.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::overflow_cast](overflow_cast.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::overflow_result](overflow_result.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::overflow_result::overflow](overflow_result_overflow.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::overflow_result::value](overflow_result_value.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::saturating_add](saturating_add.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::saturating_div](saturating_div.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::saturating_mul](saturating_mul.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::saturating_overflow_cast](saturating_overflow_cast.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::saturating_sub](saturating_sub.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::sub_overflow](sub_overflow.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
