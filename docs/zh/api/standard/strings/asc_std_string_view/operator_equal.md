# `asc::std::operator==`（string_view）

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

头文件路径为：`<asc/std/string_view>`。

按照字符特性`T`比较字符序列内容和长度。顺序比较使用字典序。三个形式分别接受两个视图，以及单侧可隐式转换为视图的值；不比较指针地址。

## 函数原型

以下为`asc::std`命名空间中的函数模板声明；执行空间宏已省略。

```cpp
template<class C, class T>
constexpr bool operator==(basic_string_view<C, T> left, basic_string_view<C, T> right) noexcept;

template<class C, class T, int = 1>
constexpr bool operator==(basic_string_view<C, T> left, type_identity_t<basic_string_view<C, T>> right) noexcept;

template<class C, class T, unsigned int = 2>
constexpr bool operator==(type_identity_t<basic_string_view<C, T>> left, basic_string_view<C, T> right) noexcept;
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 比较的左操作数，比较不修改它。 |
| `right` | 输入 | 比较的右操作数，比较不修改它。 |

`C`是字符类型，`T`是字符特性类型。未命名整数模板参数仅用于区分重载，无需显式传入。

## 返回值说明

返回`bool`，比较关系成立时为`true`，否则为`false`。

## 约束说明

- 视图引用的字符区间在调用期间必须可读且存活；字符串字面量转换按其终止符确定长度。
- D-SIMD的普通字符指针适用于local或generic地址空间。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/string_view>

bool example()
{
    asc::std::string_view left("2");
    asc::std::string_view right("2");
    return (left == right) && (left == "2") && ("2" == right);
}
```

## 相关比较接口

原混合页面中的其他类型重载现分别收录于：[variant](../../utilities/asc_std_variant/operator_equal.md)、[array](../../containers/asc_std_array/operator_equal.md)、[optional](../../utilities/asc_std_optional/operator_equal.md)、[pair](../../utilities/asc_std_utility/pair_operator_equal.md)、[scoped_allocator](../../memory_management/asc_std_scoped_allocator/operator_equal.md)、[complex](../../numerics/asc_std_complex/operator_equal.md)、[philox_engine](../../numerics/asc_std_random/philox_engine_operator_equal.md)、[uniform_real_distribution](../../numerics/asc_std_random/uniform_real_distribution_operator_equal.md)、[uniform_real_distribution_param_type](../../numerics/asc_std_random/uniform_real_distribution_param_type_operator_equal.md)。
