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

`asc::std::extents::extents`按本页所列构造形态初始化`extents`对象。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

### 原型1

```cpp
constexpr extents();
```

### 原型2

```cpp
template<class ...OtherIndexTypes> constexpr extents(OtherIndexTypes... args);
```

### 原型3

```cpp
template<class OtherIndexType, size_t ...OtherStaticExtents> constexpr extents(const extents<OtherIndexType, OtherStaticExtents...>& other);
```

### 原型4

```cpp
template<class OtherIndexType, size_t Size> constexpr extents(const array<OtherIndexType, Size>& count);
```

### 原型5

```cpp
template<class OtherIndexType, size_t Size> constexpr extents(span<OtherIndexType, Size> count);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexTypes` | 用于初始化各动态维度的整数实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `args` | 输入 | 转发给对象构造或函数调用的实参列表。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源extents的索引整数类型；各维长度须能在目标类型中表示。 |
| `OtherStaticExtents` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源extents的索引整数类型；各维长度须能在目标类型中表示。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `count` | 输入 | 参与操作的元素数量。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源extents的索引整数类型；各维长度须能在目标类型中表示。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `count` | 输入 | 参与操作的元素数量。 |

## 返回值说明

无返回值。

## 约束说明

- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

bool example()
{
    asc::std::extents<int, 2, 3> shape;
    return shape.rank() == 2 && shape.rank_dynamic() == 0 && shape.extent(0) == 2 && shape.extent(1) == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
