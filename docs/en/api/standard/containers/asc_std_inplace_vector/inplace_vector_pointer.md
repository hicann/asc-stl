# asc::std::inplace_vector::pointer

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

Header: `<asc/std/inplace_vector>`.

`asc::std::inplace_vector::pointer` denotes the element pointer type.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Declaration

Member of: [`asc::std::inplace_vector`](inplace_vector.md).

```cpp
// Excerpt of the declaration inside class asc::std::inplace_vector; template parameters and other members are provided by the owning class.
using pointer = T*;
```

## Constraints

- Pointers, iterators, and references borrow the element storage inside the object; they must not be used after the container is destroyed.
- After elements are erased or moved, the original positions may no longer denote the original elements; the new positions returned by the operation prevail.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/inplace_vector>

void use_type()
{
    using alias_type = typename asc::std::inplace_vector<int, 8>::pointer;
}
```

## Related APIs

- [`asc::std::inplace_vector`](inplace_vector.md)
- [API list for this header](asc_std_inplace_vector.md)
