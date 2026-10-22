# asc::std::chrono::hh_mm_ss::operator precision

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

Header: `<asc/std/chrono>`.

`asc::std::chrono::hh_mm_ss::operator precision` is provided by `<asc/std/chrono>` and restores the hours-minutes-seconds decomposition into a total duration at precision. The interface follows the semantics of the corresponding C++ standard facility; the language modes and call sites of ASC-STL are governed by the declarations on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

The enclosing class is [`hh_mm_ss<Duration>`](chrono_hh_mm_ss.md); Duration is provided by that class.

```cpp
[[nodiscard]] explicit constexpr operator precision() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `precision` | The duration composed from this object's sign and its hours, minutes, seconds, and fractional seconds. |

## Constraints

- The conversion result is equivalent to to_duration(), combining the sign, hours, minutes, seconds, and fractional seconds at precision; if the original period cannot be exactly represented by precision, the result may lose fractional precision.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::hh_mm_ss<asc::std::chrono::seconds> value{asc::std::chrono::seconds{3661}};
    return static_cast<asc::std::chrono::seconds>(value).count() == 3661;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
