# asc::std::format_to_n_result

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

`asc::std::format_to_n_result`保存有界格式化的输出位置和完整结果大小。

该结果类型从C++17起提供；创建结果对象不执行格式化或格式串校验。

标准语义参考：[cppreference `format`](https://en.cppreference.com/w/cpp/header/format)。

## 声明

```cpp
namespace asc::std {
template<class Out>
struct format_to_n_result {
    Out out;
    ptrdiff_t size;
};
} // namespace asc::std
```

## 约束说明

- `Out`表示输出位置类型；`out`记录写入结束位置，`size`记录未截断的结果长度。
- 该聚合本身不拥有输出缓冲区。指针形式的`out`仅在相应缓冲区仍有效时可用。
- `format_to_n`等带类型格式化调用仍要求C++20及编译器支持`consteval`，保留格式串立即校验。结果类型在C++17可用不表示这些调用同时开放。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/format>

bool example()
{
    char output[3] = {};
    asc::std::format_to_n_result<char*> result{output + 2, 5};
    return result.out == output + 2 && result.size == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_format.md)
