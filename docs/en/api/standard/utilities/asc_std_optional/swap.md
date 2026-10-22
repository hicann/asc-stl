# asc::std::swap

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

`asc::std::swap(optional<T>&, optional<T>&)` is provided by `<asc/std/optional>`, a free-function swap that is found by ADL and unqualified call sites and forwards to the member swap.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

```cpp
template <class T> constexpr enable_if_t<is_move_constructible_v<T> && is_swappable_v<T>, void> swap(optional<T>& left, optional<T>& right) noexcept(noexcept(left.swap(right)));
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The stored element type of both optionals; the element must support move construction and swap. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input/Output | A reference to an object participating in the operation; the referenced object must remain valid during the call. |
| `right` | Input/Output | A reference to an object participating in the operation; the referenced object must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `void` | No return value; swaps the engaged states and stored values of the two objects. |

## Constraints

- A free-function swap that is found by ADL and unqualified call sites and forwards to the member swap.

## Example

The following Host example provides concrete inputs and checks the result while the objects are still valid.

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> left(3), right;
    asc::std::swap(left, right);
    return !left && right && *right == 3;
}
```

## Related APIs

- [API list for this header](asc_std_optional.md)
