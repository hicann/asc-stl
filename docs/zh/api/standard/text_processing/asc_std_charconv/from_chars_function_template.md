# asc::std::from_chars（函数模板）

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

`asc::std::from_chars`按指定进制解析字符范围中的整数。

标准语义参考：[cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv)。

## 函数原型

各重载位于`asc::std`命名空间；整数模板的选择条件排除bool和字符编码类型。

```cpp
namespace asc::std {
template<class T, enable_if_t<__is_integer_v<T>, int> = 0>
constexpr from_chars_result from_chars(const char* first, const char* last, T& value, int base = 10) noexcept;
}
```

```cpp
namespace asc::std {
constexpr from_chars_result from_chars(const char* first, const char* last, signed char& value, int base = 10) noexcept;
}
```

```cpp
namespace asc::std {
constexpr from_chars_result from_chars(const char* first, const char* last, unsigned char& value, int base = 10) noexcept;
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
| `first` | 输入 | 有效字符范围的起点，须与last属于同一缓冲区。 |
| `last` | 输入 | 字符范围的末尾后一位置。 |
| `value` | 输入/输出 | 接收解析值；失败时保持原值。 |
| `base` | 输入 | 进制，2至36；省略时为10。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `from_chars_result` | ptr指向解析停止位置，ec为空错误码时成功并写入value；无匹配字符或超出可表示范围时报告对应错误，value保持原值。 |

## 约束说明

- 支持所有标准有符号/无符号整数类型以及2至36进制。
- 不跳过前导空白，不接受前导`+`；仅有符号目标接受`-`。即使`base`为16，也不会自动跳过`0x`前缀。
- 字符串张量转整数时，`ec == errc{}`只表示成功解析了数值前缀。若业务要求整个字段都是整数，还须检查`ptr == last`；例如`"42x"`会成功解析42，但停止于`x`。空白裁剪应由调用方明确完成，失败时不可使用旧的`value`作为本行输出。
- AI Core SIMD编程 缓冲区必须是local或generic地址空间的普通char指针。

## 调用示例

以下Host示例给出具体输入，并在对象与底层存储仍有效时检查结果。

```cpp
#include <asc/std/charconv>

bool example()
{
    const char input[] = "42";
    int value = 0;
    const auto result = asc::std::from_chars(input, input + 2, value);
    if (result.ptr != input + 2 || result.ec != asc::std::errc{} || value != 42) {
        return false;
    }
    const char partial[] = "42x";
    const auto prefix = asc::std::from_chars(partial, partial + 3, value);
    const bool whole_field = prefix.ec == asc::std::errc{} && prefix.ptr == partial + 3;
    return prefix.ec == asc::std::errc{} && prefix.ptr == partial + 2 && !whole_field;
}
```

## 关联API

- [本头文件的接口列表](asc_std_charconv.md)
