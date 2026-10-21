# asc::std::expected::expected

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

头文件路径为：`<asc/std/expected>`。

`asc::std::expected::expected`按本页所列构造形态初始化`expected`对象。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

以下为所属类内的**调用形态摘要**。省略实现使用的SFINAE选择参数；同形的隐式与explicit形式分别受下面的可构造性、可转换性条件选择，不能将摘要复制为一组无条件重载定义。

```cpp
template <class Value2 = Value>
constexpr expected() noexcept(is_nothrow_default_constructible_v<Value2>);
```

```cpp
constexpr expected(const Value& value);
```

```cpp
constexpr expected(const unexpected<Error>& error);
```

```cpp
constexpr expected(unexpect_t, const Error& error);
```

```cpp
constexpr expected(const expected& other);
```

```cpp
expected(expected&&) = default;
```

该形态的constexpr限定仅在C++20加入。

```cpp
~expected() = default;
```

```cpp
template <class Up, class OtherErr>
expected(const expected<Up, OtherErr>& other) noexcept(
        is_nothrow_constructible_v<Value, const Up&> && is_nothrow_constructible_v<Error, const OtherErr&>);
```

该形态的constexpr限定仅在C++20加入。

```cpp
template <class Up, class OtherErr>
explicit expected(
        const expected<Up, OtherErr>& other) noexcept(is_nothrow_constructible_v<Value, const Up&> &&
        is_nothrow_constructible_v<Error, const OtherErr&>);
```

该形态的constexpr限定仅在C++20加入。

```cpp
template <class Up, class OtherErr>
expected(expected<Up, OtherErr>&& other) noexcept(
        is_nothrow_constructible_v<Value, Up> && is_nothrow_constructible_v<Error, OtherErr>);
```

该形态的constexpr限定仅在C++20加入。

```cpp
template <class Up, class OtherErr>
explicit expected(expected<Up, OtherErr>&& other) noexcept(
        is_nothrow_constructible_v<Value, Up> && is_nothrow_constructible_v<Error, OtherErr>);
```

该形态的constexpr限定仅在C++20加入。

```cpp
template <class Up = Value>
constexpr expected(Up&& value) noexcept(is_nothrow_constructible_v<Value, Up>);
```

```cpp
template <class Up = Value>
constexpr explicit expected(Up&& value) noexcept(is_nothrow_constructible_v<Value, Up>);
```

```cpp
template <class OtherErr>
constexpr expected(const unexpected<OtherErr>& error) noexcept(
        is_nothrow_constructible_v<Error, const OtherErr&>);
```

```cpp
template <class OtherErr>
constexpr explicit expected(const unexpected<OtherErr>& error) noexcept(
        is_nothrow_constructible_v<Error, const OtherErr&>);
```

```cpp
template <class OtherErr>
constexpr expected(unexpected<OtherErr>&& error) noexcept(
        is_nothrow_constructible_v<Error, OtherErr>);
```

```cpp
template <class OtherErr>
constexpr explicit expected(unexpected<OtherErr>&& error) noexcept(
        is_nothrow_constructible_v<Error, OtherErr>);
```

```cpp
template <class... Args>
constexpr explicit expected(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<Value, Args...>);
```

```cpp
template <class Up, class... Args>
constexpr explicit expected(in_place_t, ::std::initializer_list<Up> list, Args&&... args) noexcept(
        is_nothrow_constructible_v<Value, ::std::initializer_list<Up>&, Args...>);
```

此形态仅用于Host。

```cpp
template <class... Args>
constexpr explicit expected(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<Error, Args...>);
```

```cpp
template <class Up, class... Args>
constexpr explicit expected(unexpect_t, ::std::initializer_list<Up> list, Args&&... args) noexcept(
        is_nothrow_constructible_v<Error, ::std::initializer_list<Up>&, Args...>);
```

此形态仅用于Host。

## 参数说明

**模板参数**

Value和Error是所属expected的值/错误类型；默认构造的Value2默认等于Value。Up和OtherErr表示转换来源成分类型，Args...表示原位构造实参类型。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出（可移动来源） | 成功值的构造来源。 |
| `error` | 输入/输出（可移动来源） | unexpected或错误原位构造的来源。 |
| `other` | 输入/输出（可移动来源） | 来源expected；按其当前活动状态构造对应值或错误。 |
| `args...` | 输入/输出 | 转发给Value或Error的原位构造实参。 |
| `list` | 输入 | 仅Host的初始化列表形态使用，元素在构造完成前有效。 |

## 返回值说明

无返回值。

## 约束说明

- Value为非void值类型，Error为有效错误对象类型。默认构造要求Value可默认构造；值、unexpected和原位形式分别要求对应成分可构造。跨expected转换要求值和错误两侧均可构造，并排除可直接从整个expected转换的冲突形态；两侧都可隐式转换时不带explicit，否则显式。移动特殊成员的可用性随Value和Error的移动能力决定。
- 用户提供的构造、分配及可调用操作须在所选执行位置有效；Device实例须适用于目标的非抛出环境。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::expected<int, int> zero;
    asc::std::expected<int, int> value(asc::std::in_place, 7);
    asc::std::expected<int, int> error(asc::std::unexpect, 5);
    return zero && *zero == 0 && value && *value == 7 && !error && error.error() == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_expected.md)
