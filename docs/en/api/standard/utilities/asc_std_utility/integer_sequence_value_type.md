# asc::std::integer_sequence::value_type

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

Header: `<asc/std/utility>`.

`asc::std::integer_sequence::value_type` identifies the value type of the element or result.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Declaration

Member of: [`asc::std::integer_sequence`](integer_sequence.md).

```cpp
// Excerpt of the declaration inside class asc::std::integer_sequence; template parameters and other members are provided by the owning class.
using value_type = T;
```

## Constraints

- Provides the complete standard form.

## Example

The following Host example checks the alias or tag result with concrete types and an independent expectation.

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

void use_type()
{
    using alias_type = typename asc::std::integer_sequence<int, 1, 2, 3>::value_type;
    static_assert(asc::std::is_same_v<alias_type, int>);
}
```

## Related APIs

- [`asc::std::integer_sequence`](integer_sequence.md)
- [API list for this header](asc_std_utility.md)
