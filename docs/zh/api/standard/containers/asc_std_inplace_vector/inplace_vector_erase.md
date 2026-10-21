# asc::std::inplace_vector::erase

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

头文件路径为：`<asc/std/inplace_vector>`。

`asc::std::inplace_vector::erase`按迭代器位置或半开范围删除元素，压紧后续元素，并返回删除位置后的新迭代器。

该接口支持Host和Device，均限于本页列出的非抛出操作。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

所属类型：[`inplace_vector<T, Capacity>`](inplace_vector.md)。以下为类内声明，类型别名及模板形参由所属类提供。

### 原型1

```cpp
constexpr iterator erase(const_iterator position);
```

### 原型2

```cpp
constexpr iterator erase(const_iterator first, const_iterator last);
```

## 参数说明

### 原型1的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `position` | 输入 | 本容器中可解引用的删除位置，不得为end()。 |

### 原型2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 删除半开范围的起点；与last构成本容器的有效有序子范围。 |
| `last` | 输入 | 删除范围尾后位置；可为end()，first==last表示不删除。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `iterator` | 返回删除位置后的元素位置；删除至末尾时为新的end()。 |
| 原型2 | `iterator` | 返回原first对应的新位置；删除至末尾时为新的end()，空范围不改变容器。 |

## 约束说明

- position须为本容器中可解引用的位置；范围形式要求[first,last)是本容器的有效有序子范围。
- 通过移动赋值压紧后续元素并销毁尾部；旧位置可能改为其它元素，使用返回的新迭代器。
- 元素的对应构造、赋值和析构须满足非抛出使用域；constexpr声明不保证任意T和语言模式都能常量求值。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(2) || !values.try_push_back(3)) return false;
    const auto next = values.erase(values.begin());
    return values.size() == 1 && next == values.begin() && *next == 3;
}
```

## 关联API

- [`asc::std::inplace_vector`](inplace_vector.md)
- [本头文件的接口列表](asc_std_inplace_vector.md)
