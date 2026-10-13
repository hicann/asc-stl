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

所属类型：[`asc::std::source_location`](source_location.md)。

```cpp
// asc::std::source_location 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr source_location current(const char* file_name, const char* function_name, uint_least32_t line, uint_least32_t column) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `file_name` | 输入 | 源文件名，以空字符结尾的字符串首地址；缺省实参由编译器内建信息填充。 |
| `function_name` | 输入 | 函数名，以空字符结尾的字符串首地址；缺省实参由编译器内建信息填充。 |
| `line` | 输入 | 行号（uint_least32_t，从1起）；缺省实参由编译器内建信息填充。 |
| `column` | 输入 | 列号（uint_least32_t，从1起）；缺省实参由编译器内建信息填充。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `source_location` | 返回记录当前调用点文件、函数、行和列的源码位置对象。 |

## 约束说明

- 提供标准source_location接口。
- 当编译器不能直接提供列号时，column()使用标准允许的回退值。

## 调用示例

以下Host片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/source_location>

decltype(auto) example()
{
    auto source = asc::std::source_location::current("example.cpp", "example", 1, 0);
    return source.line();
}
```

## 关联API

- [`asc::std::source_location`](source_location.md)
- [本头文件的接口列表](asc_std_source_location.md)
