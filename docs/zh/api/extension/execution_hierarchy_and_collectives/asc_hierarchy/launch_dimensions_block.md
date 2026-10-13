# asc::launch_dimensions::block

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

头文件路径为：`<asc/hierarchy>`。

`asc::launch_dimensions::block`提供Block层级的全局常量标签。

## 声明

所属类型：[`asc::launch_dimensions`](launch_dimensions.md)。

```cpp
// asc::launch_dimensions 类内的声明节选；模板形参和其他成员由所属类提供。
asc::extent3d block;
```

## 约束说明

- 提供C++17 constexpr Host/Device层次结构接口。
- 带extent的值要求每一维均非零。
- extent总数按无符号64位的x*y*z计算。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/hierarchy>

bool example()
{
    asc::launch_dimensions dimensions{asc::extent3d{2, 1, 1}, asc::extent3d{32, 1, 1}};
    return dimensions.grid.count() == 2 && dimensions.block.count() == 32;
}
```

## 关联API

- [`asc::launch_dimensions`](launch_dimensions.md)
- [本头文件的接口列表](asc_hierarchy.md)
