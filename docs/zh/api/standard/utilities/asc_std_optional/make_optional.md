# asc::std::make_optional

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

`asc::std::make_optional`从给定参数推导类型并构造有值optional。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T, class... Args> constexpr asc::std::optional<T> make_optional(Args&&... args);
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> constexpr asc::std::optional<decay_t<T>> make_optional(T&& value);
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 待构造的值类型；由调用方显式指定。 |
| `Args` | 原位构造T的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `args` | 输入/输出 | 原位构造T的实参；按序转发，右值被移动后处于有效但未指定状态。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 值实参的类型；经decay后作为结果optional的元素类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 构造结果所含值的来源；左值被复制、右值被移动，右值移动后处于有效但未指定状态。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::std::optional<T>` | 返回按当前值或错误状态变换后形成的新状态对象。 |
| 原型2 | `asc::std::optional<decay_t<T>>` | 返回按当前值或错误状态变换后形成的新状态对象。 |

## 约束说明

- T必须是普通的非引用对象类型。
- Host遵循有效的C++17操作。
- Device侧构造、赋值、调用和交换所依赖的操作必须不抛出异常。

## 调用示例

以下片段用具体类型展示调用；declval仅用于不求值的类型表达式。

```cpp
#include <asc/std/optional>

decltype(auto) example()
{
    return asc::std::make_optional(7);
}

bool verify_example()
{
    const auto result = example();
    return result.has_value() && *result == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_optional.md)
