# asc::std::wcscpy

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

`asc::std::wcscpy`复制以零字符结尾的宽字符串。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 函数原型

```cpp
namespace asc::std {
wchar_t* wcscpy(wchar_t* destination, const wchar_t* source) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `destination` | 输出 | 用于接收结果的目标存储。本调用为同步执行，返回时写入已完成；目标存储在调用期间保持有效即可，且须为待写入内容预留足够空间。 |
| `source` | 输入 | 源数据或源对象。本调用为同步执行，返回时读取已完成；源存储在调用期间保持有效即可。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `wchar_t *` | 返回目标缓冲区的起始指针。 |

## 约束说明

- 18个标准函数名及23个可调用签名：wmemcpy/wmemmove/wmemchr/wmemcmp/wmemset、wcscpy/wcsncpy/wcscat/wcsncat、wcschr/wcsrchr、wcscmp/wcsncmp、wcsspn/wcscspn/wcspbrk/wcsstr/wcslen。
- 5个查找函数包含const与可变指针重载。
- Host委托系统，Device纯计算实现。
- Host、AI Core SIMD编程 和AI Core SIMT编程兼容plain-pointer域。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>

decltype(auto) example(wchar_t * destination, const wchar_t * source)
{
    return asc::std::wcscpy(destination, source);
}

bool verify_example()
{
    wchar_t output[8] = {};
    const bool same = example(output, L"cd") == output;
    const wchar_t expected[] = L"cd";
    for (unsigned index = 0; index < sizeof(expected) / sizeof(wchar_t); ++index) { if (output[index] != expected[index]) return false; }
    return same;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwchar.md)
