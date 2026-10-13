# `asc::std::operator==`（optional）

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

比较可选值、普通值或空值标记。两个空值相等；空值小于任意含值对象。只有双方都含值时才比较所存储的值，普通值按含值一侧处理。

## 函数原型

以下为`asc::std`命名空间中的函数模板声明；执行空间宏已省略。

```cpp
template<class T, class U>
constexpr bool operator==(const optional<T>& left, const optional<U>& right);

template<class T, class U>
constexpr bool operator==(const optional<T>& left, const U& right);

template<class T, class U>
constexpr bool operator==(const T& left, const optional<U>& right);

template<class T>
constexpr bool operator==(const optional<T>& left, nullopt_t right) noexcept;

template<class T>
constexpr bool operator==(nullopt_t left, const optional<T>& right) noexcept;
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 比较的左操作数，比较不修改它。 |
| `right` | 输入 | 比较的右操作数，比较不修改它。 |

`T`、`U`是可选值的元素类型或另一侧普通值的类型；`nullopt_t`表示空状态。

## 返回值说明

返回`bool`，比较关系成立时为`true`，否则为`false`。

## 约束说明

- 所存储值的对应比较表达式须合法且结果可转换为`bool`。
- 本页重载属于optional；variant与string_view的重载分别见各自模块。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> left(2);
    asc::std::optional<int> right(2);
    return (left == right) && (left == 2) && (2 == right);
}
```

## 相关比较接口

原混合页面中的其他类型重载现分别收录于：[variant](../asc_std_variant/operator_equal.md)、[array](../../containers/asc_std_array/operator_equal.md)、[string_view](../../strings/asc_std_string_view/operator_equal.md)、[pair](../asc_std_utility/pair_operator_equal.md)、[scoped_allocator](../../memory_management/asc_std_scoped_allocator/operator_equal.md)、[complex](../../numerics/asc_std_complex/operator_equal.md)、[philox_engine](../../numerics/asc_std_random/philox_engine_operator_equal.md)、[uniform_real_distribution](../../numerics/asc_std_random/uniform_real_distribution_operator_equal.md)、[uniform_real_distribution_param_type](../../numerics/asc_std_random/uniform_real_distribution_param_type_operator_equal.md)。
