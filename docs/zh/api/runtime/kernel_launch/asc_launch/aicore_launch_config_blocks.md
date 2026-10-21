# asc::aicore_launch_config::blocks

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

`asc::aicore_launch_config::blocks`指定要启动的AICore Block数量，该值必须大于零。

## 声明

所属类型：[`asc::aicore_launch_config`](aicore_launch_config.md)。

```cpp
// asc::aicore_launch_config 类内的声明节选；模板形参和其他成员由所属类提供。
asc::std::uint32_t blocks;
```

## 约束说明

- 本类型或成员只描述Host侧启动配置，不提交核函数；实际启动要求见`launch`。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/launch>

bool example()
{
    asc::aicore_launch_config config{2};
    return config.blocks == 2;
}
```

## 关联API

- [`asc::aicore_launch_config`](aicore_launch_config.md)
- [本头文件的接口列表](asc_launch.md)
