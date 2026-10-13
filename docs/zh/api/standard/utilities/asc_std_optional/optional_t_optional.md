# asc::std::optional<T&>::optional

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

头文件路径为：`<asc/std/optional>`。

`asc::std::optional<T&>::optional`按本页所列构造形态初始化`optional<T&>`对象。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

### 原型1

```cpp
// asc::std::optional<T&> 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr optional() noexcept;
```

### 原型2

```cpp
// asc::std::optional<T&> 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr optional(T& value) noexcept;
```

### 原型3

```cpp
// asc::std::optional<T&> 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr optional(asc::std::nullopt_t) noexcept;
```

### 原型4

```cpp
// asc::std::optional<T&> 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr optional(const asc::std::optional<T&>&) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 被绑定的对象；新optional保存指向它的引用，对象生命周期须覆盖optional使用期。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `asc` | 输入 | nullopt_t空状态标记（nullopt常量）；构造不含引用的空optional。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `参数1` | 输入 | 复制来源optional<T&>；新对象绑定到其引用的同一目标。 |

## 返回值说明

无返回值。

## 约束说明

- 引用特化仅允许安全的同类型左值绑定。
- 采用借用指针语义，不提供容易产生悬空引用的转换。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/optional>

bool example()
{
    int number = 7;
    asc::std::optional<int&> value(number);
    return value.has_value() && &*value == &number;
}
```

## 关联API

- [本头文件的接口列表](asc_std_optional.md)
