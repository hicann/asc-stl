# asc::std::replace

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

`asc::std::replace` replaces the elements in the range that are equal to the old value with the new value; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class T>
constexpr void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the old value and the new value; the old value must be comparable with elements of the range via `operator==`, and the new value must be assignable to the elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `old_value` | Input | Old value to be replaced, compared with elements of the range by equality semantics (`operator==`). |
| `new_value` | Input | New value after replacement, assigned to elements equal to old_value. |

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
    asc::std::replace(values, values + 8, 3, 9);
    const int expected[8] = {8, 9, 6, 1, 7, 2, 5, 4};
    for (int index = 0; index < 8; ++index) { if (values[index] != expected[index]) return false; }
    return true;
}
```

## Related APIs

- [`asc::parallel::replace`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_replace.md): Submits an asynchronous device operation using an execution policy.
