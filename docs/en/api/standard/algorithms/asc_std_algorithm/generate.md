# asc::std::generate

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

`asc::std::generate` invokes the generator on every element in the range and writes the result; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class ForwardIterator, class Generator>
constexpr void generate(ForwardIterator first, ForwardIterator last, Generator gen);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Generator` | Generator type; invoked in the form gen(), and its return value must be assignable to the elements of the range. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator or pointer to the start of the range to write. |
| `last` | Input | End position of the range to write, not included. |
| `gen` | Input | Generator object; gen() is invoked once for every element and its return value is written to that element. |

## Return Value

No return value.

## Constraints

- Uses C++17.
- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer with sufficient capacity.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {8, 3, 6, 1, 7, 2, 5, 4};
    int next = 0;
    asc::std::generate(values, values + 8, [&next] { return ++next; });
    for (int index = 0; index < 8; ++index) { if (values[index] != index + 1) return false; }
    return next == 8;
}
```

## Related APIs

- [`asc::parallel::generate`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_generate.md): Submits an asynchronous device operation using an execution policy.
