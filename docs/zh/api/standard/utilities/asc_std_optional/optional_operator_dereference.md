# asc::std::optional::operator*

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

`asc::std::optional::operator*` 解引用当前迭代器或有值对象。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

### 原型 1

```cpp
constexpr T& asc::std::optional::operator*()& noexcept;
```

### 原型 2

```cpp
constexpr T&& asc::std::optional::operator*()&& noexcept;
```

### 原型 3

```cpp
constexpr const T& asc::std::optional::operator*() const& noexcept;
```

### 原型 4

```cpp
constexpr const T&& asc::std::optional::operator*() const&& noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

无参数。

### 原型 3 的参数

无参数。

### 原型 4 的参数

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `T&` | 返回当前迭代器或包装器所引用的对象。 |
| 原型 2 | `T&&` | 返回当前迭代器或包装器所引用的对象。 |
| 原型 3 | `const T&` | 返回当前迭代器或包装器所引用的对象。 |
| 原型 4 | `const T&&` | 返回当前迭代器或包装器所引用的对象。 |

## 约束说明

- T 必须是普通的非引用对象类型
- Host 遵循有效的 C++17 操作
- Device 侧构造、赋值、调用和交换所依赖的操作必须不抛出异常

## 调用示例

以下 Host 片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/optional>

decltype(auto) example()
{
    asc::std::optional<int> value(7);
    return *value;
}
```
