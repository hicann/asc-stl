# asc::std::optional<T&>::has_value

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

`asc::std::optional<T&>::has_value`判断对象当前是否保存有效值。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

```cpp
// asc::std::optional<T&> 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr bool has_value() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 对象保存有效值时返回`true`，否则返回`false`。 |

## 约束说明

- 引用特化仅允许安全的同类型左值绑定。
- 采用借用指针语义，不提供容易产生悬空引用的转换。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/optional>

bool example()
{
    int number = 7;
    asc::std::optional<int&> value(number);
    return value.has_value() && &*value == &number;
}
```

## 关联API

- [本头文件的接口列表](asc_std_optional.md)
