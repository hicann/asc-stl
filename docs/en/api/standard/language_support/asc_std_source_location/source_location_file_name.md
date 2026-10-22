# asc::std::source_location::file_name

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

Header: `<asc/std/source_location>`.

`asc::std::source_location::file_name` returns the file name stored in the source location.

Standard semantics reference: [cppreference `source_location`](https://en.cppreference.com/w/cpp/header/source_location).

## Function Prototype

Member of: [`asc::std::source_location`](source_location.md).

```cpp
// Excerpt of the declaration inside the asc::std::source_location class; template parameters and other members are provided by the enclosing class.
[[nodiscard]] constexpr const char* file_name() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `const char *` | Returns a pointer to a read-only null-terminated character sequence whose validity is bound to the enclosing object. |

## Constraints

- Provides the standard source_location interface.
- When the compiler cannot directly provide the column, column() uses the fallback value allowed by the standard.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/source_location>

bool example()
{
    const auto location = asc::std::source_location::current();
    return location.line() > 0 && location.file_name()[0] != '\0' && location.function_name()[0] != '\0';
}
```

## Related APIs

- [`asc::std::source_location`](source_location.md)
- [API list for this header](asc_std_source_location.md)
