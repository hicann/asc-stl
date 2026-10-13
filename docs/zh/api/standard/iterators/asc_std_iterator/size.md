# asc::std::size

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

`asc::std::size` 取得范围的元素数量。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型 1

```cpp
template<class Cont> constexpr auto asc::std::size(const Cont& value) noexcept(noexcept(value.size())) -> decltype(value.size());
```

### 原型 2

```cpp
template<class T, size_t Sz> constexpr size_t asc::std::size(const T (&value)[Sz]) noexcept;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Cont` | 容器类型；须提供 size() 成员。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被测量元素数量的容器；返回其 size() 的无符号形式。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 数组的元素类型。 |
| `Sz` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被测量元素数量的数组；返回其长度 Sz。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `decltype(value.size())` | 返回范围的元素数量。 |
| 原型 2 | `size_t` | 返回范围的元素数量。 |

## 约束说明

- 支持非 I/O 范围、数组和用户容器

## 调用示例

以下 Host 片段使用具体数组或显式容器演示调用；迭代器须保持在有效范围内。

```cpp
#include <asc/std/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    return asc::std::size(values);
}
```
