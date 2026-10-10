# asc::std::front_insert_iterator::operator++

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

`asc::std::front_insert_iterator::operator++` 把当前迭代器或计数值推进一步。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型 1

```cpp
constexpr front_insert_iterator<Container>& asc::std::front_insert_iterator::operator++() noexcept;
```

### 原型 2

```cpp
constexpr front_insert_iterator<Container> asc::std::front_insert_iterator::operator++(int unused) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `unused` | 输入 | 用于区分后置自增或后置自减形式的占位参数；调用时写作整数 0。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `front_insert_iterator<Container> &` | 返回更新后的当前对象引用。 |
| 原型 2 | `front_insert_iterator<Container>` | 返回更新后的迭代器或计数值。 |

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

#include <deque>

void example()
{
    ::std::deque<int> values{};
    asc::std::front_insert_iterator<::std::deque<int>> output(values);
    ++output;
}
```
