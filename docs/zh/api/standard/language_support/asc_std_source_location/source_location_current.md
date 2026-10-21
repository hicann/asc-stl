# asc::std::source_location::current

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

头文件路径为：`<asc/std/source_location>`。

`asc::std::source_location::current`捕获调用位置的文件、函数、行和列信息。

标准语义参考：[cppreference `source_location`](https://en.cppreference.com/w/cpp/header/source_location)。

## 函数原型

所属类型：[`source_location`](source_location.md)。以下展示提供文件、函数和行号内建函数的配置；可零实参按类调用。没有这些内建函数时，文件/行号退回声明处的__FILE__/__LINE__，函数名退回空字符串。

```cpp
#if __has_builtin(__builtin_COLUMN)
[[nodiscard]] static constexpr source_location current(
    const char* file_name = __builtin_FILE(),
    const char* function_name = __builtin_FUNCTION(),
    uint_least32_t line = __builtin_LINE(),
    uint_least32_t column = __builtin_COLUMN()) noexcept;
#else
[[nodiscard]] static constexpr source_location current(
    const char* file_name = __builtin_FILE(),
    const char* function_name = __builtin_FUNCTION(),
    uint_least32_t line = __builtin_LINE(),
    uint_least32_t column = 0) noexcept;
#endif
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `file_name` | 输入 | 源文件名，以空字符结尾的字符串首地址；缺省实参由编译器内建信息填充。 |
| `function_name` | 输入 | 函数名，以空字符结尾的字符串首地址；缺省实参由编译器内建信息填充。 |
| `line` | 输入 | 行号，按值保存；缺省由编译器提供，0可用于表示未知位置。 |
| `column` | 输入 | 列号，按值保存；有列号内建函数时缺省由其提供，否则为0。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `source_location` | 返回记录当前调用点文件、函数、行和列的源码位置对象。 |

## 约束说明

- 同步捕获位置，不分配或复制文件名、函数名字符串。
- 缺省字符串来自编译器；显式传入字符串时，其存储须覆盖source_location及其字符串指针的使用期。
- 不支持列号内建函数时，缺省column为0；0表示没有可用列号。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/source_location>

bool example()
{
    const auto implicit = asc::std::source_location::current();
    const auto selected = asc::std::source_location::current("example.cpp", "example", 7, 0);
    return implicit.line() > 0 && selected.line() == 7 && selected.file_name()[0] == 'e';
}
```

## 关联API

- [`asc::std::source_location`](source_location.md)
- [本头文件的接口列表](asc_std_source_location.md)
