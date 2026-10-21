# asc::std::uniform_int_distribution

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

`asc::std::uniform_int_distribution`把随机引擎结果映射为给定整数区间内的值。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 声明

```cpp
namespace asc::std {
template<class IntType = int> class uniform_int_distribution;
} // namespace asc::std
```

## 约束说明

- 支持全部标准整数结果类型。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::minstd_rand engine(1);
    asc::std::uniform_int_distribution<int> distribution(2, 4);
    const int value = distribution(engine);
    return distribution.a() == 2 && distribution.b() == 4 && value >= 2 && value <= 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_random.md)
