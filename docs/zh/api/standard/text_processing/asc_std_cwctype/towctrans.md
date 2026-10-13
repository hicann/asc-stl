# asc::std::towctrans

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

头文件路径为：`<asc/std/cwctype>`。

`asc::std::towctrans`按当前支持的C区域设置规则取得或应用宽字符分类与转换描述符。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cwctype`](https://en.cppreference.com/w/cpp/header/cwctype)。

## 函数原型

```cpp
namespace asc::std {
wint_t towctrans(wint_t value, wctrans_t descriptor) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待转换的宽字符（wint_t）；取值须可表示为宽字符或等于WEOF，等于WEOF时原样返回。 |
| `descriptor` | 输入 | 字符转换描述符（wctrans_t），由wctrans取得；指定把宽字符映射为大写或小写所用的转换规则。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `wint_t` | 返回按指定字符转换规则得到的宽字符。 |

## 约束说明

- Host行为由系统`<cwctype>`实现，受当前C语言区域设置影响。
- Device的宽字符分类及大小写转换固定使用C locale。
- Host提供完整接口，设备端仅提供C语言区域设置相关接口。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwctype>

decltype(auto) example(asc::std::wint_t value, asc::std::wctrans_t descriptor)
{
    return asc::std::towctrans(value, descriptor);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwctype.md)
