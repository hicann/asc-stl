# asc::std::source_location::source_location

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

`asc::std::source_location::source_location` initializes a `source_location` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `source_location`](https://en.cppreference.com/w/cpp/header/source_location).

## Function Prototype

Member of: [`source_location`](source_location.md).

```cpp
constexpr source_location() noexcept = default;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `file_name` | Input | Provides the object reference used by "initializes a `source_location` object with the construction forms listed on this page"; the referenced object must be valid for the duration of the call. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `file_name` | Input/Output | Provides the object reference used by "initializes a `source_location` object with the construction forms listed on this page"; the referenced object must be valid for the duration of the call. |

## Return Value

No return value.

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

- [API list for this header](asc_std_source_location.md)
