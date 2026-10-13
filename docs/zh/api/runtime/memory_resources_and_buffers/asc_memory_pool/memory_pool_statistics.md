# asc::memory_pool_statistics

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

`asc::memory_pool_statistics`是内存池状态快照，分别记录已向底层资源保留、正由调用方使用和已缓存待复用的字节数。

该接口的可用位置为Host。

## 声明

```cpp
namespace asc {
class memory_pool_statistics;
} // namespace asc
```

## 约束说明

- 提供软件内存池、collect、trim、stats以及Event安全复用。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/memory_pool>

bool example()
{
    asc::memory_pool_statistics statistics(128, 32, 96);
    return statistics.reserved_bytes() == 128 && statistics.used_bytes() == 32 && statistics.cached_bytes() == 96;
}
```

## 关联API

- [本头文件的接口列表](asc_memory_pool.md)
