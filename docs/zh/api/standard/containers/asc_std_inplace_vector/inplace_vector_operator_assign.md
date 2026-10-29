# asc::std::inplace_vector::`operator=`

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

`asc::std::inplace_vector::operator=`按所选赋值重载更新对象，并返回规定的结果。

该接口支持Host和Device，均限于本页列出的非抛出操作。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

所属类型：[`inplace_vector<T, Capacity>`](inplace_vector.md)。以下为类内声明，类型别名及模板形参由所属类提供。

### 原型1

```cpp
constexpr inplace_vector& operator=(const inplace_vector& other);
```

### 原型2

```cpp
constexpr inplace_vector& operator=(inplace_vector&& other);
```

## 参数说明

### 原型1的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 复制赋值来源；按公共前缀赋值，并构造或销毁数量差额。 |

### 原型2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 移动赋值来源；来源size不变，元素可能被移动。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `inplace_vector&` | 返回*this引用；接收对象须覆盖该引用使用期。 |
| 原型2 | `inplace_vector&` | 返回*this引用；接收对象须覆盖该引用使用期。 |

## 约束说明

- 对应的元素复制/移动构造和赋值须有效；移动后来源保留元素数量，元素状态由T决定。
- 元素的对应构造、赋值和析构须满足非抛出使用域；constexpr声明不保证任意T和语言模式都能常量求值。

## 调用示例

以下Host片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/inplace_vector>
#include <memory>

bool example()
{
    using sequence = asc::std::inplace_vector<int, 8>;
    sequence values;
    values.unchecked_push_back(7);
    sequence target;
    target = values;
    return !target.empty() && target.front() == 7;
}
```

## 关联API

- [`asc::std::inplace_vector`](inplace_vector.md)
- [本头文件的接口列表](asc_std_inplace_vector.md)
