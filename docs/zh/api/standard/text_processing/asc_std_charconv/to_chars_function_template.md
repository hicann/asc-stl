# asc::std::to_chars（函数模板）

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

头文件路径为：`<asc/std/charconv>`。

`asc::std::to_chars`按指定进制把整数写入调用方提供的字符缓冲区。

标准语义参考：[cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr to_chars_result to_chars(char* first, char* last, T value) noexcept;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr to_chars_result to_chars(char* first, char* last, T value, int base) noexcept;
} // namespace asc::std
```

### 原型3

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr to_chars_result to_chars(char* first, char* last, signed char value, int base) noexcept;
} // namespace asc::std
```

### 原型4

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr to_chars_result to_chars(char* first, char* last, unsigned char value, int base) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 待写出值的类型；由所选原型决定按整数还是浮点格式转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 指向输出缓冲区起始位置的指针；转换结果从该位置开始写入。 |
| `last` | 输入 | 指向输出缓冲区末尾后一位置的指针；写出不得越过该位置。 |
| `value` | 输入 | 待转换为字符表示的数值。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 待写出值的类型；由所选原型决定按整数还是浮点格式转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 指向输出缓冲区起始位置的指针；转换结果从该位置开始写入。 |
| `last` | 输入 | 指向输出缓冲区末尾后一位置的指针；写出不得越过该位置。 |
| `value` | 输入 | 待转换为字符表示的数值。 |
| `base` | 输入 | 写出使用的进制，取值范围为2到36。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 待写出值的类型；由所选原型决定按整数还是浮点格式转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 指向输出缓冲区起始位置的指针；转换结果从该位置开始写入。 |
| `last` | 输入 | 指向输出缓冲区末尾后一位置的指针；写出不得越过该位置。 |
| `value` | 输入 | 待转换为字符表示的数值。 |
| `base` | 输入 | 写出使用的进制，取值范围为2到36。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 待写出值的类型；由所选原型决定按整数还是浮点格式转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 指向输出缓冲区起始位置的指针；转换结果从该位置开始写入。 |
| `last` | 输入 | 指向输出缓冲区末尾后一位置的指针；写出不得越过该位置。 |
| `value` | 输入 | 待转换为字符表示的数值。 |
| `base` | 输入 | 写出使用的进制，取值范围为2到36。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `to_chars_result` | 返回写入停止位置和错误状态；字符写入调用方缓冲区。 |
| 原型2 | `to_chars_result` | 返回写入停止位置和错误状态；字符写入调用方缓冲区。 |
| 原型3 | `to_chars_result` | 返回写入停止位置和错误状态；字符写入调用方缓冲区。 |
| 原型4 | `to_chars_result` | 返回写入停止位置和错误状态；字符写入调用方缓冲区。 |

## 约束说明

- 支持所有标准有符号/无符号整数类型以及2至36进制。
- AI Core SIMD编程 缓冲区必须是local或generic地址空间的普通char指针。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/charconv>

template <class T>
decltype(auto) example(char * first, char * last, T value)
{
    return asc::std::to_chars(first, last, value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_charconv.md)
