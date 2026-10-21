# asc::overflow_result::overflow

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

头文件路径为：`<asc/numeric>`。

`asc::overflow_result::overflow`标记对应算术结果是否发生溢出。

## 声明

所属类型：[`asc::overflow_result`](overflow_result.md)。

```cpp
// asc::overflow_result 类内的声明节选；模板形参和其他成员由所属类提供。
bool overflow;
```

## 约束说明

- 可在Host、AI Core SIMD和AI Core SIMT调用；结果按本页声明的整数类型返回。
- `T`须为不超过64位的标准非bool整数；查询结果成员不执行额外计算。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/numeric>

bool example()
{
    auto result = asc::add_overflow(2, 3);
    return !result.overflow && result.value == 5;
}
```

## 关联API

- [`asc::overflow_result`](overflow_result.md)
- [本头文件的接口列表](asc_numeric.md)
