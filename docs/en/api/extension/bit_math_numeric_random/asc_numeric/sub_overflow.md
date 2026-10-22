# asc::sub_overflow

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

Header: `<asc/numeric>`.

`asc::sub_overflow` computes integer subtraction and reports whether the result is outside the range of the target type.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <class T>
constexpr asc::overflow_result<T> sub_overflow(T left, T right) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <class T>
constexpr bool sub_overflow(T left, T right, T& result) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Standard integer type participating in the checked subtraction (not bool, no more than 64 bits). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand of the overflow-checked integer subtraction.
| `right` | Input | Right operand of the overflow-checked integer subtraction.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Standard integer type participating in the checked subtraction (not bool, no more than 64 bits). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand of the overflow-checked integer subtraction.
| `right` | Input | Right operand of the overflow-checked integer subtraction.
| `result` | Output | Reference to which the operation result is written; a return value of true indicates that an overflow occurred. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::overflow_result<T>` | Returns the computed result of the integer subtraction and reports whether the result is outside the range of the target type. |
| Prototype 2 | `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- When `overflow == true`, the value of integer addition, subtraction, and multiplication stores the result converted to the target bit width; division by zero stores 0, and a signed minimum value divided by -1 stores that minimum value. `overflow_cast` stores the converted value; it must not be treated as an exact mathematical result while ignoring the flag.

- Can be called in Host, AI Core SIMD, and AI Core SIMT; the result is returned according to the integer type declared on this page.
- `T` must be a standard non-bool integer of no more than 64 bits; arithmetic is handled according to the corresponding checked or saturating rules.

## Example

The following snippet demonstrates the interface call with concrete integer arguments.

```cpp
#include <asc/numeric>

decltype(auto) example()
{
    return asc::sub_overflow(2, 8);
}
```

## Related APIs

- [API list for this header](asc_numeric.md)
