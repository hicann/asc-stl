# asc::std::stable_sort

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

`asc::std::stable_sort` sorts the range while preserving the original relative order of equivalent elements; it executes sequentially within the execution entity where the caller resides.

Availability of this interface: Host, AI Core SIMD programming.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class RandomAccessIterator, class Compare>
constexpr void stable_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class RandomAccessIterator>
constexpr void stable_sort(RandomAccessIterator first, RandomAccessIterator last);
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

- Non-allocating, non-recursive random-access pointer cores of stable_sort/stable_partition/inplace_merge.
- Host + ordinary AI Core.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer of sufficient capacity.

```cpp
#include <asc/std/algorithm>

bool example()
{
    struct record { int key; int order; };
    record values[] = {{2, 0}, {1, 1}, {2, 2}, {1, 3}};
    asc::std::stable_sort(values, values + 4, [](const record& a, const record& b) { return a.key < b.key; });
    const int expected_order[] = {1, 3, 0, 2};
    for (int index = 0; index < 4; ++index) {
        if (values[index].key != (index < 2 ? 1 : 2) || values[index].order != expected_order[index]) return false;
    }
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
