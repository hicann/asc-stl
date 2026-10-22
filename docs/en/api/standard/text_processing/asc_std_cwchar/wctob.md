# asc::std::wctob

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

`asc::std::wctob` converts between a single-byte character and its wide character representation.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
int wctob(wint_t value) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The wide character (wint_t) to check; the value must be representable as a wide character or equal to WEOF, and whether it corresponds to a single-byte character is indicated by the return value. |

## Return Value

| Return type | Description |
| --- | --- |
| `int` | When the value is representable as a single-byte character, returns the corresponding unsigned char value promoted to int; otherwise returns EOF. |

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- Device is fixed to stateless single-byte conversion and supports only ASCII and the null character; out-of-range input reports failure as described in the return value of this interface.
- Different character sequences use independent state objects; string output buffers must have sufficient capacity.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>

decltype(auto) example(asc::std::wint_t value)
{
    return asc::std::wctob(value);
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
