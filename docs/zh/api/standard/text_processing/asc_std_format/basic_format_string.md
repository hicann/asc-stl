# asc::std::basic_format_string

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

头文件路径为：`<asc/std/format>`。

`asc::std::basic_format_string`保存可在编译期检查语法的格式串。

该接口自C++20+ 模式起提供。

标准语义参考：[cppreference `format`](https://en.cppreference.com/w/cpp/header/format)。

## 声明

```cpp
namespace asc::std {
template<class CharT, class ...Args> class basic_format_string;
} // namespace asc::std
```

## 约束说明

- basic_format_string<char,Args...>的编译期char数组构造与format_string别名。
- format_to_n_result<char*>及其out/size成员。
- 格式串内部仅接受已验证的{}、转义花括号和非bool/char标准整数d/x/X/o/b语法。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/format>

bool example()
{
    asc::std::basic_format_string<char, int> format("value={}");
    return format.size() == 8;
}
```

## 关联API

- [本头文件的接口列表](asc_std_format.md)
