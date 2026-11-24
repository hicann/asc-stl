# asc::div_overflow

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

`asc::div_overflow` computes integer division and reports division by zero or an out-of-range result.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <class T>
constexpr asc::overflow_result<T> div_overflow(T left, T right) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <class T>
constexpr bool div_overflow(T left, T right, T& result) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Standard integer type participating in the checked division (not bool, no more than 64 bits). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand of the integer division checked for division by zero or out-of-range results. |
| `right` | Input | Right operand of the integer division checked for division by zero or out-of-range results; when it is 0, the returned value is 0 and overflow is true. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Standard integer type participating in the checked division (not bool, no more than 64 bits). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand of the integer division checked for division by zero or out-of-range results. |
| `right` | Input | Right operand of the integer division checked for division by zero or out-of-range results; when it is 0, the returned value is 0 and overflow is true. |
| `result` | Output | Reference to which the division result is written; a return value of true indicates division by zero or an out-of-range result. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::overflow_result<T>` | Returns the computed result of the integer division and reports division by zero or an out-of-range result. |
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
    return asc::div_overflow(8, 2);
}

bool verify_example()
{
    const auto actual = example();
    return actual.value == 4 && actual.overflow == false;
}
```

## Related APIs

- [API list for this header](asc_numeric.md)
