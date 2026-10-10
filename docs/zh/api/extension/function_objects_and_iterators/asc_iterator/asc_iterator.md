# 头文件 asc/iterator

提供常量、计数、丢弃、排列、跨步、重排（shuffle）、变换、组合及输出等非拥有迭代器适配器

## 使用方式

```cpp
#include <asc/iterator>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::constant_iterator](constant_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::counting_iterator](counting_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::discard_iterator](discard_iterator.md) | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_constant_iterator](make_constant_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_counting_iterator](make_counting_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_discard_iterator](make_discard_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_permutation_iterator](make_permutation_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_shuffle_iterator](make_shuffle_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_strided_iterator](make_strided_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_tabulate_output_iterator](make_tabulate_output_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_transform_input_output_iterator](make_transform_input_output_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_transform_iterator](make_transform_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_transform_output_iterator](make_transform_output_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_zip_function](make_zip_function.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_zip_iterator](make_zip_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::make_zip_transform_iterator](make_zip_transform_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::permutation_iterator](permutation_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::shuffle_iterator](shuffle_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::strided_iterator](strided_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::tabulate_output_iterator](tabulate_output_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::transform_input_output_iterator](transform_input_output_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::transform_iterator](transform_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::transform_output_iterator](transform_output_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::zip_function](zip_function.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::zip_iterator](zip_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::zip_transform_iterator](zip_transform_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
