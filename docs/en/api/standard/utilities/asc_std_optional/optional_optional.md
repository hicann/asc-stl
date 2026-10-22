# asc::std::optional::optional

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

Header: `<asc/std/optional>`.

`asc::std::optional::optional` initializes an `optional` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

The following is a **call-form summary** inside the owning class. The SFINAE selection parameters used by the implementation are omitted; the implicit and explicit forms of the same shape are selected by the constructibility and convertibility conditions below, and the summary must not be copied as a set of unconditional overload definitions.

```cpp
constexpr optional() noexcept = default;
```

```cpp
constexpr optional(nullopt_t) noexcept;
```

```cpp
constexpr optional(const optional& other);
```

```cpp
constexpr optional(optional&& other) noexcept(is_nothrow_move_constructible_v<T>);
```

```cpp
template <class U>
constexpr optional(const optional<U>& other);
```

```cpp
template <class U>
constexpr explicit optional(const optional<U>& other);
```

```cpp
template <class U>
constexpr optional(optional<U>&& other);
```

```cpp
template <class U>
constexpr explicit optional(optional<U>&& other);
```

```cpp
template <class U = T>
constexpr optional(U&& value);
```

```cpp
template <class U = T>
constexpr explicit optional(U&& value);
```

```cpp
template <class... Args>
constexpr explicit optional(in_place_t, Args&&... args);
```

```cpp
template <class U, class... Args>
constexpr explicit optional(in_place_t, ::std::initializer_list<U> list, Args&&... args);
```

This form is used on the Host only.

## Parameters

**Template Parameters**

T is the value type of the owning optional; U is the element type of the value or of the source optional, and Args... are the in-place construction argument types.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output (forwarded form) | The source value used to construct T. |
| `other` | Input/Output (movable source) | The source optional; an empty state stays empty, and an engaged value is copied or moved. |
| `args...` | Input/Output | Arguments forwarded to the in-place construction of T. |
| `list` | Input | An initializer list used on the Host only; its elements remain valid until construction completes. |

## Return Value

No return value.

## Constraints

- T must be a valid object type; value construction and converting construction from a different optional type must be able to construct T, and forms with in_place tags and forms that conflict with conversion from optional itself are excluded. Implicit construction is used when the source is implicitly convertible to T; otherwise explicit construction is used. An empty source stays empty; the copy and move forms require the corresponding element construction to be valid.
- User-provided construction, allocation, and callable operations must be valid at the selected execution location; device instances must suit the target's non-throwing environment.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/optional>

bool example()
{
    asc::std::optional<int> empty;
    asc::std::optional<int> value = 7;
    asc::std::optional<int> placed(asc::std::in_place, 9);
    return !empty && value && *value == 7 && placed && *placed == 9;
}
```

## Related APIs

- [`asc::std::optional`](optional.md)
- [API list for this header](asc_std_optional.md)
