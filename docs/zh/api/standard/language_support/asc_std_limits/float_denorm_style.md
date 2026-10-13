# asc::std::float_denorm_style

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

头文件路径为：`<asc/std/limits>`。

`asc::std::float_denorm_style`列出浮点类型的次正规数表示类别。

标准语义参考：[cppreference `limits`](https://en.cppreference.com/w/cpp/header/limits)。

## 声明

```cpp
namespace asc::std {
enum float_denorm_style;
} // namespace asc::std
```

## 约束说明

- 支持全部标准算术类型及其cv限定形式。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/limits>

bool example()
{
    // 查询当前目标float类型的表示和舍入特性。
    const auto style = asc::std::numeric_limits<float>::has_denorm;
    return style == asc::std::denorm_present || style == asc::std::denorm_absent || style == asc::std::denorm_indeterminate;
}
```

## 关联API

- [本头文件的接口列表](asc_std_limits.md)
