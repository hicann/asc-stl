# asc::std::ranges::enable_borrowed_range

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

头文件路径为：`<asc/std/span>`。

`asc::std::ranges::enable_borrowed_range<span<T,Extent>>` 由 `<asc/std/span>` 提供，标准 C++20：span 为借用范围（ranges 悬垂语义）

标准语义参考：[cppreference `span`](https://en.cppreference.com/w/cpp/header/span)。

## 函数原型

```cpp
template<class T, size_t Extent> constexpr bool enable_borrowed_range<span<T,Extent>> = true;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |
| `Extent` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `按声明确定` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 标准 C++20：span 为借用范围（ranges 悬垂语义）

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/span>

static_assert(asc::std::ranges::enable_borrowed_range<asc::std::span<int>>);
```
