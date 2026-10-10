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

`asc::static_for` 在编译期展开零基计数区间或带步长半开区间，并为每个索引调用一次可调用对象，不产生 Runtime 循环调度。

## 函数原型

### 原型 1

```cpp
template<auto Size, class Operator, class... Args> constexpr void asc::static_for(Operator operation, Args&&... args) noexcept(noexcept(asc::static_for<decltype(Size), Size>(operation, static_cast<Args&&>(args)...)));
```

### 原型 2

```cpp
template<auto Start, decltype(Start) End, decltype(Start) Step = decltype(Start){1}, class Operator, class... Args> constexpr void asc::static_for(Operator operation, Args&&... args) noexcept(noexcept(asc::static_for<decltype(Start), Start, End, Step>(operation, static_cast<Args&&>(args)...)));
```

### 原型 3

```cpp
template<class IndexType, IndexType Start, IndexType End, IndexType Step = IndexType{1}, class Operator, class... Args> constexpr void asc::static_for(Operator operation, Args&&... args) noexcept(noexcept(detail::static_for_invoke<IndexType, Start, Step>(operation, static_cast<Args&&>(args)...)));
```

### 原型 4

```cpp
template<class SizeType, SizeType Size, class Operator, class... Args> constexpr void asc::static_for(Operator operation, Args&&... args) noexcept(noexcept(detail::static_for_invoke<SizeType, SizeType{0}, SizeType{1}>(operation, static_cast<Args&&>(args)...)));
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |
| `Operator` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operation` | 输入 | 提供“在编译期展开零基计数区间或带步长半开区间，并为每个索引调用一次可调用对象，不产生 Runtime 循环调度”所需的输入对象；类型须满足所选原型约束。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Start` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `End` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `Step` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `Operator` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operation` | 输入 | 提供“在编译期展开零基计数区间或带步长半开区间，并为每个索引调用一次可调用对象，不产生 Runtime 循环调度”所需的输入对象；类型须满足所选原型约束。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `IndexType` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Start` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `End` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `Step` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `Operator` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operation` | 输入 | 提供“在编译期展开零基计数区间或带步长半开区间，并为每个索引调用一次可调用对象，不产生 Runtime 循环调度”所需的输入对象；类型须满足所选原型约束。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `SizeType` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |
| `Operator` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operation` | 输入 | 提供“在编译期展开零基计数区间或带步长半开区间，并为每个索引调用一次可调用对象，不产生 Runtime 循环调度”所需的输入对象；类型须满足所选原型约束。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

无返回值。

## 约束说明

- in_range 的操作数必须为同一算术类型且满足 first <= last
- static_for 对半开编译期区间内的每个索引恰好调用一次可调用对象

## 调用示例

以下片段给出具体模板实参和调用对象。

```cpp
#include <asc/utility>

void example()
{
    asc::static_for<4>([](auto index) { (void)index; });
}
```
