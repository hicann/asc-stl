# 头文件asc/std/linalg

提供面向向量和矩阵的非拥有视图变换：缩放、共轭、转置和共轭转置。当前交付范围不包括矩阵乘法、矩阵向量乘法、内积或范数归约算法；这些计算仍由调用方实现。

组合视图在读取元素时应用变换，不分配或填充变换后的临时矩阵。例如，[共轭转置的协方差示例](linalg_conjugate_transposed.md)用 `scaled(1/N, conjugate_transposed(A))` 表达 `Aᴴ/N`，随后通过显式归约计算 `AᴴA/N`。视图借用原始存储，必须在存储有效期间使用；组合调用的执行位置还受元素类型、访问器和所调用数学函数的支持范围约束。

## 使用方式

```cpp
#include <asc/std/linalg>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::linalg::conjugate_transposed](linalg_conjugate_transposed.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated](linalg_conjugated.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor](linalg_conjugated_accessor.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::access](linalg_conjugated_accessor_access.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::conjugated_accessor](linalg_conjugated_accessor_conjugated_accessor.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::data_handle_type](linalg_conjugated_accessor_data_handle_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::element_type](linalg_conjugated_accessor_element_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::nested_accessor](linalg_conjugated_accessor_nested_accessor.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::offset](linalg_conjugated_accessor_offset.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::offset_policy](linalg_conjugated_accessor_offset_policy.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::reference](linalg_conjugated_accessor_reference.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::layout_transpose](linalg_layout_transpose.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::layout_transpose::mapping](linalg_layout_transpose_mapping.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::layout_transpose::nested_layout_type](linalg_layout_transpose_nested_layout_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled](linalg_scaled.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor](linalg_scaled_accessor.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::access](linalg_scaled_accessor_access.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::data_handle_type](linalg_scaled_accessor_data_handle_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::element_type](linalg_scaled_accessor_element_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::nested_accessor](linalg_scaled_accessor_nested_accessor.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::offset](linalg_scaled_accessor_offset.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::offset_policy](linalg_scaled_accessor_offset_policy.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::reference](linalg_scaled_accessor_reference.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::scaled_accessor](linalg_scaled_accessor_scaled_accessor.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::scaled_accessor::scaling_factor](linalg_scaled_accessor_scaling_factor.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linalg::transposed](linalg_transposed.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
