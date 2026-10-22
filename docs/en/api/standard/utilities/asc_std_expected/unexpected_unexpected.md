# asc::std::unexpected::unexpected

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

`asc::std::unexpected::unexpected` initializes an `unexpected` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

The following is a **call-form summary** inside the owning class. The SFINAE selection parameters used by the implementation are omitted; the implicit and explicit forms of the same shape are selected by the constructibility and convertibility conditions below, and the summary must not be copied as a set of unconditional overload definitions.

```cpp
unexpected(const unexpected&) = default;
```

```cpp
unexpected(unexpected&&) = default;
```

```cpp
constexpr explicit unexpected(const Error& error);
```

```cpp
constexpr explicit unexpected(Error&& error) noexcept(is_nothrow_move_constructible_v<Error>);
```

```cpp
template <class Error2 = Error>
constexpr explicit unexpected(Error2&& error) noexcept(is_nothrow_constructible_v<Error, Error2>);
```

```cpp
template <class... Args>
constexpr explicit unexpected(in_place_t, Args&&... args);
```

This form is for Host use only.

```cpp
template <class U, class... Args>
constexpr explicit unexpected(in_place_t, ::std::initializer_list<U> il, Args&&... args) noexcept(
        is_nothrow_constructible_v<Error, ::std::initializer_list<U>&, Args...>);
```

This form is for Host use only.

## Parameters

**Template Parameters**

Error is the error type of the owning unexpected; Error2 is the source type of the forwarded error value, U is the element type of the Host initializer list, and Args... denotes the in-place construction argument types.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `error` | Input/Output (movable source) | The source used to construct the stored error object. |
| `args...` | Input/Output | The arguments forwarded to Error by the Host-only general in_place form. |
| `il` | Input | The initializer list used by Host only; it remains valid until the construction completes. |

## Return Value

No return value.

## Constraints

- Error must be a cv-unqualified non-array object type and cannot be an unexpected specialization; the forwarding construction excludes the in_place tag and unexpected itself. The error value and in-place construction are both explicit; the initializer_list and general in_place constructions are for Host use only.
- User-provided construction, allocation, and callable operations must be valid at the selected execution location; Device instances must suit the non-throwing target environment.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::unexpected<int> error(7);
    asc::std::unexpected<int> placed(asc::std::in_place, 9);
    return error.error() == 7 && placed.error() == 9;
}
```

## Related APIs

- [API list for this header](asc_std_expected.md)
