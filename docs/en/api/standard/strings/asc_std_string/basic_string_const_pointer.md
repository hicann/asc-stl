# asc::std::basic_string::const_pointer

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

`asc::std::basic_string::const_pointer` identifies the read-only element pointer type.

Standard semantics reference: [cppreference `string`](https://en.cppreference.com/w/cpp/header/string).

## Declaration

Member of: [`asc::std::basic_string`](basic_string.md).

```cpp
// Excerpt of the declaration inside class asc::std::basic_string; template parameters and other members are provided by the owning class.
using const_pointer = const CharT*;
```

## Constraints

- Explicit-allocator construction of basic_string<char,Traits,A>.
- append/push_back/clear for plain/local character sources.
- size/capacity/data/c_str/iteration/indexing and destruction.
- Only the sufficient-capacity and non-throwing exception domains.

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
    static_assert(asc::std::is_same_v<S::const_pointer, const char*>);
    return true;
}
```

## Related APIs

- [`asc::std::basic_string`](basic_string.md)
- [API list for this header](asc_std_string.md)
