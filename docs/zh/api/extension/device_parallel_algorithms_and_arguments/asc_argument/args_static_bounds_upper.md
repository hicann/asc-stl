# asc::args::static_bounds::upper

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

头文件路径为：`<asc/argument>`。

`asc::args::static_bounds::upper`返回边界对象保存或编码的上界。

## 函数原型

所属类型：[`asc::args::static_bounds`](args_static_bounds.md)。

```cpp
// asc::args::static_bounds 类内的声明节选；模板形参和其他成员由所属类提供。
static constexpr decltype(Upper) upper() noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `decltype(Upper)` | 返回边界对象保存或编码的上界。 |

## 约束说明

- Lower和Upper是编译期边界，须满足Lower <= Upper；查询只返回所保存常量，不读取延迟指针。

- 使用C++17，可在Host、AI Core SIMD编程 和AI Core SIMT编程中使用。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/argument>

bool example()
{
    static_assert(asc::args::static_bounds<0, 10>::lower() == 0);
    static_assert(asc::args::static_bounds<0, 10>::upper() == 10);
    return true;
}
```

## 关联API

- [`asc::args::static_bounds`](args_static_bounds.md)
- [本头文件的接口列表](asc_argument.md)
