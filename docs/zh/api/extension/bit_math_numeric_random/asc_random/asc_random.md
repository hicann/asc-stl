# 头文件 asc/random

提供确定性PCG64伪随机数引擎，以及有限整数域上的确定性双射`random_bijection`

## 使用方式

```cpp
#include <asc/random>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::operator!=（函数模板）](operator_not_equal.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::operator==（函数模板）](operator_equal.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64](pcg64.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64_engine](pcg64_engine.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64_engine::default_seed](pcg64_engine_default_seed.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64_engine::discard](pcg64_engine_discard.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64_engine::max](pcg64_engine_max.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64_engine::min](pcg64_engine_min.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64_engine::operator()](pcg64_engine_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64_engine::pcg64_engine](pcg64_engine_pcg64_engine.md) | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64_engine::result_type](pcg64_engine_result_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::pcg64_engine::seed](pcg64_engine_seed.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::random_bijection](random_bijection.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::random_bijection::index_type](random_bijection_index_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::random_bijection::operator()](random_bijection_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::random_bijection::random_bijection](random_bijection_random_bijection.md) | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::random_bijection::size](random_bijection_size.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
