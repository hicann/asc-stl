# asc::std::from_chars_result

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

头文件路径为：`<asc/std/charconv>`。

`asc::std::from_chars_result`保存字符解析停止位置和错误状态。

标准语义参考：[cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv)。

## 声明

```cpp
namespace asc::std {
struct from_chars_result;
} // namespace asc::std
```

## 约束说明

- 支持所有标准有符号/无符号整数类型以及2至36进制。
- AI Core SIMD编程 缓冲区必须是local或generic地址空间的普通char指针。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/charconv>

bool example()
{
    const char text[] = "42";
    int value = 0;
    asc::std::from_chars_result result = asc::std::from_chars(text, text + 2, value);
    return result.ec == asc::std::errc{} && result.ptr == text + 2 && value == 42;
}
```

## 关联API

- [本头文件的接口列表](asc_std_charconv.md)
