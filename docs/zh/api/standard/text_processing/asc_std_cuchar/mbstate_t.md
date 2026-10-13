# asc::std::mbstate_t

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

头文件路径为：`<asc/std/cuchar>`、`<asc/std/cwchar>`。

`asc::std::mbstate_t` 标识当前 ABI 对应的时间、字符转换或宽字符类型。

该接口的可用位置为 Host（完整接口）、Device（C locale 相关接口）。

标准语义参考：[cppreference `cuchar`](https://en.cppreference.com/w/cpp/header/cuchar)。

## 声明

```cpp
using asc::std::mbstate_t = ::std::mbstate_t
```

此原型对应头文件：`<asc/std/cuchar>`、`<asc/std/cwchar>`。

## 约束说明

- Host委托系统<cuchar>完整合同
- Device交付size_t/mbstate_t，C++11起的mbrtoc16/c16rtomb/mbrtoc32/c32rtomb和C++20起的mbrtoc8/c8rtomb
- Device固定C locale的ASCII/NUL、count==0、空输入/输出、重置、显式或空state无状态路径与size_t(-1)/(-2)错误/未完成返回
- Host 提供完整接口，设备端仅提供 C 语言区域设置相关接口
- Host对本家族委托系统<cwchar>完整合同
- Device交付size_t/mbstate_t/wint_t/NULL/WCHAR_MIN/WCHAR_MAX/WEOF、wcscoll/wcsxfrm/wcstok与btowc/wctob/mbrlen/mbrtowc/mbsinit/mbsrtowcs/wcrtomb/wcsrtombs，语义固定为无状态单字节C locale

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cuchar>

void use_type(const asc::std::mbstate_t& value)
{
    (void)value;
}
```
