# asc::std::optional

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

`asc::std::optional`选择性地保存一个值。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 声明

### 原型1

```cpp
namespace asc::std {
template<class T> class optional;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> class optional<T&>;
} // namespace asc::std
```

## 约束说明

- 对象类型 `T` 可复制构造时，`optional<T>` 可复制构造。复制赋值还要求 `T` 可复制赋值。若 `T` 的复制构造平凡，包装类型的复制构造也平凡。若复制赋值和析构也平凡，包装类型的复制赋值也平凡。复制 `optional<T&>` 会复制引用绑定。
- T必须是普通的非引用对象类型。
- Host遵循有效的C++17操作。
- Device侧构造、赋值、调用和交换所依赖的操作必须不抛出异常。
- 引用特化仅允许安全的同类型左值绑定。
- 采用借用指针语义，不提供容易产生悬空引用的转换。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> value;
    const bool initially_empty = !value.has_value();
    value.emplace(7);
    const bool stored = value.has_value() && *value == 7;
    value.reset();
    return initially_empty && stored && !value.has_value();
}
```

## 关联API

- [本头文件的接口列表](asc_std_optional.md)
