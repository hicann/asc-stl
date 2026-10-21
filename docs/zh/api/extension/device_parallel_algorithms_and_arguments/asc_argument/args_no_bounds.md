# asc::args::no_bounds

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

头文件路径为：`<asc/argument>`。

`asc::args::no_bounds`表示参数没有附加取值边界。

## 声明

```cpp
// asc::args 类内的声明节选；模板形参和其他成员由所属类提供。
struct no_bounds;
```

## 约束说明

- no_bounds只表示未携带边界信息，不校验实际值或数据指针；使用数据时仍须满足被调用接口前提。

- 使用C++17，可在Host、AI Core SIMD编程 和AI Core SIMT编程中使用。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/argument>

bool example()
{
    asc::args::immediate<int> argument(7, asc::args::no_bounds{});
    return argument.value() == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_argument.md)
