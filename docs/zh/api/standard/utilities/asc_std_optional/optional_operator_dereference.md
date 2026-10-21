# asc::std::optional::`operator*`

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

`asc::std::optional::operator*`解引用当前迭代器或有值对象。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

所属类型：[`asc::std::optional`](optional.md)。

### 原型1

```cpp
// asc::std::optional 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr T& operator*()& noexcept;
```

### 原型2

```cpp
// asc::std::optional 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr T&& operator*()&& noexcept;
```

### 原型3

```cpp
// asc::std::optional 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr const T& operator*() const& noexcept;
```

### 原型4

```cpp
// asc::std::optional 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr const T&& operator*() const&& noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

无参数。

### 原型3的参数

无参数。

### 原型4的参数

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `T&` | 返回当前迭代器或包装器所引用的对象。 |
| 原型2 | `T&&` | 返回当前迭代器或包装器所引用的对象。 |
| 原型3 | `const T&` | 返回当前迭代器或包装器所引用的对象。 |
| 原型4 | `const T&&` | 返回当前迭代器或包装器所引用的对象。 |

## 约束说明

- T必须是普通的非引用对象类型。
- Host遵循有效的C++17操作。
- Device侧构造、赋值、调用和交换所依赖的操作必须不抛出异常。
- 返回的引用、指针或非拥有包装器不延长被引用对象的生命周期。使用时须保证该对象仍存活；对象销毁或其值存储生命周期结束后不得继续访问。

## 调用示例

以下Host示例在被引用对象仍存活时检查结果。

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> value(7);
    int* selected = &*value;
    *selected = 9;
    return value.has_value() && *value == 9;
}
```

## 关联API

- [`asc::std::optional`](optional.md)
- [本头文件的接口列表](asc_std_optional.md)
