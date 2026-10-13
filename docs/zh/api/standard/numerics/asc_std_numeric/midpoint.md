# asc::std::midpoint

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

头文件路径为：`<asc/std/numeric>`。

`asc::std::midpoint`在避免不必要溢出的前提下求中点。整数重载的舍入朝向第一参数。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class Fp> [[nodiscard]] constexpr enable_if_t<is_floating_point_v<Fp>, Fp> midpoint(Fp left, Fp right) noexcept;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T, enable_if_t<is_object_v<T>&& !is_void_v<T>&& (sizeof(T) > 0), int>> [[nodiscard]] constexpr T* midpoint(T* left, T* right) noexcept;
} // namespace asc::std
```

### 原型3

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr enable_if_t<is_integral_v<T>&& !is_same_v<bool, T>&& !is_null_pointer_v<T>, T> midpoint(T left, T right) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fp` | 端点与中点结果的浮点类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 求中点的左端浮点值。 |
| `right` | 输入 | 求中点的右端浮点值。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | `left`与`right`所指对象的类型；须为非void的对象类型。 |
| `未命名参数3` | 匿名非类型模板参数，类型为int，仅用于承载上一个参数的约束类型；调用方无需显式指定。 |
**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 求中点的左端对象指针；应与`right`指向同一数组或其尾后位置。 |
| `right` | 输入 | 求中点的右端对象指针；应与`left`指向同一数组或其尾后位置。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 端点与中点结果的整数类型；不含bool。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 求中点的左端整数值。 |
| `right` | 输入 | 求中点的右端整数值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `Fp` | 返回两个浮点数的中点。 |
| 原型2 | `T *` | 返回指向两指针之间中点元素的指针。 |
| 原型3 | `T` | 返回两个整数的中点。 |

## 约束说明

- 提供顺序迭代器/值重载。
- 本族中标准定义的执行策略重载采用顺序执行语义。
- 整数重载的两实参可同号或异号。
- 整数重载经无符号差值计算中点，结果不因`left + right`中间量溢出而失真。
- 指针重载的两实参须指向同一数组对象内的元素或其尾后位置，否则行为无定义。

## 调用示例

以下片段用具体整数范围展示数值调用；输出数组具有足够容量。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    return asc::std::midpoint(2, 8);
}
```

## 关联API

- [本头文件的接口列表](asc_std_numeric.md)
