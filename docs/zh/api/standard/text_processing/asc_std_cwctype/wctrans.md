# asc::std::wctrans

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

`asc::std::wctrans`按当前支持的C区域设置规则取得或应用宽字符分类与转换描述符。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cwctype`](https://en.cppreference.com/w/cpp/header/cwctype)。

## 函数原型

```cpp
namespace asc::std {
wctrans_t wctrans(const char* property) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `property` | 输入 | 以零字符终止的窄字符属性名称，例如tolower或toupper。返回的描述符用于对应宽字符分类或转换函数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `wctrans_t` | 名称受当前区域设置支持时返回对应描述符；未知名称返回0。 |

## 约束说明

- property须指向以零字符结尾的有效名称。Device中转换名称仅为tolower和toupper。

- Host行为由系统`<cwctype>`实现，受当前C语言区域设置影响。
- Device的宽字符分类及大小写转换固定使用C locale。
- Host提供完整接口，设备端仅提供C语言区域设置相关接口。

## 调用示例

以下Host示例使用具体输入，并检查结果。

```cpp
#include <asc/std/cwctype>

bool example()
{
    const auto descriptor = asc::std::wctrans("tolower");
    return descriptor != 0 && asc::std::towctrans(L'A', descriptor) == L'a';
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwctype.md)
