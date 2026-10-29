# asc::std::in_range

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

头文件路径为：`<asc/std/utility>`。

`asc::std::in_range`判断整数值能否由指定目标整数类型表示。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
namespace asc::std {
template<class T, class U> constexpr bool in_range(U value) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 目标整数类型；判断value的值能否由该类型表示。 |
| `U` | 待判断值的整数类型，须为标准有符号或无符号整数类型（不含bool、char及其他字符编码类型）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待判断可表示性的整数值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 类型域包括signed char、unsigned char及标准有符号/无符号整数类型；排除bool、char、wchar_t、char8_t、char16_t和char32_t。

- 遵循标准整数约束。

## 调用示例

以下片段用具体数值展示本页调用。

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    return asc::std::in_range<unsigned int>(3);
}

bool verify_example()
{
    return example();
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
