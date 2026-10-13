# asc::std::default_searcher

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

`asc::std::default_searcher`保存搜索模式及比较条件以供子序列查找。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 声明

```cpp
namespace asc::std {
template<class ForwardIterator, class BinaryPredicate = asc::std::equal_to<>> class default_searcher;
} // namespace asc::std
```

## 约束说明

- 提供标准算术类型、枚举和指针类型的hash特化。
- default_searcher使用调用方管理的对象和存储。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/functional>

bool example()
{
    int values[] = {1, 2, 3, 4};
    int pattern[] = {2, 3};
    asc::std::default_searcher<int*> searcher(pattern, pattern + 2);
    auto result = searcher(values, values + 4);
    return result.first == values + 1 && result.second == values + 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_functional.md)
