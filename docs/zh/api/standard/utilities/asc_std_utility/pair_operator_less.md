# `asc::std::operator<`（pair）

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

比较pair的两个成员。相等比较要求两个成员各自相等；小于比较先判断first，first等价时再判断second。

## 函数原型

以下为`asc::std`命名空间中的函数模板声明；执行空间宏已省略。

```cpp
template<class T1, class T2>
constexpr bool operator<(const pair<T1, T2>& left, const pair<T1, T2>& right)
    noexcept(noexcept(left.first < right.first && left.second < right.second));
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 比较的左操作数，比较不修改它。 |
| `right` | 输入 | 比较的右操作数，比较不修改它。 |

`T1`、`T2`是pair的第一、第二元素类型。

## 返回值说明

返回`bool`，比较关系成立时为`true`，否则为`false`。

## 约束说明

- 元素须支持相应比较。异常规格由声明中的表达式决定。
- 当前`asc::std`中pair的直接自由重载为`==`与`<`；不在此列入`rel_ops`中的通用关系辅助。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/utility>

bool example()
{
    asc::std::pair<int, int> left{1, 2};
    asc::std::pair<int, int> right{1, 3};
    return left < right;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
