# asc::std::isupper

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

头文件路径为：`<asc/std/cctype>`。

`asc::std::isupper` 按当前支持的 C 区域设置规则分类输入字符。

标准语义参考：[cppreference `cctype`](https://en.cppreference.com/w/cpp/header/cctype)。

## 函数原型

```cpp
int asc::std::isupper(int value) noexcept;
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

- 14个标准函数isalnum/isalpha/isblank/iscntrl/isdigit/isgraph/islower/isprint/ispunct/isspace/isupper/isxdigit/tolower/toupper完整交付
- Host委托系统当前C locale
- Device执行环境固定C locale
- EOF与全部256个unsigned-char值的合法输入域
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cctype>

decltype(auto) example(int value)
{
    return asc::std::isupper(value);
}
```
