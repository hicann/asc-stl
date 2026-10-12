# asc::std::chrono::operator%

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

`asc::std::chrono::operator%` 由 `<asc/std/chrono>` 提供，执行时长维度的时长对标量取模运算。接口遵循对应 C++ 标准设施的语义；ASC-STL 的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型 1

```cpp
template <class Rep2, enable_if_t<!__is_asc_std_duration_v<Rep2> && is_convertible_v<const Rep2&, common_type_t<Rep, Rep2>>, int> = 0> constexpr duration<common_type_t<Rep, Rep2>, Period> asc::std::chrono::operator%(const duration& lhs, const Rep2& rhs)
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 2

```cpp
template <class Rep2, class Period2> constexpr common_type_t<duration, duration<Rep2, Period2>> asc::std::chrono::operator%(const duration& lhs, const duration<Rep2, Period2>& rhs)
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep2` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |
| `Period2` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |
| `rhs` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `&& is_convertible_v<const Rep2&, common_type_t<Rep, Rep2>>, int> = 0> constexpr duration<common_type_t<Rep, Rep2>, Period>` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `common_type_t<duration, duration<Rep2, Period2>>` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 右操作数须为可转换到公共计数类型的标量且不得为时长类型
- 两个时长先转换为公共时长类型后取模

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/chrono>

void example()
{
    (void)(asc::std::chrono::seconds{90} % 30);
}
```
