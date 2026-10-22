# asc::std::ignore

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

Header: `<asc/std/tuple>`.

`asc::std::ignore` discards the value assigned to this position.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Declaration

The following is the object declaration after the class definition. The concrete type is an implementation detail; the caller uses `ignore` directly as an assignment sink.

```cpp
namespace asc::std {
inline constexpr __ignore_t ignore{};
}
```

## Constraints

- ignore serves only as an assignment sink and discards the assigned value; it does not promise to substitute for an arbitrary construction placeholder or to hold the assigned object.

## Example

The following Host example shows this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/tuple>

bool example()
{
    int first = 0;
    asc::std::tie(first, asc::std::ignore) = asc::std::make_tuple(3, 4);
    return first == 3;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
