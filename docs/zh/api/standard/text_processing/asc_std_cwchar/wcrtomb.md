# asc::std::wcrtomb

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

`asc::std::wcrtomb`在调用方保存的多字节转换状态下处理宽字符或多字节序列。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 函数原型

```cpp
namespace asc::std {
size_t wcrtomb(char* output, wchar_t input, mbstate_t* state) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 指向接收多字节结果的目标缓冲区，容量须至少为MB_CUR_MAX字节；为空指针时不写入外部存储。 |
| `input` | 输入 | 待转换为多字节序列的宽字符。 |
| `state` | 输入/输出 | mbstate_t转换状态，跨调用保持；本次转换从该状态继续并在结束时更新它。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `size_t` | 返回写入的多字节序列字节数，包含空字符所需字节；编码错误返回size_t(-1)。 |

## 约束说明

- Host行为遵循系统`<cwchar>`提供的同名接口；字符转换和排序受当前C语言区域设置影响。
- Device固定为无状态单字节转换，仅支持ASCII及空字符；超出范围时按本接口返回值说明报告失败。
- 不同字符序列使用独立状态对象；字符串输出缓冲区须具有足够容量。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>

decltype(auto) example(char * output, wchar_t input, asc::std::mbstate_t * state)
{
    return asc::std::wcrtomb(output, input, state);
}

bool verify_example()
{
    asc::std::mbstate_t state{};
    char output[8] = {};
    return example(output, L'A', &state) == 1 && output[0] == 'A';
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwchar.md)
