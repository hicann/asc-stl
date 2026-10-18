# asc::pinned_memory_resource::allocate

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

`asc::pinned_memory_resource::allocate`分配指定字节数的页锁定Host内存，并把地址写入原本为空的输出指针。

## 函数原型

所属类型：[`asc::pinned_memory_resource`](pinned_memory_resource.md)。

```cpp
// asc::pinned_memory_resource 类内的声明节选；模板形参和其他成员由所属类提供。
asc::execution_status allocate(void** output, asc::std::size_t bytes, asc::std::size_t alignment = alignof(asc::std::max_align_t)) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 用于接收分配地址的可写指针槽；槽本身非空且调用前 *output为nullptr。成功时写入资源分配的地址，失败时按返回状态处理。 |
| `bytes` | 输入 | 本次申请的非零字节数。 |
| `alignment` | 输入 | 字节对齐值，须为2的非负整数次幂且不超过`alignof(asc::std::max_align_t)`；默认值同上限。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回本次同步分配的状态；成功时本次操作已经完成。 |

## 约束说明

- 仅可在Host调用；运行时须已初始化。
- 本接口不抛出异常，失败通过`asc::execution_status`报告。
- `output`必须非空，且调用前`*output == nullptr`；`bytes`必须大于0。
- `alignment`须为2的非负整数次幂且不超过`alignof(asc::std::max_align_t)`。有效资源在上述参数校验失败时返回`asc::execution_errc::invalid_argument`，不写入`*output`。
- 底层分配失败通过返回状态报告；调用方仅在成功后使用输出地址。

## 调用示例

以下Host片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/memory_resource>

asc::execution_status example(const asc::pinned_memory_resource& resource)
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
