# asc::std::iter_move

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

`asc::std::iter_move`按迭代器定制规则取得可移动的引用或值。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

`asc::std::iter_move`是已初始化的常量可调用对象，以`asc::std::iter_move(iterator)`调用。实现类不作为公开类型；下列object_type只是查询示例别名。

```cpp
using object_type = decltype(asc::std::iter_move);
```

优先调用ADL发现的定制iter_move；否则，解引用为左值时取得其移动引用，其他情况下返回相应的解引用结果。

## 约束说明

- 迭代器须可解引用，定制或回退表达式须有效；定制可以返回与普通解引用不同的可移动结果类型。
- 返回引用时仍借用原元素存储；本操作不延长存储寿命，也不单独保证后续移动构造已发生。

## 调用示例

以下Host示例在底层对象存活期内检查调用结果。

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    int values[2] = {2, 4};
    int&& reference = asc::std::iter_move(values);
    static_assert(asc::std::is_same_v<decltype(reference), int&&>);
    reference = 7;
    return &reference == values && values[0] == 7 && values[1] == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
