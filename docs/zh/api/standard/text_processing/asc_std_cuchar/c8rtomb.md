# asc::std::c8rtomb

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

包含公开头文件`<asc/std/cuchar>`，通过`asc::std::c8rtomb`将一个UTF编码单元转换为多字节输出。Host使用系统转换接口；Device只处理ASCII及空字符。该接口要求C++20。

Host语义参考：[cppreference字符转换接口](https://en.cppreference.com/w/cpp/header/cuchar)。

## 函数原型

Host通过`using`引入系统`std::c8rtomb`，异常说明和参数名称以系统声明为准。以下为Device声明；省略了执行位置宏。Device实现使用的`__SIZE_TYPE__`等价于公开的`asc::std::size_t`。

```cpp
namespace asc::std {
size_t c8rtomb(char* output, char8_t value, mbstate_t* state) noexcept;
}
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 可写目标缓冲区。Host需要容纳当前编码的最长序列；Device非空时至少容纳1字节。Device为空时不写入，但仍按value判断结果。 |
| `value` | 输入 | 待转换的char8_t编码单元。Device仅接受0至127；Host的代理项或多单元续接遵循系统接口。 |
| `state` | 输入/输出 | Host保留跨调用转换状态，空指针采用系统内部状态。Device不读写该参数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::size_t` | Host：成功返回写入字节数；续接尚未形成输出时可返回0；编码错误返回`size_t(-1)`并设置错误状态。具体续接规则取决于本接口和系统区域设置。Device：value为0至127时返回1，否则返回`size_t(-1)`；不返回未完成状态。 |

## 约束说明

- Device不执行UTF多单元续接，不更新state。Host在连续转换中保持同一状态对象，转换不同序列时重新初始化状态。
- 输入和输出存储在调用期间保持有效；输入范围与输出容量符合参数说明。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/cuchar>

bool example()
{
    char output[8] = {};
    asc::std::mbstate_t state{};
    auto count = asc::std::c8rtomb(output, u8'A', &state);
    return count == 1 && output[0] == 'A';
}
```

## 关联API

- [本头文件的接口列表](asc_std_cuchar.md)
