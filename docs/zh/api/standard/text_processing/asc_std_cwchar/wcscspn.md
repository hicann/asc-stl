# asc::std::wcscspn

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

`asc::std::wcscspn`统计起始位置连续不属于给定字符集合的长度。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 函数原型

```cpp
namespace asc::std {
size_t wcscspn(const wchar_t* input, const wchar_t* rejected) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `input` | 输入 | 被扫描的以零宽字符终止的字符串。 |
| `rejected` | 输入 | 以零宽字符终止的拒绝字符集合。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `size_t` | 返回满足该接口匹配规则的初始连续字符数量。 |

## 约束说明

- 18个标准函数名及23个可调用签名：wmemcpy/wmemmove/wmemchr/wmemcmp/wmemset、wcscpy/wcsncpy/wcscat/wcsncat、wcschr/wcsrchr、wcscmp/wcsncmp、wcsspn/wcscspn/wcspbrk/wcsstr/wcslen。
- 5个查找函数包含const与可变指针重载。
- Host委托系统，Device纯计算实现。
- Host、AI Core SIMD编程 和AI Core SIMT编程兼容plain-pointer域。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>

decltype(auto) example(const wchar_t * input, const wchar_t * rejected)
{
    return asc::std::wcscspn(input, rejected);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cwchar.md)
