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

`asc::work_queue_ref<Index>`非拥有地引用调用方管理的GM原子游标，并按值保存任务结束位置和每次领取的粒度。

该接口的可用位置为AI Core SIMD编程、AI Core SIMT编程。

## 声明

```cpp
namespace asc {
template<class Index> class work_queue_ref;
} // namespace asc
```

## 约束说明

- Index必须为受支持的32位或64位无符号整数。
- 游标须位于可用的GM并在所有并发领取完成前保持有效。
- 非正粒度会按1保存。
- 认领终点饱和：领取块的终点在到达 end 前截断，游标越过 end 后返回空块，不再回绕产生新的有效任务。
- 接口不保证领取顺序或公平性。

## 调用示例

默认构造得到空队列引用；从空引用领取返回false并清空输出区间。实际并发领取须先绑定有效的GM游标。

```cpp
#include <asc/work_queue>
#include <asc/std/cstdint>

bool example()
{
    asc::work_queue_ref<asc::std::uint32_t> queue;
    asc::work_chunk<asc::std::uint32_t> chunk(2U, 5U);
    const bool acquired = asc::acquire_work(queue, chunk);
    return queue.cursor() == nullptr && queue.grain_size() == 1 && !acquired && chunk.empty();
}
```

## 关联API

- [本头文件的接口列表](asc_work_queue.md)
