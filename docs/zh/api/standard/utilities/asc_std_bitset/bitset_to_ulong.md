# asc::std::bitset::to_ulong

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

头文件路径为：`<asc/std/bitset>`。

`asc::std::bitset::to_ulong`把位集合转换为unsigned long，超出可表示范围时失败。

标准语义参考：[cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset)。

## 函数原型

以下为`bitset<Size>`类内声明。

```cpp
template<size_t Width = Size, enable_if_t<(Width <= sizeof(unsigned long) * CHAR_BIT), int> = 0>
constexpr unsigned long to_ulong() const noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 默认值为所属bitset的Size，用于编译期检查目标整数位宽；正常调用无需显式指定。 |

无函数参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned long` | 返回由当前位集合转换得到的无符号整数；超出目标类型范围时按约束处理。 |

## 约束说明

- 默认Width等于Size，Size须不超过目标无符号整数类型的二进制位数；范围按位数限定，不是只看当前置位值。该子集不提供运行期overflow_error转换。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/bitset>

bool example()
{
    asc::std::bitset<8> bits(5);
    return bits.to_ulong() == 5;
}
```

## 关联API

- [`asc::std::bitset`](bitset.md)
- [本头文件的接口列表](asc_std_bitset.md)
