# asc::acquire_work

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

`asc::acquire_work`从共享工作队列中原子领取一个互不重叠的索引区间，并将区间写入`chunk`。返回false表示没有剩余工作。

可在Host、AI Core SIMD编程和AI Core SIMT编程中使用各自适用的重载。

## 函数原型

Host和AI Core SIMT编程可使用队列引用或普通游标指针形式。

```cpp
namespace asc {
template<class Index>
bool acquire_work(work_queue_ref<Index> queue, work_chunk<Index>& chunk) noexcept;
} // namespace asc
```

```cpp
namespace asc {
template<class Index>
bool acquire_work(work_cursor* cursor, Index end, Index grain_size, work_chunk<Index>& chunk) noexcept;
} // namespace asc
```

AI Core SIMD编程须使用GM地址空间指针形式。

```cpp
namespace asc {
template<class Index>
bool acquire_work(__gm__ work_cursor* cursor, Index end, Index grain_size, work_chunk<Index>& chunk) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 支持的32位或64位无符号索引类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `queue` | 输入 | 引用调用方管理的并发工作队列；游标须在任务领取期间有效。 |
| `cursor` | 输入/输出 | 共享的工作游标；领取时以原子操作推进`next`。 |
| `end` | 输入 | 可领取范围的结束索引，不包含该值。 |
| `grain_size` | 输入 | 本次领取粒度；0按1处理。 |
| `chunk` | 输出 | 成功时接收半开区间；失败时置为空区间。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 领取到非空区间时返回`true`；游标为空或已到达结束位置时返回`false`。 |

## 约束说明

- Index必须为受支持的32位或64位无符号整数。
- 队列引用及其游标在并发领取期间必须保持有效。
- 正粒度与游标当前值相加须可由64位无符号整数表示；不能依赖溢出回绕继续领取。
- 本接口不保证线程领取顺序、公平性或隐式同步；游标构造和生命周期见[`asc::work_cursor`](work_cursor.md)。

## 调用示例

以下片段演示AI Core SIMT编程中的队列领取；普通AI Core SIMD编程应使用页面列出的全局内存游标指针重载。

```cpp
#include <asc/work_queue>

__aicore__ decltype(auto) example(asc::work_queue_ref<unsigned int> queue)
{
    asc::work_chunk<unsigned int> chunk;
    return asc::acquire_work(queue, chunk);
}
```

## 关联API

- [本头文件的接口列表](asc_work_queue.md)
