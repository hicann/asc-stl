# asc::std::default_searcher::default_searcher

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

头文件路径为：`<asc/std/functional>`。

`asc::std::default_searcher::default_searcher` 按本页所列构造形态初始化 `default_searcher` 对象。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

```cpp
asc::std::default_searcher::default_searcher(ForwardIterator first, ForwardIterator last, BinaryPredicate pred = BinaryPredicate());
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `pred` | 输入 | 用于判断元素是否满足条件的可调用对象。 |

## 约束说明

- 提供标准算术类型、枚举和指针类型的 hash 特化
- default_searcher 使用调用方管理的对象和存储

## 调用示例

以下 Host 片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/functional>

void example(int* pattern)
{
    asc::std::default_searcher<int*> searcher(pattern, pattern + 2);
    (void)searcher;
}
```
