# asc::simt_launch_config::grid

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

头文件路径为：`<asc/launch>`。

`asc::simt_launch_config::grid`指定SIMT Kernel的三维Grid大小；每一维都必须非零，三维乘积不得溢出。

## 声明

所属类型：[`asc::simt_launch_config`](simt_launch_config.md)。

```cpp
// asc::simt_launch_config 类内的声明节选；模板形参和其他成员由所属类提供。
asc::extent3d grid;
```

## 约束说明

- 本类型或成员只描述Host侧启动配置，不提交核函数；实际启动要求见`launch`。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/launch>

bool example()
{
    asc::simt_launch_config config{asc::extent3d{2, 1, 1}, asc::extent3d{32, 1, 1}, 0};
    return config.grid.count() == 2 && config.block.count() == 32 && config.dynamic_ub_bytes == 0;
}
```

## 关联API

- [`asc::simt_launch_config`](simt_launch_config.md)
- [本头文件的接口列表](asc_launch.md)
