# asc::std::wcstok

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

`asc::std::wcstok`按调用方提供的分隔集合切分宽字符串。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 函数原型

```cpp
namespace asc::std {
wchar_t* wcstok(wchar_t* input, const wchar_t* delimiters, wchar_t** state) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `input` | 输入/输出 | 首轮为可写、以零宽字符终止的字符串，分隔位置会写入零字符；后续传nullptr继续分词。 |
| `delimiters` | 输入 | 以零宽字符终止的分隔字符集合，可在连续调用之间更换。 |
| `state` | 输入/输出 | 指向保存下次扫描位置的指针槽；连续调用使用同一个非空槽。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `wchar_t *` | 返回本次切分所得宽字符串的起始指针；没有更多片段时返回空指针。 |

## 约束说明

- Host行为遵循系统`<cwchar>`提供的同名接口；字符转换和排序受当前C语言区域设置影响。
- 输入宽字符串须可写且以空字符结尾。该操作会写入分隔符终止位置；保存后续扫描位置的状态指针须有效。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>

decltype(auto) example(wchar_t * input, const wchar_t * delimiters, wchar_t ** state)
{
    return asc::std::wcstok(input, delimiters, state);
}

bool verify_example()
{
    wchar_t input[] = L"ab,cd";
    wchar_t* state = nullptr;
    wchar_t* first = example(input, L",", &state);
    wchar_t* second = example(nullptr, L",", &state);
    return first == input && first[0] == L'a' && first[2] == 0 && second == input + 3 && second[0] == L'c' && example(nullptr, L",", &state) == nullptr;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwchar.md)
