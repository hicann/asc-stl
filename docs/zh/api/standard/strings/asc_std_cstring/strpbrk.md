# asc::std::strpbrk

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

`asc::std::strpbrk`查找首次属于给定字符集合的字符位置；AI Core SIMD编程 仅接受兼容的普通指针地址空间。

标准语义参考：[cppreference `cstring`](https://en.cppreference.com/w/cpp/header/cstring)。

## 函数原型

```cpp
namespace asc::std {
[[nodiscard]] constexpr const char* strpbrk(const char* value, const char* accepted) noexcept;
}
```

```cpp
namespace asc::std {
[[nodiscard]] constexpr char* strpbrk(char* value, const char* accepted) noexcept;
}
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被查找的窄字符串首地址，以空字符结尾。 |
| `accepted` | 输入 | 接受字符集合，以空字符结尾的窄字符串；命中其中任一字符即为查找成功。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被查找的窄字符串首地址，以空字符结尾。 |
| `accepted` | 输入 | 接受字符集合，以空字符结尾的窄字符串；命中其中任一字符即为查找成功。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `char *` | 返回匹配位置的指针；没有匹配项时返回空指针。 |
| 原型2 | `const char *` | 返回匹配位置的指针；没有匹配项时返回空指针。 |

## 约束说明

- 在Host侧和AI Core SIMT编程中使用普通指针。
- AI Core SIMD编程中使用local或generic地址空间的普通指针。
- 本接口只读访问输入，不限制只读输入彼此相同或重叠；返回的借用指针须在原字符存储仍有效时使用。

## 调用示例

以下Host示例给出具体输入并检查结果；底层对象与存储在检查期间仍有效。

```cpp
#include <asc/std/cstring>

bool example()
{
    char text[] = "abc123";
    return asc::std::strpbrk(text, "0123456789") == text + 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cstring.md)
