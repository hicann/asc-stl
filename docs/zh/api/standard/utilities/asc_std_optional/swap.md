# asc::std::swap

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

`asc::std::swap(optional<T>&, optional<T>&)`由`<asc/std/optional>`提供，自由函数swap，ADL与非限定调用点命中并转发成员swap。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

```cpp
template <class T> constexpr enable_if_t<is_move_constructible_v<T> && is_swappable_v<T>, void> swap(optional<T>& left, optional<T>& right) noexcept(noexcept(left.swap(right)));
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 两侧optional的存储元素类型；元素须支持移动构造和交换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入/输出 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |
| `right` | 输入/输出 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `void` | 无返回值；交换两对象的含值状态及其存储值。 |

## 约束说明

- 自由函数swap，ADL与非限定调用点命中并转发成员swap。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/optional>

template <class T>
decltype(auto) example(asc::std::optional<T>& left, asc::std::optional<T>& right)
{
    return asc::std::swap(left, right);
}
```

## 关联API

- [本头文件的接口列表](asc_std_optional.md)
