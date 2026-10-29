# asc::std::saturating_div

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

`asc::std::saturating_div`计算两个同类型整数的商；有符号最小值除以`-1`时返回`T`的最大值。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

```cpp
namespace asc::std {
template<class T> constexpr T saturating_div(T left, T right) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 参与饱和除法的整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 饱和除法的左整数操作数。 |
| `right` | 输入 | 饱和除法的右整数操作数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回按目标类型边界钳位后的整数结果。 |

## 约束说明

- 标准整数类型可使用`signed char`、`unsigned char`、`short`、`unsigned short`、`int`、`unsigned int`、`long`、`unsigned long`、`long long`和`unsigned long long`；不接受`bool`、普通`char`、`wchar_t`、`char8_t`、`char16_t`、`char32_t`及浮点类型。
- 未显式指定模板实参时，两个输入必须推导出相同的`T`，不进行算术运算通常采用的整型提升。
- 可在Host、AI Core SIMD编程和AI Core SIMT编程中调用；接口为`constexpr`且不抛出异常。
- 除数`right`不得为0；饱和处理不为除零提供有效结果。

## 调用示例

以下示例计算8除以2，返回4。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    return asc::std::saturating_div(8, 2);
}

bool verify_example()
{
    return example() == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_numeric.md)
