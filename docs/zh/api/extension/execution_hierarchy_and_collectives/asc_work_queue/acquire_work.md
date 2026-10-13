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

该接口的可用位置为AI Core SIMD编程、AI Core SIMT编程。

## 函数原型

```cpp
namespace asc {
template<class Index> bool acquire_work(asc::work_queue_ref<Index> queue, asc::work_chunk<Index>& chunk) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `queue` | 输入 | 引用调用方管理的并发工作队列；游标须在任务领取期间有效。 |
| `chunk` | 输入/输出 | 接收本次领取的非重叠工作区间。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- Index必须为受支持的32位或64位无符号整数。
- 队列引用及其游标在并发领取期间必须保持有效。
- 接口不保证领取顺序或公平性。

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
