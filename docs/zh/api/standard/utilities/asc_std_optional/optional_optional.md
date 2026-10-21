# asc::std::optional::optional

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

`asc::std::optional::optional`按本页所列构造形态初始化`optional`对象。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

以下为所属类内的**调用形态摘要**。省略实现使用的SFINAE选择参数；同形的隐式与explicit形式分别受下面的可构造性、可转换性条件选择，不能将摘要复制为一组无条件重载定义。

```cpp
constexpr optional() noexcept = default;
```

```cpp
constexpr optional(nullopt_t) noexcept;
```

```cpp
constexpr optional(const optional& other);
```

```cpp
constexpr optional(optional&& other) noexcept(is_nothrow_move_constructible_v<T>);
```

```cpp
template <class U>
constexpr optional(const optional<U>& other);
```

```cpp
template <class U>
constexpr explicit optional(const optional<U>& other);
```

```cpp
template <class U>
constexpr optional(optional<U>&& other);
```

```cpp
template <class U>
constexpr explicit optional(optional<U>&& other);
```

```cpp
template <class U = T>
constexpr optional(U&& value);
```

```cpp
template <class U = T>
constexpr explicit optional(U&& value);
```

```cpp
template <class... Args>
constexpr explicit optional(in_place_t, Args&&... args);
```

```cpp
template <class U, class... Args>
constexpr explicit optional(in_place_t, ::std::initializer_list<U> list, Args&&... args);
```

此形态仅用于Host。

## 参数说明

**模板参数**

T是所属optional的值类型；U是值或来源optional的元素类型，Args...是原位构造实参类型。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出（转发形式） | 用来构造T的来源值。 |
| `other` | 输入/输出（可移动来源） | 来源optional；空状态保持为空，有值时复制或移动其值。 |
| `args...` | 输入/输出 | 转发给T原位构造的实参。 |
| `list` | 输入 | 仅Host使用的初始化列表，元素在构造完成前有效。 |

## 返回值说明

无返回值。

## 约束说明

- T须为有效对象类型；值构造和异类型optional转换须能构造T，且排除in_place标记和与optional自身转换冲突的形态。来源可隐式转换为T时采用隐式构造，否则采用explicit构造。空来源保持空状态；复制或移动形式要求相应的元素构造有效。
- 用户提供的构造、分配及可调用操作须在所选执行位置有效；Device实例须适用于目标的非抛出环境。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> empty;
    asc::std::optional<int> value = 7;
    asc::std::optional<int> placed(asc::std::in_place, 9);
    return !empty && value && *value == 7 && placed && *placed == 9;
}
```

## 关联API

- [`asc::std::optional`](optional.md)
- [本头文件的接口列表](asc_std_optional.md)
