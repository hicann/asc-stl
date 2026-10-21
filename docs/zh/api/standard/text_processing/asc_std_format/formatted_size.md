# asc::std::formatted_size

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

`asc::std::formatted_size`计算格式化结果所需的字符数，不写入输出缓冲区。

该接口自C++20+ 模式起提供。

标准语义参考：[cppreference `format`](https://en.cppreference.com/w/cpp/header/format)。

## 函数原型

```cpp
namespace asc::std {
template<class... Args> constexpr size_t formatted_size(format_string<Args...> format, Args&&... args) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args` | 格式化实参的类型列表，由args推导。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `format` | 输入 | 编译期校验的格式串；替换字段、格式说明与args中的对应实参匹配。 |
| `args` | 输入 | 与格式串替换字段对应的值；按其实际类型格式化。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `size_t` | 返回按给定格式生成完整结果所需的字符数量。 |

## 约束说明

- 自C++20起提供。支持bool、char、C字符串的默认格式，以及非bool/char标准整数的默认格式和d/x/X/o/b进制格式。
- 支持转义花括号，不进行动态分配；格式串与实参须满足类型及字段要求。
- 只计算字符数，返回值不包含结尾空字符。
- 可在Host、AI Core SIMD编程和AI Core SIMT编程使用。

## 调用示例

以下Host示例给出具体输入，并在对象与底层存储仍有效时检查结果。

```cpp
#include <asc/std/format>

bool example()
{
    return asc::std::formatted_size("{}", 123) == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_format.md)
