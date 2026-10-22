# asc::std::basic_string::`operator[]`

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

`asc::std::basic_string::operator[]` accesses the specified element when the caller guarantees the index is valid.

Standard semantics reference: [cppreference `string`](https://en.cppreference.com/w/cpp/header/string).

## Function Prototype

Member of: [`asc::std::basic_string`](basic_string.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::basic_string; template parameters and other members are provided by the owning class.
const_reference operator[](size_type index) const noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::basic_string; template parameters and other members are provided by the owning class.
reference operator[](size_type index) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | Subscript of the character to access (starting from 0); the caller must guarantee index < size(), and this operator performs no out-of-bounds checking. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | Subscript of the character to access (starting from 0); the caller must guarantee index < size(), and this operator performs no out-of-bounds checking. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `const_reference` | Returns a reference or proxy value to the element at the specified index; the index must be valid. |
| Prototype 2 | `reference` | Returns a reference or proxy value to the element at the specified index; the index must be valid. |

## Constraints

- The returned pointer, reference, or iterator borrows the current string's character storage; destroying the string or an operation that triggers reallocation invalidates it. Confirm that the object and the corresponding element are still alive before use, and do not keep this borrowed result across capacity growth.

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
    char& first = value[0];
    first = 'A';
    return value.size() == 3 && value[0] == 'A';
}
```

## Related APIs

- [`asc::std::basic_string`](basic_string.md)
- [API list for this header](asc_std_string.md)
