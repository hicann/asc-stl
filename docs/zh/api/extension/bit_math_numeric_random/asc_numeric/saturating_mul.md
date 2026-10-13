# asc::saturating_mul

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

`asc::saturating_mul`执行饱和乘法，越界时返回目标类型相应边界值。

## 函数原型

```cpp
namespace asc {
template<class T> constexpr T saturating_mul(T left, T right) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 参与饱和乘法的标准整数类型（非bool，不超过64位）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 饱和乘法的左整数操作数。 |
| `right` | 输入 | 饱和乘法的右整数操作数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回按目标类型边界钳位后的整数结果。 |

## 约束说明

- T、From和To必须是不超过64位的标准非bool整数类型。
- 所有溢出检查均不得触发有符号整数溢出的未定义行为。

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/numeric>

decltype(auto) example()
{
    return asc::saturating_mul(7, 2);
}
```

## 关联API

- [本头文件的接口列表](asc_numeric.md)
