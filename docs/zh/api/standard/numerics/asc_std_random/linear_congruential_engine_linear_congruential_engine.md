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

`asc::std::linear_congruential_engine::linear_congruential_engine` 按本页所列构造形态初始化 `linear_congruential_engine` 对象。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

### 原型 1

```cpp
constexpr linear_congruential_engine() noexcept;
```

### 原型 2

```cpp
constexpr linear_congruential_engine(result_type seed) noexcept;
```

### 原型 3

```cpp
template<class Sseq, enable_if_t<Isseedsequence<Sseq, linear_congruential_engine<UIntType, A, C, M>>, int>> constexpr linear_congruential_engine(Sseq& seed) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `seed` | 输入 | 用于初始化或重置伪随机数引擎状态的种子值。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Sseq` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `seed` | 输入/输出 | 用于初始化或重置伪随机数引擎状态的种子值。 |

## 约束说明

- 提供不接收 seed_seq 的标准 seed、discard、生成和相等比较成员

## 调用示例

以下 Host 片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/random>

void example()
{
    asc::std::minstd_rand generator{};
    (void)generator();
}
```
