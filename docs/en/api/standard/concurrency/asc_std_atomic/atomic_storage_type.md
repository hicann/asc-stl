# asc::std::atomic::storage_type

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

Header: `<asc/std/atomic>`.

`asc::std::atomic::storage_type` identifies the underlying unit type held by the atomic object.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Declaration

`storage_type` is the 32-bit or 64-bit storage unit type used by the current integer or character type. The following obtains the storage type corresponding to `atomic<int>` through the public alias.

```cpp
using storage_type = asc::std::atomic<int>::storage_type;
```

## Constraints

- This alias is the integer storage type actually used by the atomic object; it must be instantiated with a `T` supported by [atomic](atomic.md).
- `bool` and 8-bit or 16-bit values use a 32-bit storage unit; 32-bit and 64-bit values use a storage unit of the corresponding width. Reading the type itself performs no atomic operation.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/atomic>

void use_type()
{
    using alias_type = typename asc::std::atomic<int>::storage_type;
}
```

## Related APIs

- [`asc::std::atomic`](atomic.md)
- [API list for this header](asc_std_atomic.md)
