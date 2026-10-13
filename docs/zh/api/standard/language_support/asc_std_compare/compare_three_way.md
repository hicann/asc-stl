# asc::std::compare_three_way

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

头文件路径为：`<asc/std/compare>`。

`asc::std::compare_three_way`按名称指定的比较强度比较两个值，并返回ASC比较类别。

该接口自C++20+ 模式起提供。

标准语义参考：[cppreference `compare`](https://en.cppreference.com/w/cpp/header/compare)。

## 声明

```cpp
namespace asc::std {
struct compare_three_way;
} // namespace asc::std
```

## 约束说明

- 操作数必须为算术类型，或用户定义的 <=> 必须返回ASC比较类别。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <compare>
#include <asc/std/compare>

bool example()
{
    return asc::std::compare_three_way{}(2, 3) < 0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_compare.md)
