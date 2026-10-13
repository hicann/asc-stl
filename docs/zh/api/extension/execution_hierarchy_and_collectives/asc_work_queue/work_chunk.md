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

`asc::work_chunk<Index>`表示一次成功领取得到的半开任务区间`[begin, end)`，可查询区间是否为空及包含的索引数量。

该接口的可用位置为AI Core SIMD编程、AI Core SIMT编程。

## 声明

```cpp
namespace asc {
template<class Index> class work_chunk;
} // namespace asc
```

## 约束说明

- Index必须为受支持的32位或64位无符号整数。
- 区间按[begin, end)解释，begin不小于end时empty为true且size为0。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/work_queue>
#include <asc/std/cstdint>

bool example()
{
    asc::work_chunk<asc::std::uint32_t> chunk(2U, 5U);
    return chunk.begin == 2 && chunk.end == 5 && chunk.size() == 3 && !chunk.empty();
}
```

## 关联API

- [本头文件的接口列表](asc_work_queue.md)
