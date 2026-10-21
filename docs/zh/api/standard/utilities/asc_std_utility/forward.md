# asc::std::forward

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

头文件路径为：`<asc/std/utility>`。

`asc::std::forward`按模板参数保留实参的值类别。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<typename T> [[nodiscard]] constexpr T&& forward(typename std::remove_reference<T>::type&& value) noexcept;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<typename T> [[nodiscard]] constexpr T&& forward(typename std::remove_reference<T>::type& value) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 调用方显式指定的目标类型；决定返回引用的值类别（非引用类型得到右值引用，左值引用类型折叠为左值引用）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待转发的右值；按显式模板参数T以T&& 原样转发，不产生复制或移动。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 调用方显式指定的目标类型；决定返回引用的值类别（非引用类型得到右值引用，左值引用类型折叠为左值引用）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待转发的左值；按显式模板参数T以T&& 转发（引用折叠后，T为左值引用时保持左值，否则可得到右值引用），不产生复制或移动。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型2 | `T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |

## 约束说明

- 遵循标准约束。
- forward_like保留const/volatile限定和值类别。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

bool example()
{
    int value = 3;
    auto&& reference = asc::std::forward<int&>(value);
    static_assert(asc::std::is_same_v<decltype(reference), int&>);
    // 在value仍存活时检查引用；函数只返回布尔值。
    return &reference == &value && reference == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
