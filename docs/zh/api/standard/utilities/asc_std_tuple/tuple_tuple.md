# asc::std::tuple::tuple

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

`asc::std::tuple::tuple`按本页所列构造形态初始化`tuple`对象。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

以下为所属类内的**调用形态摘要**。省略实现使用的SFINAE选择参数；同形的隐式与explicit形式分别受下面的可构造性、可转换性条件选择，不能将摘要复制为一组无条件重载定义。

```cpp
constexpr tuple() = default;
```

```cpp
tuple(const tuple&) = default;
```

```cpp
tuple(tuple&&) = default;
```

```cpp
constexpr tuple(const Types&... values);
```

```cpp
constexpr explicit tuple(const Types&... values);
```

```cpp
template <class... Values>
constexpr tuple(Values&&... values);
```

```cpp
template <class... Values>
constexpr explicit tuple(Values&&... values);
```

```cpp
template <class... UTypes>
constexpr tuple(const tuple<UTypes...>& other);
```

```cpp
template <class... UTypes>
constexpr explicit tuple(const tuple<UTypes...>& other);
```

```cpp
template <class... UTypes>
constexpr tuple(tuple<UTypes...>&& other);
```

```cpp
template <class... UTypes>
constexpr explicit tuple(tuple<UTypes...>&& other);
```

```cpp
template <class Alloc>
constexpr tuple(allocator_arg_t, const Alloc& alloc);
```

```cpp
template <class Alloc>
constexpr tuple(allocator_arg_t, const Alloc& alloc, const Types&... values);
```

```cpp
template <class Alloc>
constexpr tuple(allocator_arg_t, const Alloc& alloc, const tuple& other);
```

```cpp
template <class Alloc>
constexpr tuple(allocator_arg_t, const Alloc& alloc, tuple&& other);
```

```cpp
template <class Alloc, class... UTypes>
constexpr tuple(allocator_arg_t, const Alloc& alloc, const tuple<UTypes...>& other);
```

## 参数说明

**模板参数**

`Types...`是所属tuple元素类型；Values...和UTypes...分别表示逐元素实参与来源tuple元素类型，Alloc是分配器类型。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values...` | 输入/输出（可移动来源） | 按相应值类别构造每个元素；const引用形式只读。 |
| `other` | 输入/输出（可移动来源） | 来源tuple；const引用复制，右值形式可移动。 |
| `alloc` | 输入 | allocator_arg形态使用的分配器，按各元素uses_allocator规则参与构造。 |

## 返回值说明

无返回值。

## 约束说明

- const Types&...元素构造仅用于非空tuple。同形的implicit和explicit摘要分别受逐元素可隐式转换与至少一个显式转换条件选择。

- 参数个数须与Types...个数一致且各元素可从对应来源构造；全部对应转换可隐式进行时采用不带explicit的形式，否则采用explicit形式。异类型tuple转换还排除应由单元素构造或复制/移动形态处理的情况。allocator_arg形式按各元素的uses_allocator规则传递分配器，构造、复制或用户元素操作是否分配由这些操作决定。
- 用户提供的构造、分配及可调用操作须在所选执行位置有效；Device实例须适用于目标的非抛出环境。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <memory>
#include <asc/std/tuple>

bool example()
{
    asc::std::tuple<int, int> values(2, 3);
    asc::std::tuple<long, long> converted = values;
    ::std::allocator<int> allocator;
    asc::std::tuple<int, int> allocated(asc::std::allocator_arg, allocator, 4, 5);
    return asc::std::get<0>(converted) == 2 && asc::std::get<1>(allocated) == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_tuple.md)
