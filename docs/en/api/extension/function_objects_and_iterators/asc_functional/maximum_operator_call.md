# asc::maximum::`operator()`

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

`asc::maximum::operator()` compares two inputs and returns the larger value.

## Function Prototype

In-class declaration of the primary template `asc::maximum<T>`:

```cpp
constexpr T operator()(const T& left, const T& right) const noexcept(noexcept(left < right));
```

In-class declaration of the transparent specialization `asc::maximum<void>`:

```cpp
template <class Left, class Right>
constexpr auto operator()(Left&& left, Right&& right) const
    noexcept(noexcept(left < right)) -> decltype(left < right ? right : left);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Left` | The type of the left comparison operand. |
| `Right` | The type of the right comparison operand. |

## Return Value

- The primary template returns a copy of the T value.
- The void specialization returns the actual type of the conditional expression, which may be a reference; the selected operand must stay alive while the returned reference is in use.

## Constraints

- The object on this page only performs the described predicate, comparison, or compile-time property query; it does not perform any Runtime submission.
- Comparison operands must support the corresponding operation; transparent min/max may return a reference, and the selected object must remain valid for the duration of use.
- A copyable-arguments declaration only states the caller's copying promise; it does not extend the lifetime of captured references and does not replace callability checks.

## Example

The following Host example uses concrete inputs and checks the result within the object's lifetime.

```cpp
#include <asc/functional>
bool example()
{
    int left = 1;
    int right = 2;
    const int& result = asc::maximum<>{}(left, right);
    return &result == &right && result == 2;
}
```

## Related APIs

- [`asc::maximum`](maximum.md)
- [API list for this header](asc_functional.md)
