# asc::std::forward_like

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

`asc::std::forward_like` copies const/volatile qualification and the value category from a model type.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

The following is a call-form summary; the cv qualification and value category of the returned reference are applied to U modeled on T&&, and the actual type is obtained through type computation in the implementation.

```cpp
namespace asc::std {
template<class T, class U>
[[nodiscard]] constexpr decltype(auto) forward_like(U&& value) noexcept;
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The reference type providing the target const/volatile qualification and lvalue/rvalue reference category. |
| `U` | The deduced type of the forwarded argument; the returned expression merges the const/volatile qualification specified by T while preserving U's existing qualification and reference category. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The object reference on which "copying const/volatile qualification and the value category from a model type" operates; the referenced object must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `decltype(auto)` | Returns a reference that preserves qualification and value category modeled on T, constructing no new object. |

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
    auto&& reference = asc::std::forward_like<int&>(value);
    static_assert(asc::std::is_same_v<decltype(reference), int&>);
    // Check the reference while value is still alive; the function only returns a boolean value.
    return &reference == &value && reference == 3;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
