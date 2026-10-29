# asc::mul_overflow

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

头文件路径为：`<asc/numeric>`。

`asc::mul_overflow`计算整数乘法并报告结果是否超出目标类型范围。

## 函数原型

### 原型1

```cpp
namespace asc {
template <class T>
constexpr asc::overflow_result<T> mul_overflow(T left, T right) noexcept;
}  // namespace asc
```

### 原型2

```cpp
namespace asc {
template <class T>
constexpr bool mul_overflow(T left, T right, T& result) noexcept;
}  // namespace asc
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 参与检查式乘法的标准整数类型（非bool，不超过64位）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 检查溢出的整数乘法左操作数。
| `right` | 输入 | 检查溢出的整数乘法右操作数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 参与检查式乘法的标准整数类型（非bool，不超过64位）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 检查溢出的整数乘法左操作数。
| `right` | 输入 | 检查溢出的整数乘法右操作数。
| `result` | 输出 | 写出运算结果的引用；返回true表示发生溢出。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::overflow_result<T>` | 返回整数乘法并报告结果是否超出目标类型范围的计算结果。 |
| 原型2 | `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- `overflow == true`时，整数加减乘的value保存转换到目标位宽的结果；除零保存0，有符号最小值除以-1保存该最小值。`overflow_cast`保存转换后的值；不能在忽略标志的情况下把它当作精确数学结果。

- 可在Host、AI Core SIMD和AI Core SIMT调用；结果按本页声明的整数类型返回。
- `T`须为不超过64位的标准非bool整数；算术按相应检查或饱和规则处理。

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/numeric>

decltype(auto) example()
{
    return asc::mul_overflow(7, 2);
}

bool verify_example()
{
    const auto actual = example();
    return actual.value == 14 && actual.overflow == false;
}
```

## 关联API

- [本头文件的接口列表](asc_numeric.md)
