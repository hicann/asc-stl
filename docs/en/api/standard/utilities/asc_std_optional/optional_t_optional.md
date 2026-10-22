# asc::std::optional<T&>::optional

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

`asc::std::optional<T&>::optional` initializes an `optional<T&>` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::optional<T&>; template parameters and other members are provided by the owning class.
constexpr optional() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::optional<T&>; template parameters and other members are provided by the owning class.
constexpr optional(T& value) noexcept;
```

### Prototype 3

```cpp
// Excerpt of the declaration inside class asc::std::optional<T&>; template parameters and other members are provided by the owning class.
constexpr optional(asc::std::nullopt_t) noexcept;
```

### Prototype 4

```cpp
// Excerpt of the declaration inside class asc::std::optional<T&>; template parameters and other members are provided by the owning class.
constexpr optional(const asc::std::optional<T&>&) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The object being bound; the new optional holds a reference to it, and the object's lifetime must cover the optional's period of use. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `asc` | Input | The nullopt_t empty-state tag (the nullopt constant); constructs an empty optional holding no reference. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `parameter 1` | Input | The source optional<T&> of the copy; the new object binds to the same target it references. |

## Return Value

No return value.

## Constraints

- The reference specialization only allows safe same-type lvalue binding.
- Borrowed-pointer semantics are adopted; conversions that easily produce dangling references are not provided.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/optional>

bool example()
{
    int number = 7;
    asc::std::optional<int&> value(number);
    return value.has_value() && &*value == &number;
}
```

## Related APIs

- [API list for this header](asc_std_optional.md)
