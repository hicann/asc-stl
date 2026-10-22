# asc::std::size_t

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

Header: `<asc/std/cstddef>`, `<asc/std/cuchar>`, `<asc/std/cwchar>`.

`asc::std::size_t` identifies the size, pointer difference, null pointer, or maximum alignment type corresponding to the current C++ ABI.

Standard semantics reference: [cppreference `cstddef`](https://en.cppreference.com/w/cpp/header/cstddef).

## Declaration

```cpp
namespace asc::std {
using size_t = unsigned long;
} // namespace asc::std
```

This prototype corresponds to the headers: `<asc/std/cstddef>`, `<asc/std/cuchar>`, `<asc/std/cwchar>`.

## Constraints

- `asc::std::size_t` is an unsigned integer type used to represent object byte counts, element counts, and indices.
- The maximum representable value depends on the address width of the target platform; the range should be checked before converting from a wider or signed integer.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cstddef>
#include <asc/std/type_traits>

bool example()
{
    using Integer = asc::std::size_t;
    static_assert(asc::std::is_integral_v<Integer>);
    static_assert(asc::std::is_signed_v<Integer> == false);
    Integer left = 2;
    Integer right = 3;
    return left + right == 5;
}
```

## Related APIs

- [API list for this header](asc_std_cstddef.md)
