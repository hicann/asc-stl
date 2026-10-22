# asc::std::chrono::treat_as_floating_point

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

`asc::std::chrono::treat_as_floating_point` determines whether `Rep` is treated as a floating-point count, inheriting `is_floating_point` by default; custom count types can be explicitly specialized before first use.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

```cpp
namespace asc::std::chrono {
template<class Rep> struct treat_as_floating_point;
} // namespace asc::std::chrono
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep` | The duration count type to classify; it can be a custom type. |

## Constraints

- Provides value arithmetic and the six explicit relational operators.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/chrono>

bool example()
{
    static_assert(asc::std::chrono::treat_as_floating_point<float>::value);
    static_assert(!asc::std::chrono::treat_as_floating_point<int>::value);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
