# asc::std::chars_format

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

Header: `<asc/std/charconv>`.

`asc::std::chars_format` is provided by `<asc/std/charconv>`; it is the [charconv.syn] format vocabulary bitmask enumeration, whose enumerator values are independent of the host standard library, and hosted and device compilation share the same representation

Standard semantics reference: [cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv).

## Declaration

```cpp
enum class chars_format { scientific = 0x1, fixed = 0x2, hex = 0x4, general = fixed | scientific };
```

## Constraints

- The [charconv.syn] format vocabulary bitmask enumeration; the enumerator values are independent of the host standard library, and hosted and device compilation share the same representation.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/charconv>

decltype(auto) example()
{
    return asc::std::chars_format();
}

bool verify_example()
{
    return static_cast<int>(example()) == 0;
}
```

## Related APIs

- [API list for this header](asc_std_charconv.md)
