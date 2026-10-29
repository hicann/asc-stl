# asc::std::wcscoll

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

`asc::std::wcscoll` compares two wide strings under the current C locale on Host (with the C locale fixed on Device).

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
int wcscoll(const wchar_t* left, const wchar_t* right) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The address of the first character of the left wide string in the comparison, terminated by a null character; compared according to the collation rules of the current locale. |
| `right` | Input | The address of the first character of the right wide string in the comparison, terminated by a null character; compared according to the collation rules of the current locale. |

## Return Value

| Return type | Description |
| --- | --- |
| `int` | Returns a comparison result less than, equal to, or greater than zero, indicating that the left sequence is less than, equal to, or greater than the right sequence, respectively. |

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- Device uses the C locale as fixed, processes in wide character encoding order, and does not support locale-dependent collation rules.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>

decltype(auto) example(const wchar_t * left, const wchar_t * right)
{
    return asc::std::wcscoll(left, right);
}

bool verify_example()
{
    return example(L"abc", L"abc") == 0;
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
