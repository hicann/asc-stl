# asc::std::chrono::duration::rep

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

`asc::std::chrono::duration::rep` is the `Rep` type that holds the number of ticks; it determines the count range and the integer or floating-point arithmetic properties.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

Member of: [`asc::std::chrono::duration`](chrono_duration.md).

```cpp
// Declaration excerpt from inside the asc::std::chrono::duration class; template parameters and other members are provided by the enclosing class.
using rep = Rep;
```

## Constraints

- Provides value operations and the six explicit relational operators.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/type_traits>

bool example()
{
    using Duration = asc::std::chrono::duration<int>;
    static_assert(asc::std::is_same_v<Duration::rep, int>);
    return Duration{3}.count() == 3;
}
```

## Related APIs

- [`asc::std::chrono::duration`](chrono_duration.md)
- [API list for this header](asc_std_chrono.md)
