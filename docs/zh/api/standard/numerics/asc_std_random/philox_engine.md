# asc::std::philox_engine

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：支持
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3系列产品：不支持
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2系列产品：不支持
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2推理产品：不支持
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas推理系列产品AI Core：不支持
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas推理系列产品Vector Core：不支持
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas训练系列产品：不支持
<!-- end id7 -->

## 功能说明

头文件路径为：`<asc/std/random>`。

`asc::std::philox_engine`保存计数器型伪随机引擎的状态并生成数值。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 声明

```cpp
namespace asc::std {
template<class UIntType, size_t WordSize, size_t WordCount, size_t NumRounds, UIntType... Constants> class philox_engine;
} // namespace asc::std
```

## 约束说明

- UIntType须为无cv限定的无符号整数。WordSize仅32或64，WordCount仅2或4，Constants个数须等于WordCount，NumRounds必须大于0。

- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式。
- 不提供SeedSequence、流式输入输出或共享全局状态。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::philox4x32 first;
    asc::std::philox4x32 second;
    const auto a = first();
    const auto b = second();
    return a == b && first() == second();
}
```

## 关联API

- [本头文件的接口列表](asc_std_random.md)
