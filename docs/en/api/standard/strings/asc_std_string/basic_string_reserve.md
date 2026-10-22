# asc::std::basic_string::reserve

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

`asc::std::basic_string::reserve` requests storage capacity for at least the specified number of elements.

Standard semantics reference: [cppreference `string`](https://en.cppreference.com/w/cpp/header/string).

## Function Prototype

Member of: [`asc::std::basic_string`](basic_string.md).

```cpp
// Excerpt of the declaration inside class asc::std::basic_string; template parameters and other members are provided by the owning class.
void reserve(size_type requested);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `requested` | Input | Minimum character capacity requested; requested + 1 must be representable by size_type and allocatable by the allocator. After a successful return, capacity() is not less than requested. |

## Return Value

No return value.

## Constraints

- Pure AI Core SIMT programming use must also follow the [toolchain verification boundaries](basic_string.md#toolchain-verification-boundaries-in-ai-core-simt-programming) of the owning type.

- The allocator must provide storage for at least requested + 1 characters, with the extra 1 position reserved for the terminating null character; terminate is called when the allocation returns a null pointer, and returning by exception is not guaranteed. terminate is also called when requested + 1 cannot be represented.

- Explicit-allocator construction of basic_string<char,Traits,A>.
- append/push_back/clear for plain/local character sources.
- size/capacity/data/c_str/iteration/indexing and destruction.
- Only the sufficient-capacity and non-throwing exception domains.

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <memory>
#include <asc/std/string>

bool example()
{
    ::std::allocator<char> allocator;
    asc::std::basic_string<char, asc::std::char_traits<char>, ::std::allocator<char>> value("abc", allocator);
    value.reserve(32);
    return value.capacity() >= 32 && value.size() == 3 && value[0] == 'a' && value.c_str()[3] == '\0';
}
```

## Related APIs

- [`asc::std::basic_string`](basic_string.md)
- [API list for this header](asc_std_string.md)
