# asc::memory_resource_properties::host_accessible

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

头文件路径为：`<asc/memory_resource>`。

`asc::memory_resource_properties::host_accessible`返回该资源分配的内存是否可由Host直接访问。

## 函数原型

所属类型：[`asc::memory_resource_properties`](memory_resource_properties.md)。

```cpp
// asc::memory_resource_properties 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr bool host_accessible() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 本操作在Host同步观察或保存资源属性，不提交分配和释放。
- 资源引用不拥有被引用对象，使用分配/释放成员时资源对象须仍有效；比较只判断引用是否关联同一对象。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/memory_resource>

bool example()
{
    asc::memory_resource_properties properties(true, false, 64);
    return properties.host_accessible() && !properties.device_accessible() && properties.maximum_alignment() == 64;
}
```

## 关联API

- [`asc::memory_resource_properties`](memory_resource_properties.md)
- [本头文件的接口列表](asc_memory_resource.md)
