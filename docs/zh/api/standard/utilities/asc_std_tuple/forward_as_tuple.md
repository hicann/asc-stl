# asc::std::forward_as_tuple

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

`asc::std::forward_as_tuple`把实参的引用和值类别组合为不拥有对象的tuple。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

```cpp
namespace asc::std {
template<class ...T> [[nodiscard]] constexpr tuple<T&&...> forward_as_tuple(T&&... values) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 待转发实参的类型；结果tuple以T&& 保存其引用并保持原值类别。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 待转发的各实参；返回的tuple保存各实参的引用（保持原值类别），实参生命周期须覆盖tuple的使用期。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `tuple<T &&...>` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |

## 约束说明

- 工具本身不额外分配容器存储；元素构造、赋值、交换或传入可调用体仍可按其自身语义分配或抛出，不能据此保证整个调用不分配。返回tuple借用原对象；这些对象须覆盖引用的全部使用期，不能返回借用局部对象的结果。

## 调用示例

以下Host示例在被引用对象仍存活时检查结果。

```cpp
#include <asc/std/tuple>

bool example()
{
    int value = 3;
    auto selected = asc::std::forward_as_tuple(value);
    asc::std::get<0>(selected) = 7;
    return value == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_tuple.md)
