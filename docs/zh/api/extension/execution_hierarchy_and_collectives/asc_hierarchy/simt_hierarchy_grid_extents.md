# asc::simt_hierarchy::grid_extents

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

`asc::simt_hierarchy::grid_extents` 保存 SIMT 层级中的 Grid 三维范围。

## 声明

```cpp
asc::extent3d asc::simt_hierarchy::grid_extents
```

## 约束说明

- 提供 C++17 constexpr Host/Device 层次结构接口
- 带 extent 的值要求每一维均非零
- extent 总数按无符号 64 位的 x*y*z 计算

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/hierarchy>

void example(const asc::simt_hierarchy& object)
{
    (void)object.grid_extents;
}
```
