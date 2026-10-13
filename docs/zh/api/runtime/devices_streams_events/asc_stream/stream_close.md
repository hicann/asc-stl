# asc::stream::close

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

`asc::stream::close`同步并销毁当前持有的Runtime Stream；成功后对象变为空，空对象直接返回true。

## 函数原型

所属类型：[`asc::stream`](stream.md)。

```cpp
// asc::stream 类内的声明节选；模板形参和其他成员由所属类提供。
bool close() noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 仅可在Host使用且对象不可复制。
- 移动操作转移资源所有权。
- close()负责同步并销毁自身资源，失败时保留所有权。
- 析构函数会尝试完成本地清理。

## 调用示例

以下Host示例在设备0上初始化Runtime，检查资源状态，并在资源释放后关闭Runtime；运行需要已安装CANN且设备可用。

```cpp
#include <acl/acl.h>
#include <asc/stream>

bool resource_example()
{
    asc::stream owner;
    if (!asc::make_stream(owner)) return false;
    const bool closed = owner.close();
    return closed && !owner;
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

- [`asc::stream`](stream.md)
- [本头文件的接口列表](asc_stream.md)
