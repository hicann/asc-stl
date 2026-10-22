# asc::std::ranges::less::`operator()`

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

Header: `<asc/std/functional>`.

`asc::std::ranges::less::operator()` compares the input values as denoted by the function object name and returns a boolean result.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

Member of: [`asc::std::ranges::less`](ranges_less.md).

```cpp
// Excerpt of the declaration inside asc::std::ranges::less; the template parameters and other members are provided by the enclosing class.
template<class T, class U> constexpr bool operator()(T&& lhs, U&& rhs) const noexcept(noexcept(static_cast<bool>(lhs < rhs)));
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Left operand type; it must support the operation performed by this function object. |
| `U` | Right operand type; it must support the operation performed by this function object. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds and `false` otherwise. |

## Constraints

- Both the specified-type form and the transparent call form are provided.

## Example

The following Host snippet demonstrates a function object call with concrete integer arguments.

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    return asc::std::ranges::less{}(1, 2);
}
```

## Related APIs

- [`asc::std::ranges::less`](ranges_less.md)
- [API list for this header](asc_std_functional.md)
