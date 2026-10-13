# asc::integer_sqrt

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

头文件路径为：`<asc/cmath>`。

`asc::integer_sqrt`返回满足`r * r <= value`的最大整数`r`。

## 函数原型

```cpp
namespace asc {
template<class T> constexpr auto integer_sqrt(T value) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 输入与结果的整数或枚举类型（不含bool）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待求整数平方根的整数值；有符号类型时不得为负。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `auto` | 返回满足`r * r <= value`的最大整数`r`。 |

## 约束说明

- T必须为非bool的整数或枚举类型。
- 有符号类型的value不得为负数。

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/cmath>

decltype(auto) example()
{
    return asc::integer_sqrt(9u);
}
```

## 关联API

- [本头文件的接口列表](asc_cmath.md)
