# asc::std::optional::value_or

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

头文件路径为：`<asc/std/optional>`。

`asc::std::optional::value_or`在对象有值时返回该值，否则返回调用方提供的替代值。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

所属类型：[`asc::std::optional`](optional.md)。

### 原型1

```cpp
// asc::std::optional 类内的声明节选；模板形参和其他成员由所属类提供。
template<class U> constexpr T value_or(U&& default_value)&&;
```

### 原型2

```cpp
// asc::std::optional 类内的声明节选；模板形参和其他成员由所属类提供。
template<class U> constexpr T value_or(U&& default_value) const&;
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 替代值的类型；须能转换为T。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `default_value` | 输入/输出 | 替代值；本对象不含值时返回由它转换得到的T，含值时返回所含值（右值重载按移动返回）。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 替代值的类型；须能转换为T。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `default_value` | 输入/输出 | 替代值；本对象不含值时返回由它转换得到的T，含值时返回所含值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `T` | 返回该值，否则返回调用方提供的替代值。 |
| 原型2 | `T` | 返回该值，否则返回调用方提供的替代值。 |

## 约束说明

- T必须是普通的非引用对象类型。
- Host遵循有效的C++17操作。
- Device侧构造、赋值、调用和交换所依赖的操作必须不抛出异常。

## 调用示例

以下Host片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/optional>

decltype(auto) example()
{
    asc::std::optional<int> value(7);
    return static_cast<asc::std::optional<int>&&>(value).value_or(0);
}
```

## 关联API

- [`asc::std::optional`](optional.md)
- [本头文件的接口列表](asc_std_optional.md)
