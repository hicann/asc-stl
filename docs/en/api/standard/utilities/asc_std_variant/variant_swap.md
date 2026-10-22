# asc::std::variant::swap

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

Header: `<asc/std/variant>`.

`asc::std::variant::swap` swaps the held states or elements of two objects.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

Member of: [`asc::std::variant<Types...>`](variant.md). The following are declarations inside the class; unnamed constraint parameters and the default index are used to select overloads, and the caller does not need to specify them.

### Swapping the contents

```cpp
constexpr void swap(variant& other) noexcept(
    __fold_and_v<(is_nothrow_move_constructible_v<Types> && is_nothrow_move_assignable_v<Types>)...>);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Types` | The list of alternative types of the owning `variant`; it must not contain arrays, references, or `void`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input; Input/Output when swapping | A same-type source object; the rvalue form may move its active alternative value, and a swap changes both objects. |

## Return Value

No return value.

## Constraints

- The object holds one active alternative value at a time; the selected alternative must be confirmed through `index()` before reading.
- Alternative types used on the device and their construction, assignment, destruction, and swap operations must be available in the corresponding programming mode and must not throw.
- The swap is performed through move construction and move assignment; all alternative types must support the corresponding operations, and this member is `noexcept` when every operation does not throw.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> left(7);
    asc::std::variant<int, float> right(2.5F);
    left.swap(right);
    return left.index() == 1 && right.index() == 0 &&
        asc::std::get<1>(left) == 2.5F && asc::std::get<0>(right) == 7;
}
```

## Related APIs

- [`asc::std::variant`](variant.md)
- [API list for this header](asc_std_variant.md)
