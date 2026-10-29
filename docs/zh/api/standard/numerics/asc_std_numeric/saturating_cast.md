# asc::std::saturating_cast

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

`asc::std::saturating_cast`将整数转换为目标整数类型；超出目标类型表示范围时，返回对应的最小值或最大值。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

```cpp
namespace asc::std {
template<class U, class T> constexpr U saturating_cast(T value) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 转换的目标整数类型。 |
| `T` | 待转换值的源整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待转换的整数值；结果超出目标类型U表示范围时被钳位到U的边界。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `U` | 返回按目标类型边界钳位后的整数结果。 |

## 约束说明

- 标准整数类型可使用`signed char`、`unsigned char`、`short`、`unsigned short`、`int`、`unsigned int`、`long`、`unsigned long`、`long long`和`unsigned long long`；不接受`bool`、普通`char`、`wchar_t`、`char8_t`、`char16_t`、`char32_t`及浮点类型。
- 源类型和目标类型均须满足上述整数类型要求；转换在目标类型范围内保留原值。
- 可在Host、AI Core SIMD编程和AI Core SIMT编程中调用；接口为`constexpr`且不抛出异常。

## 调用示例

以下示例将300转换为`unsigned char`；当前目标的该类型最大值为255，结果饱和为255。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    return asc::std::saturating_cast<unsigned char>(300);
}

bool verify_example()
{
    return example() == 255;
}
```

## 关联API

- [本头文件的接口列表](asc_std_numeric.md)
