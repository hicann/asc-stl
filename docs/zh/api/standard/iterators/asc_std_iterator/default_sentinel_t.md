# asc::std::default_sentinel_t

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

头文件路径为：`<asc/std/iterator>`。

`asc::std::default_sentinel_t`标识对应迭代器能力或结束哨兵类别。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

```cpp
namespace asc::std {
struct default_sentinel_t;
} // namespace asc::std
```

## 约束说明

- 默认哨兵仅作为结束标记；须与定义了该哨兵比较操作的迭代器配合使用，例如`counted_iterator`。
- 哨兵不持有范围，也不能解引用。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    asc::std::counted_iterator<int*> iterator(values, 2);
    int sum = 0;
    for (; iterator != asc::std::default_sentinel; ++iterator) sum += *iterator;
    return sum == 6 && iterator.count() == 0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
