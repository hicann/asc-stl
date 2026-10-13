# 头文件asc/functional

提供最小值和最大值函数对象，以及用于描述返回类型、可复制性、结合性、交换性、单位元和吸收元的操作属性

## 使用方式

```cpp
#include <asc/functional>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::absorbing_element](absorbing_element.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::always_false](always_false.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::always_false::`operator()`](always_false_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::always_true](always_true.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::always_true::`operator()`](always_true_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::equal_to_value](equal_to_value.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::equal_to_value::`operator()`](equal_to_value_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::has_absorbing_element_v](has_absorbing_element_v.md) | 变量模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::has_identity_element_v](has_identity_element_v.md) | 变量模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::identity_element](identity_element.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::is_associative_v](is_associative_v.md) | 变量模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::is_commutative_v](is_commutative_v.md) | 变量模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::maximum](maximum.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::maximum::`operator()`](maximum_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::minimum](minimum.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::minimum::`operator()`](minimum_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::proclaim_copyable_arguments](proclaim_copyable_arguments.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::proclaim_return_type](proclaim_return_type.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::proclaims_copyable_arguments](proclaims_copyable_arguments.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::proclaims_copyable_arguments_v](proclaims_copyable_arguments_v.md) | 变量模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
