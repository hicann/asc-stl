# asc::pointer_attributes

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

头文件路径为：`<asc/memory>`。

`asc::pointer_attributes`保存指针所处内存空间、Host/Device可访问性以及所属分配的字节数。

## 声明

```cpp
namespace asc {
class pointer_attributes;
} // namespace asc
```

## 约束说明

- 属性对象仅描述查询结果，不拥有或延长指针及其底层分配的生命周期。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/memory>

bool example()
{
    asc::pointer_attributes attributes;
    return attributes.space == asc::memory_space::local;
}
```

## 关联API

- [本头文件的接口列表](asc_memory.md)
