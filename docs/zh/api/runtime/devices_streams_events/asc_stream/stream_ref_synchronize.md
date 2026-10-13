# asc::stream_ref::synchronize

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

头文件路径为：`<asc/stream>`。

`asc::stream_ref::synchronize`阻塞Host，直到该Stream中此前提交的任务完成；空句柄或Runtime调用失败时返回false。

## 函数原型

所属类型：[`asc::stream_ref`](stream_ref.md)。

```cpp
// asc::stream_ref 类内的声明节选；模板形参和其他成员由所属类提供。
bool synchronize() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 提供可为空的非拥有Host引用。
- 原生句柄为不透明void指针。
- 仅当CANN Runtime调用成功时才更新查询结果和输出参数。

## 调用示例

以下Host示例在设备0上初始化Runtime，检查资源状态，并在资源释放后关闭Runtime；运行需要已安装CANN且设备可用。

```cpp
#include <acl/acl.h>
#include <asc/stream>

bool resource_example()
{
    asc::stream owner;
    if (!asc::make_stream(owner)) return false;
    asc::stream_ref view(owner.native_handle());
    const bool observed = view.synchronize();
    const bool closed = owner.close();
    return observed && closed;
}

bool example()
{
    if (aclInit(nullptr) != ACL_SUCCESS) return false;
    if (aclrtSetDevice(0) != ACL_SUCCESS) {
        const bool finalized = aclFinalize() == ACL_SUCCESS;
        return finalized && false;
    }
    const bool passed = resource_example();
    const bool reset = aclrtResetDevice(0) == ACL_SUCCESS;
    const bool finalized = aclFinalize() == ACL_SUCCESS;
    return passed && reset && finalized;
}
```

## 关联API

- [`asc::stream_ref`](stream_ref.md)
- [本头文件的接口列表](asc_stream.md)
