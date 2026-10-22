# asc::std::basic_string::append

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

`asc::std::basic_string::append` appends characters or string contents to the end of the current string.

Standard semantics reference: [cppreference `string`](https://en.cppreference.com/w/cpp/header/string).

## Function Prototype

Member of: [`asc::std::basic_string`](basic_string.md).

```cpp
// Excerpt of the declaration inside class asc::std::basic_string; template parameters and other members are provided by the owning class.
basic_string<CharT, Traits, Allocator>& append(const CharT* text);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `text` | Input | Source character sequence to copy; it must be zero-terminated when no length argument is given, and must contain at least the specified number of readable characters when a length argument is given. The call copies the characters and does not take ownership of the source storage. |

## Return Value

| Return type | Description |
| --- | --- |
| `basic_string<CharT, Traits, Allocator> &` | Returns a reference to the object; the referenced object must remain valid for as long as the reference is used. |

## Constraints

- Pure AI Core SIMT programming use must also follow the [toolchain verification boundaries](basic_string.md#toolchain-verification-boundaries-in-ai-core-simt-programming) of the owning type.

- Null-terminated input may come from this object's character storage, including the object's whole string or a suffix. Appending preserves the source location when capacity growth is required; character-pointer assignment reads the source length before modifying the contents; re-obtain externally borrowed pointers invalidated by reallocation after the operation completes.
- The space required for the new length plus the terminating null character must be representable; if it cannot be represented, terminate is called, and allocator operations must still satisfy this type's non-throwing usage domain.

- Explicit-allocator construction of basic_string<char,Traits,A>.
- append/push_back/clear for plain/local character sources.
- size/capacity/data/c_str/iteration/indexing and destruction.
- Only the sufficient-capacity and non-throwing exception domains.

## Example

The following Host example uses an explicit allocator and observes operations whose input comes from the string itself while the string is alive.

```cpp
#include <memory>
#include <asc/std/string>

bool example()
{
    ::std::allocator<char> allocator;
    using S = asc::std::basic_string<char, asc::std::char_traits<char>, ::std::allocator<char>>;
    S value("abc", allocator);
    S& result = value.append(value.data());
    return &result == &value && value.size() == 6 && value[0] == 'a' && value[3] == 'a' && value.back() == 'c';
}
```

## Related APIs

- [`asc::std::basic_string`](basic_string.md)
- [API list for this header](asc_std_string.md)
