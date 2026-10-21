# asc::bit_reverse

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

头文件路径为：`<asc/bit>`。

`asc::bit_reverse`反转32位或64位无符号整数的全部二进制位，使最低位与最高位、次低位与次高位依次交换。

## 函数原型

```cpp
namespace asc {
template <class T>
constexpr T bit_reverse(T value) noexcept;
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 无符号整数类型；须为uint32_t或uint64_t。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待反转全部二进制位的无符号整数值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回所有二进制位逆序排列后的整数。 |

## 约束说明

- T必须为uint32_t或uint64_t。
- 反转整个输入类型的位序；本函数没有start或width参数。

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/bit>

decltype(auto) example()
{
    return asc::bit_reverse(0x12u);
}
```

## 关联API

- [本头文件的接口列表](asc_bit.md)
