# asc::std::wcstok

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

Header: `<asc/std/cwchar>`.

`asc::std::wcstok` splits a wide string by the delimiter set provided by the caller.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
wchar_t* wcstok(wchar_t* input, const wchar_t* delimiters, wchar_t** state) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `input` | Input/Output | In the first round, the writable string terminated by a zero wide character, at whose delimiter positions zero characters are written; subsequent calls pass nullptr to continue tokenizing. |
| `delimiters` | Input | The set of delimiter characters, terminated by a zero wide character, which may be changed between successive calls. |
| `state` | Input/Output | The pointer slot that saves the next scan position; successive calls use the same non-null slot. |

## Return Value

| Return type | Description |
| --- | --- |
| `wchar_t *` | Returns the pointer to the start of the wide string obtained by this split; returns a null pointer when there are no more segments. |

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- The input wide string must be writable and terminated by a null character. This operation writes zero characters at the delimiter termination positions; the state pointer that saves the next scan position must be valid.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>

decltype(auto) example(wchar_t * input, const wchar_t * delimiters, wchar_t ** state)
{
    return asc::std::wcstok(input, delimiters, state);
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
