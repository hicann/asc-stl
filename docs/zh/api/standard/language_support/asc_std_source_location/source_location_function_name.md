# asc::std::source_location::function_name

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

`asc::std::source_location::function_name`返回源代码位置保存的函数名。

标准语义参考：[cppreference `source_location`](https://en.cppreference.com/w/cpp/header/source_location)。

## 函数原型

所属类型：[`asc::std::source_location`](source_location.md)。

```cpp
// asc::std::source_location 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr const char* function_name() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `const char *` | 返回以零字符结尾的只读字符序列指针，其有效期受所属对象约束。 |

## 约束说明

- 提供标准source_location接口。
- 当编译器不能直接提供列号时，column()使用标准允许的回退值。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/source_location>

bool example()
{
    const auto location = asc::std::source_location::current();
    return location.line() > 0 && location.file_name()[0] != '\0' && location.function_name()[0] != '\0';
}
```

## 关联API

- [`asc::std::source_location`](source_location.md)
- [本头文件的接口列表](asc_std_source_location.md)
