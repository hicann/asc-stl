# asc::std::source_location::current

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

`asc::std::source_location::current` captures the file, function, line, and column information of the call site.

Standard semantics reference: [cppreference `source_location`](https://en.cppreference.com/w/cpp/header/source_location).

## Function Prototype

Member of: [`source_location`](source_location.md). The following shows the configuration with built-in functions for the file, function, and line; it can be called on the class with zero arguments. Without these built-in functions, the file/line fall back to __FILE__/__LINE__ at the declaration site, and the function name falls back to an empty string.

```cpp
#if __has_builtin(__builtin_COLUMN)
[[nodiscard]] static constexpr source_location current(
    const char* file_name = __builtin_FILE(),
    const char* function_name = __builtin_FUNCTION(),
    uint_least32_t line = __builtin_LINE(),
    uint_least32_t column = __builtin_COLUMN()) noexcept;
#else
[[nodiscard]] static constexpr source_location current(
    const char* file_name = __builtin_FILE(),
    const char* function_name = __builtin_FUNCTION(),
    uint_least32_t line = __builtin_LINE(),
    uint_least32_t column = 0) noexcept;
#endif
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `file_name` | Input | The source file name, the address of the first character of a null-terminated string; the default argument is filled in from the compiler's built-in information. |
| `function_name` | Input | The function name, the address of the first character of a null-terminated string; the default argument is filled in from the compiler's built-in information. |
| `line` | Input | The line, stored by value; the default is provided by the compiler, and 0 can be used to indicate an unknown location. |
| `column` | Input | The column, stored by value; when a column built-in function is available the default is provided by it, otherwise it is 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `source_location` | Returns a source location object recording the file, function, line, and column of the current call site. |

## Constraints

- Captures the location synchronously and does not allocate or copy the file name or function name strings.
- The default strings come from the compiler; when strings are passed explicitly, their storage must cover the usage period of the source_location and its string pointers.
- When the column built-in function is not supported, the default column is 0; 0 indicates that no column is available.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/source_location>

bool example()
{
    const auto implicit = asc::std::source_location::current();
    const auto selected = asc::std::source_location::current("example.cpp", "example", 7, 0);
    return implicit.line() > 0 && selected.line() == 7 && selected.file_name()[0] == 'e';
}
```

## Related APIs

- [`asc::std::source_location`](source_location.md)
- [API list for this header](asc_std_source_location.md)
