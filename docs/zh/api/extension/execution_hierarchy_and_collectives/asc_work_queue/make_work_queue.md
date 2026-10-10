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

`asc::make_work_queue` 将调用方管理的工作游标、结束索引和粒度组合为非拥有的 `work_queue_ref<Index>`，供并发任务领取接口使用。

该接口的可用位置为 AI Core SIMD 编程、AI Core SIMT 编程。

## 函数原型

```cpp
template<class Index> constexpr asc::work_queue_ref<Index> asc::make_work_queue(asc::detail::work_cursor& cursor, Index end, Index grain_size) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `cursor` | 输入/输出 | 提供“将调用方管理的工作游标、结束索引和粒度组合为非拥有的 `work_queue_ref<Index>`，供并发任务领取接口使用”使用的对象引用；被引用对象须在调用期间有效。 |
| `end` | 输入 | 提供“将调用方管理的工作游标、结束索引和粒度组合为非拥有的 `work_queue_ref<Index>`，供并发任务领取接口使用”所需的输入对象；类型须满足所选原型约束。 |
| `grain_size` | 输入 | 对象或范围的大小。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::work_queue_ref<Index>` | 返回引用调用方工作游标的非拥有队列对象。 |

## 约束说明

- Index 必须为受支持的 32 位或 64 位无符号整数
- grain_size 必须大于零
- cursor 在队列引用使用期间必须保持有效

## 调用示例

以下片段借用调用方初始化并保持有效的全局内存游标，建立一次领取四项的工作队列引用。

```cpp
#include <asc/work_queue>

__aicore__ decltype(auto) example(asc::detail::work_cursor& cursor)
{
    return asc::make_work_queue(cursor, 100u, 4u);
}
```
