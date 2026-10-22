# asc::std::advance

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

Header: `<asc/std/iterator>`.

`asc::std::advance` advances the iterator by the given distance.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

```cpp
namespace asc::std {
template<class InputIter, class Distance>
constexpr void advance(InputIter& __i, Distance __orig_n);
} // namespace asc::std
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `__i` | Input/Output | The iterator to be advanced, of type `InputIter`. |
| `__orig_n` | Input | The number of element steps, of type `Distance`, used after conversion to the iterator's `difference_type`; a negative value requires support for bidirectional movement. |

## Return Value

No return value.

## Constraints

- The advance path must stay within the valid range allowed for the iterator; iterators that support only forward movement must not use a negative distance.
- Random-access iterators advance by addition; bidirectional iterators increment or decrement according to the sign of the distance; other input iterators increment step by step.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    int* iterator = values;
    asc::std::advance(iterator, 2);
    return iterator == values + 2 && *iterator == 3;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
