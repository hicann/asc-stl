# asc::std::expected::error

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

`asc::std::expected::error` returns a reference to the error object stored in the error state.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

The following is the declaration inside class `expected<Value, Error>`; Value and Error are the owning class template parameters.

```cpp
constexpr Error& error() & noexcept;
```

```cpp
constexpr const Error& error() const& noexcept;
```

```cpp
constexpr Error&& error() && noexcept;
```

```cpp
constexpr const Error&& error() const&& noexcept;
```

## Parameters

No function parameters. Value and Error are the parameters of the owning expected class template.

## Return Value

Returns Error&, const Error&, Error&&, or const Error&&. Returns a reference to the error object, with cv/ref determined by this object. Only error-state access is allowed.

## Constraints

- The owning expected<Value, Error> requires a valid non-void value type and an error object type; the current operation must also satisfy the prototype, parameter, and state requirements on this page. error() access requires !has_value(); the error storage must not be read in the success state.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::expected<int, int> result(asc::std::unexpect, 7);
    return !result.has_value() && result.error() == 7;
}
```

## Related APIs

- [`asc::std::expected`](expected.md)
- [API list for this header](asc_std_expected.md)
