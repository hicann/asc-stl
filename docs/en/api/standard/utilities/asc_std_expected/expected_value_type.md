# asc::std::expected::value_type

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

Header: `<asc/std/expected>`.

`asc::std::expected::value_type` identifies the value type of an element or result.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Declaration

Member of: [`asc::std::expected`](expected.md).

```cpp
// Excerpt of the declaration inside class asc::std::expected; template parameters and other members are provided by the owning class.
using value_type = Value;
```

## Constraints

- The owning expected<Value, Error> requires a valid non-void value type and an error object type; the current operation must also satisfy the prototype, parameter, and state requirements on this page.

## Example

The following Host example uses concrete types and an independent expectation to check an alias or marker result.

```cpp
#include <asc/std/expected>
#include <asc/std/type_traits>

void use_type()
{
    using alias_type = typename asc::std::expected<int, int>::value_type;
    static_assert(asc::std::is_same_v<alias_type, int>);
}
```

## Related APIs

- [`asc::std::expected`](expected.md)
- [API list for this header](asc_std_expected.md)
