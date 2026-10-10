# asc::std::wcstok

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

头文件路径为：`<asc/std/cwchar>`。

`asc::std::wcstok` 按调用方提供的分隔集合切分宽字符串。

该接口的可用位置为 Host（完整接口）、Device（C locale 相关接口）。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 函数原型

```cpp
wchar_t* asc::std::wcstok(wchar_t* input, const wchar_t* delimiters, wchar_t** state) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `input` | 输入 | 提供“按调用方提供的分隔集合切分宽字符串”所需的数据地址；可访问范围和生命周期须满足约束。 |
| `delimiters` | 输入 | 提供“按调用方提供的分隔集合切分宽字符串”所需的数据地址；可访问范围和生命周期须满足约束。 |
| `state` | 输入 | 提供“按调用方提供的分隔集合切分宽字符串”所需的数据地址；可访问范围和生命周期须满足约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `wchar_t *` | 返回本次切分所得宽字符串的起始指针；没有更多片段时返回空指针。 |

## 约束说明

- Host对本家族委托系统<cwchar>完整合同
- Device交付size_t/mbstate_t/wint_t/NULL/WCHAR_MIN/WCHAR_MAX/WEOF、wcscoll/wcsxfrm/wcstok与btowc/wctob/mbrlen/mbrtowc/mbsinit/mbsrtowcs/wcrtomb/wcsrtombs，语义固定为无状态单字节C locale
- Host 提供完整接口，设备端仅提供 C 语言区域设置相关接口

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>

decltype(auto) example(wchar_t * input, const wchar_t * delimiters, wchar_t ** state)
{
    return asc::std::wcstok(input, delimiters, state);
}
```
