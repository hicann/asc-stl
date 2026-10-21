# asc::std::linear_congruential_engine::linear_congruential_engine

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

`asc::std::linear_congruential_engine::linear_congruential_engine`按本页所列构造形态初始化`linear_congruential_engine`对象。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

### 原型1

```cpp
constexpr linear_congruential_engine() noexcept;
```

### 原型2

```cpp
explicit constexpr linear_congruential_engine(result_type seed) noexcept;
```

### 原型3

```cpp
template<class Sseq, enable_if_t<detail::__is_seed_sequence<Sseq, linear_congruential_engine>::value, int> = 0>
explicit constexpr linear_congruential_engine(Sseq& sequence) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `seed` | 输入 | 用于初始化或重置伪随机数引擎状态的种子值。 |

### 原型3的参数

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

- 种子对象通过无参调用取得一个整数；当模数非零时对其取模，并按增量与零状态规则归一化。该形式不接受只有generate成员的标准SeedSequence。

- 提供不接收seed_seq的标准seed、discard、生成和相等比较成员。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/random>
#include <asc/std/limits>

bool example()
{
    using Engine = asc::std::minstd_rand;
    Engine engine(1);
    return engine() == 48271;
}
```

## 关联API

- [本头文件的接口列表](asc_std_random.md)
