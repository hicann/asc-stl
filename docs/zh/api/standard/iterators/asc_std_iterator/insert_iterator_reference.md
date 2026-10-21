# asc::std::insert_iterator::reference

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

`asc::std::insert_iterator::reference`标识可写元素引用类型。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

所属类型：[`asc::std::insert_iterator`](insert_iterator.md)。

```cpp
// asc::std::insert_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
using reference = void;
```

## 约束说明

- 目标容器须支持对应的`insert(position, value)`操作；插入迭代器保存容器地址，不拥有容器。
- 容器须在适配器使用期间有效；插入操作还须遵守目标容器自身的迭代器失效规则。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <vector>
#include <asc/std/type_traits>

bool example()
{
    using selected = typename asc::std::insert_iterator<::std::vector<int>>::reference;
    static_assert(asc::std::is_same_v<selected, void>);
    return true;
}
```

## 关联API

- [`asc::std::insert_iterator`](insert_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
