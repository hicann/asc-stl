# asc::work_chunk

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

`asc::work_chunk<Index>` 表示一次成功领取得到的半开任务区间 `[begin, end)`，可查询区间是否为空及包含的索引数量。

该接口的可用位置为 AI Core SIMD 编程、AI Core SIMT 编程。

## 声明

```cpp
template<class Index> class asc::work_chunk
```

## 约束说明

- Index 必须为受支持的 32 位或 64 位无符号整数
- 区间按 [begin, end) 解释，begin 不小于 end 时 empty 为 true 且 size 为 0

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
    // 明确指定索引类型，并查询一次领取的区间大小。
    asc::work_chunk<asc::std::uint32_t> chunk(2u, 5u);
    (void)chunk.size();
}
```
