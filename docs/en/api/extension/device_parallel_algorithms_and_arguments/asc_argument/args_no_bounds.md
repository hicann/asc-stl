# asc::args::no_bounds

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

`asc::args::no_bounds` indicates that the argument carries no value bounds.

## Declaration

```cpp
// Excerpt of the declaration inside asc::args; template parameters and other members are provided by the owning class.
struct no_bounds;
```

## Constraints

- no_bounds only indicates that no bounds information is carried; it does not validate actual values or data pointers, and when the data is used the preconditions of the called interface must still be satisfied.

- Uses C++17 and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/argument>

bool example()
{
    asc::args::immediate<int> argument(7, asc::args::no_bounds{});
    return argument.value() == 7;
}
```

## Related APIs

- [API list for this header](asc_argument.md)
