# asc::std::variant::swap

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

头文件路径为：`<asc/std/variant>`。

`asc::std::variant::swap`交换两个对象保存的状态或元素。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

所属类型：[`asc::std::variant`](variant.md)。

```cpp
// asc::std::variant 类内的声明节选；模板形参和其他成员由所属类提供。
template<bool Dummy, class Constraint, class> void swap(variant<Types...>& other) noexcept(Constraint::Isnothrowswappablev);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Dummy` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `未命名参数3` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 与当前对象交换状态的另一对象；交换后双方保存对方原有状态。 |

## 返回值说明

无返回值。

## 约束说明

- Device侧备选类型以及所选构造、赋值和交换操作必须不抛出异常。
- index、`operator*`、emplace、swap和visit仅提供非抛出路径。

## 调用示例

以下Host片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/variant>

void example()
{
    asc::std::variant<int, float> left(7), right(8.0f);
    left.swap(right);
}
```

## 关联API

- [`asc::std::variant`](variant.md)
- [本头文件的接口列表](asc_std_variant.md)
