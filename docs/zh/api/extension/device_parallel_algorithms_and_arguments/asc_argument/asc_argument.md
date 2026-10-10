# 头文件 asc/argument

提供常量、立即值、延迟求值参数、延迟序列和边界信息等并行算法参数包装

## 使用方式

```cpp
#include <asc/argument>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::args::bounds](args_bounds.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::constant](args_constant.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::constant::value](args_constant_value.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::deferred](args_deferred.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::deferred::data](args_deferred_data.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::deferred::deferred](args_deferred_deferred.md) | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::deferred_sequence](args_deferred_sequence.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::deferred_sequence::data](args_deferred_sequence_data.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::deferred_sequence::deferred_sequence](args_deferred_sequence_deferred_sequence.md) | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::deferred_sequence::size](args_deferred_sequence_size.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::immediate](args_immediate.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::immediate::immediate](args_immediate_immediate.md) | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::immediate::value](args_immediate_value.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::no_bounds](args_no_bounds.md) | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::runtime_bounds](args_runtime_bounds.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::runtime_bounds::lower](args_runtime_bounds_lower.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::runtime_bounds::runtime_bounds](args_runtime_bounds_runtime_bounds.md) | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::runtime_bounds::upper](args_runtime_bounds_upper.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::static_bounds](args_static_bounds.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::static_bounds::lower](args_static_bounds_lower.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::args::static_bounds::upper](args_static_bounds_upper.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
