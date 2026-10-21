# asc::std::countl_zero

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

头文件路径为：`<asc/std/bit>`。

`asc::std::countl_zero`统计从最高位起连续的零位数。

标准语义参考：[cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit)。

## 函数原型

以下为受无符号整数选择条件约束的模板声明；结果选择别名只控制合法类型的参与。

```cpp
namespace asc::std {
template<class T> constexpr __unsigned_integer_result_t<T, int> countl_zero(T value) noexcept;
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 支持的无cv无符号整数类型；不接受bool和普通字符编码类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被查询的无符号整数；为0时返回T的二进制位数。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `int` | 返回对应前导位、尾随位或全部置位位的数量。 |
| 原型2 | `int` | 返回对应前导位、尾随位或全部置位位的数量。 |

## 约束说明

- 遵循标准无符号整数类型约束。

## 调用示例

以下片段用具体数值展示本页调用。

```cpp
#include <asc/std/bit>

decltype(auto) example()
{
    return asc::std::countl_zero(3u);
}
```

## 关联API

- [本头文件的接口列表](asc_std_bit.md)
