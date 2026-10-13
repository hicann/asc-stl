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

`asc::std::optional<T&>::optional` 按本页所列构造形态初始化 `optional<T&>` 对象。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

### 原型 1

```cpp
constexpr asc::std::optional<T&>::optional() noexcept;
```

### 原型 2

```cpp
constexpr asc::std::optional<T&>::optional(T& value) noexcept;
```

### 原型 3

```cpp
constexpr asc::std::optional<T&>::optional(asc::std::nullopt_t) noexcept;
```

### 原型 4

```cpp
constexpr asc::std::optional<T&>::optional(const asc::std::optional<T&>&) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 被绑定的对象；新 optional 保存指向它的引用，对象生命周期须覆盖 optional 使用期。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `asc` | 输入 | nullopt_t 空状态标记（nullopt 常量）；构造不含引用的空 optional。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `参数1` | 输入 | 复制来源 optional<T&>；新对象绑定到其引用的同一目标。 |

## 约束说明

- 引用特化仅允许安全的同类型左值绑定
- 采用借用指针语义，不提供容易产生悬空引用的转换

## 调用示例

以下 Host 片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/optional>

void example()
{
    asc::std::optional<int&> reference{};
    (void)reference.has_value();
}
```
