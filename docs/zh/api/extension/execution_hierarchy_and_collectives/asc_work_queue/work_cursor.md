# asc::work_cursor

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

`asc::work_cursor`是调用方管理的工作游标类型的公共别名，记录下一个待领取索引、结束索引和领取粒度。通过[`make_work_queue`](make_work_queue.md)创建借用它的队列引用。

## 声明

包含`<asc/work_queue>`后可直接使用类型名`asc::work_cursor`。其具体类型由库提供，无需包含实现头文件。

## 参数说明

默认构造将`next`、`end`初始化为0，将`grain_size`初始化为1。三参数构造依次接收起始索引、结束索引和粒度，参数均为64位无符号整数；粒度为0时按1处理。

| 公共字段 | 描述 |
| --- | --- |
| `next` | 下一个待领取索引；并发领取时由原子操作推进。 |
| `end` | 结束索引，不包含在可领取范围内。 |
| `grain_size` | 每次请求领取的元素数量。 |

## 约束说明

- 游标由调用方拥有；所有借用它的队列和领取操作结束前，游标须保持有效。
- 在Device上并发领取时，游标须位于参与者共同可访问的GM中，并在并发访问前完成初始化。
- 并发期间不得以普通读写修改这些字段；队列的范围上界和粒度由创建队列时的值确定。
- 索引和粒度须满足[`acquire_work`](acquire_work.md)的范围及算术约束。

## 调用示例

以下Host示例验证公共类型的构造、队列借用和第一次领取的区间。

```cpp
#include <asc/work_queue>

bool example()
{
    asc::work_cursor cursor{0, 20, 7};
    auto queue = asc::make_work_queue<unsigned>(cursor, 20u, 7u);
    asc::work_chunk<unsigned> chunk;
    return queue.cursor() == &cursor && asc::acquire_work(queue, chunk) &&
        chunk.begin == 0 && chunk.end == 7;
}
```

## 关联API

- [创建工作队列](make_work_queue.md)
- [领取工作区间](acquire_work.md)
- [本头文件的接口列表](asc_work_queue.md)
