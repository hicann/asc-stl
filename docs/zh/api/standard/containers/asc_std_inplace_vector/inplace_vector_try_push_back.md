# asc::std::inplace_vector::try_push_back

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

`asc::std::inplace_vector::try_push_back`尝试在容器末尾追加`value`。容量充足时构造新元素并返回其引用；容器已满时返回空结果，容器内容保持不变。

该接口支持Host和Device，均限于本页列出的非抛出操作。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

所属类型：[`inplace_vector<T, Capacity>`](inplace_vector.md)。以下为类内声明，类型别名及模板形参由所属类提供。

### 原型1

```cpp
constexpr optional<reference> try_push_back(const T& value);
```

### 原型2

```cpp
constexpr optional<reference> try_push_back(T&& value);
```

## 参数说明

### 原型1的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 用于复制构造末尾新元素的值。 |

### 原型2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 用于移动构造末尾新元素的值；构造时可能消耗来源。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `optional<reference>` | 有容量时借用新元素；容量已满时为空，不构造或消耗来源。 |
| 原型2 | `optional<reference>` | 有容量时借用新元素；容量已满时为空，不构造或消耗来源。 |

## 约束说明

- 容量不足时返回空optional，不构造新元素；有容量时返回借用新元素的optional<T&>。
- 非空结果借用的元素必须继续存活；元素构造要求仍须满足。
- 元素的对应构造、赋值和析构须满足非抛出使用域；constexpr声明不保证任意T和语言模式都能常量求值。

## 调用示例

以下示例展示插入成功和容量耗尽两种结果，并检查容器最终状态。

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 2> values;
    const auto first = values.try_push_back(7);
    const auto second = values.try_push_back(9);
    const auto overflow = values.try_push_back(11);

    // 前两次插入成功；达到固定容量后，第三次插入返回空结果。
    return first.has_value() && *first == 7
        && second.has_value() && *second == 9
        && !overflow.has_value()
        && values.size() == 2;
}
```

## 关联API

- [`asc::std::inplace_vector`](inplace_vector.md)
- [本头文件的接口列表](asc_std_inplace_vector.md)
