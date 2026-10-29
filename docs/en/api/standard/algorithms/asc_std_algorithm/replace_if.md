# asc::std::replace_if

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

Header: `<asc/std/algorithm>`.

`asc::std::replace_if` replaces the elements satisfying the predicate with the new value; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class Predicate, class T>
constexpr void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Predicate` | Type of the callable object that determines whether an element satisfies the condition. |
| `T` | Type of the new value after replacement; must be assignable to elements of the range. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `pred` | Input | Unary predicate invoked in the form `pred(elem)` returning bool; elements for which it returns true are replaced with new_value. |
| `new_value` | Input | New value after replacement, assigned to elements satisfying the predicate. |

## Return Value

No return value.

## Constraints

- Uses C++17.
- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer of sufficient capacity.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {8, 3, 6, 1, 7, 2, 5, 4};
    asc::std::replace_if(values, values + 8, [](int value) { return value % 2 == 0; }, 9);
    const int expected[8] = {9, 3, 9, 1, 7, 9, 5, 9};
    for (int index = 0; index < 8; ++index) { if (values[index] != expected[index]) return false; }
    return true;
}
```

## Related APIs

- [`asc::parallel::replace_if`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_replace_if.md): Submits an asynchronous device operation using an execution policy.
