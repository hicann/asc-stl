# asc::std::pop_heap

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

`asc::std::pop_heap` moves the top element of the heap to the end of the range and restores the heap property of the front portion; it executes sequentially within the execution entity where the caller resides.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class RandomAccessIterator, class Compare>
constexpr void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class RandomAccessIterator>
constexpr void pop_heap(RandomAccessIterator first, RandomAccessIterator last);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RandomAccessIterator` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `Compare` | Type of the comparison object that defines the order of elements. |

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

- The input must be a non-empty heap, i.e. `first != last`; the comparator must be consistent with the order used when the heap was built.

- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer of sufficient capacity.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {8, 3, 6, 1, 7, 2, 5, 4};
    asc::std::make_heap(values, values + 8);
    asc::std::pop_heap(values, values + 8);
    if (values[7] != 8) return false;
    for (int index = 1; index < 7; ++index) { if (values[(index - 1) / 2] < values[index]) return false; }
    int counts[9] = {};
    for (int value : values) { if (value < 1 || value > 8) return false; ++counts[value]; }
    for (int value = 1; value <= 8; ++value) { if (counts[value] != 1) return false; }
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
