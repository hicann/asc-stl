# asc::args::static_bounds

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

Header: `<asc/argument>`.

`asc::args::static_bounds` encodes the compile-time lower and upper bounds in the type.

## Declaration

```cpp
// Excerpt of the declaration inside asc::args; template parameters and other members are provided by the owning class.
template <auto Lower, auto Upper>
class static_bounds;
```

## Constraints

- Lower and Upper are compile-time bounds and must satisfy Lower <= Upper; queries only return the stored constants and do not read deferred pointers.

- Uses C++17 and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/argument>

bool example()
{
    using limits = asc::args::static_bounds<0, 10>;
    static_assert(limits::lower() == 0 && limits::upper() == 10);
    return true;
}
```

## Related APIs

- [API list for this header](asc_argument.md)
