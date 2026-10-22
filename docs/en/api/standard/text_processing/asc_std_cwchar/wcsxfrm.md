# asc::std::wcsxfrm

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

`asc::std::wcsxfrm` generates a collation key for a wide string under the current C locale on Host (with the C locale fixed on Device).

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
size_t wcsxfrm(wchar_t* destination, const wchar_t* source, size_t count) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `destination` | Output | The destination storage that receives the result. This call executes synchronously and the writes are complete when it returns; the destination storage only needs to remain valid for the duration of the call, and sufficient space must be reserved for the content to be written. |
| `source` | Input | The source data or source object. This call executes synchronously and the reads are complete when it returns; the source storage only needs to remain valid for the duration of the call. |
| `count` | Input | The capacity of the destination buffer in wchar_t elements, including the space required for the terminating null character. |

## Return Value

| Return type | Description |
| --- | --- |
| `size_t` | Returns the number of wchar_t elements required by the full collation key, excluding the terminating null character; when the return value is greater than or equal to count, the destination buffer is not large enough to hold the full key and the terminating null character, and the destination must not be used as the full key. |

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- Device uses the C locale as fixed, processes in wide character encoding order, and does not support locale-dependent collation rules.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>
#include <asc/std/cstddef>

decltype(auto) example(wchar_t * destination, const wchar_t * source, asc::std::size_t count)
{
    return asc::std::wcsxfrm(destination, source, count);
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
