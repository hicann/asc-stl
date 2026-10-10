# asc::std::rbegin

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

`asc::std::rbegin` 取得逆序范围起始迭代器。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型 1

```cpp
template<class C> constexpr auto asc::std::rbegin(C& c) -> decltype(c.rbegin());
```

### 原型 2

```cpp
template<class C> constexpr auto asc::std::rbegin(const C& c) -> decltype(c.rbegin());
```

### 原型 3

```cpp
template<class T, asc::std::size_t N> constexpr asc::std::reverse_iterator<T*> asc::std::rbegin(T (&array)[N]);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `C` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `c` | 输入/输出 | 提供“取得逆序范围起始迭代器”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `C` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `c` | 输入 | 提供“取得逆序范围起始迭代器”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `N` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `array` | 输入/输出 | 提供“取得逆序范围起始迭代器”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `decltype(c.rbegin())` | 返回逆序范围起始迭代器。 |
| 原型 2 | `decltype(c.rbegin())` | 返回逆序范围起始迭代器。 |
| 原型 3 | `asc::std::reverse_iterator<T*>` | 返回逆序范围起始迭代器。 |

## 约束说明

- 支持非 I/O 范围、数组和用户容器

## 调用示例

以下 Host 片段使用具体数组或显式容器演示调用；迭代器须保持在有效范围内。

```cpp
#include <asc/std/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    return asc::std::rbegin(values);
}
```
