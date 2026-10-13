# asc::std::philox_engine::seed

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

`asc::std::philox_engine::seed`使用指定种子重置随机数引擎状态。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

所属类型：[`asc::std::philox_engine`](philox_engine.md)。

```cpp
// asc::std::philox_engine 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr void seed(UIntType value = default_seed) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 用于初始化引擎状态的种子值，将引擎重置为该种子对应的状态；省略时取default_seed。 |

## 返回值说明

无返回值。

## 约束说明

- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式。
- 不提供SeedSequence、流式输入输出或共享全局状态。

## 调用示例

以下Host片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/random>

void example()
{
    asc::std::philox4x32 generator{};
    generator.seed(9);
}
```

## 关联API

- [`asc::std::philox_engine`](philox_engine.md)
- [本头文件的接口列表](asc_std_random.md)
