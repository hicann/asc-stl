# asc::overflow_result

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

`asc::overflow_result`同时返回算术结果和是否发生溢出的标志。

## 声明

```cpp
namespace asc {
template<class T> struct overflow_result;
} // namespace asc
```

## 约束说明

- T、From和To必须是不超过64位的标准非bool整数类型。
- 所有溢出检查均不得触发有符号整数溢出的未定义行为。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/numeric>

bool example()
{
    const asc::overflow_result<int> result = asc::add_overflow(4, 5);
    return !result.overflow && result.value == 9;
}
```

## 关联API

- [本头文件的接口列表](asc_numeric.md)
