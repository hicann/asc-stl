# asc::std::c8rtomb

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

头文件路径为：`<asc/std/cuchar>`。

`asc::std::c8rtomb` 在多字节序列与指定 UTF 字符编码单元之间转换，并更新调用方提供的状态。

该接口的可用位置为 Host（完整接口）、Device（C locale 相关接口）。

标准语义参考：[cppreference `cuchar`](https://en.cppreference.com/w/cpp/header/cuchar)。

## 函数原型

```cpp
size_t asc::std::c8rtomb(char* destination, char8_t value, mbstate_t* state) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `destination` | 输出 | 用于接收结果的目标存储。本调用为同步的编码转换，返回时结果已写入。 |
| `value` | 输入 | 待转换的单个 UTF-8 编码单元。 || `state` | 输入 | 提供“在多字节序列与指定 UTF 字符编码单元之间转换，并更新调用方提供的状态”所需的数据地址；可访问范围和生命周期须满足约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `size_t` | 返回转换处理的字符或字节数量，或标准规定的错误、未完成状态编码。 |

## 约束说明

- Host委托系统<cuchar>完整合同
- Device交付size_t/mbstate_t，C++11起的mbrtoc16/c16rtomb/mbrtoc32/c32rtomb和C++20起的mbrtoc8/c8rtomb
- Device固定C locale的ASCII/NUL、count==0、空输入/输出、重置、显式或空state无状态路径与size_t(-1)/(-2)错误/未完成返回
- Host 提供完整接口，设备端仅提供 C 语言区域设置相关接口

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cuchar>

decltype(auto) example(char * destination, char8_t value, asc::std::mbstate_t * state)
{
    return asc::std::c8rtomb(destination, value, state);
}
```
