# asc::std::chrono::time_point::clock

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

`asc::std::chrono::time_point::clock` is the `Clock` type the time point belongs to; when two time points are subtracted or compared, they must belong to the same `Clock`.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

Member of: [`asc::std::chrono::time_point`](chrono_time_point.md).

```cpp
// Declaration excerpt from inside the asc::std::chrono::time_point class; template parameters and other members are provided by the enclosing class.
using clock = Clock;
```

## Constraints

- Supports user-defined clocks, value arithmetic, and the six explicit relational operators.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>
#include <asc/std/type_traits>

using actual_type = asc::std::chrono::time_point<asc::std::chrono::system_clock>::clock;
using expected_type = asc::std::chrono::system_clock;
static_assert(asc::std::is_same_v<actual_type, expected_type>);
```

## Related APIs

- [`asc::std::chrono::time_point`](chrono_time_point.md)
- [API list for this header](asc_std_chrono.md)
