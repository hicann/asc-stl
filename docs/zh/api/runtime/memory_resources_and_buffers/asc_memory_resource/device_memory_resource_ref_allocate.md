# asc::device_memory_resource_ref::allocate

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

`asc::device_memory_resource_ref::allocate`转发到被引用资源分配Device内存；无效引用返回参数错误，并在可能时把输出指针置空。

## 函数原型

所属类型：[`asc::device_memory_resource_ref`](device_memory_resource_ref.md)。

```cpp
// asc::device_memory_resource_ref 类内的声明节选；模板形参和其他成员由所属类提供。
asc::execution_status allocate(void** output, asc::std::size_t bytes, asc::std::size_t alignment = 32) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 用于接收分配地址的可写指针槽；槽本身非空且调用前 *output为nullptr。成功时写入资源分配的地址，失败时按返回状态处理。 |
| `bytes` | 输入 | 本次申请的非零字节数。 |
| `alignment` | 输入 | 要求的对齐值，单位为字节。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回本次同步分配／释放的状态；成功时本次操作已经完成。 |

## 约束说明

- 仅可在Host调用。
- 内存资源不抛出异常。
- 分配大小、对齐和输出指针必须有效，释放时须使用同一资源及原始大小和对齐。
- 资源及其引用的生命周期由调用方管理。

## 调用示例

以下Host片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/memory_resource>

asc::execution_status example(const asc::device_memory_resource_ref& resource)
{
    // 调用前完成 CANN 初始化；device 资源还要求当前 Device 与绑定值一致。
    void* pointer = nullptr;
    const auto status = resource.allocate(&pointer, 64);
    if (!status.success()) return status;
    return resource.deallocate(pointer, 64);
}
```

## 关联API

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md)：参数校验和任务提交状态；提交成功不表示异步工作已经完成。
