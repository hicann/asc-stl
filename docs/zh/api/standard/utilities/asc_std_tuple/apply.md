# asc::std::apply

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

`asc::std::apply`把tuple元素展开为函数对象的实参并调用。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

```cpp
namespace asc::std {
template<class Function, class Tuple> constexpr decltype(auto) apply(Function&& function, Tuple&& value);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Function` | 接收展开后的tuple-like元素的可调用对象类型。 |
| `Tuple` | 提供tuple_size及get的tuple-like实参类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 被调用的可调用对象；tuple的各元素按序展开为其实参（按invoke语义调用），返回其调用结果。 |
| `value` | 输入/输出 | 被展开调用的tuple对象；其各元素按序作为调用实参，右值元素被移动，移动后处于有效但未指定状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `decltype(auto)` | 返回将tuple元素展开后调用函数对象的结果。 |

## 约束说明

- 工具本身不额外分配容器存储；元素构造、赋值、交换或传入可调用体仍可按其自身语义分配或抛出，不能据此保证整个调用不分配。

## 调用示例

以下Host示例用具体输入和可判断结果展示本接口。

```cpp
#include <asc/std/tuple>

bool example()
{
    const auto values = asc::std::make_tuple(2, 3);
    return asc::std::apply([](int left, int right) { return left + right; }, values) == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_tuple.md)
