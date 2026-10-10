# asc::std::wcscoll

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

`asc::std::wcscoll` 在固定 C locale 下比较两个宽字符串。

该接口的可用位置为 Host（完整接口）、Device（C locale 相关接口）。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 函数原型

```cpp
int asc::std::wcscoll(const wchar_t* left, const wchar_t* right) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `int` | 返回小于零、等于零或大于零的比较结果，分别表示左侧序列小于、等于或大于右侧序列。 |

## 约束说明

- Host对本家族委托系统<cwchar>完整合同
- Device交付size_t/mbstate_t/wint_t/NULL/WCHAR_MIN/WCHAR_MAX/WEOF、wcscoll/wcsxfrm/wcstok与btowc/wctob/mbrlen/mbrtowc/mbsinit/mbsrtowcs/wcrtomb/wcsrtombs，语义固定为无状态单字节C locale
- Host 提供完整接口，设备端仅提供 C 语言区域设置相关接口

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>

decltype(auto) example(const wchar_t * left, const wchar_t * right)
{
    return asc::std::wcscoll(left, right);
}
```
