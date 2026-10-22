# asc::std::mismatch

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

`asc::std::mismatch` returns the positions of the first pair of unequal elements in two ranges; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
[[nodiscard]] constexpr pair<InputIterator1, InputIterator2> mismatch(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate predicate);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
[[nodiscard]] constexpr pair<InputIterator1, InputIterator2> mismatch(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 3

```cpp
namespace asc::std {
template <class InputIterator1, class InputIterator2>
[[nodiscard]] constexpr pair<InputIterator1, InputIterator2> mismatch(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

### Prototype 4

```cpp
namespace asc::std {
template <class InputIterator1, class InputIterator2>
[[nodiscard]] constexpr pair<InputIterator1, InputIterator2> mismatch(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2);
}  // namespace asc::std
```

This prototype applies to `C++17+` and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `BinaryPredicate` | Callable object type that determines whether the elements satisfy the condition. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | Iterator or pointer to the start of the input range. |
| `last1` | Input | End position of the input range, not included. |
| `first2` | Input | Iterator or pointer to the start of the input range. |
| `predicate` | Input | Callable object used to determine whether the elements satisfy the condition. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `BinaryPredicate` | Callable object type that determines whether the elements satisfy the condition. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | Iterator or pointer to the start of the input range. |
| `last1` | Input | End position of the input range, not included. |
| `first2` | Input | Iterator or pointer to the start of the input range. |
| `last2` | Input | End position of the input range, not included. |
| `pred` | Input | Callable object used to determine whether the elements satisfy the condition. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | Iterator or pointer to the start of the input range. |
| `last1` | Input | End position of the input range, not included. |
| `first2` | Input | Iterator or pointer to the start of the input range. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator1` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |
| `InputIterator2` | Iterator type used to read the elements of the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first1` | Input | Iterator or pointer to the start of the input range. |
| `last1` | Input | End position of the input range, not included. |
| `first2` | Input | Iterator or pointer to the start of the input range. |
| `last2` | Input | End position of the input range, not included. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `pair<InputIterator1, InputIterator2>` | Returns the positions of the first pair of unequal elements in the two ranges. |
| Prototype 2 | `pair<InputIterator1, InputIterator2>` | Returns the positions of the first pair of unequal elements in the two ranges. |
| Prototype 3 | `pair<InputIterator1, InputIterator2>` | Returns the positions of the first pair of unequal elements in the two ranges. |
| Prototype 4 | `pair<InputIterator1, InputIterator2>` | Returns the positions of the first pair of unequal elements in the two ranges. |

## Constraints

- For the overloads that do not take `last2`, there must be at least `last1 - first1` valid readable elements starting from `first2`; both ranges must remain valid during the comparison.

- Uses C++17.
- Supports the iterator, sentinel, and callable object overloads listed in the current version.
- The standard execution policy overloads execute sequentially.

## Example

The following Host example checks the result and output while the local range is still valid; the function returns a boolean value that can be evaluated independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int other[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto result = asc::std::mismatch(values, values + 8, other);
    return result.first == values + 8 && result.second == other + 8;
}
```

## Related APIs

- [`asc::parallel::mismatch`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_mismatch.md): Submits an asynchronous device operation using an execution policy.
