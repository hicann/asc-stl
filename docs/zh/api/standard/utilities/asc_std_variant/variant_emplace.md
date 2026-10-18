# asc::std::variant::emplace

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

`asc::std::variant::emplace`在指定位置直接构造元素。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

所属类型：[`asc::std::variant<Types...>`](variant.md)。以下为类内声明；未命名约束形参和默认索引用于选择重载，调用方无需指定。

### 按索引构造

```cpp
template <size_t Index, class... Args>
constexpr variant_alternative_t<Index, variant>& emplace(Args&&... args);
```

### 按类型构造

```cpp
template <class T, class... Args, size_t Index = __variant_index_v<T, Types...>,
    enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1, int> = 0>
constexpr T& emplace(Args&&... args);
```

### Host按索引使用初始化列表

```cpp
template <size_t Index, class Up, class... Args,
    enable_if_t<(Index < sizeof...(Types)) &&
            is_constructible_v<variant_alternative_t<Index, variant>, ::std::initializer_list<Up>&, Args...>,
        int> = 0>
constexpr variant_alternative_t<Index, variant>& emplace(
    ::std::initializer_list<Up> list, Args&&... args);
```

### Host按类型使用初始化列表

```cpp
template <class T, class Up, class... Args, size_t Index = __variant_index_v<T, Types...>,
    enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1 &&
            is_constructible_v<T, ::std::initializer_list<Up>&, Args...>,
        int> = 0>
constexpr T& emplace(::std::initializer_list<Up> list, Args&&... args);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Types` | 所属`variant`的备选类型列表，不得包含数组、引用或`void`。 |
| `T` | 按类型原位构造时选择的备选类型，须恰好出现一次。 |
| `Index` | 按索引构造时的备选位置，从0起且小于备选类型数量；按类型或值选择的形式由实现推导。 |
| `Args` | 转发给所选备选类型构造函数的参数类型。 |
| `Up` | Host初始化列表的元素类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `args` | 输入（可能被移动） | 转发给所选类型构造函数的实参。 |
| `list` | 输入 | 仅Host形式提供的初始化列表；与其余实参一起用于构造。 |

## 返回值说明

返回新构造的备选对象引用；按类型形式为`T&`，按索引形式为`variant_alternative_t<Index, variant>&`。引用有效期截至该备选对象被替换、销毁或所属`variant`被销毁；不要返回对局部`variant`元素的引用。

## 约束说明

- 对象一次保存一个活动备选值，读取前须通过`index()`确认所选备选项。
- Device使用的备选类型及构造、赋值、析构和交换操作须在对应编程模式可用且不抛出异常。
- 按索引形式要求索引在范围内；按类型形式要求该类型在备选列表中恰好出现一次。所选类型必须能由给定实参构造。
- 带`::std::initializer_list`的重载仅可在Host调用。

## 调用示例

以下Host示例使用具体对象，并检查调用结果。

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> value(7);
    auto& result = value.emplace<float>(2.5F);
    return value.index() == 1 && &result == &asc::std::get<1>(value) && result == 2.5F;
}
```

## 关联API

- [`asc::std::variant`](variant.md)
- [本头文件的接口列表](asc_std_variant.md)
