# asc::std::wctob

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

`asc::std::wctob`在单字节字符与宽字符表示之间转换。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 函数原型

```cpp
namespace asc::std {
int wctob(wint_t value) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待检查的宽字符（wint_t）；取值须可表示为宽字符或等于WEOF，是否对应单字节字符由返回值指示。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `int` | 可表示为单字节字符时返回对应unsigned char提升为int的值，否则返回EOF。 |

## 约束说明

- Host行为遵循系统`<cwchar>`提供的同名接口；字符转换和排序受当前C语言区域设置影响。
- Device固定为无状态单字节转换，仅支持ASCII及空字符；超出范围时按本接口返回值说明报告失败。
- 不同字符序列使用独立状态对象；字符串输出缓冲区须具有足够容量。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>

decltype(auto) example(asc::std::wint_t value)
{
    return asc::std::wctob(value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwchar.md)
