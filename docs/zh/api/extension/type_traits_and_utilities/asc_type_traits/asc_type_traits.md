# 头文件asc/type_traits

提供可按位比较、扩展浮点类型和可平凡重定位（trivially relocatable）等属性的类型特征

## 使用方式

```cpp
#include <asc/type_traits>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::is_bitwise_comparable](is_bitwise_comparable.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::is_bitwise_comparable_v](is_bitwise_comparable_v.md) | 变量模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::is_extended_floating_point](is_extended_floating_point.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::is_extended_floating_point_v](is_extended_floating_point_v.md) | 变量模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::is_trivially_relocatable](is_trivially_relocatable.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::is_trivially_relocatable_v](is_trivially_relocatable_v.md) | 变量模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
