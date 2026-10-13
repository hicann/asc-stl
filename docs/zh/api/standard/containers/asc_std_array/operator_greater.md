# `asc::std::operator>`（array）

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

头文件路径为：`<asc/std/array>`。

按元素比较数组。相等要求所有对应元素相等；顺序按首个不等元素确定，全部元素相等时数组等价。

## 函数原型

以下为`asc::std`命名空间中的函数模板声明；执行空间宏已省略。

```cpp
template<class T, size_t Size>
constexpr bool operator>(const array<T, Size>& left, const array<T, Size>& right);
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 比较的左操作数，比较不修改它。 |
| `right` | 输入 | 比较的右操作数，比较不修改它。 |

`T`是元素类型，`Size`是双方相同的元素数量。

## 返回值说明

返回`bool`，比较关系成立时为`true`，否则为`false`。

## 约束说明

- 元素必须支持所选相等或顺序比较；零长度数组无需访问元素。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/array>

bool example()
{
    asc::std::array<int, 2> left{1, 3};
    asc::std::array<int, 2> right{1, 2};
    return left > right;
}
```

## 相关比较接口

原混合页面中的其他类型重载现分别收录于：[variant](../../utilities/asc_std_variant/operator_greater.md)、[string_view](../../strings/asc_std_string_view/operator_greater.md)、[optional](../../utilities/asc_std_optional/operator_greater.md)。
