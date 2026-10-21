# asc::std::isgraph

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

`asc::std::isgraph`判断输入是否为除空格外的可打印字符；符合时返回非零，不符合时返回0。

标准语义参考：[cppreference `cctype`](https://en.cppreference.com/w/cpp/header/cctype)。

## 函数原型

```cpp
namespace asc::std {
int isgraph(int value) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待分类的字符值；须可表示为unsigned char或等于EOF，否则行为未定义。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `int` | 字符满足接口名称所指分类时返回非零值，否则返回零。 |

## 约束说明

- 输入必须为`EOF`或可由`unsigned char`表示的值；其他负值不满足先决条件。
- Host委托系统当前C locale。
- Device执行环境固定C locale。
- EOF与全部256个unsigned-char值的合法输入域。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例使用具体输入，并检查结果。

```cpp
#include <asc/std/cctype>

bool example()
{
    return asc::std::isgraph('A') != 0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cctype.md)
