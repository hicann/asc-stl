# asc::std::extents::extents

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

头文件路径为：`<asc/std/mdspan>`。

`asc::std::extents::extents` 按本页所列构造形态初始化 `extents` 对象。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

### 原型 1

```cpp
constexpr extents();
```

### 原型 2

```cpp
template<class ...OtherIndexTypes> constexpr extents(OtherIndexTypes... args);
```

### 原型 3

```cpp
template<class OtherIndexType, size_t ...OtherStaticExtents> constexpr extents(const extents<OtherIndexType, OtherStaticExtents...>& other);
```

### 原型 4

```cpp
template<class OtherIndexType, size_t Size> constexpr extents(const array<OtherIndexType, Size>& count);
```

### 原型 5

```cpp
template<class OtherIndexType, size_t Size> constexpr extents(span<OtherIndexType, Size> count);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexTypes` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `args` | 输入 | 转发给对象构造或函数调用的实参列表。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `OtherStaticExtents` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `count` | 输入 | 参与操作的元素数量。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `count` | 输入 | 参与操作的元素数量。 |

## 约束说明

- 固定当前版本的 C++ 标准库的完整dynamic_extent/extents/dextents/dims家族：零rank与正rank、默认/按rank或rank_dynamic传值/array/span/跨extents构造、标准显式性与约束、deduction guide、相等比较及rank/rank_dynamic/static_extent/extent观察
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/mdspan>

void example()
{
    asc::std::extents<int, 2, 3> value{};
    (void)value;
}
```
