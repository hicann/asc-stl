# asc::temporary_storage_ref

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

`asc::temporary_storage_ref` 是不拥有存储的字节区间引用，同时记录地址、字节数和所属 `memory_space`，用于向执行策略提供临时工作空间。

## 声明

```cpp
class asc::temporary_storage_ref
```

## 约束说明

- 引用不管理底层存储生命周期
- 底层区域必须在使用该临时存储的操作完成前保持有效，且地址空间标记必须与实际存储一致

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/memory>

void use_type(const asc::temporary_storage_ref& value)
{
    (void)value;
}
```
