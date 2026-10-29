# asc::extent3d::`operator!=`

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

`asc::extent3d::operator!=`比较两个三维范围是否至少有一个维度不同。

## 函数原型

所属类型：[`asc::extent3d`](extent3d.md)。

```cpp
// asc::extent3d 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr bool operator!=(asc::extent3d other) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 比较的另一操作数；本次比较不修改对象。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 提供C++17 constexpr Host/Device层次结构接口。
- 带extent的值要求每一维均非零。
- extent总数按无符号64位的x*y*z计算。

## 调用示例

以下Host示例使用具体类型或维度，检查独立的预期值；不查询正在运行的Device执行上下文。

```cpp
#include <asc/hierarchy>

bool example()
{
    const asc::extent3d left(2, 3, 4);
    const asc::extent3d same(2, 3, 4);
    const asc::extent3d changed_x(7, 3, 4);
    const asc::extent3d changed_y(2, 7, 4);
    const asc::extent3d changed_z(2, 3, 7);
    return !(left != same) && left != changed_x && left != changed_y && left != changed_z;
}
```

## 关联API

- [`asc::extent3d`](extent3d.md)
- [本头文件的接口列表](asc_hierarchy.md)
