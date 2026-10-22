# asc::std::pair::swap

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

Header: `<asc/std/utility>`.

`asc::std::pair::swap` swaps the held states or elements of two objects.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

Member of: [`asc::std::pair`](pair.md).

```cpp
// Excerpt of the declaration inside class asc::std::pair; template parameters and other members are provided by the owning class.
constexpr void swap(pair<T1, T2>& other) noexcept(is_nothrow_swappable_v<T1>&& is_nothrow_swappable_v<T2>);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The other object whose state is swapped with the current object; after the swap each holds the other's original state. |

## Return Value

No return value.

## Constraints

- The exception specification follows the corresponding declaration; element operations used on the device side must not throw.
- The direct free comparison entries for pair are `operator==` and `operator<`; the other relational helpers are in `rel_ops`.

## Example

The following Host snippet demonstrates the call with concrete types; input ranges and objects must remain valid during use.

```cpp
#include <asc/std/utility>

void example()
{
    asc::std::pair<int, int> left(1, 2), right(3, 4);
    left.swap(right);
}
```

## Related APIs

- [`asc::std::pair`](pair.md)
- [API list for this header](asc_std_utility.md)
