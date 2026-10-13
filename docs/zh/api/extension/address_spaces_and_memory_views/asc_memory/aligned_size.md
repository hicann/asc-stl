# asc::aligned_size

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

头文件路径为：`<asc/memory>`。

`asc::aligned_size`将`size`向上舍入到`alignment`的整数倍；`alignment == 0`时保持`size`不变。

## 函数原型

```cpp
namespace asc {
template<class Integer> constexpr Integer aligned_size(Integer size, Integer alignment) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Integer` | 大小和对齐倍数共用的整数类型；加法、除法及乘法的中间结果须可表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `size` | 输入 | 待向上取整的非负整数大小，与alignment使用相同单位。 |
| `alignment` | 输入 | 取整的非负整数倍数；0表示保持原始大小，正值不要求是2的幂。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `Integer` | `alignment == 0`时返回`size`；否则返回不小于`size`的最小alignment整数倍。 |

## 约束说明

- `size >= 0`、`alignment >= 0`；正alignment可以是7等非2的幂。
- `size + alignment - 1`及最终结果须可由`Integer`表示；接口不检测算术溢出。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/memory>

bool example()
{
    return asc::aligned_size(10, 7) == 14 && asc::aligned_size(10, 0) == 10;
}
```

## 关联API

- [本头文件的接口列表](asc_memory.md)
