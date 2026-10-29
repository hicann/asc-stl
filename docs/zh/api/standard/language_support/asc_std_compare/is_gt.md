# asc::std::is_gt

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

`asc::std::is_gt`判断比较类别结果是否满足名称指定的关系。

标准语义参考：[cppreference `compare`](https://en.cppreference.com/w/cpp/header/compare)。

## 函数原型

```cpp
namespace asc::std {
constexpr bool is_gt(partial_ordering value) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被检测的比较类别值（partial_ordering）；判断其是否表示“大于”关系。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- `weak_ordering`和`strong_ordering`可隐式转换后传入；对`partial_ordering::unordered`，本函数返回`false`。

- 支持ASC比较类别常量、与零比较以及标准类别转换。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/compare>

bool example(asc::std::partial_ordering value)
{
    return asc::std::is_gt(value);
}

bool verify_example()
{
    using order = asc::std::partial_ordering;
    return example(order::less) == false &&
        example(order::equivalent) == false &&
        example(order::greater) == true &&
        example(order::unordered) == false &&
        asc::std::is_gt(asc::std::weak_ordering::equivalent) == false &&
        asc::std::is_gt(asc::std::strong_ordering::greater) == true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_compare.md)
