# asc::std::mbrtoc8

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

包含公开头文件`<asc/std/cuchar>`，通过`asc::std::mbrtoc8`将多字节输入转换为一个UTF编码单元。Host使用系统转换接口；Device只处理ASCII及空字符。该接口要求C++20。

Host语义参考：[cppreference字符转换接口](https://en.cppreference.com/w/cpp/header/cuchar)。

## 函数原型

Host通过`using`引入系统`std::mbrtoc8`，异常说明和参数名称以系统声明为准。以下为Device声明；省略了执行位置宏。Device实现使用的`__SIZE_TYPE__`等价于公开的`asc::std::size_t`。

```cpp
namespace asc::std {
size_t mbrtoc8(char8_t* output, const char* input, size_t count, mbstate_t* state) noexcept;
}
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 非空时指向一个可写的char8_t元素；为空时仅计算转换结果。 |
| `input` | 输入 | 输入字节序列。Device非空且count非零时只读取首字节；为空时执行重置路径。 |
| `count` | 输入 | 输入可读取的最大字节数，单位为字节。Device在input非空且count为0时返回`size_t(-2)`。 |
| `state` | 输入/输出 | Host保留跨调用转换状态。Device只在input为空时把非空state重置为初始值，其余路径不更新。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::size_t` | Host：正常返回消费字节数，空字符返回0，非法序列返回`size_t(-1)`，输入不足返回`size_t(-2)`；从保存状态输出后续编码单元时，适用的接口可返回`size_t(-3)`。Device：input为空或首字节为空字符时返回0；有效非空ASCII返回1；超出ASCII返回`size_t(-1)`；input非空且count为0返回`size_t(-2)`。 |

## 约束说明

- Device仅支持ASCII和空字符，不保存不完整的多字节输入。input为空时，会把非空output写为空字符，并重置非空state；不要假定这一行为与所有Host系统相同。
- 输入和输出存储在调用期间保持有效；输入范围与输出容量符合参数说明。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/cuchar>

bool example()
{
    char8_t output{};
    asc::std::mbstate_t state{};
    auto count = asc::std::mbrtoc8(&output, "A", 1, &state);
    return count == 1 && output == u8'A';
}
```

## 关联API

- [本头文件的接口列表](asc_std_cuchar.md)
