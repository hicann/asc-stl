# asc::maximum

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

`asc::maximum` provides a transparent function object that returns the larger of two inputs.

## Declaration

```cpp
namespace asc {
template <class T = void>
struct maximum;
}  // namespace asc
```

## Constraints

- The object on this page only performs the described predicate, comparison, or compile-time property query; it does not perform any Runtime submission.
- Comparison operands must support the corresponding operation; transparent min/max may return a reference, and the selected object must remain valid for the duration of use.
- A copyable-arguments declaration only states the caller's copying promise; it does not extend the lifetime of captured references and does not replace callability checks.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/functional>

bool example()
{
    return asc::maximum<int>{}(3, 7) == 7;
}
```

## Related APIs

- [API list for this header](asc_functional.md)
