# asc::std::is_error_code_enum

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

Header: `<asc/std/system_error>`.

`asc::std::is_error_code_enum` marks an enumeration type as usable for constructing error codes.

Standard semantics reference: [cppreference `system_error`](https://en.cppreference.com/w/cpp/header/system_error).

## Declaration

```cpp
namespace asc::std {
template<class T> struct is_error_code_enum;
} // namespace asc::std
```

## Constraints

- Provides the invalid_argument, result_out_of_range, and value_too_large error values, the corresponding traits, and enumeration comparison operations.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/system_error>

bool example()
{
    static_assert(!asc::std::is_error_code_enum<int>::value);
    static_assert(!asc::std::is_error_code_enum<asc::std::errc>::value);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_system_error.md)
