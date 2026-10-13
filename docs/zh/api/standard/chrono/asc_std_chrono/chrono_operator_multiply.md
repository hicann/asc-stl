# asc::std::chrono::`operator*`

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

头文件路径为：`<asc/std/chrono>`。

`asc::std::chrono::operator*`由`<asc/std/chrono>`提供，执行时长维度的时长乘以标量运算。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型1

```cpp
namespace asc::std::chrono {
template <class Rep2, enable_if_t<is_convertible_v<const Rep2&, common_type_t<Rep, Rep2>>, int> = 0> constexpr duration<common_type_t<Rep, Rep2>, Period> operator*(const duration& lhs, const Rep2& rhs);
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std::chrono {
template <class Rep2, enable_if_t<is_convertible_v<const Rep2&, common_type_t<Rep, Rep2>>, int> = 0> constexpr duration<common_type_t<Rep, Rep2>, Period> operator*(const Rep2& lhs, const duration& rhs);
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep2` | 另一时长或标量的计数类型；运算时与Rep形成公共类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |
| `rhs` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `duration<common_type_t<Rep, Rep2>, Period>` | 计数与标量相乘的新duration，period不变、计数采用公共类型。 |

## 约束说明

- 标量须可转换到公共计数类型，结果的周期保持不变。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::seconds left{2}, right{3};
    return (left * 3).count() == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
