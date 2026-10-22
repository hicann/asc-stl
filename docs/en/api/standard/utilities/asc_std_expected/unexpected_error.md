# asc::std::unexpected::error

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

Header: `<asc/std/expected>`.

`asc::std::unexpected::error` returns a reference to the error object stored in the error state.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

Member of: [`asc::std::unexpected`](unexpected.md).

```cpp
// Excerpt of the declaration inside class asc::std::unexpected; template parameters and other members are provided by the owning class.
constexpr const Error& error() const& noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `const Error &` | Returns a reference to the error object stored in the error state. |

## Constraints

- Error must be a cv-unqualified non-array object type and not an unexpected specialization; each construction, access, or swap operation must also satisfy the requirements of the prototype on this page.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::unexpected<int> error(7);
    error.error() = 9;
    return error.error() == 9;
}
```

## Related APIs

- [`asc::std::unexpected`](unexpected.md)
- [API list for this header](asc_std_expected.md)
