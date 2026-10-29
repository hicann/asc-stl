# asc::always_false::`operator()`

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

Header: `<asc/functional>`.

`asc::always_false::operator()` ignores all arguments and returns false.

## Function Prototype

Member of: [`asc::always_false`](always_false.md).

```cpp
// Excerpt of the declaration inside asc::always_false; template parameters and other members are provided by the enclosing class.
template <class... Args>
constexpr bool operator()(Args&&...) const noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Args` | The list of argument types passed to the constructor or callable object. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, and `false` otherwise. |

## Constraints

- The object on this page only performs the described predicate, comparison, or compile-time property query; it does not perform any Runtime submission.
- Comparison operands must support the corresponding operation; transparent min/max may return a reference, and the selected object must remain valid for the duration of use.
- A copyable-arguments declaration only states the caller's copying promise; it does not extend the lifetime of captured references and does not replace callability checks.

## Example

The following Host snippet demonstrates the call with concrete values; inputs must satisfy the constraints on this page.

```cpp
#include <asc/functional>

decltype(auto) example()
{
    return asc::always_false{}(7);
}

bool verify_example()
{
    return example() == false;
}
```

## Related APIs

- [`asc::always_false`](always_false.md)
- [API list for this header](asc_functional.md)
