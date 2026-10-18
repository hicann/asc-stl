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

`asc::pinned_memory_resource_ref::deallocate`转发到被引用资源释放页锁定Host内存；无效引用返回参数错误。

## 函数原型

所属类型：[`asc::pinned_memory_resource_ref`](pinned_memory_resource_ref.md)。

```cpp
// asc::pinned_memory_resource_ref 类内的声明节选；模板形参和其他成员由所属类提供。
asc::execution_status deallocate(void* pointer, asc::std::size_t bytes, asc::std::size_t alignment = alignof(asc::std::max_align_t)) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 此前由对应资源分配、尚未释放的地址；非空地址须与本次字节数、对齐及设备归属匹配。有效资源上的空指针释放为无操作；无效资源引用仍返回参数错误。 |
| `bytes` | 输入 | 该分配最初申请的字节数，须与分配时一致。 |
| `alignment` | 输入 | 字节对齐值，须为2的非负整数次幂且不超过`alignof(asc::std::max_align_t)`；须与原分配时一致；仅在释放非空地址时校验。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回本次同步释放的状态；成功时本次操作已经完成。 |

## 约束说明

- 仅可在Host调用；运行时须已初始化。
- 本接口不抛出异常，失败通过`asc::execution_status`报告。
- 被引用的资源须在本次调用期间保持有效。无效引用返回`asc::execution_errc::invalid_argument`。
- 有效资源释放`nullptr`时直接返回成功，不校验`bytes`或`alignment`。
- 非空地址须来自同一资源且尚未释放；`bytes`和`alignment`须与分配时一致。
- 非空地址的`bytes`须大于0；`alignment`须为2的非负整数次幂且不超过`alignof(asc::std::max_align_t)`。参数不满足时返回`asc::execution_errc::invalid_argument`，不执行释放。
- 调用前须保证使用该分配的异步任务已经完成；释放失败时须根据状态处理，不能把地址视为已经释放。

## 调用示例

以下Host片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/memory_resource>

decltype(auto) example(asc::pinned_memory_resource_ref& resource, void* pointer)
{
    // pointer 必须是此前从同一资源成功分配的地址。
    return resource.deallocate(pointer, 64);
}
```

## 关联API

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md)：参数校验和任务提交状态；提交成功不表示异步工作已经完成。
