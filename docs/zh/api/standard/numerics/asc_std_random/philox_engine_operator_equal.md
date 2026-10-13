# `asc::std::operator==`（philox_engine）

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

比较引擎状态，状态相等时后续产生的数列相同。

## 函数原型

以下为`asc::std`命名空间中的友元函数声明；执行空间宏已省略。

```cpp
// 位于 philox_engine 类模板的类体内；当前实例的类名是注入类名。
friend constexpr bool operator==(const philox_engine& left, const philox_engine& right) noexcept;
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 比较的左操作数，比较不修改它。 |
| `right` | 输入 | 比较的右操作数，比较不修改它。 |

## 返回值说明

返回`bool`，比较关系成立时为`true`，否则为`false`。

## 约束说明

- 这是类内定义的非模板友元，通过参数相关查找（ADL）参与比较。
- 比较不推进引擎，不生成随机数。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::philox4x32 left, right;
    return left == right;
}
```

## 关联API

- [本头文件的接口列表](asc_std_random.md)
