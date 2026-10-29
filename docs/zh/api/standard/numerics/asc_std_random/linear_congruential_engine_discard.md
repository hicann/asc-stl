# asc::std::linear_congruential_engine::discard

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

`asc::std::linear_congruential_engine::discard`推进随机数引擎状态并丢弃指定数量的结果。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

所属类型：[`asc::std::linear_congruential_engine`](linear_congruential_engine.md)。

```cpp
// asc::std::linear_congruential_engine 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr void discard(unsigned long long count) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `count` | 输入 | 跳过的引擎输出步数；等效于丢弃count次生成结果。 |

## 返回值说明

无返回值。

## 约束说明

- 提供不接收seed_seq的标准seed、discard、生成和相等比较成员。

## 调用示例

以下Host片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::minstd_rand generator;
    generator.discard(4);
    return generator() == 2078669041u;
}
```

## 关联API

- [`asc::std::linear_congruential_engine`](linear_congruential_engine.md)
- [本头文件的接口列表](asc_std_random.md)
