# asc::std::negate::`operator()`

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

`asc::std::negate::operator()` processes the current object and the operands according to the operator rules available for `negate`.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

Member of: [`asc::std::negate`](negate.md).

### Prototype 1: specified-type form

```cpp
// Declaration inside negate<T> (T is not void); T is provided by the enclosing class.
constexpr T operator()(const T& x) const;
```

### Prototype 2: transparent specialization

```cpp
// Declaration inside negate<void>; the template arguments are deduced from the call.
template <class T1>
constexpr auto operator()(T1&& x) const noexcept(noexcept(-::asc::std::forward<T1>(x))) -> decltype(-::asc::std::forward<T1>(x));
```

## Parameters

### Parameters of Prototype 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | The sole operand of the current operation, read through a const reference. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | Deduced type of the operand; the forwarding reference preserves the cv-qualification and value category of the input. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | The sole operand; forwarded to the operation expression with its original value category. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | Returns the result of `-x` computed with the specified type. |
| Prototype 2 | The expression type specified by the prototype's trailing return type | Returns the result of the same operation expression after forwarding; the type is determined by `decltype` in the prototype. |

## Constraints

- The operand must support the unary operation expression in the prototype, and the result of Prototype 1 must also be convertible to its return type.
- The transparent form preserves the value category of the input; this form is available only when the operation expression is valid.
- For built-in signed integers, the operation result must be representable; the function object does not additionally detect arithmetic overflow.
- The `noexcept` of the transparent form matches the corresponding operation expression; the current specified-type form does not declare `noexcept`. A call on the device side further requires the corresponding operation to be usable at that execution location.

## Example

The following Host example checks the concrete results of the specified-type and transparent forms respectively.

```cpp
#include <asc/std/functional>

static_assert(asc::std::negate<int>{}(4) == (-4));
static_assert(asc::std::negate<>{}(4L) == (-4));
```

## Related APIs

- [`asc::std::negate`](negate.md)
- [API list for this header](asc_std_functional.md)
