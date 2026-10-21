# asc::std::memset

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

`asc::std::memset`把指定数量的字节写成同一个字节值；AI Core SIMD编程 仅接受兼容的普通指针地址空间。

标准语义参考：[cppreference `cstring`](https://en.cppreference.com/w/cpp/header/cstring)。

## 函数原型

```cpp
namespace asc::std {
void* memset(void* destination, int value, size_t count) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `destination` | 输出 | 用于接收结果的目标存储。本调用为同步执行，返回时写入已完成；目标存储在调用期间保持有效即可，且须为待写入内容预留足够空间。 |
| `value` | 输入 | 写入每个字节的字节值；转换为unsigned char后写入。 |
| `count` | 输入 | 操作的字节数；不随源对象或目标对象的类型大小自动换算。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `void *` | 返回目标缓冲区的起始指针。 |

## 约束说明

- 在Host侧和AI Core SIMT编程中使用普通指针。
- AI Core SIMD编程中使用local或generic地址空间的普通指针。
- 目标范围须可写且容纳count字节；value先转换为unsigned char后逐字节写入。

## 调用示例

以下Host示例给出具体输入并检查结果；底层对象与存储在检查期间仍有效。

```cpp
#include <asc/std/cstring>

bool example()
{
    unsigned char bytes[4]{};
    void* result = asc::std::memset(bytes, 0x41, 4);
    return result == bytes && bytes[0] == 0x41 && bytes[3] == 0x41;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cstring.md)
