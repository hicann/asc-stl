# asc::std::ranges::greater_equal::`operator()`

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

头文件路径为：`<asc/std/functional>`。

`asc::std::ranges::greater_equal::operator()`按函数对象名称比较输入值并返回布尔结果。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

所属类型：[`asc::std::ranges::greater_equal`](ranges_greater_equal.md)。

```cpp
// asc::std::ranges::greater_equal 类内的声明节选；模板形参和其他成员由所属类提供。
template<class T, class U> constexpr bool operator()(T&& lhs, U&& rhs) const noexcept(noexcept(static_cast<bool>(!(lhs < rhs))));
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 左侧操作数类型；须支持该函数对象执行的运算。 |
| `U` | 右侧操作数类型；须支持该函数对象执行的运算。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 同时提供指定类型形式和透明调用形式。

## 调用示例

以下Host片段以具体整数实参演示函数对象调用。

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    return asc::std::ranges::greater_equal{}(1, 2);
}
```

## 关联API

- [`asc::std::ranges::greater_equal`](ranges_greater_equal.md)
- [本头文件的接口列表](asc_std_functional.md)
