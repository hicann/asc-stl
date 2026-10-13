# asc::std::ranges::subrange::subrange

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::subrange::subrange` 按本页所列构造形态初始化 `subrange` 对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型 1

```cpp
subrange();
```

### 原型 2

```cpp
template<class It> constexpr subrange(It first, Sent sentinel);
```

### 原型 3

```cpp
template<class It> constexpr subrange(It first, Sent sentinel, make_unsigned_t<iter_difference_t<Iter>> last);
```

### 原型 4

```cpp
template<class Range> constexpr subrange(Range&& base);
```

### 原型 5

```cpp
template<class Range> constexpr subrange(Range&& base, make_unsigned_t<iter_difference_t<Iter>> first);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `It` | 子范围使用的迭代器类型，须满足输入迭代器要求。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 子范围的起始迭代器或指针。 |
| `sentinel` | 输入 | 子范围的尾后哨兵，与 first 配对界定范围。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `It` | 子范围使用的迭代器类型，须满足输入迭代器要求。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 子范围的起始迭代器或指针。 |
| `sentinel` | 输入 | 子范围的尾后哨兵，与 first 配对界定范围。 |
| `last` | 输入 | 范围内元素个数，类型为迭代器差值的无符号版本；须与实际长度一致，供 size() 免遍历使用。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Range` | 输入范围或视图的类型；须满足所选原型的遍历要求。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入/输出 | 被截取的底层范围或视图；视图按值包装，左值容器按首尾迭代器截取。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Range` | 输入范围或视图的类型；须满足所选原型的遍历要求。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入/输出 | 被截取的底层范围或视图；视图按值包装，左值容器按首尾迭代器截取。 |
| `first` | 输入 | 范围内元素个数，类型为迭代器差值的无符号版本；须与 base 范围实际长度一致，供 size() 免遍历使用。 |

## 约束说明

- C++20 视图不进行动态内存分配
- owning_view 仅拥有调用方传入的范围对象，不产生额外分配

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ranges>

void example()
{
    asc::std::ranges::subrange<int*> value{};
    (void)value;
}
```
