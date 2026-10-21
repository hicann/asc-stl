# asc::std::unexpected::unexpected

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

`asc::std::unexpected::unexpected`按本页所列构造形态初始化`unexpected`对象。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

以下为所属类内的**调用形态摘要**。省略实现使用的SFINAE选择参数；同形的隐式与explicit形式分别受下面的可构造性、可转换性条件选择，不能将摘要复制为一组无条件重载定义。

```cpp
unexpected(const unexpected&) = default;
```

```cpp
unexpected(unexpected&&) = default;
```

```cpp
constexpr explicit unexpected(const Error& error);
```

```cpp
constexpr explicit unexpected(Error&& error) noexcept(is_nothrow_move_constructible_v<Error>);
```

```cpp
template <class Error2 = Error>
constexpr explicit unexpected(Error2&& error) noexcept(is_nothrow_constructible_v<Error, Error2>);
```

```cpp
template <class... Args>
constexpr explicit unexpected(in_place_t, Args&&... args);
```

此形态仅用于Host。

```cpp
template <class U, class... Args>
constexpr explicit unexpected(in_place_t, ::std::initializer_list<U> il, Args&&... args) noexcept(
        is_nothrow_constructible_v<Error, ::std::initializer_list<U>&, Args...>);
```

此形态仅用于Host。

## 参数说明

**模板参数**

Error是所属unexpected的错误类型；Error2是转发错误值的来源类型，U是Host初始化列表的元素类型，Args...为原位构造实参类型。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `error` | 输入/输出（可移动来源） | 用于构造保存错误对象的来源。 |
| `args...` | 输入/输出 | 仅Host通用in_place形态转发给Error的实参。 |
| `il` | 输入 | 仅Host使用的初始化列表，在构造完成前保持有效。 |

## 返回值说明

无返回值。

## 约束说明

- Error须为无cv限定的非数组对象类型，且不能是unexpected特化；转发构造排除in_place标记及unexpected本身。错误值与原位构造均为explicit；initializer_list及通用in_place构造仅用于Host。
- 用户提供的构造、分配及可调用操作须在所选执行位置有效；Device实例须适用于目标的非抛出环境。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::unexpected<int> error(7);
    asc::std::unexpected<int> placed(asc::std::in_place, 9);
    return error.error() == 7 && placed.error() == 9;
}
```

## 关联API

- [本头文件的接口列表](asc_std_expected.md)
