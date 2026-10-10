# asc::work_queue_ref

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

头文件路径为：`<asc/work_queue>`。

`asc::work_queue_ref<Index>` 非拥有地引用调用方管理的 GM 原子游标，并按值保存任务结束位置和每次领取的粒度。

该接口的可用位置为 AI Core SIMD 编程、AI Core SIMT 编程。

## 声明

```cpp
template<class Index> class asc::work_queue_ref
```

## 约束说明

- Index 必须为受支持的 32 位或 64 位无符号整数
- 游标须位于可用的 GM 并在所有并发领取完成前保持有效
- 非正粒度会按 1 保存
- 接口不保证领取顺序或公平性

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/work_queue>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

__aicore__ void example()
{
    // 默认构造只建立空的引用值，实际领取前须绑定有效的 GM 游标。
    asc::work_queue_ref<asc::std::uint32_t> queue{};
    (void)queue.grain_size();
}
```
