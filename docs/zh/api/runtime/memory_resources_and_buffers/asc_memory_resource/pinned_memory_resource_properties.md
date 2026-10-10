# asc::pinned_memory_resource::properties

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

`asc::pinned_memory_resource::properties` 返回页锁定内存资源属性：Host 可访问、Device 不可访问，最大对齐为 `alignof(max_align_t)`。

## 函数原型

```cpp
static constexpr asc::memory_resource_properties asc::pinned_memory_resource::properties() noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::memory_resource_properties` | 返回页锁定内存资源属性：Host 可访问、Device 不可访问，最大对齐为 `alignof(max_align_t)`。 |

## 约束说明

- 仅可在 Host 调用
- 内存资源不抛出异常
- 分配大小、对齐和输出指针必须有效，释放时须使用同一资源及原始大小和对齐
- 资源及其引用的生命周期由调用方管理

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/memory_resource>

void example(asc::pinned_memory_resource& object)
{
    (void)object.properties();
}
```
