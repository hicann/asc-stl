# asc::std::insert_iterator::operator*

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

`asc::std::insert_iterator::operator*` 解引用当前迭代器或有值对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
[[nodiscard]] constexpr insert_iterator<Container>& asc::std::insert_iterator::operator*() noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `insert_iterator<Container> &` | 返回当前迭代器或包装器所引用的对象。 |

## 约束说明

- 使用调用方提供的迭代器或容器
- 关系运算符均为显式提供

## 调用示例

以下 Host 片段使用调用方提供的标准容器演示迭代器操作；目标容器须保持有效。

```cpp
#include <asc/std/iterator>
#include <deque>
#include <functional>
#include <vector>

#include <vector>

decltype(auto) example()
{
    ::std::vector<int> values{};
    asc::std::insert_iterator<::std::vector<int>> output(values, values.begin());
    return *output;
}
```
