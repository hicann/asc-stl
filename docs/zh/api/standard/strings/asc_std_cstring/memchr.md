# asc::std::memchr

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

头文件路径为：`<asc/std/cstring>`。

`asc::std::memchr` 在指定字节范围中查找目标字节；AI Core SIMD 编程 仅接受兼容的普通指针地址空间。

标准语义参考：[cppreference `cstring`](https://en.cppreference.com/w/cpp/header/cstring)。

## 函数原型

### 原型 1

```cpp
const void* asc::std::memchr(const void* value, int character, size_t count) noexcept;
```

### 原型 2

```cpp
void* asc::std::memchr(void* value, int character, size_t count) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被查找的字节缓冲区首地址；可读范围至少包含 count 个字节。 |
| `character` | 输入 | 待查找的目标字节值；按 unsigned char 解释后逐字节比较。 |
| `count` | 输入 | 被查找的字节数，即缓冲区长度，单位为字节。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被查找的字节缓冲区首地址；可读范围至少包含 count 个字节。 |
| `character` | 输入 | 待查找的目标字节值；按 unsigned char 解释后逐字节比较。 |
| `count` | 输入 | 被查找的字节数，即缓冲区长度，单位为字节。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `const void *` | 返回匹配位置的指针；没有匹配项时返回空指针。 |
| 原型 2 | `void *` | 返回匹配位置的指针；没有匹配项时返回空指针。 |

## 约束说明

- 在 Host 侧和 AI Core SIMT 编程中使用普通指针
- AI Core SIMD 编程中使用 local 或 generic 地址空间的普通指针
- 仅 memmove 允许源和目标重叠

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cstring>
#include <asc/std/cstddef>

decltype(auto) example(const void * value, int character, asc::std::size_t count)
{
    return asc::std::memchr(value, character, count);
}
```
