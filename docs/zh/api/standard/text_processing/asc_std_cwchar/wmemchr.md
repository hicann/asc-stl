# asc::std::wmemchr

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

`asc::std::wmemchr` 在指定字节范围中查找目标字节。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 函数原型

### 原型 1

```cpp
const wchar_t* asc::std::wmemchr(const wchar_t* input, wchar_t value, size_t count) noexcept;
```

### 原型 2

```cpp
wchar_t* asc::std::wmemchr(wchar_t* input, wchar_t value, size_t count) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `input` | 输入 | 被查找的宽字符数组首地址；至少可读取 count 个宽字符。 |
| `value` | 输入 | 待查找的目标宽字符。 |
| `count` | 输入 | 参与查找的宽字符数量。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `input` | 输入 | 被查找的宽字符数组首地址；至少可读取 count 个宽字符。 |
| `value` | 输入 | 待查找的目标宽字符。 |
| `count` | 输入 | 参与查找的宽字符数量。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `const wchar_t *` | 返回匹配位置的指针；没有匹配项时返回空指针。 |
| 原型 2 | `wchar_t *` | 返回匹配位置的指针；没有匹配项时返回空指针。 |

## 约束说明

- 18个标准函数名及23个可调用签名：wmemcpy/wmemmove/wmemchr/wmemcmp/wmemset、wcscpy/wcsncpy/wcscat/wcsncat、wcschr/wcsrchr、wcscmp/wcsncmp、wcsspn/wcscspn/wcspbrk/wcsstr/wcslen
- 5个查找函数包含const与可变指针重载
- Host委托系统，Device纯计算实现
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程兼容plain-pointer域

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>
#include <asc/std/cstddef>

decltype(auto) example(const wchar_t * input, wchar_t value, asc::std::size_t count)
{
    return asc::std::wmemchr(input, value, count);
}
```
