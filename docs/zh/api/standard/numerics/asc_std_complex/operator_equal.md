# `asc::std::operator==`（complex）

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

头文件路径为：`<asc/std/complex>`。

相等比较实部和虚部；与标量比较时将标量视为虚部为零的复数。不等是相等的否定。

## 函数原型

以下声明适用于C++17和C++20：

```cpp
namespace asc::std {
template<class T>
constexpr bool operator==(const complex<T>& left, const complex<T>& right) noexcept;
}
```

```cpp
namespace asc::std {
template<class T>
constexpr bool operator==(const complex<T>& left, const T& right) noexcept;
}
```

以下额外声明仅在C++17中提供：

```cpp
namespace asc::std {
template<class T>
constexpr bool operator==(const T& left, const complex<T>& right) noexcept;
}
```

C++20的反向或不等比较表达式通过语言的重写候选规则获得；不要把表达式可用性等同于同名显式函数声明存在。

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 比较的左操作数，比较不修改它。 |
| `right` | 输入 | 比较的右操作数，比较不修改它。 |

`T`是本产品支持的复数元素类型。

## 返回值说明

返回`bool`，比较关系成立时为`true`，否则为`false`。

## 约束说明

- 当前复数计算支持`float`。
- 不进行动态分配；NaN分量遵循浮点比较规则。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/complex>

bool example()
{
    asc::std::complex<float> left(2.0f, 0.0f);
    asc::std::complex<float> right(2.0f, 0.0f);
    return (left == right) && (left == 2.0f) && (2.0f == right);
}
```

## 相关比较接口

原混合页面中的其他类型重载现分别收录于：[variant](../../utilities/asc_std_variant/operator_equal.md)、[array](../../containers/asc_std_array/operator_equal.md)、[string_view](../../strings/asc_std_string_view/operator_equal.md)、[optional](../../utilities/asc_std_optional/operator_equal.md)、[pair](../../utilities/asc_std_utility/pair_operator_equal.md)、[scoped_allocator](../../memory_management/asc_std_scoped_allocator/operator_equal.md)、[philox_engine](../asc_std_random/philox_engine_operator_equal.md)、[uniform_real_distribution](../asc_std_random/uniform_real_distribution_operator_equal.md)、[uniform_real_distribution_param_type](../asc_std_random/uniform_real_distribution_param_type_operator_equal.md)。
