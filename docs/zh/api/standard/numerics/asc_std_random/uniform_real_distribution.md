# asc::std::uniform_real_distribution

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

`uniform_real_distribution<float>`从调用方随机引擎生成指定半开区间内的float值；本期不提供double或long double分布特化。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 声明

```cpp
namespace asc::std {
template<> class uniform_real_distribution<float>;
} // namespace asc::std
```

## 约束说明

- 仅提供uniform_real_distribution<float>。
- 结果位于指定的半开区间内，不提供double、long double及其他统计分布。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/random>
#include <asc/std/limits>

bool example()
{
    asc::std::uniform_real_distribution<float> distribution(2.0f, 5.0f);
    asc::std::minstd_rand engine(7);
    const auto value = distribution(engine);
    return value >= 2.0f && value < 5.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_random.md)
