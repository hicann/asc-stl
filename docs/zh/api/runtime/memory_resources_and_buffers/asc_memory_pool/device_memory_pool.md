# asc::device_memory_pool

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

头文件路径为：`<asc/memory_pool>`。

`asc::device_memory_pool` 是可移动、不可复制的 Device 内存池拥有者。释放操作先在指定 Stream 上记录事件，只有事件完成的内存块才会进入缓存并被后续分配复用。

该接口的可用位置为 Host。

## 声明

```cpp
class asc::device_memory_pool
```

## 约束说明

- 提供软件内存池、collect、trim、stats 以及 Event 安全复用

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/memory_pool>

void use_type(const asc::device_memory_pool& value)
{
    (void)value;
}
```
