# asc::overflow_cast

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

`asc::overflow_cast`转换整数类型并同时返回结果和越界标志。

## 函数原型

```cpp
namespace asc {
template <class To, class From>
constexpr asc::overflow_result<To> overflow_cast(From value) noexcept;
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `To` | 转换的目标整数类型。 |
| `From` | 转换的源整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待转换的整数值；结果连同是否越界（含符号改变或往返不一致）一并返回。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::overflow_result<To>` | 返回结果和越界标志。 |

## 约束说明

- `overflow == true`时，整数加减乘的value保存转换到目标位宽的结果；除零保存0，有符号最小值除以-1保存该最小值。`overflow_cast`保存转换后的值；不能在忽略标志的情况下把它当作精确数学结果。

- 可在Host、AI Core SIMD和AI Core SIMT调用；结果按本页声明的整数类型返回。
- `To`和`From`须为不超过64位的标准非bool整数；检查或饱和语义见本页返回值。

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/numeric>

decltype(auto) example()
{
    return asc::overflow_cast<unsigned char>(300);
}

bool verify_example()
{
    const auto actual = example();
    return actual.value == 44 && actual.overflow == true;
}
```

## 关联API

- [本头文件的接口列表](asc_numeric.md)
