# asc::pinned_memory_pool

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

`asc::pinned_memory_pool`是可移动、不可复制的页锁定Host内存池拥有者。释放操作通过Stream事件延迟回收，已完成使用的内存块可按缓存上限复用或归还底层资源。

## 声明

```cpp
namespace asc {
class pinned_memory_pool;
} // namespace asc
```

## 约束说明

- 提供软件内存池、collect、trim、stats以及Event安全复用。

## 调用示例

以下Host示例在设备0上初始化Runtime，检查资源状态，并在资源释放后关闭Runtime；运行需要已安装CANN且设备可用。

```cpp
#include <acl/acl.h>
#include <asc/memory_pool>

bool resource_example()
{
    asc::pinned_memory_pool pool;
    asc::pinned_memory_pool_config config{};
    if (!asc::pinned_memory_pool::create(pool, config).success()) return false;
    const bool ready = pool.valid() && pool.statistics().reserved_bytes() == 0;
    const bool closed = pool.close().success();
    return ready && closed && !pool.valid();
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

- [本头文件的接口列表](asc_memory_pool.md)
