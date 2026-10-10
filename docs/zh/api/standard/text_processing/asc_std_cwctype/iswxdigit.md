# asc::std::iswxdigit

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

`asc::std::iswxdigit` 按当前支持的 C 区域设置规则分类输入字符。

该接口的可用位置为 Host（完整接口）、Device（C locale 相关接口）。

标准语义参考：[cppreference `cwctype`](https://en.cppreference.com/w/cpp/header/cwctype)。

## 函数原型

```cpp
int asc::std::iswxdigit(wint_t value) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `int` | 字符满足接口名称所指分类时返回非零值，否则返回零。 |

## 约束说明

- Host对22个词元委托系统<cwctype>完整合同
- Device交付wint_t/wctype_t/wctrans_t/WEOF、14个直接分类/转换函数与wctype/iswctype/wctrans/towctrans完整描述符家族，语义固定为C locale
- Host 提供完整接口，设备端仅提供 C 语言区域设置相关接口

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwctype>

decltype(auto) example(asc::std::wint_t value)
{
    return asc::std::iswxdigit(value);
}
```
