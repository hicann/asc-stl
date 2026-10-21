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

`asc::std::wcscoll`在Host当前C语言区域设置下（Device固定C语言区域设置）比较两个宽字符串。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 函数原型

```cpp
namespace asc::std {
int wcscoll(const wchar_t* left, const wchar_t* right) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与比较的左侧宽字符串首地址，以空字符结尾；按当前区域设置的排序规则比较。 |
| `right` | 输入 | 参与比较的右侧宽字符串首地址，以空字符结尾；按当前区域设置的排序规则比较。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `int` | 返回小于零、等于零或大于零的比较结果，分别表示左侧序列小于、等于或大于右侧序列。 |

## 约束说明

- Host行为遵循系统`<cwchar>`提供的同名接口；字符转换和排序受当前C语言区域设置影响。
- Device固定使用C语言区域设置，按宽字符编码顺序处理，不支持区域设置相关排序规则。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>

decltype(auto) example(const wchar_t * left, const wchar_t * right)
{
    return asc::std::wcscoll(left, right);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwchar.md)
