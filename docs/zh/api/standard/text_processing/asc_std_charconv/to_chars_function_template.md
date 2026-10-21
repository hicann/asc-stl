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

各重载位于`asc::std`命名空间；整数模板的选择条件排除bool和字符编码类型。

```cpp
namespace asc::std {
template<class T, enable_if_t<__is_integer_v<T>, int> = 0>
constexpr to_chars_result to_chars(char* first, char* last, T value, int base = 10) noexcept;
}
```

```cpp
namespace asc::std {
constexpr to_chars_result to_chars(char* first, char* last, signed char value, int base = 10) noexcept;
}
```

```cpp
namespace asc::std {
constexpr to_chars_result to_chars(char* first, char* last, unsigned char value, int base = 10) noexcept;
}
```

## 参数说明

**模板参数（仅整数模板）**

| 参数名 | 描述 |
| --- | --- |
| `T` | 标准有符号或无符号整数类型；不含bool、char、wchar_t、char8_t、char16_t和char32_t。char及signed/unsigned char另有固定重载。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输出 | 有效字符范围的起点，须与last属于同一缓冲区。 |
| `last` | 输入 | 字符范围的末尾后一位置。 |
| `value` | 输入 | 待写出的整数值。 |
| `base` | 输入 | 进制，2至36；省略时为10。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `to_chars_result` | ptr指向输出末尾，ec为空错误码时成功；容量不足时报告value_too_large，base非法时报告invalid_argument；不会自动写入终止空字符。 |

## 约束说明

- 支持所有标准有符号/无符号整数类型以及2至36进制。
- AI Core SIMD编程 缓冲区必须是local或generic地址空间的普通char指针。

## 调用示例

以下Host示例给出具体输入，并在对象与底层存储仍有效时检查结果。

```cpp
#include <asc/std/charconv>

bool example()
{
    char output[4]{};
    const auto result = asc::std::to_chars(output, output + 4, 42);
    return result.ptr == output + 2 && result.ec == asc::std::errc{} && output[0] == '4' && output[1] == '2';
}
```

## 关联API

- [本头文件的接口列表](asc_std_charconv.md)
