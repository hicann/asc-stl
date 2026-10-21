# asc::std::back_insert_iterator::back_insert_iterator

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

`asc::std::back_insert_iterator::back_insert_iterator`按本页所列构造形态初始化`back_insert_iterator`对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
constexpr explicit back_insert_iterator(Container& container);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入/输出 | 提供“按本页所列构造形态初始化`back_insert_iterator`对象”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

无返回值。

## 约束说明

- 目标容器须支持对应的`push_back(value)`操作；插入迭代器保存容器地址，不拥有容器。
- 容器须在适配器使用期间有效；插入操作还须遵守目标容器自身的迭代器失效规则。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <vector>

bool example()
{
    ::std::vector<int> values;
    asc::std::back_insert_iterator<::std::vector<int>> output(values);
    *output = 7;
    *output = 9;
    return values.size() == 2 && values[0] == 7 && values[1] == 9;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
