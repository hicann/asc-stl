# asc::extent3d

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

`asc::extent3d`保存X、Y、Z三个维度的无符号范围。

## 声明

```cpp
namespace asc {
struct extent3d;
}  // namespace asc
```

## 约束说明

- 逐轴尺寸须满足当前设备的合法启动上限，x*y*z必须在unsigned long long中可表示；仅非零不足以保证这一条件。这里的值操作不校验实际硬件限制。

- 提供C++17 constexpr Host/Device层次结构接口。
- 带extent的值要求每一维均非零。
- extent总数按无符号64位的x*y*z计算。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/hierarchy>

bool example()
{
    asc::extent3d dimensions(2, 3, 4);
    return dimensions.x == 2 && dimensions.y == 3 && dimensions.z == 4 && dimensions.count() == 24;
}
```

## 关联API

- [本头文件的接口列表](asc_hierarchy.md)
