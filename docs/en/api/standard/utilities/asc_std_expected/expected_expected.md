# asc::std::expected::expected

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

`asc::std::expected::expected` initializes an `expected` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

The following is a **call-form summary** inside the owning class. The SFINAE selection parameters used by the implementation are omitted; the implicit and explicit forms of the same shape are selected by the constructibility and convertibility conditions below, and the summary must not be copied as a set of unconditional overload definitions.

```cpp
template <class Value2 = Value>
constexpr expected() noexcept(is_nothrow_default_constructible_v<Value2>);
```

```cpp
constexpr expected(const Value& value);
```

```cpp
constexpr expected(const unexpected<Error>& error);
```

```cpp
constexpr expected(unexpect_t, const Error& error);
```

```cpp
constexpr expected(const expected& other);
```

```cpp
expected(expected&&) = default;
```

The constexpr qualifier of this form was added only in C++20.

```cpp
~expected() = default;
```

```cpp
template <class Up, class OtherErr>
expected(const expected<Up, OtherErr>& other) noexcept(
        is_nothrow_constructible_v<Value, const Up&> && is_nothrow_constructible_v<Error, const OtherErr&>);
```

The constexpr qualifier of this form was added only in C++20.

```cpp
template <class Up, class OtherErr>
explicit expected(
        const expected<Up, OtherErr>& other) noexcept(is_nothrow_constructible_v<Value, const Up&> &&
        is_nothrow_constructible_v<Error, const OtherErr&>);
```

The constexpr qualifier of this form was added only in C++20.

```cpp
template <class Up, class OtherErr>
expected(expected<Up, OtherErr>&& other) noexcept(
        is_nothrow_constructible_v<Value, Up> && is_nothrow_constructible_v<Error, OtherErr>);
```

The constexpr qualifier of this form was added only in C++20.

```cpp
template <class Up, class OtherErr>
explicit expected(expected<Up, OtherErr>&& other) noexcept(
        is_nothrow_constructible_v<Value, Up> && is_nothrow_constructible_v<Error, OtherErr>);
```

The constexpr qualifier of this form was added only in C++20.

```cpp
template <class Up = Value>
constexpr expected(Up&& value) noexcept(is_nothrow_constructible_v<Value, Up>);
```

```cpp
template <class Up = Value>
constexpr explicit expected(Up&& value) noexcept(is_nothrow_constructible_v<Value, Up>);
```

```cpp
template <class OtherErr>
constexpr expected(const unexpected<OtherErr>& error) noexcept(
        is_nothrow_constructible_v<Error, const OtherErr&>);
```

```cpp
template <class OtherErr>
constexpr explicit expected(const unexpected<OtherErr>& error) noexcept(
        is_nothrow_constructible_v<Error, const OtherErr&>);
```

```cpp
template <class OtherErr>
constexpr expected(unexpected<OtherErr>&& error) noexcept(
        is_nothrow_constructible_v<Error, OtherErr>);
```

```cpp
template <class OtherErr>
constexpr explicit expected(unexpected<OtherErr>&& error) noexcept(
        is_nothrow_constructible_v<Error, OtherErr>);
```

```cpp
template <class... Args>
constexpr explicit expected(in_place_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<Value, Args...>);
```

```cpp
template <class Up, class... Args>
constexpr explicit expected(in_place_t, ::std::initializer_list<Up> list, Args&&... args) noexcept(
        is_nothrow_constructible_v<Value, ::std::initializer_list<Up>&, Args...>);
```

This form is for Host use only.

```cpp
template <class... Args>
constexpr explicit expected(unexpect_t, Args&&... args) noexcept(
        is_nothrow_constructible_v<Error, Args...>);
```

```cpp
template <class Up, class... Args>
constexpr explicit expected(unexpect_t, ::std::initializer_list<Up> list, Args&&... args) noexcept(
        is_nothrow_constructible_v<Error, ::std::initializer_list<Up>&, Args...>);
```

This form is for Host use only.

## Parameters

**Template Parameters**

Value and Error are the value/error types of the owning expected; Value2 of the default construction defaults to Value. Up and OtherErr denote the source component types of the conversion, and Args... denotes the in-place construction argument types.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output (movable source) | The construction source of the success value. |
| `error` | Input/Output (movable source) | The source for constructing unexpected or the error in place. |
| `other` | Input/Output (movable source) | The source expected; constructs the corresponding value or error according to its current active state. |
| `args...` | Input/Output | The in-place construction arguments forwarded to Value or Error. |
| `list` | Input | Used only by the Host-only initializer-list form; the elements are valid until the construction completes. |

## Return Value

No return value.

## Constraints

- Value is a non-void value type, and Error is a valid error object type. Default construction requires Value to be default constructible; the value, unexpected, and in-place forms each require the corresponding component to be constructible. Cross-expected conversion requires both the value side and the error side to be constructible, and excludes conflicting forms convertible directly from the whole expected; explicit is omitted when both sides are implicitly convertible, otherwise it is explicit. The availability of the move special members is determined by the move capability of Value and Error.
- User-provided construction, allocation, and callable operations must be valid at the selected execution location; Device instances must suit the non-throwing target environment.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::expected<int, int> zero;
    asc::std::expected<int, int> value(asc::std::in_place, 7);
    asc::std::expected<int, int> error(asc::std::unexpect, 5);
    return zero && *zero == 0 && value && *value == 7 && !error && error.error() == 5;
}
```

## Related APIs

- [API list for this header](asc_std_expected.md)
