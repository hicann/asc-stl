# asc::pinned_memory_resource_ref::deallocate

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

`asc::pinned_memory_resource_ref::deallocate` 转发到被引用资源释放页锁定 Host 内存；无效引用返回参数错误。

## 函数原型

```cpp
asc::execution_status asc::pinned_memory_resource_ref::deallocate(void* pointer, asc::std::size_t bytes, asc::std::size_t alignment = alignof(asc::std::max_align_t)) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“转发到被引用资源释放页锁定 Host 内存”所需的数据地址；可访问范围和生命周期须满足约束。 |
| `bytes` | 输入 | 处理的数据量，单位为字节。 |
| `alignment` | 输入 | 要求的对齐值，单位为字节。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- 仅可在 Host 调用
- 内存资源不抛出异常
- 分配大小、对齐和输出指针必须有效，释放时须使用同一资源及原始大小和对齐
- 资源及其引用的生命周期由调用方管理

## 调用示例

以下 Host 片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/memory_resource>

decltype(auto) example(asc::pinned_memory_resource_ref& resource, void* pointer)
{
    // pointer 必须是此前从同一资源成功分配的地址。
    return resource.deallocate(pointer, 64);
}
```
