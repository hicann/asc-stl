# asc::std::tuple_size

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

头文件路径为：`<asc/std/array>`、`<asc/std/tuple>`、`<asc/std/utility>`、`<asc/std/complex>`、`<asc/std/ranges>`；须按目标对象类型包含对应头文件。

`asc::std::tuple_size<T>`在编译期取得受支持类tuple类型的元素数量，通过静态成员`value`提供结果。主模板只作声明，具体类型由偏特化支持。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 声明

### 主模板

```cpp
namespace asc::std {
template<class T> struct tuple_size;
} // namespace asc::std
```

### cv限定类型的偏特化

以下是公开匹配形式的声明摘要。实际实现仅在未加cv限定的`tuple_size<T>`完整且具有`value`时提供对应结果，省略内部条件分派名称。

```cpp
namespace asc::std {
template<class T> struct tuple_size<const T>;
template<class T> struct tuple_size<volatile T>;
template<class T> struct tuple_size<const volatile T>;
} // namespace asc::std
```

这些偏特化保持未加cv限定类型的元素数量，不去除引用限定。

### array的偏特化

须包含`<asc/std/array>`；`value`等于`Size`。

```cpp
namespace asc::std {
template<class T, size_t Size> struct tuple_size<array<T, Size>>;
} // namespace asc::std
```

### tuple的偏特化

须包含`<asc/std/tuple>`；`value`等于`sizeof...(Types)`。

```cpp
namespace asc::std {
template<class... Types> struct tuple_size<tuple<Types...>>;
} // namespace asc::std
```

### pair的偏特化

须包含`<asc/std/utility>`；`value`等于2。

```cpp
namespace asc::std {
template<class T1, class T2> struct tuple_size<pair<T1, T2>>;
} // namespace asc::std
```

### integer_sequence的偏特化

须包含`<asc/std/utility>`；`value`等于`sizeof...(Values)`。

```cpp
namespace asc::std {
template<class T, T... Values> struct tuple_size<integer_sequence<T, Values...>>;
} // namespace asc::std
```

### complex的偏特化

须包含`<asc/std/complex>`；`value`等于2。该特征不扩大`complex`对象本身支持的成分类型范围。

```cpp
namespace asc::std {
template<class T> struct tuple_size<complex<T>>;
} // namespace asc::std
```

### subrange的偏特化

须包含`<asc/std/ranges>`；`value`等于2，分别对应起始迭代器和终止哨兵。

```cpp
namespace asc::std {
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_size<ranges::subrange<Iter, Sent, Kind>>;
} // namespace asc::std
```

## 约束说明

- `T`须是具有相应`tuple_size`偏特化的类型；主模板本身不提供`value`。
- `array<T, 0>`、空`tuple<>`和空`integer_sequence`的元素数量为0；它们没有可访问的第0个元素。
- cv限定类型沿用对应未限定类型的数量；引用类型不会自动转为其所引用类型。
- 应包含对应对象类型的公开头文件；不能仅因本页位于array目录就假定`<asc/std/array>`提供所有其他对象类型。
- 本特征只在编译期提供元素数量，不执行对象构造、元素访问、内存分配或比较。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/array>

bool example()
{
    static_assert(asc::std::tuple_size<asc::std::array<int, 3>>::value == 3);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_array.md)
