# asc::std::optional::swap

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

Header: `<asc/std/optional>`.

`asc::std::optional::swap` swaps the held states or elements of two objects.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

Member of: [`asc::std::optional`](optional.md).

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
constexpr void swap(asc::std::optional& other) noexcept(is_nothrow_move_constructible_v<T>&& is_nothrow_swappable_v<T>);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The other object whose state is swapped with the current object; after the swap each holds the other's original state. |

## Return Value

No return value.

## Constraints

- T must be an ordinary non-reference object type.
- Host follows the valid C++17 operations.
- The operations that construction, assignment, invocation, and swap rely on must not throw on the device side.

## Example

The following Host snippet demonstrates the call with concrete types; the object must be confirmed to be in the engaged state before accessing the value.

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> left(1), right(2);
    left.swap(right);
    return *left == 2 && *right == 1;
}
```

## Related APIs

- [`asc::std::optional`](optional.md)
- [API list for this header](asc_std_optional.md)
