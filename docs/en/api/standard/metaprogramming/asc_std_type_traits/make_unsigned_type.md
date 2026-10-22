# asc::std::make_unsigned::type

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

Header: `<asc/std/type_traits>`.

`asc::std::make_unsigned::type` provides the member type computed by the type trait, mapping, or adaptor.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

Member of: [`asc::std::make_unsigned`](make_unsigned.md).

```cpp
// Excerpt of the declaration inside asc::std::make_unsigned; template parameters and other members are provided by the owning class.
using type = make_unsigned_t<T>;
```

## Constraints

- `T` must be an integral or enumeration type other than `bool`, and an unsigned result type of the corresponding width must exist; floating-point, pointer, or `void` types must not be used.
- The conversion keeps the `const` and `volatile` qualification of the input type; it changes the type and does not perform a value conversion.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using result_type = typename asc::std::make_unsigned<int>::type;
static_assert(asc::std::is_same_v<result_type, unsigned int>);
```

## Related APIs

- [`asc::std::make_unsigned`](make_unsigned.md)
- [API list for this header](asc_std_type_traits.md)
