# asc::std::chrono::make12

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

头文件路径为：`<asc/std/chrono>`。

`asc::std::chrono::make12`把24小时制数值转换为12小时制表示。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

```cpp
namespace asc::std::chrono {
[[nodiscard]] constexpr hours make12(const hours& value) noexcept;
} // namespace asc::std::chrono
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 以24小时制表示的小时（hours，计数单位为小时），取值0到23；返回对应的1到12小时制小时。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `hours` | 返回转换后的12小时制或24小时制小时值。 |

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/chrono>

decltype(auto) example(const asc::std::chrono::hours & value)
{
    return asc::std::chrono::make12(value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
