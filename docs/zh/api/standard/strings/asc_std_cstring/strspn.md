# asc::std::strspn

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

`asc::std::strspn`统计起始位置连续属于给定字符集合的长度；AI Core SIMD编程 仅接受兼容的普通指针地址空间。

标准语义参考：[cppreference `cstring`](https://en.cppreference.com/w/cpp/header/cstring)。

## 函数原型

```cpp
namespace asc::std {
size_t strspn(const char* value, const char* accepted) noexcept(true);
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被统计的窄字符串首地址，以空字符结尾。 |
| `accepted` | 输入 | 接受字符集合，以空字符结尾的窄字符串；起始连续字符须属于该集合方计入长度。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `size_t` | 返回满足该接口匹配规则的初始连续字符数量。 |

## 约束说明

- 在Host侧和AI Core SIMT编程中使用普通指针。
- AI Core SIMD编程中使用local或generic地址空间的普通指针。
- 仅memmove允许源和目标重叠。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cstring>

decltype(auto) example(const char * value, const char * accepted)
{
    return asc::std::strspn(value, accepted);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cstring.md)
