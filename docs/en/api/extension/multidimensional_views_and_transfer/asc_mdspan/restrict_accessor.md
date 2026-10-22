# asc::restrict_accessor

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

`asc::restrict_accessor` provides an mdspan accessor for data handles that satisfy the no-aliasing constraint.

## Declaration

```cpp
namespace asc {
template <class Accessor>
class restrict_accessor;
}  // namespace asc
```

## Constraints

- The underlying accessor must use a pointer handle; the caller takes on the promise of alias-free access, and the wrapper does not check aliasing at run time nor extend the storage lifetime.


## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/mdspan>

bool example()
{
    int values[] = {2, 4};
    asc::restrict_accessor<asc::std::default_accessor<int>> accessor;
    accessor.access(values, 1) = 7;
    return values[1] == 7 && accessor.offset(values, 1) == values + 1;
}
```

## Related APIs

- [API list for this header](asc_mdspan.md)
