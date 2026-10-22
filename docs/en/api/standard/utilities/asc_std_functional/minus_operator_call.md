# asc::std::minus::`operator()`

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

`asc::std::minus::operator()` performs the corresponding arithmetic operation on the operands as denoted by the function object name.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

Member of: [`asc::std::minus`](minus.md).

### Prototype 1: specified-type form

```cpp
// Declaration inside minus<T> (T is not void); T is provided by the enclosing class.
[[nodiscard]] constexpr T operator()(const T& x, const T& y) const;
```

### Prototype 2: transparent specialization

```cpp
// Declaration inside minus<void>; the template arguments are deduced from the call.
template <class T1, class T2>
[[nodiscard]] constexpr auto operator()(T1&& x, T2&& y) const noexcept(noexcept(::asc::std::forward<T1>(x) - ::asc::std::forward<T2>(y))) -> decltype(::asc::std::forward<T1>(x) - ::asc::std::forward<T2>(y));
```

## Parameters

### Parameters of Prototype 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Left operand of the current operation, read through a const reference. |
| `y` | Input | Right operand of the current operation, read through a const reference. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | Deduced type of the left operand; the forwarding reference preserves the cv-qualification and value category of the input. |
| `T2` | Deduced type of the right operand; the forwarding reference preserves the cv-qualification and value category of the input. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Left operand; forwarded to the operation expression with its original value category. |
| `y` | Input | Right operand; forwarded to the operation expression with its original value category. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | Returns the result of `x - y` computed with the specified type. |
| Prototype 2 | The expression type specified by the prototype's trailing return type | Returns the result of the same operation expression after forwarding; the type is determined by `decltype` in the prototype. |

## Constraints

- The operands must support the operation expression in the prototype, and the result of Prototype 1 must also be convertible to its return type.
- The transparent form allows the two sides to have different types; this form is available only when the operation expression is valid.
- For built-in signed integers, the operation result must be representable; the function object does not additionally detect arithmetic overflow.
- The `noexcept` of the transparent form matches the corresponding operation expression; the current specified-type form does not declare `noexcept`. A call on the device side further requires the corresponding operation to be usable at that execution location.

## Example

The following Host example checks the concrete results of the specified-type and transparent forms respectively.

```cpp
#include <asc/std/functional>

static_assert(asc::std::minus<int>{}(4, 2) == (2));
static_assert(asc::std::minus<>{}(4L, 2) == (2));
```

## Related APIs

- [`asc::std::minus`](minus.md)
- [API list for this header](asc_std_functional.md)
