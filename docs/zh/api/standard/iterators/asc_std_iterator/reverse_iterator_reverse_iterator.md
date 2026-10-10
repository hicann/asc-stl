# asc::std::reverse_iterator::reverse_iterator

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

`asc::std::reverse_iterator::reverse_iterator` 按本页所列构造形态初始化 `reverse_iterator` 对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型 1

```cpp
constexpr reverse_iterator(Iter first) noexcept(is_nothrow_copy_constructible_v<Iter>);
```

### 原型 2

```cpp
template<class It2> constexpr reverse_iterator() noexcept(is_nothrow_default_constructible_v<It2>);
```

### 原型 3

```cpp
template<class U> constexpr reverse_iterator(const reverse_iterator<U>& other) noexcept(Noexceptreviterconvertible<U, Iter>);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `It2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 约束说明

- 使用调用方提供的迭代器或容器
- 关系运算符均为显式提供

## 调用示例

以下 Host 片段以具体指针迭代器演示调用；调用方须保证所指范围及移动后位置有效。

```cpp
#include <asc/std/iterator>

void example(int* data)
{
    asc::std::reverse_iterator<int*> iterator(data);
    (void)iterator;
}
```
