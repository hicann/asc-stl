# asc::std::nullopt_t

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

头文件路径为：`<asc/std/optional>`。

`asc::std::nullopt_t`标记optional不保存有效值的状态。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 声明

```cpp
namespace asc::std {
struct nullopt_t;
} // namespace asc::std
```

## 约束说明

- T必须是普通的非引用对象类型。
- Host遵循有效的C++17操作。
- Device侧构造、赋值、调用和交换所依赖的操作必须不抛出异常。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> value(7);
    asc::std::nullopt_t empty = asc::std::nullopt;
    value = empty;
    return !value.has_value();
}
```

## 关联API

- [本头文件的接口列表](asc_std_optional.md)
