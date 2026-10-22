# asc::std::exchange

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

`asc::std::exchange` replaces the object's value with a new value and returns the old value.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

```cpp
namespace asc::std {
template<class T, class U = T>
constexpr T exchange(T& object, U&& new_value)
    noexcept(is_nothrow_move_constructible_v<T> && is_nothrow_assignable_v<T&, U>);
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The type of the object being replaced; it must be move constructible and assignable from T2. |
| `T2` | The type of the new value; it must be assignable to T1&. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input/Output | The object being replaced; its old value is returned via move, and it holds new_value after the call. |
| `new_value` | Input/Output | The new value assigned to object; it is moved when assigned as an rvalue and ends up in a valid but unspecified state after the move. |

## Return Value

| Return type | Description |
| --- | --- |
| `T1` | Returns the old value. |

## Constraints

- Follows the standard constraints.
- forward_like preserves const/volatile qualification and value category.

## Example

The following snippet demonstrates the call on this page with concrete values.

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    int value = 3;
    return asc::std::exchange(value, 4);
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
