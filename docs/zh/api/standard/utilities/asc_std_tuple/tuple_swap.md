# asc::std::tuple::swap

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

头文件路径为：`<asc/std/tuple>`。

`asc::std::tuple::swap`交换两个对象保存的状态或元素。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

以下是`tuple<Types...>`类内的等价声明摘要，以公开元素特征表达异常条件；空tuple使用同一成员。

```cpp
constexpr void swap(tuple& other) noexcept((is_nothrow_swappable_v<Types> && ...));
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 另一个同类型tuple；逐项交换，两边元素须满足相应swap要求。 |

## 返回值说明

无返回值。

## 约束说明

- 所有对应元素须可交换；异常条件按各元素swap的noexcept合取。

- 工具本身不额外分配容器存储；元素构造、赋值、交换或传入可调用体仍可按其自身语义分配或抛出，不能据此保证整个调用不分配。

## 调用示例

以下Host示例给出具体输入，并在对象仍有效时检查结果。

```cpp
#include <asc/std/tuple>

bool example()
{
    asc::std::tuple<int, int> left(1, 2), right(3, 4);
    left.swap(right);
    return asc::std::get<0>(left) == 3 && asc::std::get<1>(right) == 2;
}
```

## 关联API

- [`asc::std::tuple`](tuple.md)
- [本头文件的接口列表](asc_std_tuple.md)
