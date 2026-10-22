# asc::std::move

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

Headers: `<asc/std/algorithm>`, `<asc/std/utility>`.

The one-argument form of `asc::std::move` converts an object to an rvalue reference preserving the original type qualification; the three-argument form moves the elements of the input range to the output range in order.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr asc::std::remove_reference_t<T>&& move(T&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header `<asc/std/utility>`.

### Prototype 2

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator> constexpr OutputIterator move(InputIterator first, InputIterator last, OutputIterator result);
} // namespace asc::std
```

This prototype corresponds to the header `<asc/std/algorithm>`.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the object on which the value category conversion is performed. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The object to be converted to an rvalue reference; the returned reference does not extend the object's lifetime. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | Iterator type used to read the elements of the input range. |
| `OutputIterator` | Iterator type used to write the destination range. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator to the start of the input range. |
| `last` | Input | Iterator to the end of the input range, not included. |
| `result` | Output | Iterator to the start of the output range; the destination storage must have sufficient capacity. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::std::remove_reference_t<T>&&` | Returns an rvalue reference to the same object; this reference does not extend the lifetime of the original object. |
| Prototype 2 | `OutputIterator` | Returns the position just after the last written element in the output range. |

## Constraints

- The one-argument form performs only a value category conversion; the returned reference does not extend the lifetime of the original object.
- The three-argument form requires [first, last) to be a valid range and the output range to have sufficient capacity, and the source and destination must not overlap in a way that violates the standard preconditions.

## Example

The following Host snippet separately checks the observable results of the rvalue reference conversion and the range move.

```cpp
#include <asc/std/algorithm>

#include <asc/std/utility>

bool example()
{
    int value = 3;
    int&& reference = asc::std::move(value);
    reference = 4;

    int input[] = {1, 2, 3};
    int output[3] = {};
    const auto end = asc::std::move(input, input + 3, output);
    return value == 4 && end == output + 3 && output[2] == 3;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
