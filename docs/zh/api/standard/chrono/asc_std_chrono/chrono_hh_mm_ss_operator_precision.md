# asc::std::chrono::hh_mm_ss::operator precision

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

`asc::std::chrono::hh_mm_ss::operator precision`由`<asc/std/chrono>`提供，把时分秒拆分值还原为precision精度的总时长。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

```cpp
explicit constexpr asc::std::chrono::hh_mm_ss::operator precision() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `precision` | 按该对象的符号及小时、分钟、秒和小数秒合成的duration。 |

## 约束说明

- 转换结果等价于to_duration()，即为构造时传入的原始时长。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::hh_mm_ss<asc::std::chrono::seconds> value{asc::std::chrono::seconds{3661}};
    return static_cast<asc::std::chrono::seconds>(value).count() == 3661;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
