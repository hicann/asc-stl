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

`asc::std::midpoint` 在避免不必要溢出的前提下求中点。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型 1

```cpp
template<class Fp> [[nodiscard]] constexpr enable_if_t<is_floating_point_v<Fp>, Fp> asc::std::midpoint(Fp left, Fp right) noexcept;
```

### 原型 2

```cpp
template<class T, enable_if_t<is_object_v<T>&& !is_void_v<T>&& (sizeof(T) > 0), int>> [[nodiscard]] constexpr T* asc::std::midpoint(T* left, T* right) noexcept;
```

### 原型 3

```cpp
template<class T> [[nodiscard]] constexpr enable_if_t<is_integral_v<T>&& !is_same_v<bool, T>&& !is_null_pointer_v<T>, T> asc::std::midpoint(T left, T right) noexcept;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fp` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 输入范围元素或参与运算的值类型。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `未命名参数3` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 输入范围元素或参与运算的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `enable_if_t<is_floating_point_v<Fp>, Fp>` | 返回两个数值或指针端点之间的中点。 |
| 原型 2 | `> [[nodiscard]] constexpr T *` | 返回两个数值或指针端点之间的中点。 |
| 原型 3 | `enable_if_t<is_integral_v<T> && !is_same_v<bool, T> && !is_null_pointer_v<T>, T>` | 返回两个数值或指针端点之间的中点。 |

## 约束说明

- 提供顺序迭代器/值重载
- 本族中标准定义的执行策略重载采用顺序执行语义

## 调用示例

以下片段用具体整数范围展示数值调用；输出数组具有足够容量。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    return asc::std::midpoint(2, 8);
}
```
