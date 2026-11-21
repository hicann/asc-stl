# asc::std::linear_congruential_engine::seed

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

`asc::std::linear_congruential_engine::seed`使用指定种子重置随机数引擎状态。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

所属类型：[`asc::std::linear_congruential_engine`](linear_congruential_engine.md)。

### 原型1

```cpp
// asc::std::linear_congruential_engine 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr void seed(result_type seed) noexcept;
```

### 原型2

```cpp
// asc::std::linear_congruential_engine 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Sseq, enable_if_t<detail::__is_seed_sequence<Sseq, linear_congruential_engine>::value, int> = 0>
constexpr void seed(Sseq& sequence) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `seed` | 输入 | 用于初始化或重置伪随机数引擎状态的种子值。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Sseq` | 种子序列类型；须可无参调用sequence()产生无符号整数，不是标准seed_seq的generate(first, last)协议。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `sequence` | 输入/输出 | 用于初始化或重置伪随机数引擎状态的种子值。 |

## 返回值说明

无返回值。

## 约束说明

- 两种重载都先将种子整数对引擎的实际模数取余。`M` 为零时保留 `result_type` 的低位。若 `C` 为零且余数为零，初始状态取 1，否则取该余数。
- 种子对象通过无参调用 `sequence()` 提供一个整数。

- 提供不接收seed_seq的标准seed、discard、生成和相等比较成员。

## 调用示例

以下Host片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::minstd_rand generator;
    generator.seed(9);
    return generator() == 434439u;
}
```

## 关联API

- [`asc::std::linear_congruential_engine`](linear_congruential_engine.md)
- [本头文件的接口列表](asc_std_random.md)
