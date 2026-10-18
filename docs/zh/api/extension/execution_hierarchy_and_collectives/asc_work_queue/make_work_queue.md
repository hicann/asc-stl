# asc::make_work_queue

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

`asc::make_work_queue`将调用方管理的工作游标、结束索引和粒度组合为非拥有的`work_queue_ref<Index>`，供并发任务领取接口使用。

该接口可用于Host和Device上的队列描述；实际领取操作还须满足其编程模式和地址空间约束。

## 函数原型

```cpp
namespace asc {
template<class Index> constexpr asc::work_queue_ref<Index> make_work_queue(asc::work_cursor& cursor, Index end, Index grain_size) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 工作索引类型：仅支持uint32_t与uint64_t。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `cursor` | 输入/输出 | 调用方管理的GM原子工作游标（work_cursor）引用：本调用仅借用不拥有，后续领取工作时以原子fetch-add前进其next值；须保持有效直至不再领取。 |
| `end` | 输入 | 工作索引上界（排他）：领取到的块被裁剪到该值以内。 |
| `grain_size` | 输入 | 每次领取的粒度（单个块的索引个数）：须为正，且游标值加该值不得溢出。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::work_queue_ref<Index>` | 返回引用调用方工作游标的非拥有队列对象。 |

## 约束说明

游标的构造和生命周期见[`asc::work_cursor`](work_cursor.md)。

- Index必须为受支持的32位或64位无符号整数。
- grain_size必须大于零。
- cursor在队列引用使用期间必须保持有效。

## 调用示例

以下Host示例给出具体输入，并检查结果。

```cpp
#include <asc/work_queue>

bool example()
{
    asc::work_cursor cursor{0, 20, 7};
    const auto queue = asc::make_work_queue<unsigned>(cursor, 20u, 7u);
    return queue.cursor() == &cursor && queue.end_value() == 20 && queue.grain_size() == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_work_queue.md)
