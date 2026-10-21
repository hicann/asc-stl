# asc::device_properties::l2_cache_bytes

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

头文件路径为：`<asc/devices>`。

`asc::device_properties::l2_cache_bytes`保存Device的L2 Cache容量，单位为字节。

## 声明

所属类型：[`asc::device_properties`](device_properties.md)。

```cpp
// asc::device_properties 类内的声明节选；模板形参和其他成员由所属类提供。
asc::std::uint64_t l2_cache_bytes;
```

## 约束说明

- 本页描述已保存的设备属性值、架构枚举或ordinal比较；观察这些值不查询Runtime。
- 获取实际设备属性时的初始化和设备可用要求见`device_ref::properties`；比较ordinal不证明对应设备实际存在。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/devices>

bool example()
{
    // 默认属性是查询前的空值，不代表任何真实设备的规格。
    asc::device_properties properties{};
    return properties.l2_cache_bytes == 0;
}
```

## 关联API

- [`asc::device_properties`](device_properties.md)
- [本头文件的接口列表](asc_devices.md)
