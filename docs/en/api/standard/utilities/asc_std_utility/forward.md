# asc::std::forward

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

`asc::std::forward` preserves the value category of the argument according to the template parameter.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<typename T> [[nodiscard]] constexpr T&& forward(typename std::remove_reference<T>::type&& value) noexcept;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<typename T> [[nodiscard]] constexpr T&& forward(typename std::remove_reference<T>::type& value) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target type explicitly specified by the caller; it determines the value category of the returned reference (a non-reference type yields an rvalue reference, and an lvalue reference type collapses to an lvalue reference). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The rvalue to forward; it is forwarded as-is as T&& according to the explicit template parameter T, producing no copy or move. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target type explicitly specified by the caller; it determines the value category of the returned reference (a non-reference type yields an rvalue reference, and an lvalue reference type collapses to an lvalue reference). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The lvalue to forward; it is forwarded as T&& according to the explicit template parameter T (after reference collapsing, it stays an lvalue when T is an lvalue reference, otherwise an rvalue reference may be obtained), producing no copy or move. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T &&` | Returns a reference to the object; the referenced object must remain valid for as long as the reference is used. |
| Prototype 2 | `T &&` | Returns a reference to the object; the referenced object must remain valid for as long as the reference is used. |

## Constraints

- Follows the standard constraints.
- forward_like preserves const/volatile qualification and value category.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

bool example()
{
    int value = 3;
    auto&& reference = asc::std::forward<int&>(value);
    static_assert(asc::std::is_same_v<decltype(reference), int&>);
    // Check the reference while value is still alive; the function only returns a boolean value.
    return &reference == &value && reference == 3;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
