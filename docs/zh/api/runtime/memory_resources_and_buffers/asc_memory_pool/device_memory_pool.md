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

`asc::device_memory_pool`是可移动、不可复制的Device内存池拥有者。释放操作先在指定Stream上记录事件，只有事件完成的内存块才会进入缓存并被后续分配复用。

该接口的可用位置为Host。

## 声明

```cpp
namespace asc {
class device_memory_pool;
}  // namespace asc
```

## 约束说明

- Host软件内存池最多登记64个同时保留的块；表满时新块请求返回insufficient_storage，与设备剩余容量无关。
- 使用同一池分配和异步释放；释放须排在该Stream对该块的全部使用之后，只有退休Event完成后才可复用。
- close前须归还所有in-use块；失败会保留未释放块和有效所有权，调用方须处理状态并可重试。
- Device池操作要求当前Runtime Device与配置ordinal一致；并发操作由元数据锁保护，池及Stream须在使用期间有效。

## 调用示例

以下Host示例在设备0上初始化Runtime，检查资源状态，并在资源释放后关闭Runtime；运行需要已安装CANN且设备可用。

```cpp
#include <acl/acl.h>
#include <asc/memory_pool>

bool resource_example()
{
    asc::device_memory_pool pool;
    asc::device_memory_pool_config config{};
    if (!asc::device_memory_pool::create(pool, config).success())
        return false;
    const bool ready = pool.valid() && pool.statistics().reserved_bytes() == 0;
    const bool closed = pool.close().success();
    return ready && closed && !pool.valid();
}

bool example()
{
    if (aclInit(nullptr) != ACL_SUCCESS)
        return false;
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
