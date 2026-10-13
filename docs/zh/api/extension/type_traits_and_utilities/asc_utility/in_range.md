# asc::in_range

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

头文件路径为：`<asc/utility>`。

`asc::in_range` 判断 `value` 是否位于包含两端点的闭区间 `[first, last]` 内。

## 函数原型

```cpp
template<class T> constexpr bool asc::in_range(T value, T first, T last) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 三个操作数共用的算术类型；value、first、last 须为同一类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待判断的值；位于闭区间 [first, last] 内（含两端）时返回 true。 |
| `first` | 输入 | 闭区间的下端点（含）；须满足 first <= last。 |
| `last` | 输入 | 闭区间的上端点（含）；须满足 first <= last。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- in_range 的操作数必须为同一算术类型且满足 first <= last
- static_for 对半开编译期区间内的每个索引恰好调用一次可调用对象

## 调用示例

以下片段给出具体模板实参和调用对象。

```cpp
#include <asc/utility>

decltype(auto) example()
{
    return asc::in_range(3, 0, 10);
}
```
