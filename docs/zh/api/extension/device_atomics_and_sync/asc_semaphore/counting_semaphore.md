# asc::counting_semaphore

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

头文件路径为：`<asc/semaphore>`。

`asc::counting_semaphore`维护可并发获取和释放的计数信号量。

## 声明

```cpp
namespace asc {
template<asc::memory_scope Scope, asc::std::ptrdiff_t LeastMaxValue = 2147483647> class counting_semaphore;
} // namespace asc
```

## 约束说明

- 使用C++17。
- 在AI Core SIMT编程 中操作调用方管理的GM状态。
- Scope必须为asc::memory_scope::block或asc::memory_scope::device。
- 所有阻塞参与者必须能够并发推进。
- 复制构造和复制赋值已删除。

## 调用示例

以下片段按AI Core SIMT编程编译。permits是GM中已构造的信号量，初始许可数在[0, 2] 内；示例在成功取得许可后归还。

```cpp
#include <asc/semaphore>

__aicore__ bool example(asc::counting_semaphore<asc::memory_scope::device, 2>& permits)
{
    if (!permits.try_acquire()) return false;
    // 在此访问受许可保护的资源。
    permits.release();
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_semaphore.md)
