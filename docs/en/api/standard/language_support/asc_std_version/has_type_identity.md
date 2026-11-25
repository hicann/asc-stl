# CANN_ASC_STL_HAS_TYPE_IDENTITY

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

Header: `<asc/std/version>`.

`CANN_ASC_STL_HAS_TYPE_IDENTITY` queries whether ASC-STL provides the type_identity type utility.

## Declaration

This object-like macro is available starting from C++17 and expands to an integer constant expression with the value 0 or 1; it can be used in `#if` conditional compilation.

## Constraints

- The value describes the capability of the selected interface subset of ASC-STL in the current configuration; it does not indicate a complete implementation of an entire ISO standard version and does not describe the Host `std` namespace.
- When the value is 1, the concrete operation must still satisfy the type, overload, execution location, resource, and constant-evaluation constraints of the corresponding API.

## Example

The following snippet checks the value form of a capability-query macro; for how to use the concrete facility, see the corresponding API page.

```cpp
#include <asc/std/version>

static_assert(CANN_ASC_STL_HAS_TYPE_IDENTITY == 0 || CANN_ASC_STL_HAS_TYPE_IDENTITY == 1);
```

## Related APIs

- [Language Modes and Compatibility](../../../../guide/cpp_compatibility.md)
- [API list for this header](asc_std_version.md)
