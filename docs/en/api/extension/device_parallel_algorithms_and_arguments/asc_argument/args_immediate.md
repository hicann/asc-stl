# asc::args::immediate

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

`asc::args::immediate` holds an immediately available kernel argument by value, together with optional bounds.

## Declaration

```cpp
// Excerpt of the declaration inside asc::args; template parameters and other members are provided by the owning class.
template <class T, class Bounds = asc::args::no_bounds>
class immediate;
```

## Constraints

- The immediate value and Bounds are stored by value inside the wrapper; no_bounds, static_bounds, or runtime_bounds may be stored, and reading the value does not automatically validate the bounds.

- Uses C++17 and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/argument>

bool example()
{
    asc::args::immediate<int> argument(7);
    argument.value() = 9;
    return argument.value() == 9;
}
```

## Related APIs

- [API list for this header](asc_argument.md)
