# asc::permutation_iterator

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

头文件路径为：`<asc/iterator>`。

`asc::permutation_iterator`使用索引迭代器重排访问数据迭代器中的元素。

## 声明

```cpp
namespace asc {
template<class Iterator, class IndexIterator = Iterator> class permutation_iterator;
} // namespace asc
```

## 约束说明

- 提供惰性、非拥有的迭代器适配器及其工厂。
- 操作数必须在当前执行位置有效。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/iterator>

bool example()
{
    int values[3] = {10, 20, 30};
    int indices[2] = {2, 0};
    asc::permutation_iterator<int*, int*> iterator(values, indices);
    const bool first = *iterator == 30;
    ++iterator;
    return first && *iterator == 10;
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
