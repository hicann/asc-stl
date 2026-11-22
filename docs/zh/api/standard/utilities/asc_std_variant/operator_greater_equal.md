# `asc::std::operator>=`（variant）

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

头文件路径为：`<asc/std/variant>`。

右侧无值时返回 `true`，包括两侧都无值的情况。仅左侧无值时返回 `false`。两者都含值时，先比较活动索引，索引相同时比较所含值。

## 函数原型

以下为`asc::std`命名空间中的函数模板声明；执行空间宏已省略。

```cpp
template<class... Types>
constexpr bool operator>=(const variant<Types...>& left, const variant<Types...>& right);
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 比较的左操作数，比较不修改它。 |
| `right` | 输入 | 比较的右操作数，比较不修改它。 |

`Types...`是双方相同的备选项类型列表。

## 返回值说明

返回`bool`，比较关系成立时为`true`，否则为`false`。

## 约束说明

- 每个备选项须支持对应的比较表达式，结果可转换为`bool`。
- 比较不会切换活跃备选项，也不分配内存。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> left(2);
    asc::std::variant<int, float> right(2);
    return left >= right;
}
```

## 关联API

- [本头文件的接口列表](asc_std_variant.md)
