# asc::ub_accessor

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

Header: `<asc/mdspan>`.

`asc::ub_accessor` provides an mdspan accessor for UB data handles.

## Declaration

```cpp
namespace asc {
template <class Accessor>
class ub_accessor;
}  // namespace asc
```

## Constraints

- AI Core SIMD programming uses the real UB address space; the Host only provides a plain pointer representation and cannot directly access the device's physical UB. AI Core SIMT programming does not provide UB accessors/aliases; the storage must cover all accesses.


## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/mdspan>

bool example()
{
    int values[] = {2, 4};
    asc::ub_accessor<asc::std::default_accessor<int>> accessor;
    accessor.access(values, 1) = 7;
    return values[1] == 7 && accessor.offset(values, 1) == values + 1;
}
```

## Related APIs

- [API list for this header](asc_mdspan.md)
