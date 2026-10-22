# asc::std::bit_or::`operator()`

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Header: `<asc/std/functional>`.

`asc::std::bit_or::operator()` performs the corresponding bitwise operation on the input integer values.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

Member of: [`asc::std::bit_or`](bit_or.md).

### Prototype 1: Typed form

```cpp
// Declared inside bit_or<T> (T is not void); T is provided by the enclosing class.
constexpr T operator()(const T& x, const T& y) const;
```

### Prototype 2: Transparent specialization

```cpp
// Declared inside bit_or<void>; the template arguments are deduced at the call.
template <class T1, class T2>
[[nodiscard]] constexpr auto operator()(T1&& x, T2&& y) const noexcept(noexcept(::asc::std::forward<T1>(x) | ::asc::std::forward<T2>(y))) -> decltype(::asc::std::forward<T1>(x) | ::asc::std::forward<T2>(y));
```

## Parameters

### Parameters of Prototype 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | The left operand of the current operation, read through a const reference. |
| `y` | Input | The right operand of the current operation, read through a const reference. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The deduced type of the left operand; the forwarding reference preserves the cv-qualification and value category of the input. |
| `T2` | The deduced type of the right operand; the forwarding reference preserves the cv-qualification and value category of the input. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | The left operand; forwarded to the operation expression with its original value category. |
| `y` | Input | The right operand; forwarded to the operation expression with its original value category. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | Returns the result of evaluating `x \| y` with the specified type. |
| Prototype 2 | The expression type specified by the prototype's trailing return type | Returns the result of the same operation expression after forwarding; the type is determined by the `decltype` in the prototype. |

## Constraints

- The operands must support the operation expression in the prototype, and the result of Prototype 1 must also be convertible to its return type.
- The transparent form allows the two sides to have different types; this form is available only when the operation expression is valid.
- The `noexcept` of the transparent form matches the corresponding operation expression; the typed form currently declares no `noexcept`. Calls on the device side additionally require the corresponding operation to be usable at that execution location.

## Example

The following Host example checks the concrete results of the typed form and the transparent form separately.

```cpp
#include <asc/std/functional>

static_assert(asc::std::bit_or<int>{}(4, 2) == (6));
static_assert(asc::std::bit_or<>{}(4L, 2) == (6));
```

## Related APIs

- [`asc::std::bit_or`](bit_or.md)
- [API list for this header](asc_std_functional.md)
