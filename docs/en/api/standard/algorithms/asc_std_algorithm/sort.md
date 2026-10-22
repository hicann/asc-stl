# asc::std::sort

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

`asc::std::sort` sorts a random-access range according to the comparison relation; it executes sequentially within the execution entity where the caller resides.

Synchronous/parallel relationship of the applicable overloads: the policy-based prototype is invoked on the Host and executes in parallel through the corresponding [asc::parallel::sort](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_sort.md) front end, synchronously waiting for that Stream to complete; the policy-free prototype executes sequentially and involves no device submission. The execution policy parameter [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md) of the policy-based prototype must be bound to a valid Stream and sufficient caller-provided temporary storage. Because the standard form has no error return channel, [`asc::std::terminate`](../../language_support/asc_std_exception/terminate.md) is called when parameter validation, submission, or synchronization fails.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class RandomAccessIterator, class Com>
constexpr void sort(RandomAccessIterator first, RandomAccessIterator last, Com compare);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template <class RandomAccessIterator>
constexpr void sort(RandomAccessIterator first, RandomAccessIterator last);
}  // namespace asc::std
```

This prototype applies to `C++17+`; availability: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RandomAccessIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Com` | Element comparator type; returning true means the first operand is ordered before the second operand, and it must satisfy strict weak ordering. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |
| `compare` | Input | Comparison object used to determine the order of elements. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RandomAccessIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, exclusive. |

## Return Value

No return value.

## Constraints

- Uses C++17.
- Sequential random-access pointer, default comparison, and custom comparison cores of sort/nth_element.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer of sufficient capacity.

```cpp
#include <asc/std/algorithm>

void example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    asc::std::sort(values, values + 8);
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
