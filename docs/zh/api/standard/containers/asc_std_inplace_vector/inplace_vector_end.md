# asc::std::inplace_vector::end

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

`asc::std::inplace_vector::end`返回指向尾后位置的迭代器。

该接口支持Host和Device，均限于本页列出的非抛出操作。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

所属类型：[`inplace_vector<T, Capacity>`](inplace_vector.md)。以下为类内声明，类型别名及模板形参由所属类提供。

### 原型1

```cpp
constexpr iterator end() noexcept;
```

### 原型2

```cpp
constexpr const_iterator end() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `iterator` | 借用当前容器的尾后位置；容器须继续存活，尾后位置不可解引用。 |
| 原型2 | `const_iterator` | 借用当前容器的尾后位置；容器须继续存活，尾后位置不可解引用。 |

## 约束说明

- 返回位置借用对象内存储；尾后迭代器不可解引用，容器析构后位置失效。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(1)) return false;
    if (!values.try_push_back(3)) return false;
    auto last = values.end();
    auto current = values.begin();
    unsigned int count = 0;
    for (; current != last; ++current) ++count;
    return count == 2;
}
```

## 关联API

- [`asc::std::inplace_vector`](inplace_vector.md)
- [本头文件的接口列表](asc_std_inplace_vector.md)
