# asc::std::difftime

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

头文件路径为：`<asc/std/ctime>`。

`asc::std::difftime`计算两个时间值之间以秒为单位的差。

标准语义参考：[cppreference `ctime`](https://en.cppreference.com/w/cpp/header/ctime)。

## 函数原型

```cpp
namespace asc::std {
constexpr double difftime(time_t end, time_t start) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `end` | 输入 | 结束时刻的日历时间（time_t，单位为秒）。 |
| `start` | 输入 | 起始时刻的日历时间（time_t，单位为秒）；返回end减start的秒数差。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `double` | 返回两个时间值之间以秒为单位的差的计算结果。 |

## 约束说明

- Host使用标准时钟。
- AI Core SIMD编程中使用get_sys_cnt，AI Core SIMT编程中使用clock64。
- Device计数器频率为页面声明的1 GHz，difftime仅进行值计算。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ctime>

decltype(auto) example(asc::std::time_t end, asc::std::time_t start)
{
    return asc::std::difftime(end, start);
}
```

## 关联API

- [本头文件的接口列表](asc_std_ctime.md)
