# asc::std::tuple_element

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

`asc::std::tuple_element<Index, T>`通过成员类型`type`取得受支持类tuple类型中指定索引处的元素类型。主模板只作声明；各偏特化的有效索引和cv处理如下。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 声明

### 主模板

```cpp
namespace asc::std {
template<size_t Index, class T> struct tuple_element;
} // namespace asc::std
```

### cv限定类型的偏特化

```cpp
namespace asc::std {
template<size_t Index, class T> struct tuple_element<Index, const T>;
template<size_t Index, class T> struct tuple_element<Index, volatile T>;
template<size_t Index, class T> struct tuple_element<Index, const volatile T>;
} // namespace asc::std
```

通常在未限定类型的元素类型上增加相同的cv限定；元素类型本身为引用时遵循C++引用类型的限定规则。下述`const integer_sequence`和`const subrange`另有专门的偏特化。

### array的偏特化

须包含`<asc/std/array>`；`Index < Size`时，`type`为`T`。

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size>
struct tuple_element<Index, array<T, Size>>;
} // namespace asc::std
```

### tuple的偏特化

须包含`<asc/std/tuple>`。非空tuple逐项选择第`Index`个类型；空tuple的偏特化不提供`type`。

```cpp
namespace asc::std {
template<size_t Index, class Head, class... Tail>
struct tuple_element<Index, tuple<Head, Tail...>>;
template<class Head, class... Tail>
struct tuple_element<0, tuple<Head, Tail...>>;
template<size_t Index> struct tuple_element<Index, tuple<>>;
} // namespace asc::std
```

### pair的偏特化

须包含`<asc/std/utility>`；索引0的`type`为`T1`，索引1的`type`为`T2`。

```cpp
namespace asc::std {
template<class T1, class T2> struct tuple_element<0, pair<T1, T2>>;
template<class T1, class T2> struct tuple_element<1, pair<T1, T2>>;
} // namespace asc::std
```

### integer_sequence的偏特化

须包含`<asc/std/utility>`；`Index < sizeof...(Values)`时，以下两种形式的`type`均为`T`。`const`作用于序列对象，不使该专门偏特化的结果变为`const T`。

```cpp
namespace asc::std {
template<size_t Index, class T, T... Values>
struct tuple_element<Index, integer_sequence<T, Values...>>;
template<size_t Index, class T, T... Values>
struct tuple_element<Index, const integer_sequence<T, Values...>>;
} // namespace asc::std
```

### complex的偏特化

须包含`<asc/std/complex>`；索引0和1分别对应实部与虚部，`type`均为`T`。该特征不扩大`complex`对象本身支持的成分类型范围。

```cpp
namespace asc::std {
template<size_t Index, class T> struct tuple_element<Index, complex<T>>;
} // namespace asc::std
```

### subrange的偏特化

须包含`<asc/std/ranges>`；索引0的`type`为`Iter`，索引1的`type`为`Sent`。`const subrange`的专门偏特化也返回这两个类型，不额外增加`const`。

```cpp
namespace asc::std {
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_element<0, ranges::subrange<Iter, Sent, Kind>>;
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_element<1, ranges::subrange<Iter, Sent, Kind>>;
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_element<0, const ranges::subrange<Iter, Sent, Kind>>;
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_element<1, const ranges::subrange<Iter, Sent, Kind>>;
} // namespace asc::std
```

## 约束说明

- `T`须具有对应的`tuple_element`偏特化；主模板本身不提供`type`，引用类型不会自动转为其所引用类型。
- `Index`从0开始，须小于相应类型的元素数量。空array、空tuple和空`integer_sequence`均没有有效元素索引。
- `type`描述元素类型，不是一次元素访问，也不创建或复制对象；若需访问对象元素，应使用相应的`get`接口。
- cv限定通常传播到元素类型；`const integer_sequence`和`const subrange`按上列专门偏特化处理。
- 应包含各类型对应的公共头文件；各对象类型自身的实例化条件仍需满足，例如当前ASC复数对象只支持`complex<float>`。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/array>
#include <asc/std/type_traits>

bool example()
{
    using Array = asc::std::array<int, 3>;
    static_assert(asc::std::is_same_v<asc::std::tuple_element<1, Array>::type, int>);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_array.md)
