# asc::bitfield_extract

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

`asc::bitfield_extract`从无符号整数的`start`位开始提取连续`width`位，并将结果右对齐返回。

## 函数原型

```cpp
namespace asc {
template<class T> constexpr T bitfield_extract(T value, int start, int width) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 无符号整数类型；须为uint32_t或uint64_t。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待提取位域的无符号整数值。 |
| `start` | 输入 | 位域在`value`中的起始位编号（最低位为第0位）；不得为负。 |
| `width` | 输入 | 待提取的连续位数；不得为负。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回从指定起始位提取并右对齐的位域值。 |

## 约束说明

- T必须为uint32_t或uint64_t。
- start和width不得为负且不得超出类型位宽，零位宽和全位宽操作不得产生未定义移位。

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/bit>

decltype(auto) example()
{
    return asc::bitfield_extract(0x3fu, 1, 3);
}
```

## 关联API

- [本头文件的接口列表](asc_bit.md)
