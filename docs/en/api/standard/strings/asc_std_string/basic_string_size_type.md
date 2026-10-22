# asc::std::basic_string::size_type

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

Header: `<asc/std/string>`.

`asc::std::basic_string::size_type` identifies the unsigned type used for container sizes.

Standard semantics reference: [cppreference `string`](https://en.cppreference.com/w/cpp/header/string).

## Declaration

Member of: [`asc::std::basic_string`](basic_string.md).

```cpp
// Excerpt of the declaration inside class asc::std::basic_string; template parameters and other members are provided by the owning class.
using size_type = unsigned long;
```

## Constraints

- This alias denotes the unsigned integer type the owning type uses for element counts or sizes; reading the type itself allocates no memory and accesses no elements.
- For the runtime conditions of construction, allocation, and access, see the owning type [asc::std::basic_string](basic_string.md).

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <memory>
#include <asc/std/string>
#include <asc/std/cstddef>
#include <asc/std/type_traits>

bool example()
{
    using S = asc::std::basic_string<char, asc::std::char_traits<char>, ::std::allocator<char>>;
    static_assert(asc::std::is_same_v<S::size_type, asc::std::size_t>);
    return true;
}
```

## Related APIs

- [`asc::std::basic_string`](basic_string.md)
- [API list for this header](asc_std_string.md)
