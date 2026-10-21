# asc::saturating_div

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

头文件路径为：`<asc/numeric>`。

`asc::saturating_div`执行饱和除法，并处理不可表示的最小值除以负一情形。

## 函数原型

```cpp
namespace asc {
template <class T>
constexpr T saturating_div(T left, T right) noexcept;
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 参与饱和除法的标准整数类型（非bool，不超过64位）。 |

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

- 除数为0时返回`T`的最大值；有符号最小值除以`-1`同样钳位到最大值。这是该饱和接口的明确策略。

- 可在Host、AI Core SIMD和AI Core SIMT调用；结果按本页声明的整数类型返回。
- `T`须为不超过64位的标准非bool整数；算术按相应检查或饱和规则处理。

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/numeric>

decltype(auto) example()
{
    return asc::saturating_div(8, 2);
}
```

## 关联API

- [本头文件的接口列表](asc_numeric.md)
