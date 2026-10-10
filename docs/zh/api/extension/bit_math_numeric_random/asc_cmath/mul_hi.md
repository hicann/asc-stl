# asc::mul_hi

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

`asc::mul_hi` 返回两个同类型无符号整数乘积的高半部分。

## 函数原型

```cpp
template<class T> constexpr T asc::mul_hi(T left, T right) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回两个同类型无符号整数乘积的高半部分。 |

## 约束说明

- T 必须为非 bool 的无符号整数类型，两个操作数类型必须相同

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/cmath>

decltype(auto) example()
{
    return asc::mul_hi(0x10000u, 0x10000u);
}
```
