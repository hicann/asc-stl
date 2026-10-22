# asc::std::in_place_index_t::in_place_index_t

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

`asc::std::in_place_index_t::in_place_index_t` initializes an `in_place_index_t` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

```cpp
in_place_index_t();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- Provides the complete standard form.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/utility>
#include <asc/std/variant>

bool example()
{
    asc::std::in_place_index_t<0> tag{};
    asc::std::variant<int, float> value(tag, 7);
    return asc::std::get<0>(value) == 7;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
