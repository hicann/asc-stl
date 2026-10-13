# asc::std::integer_sequence::value_type

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

头文件路径为：`<asc/std/utility>`。

`asc::std::integer_sequence::value_type`标识元素或结果的值类型。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 声明

所属类型：[`asc::std::integer_sequence`](integer_sequence.md)。

```cpp
// asc::std::integer_sequence 类内的声明节选；模板形参和其他成员由所属类提供。
using value_type = T;
```

## 约束说明

- 提供完整的标准形式。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/utility>

void use_type()
{
    using alias_type = typename asc::std::integer_sequence<int, 1, 2, 3>::value_type;
}
```

## 关联API

- [`asc::std::integer_sequence`](integer_sequence.md)
- [本头文件的接口列表](asc_std_utility.md)
