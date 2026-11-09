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

Include `<asc/std/utility>`. Exchanges two object values or swaps equal-length arrays element by element. The prototypes express equivalent public type constraints and omit the internal return alias.

## Function Prototype

```cpp
template <class T>
constexpr void swap(T& left, asc::std::type_identity_t<T>& right)
    noexcept(asc::std::is_nothrow_move_constructible_v<T> && asc::std::is_nothrow_move_assignable_v<T>);
```

```cpp
template <class T, asc::std::size_t N>
constexpr void swap(T (&left)[N], T (&right)[N])
    noexcept(asc::std::is_nothrow_swappable_v<T>);
```

## Parameters

| Name | Direction | Description |
| --- | --- | --- |
| `T` | Input | Object or array element type. |
| `N` | Input | Equal array extent. |
| `left` | Input/output | First valid object or array. |
| `right` | Input/output | Second valid object or array. |

## Return Value

No return value.

## Constraints

The object overload requires move construction and move assignment. The array overload requires swappable elements and does not replace an applicable array ADL overload. Device calls support native GM/UB arithmetic object references satisfying the type constraints, using a register temporary. Callers must provide valid addresses and required inter-thread synchronization. Host calls retain a temporary of the object type.

## Example

```cpp
#include <asc/std/utility>

bool example()
{
    int left = 2, right = 7;
    asc::std::swap(left, right);
    int first[] = {1, 2}, second[] = {3, 4};
    asc::std::swap(first, second);
    return left == 7 && right == 2 && first[0] == 3 && first[1] == 4 && second[0] == 1;
}
```

## Related APIs

- [<asc/std/utility>](asc_std_utility.md)
- [swap(unique_lock/shared_lock)](../../concurrency/asc_std_mutex/swap.md)
