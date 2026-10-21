# asc::std::inplace_vector::inplace_vector

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

`asc::std::inplace_vector::inplace_vector`按本页所列构造形态初始化`inplace_vector`对象。

该接口支持Host和Device，均限于本页列出的非抛出操作。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

所属类型：[`inplace_vector<T, Capacity>`](inplace_vector.md)。以下为类内声明，类型别名及模板形参由所属类提供。

### 原型1

```cpp
constexpr inplace_vector() noexcept;
```

### 原型2

```cpp
constexpr inplace_vector(const inplace_vector& other);
```

### 原型3

```cpp
constexpr inplace_vector(inplace_vector&& other);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 逐元素复制构造的来源；来源元素保持不变。 |

### 原型3的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 逐元素移动构造的来源；来源size不变，元素状态由T的移动构造决定。 |

## 返回值说明

无返回值。

## 约束说明

- 元素存储位于容器对象内，不动态分配；Capacity是编译期固定容量。
- Host和Device均提供所列非抛出子集，不提供at、push_back、emplace_back或resize。
- 元素的对应构造、赋值和析构须满足非抛出使用域；constexpr声明不保证任意T和语言模式都能常量求值。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(1)) return false;
    if (!values.try_push_back(3)) return false;
    return values.size() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_inplace_vector.md)
