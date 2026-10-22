# asc::std::unexpect_t::unexpect_t

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

`asc::std::unexpect_t::unexpect_t` initializes a `unexpect_t` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

### Prototype 1

```cpp
constexpr unexpect_t() noexcept;
```

### Prototype 2

```cpp
constexpr unexpect_t(const unexpect_t& other);
```

### Prototype 3

```cpp
constexpr unexpect_t(unexpect_t&& other);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The construction source object; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The construction source object; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

## Return Value

No return value.

## Constraints

- This tag selects the error in-place construction of expected; it contains no value or error storage and has no Value/Error template parameters.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::unexpect_t tag{};
    asc::std::expected<int, int> result(tag, 7);
    return !result.has_value() && result.error() == 7;
}
```

## Related APIs

- [API list for this header](asc_std_expected.md)
