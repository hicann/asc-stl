# asc::std::integral_constant::`operator()`

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

头文件路径为：`<asc/std/type_traits>`。

`asc::std::integral_constant::operator()`按`integral_constant`的可用运算符规则处理当前对象及操作数。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 函数原型

所属类型：[`asc::std::integral_constant`](integral_constant.md)。

```cpp
// asc::std::integral_constant 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr value_type operator()() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `value_type` | 返回该编译期常量包装器保存的值。 |

## 约束说明

- 提供特征类及其对应的 _v辅助形式。

## 调用示例

以下Host片段使用具体类型演示调用；指针、范围和索引须满足本页约束。

```cpp
#include <asc/std/type_traits>

decltype(auto) example()
{
    return asc::std::integral_constant<int, 3>{}();
}
```

## 关联API

- [`asc::std::integral_constant`](integral_constant.md)
- [本头文件的接口列表](asc_std_type_traits.md)
