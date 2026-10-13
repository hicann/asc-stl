# asc::std::errc

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

头文件路径为：`<asc/std/charconv>`、`<asc/std/system_error>`。

`asc::std::errc`列出本期整数转换及轻量错误接口支持的错误值。

标准语义参考：[cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv)。

## 声明

```cpp
namespace asc::std {
enum errc;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/charconv>`、`<asc/std/system_error>`。

## 约束说明

- 支持所有标准有符号/无符号整数类型以及2至36进制。
- AI Core SIMD编程 缓冲区必须是local或generic地址空间的普通char指针。
- 提供invalid_argument、result_out_of_range和value_too_large错误值、对应特征及枚举比较操作。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/charconv>

bool example()
{
    const char text[] = "x";
    int value = 7;
    auto result = asc::std::from_chars(text, text + 1, value);
    return result.ec == asc::std::errc::invalid_argument && value == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_charconv.md)
