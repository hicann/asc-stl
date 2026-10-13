# asc::static_for

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

头文件路径为：`<asc/utility>`。

`asc::static_for`在编译期展开零基计数区间或带步长半开区间，并为每个索引调用一次可调用对象，不产生Runtime循环调度。

## 函数原型

### 原型1

```cpp
namespace asc {
template<auto Size, class Operator, class... Args> constexpr void static_for(Operator operation, Args&&... args) noexcept(noexcept(static_for<decltype(Size), Size>(operation, static_cast<Args&&>(args)...)));
} // namespace asc
```

### 原型2

```cpp
namespace asc {
template<auto Start, decltype(Start) End, decltype(Start) Step = decltype(Start){1}, class Operator, class... Args> constexpr void static_for(Operator operation, Args&&... args) noexcept(noexcept(static_for<decltype(Start), Start, End, Step>(operation, static_cast<Args&&>(args)...)));
} // namespace asc
```

### 原型3

```cpp
namespace asc {
template<class IndexType, IndexType Start, IndexType End, IndexType Step = IndexType{1}, class Operator, class... Args> constexpr void static_for(Operator operation, Args&&... args) noexcept(noexcept(detail::static_for_invoke<IndexType, Start, Step>(operation, static_cast<Args&&>(args)...)));
} // namespace asc
```

### 原型4

```cpp
namespace asc {
template<class SizeType, SizeType Size, class Operator, class... Args> constexpr void static_for(Operator operation, Args&&... args) noexcept(noexcept(detail::static_for_invoke<SizeType, SizeType{0}, SizeType{1}>(operation, static_cast<Args&&>(args)...)));
} // namespace asc
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Size` | 零基展开的迭代次数（编译期值）；按索引0至Size-1依次各调用一次operation，非正数时不调用。 |
| `Operator` | 可调用对象operation的类型；须能以编译期索引常量为首实参、后随转发的args被调用。 |
| `Args` | 每次索引调用时转发给operation的实参类型包（对应函数形参Args&&...）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operation` | 输入 | 每个编译期索引处被调用一次的可调用对象；以索引常量（integral_constant形式，可隐式转换为索引类型）为首实参，随后接收转发的args。设备侧使用时其执行空间属性须与调用方一致。 |
| `args` | 输入/输出 | 以转发引用接收、在每次索引调用时原样转发给operation的实参包；右值实参保持可被移动，若被移动则移动后处于有效但未指定状态。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Start` | 半开迭代区间的起始索引（编译期值，含端点）。 |
| `End` | 半开迭代区间的结束索引（编译期值，不含端点）。 |
| `Step` | 索引步长（编译期值，默认1），须非零；取负值时按倒序展开。 |
| `Operator` | 可调用对象operation的类型；须能以编译期索引常量为首实参、后随转发的args被调用。 |
| `Args` | 每次索引调用时转发给operation的实参类型包（对应函数形参Args&&...）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operation` | 输入 | 每个编译期索引处被调用一次的可调用对象；以索引常量（integral_constant形式，可隐式转换为索引类型）为首实参，随后接收转发的args。设备侧使用时其执行空间属性须与调用方一致。 |
| `args` | 输入/输出 | 以转发引用接收、在每次索引调用时原样转发给operation的实参包；右值实参保持可被移动，若被移动则移动后处于有效但未指定状态。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `IndexType` | 迭代索引的整数类型；Start、End、Step均为该类型的编译期值。 |
| `Start` | 半开迭代区间的起始索引（编译期值，含端点）。 |
| `End` | 半开迭代区间的结束索引（编译期值，不含端点）。 |
| `Step` | 索引步长（编译期值，默认1），须非零；取负值时按倒序展开。 |
| `Operator` | 可调用对象operation的类型；须能以编译期索引常量为首实参、后随转发的args被调用。 |
| `Args` | 每次索引调用时转发给operation的实参类型包（对应函数形参Args&&...）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operation` | 输入 | 每个编译期索引处被调用一次的可调用对象；以索引常量（integral_constant形式，可隐式转换为索引类型）为首实参，随后接收转发的args。设备侧使用时其执行空间属性须与调用方一致。 |
| `args` | 输入/输出 | 以转发引用接收、在每次索引调用时原样转发给operation的实参包；右值实参保持可被移动，若被移动则移动后处于有效但未指定状态。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `SizeType` | 迭代索引的整数类型；Size为该类型的编译期值。 |
| `Size` | 零基展开的迭代次数（编译期值）；按索引0至Size-1依次各调用一次operation，非正数时不调用。 |
| `Operator` | 可调用对象operation的类型；须能以编译期索引常量为首实参、后随转发的args被调用。 |
| `Args` | 每次索引调用时转发给operation的实参类型包（对应函数形参Args&&...）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operation` | 输入 | 每个编译期索引处被调用一次的可调用对象；以索引常量（integral_constant形式，可隐式转换为索引类型）为首实参，随后接收转发的args。设备侧使用时其执行空间属性须与调用方一致。 |
| `args` | 输入/输出 | 以转发引用接收、在每次索引调用时原样转发给operation的实参包；右值实参保持可被移动，若被移动则移动后处于有效但未指定状态。 |

## 返回值说明

无返回值。

## 约束说明

- in_range的操作数必须为同一算术类型且满足first <= last。
- static_for对半开编译期区间内的每个索引恰好调用一次可调用对象。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/utility>

bool example()
{
    int sum = 0;
    asc::static_for<4>([&](auto index) { sum += index; });
    return sum == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_utility.md)
